//GlobalSingleSearch.h
#pragma once
#include "..\ASSInterface\ISupervisor.h"
using namespace SS::Interface::Supervisor;
#include "GlobalSearchEngine.h"

namespace GlobalSearch
{

///������������ ���������� �����
class CGlobalSingleSearch : public IGlobalSingleSearch,
							public CGlobalSearchEngine
{
public:
	CGlobalSingleSearch(){};
	~CGlobalSingleSearch(){};
	///���������� ����� � ������� �������, ���������� �� ������� ������ ������������ � ����������
	bool Search(LPCWSTR wzQuery, LPCWSTR* rszText, int iCount, ISearchResult** ppSearchResult);
	///���������� ����� � ������
	bool Search(LPCWSTR wzQuery, LPCWSTR szText, ISearchResult** ppSearchResult);
	///���������� ����� �� ������� � �++ ���������
	bool Search(const wchar_t* wzQuery, ISearchResult** ppSearchResult);
	///�������� ������ ��������
	void GetPluginList(std::list<IGSPlugin*> & lstPlugins);
	virtual void GetQueryKeywords(LPCWSTR szQuery, std::vector<std::wstring>* pKeywords, 
			std::vector<std::vector<std::wstring> >* pMorphoForms);
};

}
