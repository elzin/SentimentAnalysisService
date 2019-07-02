//SyntaxConstructionGroups.cpp

#include "StdAfx.h"
#include ".\syntaxconstructiongroups.h"

//��������� ������� ���� (m_iConstructionId, m_ConstructionGroupId) � ����
bool SS::SyntaxConstructions::SQL::CSyntaxConstructionGroups::Add()
{
	SS_TRY
	{
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::ConstructionGroups;
		CPreparedConstructionGroupsI oPrepared;
		oPrepared.Prepare(*m_pConnection->GetSession());
		oPrepared.SetIDConstruction((long)m_GroupAndConstruction.m_i32IDConstruction);
		oPrepared.SetIDGroup((short)m_GroupAndConstruction.m_i32IDGroup);
		oPrepared.Open();
		oPrepared.Close();
	}	
	SS_CATCH(L"");
	return true;
}

//������������ ��� ���� (m_iConstructionId, m_ConstructionGroupId), �������� � ����
bool SS::SyntaxConstructions::SQL::CSyntaxConstructionGroups::Get(
								std::list<SS::SyntaxConstructions::Types::SGroupAndConstruction >& listConstructionGroups)
{
	SS_TRY
	{
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::ConstructionGroups;
		SS::SyntaxConstructions::Types::SGroupAndConstruction oGroupAndConstruction;
		CPreparedConstructionGroupsSAll oPrepared;
		oPrepared.Prepare(*m_pConnection->GetSession());
		
		if (oPrepared.Open() == S_OK)
		{
			if (oPrepared.MoveFirst() != DB_S_ENDOFROWSET)
			{					
				do
				{
					oGroupAndConstruction.m_i32IDGroup = oPrepared.GetIDGroup();
					oGroupAndConstruction.m_i32IDConstruction = oPrepared.GetIDConstruction();
					listConstructionGroups.push_back(oGroupAndConstruction);
				}
				while (oPrepared.MoveNext() != DB_S_ENDOFROWSET);					
			}
		}
		oPrepared.Close();
	}
	SS_CATCH(L"");
	return true;
}

///��������� � �������� ��� ��������� ������ 
bool SS::SyntaxConstructions::SQL::CSyntaxConstructionGroups::ToBinary()
{
	SS_TRY
	{
		std::wstring wDataTableName = L"SyntaxConstructionGroups";		
		m_pDataBase->MoveToDataTable(wDataTableName.c_str());
		SS::Interface::Core::DBMS::IDataTable* pDTable = m_pDataBase->OpenDataTable();
		
		if ( (pDTable == NULL) || (!pDTable->IsOpen()) )
		{ SS_THROW(L"������ ��� �������� ������� SyntaxConstructionGroups"); }
		
		//������ DBMS �������
		pDTable->Clear();
		//��������� ��� ���������� �������
		SS::SyntaxConstructions::Types::SGroupAndConstruction oGroupAndConstruction;
		void* TableRecord[] = 
		{
			&oGroupAndConstruction.m_i32IDConstruction,
			&oGroupAndConstruction.m_i32IDGroup			
		};

		if ( pDTable->AddInit(TableRecord) != S_OK )  
		{ SS_THROW(L"������ AddInit ��� ������� SyntaxConstructionGroups."); }	
		
		//��������� ���������� �� ������ � ����� ������
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::ConstructionGroups;
		CPreparedConstructionGroupsSAll oPrepared;
		oPrepared.Prepare(*m_pConnection->GetSession());
		
		if (oPrepared.Open() == S_OK)
		{
			if (oPrepared.MoveFirst() != DB_S_ENDOFROWSET)
			{					
				do
				{
					oGroupAndConstruction.m_i32IDConstruction	= oPrepared.GetIDConstruction();
					oGroupAndConstruction.m_i32IDGroup			= oPrepared.GetIDGroup();
					pDTable->Add();
				}
				while (oPrepared.MoveNext() != DB_S_ENDOFROWSET);
			}
		}
		oPrepared.Close();
		pDTable->Close();
		ToBinaryGroupsType();
	}
	SS_CATCH(L"")
	return true;
}

//����������� ����� ��� �������� �� SQL ������� SyntaxConstructionGroupsType
void SS::SyntaxConstructions::SQL::CSyntaxConstructionGroups::ToBinaryGroupsType()
{
	SS_TRY
	{
		std::wstring wDataTableName = L"SyntaxConstructionGroupsType";		
		m_pDataBase->MoveToDataTable(wDataTableName.c_str());
		SS::Interface::Core::DBMS::IDataTable* pDTable = m_pDataBase->OpenDataTable();
		
		if ( (pDTable == NULL) || (!pDTable->IsOpen()) )
		{ SS_THROW(L"������ ��� �������� ������� SyntaxConstructionGroupsType."); }

		//������� �������
		pDTable->Clear();
		//��������� ��� ���������� �������
		SS::SyntaxConstructions::Types::SGroupAndCharacteristics oGroupCharacteristics;
		void* TableRecord[] = { &oGroupCharacteristics.iIdGroup,
								&oGroupCharacteristics.iAnalyseMode, 
								&oGroupCharacteristics.iResolveAmbiguity };

		if ( pDTable->AddInit(TableRecord) != S_OK )  
		{ SS_THROW(L"������ AddInit ��� ������� SyntaxConstructionGroupsType"); }

		//��������� ���������� �� ������ � ����� ������
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::ConstructionGroups;
		CPreparedConstructionGroupsTypeSAll oPrepared;
		oPrepared.Prepare(*m_pConnection->GetSession());

		if (oPrepared.Open() == S_OK)
		{
			if (oPrepared.MoveFirst() != DB_S_ENDOFROWSET)
			{					
				do
				{
					oGroupCharacteristics.iIdGroup = oPrepared.GetIdGroup();
					oGroupCharacteristics.iAnalyseMode = oPrepared.GetAnalyseMode();
					oGroupCharacteristics.iResolveAmbiguity = oPrepared.GetResolveAmbiguity();
					pDTable->Add();
				}
				while (oPrepared.MoveNext() != DB_S_ENDOFROWSET);
			}
		}
		oPrepared.Close();
		pDTable->Close();
	}
	SS_CATCH(L"")
}

//������� ������� ���� �� ����
bool SS::SyntaxConstructions::SQL::CSyntaxConstructionGroups::Delete()
{
	SS_TRY
	{
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::ConstructionGroups;
		CPreparedConstructionGroupsD oPrepared;
		oPrepared.Prepare(*m_pConnection->GetSession());
		oPrepared.SetIDConstruction((long)m_GroupAndConstruction.m_i32IDConstruction);
		oPrepared.SetIDGroup((short)m_GroupAndConstruction.m_i32IDGroup);
		oPrepared.Open();
		oPrepared.Close();
	}
	SS_CATCH(L"");
	return true;
}

//���������� ������ �������� ���������� ������ ��� ���� ������� � �������������� � ��. ����. �������� (��� SQL �� ������������)
void SS::SyntaxConstructions::SQL::CSyntaxConstructionGroups::GetGroupsForType(SS::Core::Types::EAnalyseMods eAnalyseMode, 
																				std::list<SGroupAndCharacteristics> & lstGroupCharacteristics)
{
	SS_TRY
	{
		SS_THROW(L"������� ��� ������� ������ ������ �� �������������.");
	}
	SS_CATCH(L"")
}

//**************************************************************************************
//******************************************DBMS ***************************************

///�����������
SS::SyntaxConstructions::DBMS::CSyntaxConstructionGroups::CSyntaxConstructionGroups(wchar_t* szBaseName)
	: 
	SS::CConnectDBMS(szBaseName),
	m_TableInited(false)
{
	m_GroupTableRecord[0] = &m_oGroupAndConstruction.m_i32IDConstruction;
	m_GroupTableRecord[1] = &m_oGroupAndConstruction.m_i32IDGroup;
	m_GroupTypeTableRecord[0] = &m_oGroupAndCharacteristics.iIdGroup;
	m_GroupTypeTableRecord[1] = &m_oGroupAndCharacteristics.iAnalyseMode;
	m_GroupTypeTableRecord[2] = &m_oGroupAndCharacteristics.iResolveAmbiguity;
}

//����� ��� ��������� ������������� ����������� ������
void SS::SyntaxConstructions::DBMS::CSyntaxConstructionGroups::InitTables()
{
	SS_TRY
	{
		//������� SyntaxConstructionGroups
		std::wstring wTable = L"SyntaxConstructionGroups";
		SS::CConnectDBMS::SetTable(wTable);
		if ( m_pDTable->ScanInit(0, m_GroupTableRecord) != S_OK )   
		{ SS_THROW(L"������ ������������� ������������"); }
		
		//������� SyntaxConstructionGroupsType
		wTable = L"SyntaxConstructionGroupsType";
		SS::CConnectDBMS::SetTable(wTable);
		if ( m_pDTable->ScanInit(0, m_GroupTypeTableRecord) != S_OK )   
		{ SS_THROW(L"������ ������������� ������������"); }

		m_TableInited = true;
	}
	SS_CATCH(L"")
}

//������������ ��� ���� (m_iConstructionId, m_ConstructionGroupId), �������� � ����
bool SS::SyntaxConstructions::DBMS::CSyntaxConstructionGroups::Get(std::list<SS::SyntaxConstructions::Types::SGroupAndConstruction> & listConstructionGroups)
{
	SS_TRY
	{
		if (!m_TableInited) 
		{ InitTables(); }
		
		listConstructionGroups.clear();
		std::wstring wTable = L"SyntaxConstructionGroups";
		SS::CConnectDBMS::SetTable(wTable);
			
		m_pDTable->ScanStart(0);
		while ( m_pDTable->Scan() == S_OK )   
		{ listConstructionGroups.push_back(m_oGroupAndConstruction); }
	}
	SS_CATCH(L"")
	return !listConstructionGroups.empty();
}

//���������� ������ �������� ���������� ������ ��� ���� ������� � �������������� � ��. ����. ��������
void SS::SyntaxConstructions::DBMS::CSyntaxConstructionGroups::GetGroupsForType(SS::Core::Types::EAnalyseMods eAnalyseMode, 
																					std::list<SGroupAndCharacteristics> & lstGroupCharacteristics)
{
	SS_TRY
	{
		if (!m_TableInited) 
		{ InitTables(); }
		
		//������� ����� ��� �������� ��������
		const int MaskAmbiguity = 1;

		std::wstring wTable = L"SyntaxConstructionGroupsType";
		SS::CConnectDBMS::SetTable(wTable);
	
		m_pDTable->ScanStart(0);
		while ( m_pDTable->Scan() == S_OK )  
		{ 
			if ( m_oGroupAndCharacteristics.iAnalyseMode == eAnalyseMode ) 
			{
				if ( m_oGroupAndCharacteristics.iResolveAmbiguity & MaskAmbiguity ) 
				{ m_oGroupAndCharacteristics.iResolveAmbiguity = 1; }
				else
				{ m_oGroupAndCharacteristics.iResolveAmbiguity = 0; }
				
				lstGroupCharacteristics.push_back(m_oGroupAndCharacteristics);
			}
		}
	}
	SS_CATCH(L"")
}

//��������� ������� ���� (m_iConstructionId, m_ConstructionGroupId) � ����
bool SS::SyntaxConstructions::DBMS::CSyntaxConstructionGroups::Add()
{
	SS_TRY
	{
		SS_THROW(L"������� ��� ������� ������ ������ �� �������������.");
	}
	SS_CATCH(L"")
	return false;
}

///������� ������� ���� �� ����
bool SS::SyntaxConstructions::DBMS::CSyntaxConstructionGroups::Delete()
{
	SS_TRY
	{
		SS_THROW(L"������� ��� ������� ������ ������ �� �������������.");
	}
	SS_CATCH(L"")
	return false;
}

