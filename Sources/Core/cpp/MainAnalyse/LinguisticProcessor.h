#pragma once

#include "../ASCInterface/ILinguisticProcessor.h"

#include ".\linguisticindexation.h"
#include ".\linguisticquery.h"
#include ".\linguisticsearch.h"
#include ".\linguisticshowresults.h"

namespace SS
{
namespace LinguisticProcessor
{

	class CLinguisticProcessor : public SS::Interface::Core::ILinguisticProcessor
	{
		SS::LinguisticProcessor::Indexation::CLinguisticIndexation*	m_pLinguisticIndexation;
		SS::LinguisticProcessor::CLinguisticQuery*		m_pLinguisticQuery;
		SS::LinguisticProcessor::Search::CLinguisticSearch*		m_pLinguisticSearch;
		SS::LinguisticProcessor::CLinguisticShowResults*	m_pLinguisticShowResults;

		SS::Core::Types::IndexationSearch::TLinguisticProcessorMode m_oMode;
	public:
		CLinguisticProcessor(void);
		virtual ~CLinguisticProcessor(void);
	public: // from IBase
		///������������
		ULONG Release();
		///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
		HRESULT QueryInterface(REFIID pIID, void** pBase); 
	public:// from ILinguisticProcessor
		/// ���������� ��������� ��� ���������� ��������������� ����������
		SS::Interface::Core::ILinguisticIndexation* GetLinguisticIndexation();
		/// ���������� ��������� ��� ���������� ���������������� ������� ������� ������������
		SS::Interface::Core::ILinguisticQuery* GetLinguisticQuery();
		/// ���������� ��������� ��� ���������� ���������������� ������
		SS::Interface::Core::ILinguisticSearch* GetLinguisticSearch();
		/// ���������� ��������� ��� ����������� ����������� ������
		SS::Interface::Core::ILinguisticShowResults* GetLinguisticShowResults();
		/// ������ ��� ����������� ������ ������ ���������������� ����������
	public:
		void SetMode(SS::Core::Types::IndexationSearch::TLinguisticProcessorMode* pMode)
		{
			m_oMode = *pMode;
			if(m_pLinguisticIndexation)
				m_pLinguisticIndexation->SetMode(&m_oMode);
			if(m_pLinguisticQuery)
				m_pLinguisticQuery->SetMode(&m_oMode);
			if(m_pLinguisticSearch)
				m_pLinguisticSearch->SetMode(&m_oMode);
			if(m_pLinguisticShowResults)
				m_pLinguisticShowResults->SetMode(&m_oMode);
		}
	};
}
}