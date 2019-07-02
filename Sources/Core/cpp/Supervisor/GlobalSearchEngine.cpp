//GlobalSearchEngine.cpp
#include "StdAfx.h"
#include ".\globalsearchengine.h"

namespace GlobalSearch
{
	///��������� �������
	bool CGlobalSearchEngine::GenerateQuery(const wchar_t* wzQuery)
	{
		SS_TRY
		{
			m_oQueryParams.m_GenerateQueryMode = SS::Core::Types::IndexationSearch::gqmString;
			m_oQueryParams.SetQuery(wzQuery);
			m_oQueryParams.m_SearchDepth = SS::Core::Types::IndexationSearch::sdNormal;
			m_pQueryResult->Clear();
			m_pLinguisticQuery->GenerateQuery(&m_oSearchParams, &m_oQueryParams, m_pQueryResult, false);
			if (!m_pQueryResult->GetFirstQueryIndex()) return false;
		}
		SS_CATCH(L"")
		return true;
	}

	///���������� ������ ���������� xml ��������� �� ��������
	void CGlobalSearchEngine::PluginSearch(std::wstring & wPluginXml)
	{
		SS_TRY
		{
			if (!m_pQueryResult->GetFirstQueryIndex())
			{ SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"������ �� ��������������."); return; }
			//�������
			CGlobalSearchData::CreatePluginSearchData();
			if (!m_pGSPluginManager->LoadPlugins())
			{ SS_THROW(L"������� ����������� ������ �� �����������."); return; }
			//Parse
			m_pSearchResult->Clear();
			m_pSearchResult->SetSortedMode(false);
			std::wstring wResult;
			wPluginXml = L"<Result>";
			unsigned int uiID = 0;
			const wchar_t* wzPluginResult = NULL;
			m_pGlobalSearchBase->AddQuery(m_oQueryParams.GetQuery(), m_pQueryResult->GetFirstQueryIndex()->GetQueryWord(), uiID);
			for (IGSPlugin* pPlugin = m_pGSPluginManager->GetFirstPlugin(); pPlugin; pPlugin = m_pGSPluginManager->GetNextPlugin())
			{
				if ( !pPlugin->IsSelected() )
				{ continue;	}
				//��������� � ����
				wzPluginResult = m_pGlobalSearchBase->GetPluginResult(uiID, pPlugin->GetName());
				if (wzPluginResult != NULL)
				{
					wPluginXml += wzPluginResult;
				}
				else
				{
					wResult.clear();
					pPlugin->Parse(m_pQueryResult->GetFirstQueryIndex()->GetQueryWord());
					pPlugin->GetXML(&wResult);
					m_pGlobalSearchBase->AddPluginResult(uiID, pPlugin->GetName(), wResult.c_str());
					wPluginXml += wResult;
				}
			}
			wPluginXml += L"</Result>";
		}
		SS_CATCH(L"")
	}

	///����� �� ����������� ��������
	void CGlobalSearchEngine::LinguisticSearch(const wchar_t* wzPluginXml, ISearchResult** ppSearchResult)
	{
		SS_TRY
		{
			if (!m_pQueryResult->GetFirstQueryIndex())
			{ SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"������ �� ��������������."); return; }
			//�����������
			m_pSearchResult->Clear();
			m_pSearchResult->SetSortedMode(false);
			m_pSearchResult->SetGsXML(wzPluginXml);
			TUpdateRelevanceParams oUpdateRelevanceParams;
			m_pLinguisticSearch->UpdateRelevance(m_pSearchResult, &m_oSearchParams, &m_oQueryParams, &oUpdateRelevanceParams);
			m_pSearchResult->SetSortedMode(true);
			*ppSearchResult = m_pSearchResult;
		}
		SS_CATCH(L"")
	}

	///�������� ������ ��������
	void CGlobalSearchEngine::GetPluginList(std::list<IGSPlugin*> & lstPlugins)
	{
		SS_TRY
		{
			CGlobalSearchData::CreatePluginSearchData();
			if (!m_pGSPluginManager->LoadPlugins())
			{ SAVE_LOG(SS_ERROR AND __WFUNCTION__ AND L"������� �� ���������"); return; }
			for (IGSPlugin* pPlugin = m_pGSPluginManager->GetFirstPlugin(); pPlugin; pPlugin = m_pGSPluginManager->GetNextPlugin())
			{ lstPlugins.push_back(pPlugin); }
		}
		SS_CATCH(L"")
	}

	///����� �� ����
	void CGlobalSearchEngine::CacheSearch()
	{
		SS_TRY
		{
			SS_THROW(L"�� ������������.");
		}
		SS_CATCH(L"")
	}
}



