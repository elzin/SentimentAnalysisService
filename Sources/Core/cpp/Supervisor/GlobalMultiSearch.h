//GlobalMultiSearch.h
#pragma once
#include "..\ASSInterface\ISupervisor.h"
using namespace SS::Interface::Supervisor;
#include "GlobalSearchEngine.h"

namespace GlobalSearch
{
	///������������� �����
	class CGlobalMultiSearch : public IGlobalMultiSearch,
							   public CGlobalSearchEngine
	{
	public:
		CGlobalMultiSearch(){};
		~CGlobalMultiSearch(){};
		///����� ����������� �� �������
		void ServerSearch(const wchar_t* wzQuery, std::wstring & wPluginXml);
		///����� ����������� �� �������� (sub-��������)
		void ClientSearch(const wchar_t* wzQuery,
						  const wchar_t* wzPluginXml, ISearchResult** ppSearchResult);
		///�������� ������ ��������
		void GetPluginList(std::list<IGSPlugin*> & lstPlugins);
	};
}