#pragma once

#include "..\ASSInterface\ISyntaxConstructions.h"
#include ".\dboConstruction.h"
#include ".\connect.h"
#include "..\ASSInterface\construction.h"

namespace SS
{
	namespace SyntaxConstructions
	{
		namespace SQL
		{
			using SS::SyntaxConstructions::Types::SGroupAndCharacteristics;

			/// �����, ����������� ������ � �������� �����������
			class CSyntaxConstructionGroups : public SS::Interface::Core::SyntaxConstructions::ISyntaxConstructionGroups,
											  public SS::CConnectSQL
			{
			private:
				///��������� � �������� ��� ��������� ������ 
				void ToBinaryGroupsType();

			public:
				///�����������
				CSyntaxConstructionGroups(wchar_t* szBaseName) : SS::CConnectSQL(szBaseName){};
				///����������
				virtual ~CSyntaxConstructionGroups(){};
				///��������� � �������� ��� ��������� ������ 
				bool ToBinary();
				///������ ISyntaxConstructionGroups
				///��������� ������� ���� (m_iConstructionId, m_ConstructionGroupId) � ����
				bool Add();	
				/// ������������ ��� ���� (m_iConstructionId, m_ConstructionGroupId), �������� � ����
				bool Get(std::list<SS::SyntaxConstructions::Types::SGroupAndConstruction> & listConstructionGroups);
				///	������� ������� ���� �� ����
				bool Delete();
				///���������� ������ �������� ���������� ������ ��� ���� ������� � �������������� � ��. ����. ��������
				void GetGroupsForType( SS::Core::Types::EAnalyseMods eAnalyseMode,
									   std::list<SGroupAndCharacteristics> & lstGroupCharacteristics);
			};
		
		}
		
		namespace DBMS
		{
			using SS::SyntaxConstructions::Types::SGroupAndCharacteristics;
			
			///�����, ����������� ������ � �������� �����������
			class CSyntaxConstructionGroups : public SS::Interface::Core::SyntaxConstructions::ISyntaxConstructionGroups,
											  public SS::CConnectDBMS
			{
			private:
				///��������� ��� ������� � ������� SyntaxConstructionGroups
				SS::SyntaxConstructions::Types::SGroupAndConstruction	m_oGroupAndConstruction;
				///��������� ��� ������� � ������� SyntaxConstructionGroupsType
				SS::SyntaxConstructions::Types::SGroupAndCharacteristics	m_oGroupAndCharacteristics;
				///������ �� ������� SyntaxConstructionGroups
				void* m_GroupTableRecord[2];
				///������ �� ������� SyntaxConstructionGroupsType
				void* m_GroupTypeTableRecord[3];
				///���������� ���������� ������������� ������
				bool m_TableInited;
			
			private:
				///����� ��� ��������� ������������� ����������� ������
				void InitTables();
			
			public:
				///�����������
				CSyntaxConstructionGroups(wchar_t* szBaseName);
				///����������
				virtual ~CSyntaxConstructionGroups(){};
				///������ ISyntaxConstructionGroups								
				///��������� ������� ���� (m_iConstructionId, m_ConstructionGroupId) � ����
				bool Add();	
				///������������ ��� ���� (m_iConstructionId, m_ConstructionGroupId), �������� � ����
				bool Get(std::list<SS::SyntaxConstructions::Types::SGroupAndConstruction> & listConstructionGroups);					
				///������� ������� ���� �� ����
				bool Delete();
				///���������� ������ �������� ���������� ������ ��� ���� ������� � �������������� � ��. ����. ��������
				void GetGroupsForType( SS::Core::Types::EAnalyseMods eAnalyseMode,
									   std::list<SGroupAndCharacteristics> & lstGroupCharacteristics );
				///���������� ��������� ���������� ������������� ������
				void SetRepeatTableInit() { m_TableInited = false; };
			};
		
		}
	}
}