#ifndef COMMON_H
/*! \file
\brief ������������ ���� ������ ������ ���������� common.c
*/
#define COMMON_H 1

#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>
#include <asm/types.h>

//! ������ �����������
struct destination {
	__u32 count; //!< ���������� ����������� � ������
	struct destination_item *destinations; //!< �����������
};

//! �����������
struct destination_item {
	__u32 id; //!< �������������
	struct in_addr network; //!< ����� ����
	struct in_addr netmask; //!< ����� ����
	__u32 destination; //! ������������� �����������
};

//! ���������� ������������� ����������� � ����������� �� ������ �����������
int get_service_type(__u32 daddr,struct destination *destination);

#endif
