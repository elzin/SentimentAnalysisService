#include "stdafx.h"
#include "CBaseLoadManager.h"

namespace SS
{
namespace Core
{
namespace ResourceManagers
{

CBaseLoadManager::CBaseLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
								   : m_pLoadManager(pLoadManager)
{
}

void CBaseLoadManager::Create( TCoreLibrary CoreLibrary, 
							   const GUID& guidEntity, const GUID& iidInterface, void** ptssBase, const wchar_t* wszPath)
{

	//������� ������ ��������
	m_oControlDynamicLibrary.CreateInstance(&guidEntity, ptssBase, CoreLibrary, wszPath);

	SS::Interface::IBase* pBase=(SS::Interface::IBase*)*ptssBase;
	pBase->QueryInterface(iidInterface, ptssBase);
	pBase->SetLoadManager(m_pLoadManager);
};

///�������� �������� � ������� ������� ���������� ��� ����������� �� ����� dll
void CBaseLoadManager::Create( const wchar_t* wszDllName, 
							   const GUID& guidEntity, const GUID& iidInterface, void** ptssBase, const wchar_t* wszPath)
{
	//������� ������ �������� �� ����� dll
	m_oControlDynamicLibrary.CreateInstance(&guidEntity, ptssBase, wszDllName, wszPath);
	
	SS::Interface::IBase* pBase=(SS::Interface::IBase*)*ptssBase;
	pBase->QueryInterface(iidInterface, ptssBase);
	pBase->SetLoadManager(m_pLoadManager);
}

}
}
}