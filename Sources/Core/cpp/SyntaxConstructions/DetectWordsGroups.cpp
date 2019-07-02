//DetectWordsGroups.cpp

#include "StdAfx.h"
#include ".\detectwordsgroups.h"

//�����������
SS::SyntaxConstructions::SQL::CDetectWordsGroups::CDetectWordsGroups(wchar_t* szBaseName) : SS::CConnectSQL(szBaseName)
{
}

//������� ������ ���� ��� ��������������
bool SS::SyntaxConstructions::SQL::CDetectWordsGroups::CreateDetectWordsGroup(
													SS::SyntaxConstructions::Types::TDetectWordsGroup & oDetectGroup)
{
	SS_TRY
	{		
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::Syntax;
		//��������� ���������� �� ������ � ����� ������
		CPreparedSDetectWordsGroupsByDetectWordsGroupName oPreparedSDetectWordsGroupsByDetectWordsGroupName;	
		oPreparedSDetectWordsGroupsByDetectWordsGroupName.Prepare(*m_pConnection->GetSession());		
		oPreparedSDetectWordsGroupsByDetectWordsGroupName.SetDetectWordsGroupName(m_wsDetectWordsGroupName);		
		if (oPreparedSDetectWordsGroupsByDetectWordsGroupName.Open() != S_OK)
		{
			oPreparedSDetectWordsGroupsByDetectWordsGroupName.Close();
			SS_THROW(L"�������� ��������� ��������: �� ������� ��������� ������ � ���� �� �������� ������");
		}
		else if (oPreparedSDetectWordsGroupsByDetectWordsGroupName.MoveFirst() == S_OK)
		{
			//����� ������ ��� ����������
			oPreparedSDetectWordsGroupsByDetectWordsGroupName.Close();
			SS_THROW(L"�������� ��������� ��������: ������ ���� ��� �������������� � ����� ������ ��� ����������");
		}
		else oPreparedSDetectWordsGroupsByDetectWordsGroupName.Close();

		//��������� ���������� ������
		CPreparedIDetectWordsGroups oPreparedIDetectWordsGroups;
		oPreparedIDetectWordsGroups.Prepare(*m_pConnection->GetSession());
		oPreparedIDetectWordsGroups.SetDetectWordsGroupName(m_wsDetectWordsGroupName);		

		for (SS::SyntaxConstructions::Types::TDetectWordsGroup::iterator iter = oDetectGroup.begin();
			 iter != oDetectGroup.end(); ++iter)
		{
			oPreparedIDetectWordsGroups.SetDetectWord((*iter));		
			//�� ������� ��������� ����������
			if(oPreparedIDetectWordsGroups.Open() != S_OK)
			{
				oPreparedIDetectWordsGroups.Close();
				//������� � ���� ��� ��, ��� ������ �������
				DeleteDetectWordsGroup();
				SS_THROW(L"�������� ��������� ��������: ������ ��� �������� ���������� � ������");
			}
			//��������� ����������
			oPreparedIDetectWordsGroups.Close();
		}
	}
	SS_CATCH(L"")
	return true;
}

//��������� � �������� ��� ��������� ������ 
bool SS::SyntaxConstructions::SQL::CDetectWordsGroups::ToBinary()
{
	SS_TRY
	{
		std::wstring wDataTableName = L"DetectWordsGroups";		
		m_pDataBase->MoveToDataTable(wDataTableName.c_str());
		SS::Interface::Core::DBMS::IDataTable* pDTable = m_pDataBase->OpenDataTable();
		
		if ( (pDTable==NULL) || (!pDTable->IsOpen()) )
		{ SS_THROW(L"������ ��� �������� ������� Combinatory"); }
		
		//�������� �������
		pDTable->Clear();

		SS::SyntaxConstructions::Types::SDetectWordGroupName oDetectWordGroupName;
		void* TableRecord[] = 
		{
			&oDetectWordGroupName.m_wsDetectWordGroupName,
			&oDetectWordGroupName.m_wsDetectWord			
		};
		
		if (pDTable->AddInit(TableRecord) != S_OK)  
		{ SS_THROW(L"������ AddInit ��� ������� Combinatory"); }	

		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::Syntax;
		//��������� ���������� �� ������ � ����� ������
		CPreparedSDetectWordsGroups oPrepared;	
		oPrepared.Prepare(*m_pConnection->GetSession());		
		
		if(oPrepared.Open() != S_OK)
		{
			oPrepared.Close();
			SS_THROW(L"�������� ��������� ��������: �� ������� ��������� ������ � ���� �� �������� ������.");
		}
		
		if (oPrepared.MoveFirst() != S_OK)
		{
			oPrepared.Close();
			SAVE_LOG( SS_MESSAGE AND __WFUNCTION__ AND L"�������� ��������� ��������: ������ � ���� ������ ������ ������ ���� ��� ��������������");
			oPrepared.Close();
			pDTable->Close();
			return true;
		} 
		do
		{
			oPrepared.GetDetectWordsGroupName(oDetectWordGroupName.m_wsDetectWordGroupName);
			oPrepared.GetDetectWord(oDetectWordGroupName.m_wsDetectWord);
			pDTable->Add();
		}
		while (oPrepared.MoveNext() == S_OK);
		oPrepared.Close();
		pDTable->Close();
	}
	SS_CATCH(L"")
	return true;
}

//������� ������� ������ ���� ��� ��������������
void SS::SyntaxConstructions::SQL::CDetectWordsGroups::DeleteDetectWordsGroup()
{
	SS_TRY
	{
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::Syntax;
		//������� ������
		CPreparedDDetectWordsGroups oPreparedDDetectWordsGroups;
		oPreparedDDetectWordsGroups.Prepare(*m_pConnection->GetSession());
		oPreparedDDetectWordsGroups.SetDetectWordsGroupName(m_wsDetectWordsGroupName);		
		oPreparedDDetectWordsGroups.Open();
		oPreparedDDetectWordsGroups.Close();
	}
	SS_CATCH(L"")
}

//���������� ��� �������� ������ ���� ��� ��������������
void SS::SyntaxConstructions::SQL::CDetectWordsGroups::GetWords(
											SS::SyntaxConstructions::Types::TDetectWordsGroup & oDetectGroup)
{
	SS_TRY
	{
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::Syntax;
		//��������� ���������� �� ������ � ����� ������
		CPreparedSDetectWordsGroupsByDetectWordsGroupName oPreparedSDetectWordsGroupsByDetectWordsGroupName;	
		oPreparedSDetectWordsGroupsByDetectWordsGroupName.Prepare(*m_pConnection->GetSession());		
		oPreparedSDetectWordsGroupsByDetectWordsGroupName.SetDetectWordsGroupName(m_wsDetectWordsGroupName);		
		
		if (oPreparedSDetectWordsGroupsByDetectWordsGroupName.Open() != S_OK)
		{
			std::wstring wsMessage = L"�������� ��������� ��������: �� ������� ��������� ������ � ���� �� �������� ������.";
			wsMessage += L"��� ������ ���� ��� �������������� : ";
			wsMessage += m_wsDetectWordsGroupName;
			oPreparedSDetectWordsGroupsByDetectWordsGroupName.Close();
			SS_THROW((wchar_t*)wsMessage.c_str());
		}
		
		if (oPreparedSDetectWordsGroupsByDetectWordsGroupName.MoveFirst() != S_OK)
		{
			std::wstring wsMessage = L"�������� ��������� ��������: ������ ���� ��� �������������� � ����� ������ �����������. ";
			wsMessage += L"��� ������ ���� ��� �������������� : ";
			wsMessage += m_wsDetectWordsGroupName;
			oPreparedSDetectWordsGroupsByDetectWordsGroupName.Close();
			SS_THROW((wchar_t*)wsMessage.c_str());
		} 
		
		do
		{
			std::wstring wsDetectWord;
			oPreparedSDetectWordsGroupsByDetectWordsGroupName.GetDetectWord(wsDetectWord);
			oDetectGroup.insert(wsDetectWord);
		}
		while (oPreparedSDetectWordsGroupsByDetectWordsGroupName.MoveNext() == S_OK);
		oPreparedSDetectWordsGroupsByDetectWordsGroupName.Close();
	}
	SS_CATCH(L"")
}

//������� ������� ����� ��������� �� ������ ���� ��� �������������� � ������������� �����
void SS::SyntaxConstructions::SQL::CDetectWordsGroups::SetWords(SS::SyntaxConstructions::Types::TDetectWordsGroup& oDetectGroup)
{
	DeleteDetectWordsGroup();
	CreateDetectWordsGroup(oDetectGroup);
}

//���������� ������ �� ����� � ������ ��� ��������������
bool SS::SyntaxConstructions::SQL::CDetectWordsGroups::IsDetectWord(std::string& sDetectWord)
{
	SS_TRY
		SS_THROW(L"������ ������� �� ������������� ��� ������ � ������ �������");
	SS_CATCH(L"")
	return false;
}

//*************************************** DBMS ***************************************

//�����������
SS::SyntaxConstructions::DBMS::CDetectWordsGroups::CDetectWordsGroups(wchar_t* szBaseName)
	: 
	SS::CConnectDBMS(szBaseName),
	m_TableInited(false)
{
	TableRecord[0] = &m_oDetectWordGroupName.m_wsDetectWordGroupName; 
	TableRecord[1] = &m_oDetectWordGroupName.m_wsDetectWord;
}

//������������� ���������� � ��������
void SS::SyntaxConstructions::DBMS::CDetectWordsGroups::InitConnection()
{
	SS_TRY
	{
		std::wstring wTable = L"DetectWordsGroups";
		SS::CConnectDBMS::SetTable(wTable);
				
		if ( m_pDTable->FindInit(L"DetectWordsGroupName", &m_oDetectWordGroupName.m_wsDetectWordGroupName, TableRecord, efmByDetectWordGroupName) != S_OK )   
		{ SS_THROW(L"������ ������������� ������ �� ���� ID"); }

		if ( m_pDTable->FindInit(L"DetectWord", &m_oDetectWordGroupName.m_wsDetectWord, TableRecord, efmByDetectWord) != S_OK )   
		{ SS_THROW(L"������ ������������� ������ �� ���� Name"); }
		
		if ( m_pDTable->ScanInit(0, TableRecord) != S_OK )   
		{ SS_THROW(L"������ ������������� ������ �� ���� Name"); }

		m_TableInited = true;
	}
	SS_CATCH(L"")
}

//���������� ��� �������� ������ ���� ��� ��������������
void SS::SyntaxConstructions::DBMS::CDetectWordsGroups::GetWords(
												SS::SyntaxConstructions::Types::TDetectWordsGroup & oDetectGroup)
{
	SS_TRY
	{
		if (!m_TableInited) 
		{ InitConnection(); }

		m_oDetectWordGroupName.m_wsDetectWordGroupName = m_wsDetectWordsGroupName;

		while ( m_pDTable->Find(efmByDetectWordGroupName) == S_OK )   
		{ oDetectGroup.insert(m_oDetectWordGroupName.m_wsDetectWord); }
	}
	SS_CATCH(L"")
}

//������� ������� ����� ��������� �� ������ ���� ��� �������������� � ������������� �����
void SS::SyntaxConstructions::DBMS::CDetectWordsGroups::SetWords(SS::SyntaxConstructions::Types::TDetectWordsGroup& oDetectGroup)
{
	SS_TRY
		SS_THROW(L"������ ������� � ������� ������ �� ��������");
	SS_CATCH(L"")
}

//���������� ������ �� ����� � ������ ��� ��������������
bool SS::SyntaxConstructions::DBMS::CDetectWordsGroups::IsDetectWord(std::string & sDetectWord)
{
	SS_TRY
		SS_THROW(L"������ ������� � ������� ������ �� ��������");
	SS_CATCH(L"")
	return false;
}

//C������ ������ ���� ��� ��������������
bool SS::SyntaxConstructions::DBMS::CDetectWordsGroups::CreateDetectWordsGroup(SS::SyntaxConstructions::Types::TDetectWordsGroup& oDetectGroup)
{
	SS_TRY
		SS_THROW(L"������ ������� � ������� ������ �� ��������");
	SS_CATCH(L"")
	return false;
}

///������� ������� ������ ���� ��� ��������������
void SS::SyntaxConstructions::DBMS::CDetectWordsGroups::DeleteDetectWordsGroup()
{
	SS_TRY
		SS_THROW(L"������ ������� � ������� ������ �� ��������");
	SS_CATCH(L"")
}





