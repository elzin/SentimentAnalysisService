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


class CISContainerLite : public IISContainerUM
{
public:
	CISContainerLite();
	virtual ~CISContainerLite();

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
	IQueryResult* m_pQueryResult;
	ISearchResult* m_pSearchResult;
	ILinguisticProcessor* m_pLinguisticProcessor;
};
