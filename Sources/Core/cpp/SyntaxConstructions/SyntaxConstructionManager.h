//SyntaxConstructionManager.h
#pragma once

#include "..\ASSInterface\ISyntaxConstructions.h"
#include ".\CSyntaxConstructions.h"
#include ".\SyntaxConstructionGroups.h"
#include ".\SyntaxConstructionGroupsNames.h"
#include ".\DetectWordsGroups.h"

namespace SS
{
	namespace SyntaxConstructions
	{
		///��� ���� ������
		enum EDataBaseType
		{
			edbtUndefined,
         edbtDBMS,
			edbtSQL
		} ;

		///����� ����������� ������� � ��������������� �������������
		class CSyntaxConstructionManager : public SS::Interface::Core::SyntaxConstructions::ISyntaxConstructionsManager
		{
		private:
			///��������� �� ������ ������ SQL::CSyntaxConstuctions
			SS::SyntaxConstructions::SQL::CSyntaxConstuctions*		m_pSyntaxConstuctionsSQL;
			///��������� �� ������ ������ DBMS::CSyntaxConstuctions
			SS::SyntaxConstructions::DBMS::CSyntaxConstuctions*		m_pSyntaxConstuctionsDBMS;
			///��������� �� ������ ������ SQL::CSyntaxConstructionGroups
			SS::SyntaxConstructions::SQL::CSyntaxConstructionGroups*	m_pSyntaxConstructionGroupsSQL;
			///��������� �� ������ ������ DBMS::CSyntaxConstructionGroups
			SS::SyntaxConstructions::DBMS::CSyntaxConstructionGroups* m_pSyntaxConstructionGroupsDBMS;
			///��������� �� ������ ������ SQL::CDetectWordsGroups
			SS::SyntaxConstructions::SQL::CDetectWordsGroups*		m_pDetectWordsGroupsSQL;
			///��������� �� ������ ������ DBMS::CDetectWordsGroups
			SS::SyntaxConstructions::DBMS::CDetectWordsGroups*		m_pDetectWordsGroupsDBMS;
			///��� ����
			wchar_t m_szBaseName[100];
			///��� ����
			EDataBaseType m_eDataBaseType;
		
		private:
			///�������� �������
			void CreateObjects();
		
		public:
			///�����������
			CSyntaxConstructionManager(const wchar_t* szBaseName);
			///����������
			~CSyntaxConstructionManager();
			///���������� �������� ��� ������ � ��������������� �������������	
			SS::Interface::Core::SyntaxConstructions::ISyntaxConstructions			* GetSyntaxConstructions();
			///���������� �������� ��� ������ � �������� �������������� �����������	
			SS::Interface::Core::SyntaxConstructions::ISyntaxConstructionGroups		* GetSyntaxConstructionGroups();
			///���������� �������� ��� ������ � �������� �������������� ����������� � �� ����������	
			SS::Interface::Core::SyntaxConstructions::ISyntaxConstructionGroupsNames	* GetSyntaxConstructionGroupsNames();
			///���������� �������� ��� ������ � �������� ���� ��� ��������������
			SS::Interface::Core::SyntaxConstructions::IDetectWordsGroups				* GetDetectWordsGroups();
			///������ IBase 
			///������������
			ULONG Release();
			///���������� � ����������
			HRESULT QueryInterface(REFIID pIID, void** pBase); 		
			///������ ILoad
			///��������� � �������� ��� ��������� ������ 
			bool ToBinary();
			///������������� �������
			bool ReLoad() { return false; };
			///��������� �������
			bool Load() { return false; };
			///����������� ������
			bool Clear() { return false; };
		};
	
	}
}
