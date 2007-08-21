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

//! ������� ����� ������ �����. � ������ ������� ���������� NULL
struct networks_list *create_networks_list();

//! ��������� ����� ������� � ������ �����, ���� after_item ����� NULL, �� ������� ����������� � ������. � ��������� ������ ������� ����������� ����� after_item. ��� ������ ���������� NULL.  
struct network_item *add_item_networks_list(struct networks_list *networks_list, struct network_item *after_item);

//! ������� ������� item �� ������ �����. � ������ ���� ������� ����� NULL ��������� ��������� �������. ���������� ���������� ���������� ��������� ��� -1 � ������ ������.
int del_item_networks_list(struct networks_list *networks_list, struct network_item *item);

//! ������� ������ �����. ���������� -1 � ������ ������, � ������ �������� ���������� ���������� 0;
int destroy_networks_list(struct networks_list *networks_list);

//! ������������ ����� ����������� ������������ � �������� ip. � ������ �������� ������ ���������� �����������, � ��������������� ������ ���������� NULL.
struct traffic_item *search_destination(struct networks_list *networks_list, struct in_addr ip);

#endif /*NETWORKS_H_*/
