#pragma once

#include "..\ASCInterface\IInterface.h"
#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASSInterface\IGSPluginManager.h"

#include <string>

// {438C6FE7-5665-4d38-B3E6-74EE340F6FF3}
static const GUID CLSID_Supervisor = 
{ 0x438c6fe7, 0x5665, 0x4d38, { 0xb3, 0xe6, 0x74, 0xee, 0x34, 0xf, 0x6f, 0xf3 } };
// {6237394C-5968-4e9c-BAFA-9D28E5E44FC7}
static const GUID IID_Supervisor = 
{ 0x6237394c, 0x5968, 0x4e9c, { 0xba, 0xfa, 0x9d, 0x28, 0xe5, 0xe4, 0x4f, 0xc7 } };


namespace SS
{
namespace Interface
{
namespace Supervisor
{

class IIndexBase
{
public:
	///��������� ����, ��� ���� ���������� �������� ���� �����������
	virtual bool Open() = 0;
	///��������� ����
	virtual void Close() = 0;
	///������� ����
	virtual void Remove() = 0;
	/// ���������� ���� � ���� ������
	virtual LPCWSTR GetPath() = 0;
	///���������� ���������� ��� ���� (����. IndX7Z7N700OYALNO0X)
	virtual LPCWSTR GetName() = 0;
	///���������� �������� ���� (������������)
	virtual LPCWSTR GetDescription() = 0;
	///������������� �������� ����
	virtual bool SetDescription(LPCWSTR szDescription) = 0;
	///���������, �������� �� ���� ����� ������
	virtual BOOL IsKnowledgeBase() = 0;
	///������������� ���� ���� ������
	virtual bool SetKnowledgeBase(BOOL bSet) = 0;
};

class IDatabaseList
{
public:
	///���������� ������ ����
	virtual IIndexBase* GetFirstBase() = 0;
	///���������� ��������� ����
	virtual IIndexBase* GetNextBase() = 0;
	///���� ���� �� ��������
	virtual IIndexBase* FindBase(LPCWSTR szDescription) = 0;
	///������� ����� ����
	virtual IIndexBase* CreateBase(LPCWSTR szDescription) = 0;
};

class IPluginInfo
{
public:
	///�������� ��� ����������
	virtual LPCWSTR GetName() = 0;
	///�������� ��� ��������� ���������
	virtual void Select(bool bSet) = 0;
	///��������� ������� �� ���������
	virtual bool IsSelected() = 0;
};

class IPluginList
{
public:
	///��������� ������� ���������� ������
	virtual IPluginInfo* GetFirst() = 0;
	///��������� ���������� ���������� ������
	virtual IPluginInfo* GetNext() = 0;
};

class ILocalSearchEngine
{
public:
	///��������� ����� �� ��������� ����
	virtual bool Search(LPCWSTR szQuery, 
		SS::Interface::Core::CommonContainers::ISearchResult** ppSearchResult) = 0;
	///�������� ������� � ����������� ������
	virtual bool Load(LPCWSTR szQuery) = 0;
};

class IIndexationEngine
{
public:
	///���������������� ���� ��� ����������
	virtual bool Indexate(LPCWSTR szPath) = 0;
};

//-----------------------------------------------------------���������� �����-------------------------------------------------------//

///������������ ���������� �����
class IGlobalSingleSearch
{
public:
	IGlobalSingleSearch(){};
	virtual ~IGlobalSingleSearch(){};
	///���������� ����� � ������� �������, ���������� �� ������� ������ ������������ � ����������
	virtual bool Search(LPCWSTR wzQuery, LPCWSTR* rszText, int iCount,
						SS::Interface::Core::CommonContainers::ISearchResult** ppSearchResult) = 0;
	///���������� ����� � ������
	virtual bool Search(LPCWSTR wzQuery, LPCWSTR szText, 
						SS::Interface::Core::CommonContainers::ISearchResult** ppSearchResult) = 0;
	///���������� ����� �� ������� � �++ ���������
	virtual bool Search(const wchar_t* wzQuery, 
						SS::Interface::Core::CommonContainers::ISearchResult** ppSearchResult) = 0;
	///�������� ������ ��������
	virtual void GetPluginList(std::list<SS::Interface::GSPlugins::IGSPlugin*> & lstPlugins) = 0;
	virtual void GetQueryKeywords(LPCWSTR szQuery, std::vector<std::wstring>* pKeywords, 
			std::vector<std::vector<std::wstring> >* pMorphoForms) = 0;
};

///������������� ���������� �����
class IGlobalMultiSearch
{
public:
	IGlobalMultiSearch(){};
	virtual ~IGlobalMultiSearch(){};
	///����� ����������� �� �������
	virtual void ServerSearch(const wchar_t* wzQuery, std::wstring & wPluginXml) = 0;
	///����� ����������� �� �������� (sub-��������)
	virtual void ClientSearch(const wchar_t* wzQuery, const wchar_t* wzPluginXml,
							  SS::Interface::Core::CommonContainers::ISearchResult** ppSearchResult) = 0;
	///�������� ������ ��������
	virtual void GetPluginList(std::list<SS::Interface::GSPlugins::IGSPlugin*> & lstPlugins) = 0;
};

//----------------------------------------------------------------����������-------------------------------------------------------//

class ISupervisor : public virtual IBase
{
public:
	///���������� ������ ������������ ��������� ���
	virtual IDatabaseList* GetBasesList() = 0;
	///�������� ������ ����������� ����������� ������
	virtual IPluginList* GetPluginList() = 0;
	///�������� ��������� ���������� ������
	virtual ILocalSearchEngine* GetLocalSearchEngine() = 0;
	///�������� ��������� ����������� ������������� ������
	virtual IGlobalSingleSearch* GetGlobalSingleSearch() = 0;
	///�������� ��������� ����������� �������������� ������
	virtual IGlobalMultiSearch* GetGlobalMultiSearch() = 0;
	///�������� ��������� ����������
	virtual IIndexationEngine* GetIndexationEngine() = 0;
};

}
}
}
