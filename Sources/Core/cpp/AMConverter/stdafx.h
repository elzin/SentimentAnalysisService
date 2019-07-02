/** \mainpage
1. ����� ��������
����������� ��������� ������ AMConverter.dll � ������ ����������� ��������� (���������������, ������������� � ��������������) �������������\n
������ ������ ������������� � ������� ������������ ���������. �������������� ����������� �� ������� �������������� ������������ ����������� ���. \n
������ ���������� �� ����� ���������������� C++ � �������������� ���������������� ������� �� ����� ���������� Microsoft Visual Studio .Net, ���������� STL \n
\n

2. �������������� ����������
������ ������ ������ ��������� ������:\n
�	����������� ��������������� �������������\n
�	����������� ������������� �������������\n
�	����������� �������������� �������������\n
\n
������ ������������ �����������:\n
�	SS::Interface::Core::IAMConverterMorpho - ��������� ����������� ��������������� ������������\n
�	SS::Interface::Core::IAMConverterSyntax - ��������� ����������� �������������� �������������\n
�	SS::Interface::Core::IAMConverterSyntaxAposteriori - ��������� ����������� �������������� �������������� �������������\n
�	SS::Interface::Core::IAMConverterSemantic - ��������� ����������� ������������� ������������\n
\n

3. ������������ ����������� ��������
������������ ����������� ����������� ����, �� ������� ����� ���� ����������� �� Windows. \n
\n
4. ����� � ��������
	4.1. �������� ������ �������������� ����������� ����� ������ ���������� CManagerConnections\n\n

	4.2. ����� ����� ���.\n\n

5. ������� ������
	���.\n\n

6. �������� ������
	���.\n\n

*/
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define  _WIN32_WINNT 0x0403 
#define APP_ID "AMConverter"
#define NWLIB_SS_FRAMEWORK

// Windows Header Files:

// Windows Header Files:
#include <tchar.h>
#include "../[libs]/FirstHeader.h"
#include <windows.h>
#include <atldbcli.h>
#include "stl.h"

#include "..\ASCInterface\defines.h"
USES_LOAD_MANAGER;

#include "..\FeatureLibrary\define.h"
#include "..\ASSInterface\IAMConverter.h"
#include "..\ASSInterface\TDictionaryManager.h"

// TODO: reference additional headers your program requires here
