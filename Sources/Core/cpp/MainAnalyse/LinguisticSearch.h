#pragma once

#include "../ASCInterface/ILinguisticProcessor.h"
//#include "../ASCInterface/ITextsInfoExtracting.h"


#include "../ASSInterface/ILexicaLib.h"
#include "../ASSInterface/ISemanticAnalyze.h"
#include "../ASSInterface/IRev.h"
#include "../ASSInterface/ICommon.h"

#include "./LinguisticQuery.h"
#include "./ResultsEx.h"

#include "./GlobalSearch.h"
#include "./LocalSearch.h"


#define ANAFORA
//#define _UNIT_TEST


namespace SS
{
namespace LinguisticProcessor
{
namespace Search
{
	class CLinguisticSearch 
		: public SS::Interface::Core::ILinguisticSearch
		, public SS::Core::CommonServices::CBaseCoreClass
		, public SS::Interface::Core::Common::CAnalyseParams
	{
		SS::Core::Types::IndexationSearch::TLinguisticProcessorMode m_oMode;

		CGlobalSearch	m_oGlobalSearch;
		CLocalSearch	m_oLocalSearch; 

	public:
		CLinguisticSearch(void);
		~CLinguisticSearch(void);
	public:
		/// ������������ ��������������� ������������� ����������� ������
		void UpdateRelevance(
			/// ��������� � ������������ ������
			SS::Interface::Core::CommonContainers::ISearchResult* pSearchResult
			/// ��������� � �������� ������������ (� ������ ���������, �������������� ��� ������ ILinguisticQuery)
			,SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams
			/// ��������� ������� ������� (� ������ ���������, �������������� ��� ������ ILinguisticQuery)
			, SS::Core::Types::IndexationSearch::TQueryParams* pQueryParams
			/// ��������� �������� �������������
			, SS::Core::Types::IndexationSearch::TUpdateRelevanceParams* pUpdateRelevanceParams
			);

		/// ��������� ����� ���� ����������� �����������
		virtual void SetTitles(SS::Interface::Core::CommonContainers::ITextBlock * pTextBlock) 
		{
			SS_TRY
			{
				SS_THROW(L"������ ������������ ����� ILinguisticSearch::SetTitles()");
			}
			SS_CATCH(L"");
		}

		void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);

	public:
		/// ������������� ���������� ������� ������� ��� ����������� �������
		void SetLastQuery(SS::Interface::Core::BlackBox::Query::IQuery* pQuery);		
	public:
		void SetMode(SS::Core::Types::IndexationSearch::TLinguisticProcessorMode* pMode)
		{
			m_oMode = *pMode;
		}
	private:
		/// ��������� ��������� ������
		void ApplySearchParams(	
			SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams
			, SS::Core::Types::IndexationSearch::TQueryParams* pQueryParams
			, SS::Core::Types::IndexationSearch::TUpdateRelevanceParams* pUpdateRelevanceParams
			);
	};
}
}
}