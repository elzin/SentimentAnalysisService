/** \mainpage
1. ����� ��������
	����������� ��������� ������ CoSeDi.dll.\n
	������ ������ ������������� � ������� ������������ ���������, �������������� ����������� �� ������� �������������� ������������ ����������� ���.\n
	������ ���������� �� ����� ���������������� C++ � �������������� ���������������� ������� �� ����� ���������� Microsoft Visual Studio .Net, ���������� STL.\n\n

2. �������������� ����������
	�������� ���������� ������ - ���������� ������ ����������� �� ������ � �������-������������� ��������

3. �������� ���������� ���������
	������ ������������� ��������� ����������:
		1. ISemanticClassesTree - �������� ����� ������� �� ������ � ������� ������������� �������
		2. ISemanticIDSourceTree - �������� ����� �������, ����������� ��� ������ � ������� �����
		3. ISemanticAnalysis - �������� ����� ������� ��� �������������� �������
		4. ISyntaxAnalysis - ��������� ��� ��������������� �������
		5. ISyntaxConstructions - ��������� ��� ������ � ��������������� �������������, ��������� ���������, ������� � �������� � ���������� ������������� 
		6. ISyntaxConstructionGroups - ��������� ��� ������ � �������� �������������� �����������, �������� ����� ������� �� ��������, �������� � ������ � �������� ����������� 
		7. ICombinatoryAnalysis	- ��������� ��� �������������� ������� 
		8. ICoSeDiLoad - ��������� ��� �������� �������
		9. ICoSeDiManager - ���������, ����������� ������� ����������� ���������� �������������� �������			 

4. ������������ ����������� ��������
	������������ ����������� ����������� ����, �� ������� ����� ���� ����������� �� Windows.\n\n

5. ����� � ��������
	5.1. �������� ������ �������������� ����������� ����� ������ ���������� CManagerConnections,
	������� ��� �� ��������� ��� ����� ���������� IConnection,  IManagerConnections, ISubConnection.\n\n
	5.2. ����� ����� ���.\n\n

6. ������� ������
	���.\n\n

7. �������� ������
	���.\n\n

*/
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <atldbcli.h>

#include <algorithm>

#include "..\ASCInterface\defines.h"

USES_LOAD_MANAGER;
//using namespace std;

// TODO: reference additional headers your program requires here
