#ifndef DESTINATIONS_H_
#define DESTINATIONS_H_

#include <netinet/in.h>
#include <asm/types.h>

//! �������� ������������ ��� ����������� ����������� �������
#define OUTGOING 0
#define INCOMING 1

//! ������ �����������
struct destinations_list {
	struct destination *destinations; //!< ������ �����������
	__u32 count; //!< ���������� ����������� � ������
};

//! �����������
struct destination {
	__u32 id; //!< �������������
	struct network *networks; //!< ������ �����
	__u32 count; //!< ���������� ����� � ������
};

//! ����
struct network {
	struct in_addr network; //!< ����� ����
	struct in_addr netmask; //!< ����� ����
};

//! ������� ����� ����������� � �������������� id � �������� ����� ������ count, ���� count ����� ����, �� ������ ����� �� ���������. � ������ ������ ���������� NULL
struct destination *create_destination(__u32 id, __u32 count);

//! ������� ����� ������ ����� ������ count ��� ������������� ����������� 
struct network *create_destination_network_list(struct destination *destination, __u32 count);

//! �������� ���� ��� �������� index � ������ ����� ����������� destination, � ������ ������� ���������� -1
int set_destination_network(struct destination *destination, __u32 index, struct in_addr network, struct in_addr netmask);

//! ����������� ������ ������� ������������ destination, ���������� NULL ��� ���������� ��������� ����� ����������� ������ 
struct destination *delete_destination(struct destination *destination);

//! ������� ����� ������ ����������� ������� count, ���� �� count ����� ���� �� ������ ����� �� ���������. � ������ ������ ���������� NULL
struct destinations_list *create_destinations_list(__u32 count);

//! ����������� ������ ������� ������� �����������, ���������� NULL ��� ���������� ��������� ����� ������������ ������.
struct destination_list *delete_destinations_list(struct destinations_list *destinations_list);
#endif /*DESTINATIONS_H_*/
