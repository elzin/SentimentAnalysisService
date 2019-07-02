//SyntaxConstructionsTest.cpp

#include "StdAfx.h"
#include ".\syntaxconstructionstest.h"

namespace SS
{
namespace UnitTests
{
namespace SyntaxConstructions
{
	
	///�����������
	CSyntaxConstructionsTest::CSyntaxConstructionsTest(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager) : 
		m_pSyntaxConstructionsManagerSQL(NULL)
	{
		SS_TRY
		{
			if (!pLoadManager)
			{ SS_THROW(L"�� ���������� LoadManager."); }
			m_pLoadManager = pLoadManager;
		}
		SS_CATCH(L"");
	}

	///���������� �������� ��� ������ � �������������
	void CSyntaxConstructionsTest::SetConstructionsManager()
	{
		SS_TRY
		{
			m_pSyntaxConstructionsManagerSQL = (SS::Interface::Core::SyntaxConstructions::ISyntaxConstructionsManager*)
			m_pLoadManager->GetInterface(L"./core/linguistics/SyntaxConstructions.dll", CLSID_ISyntaxConstructionManagerEng, IID_ISyntaxConstructionManagerSQL);		
		}
		SS_CATCH(L"")
	}

	///���� ������ ����������� DBMS
	void CSyntaxConstructionsTest::TestToBinary()
	{
		SS_TRY
		{
			CoInitialize(NULL);
			SetConstructionsManager();
			m_pSyntaxConstructionsManagerSQL->ToBinary();
			std::cout << "Test OK! \n";
			CoUninitialize();
		}
		SS_CATCH(L"")
	}




}
}
}