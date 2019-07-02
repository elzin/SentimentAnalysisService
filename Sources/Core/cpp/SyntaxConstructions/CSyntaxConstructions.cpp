//CSyntaxConstructions.cpp

#include "StdAfx.h"
#include "..\ASSInterface\TSyntaxConstructions.h"
#include "./dboSyntax.h"
#include ".\csyntaxconstructions.h"

//�����������
SS::SyntaxConstructions::SQL::CSyntaxConstuctions::CSyntaxConstuctions(wchar_t* szBaseName, 
								SS::Interface::Core::SyntaxConstructions::IDetectWordsGroups* pDetectWordsGroups)
								: 
								SS::CConnectSQL(szBaseName), m_pDetectWordsGroups(pDetectWordsGroups)
{}

//��������� � �������� ��� ��������� ������ 
bool SS::SyntaxConstructions::SQL::CSyntaxConstuctions::ToBinary()
{
	SS_TRY
	{
		std::wstring wDataTableName = L"SyntaxConstruction";		
		m_pDataBase->MoveToDataTable(wDataTableName.c_str());
		SS::Interface::Core::DBMS::IDataTable* pDTable = m_pDataBase->OpenDataTable();
	
		if ( (pDTable==NULL) || (!pDTable->IsOpen()) )
		{ SS_THROW(L"������ ��� �������� ������� SyntaxConstruction"); }
		
		//�������� DBMS �������
		pDTable->Clear();

		SS::SyntaxConstructions::Types::SSyntaxConstruction oSSyntaxConstruction;
		void* TableRecord[] = 
		{
			&oSSyntaxConstruction.m_i32ID,
			&oSSyntaxConstruction.m_wsName,
			&oSSyntaxConstruction.m_wsWord,
			&oSSyntaxConstruction.m_v_Data,
			&oSSyntaxConstruction.m_i32DataSize,
			&oSSyntaxConstruction.m_i32Level,			
		};
		if (pDTable->AddInit(TableRecord) != S_OK)  
		{ SS_THROW(L"������ AddInit ��� ������� SyntaxConstruction"); }	

		//�����������
		SS::SyntaxConstructions::Types::CConstructionEx oConstructionEx;

		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::Syntax;
		CPreparedSAllSyntaxConstruction oPrepared;
		oPrepared.Prepare(*m_pConnection->GetSession());
		
		if(oPrepared.Open() == S_OK)
		{
			if(oPrepared.MoveFirst() != DB_S_ENDOFROWSET)
			{
				oConstructionEx.SetID(oPrepared.GetID());					
				oConstructionEx.SetName(oPrepared.GetName());
				do
				{
					oSSyntaxConstruction.m_i32ID	= oPrepared.GetID();					
					oSSyntaxConstruction.m_wsName	= oPrepared.GetName();
					oPrepared.GetConstructionData(oSSyntaxConstruction.m_v_Data);
					oSSyntaxConstruction.m_wsWord	= oPrepared.GetWord();
					oSSyntaxConstruction.m_i32Level	= oPrepared.GetLevel();
					pDTable->Add();
				}
				while (oPrepared.MoveNext() != DB_S_ENDOFROWSET);	
			}
		}
		oPrepared.Close();
		pDTable->Close();
	}
	SS_CATCH(L"")
	return true;
}

//���������� ��� �������������� �����������
bool SS::SyntaxConstructions::SQL::CSyntaxConstuctions::Get(
							/*out*/std::list<SS::SyntaxConstructions::Types::CConstructionEx>* p_list_OfSyntaxConstruction)
{
	SS_TRY
	{
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::Syntax;
		SS::SyntaxConstructions::Types::CConstructionEx oConstructionEx;
		CPreparedSAllSyntaxConstruction oPrepared;
		oPrepared.Prepare(*m_pConnection->GetSession());
		
		if (oPrepared.Open() == S_OK)
		{
			if (oPrepared.MoveFirst() != DB_S_ENDOFROWSET)
			{
				oConstructionEx.SetID(oPrepared.GetID());					
				oConstructionEx.SetName(oPrepared.GetName());
				do
				{
					if (oConstructionEx.GetID() != oPrepared.GetID())
					{
						p_list_OfSyntaxConstruction->push_back(oConstructionEx);
						oConstructionEx.clear();
						oConstructionEx.SetID(oPrepared.GetID());					
						oConstructionEx.SetName(oPrepared.GetName());
					}

					//������ �����������
					SS::SyntaxConstructions::Types::CConstructionObject oConstructionObject;
					std::wstring wsDetectWordGroupName = oPrepared.GetWord();
					std::vector<unsigned char> vecOfByte;
					oPrepared.GetConstructionData(vecOfByte);
					oConstructionObject.SetValue(vecOfByte);
					oConstructionObject.SetDetectWordGroupName( wsDetectWordGroupName );
					if (wsDetectWordGroupName != L"") 
					{
						SS::SyntaxConstructions::Types::TDetectWordsGroup oDetectGroup;
						m_pDetectWordsGroups->SetDetectWordsGroupName(wsDetectWordGroupName);
						m_pDetectWordsGroups->GetWords(oDetectGroup);
						oConstructionObject.SetDetectWords(oDetectGroup);
					}					
					oConstructionEx.push_back(oConstructionObject);
				}
				while (oPrepared.MoveNext() != DB_S_ENDOFROWSET);	
				p_list_OfSyntaxConstruction->push_back(oConstructionEx);
			}
		}
		oPrepared.Close();
	}
	SS_CATCH(L"");	
	return false;
}
/*	���������� ������� �������������� �����������	*/
bool SS::SyntaxConstructions::SQL::CSyntaxConstuctions::Get(/*out*/SS::SyntaxConstructions::Types::CConstructionEx* p_SyntaxConstruction)
{
	SS_TRY
	{
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::Syntax;
		CPreparedSByIDSyntaxConstruction oPrepared;
		oPrepared.Prepare(*m_pConnection->GetSession());
		oPrepared.SetID(m_iID);

		if (oPrepared.Open() == S_OK)
		{
			if (oPrepared.MoveFirst() != DB_S_ENDOFROWSET)
			{		
				p_SyntaxConstruction->SetID(oPrepared.GetID());
				p_SyntaxConstruction->SetName(oPrepared.GetName());
				do
				{
					//������ �����������
					SS::SyntaxConstructions::Types::CConstructionObject oConstructionObject;
					std::vector<unsigned char> vecOfByte;
					oPrepared.GetConstructionData(vecOfByte);
					oConstructionObject.SetValue(vecOfByte);
					oConstructionObject.SetDetectWordGroupName(oPrepared.GetWord());
					p_SyntaxConstruction->push_back(oConstructionObject);
				}
				while (oPrepared.MoveNext() != DB_S_ENDOFROWSET);					
			}
		}
		oPrepared.Close();
	}
	SS_CATCH(L"");	
	return false;
}

//��������� ����������� � ���������� �� �����
long SS::SyntaxConstructions::SQL::CSyntaxConstuctions::Add(
									/*in*/SS::SyntaxConstructions::Types::CConstructionEx* p_SyntaxConstruction)
{
	SS_TRY
	{
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::Syntax;
		p_SyntaxConstruction->SetID((GetMaxId() + 1));
		CPreparedISyntaxConstruction oPrepared;
		oPrepared.Prepare(*m_pConnection->GetSession());
		CPreparedSDetectWordsGroupsByDetectWordsGroupName oPreparedSDetectWordsGroupsByDetectWordsGroupName;
		oPreparedSDetectWordsGroupsByDetectWordsGroupName.Prepare(*m_pConnection->GetSession());
		oPrepared.SetID(p_SyntaxConstruction->GetID());
		oPrepared.SetName(p_SyntaxConstruction->GetName().c_str());

		int iLevel = 0;
		SS::SyntaxConstructions::Types::CConstructionEx::iterator	iter;

		//������ ��������������� �������� �����������
		for (iter = p_SyntaxConstruction->begin(); iter != p_SyntaxConstruction->end();	++iter)
		{
			++iLevel;
			if ((*iter)->GetDetectWordGroupName() != L"")
			{
				//���������, ���������� �� ������ ���� ��� �������������� � ��������� ������� ������
				oPreparedSDetectWordsGroupsByDetectWordsGroupName.SetDetectWordsGroupName((*iter)->GetDetectWordGroupName());
				if (oPreparedSDetectWordsGroupsByDetectWordsGroupName.Open() != S_OK)
				{
					oPreparedSDetectWordsGroupsByDetectWordsGroupName.Close();
					SS_THROW(L"������ ��� ���������� ������� � ������� DetectWordsGroups �� �������� ������");
				}
				if (oPreparedSDetectWordsGroupsByDetectWordsGroupName.MoveFirst() != S_OK)
				{
					oPreparedSDetectWordsGroupsByDetectWordsGroupName.Close();
					wchar_t szToMessage[200];
					wcscpy(szToMessage, L"������ ���� ��� �������������� � ������ : ");
					wcscat(szToMessage, (*iter)->GetDetectWordGroupName().c_str());
					wcscat(szToMessage, L" �� ����������");
					SS_THROW(szToMessage);
				}
				oPreparedSDetectWordsGroupsByDetectWordsGroupName.Close();
			}

			std::vector<unsigned char> vecOfByte;
			(*iter)->GetValue(vecOfByte);
			oPrepared.SetConstructionData(vecOfByte);
			oPrepared.SetWord((*iter)->GetDetectWordGroupName().c_str());
			oPrepared.SetLevel(iLevel);

			if (oPrepared.Open() != S_OK)
			{
				oPrepared.Close();
				SS_THROW(L"����������� �� ���������.");
			}
			oPrepared.Close();
		}
	}
	SS_CATCH(L"");
	return p_SyntaxConstruction->GetID();
}

//���������� ������������ ����� �����������
long SS::SyntaxConstructions::SQL::CSyntaxConstuctions::GetMaxId()
{
	long iID = 0;
	SS_TRY
	{
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::Syntax;
		CPreparedSMaxIDSyntaxConstruction oPrepared;
		oPrepared.Prepare(*m_pConnection->GetSession());
		
		if (oPrepared.Open() == S_OK)
		{
			if(oPrepared.MoveFirst() != DB_S_ENDOFROWSET)
			{ iID = oPrepared.GetID(); }
		}
		oPrepared.Close();	
	}
	SS_CATCH(L"");
	return iID;
}

//������� ������� �����������
void SS::SyntaxConstructions::SQL::CSyntaxConstuctions::Delete()
{
	SS_TRY
	{
		using namespace SS::SyntaxConstructions::SQL::SQL_ACCESS::Syntax;
		CPreparedDSyntaxConstruction oPrepared;
		oPrepared.Prepare(*m_pConnection->GetSession());
		oPrepared.SetID(m_iID);
		
		if (oPrepared.Open() != S_OK)
		{
			oPrepared.Close();
			SS_THROW(L"����������� �� �������");
		}
		oPrepared.Close();
	}
	SS_CATCH(L"");	
}		

////////////////////////////////////DBMS////////////////////////////////////////

//�����������
SS::SyntaxConstructions::DBMS::CSyntaxConstuctions::CSyntaxConstuctions(wchar_t* szBaseName,
					SS::Interface::Core::SyntaxConstructions::IDetectWordsGroups* pDetectWordsGroups)
					:
					SS::CConnectDBMS(szBaseName),
					m_pDetectWordsGroups(pDetectWordsGroups),
					m_TableInited(false)
{
	TableRecord[0] = &m_oSSyntaxConstruction.m_i32ID;
	TableRecord[1] = &m_oSSyntaxConstruction.m_wsName;
	TableRecord[2] = &m_oSSyntaxConstruction.m_wsWord;
	TableRecord[3] = &m_oSSyntaxConstruction.m_v_Data;
	TableRecord[4] = &m_oSSyntaxConstruction.m_i32DataSize;
	TableRecord[5] = &m_oSSyntaxConstruction.m_i32Level;
}

//������������� ���������� � ��������
void SS::SyntaxConstructions::DBMS::CSyntaxConstuctions::InitConnection()
{
	SS_TRY
	{
		std::wstring wTable = L"SyntaxConstruction";	
		SS::CConnectDBMS::SetTable(wTable);
		
		if ( m_pDTable->FindInit(L"ID", &m_oSSyntaxConstruction.m_i32ID, TableRecord, efmByID) != S_OK )   
		{ SS_THROW(L"������ ������������� ������ �� ���� ID"); }
		
		if ( m_pDTable->FindInit(L"Name", &m_oSSyntaxConstruction.m_wsName, TableRecord, efmByName) != S_OK )   
		{ SS_THROW(L"������ ������������� ������ �� ���� Name"); }
		
		if ( m_pDTable->ScanInit(0, TableRecord) != S_OK )   
		{ SS_THROW(L"������ ������������� ������ �� ���� Name"); }

		m_TableInited = true;
	}
	SS_CATCH(L"")
}

//���������� ��� �������������� �����������
bool SS::SyntaxConstructions::DBMS::CSyntaxConstuctions::Get(
									/*out*/std::list<SS::SyntaxConstructions::Types::CConstructionEx>* p_list_OfSyntaxConstruction)
{
	SS_TRY
	{
		if (!m_TableInited) 
		{ InitConnection(); }

		//�����������
		SS::SyntaxConstructions::Types::CConstructionEx oConstructionEx;

		m_pDTable->ScanStart(0);
		if (m_pDTable->Scan() == S_OK)
		{
			oConstructionEx.SetID(m_oSSyntaxConstruction.m_i32ID);
			oConstructionEx.SetName(m_oSSyntaxConstruction.m_wsName);
		}
		else
		{ return false; }

//		int iObjectNumber = 0;

		do
		{
			if (oConstructionEx.GetID() != m_oSSyntaxConstruction.m_i32ID)
			{
				//iObjectNumber = 0;

				p_list_OfSyntaxConstruction->push_back(oConstructionEx);
				oConstructionEx.clear();
				oConstructionEx.SetID(m_oSSyntaxConstruction.m_i32ID);					
				oConstructionEx.SetName(m_oSSyntaxConstruction.m_wsName);
			}

			//������ �����������
			SS::SyntaxConstructions::Types::CConstructionObject oConstructionObject;
			//������ ������-����
			SS::SyntaxConstructions::Types::TDetectWordsGroup oDetectGroup;
			m_pDetectWordsGroups->SetDetectWordsGroupName(m_oSSyntaxConstruction.m_wsWord);
			m_pDetectWordsGroups->GetWords(oDetectGroup);
			oConstructionObject.SetDetectWords(oDetectGroup);
			//��������� ���
			oConstructionObject.SetValue(m_oSSyntaxConstruction.m_v_Data);
			oConstructionObject.SetDetectWordGroupName(m_oSSyntaxConstruction.m_wsWord);
		

			//if((iObjectNumber != 0)&&(oConstructionObject.m_ObjectFeature.m_PositionToDetectedObject.IsUndefined()))
			//{
			//	SAVE_LOG(SS_WARNING AND oConstructionEx.GetName().c_str() AND __WFUNCTION__);
			//}
			//iObjectNumber++;

			//���������� �������� � �����������
			oConstructionEx.push_back(oConstructionObject);
		}
		while (m_pDTable->Scan() == S_OK);
		p_list_OfSyntaxConstruction->push_back(oConstructionEx);
	}
	SS_CATCH(L"")
	return true;
}

//���������� ������� �������������� �����������
bool SS::SyntaxConstructions::DBMS::CSyntaxConstuctions::Get(
									/*out*/SS::SyntaxConstructions::Types::CConstructionEx* pSyntaxConstruction)
{
	bool bRetVal = false;
	SS_TRY
	{
		if (!m_TableInited) 
		{ InitConnection(); }

		//������ �����������
		m_oSSyntaxConstruction.m_i32ID = m_iID;


		std::list<SS::SyntaxConstructions::Types::SSyntaxConstruction> o_l_SyntaxConstruction;

		while (m_pDTable->Find(efmByID) == S_OK)   
		{
			o_l_SyntaxConstruction.push_back(m_oSSyntaxConstruction);
		}
		o_l_SyntaxConstruction.sort();
/////////////////////////////////////////////////////////////////////////////////////////////////
		//int iObjectNumber = 0;
		for(std::list<SS::SyntaxConstructions::Types::SSyntaxConstruction>::iterator i = o_l_SyntaxConstruction.begin(); i != o_l_SyntaxConstruction.end(); i++)
		{
			bRetVal = true;
			//������ �����������
			SS::SyntaxConstructions::Types::CConstructionObject oConstructionObject;
			//������ ������-����
			SS::SyntaxConstructions::Types::TDetectWordsGroup oDetectGroup;
			m_pDetectWordsGroups->SetDetectWordsGroupName(i->m_wsWord);
			m_pDetectWordsGroups->GetWords(oDetectGroup);
			oConstructionObject.SetDetectWords(oDetectGroup);
			//��������� ���
			oConstructionObject.SetValue(i->m_v_Data);
			oConstructionObject.SetDetectWordGroupName(i->m_wsWord);

			//if((iObjectNumber != 0)&&(oConstructionObject.m_ObjectFeature.m_PositionToDetectedObject.IsUndefined()))
			//{
			//	SAVE_LOG(SS_WARNING AND pSyntaxConstruction->GetName().c_str() AND __WFUNCTION__);
			//}

			//iObjectNumber++;

         //���������� �������� � �����������
         pSyntaxConstruction->push_back(oConstructionObject);
		}

		pSyntaxConstruction->SetID(m_oSSyntaxConstruction.m_i32ID);					
		pSyntaxConstruction->SetName(m_oSSyntaxConstruction.m_wsName);


	}
	SS_CATCH(L"")
	return bRetVal;
}

//��������� ����������� � ���������� �� �����
long SS::SyntaxConstructions::DBMS::CSyntaxConstuctions::Add(
											/*in*/SS::SyntaxConstructions::Types::CConstructionEx* p_SyntaxConstruction)
{
	SS_TRY
	{
		SS_THROW(L"������� ��� ������� ������ ������ �� ������������� ���������� � ������ ����������� ���������");
	}
	SS_CATCH(L"")
	return 0;
}

//������� ������� �����������
void SS::SyntaxConstructions::DBMS::CSyntaxConstuctions::Delete()
{
	SS_TRY
	{
		SS_THROW(L"������� ��� ������� ������ ������ �� ������������� ���������� � ������ ����������� ���������");
	}
	SS_CATCH(L"")
}