#pragma once

#include <math.h>
#include "..\ASCInterface\IDBMS.h"

#undef  DBMS_SRC_FILE
#define DBMS_SRC_FILE "fn_HashFunc.h"

///	������� ��� ����������� ������� CRC16
extern UINT16 Crc16Tbl[256];

///	������� ��� ����������� ������� CRC32
extern UINT32 Crc32Tbl[256];
