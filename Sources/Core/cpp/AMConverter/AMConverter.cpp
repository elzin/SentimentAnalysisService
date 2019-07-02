/// AMConverter.cpp : Defines the entry point for the DLL application.
///

#include "stdafx.h"
#include "AMConverter.h"

#include "CoConverter.h"

#include ".\TestRunner.h"

/** \mainpage

1.	����� �������� \n
AMConverter.dll ����������� ��������� ������, � ������������ ����������� ��������. 
����������: ����������� � ������������� ��������������� ���������� ����, ���������� � ��������������� �������.
������ ������ ������������� � ������� ������������ ��������� �������������� ����������� �� ������� �������������� ������������ ����������� ���.
������ ���������� �� ����� ���������������� C++ � �������������� ���������������� ������� �� ����� ���������� Microsoft Visual Studio .Net. \n
2.	 �������������� ���������� \n
������ ������ ������ ��������� ������: \n
�	����������� ��������������� ����������. \n
�	������������� ��������������� ����������. \n
�	�������������� ����������� ����� ������ ��� ����������� ������� ��������������� �������������. \n
�������������� ����������� ���. \n
3.	������������ ����������� �������� \n
������������ ����������� ����������� ����, �� ������� ����� ���� ����������� �� Windows. \n
4.	����� � �������� \n
4.1. �������� ������ ���������� �� ����� ���������� ������������ ��������� �������� ����� dll. ����� ������� ���������� ����� ��������� IAMConverter. \n
4.2. ����� �����: \n
�	DllMain \n
�	CreateInstance � ����� �����, ��� ���������� ����������� SS \n
5.	������� ������ \n
5.1	��������� �� �������� CMorphoFeature  \n
5.2	����� ���������� ���� ������ int, ���������� ���������� ��� �������������. \n
6.	�������� ������ \n
6.1	��������� �� �������� CMorphoFeature \n
6.2	����� ���������� �� ��� ������ int, ���������� ������ ��������������� ���������� ����� ����������� ����������, ������������ � ��������� CMorphoFeature. \n

*/

SET_LOAD_MANAGER_IMPLEMENTATION;

///����� ����������
/// ���� � ������

HRESULT CreateInstance(const GUID* pGuid, void** pBase)
{

	try
	{
		if(*pGuid == CLSID_AMConverterMorpho)
			*pBase = (SS::Interface::IBase*)new SS::Core::Features::CCoConverter();
		else
			if(*pGuid == CLSID_AMConverterSyntax)
				*pBase = (SS::Interface::IBase*)new SS::Core::Features::CCoConverter();
		else
			if(*pGuid == CLSID_AMConverterSemantic)
				*pBase = (SS::Interface::IBase*)new SS::Core::Features::CCoConverter();
		else 
			if(*pGuid==CLSID_TestRunner)
				*pBase=(SS::Interface::IBase*)
				new SS::UnitTests::AMConverter::CTestRunner();	
		else
			*pBase = NULL;
	
		return S_OK;
	}
	catch (...) {
		return E_FAIL;
	}
	
}



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

