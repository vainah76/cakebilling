#ifndef NETWORKS_H_
#define NETWORKS_H_

#include <netinet/in.h>
#include <asm/types.h>

//! ������ �����
struct networks_list {
	struct network_item *first; //!< ������ ������
	struct network_item *last; //!< ����� ������
	struct network_item *curr; //!< ������� ������� ������
	__u32 count; //!< ���������� ����������� � ������
};

//! ��������� �������� ������ �����������
struct network_item {
	struct in_addr network; //!< ����� ����
	struct in_addr netmask; //!< ����� ����
	struct traffic_item *destination; //!< ��������� �� �����������
	struct network_item *prev; //!< ��������� �� ���������� �������
	struct network_item *next; //!< ��������� �� ��������� �������
};

#endif /*NETWORKS_H_*/
