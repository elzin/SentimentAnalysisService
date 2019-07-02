// CoSeDi.cpp : Defines the entry point for the DLL application.
//

#pragma once

#include "stdafx.h"

#include ".\CoSeDi.h"


#include ".\CoSeDiManager.h"
#include ".\SemanticClassesTree.h"
#include ".\SemanticAnalysis.h"
#include ".\TestRunner.h"

SET_LOAD_MANAGER_IMPLEMENTATION;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

/// ������� ����� �� ������� ������������ ������
/** 
	\param *pGuid - GUID ������, ������� ���������� �������
	\param **ppBase - ��������� �� ��������� IBase, ������� ��������� ��������� �����
	\return HRESULT - ��������� ���������� ��������
 */
HRESULT CreateInstance(const GUID *pGuid, void **ppBase)
{
	if(*pGuid == CLSID_ICoSeDiManager)
		*ppBase=(SS::Interface::IBase*)
		new SS::CoSeDi::CCoSeDiManager();	
	else 
		if(*pGuid==CLSID_TestRunner)
			*ppBase=(SS::Interface::IBase*)
			new SS::UnitTests::CoSeDi::CTestRunner();	
	else
			*ppBase=NULL;

	return S_OK;
};