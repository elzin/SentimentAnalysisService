//SyntaxConstuctions.h
#pragma once

#include "..\ASSInterface\ISyntaxConstructions.h"
#include ".\dboSyntax.h"
#include ".\connect.h"
#include "..\ASSInterface\construction.h"

namespace SS
{
	namespace SyntaxConstructions
	{
		///������������ ���� SQL
		namespace SQL
		{
			///�����, ����������� ������ � ��������������� �������������
			class CSyntaxConstuctions : public SS::Interface::Core::SyntaxConstructions::ISyntaxConstructions,
										public SS::CConnectSQL
			{
			private:
				//������ ������-����
				SS::Interface::Core::SyntaxConstructions::IDetectWordsGroups* m_pDetectWordsGroups;
				///���������� ������������ ������������ ������
				long GetMaxId();
		
			public:
				///�����������
				CSyntaxConstuctions(wchar_t* szBaseName,
									SS::Interface::Core::SyntaxConstructions::IDetectWordsGroups* pDetectWordsGroups);
				///����������
				virtual ~CSyntaxConstuctions(){};
				///������ ISyntaxConstructions
				///��������� � ���� ����������� � ���������� �� �����
				long Add(/*in*/SS::SyntaxConstructions::Types::CConstructionEx* p_SyntaxConstruction);
				///������� ������� �����������
				void Delete();
				///���������� ������ ���� �������������� �����������
				bool Get(/*out*/std::list<SS::SyntaxConstructions::Types::CConstructionEx>* p_list_OfSyntaxConstruction);
				///���������� ������� �������������� �����������
				bool Get(/*out*/SS::SyntaxConstructions::Types::CConstructionEx* p_SyntaxConstruction);
				///������ ILoad
				///��������� � �������� ��� ��������� ������ 
				bool ToBinary();
			};
		}
		
		///������������ ���� DBMS
		namespace DBMS
		{
			///�����, ����������� ������ � ��������������� �������������
			class CSyntaxConstuctions :	public SS::Interface::Core::SyntaxConstructions::ISyntaxConstructions,
										public SS::CConnectDBMS
			{
			private:
				///��������� ����, �� �������� ����� �������������� �����
				enum EFindMode
				{
					efmByID,
					efmByName
				};
				///������ � �������������� �����������
				SS::SyntaxConstructions::Types::SSyntaxConstruction m_oSSyntaxConstruction;		
				///������ ���������� �� ������, ���������� ������ � DBMS �������
				void* TableRecord[6];
				///������� ������-������
				SS::Interface::Core::SyntaxConstructions::IDetectWordsGroups* m_pDetectWordsGroups;
				//���������� ���������� ������������� ������
				bool m_TableInited;
			
			private:
				///������������� ���������� � ���������
				void InitConnection();
		
			public:
				///�����������
				CSyntaxConstuctions( wchar_t* szBaseName, 
									 SS::Interface::Core::SyntaxConstructions::IDetectWordsGroups* pDetectWordsGroups );
				///����������
				virtual ~CSyntaxConstuctions(){};
				/// ������ ISyntaxConstructions
				/// ��������� � ���� ����������� � ���������� �� �����
				long Add(SS::SyntaxConstructions::Types::CConstructionEx* pSyntaxConstruction);
				/// ������� ������� �����������
				void Delete();
				/// ���������� ������ ���� �������������� �����������
				bool Get(std::list<SS::SyntaxConstructions::Types::CConstructionEx>* p_list_OfSyntaxConstruction);
				/// ���������� ������� �������������� �����������
				bool Get(SS::SyntaxConstructions::Types::CConstructionEx* p_SyntaxConstruction);
				///���������� ��������� ���������� ������������� ������
				void SetRepeatTableInit() { m_TableInited = false; };
			};
		}
	}
}