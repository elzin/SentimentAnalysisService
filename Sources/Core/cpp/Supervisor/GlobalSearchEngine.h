//GlobalSearchEngine.h
#pragma once
#include "GlobalSearchData.h"

namespace GlobalSearch
{
	///���������������� ����������� ������
	class CGlobalSearchEngine : public CGlobalSearchData
	{
	protected:
		TSearchParams m_oSearchParams;
		TQueryParams  m_oQueryParams;

	public:
		CGlobalSearchEngine(){};
		~CGlobalSearchEngine(){};
		///��������� �������
		bool GenerateQuery(const wchar_t* wzQuery);
		///���������� ������ ���������� xml ��������� �� ��������
		void PluginSearch(std::wstring & wPluginXml);
		///����� �� ����������� ��������
		void LinguisticSearch(const wchar_t* wzPluginXml, ISearchResult** ppSearchResult);
		///�������� ������ ��������
		void GetPluginList(std::list<IGSPlugin*> & lstPlugins);
		///����� �� ����
		void CacheSearch();
	};
}