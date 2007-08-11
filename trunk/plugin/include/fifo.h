#ifndef FIFO_H
/*! \file
\brief ������������ ���� ������ ���������� ��������� ������� fifo.c

*/
#define FIFO_H 1

#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include "destinations.h"

//! ��������� �������� ������� �������
struct traffic_item {
	__u64 in_traffic; //!< �������� ������
	__u64 out_traffic; //!< ��������� ������
	__u32 service_type; //!< ��� �����������
	struct traffic_item *prev; //!< ���������� �������
	struct traffic_item *next; //!< ��������� �������
};

//! ������� �������
struct fifo {
    unsigned long long count; //!< ������� ���������� ��������� � �������
	struct traffic_item *first; //!< ������ �������
	struct traffic_item *curr; //!< ������� ������� �������
	struct traffic_item *last; //!< ����� �������
};

/*! \brief ������������� ������� �������

�������� ������� ������ �������� struct fifo, ����� ������������� ��� ��������� ��������� NULL
� ���������� ������� ��������� ������� � 0.\n
��� ������� ���������� ���������� ��������� �� ��������� ������� �������.\n
��� ��������� ���������� ���������� NULL.
*/
struct fifo *init_fifo();

/*! \brief ��������� ������� � ����� �������

�������� ������� ������ ��� ����� �������, ������������� ��� � ��������� ��� � ����� ������� manage_fifo,
����� ����������� ������� �������.\n
��� ������� ���������� ���������� ��������� �� ����� ������� �������.\n
��� ��������� ���������� ���������� NULL.
*/
struct traffic_item *push_fifo(struct fifo *manage_fifo);

/*! \brief ������� ������� �� ������ �������

�������� ������ ��� ����� ���������� ��������, �������� ������� ����� ������� ������� �� �������
� ��������� ������� �������.
��� ������� ���������� � �� ������ ������� ���������� ��������� �� ����� ���������� �������� �������.\n
��� ��������� ���������� ��� ������ ������� ���������� NULL
*/
struct traffic_item *pop_fifo(struct fifo *manage_fifo);

//! ������� ����� �������
struct fifo *copy_fifo(struct fifo *manage_fifo);

/*! \brief ����� �������� �� ������ ������� � ���� �������

������������ ����� �������� �� ������ ������� � ���� ������� � ������� manage_fifo.\n
��� ������� ���������� ������������� ��������� ������� manage_fifo->curr � ���������� ���.
��� ��������� ���������� ���������� NULL.
*/
struct traffic_item *search_fifo(struct fifo *manage_fifo, __u32 service_type);

/*! \brief ������� �������.

������������ ������� ������� manage_fifo �� ���������.
*/
void flush_fifo(struct fifo *manage_fifo);

#endif
