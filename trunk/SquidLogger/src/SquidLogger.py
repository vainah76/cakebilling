#!/usr/bin/python

from twisted.internet.protocol import DatagramProtocol
from twisted.internet import reactor
import MySQLdb
from time import localtime, strftime, time, mktime


class DbLogger:
    "Db Logger for Squid"
    proxy_servers = {}
    proxy_userips = {}
    traffics = {}
            
    def __init__(self, host, user, password, database, interval):
        self.host = host
        self.user = user
        self.password = password
        self.database = database
        self.interval = interval
        self.connection = MySQLdb.connect(host,user,password,database)
        self.connection.autocommit(1)
        self.cursor = self.connection.cursor()
        self.get_proxy_servers()
        self.get_proxy_user_ips()
        self.get_traffic(strftime("%Y-%m-%d %H:%M:%S",localtime(time()-time()%interval)))

    def get_proxy_servers(self):
        self.cursor.execute("select id,ip from proxy_server")
        rows = self.cursor.fetchall()
        for i in xrange(len(rows)):
            self.proxy_servers[rows[i][1]] = rows[i][0]
        print self.proxy_servers
    
    def get_traffic(self, starttime):
        self.cursor.execute("select proxy_user_ip_id,proxy_server_id,starttime,period,id from traffic where starttime = %s", starttime)
        rows = self.cursor.fetchall()
        for i in xrange(len(rows)):
            self.traffics[(rows[i][0],rows[i][1],mktime(rows[i][2].timetuple()),rows[i][3])] = rows[i][4]
        print self.traffics

    def get_proxy_user_ips(self):
        self.cursor.execute("select id, ip from proxy_user_ip")
        rows = self.cursor.fetchall()
        for i in xrange(len(rows)):
            self.proxy_userips[rows[i][1]] = rows[i][0]
        print self.proxy_userips

    def update_trafic(self,proxy_user_ip_id,proxy_server_id,starttime,interval,inbytes,outbytes,cached):
        ttime = strftime("%Y-%m-%d %H:%M:%S",localtime(starttime-starttime%interval))
        try:
            traffic_id = self.traffics[(proxy_user_ip_id,proxy_server_id,starttime-starttime%interval,interval)]
        except StandardError:
            self.cursor.execute("insert into traffic (proxy_user_ip_id,proxy_server_id,starttime,period) values(%s,%s,%s,%s)", (proxy_user_ip_id,proxy_server_id,ttime,interval))
            traffic_id = self.connection.insert_id()
            self.get_traffic(ttime)
        if cached:
            self.cursor.execute("update traffic set cinbytes=cinbytes+%s,coutbytes=coutbytes+%s where id=%s",(inbytes,outbytes,traffic_id))
        else:
            self.cursor.execute("update traffic set inbytes=inbytes+%s,outbytes=outbytes+%s where id=%s",(inbytes,outbytes,traffic_id))
            
    def save(self,time,proxy,host,request,reply,server,url,status):
        savetime = float(time)
        if status in ('TCP_MEM_HIT','TCP_REFRESH_HIT','TCP_HIT'):
            print "cached/serverid %d: time:%s hostid:%d recived:%s send:%s server:%s url:%s" % (self.proxy_servers[proxy],strftime("%Y-%m-%d %H:%M:%S",localtime(savetime)),self.proxy_userips[host],request,reply,server,url)
            self.update_trafic(self.proxy_userips[host], self.proxy_servers[proxy], savetime, self.interval, request, reply, 1)
        else:
            print "not cached/serverid %s: time:%s hostid:%d recived:%s send:%s server:%s url:%s" % (self.proxy_servers[proxy],strftime("%Y-%m-%d %H:%M:%S",localtime(savetime)),self.proxy_userips[host],request,reply,server,url)
            self.update_trafic(self.proxy_userips[host], self.proxy_servers[proxy], savetime, self.interval, request, reply, 0)
 

class SquidParser(DatagramProtocol):

    def __init__(self, logger):
        self.logger = logger
        self.__init__
        
    def parseLog(self, proxy, log):
	data = log.split()
	time = data[0]
	status = data[1]
	host = data[2]
	request = data[3]
	reply = data[4]
	server = data[5]
	url = data[6]
	self.logger.save(time,proxy,host,request,reply,server,url,status)

    def datagramReceived(self, data, (host, port)):
	logs = data.splitlines()
	for log in logs:
	    self.parseLog(host,log)

dblogger = DbLogger("localhost","squid","squidpw","squidlogger",3600)
reactor.listenUDP(9999, SquidParser(dblogger))
reactor.run()
