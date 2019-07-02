#pragma once


#include "../ASCInterface/ILinguisticProcessor.h"

#include "./LinguisticWorkingInterfaces.h"

#include "..\ASSInterface\IBlackBoxQuery.h"
using namespace SS::Interface::Core::BlackBox::Query;



//#include "../ASSInterface/ILexicaLib.h"
//#include "../ASSInterface/ISyntaxAnalyzer.h"
//#include "../ASSInterface/ISemanticAnalyze.h"
//#include "../ASSInterface/IRev.h"

//#include "../ASSInterface/IDictionaryManager.h"

namespace SS
{
namespace LinguisticProcessor
{

	class CLinguisticQuery 
        : public SS::Interface::Core::ILinguisticQuery
		, public SS::LinguisticProcessor::CLinguisticWorkingInterfaces
	{
	private:// ��������� ���������������� ����������
		/// ������ ����������� �������
		bool m_bRemember;		
	protected:// �����������
		/// ����������� ����������
	public:
		CLinguisticQuery(void);
		~CLinguisticQuery(void);
	public:
		/// ������ ������� ������������ ��� ������ ��� ��������� ������� � ���������� ���������� �� ������������ ������� 
		/**
			������������ ��� ������ ������� � ��������� �����������, ����������� �� ���� ����������� ��������� ������� SS
		*/
		void GenerateQuery(
			/// ��������� ������
			SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams
			/// ��������� ������� �������
			, SS::Core::Types::IndexationSearch::TQueryParams* pQueryParams
			/// ���������, ������� ���������� ���������
			, SS::Interface::Core::CommonContainers::IQueryResult* pQueryResult
			/// �������� ���������� ���������� ������� �������� �������
			, bool bIsRememberQuery					
			);

		/// ������ ������� ������������ ��� ������ ��� ��������� ������� � ���������� ���������� �� ������������ ������� 
		/**
			������������ ��� ������ ������� � ��������� �����������, ����������� �� ���� ����������� ��������� ������� SS
		*/
		void GenerateQuery(
			/// ��������� ������
			SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams
			/// ��������� ������� �������
			, SS::Core::Types::IndexationSearch::TQueryParams* pQueryParams
			/// ���������, ������� ���������� ���������
			, SS::Core::Types::IndexationSearch::TAbsentWords* pAbsentWords
			);

		virtual void GetQuerySourceIndices(std::vector<unsigned int>* pvIndices);

		virtual void GetQueryKeywords(LPCWSTR szQuery, std::vector<std::wstring>* pKeywords, 
				std::vector<std::vector<std::wstring> >* pMorphoForms);

	public:
		/// ���������� ��������� ��������� �������
		virtual SS::Interface::Core::BlackBox::Query::IQuery* GetLastQuery()
		{
			return m_pQuery;
		}
	protected:
		void AddCollectionIndexes(std::set<unsigned int>* pSet, IQueryUnitIndexCollection* pColl);
		/// ��������� ��������������� ������� ��������� � ������ ��� ���������
		void GetSynonims( SS::Dictionary::Types::TDictionaryIndex& oDictionaryIndex, std::vector<unsigned int>* pvIndices);
		/// ��������� ������������ ����� ��� ������� ����� �������
		void AddOneRootWords();
		/// ��������� ��������� ������� � ���������������� ����������
		void ApplyQueryParams(
			/// ��������� ������
			SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams
			/// ��������� ������� �������
			, SS::Core::Types::IndexationSearch::TQueryParams* pQueryParams
			);
		/// ���������� ������������� ����
		void FillAbsentWords(SS::Core::Types::IndexationSearch::TAbsentWords* pAbsentWords);
		/// �������� ������ �� ������� � ��� �����-���� ����������
		bool IsITextEmpty();
	};
}
}