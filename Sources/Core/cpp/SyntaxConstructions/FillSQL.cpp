//FillSQL.cpp
#include "StdAfx.h"
#include ".\fillsql.h"
#include "../ASSInterface/TSyntaxConstructions.h"
#include "../ASSInterface/Construction.h"
#include "./dboSyntax.h"

namespace SS
{
namespace UnitTests
{
namespace SyntaxConstructions
{
	//���������� SQL ���� �� DBMS
	void CFillSQL::Fill()
	{
		//�������� ������� DBMS
		std::wstring wDataTableName = L"SyntaxConstruction";		
		m_pDataBase->MoveToDataTable(wDataTableName.c_str());
		SS::Interface::Core::DBMS::IDataTable* pDTable = m_pDataBase->OpenDataTable();
		if ( (pDTable==NULL) || (!pDTable->IsOpen()) )
		{ SS_THROW(L"������ ��� �������� ������� SyntaxConstruction"); }

		//������������� DBMS
		SS::SyntaxConstructions::Types::SSyntaxConstruction oSSyntaxConstruction;
		void* TableRecord[] = 
		{
			&oSSyntaxConstruction.m_i32ID,
			&oSSyntaxConstruction.m_wsName,
			&oSSyntaxConstruction.m_wsWord,
			&oSSyntaxConstruction.m_v_Data,
			&oSSyntaxConstruction.m_i32DataSize,
			&oSSyntaxConstruction.m_i32Level
		};
		if ( pDTable->ScanInit(0, TableRecord) != S_OK )   
		{ SS_THROW(L"������ �������������."); }

		//������������� SQL
		SS::SyntaxConstructions::SQL::SQL_ACCESS::Syntax::CPreparedDAllSyntaxConstruction oPreparedDelete;
		SS::SyntaxConstructions::SQL::SQL_ACCESS::Syntax::CPreparedISyntaxConstruction oPreparedInsert;
		
		//������� ������ �� ����
		oPreparedDelete.Prepare(*m_pConnection->GetSession());
		if(oPreparedDelete.Open() != S_OK)
		{ SS_THROW(L"������� SQL ������� �� ���������."); }
		oPreparedDelete.Close();
		
		//�������� ������ � ����
		oPreparedInsert.Prepare(*m_pConnection->GetSession());
		//������ �����������
		SS::SyntaxConstructions::Types::CConstructionObject oConstructionObject;	
		while (pDTable->Scan() == S_OK)
		{
			////��������� ���
			oConstructionObject.SetValue(oSSyntaxConstruction.m_v_Data);
			oSSyntaxConstruction.m_v_Data.clear();
			oConstructionObject.GetValue(oSSyntaxConstruction.m_v_Data);
			//���������� SQL
			oPreparedInsert.SetID(oSSyntaxConstruction.m_i32ID);
			oPreparedInsert.SetName(oSSyntaxConstruction.m_wsName.c_str());
			oPreparedInsert.SetWord(oSSyntaxConstruction.m_wsWord.c_str());
			oPreparedInsert.SetConstructionData(oSSyntaxConstruction.m_v_Data);
			oPreparedInsert.SetLevel(oSSyntaxConstruction.m_i32Level);

			if (oPreparedInsert.Open() != S_OK)
			{ SS_THROW(L"������� �� ������!"); }
			oPreparedInsert.Close();
		}
		pDTable->Close();
	}

}
}
}