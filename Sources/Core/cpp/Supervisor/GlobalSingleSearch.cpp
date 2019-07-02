//GlobalSingleSearch.cpp
#include "stdafx.h"
#include ".\globalsinglesearch.h"

namespace GlobalSearch
{
///���������� ����� � ������� �������, ���������� �� ������� ������ ������������ � ����������
bool CGlobalSingleSearch::Search(LPCWSTR wzQuery, LPCWSTR* rszText, int iCount, ISearchResult** ppSearchResult)
{
	SS_TRY;

	if(!GenerateQuery(wzQuery))
	{
		SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"������ �� ��������������.");
		return false;
	}

	m_pSearchResult->Clear();
	m_pSearchResult->SetSortedMode(false);
	for (int i = 0; i < iCount; i++)
	{
		ITextBlock* pBlock = m_pSearchResult->AddTextBlock();
		ITextBlockCut* pCut = pBlock->AddBlockCut();
		pCut->SetTextCut(rszText[i]);
	}
	
	TSearchParams oSearchParams;
	TUpdateRelevanceParams oUpdateRelevanceParams;
	m_pLinguisticSearch->UpdateRelevance(m_pSearchResult, &m_oSearchParams, &m_oQueryParams, &oUpdateRelevanceParams);
	*ppSearchResult = m_pSearchResult;

	SS_CATCH(L"");
	return true;
}

///���������� ����� � ������
bool CGlobalSingleSearch::Search(LPCWSTR wzQuery, LPCWSTR szText, ISearchResult** ppSearchResult)
{
	return Search(wzQuery, &szText, 1, ppSearchResult);
}

///���������� ����� �� ������� � �++ ���������
bool CGlobalSingleSearch::Search(const wchar_t * wzQuery, ISearchResult** ppSearchResult)
{
	SS_TRY
	{
		if (!GenerateQuery(wzQuery))
		{ SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"������ �� ��������������."); return false; }
		std::wstring wPluginXml;
		PluginSearch(wPluginXml);
		LinguisticSearch(wPluginXml.c_str(), ppSearchResult);
	}
	SS_CATCH(L"")
	return true;
}

///�������� ������ ��������
void CGlobalSingleSearch::GetPluginList(std::list<IGSPlugin*> & lstPlugins)
{
	CGlobalSearchEngine::GetPluginList(lstPlugins);
}

void CGlobalSingleSearch::GetQueryKeywords(LPCWSTR szQuery, std::vector<std::wstring>* pKeywords, 
		std::vector<std::vector<std::wstring> >* pMorphoForms)
{
	m_pLinguisticQuery->GetQueryKeywords(szQuery, pKeywords, pMorphoForms);
}

}
