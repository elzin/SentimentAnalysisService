//GlobalMultiSearch.cpp
#include "stdafx.h"
#include ".\globalmultisearch.h"

namespace GlobalSearch
{
	///����� ����������� �� �������
	void CGlobalMultiSearch::ServerSearch(const wchar_t* wzQuery, std::wstring & wPluginXml)
	{
		SS_TRY
		{
			if (!GenerateQuery(wzQuery))
			{ SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"������ �� ��������������."); return; }
			PluginSearch(wPluginXml);
		}
		SS_CATCH(L"")
	}

	///����� ����������� �� �������� (sub-��������)
	void CGlobalMultiSearch::ClientSearch(const wchar_t* wzQuery,
										  const wchar_t* wzPluginXml, ISearchResult** ppSearchResult)
	{
		SS_TRY
		{
			if (!GenerateQuery(wzQuery))
			{ SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"������ �� ��������������."); return; }
			LinguisticSearch(wzPluginXml, ppSearchResult);
		}
		SS_CATCH(L"")
	}
	
	///�������� ������ ��������
	void CGlobalMultiSearch::GetPluginList(std::list<IGSPlugin*> & lstPlugins)
	{
		CGlobalSearchEngine::GetPluginList(lstPlugins);
	}
}