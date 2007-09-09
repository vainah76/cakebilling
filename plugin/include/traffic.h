#ifndef TRAFFIC_H
/*! \file
\brief ������������ ���� ������ ���������� ��������� ������� traffic.c

*/
#define TRAFIC_H

#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <netinet/in.h>
#include <asm/types.h>

//! �������� ������������ ��� ����������� ����������� �������
#define OUTGOING 0
#define INCOMING 1
//! ��������� �������� ������ �����������
struct traffic_item {
	__u32 service_type; //!< ��� �����������
	__u64 in_traffic; //!< �������� ������
	__u64 out_traffic; //!< ��������� ������
	struct traffic_item *prev; //!< ���������� �������
	struct traffic_item *next; //!< ��������� �������
};

//! ������ � �������� �����������
struct traffic_list {
    unsigned long long count; //!< ���������� ����������� � ������
	struct traffic_item *first; //!< ������ ������
	struct traffic_item *curr; //!< ������� ������� ������
	struct traffic_item *last; //!< ����� ������
};

/*! \brief ������������� ������� �������

�������� ������� ������ �������� struct traffic_list, ����� ������������� ��� ��������� ��������� NULL
� ���������� ������� ��������� ������� � 0.\n
��� ������� ���������� ���������� ��������� �� ��������� ������� �������.\n
��� ��������� ���������� ���������� NULL.
*/
struct traffic_list *create_traffic_list();

/*! \brief ��������� ������� � ����� �������

�������� ������� ������ ��� ����� �������, ������������� ��� � ��������� ��� � ����� ������� manage_fifo,
����� ����������� ������� �������.\n
��� ������� ���������� ���������� ��������� �� ����� ������� �������.\n
��� ��������� ���������� ���������� NULL.
*/
struct traffic_item *add_item_traffic_list(struct traffic_list *traffic_list);

/*! \brief ������� ������� �� ������ �������

�������� ������ ��� ����� ���������� ��������, �������� ������� ����� ������� ������� �� �������
� ��������� ������� �������.
��� ������� ���������� � �� ������ ������� ���������� ��������� �� ����� ���������� �������� �������.\n
��� ��������� ���������� ��� ������ ������� ���������� NULL
*/
int del_item_traffic_list(struct traffic_list *traffic_list);

/*! \brief ����� �������� �� ������ ������� � ���� �������

������������ ����� �������� �� ������ ������� � ���� ������� � ������� manage_fifo.\n
��� ������� ���������� ������������� ��������� ������� manage_fifo->curr � ���������� ���.
��� ��������� ���������� ���������� NULL.
*/
struct traffic_item *search_traffic_list(struct traffic_list *traffic_list, __u32 service_type);

/*! \brief ������� �������.

������������ ������� ������� manage_fifo �� ���������.
*/
int destroy_network_list(struct traffic_list *traffic_list);

#endif
