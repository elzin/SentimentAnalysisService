#pragma once

#include "..\ASDInterface\IISContainer.h"
using namespace SS::Interface::Core;
using namespace SS::Interface::Core::CommonContainers;

#include "..\ASDInterface\IBasesManager.h"
using namespace SS::Interface::Core::ResourceManagers;

#include "..\ASCInterface\IInterface.h"
using namespace SS::Interface::Core::ResourceManagers;

#include "..\ASCInterface\ICommonContainers.h"
using namespace SS::Interface::Core::CommonContainers;

#include "..\ASCInterface\TCoommonTypes.h"
using namespace SS::Core::Types::IndexationSearch;

#include "..\ASCInterface\ICommonServices.h"
using namespace SS::Interface::Core::CommonServices;

#include <unordered_map>
using namespace std;

/// ���-��� LoadManager-��
typedef unordered_map<std::wstring, ILoadManager*> TLoadManagerMap;
/// ���-��� QueryResults-��
typedef unordered_map<std::wstring, IQueryResult*> TQueryResultsMap;
/// ���-��� SearchResults-��
typedef unordered_map<std::wstring, ISearchResult*> TSearchResultsMap;
/// ���-��� LinguisticProcessor-��
typedef unordered_map<std::wstring, ILinguisticProcessor*> TLinguisticProcessorMap;


class CISContainer : public IISContainerUM
{
public:
	CISContainer();
	virtual ~CISContainer();

public:
	virtual HRESULT QueryInterface(REFIID refIID, void** pBase);
	virtual ULONG Release();

public:
	virtual void SetLoadManager(ILoadManager* pLoadManager);
	///��������� ��������� ������� �������, ���������������� ����� ���� wszFieldName
	virtual IQueryResult* GetQueryResult(const wchar_t* wszFieldName);
	///��������� ��������� ����������� ������, ���������������� ����� ���� wszFieldName
	virtual ISearchResult* GetSearchResult(const wchar_t* wszFieldName);
	///��������� ���������������� ����������, ���������������� ����� ���� wszFieldName
	virtual ILinguisticProcessor* GetLinguisticProcessor(const wchar_t* wszFieldName);
	/// ������� ����������� ���������� ������
	virtual void Clear();

private:
	void SetBase(const wchar_t* wsz);
	ILoadManager* GetNewLoadManager(const wchar_t* wszFieldName);

private:
	TLinguisticProcessorMode m_oLinguisticMode;
	std::wstring m_wszBase;

	TQueryResultsMap m_QRMap;
	TSearchResultsMap m_SRMap;
	TLinguisticProcessorMap m_LPMap;
	TLoadManagerMap m_LMMap;
};
