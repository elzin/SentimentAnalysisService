#pragma once

#pragma once

#ifdef _SS_UNITTESTS

#include ".\unittestsusings.h"
#include "../ASCInterface/ICommonContainers.h"
#include "..\ASDInterface\TNdxSearchEngineTypes.h"
#include "..\ASDInterface\IISContainer.h"
#include "..\ASDInterface\INdxQuery.h"

namespace SS
{
namespace UnitTests
{
namespace NdxSE
{
namespace NdxProcessor
{

//--------------------------------------------------------------------//

class CCommonContainersUsing : public CUnitTestsUsings
{
public:
	CCommonContainersUsing(void):m_pIndexationResult(NULL), m_pSearchResult(NULL), m_pQueryResult(NULL), m_pPrmQueryResult(NULL), m_pISContainer(NULL){};

protected:
	///���������� �������� ��������
	SS::Interface::Core::ResourceManagers::ILoadManager* GetLoadManager(void);
	///���������� ��������� ��� ����������
	SS::Interface::Core::CommonContainers::IIndexationResult* GetIndexationResult(void){return m_pIndexationResult;};
	///���������� ��������� ��� ������
	SS::Interface::Core::CommonContainers::ISearchResult* GetSearchResult(void){return m_pSearchResult;};
	///���������� ��������� ��� �������
	SS::Interface::Core::CommonContainers::IQueryResult* GetQueryResult(void){return m_pQueryResult;};
	///���������� ��������� ��� ����������������� ������� (�� �� ����������� �������)
	SS::Interface::Core::NdxSE::IParametrizedQuery* GetPrmQueryResult(void){return m_pPrmQueryResult;};
	///���������� ��������� ��� ���������� ����� ����������
	SS::Interface::Core::NdxSE::TNdxMetaFieldCollection* GetNdxMetaFieldCollection(void){return &m_NdxMetaFieldCollection;};
	///���������� ��������� ��� ������
	SS::Interface::Core::IISContainerUM* GetISContainer(void){return m_pISContainer;};

	//��������� ��� ���������� �������
	void StartFillIndexationResult(void);
	void FillIndexationResult(void);
	void FillIndexationResultTable(void);
	void InitMetaFieldCollection(void);
	void FillMetaFieldCollection(void);
	void ViewMetaFieldCollection(void);

	///���������� ��������� ���������
	void InitDocumentStructure(void);
	///��������� ���������� ���������� � ������������� �� ���������� ���������
	void FillIndexationResultByStructure(unsigned int uiBlockNumber);

	void GetQueries(wstring& wsFilePath, vector<wstring>& Queries);
	void QueryResultToString(wstring* pwszQueryResult);

	//��������� ��� ������� �������
	void FillQueryResult(void);
	void NextText(void){m_uiCurrTextNumber++; m_uiCurrPosition=0;};

	void SetCurrentQuery(const wchar_t* pwszQuery){if(pwszQuery) m_wszCurrentQuery.assign(pwszQuery);};
private:
	void MakeQueryFromString(wstring& wszValue);
	unsigned int GetTogetherCharsNumber(wchar_t* wszToken, wchar_t wsChar);
	void MakeQueryIndexFromString(wstring& wszValue, char chOperator);
	void FillTexBlockCut(SS::Interface::Core::CommonContainers::ITextBlockCut* pTextBlockCut, unsigned int uiIndexesCount);

	///������� ����� ������
	unsigned int m_uiCurrTextNumber;
	///������� ����� ������
	unsigned int m_uiCurrPosition;
	///��������� ��� ����������
	SS::Interface::Core::CommonContainers::IIndexationResult* m_pIndexationResult;
	///��������� ��� ������
	SS::Interface::Core::CommonContainers::ISearchResult* m_pSearchResult;
	///��������� ��� �������
	SS::Interface::Core::CommonContainers::IQueryResult* m_pQueryResult;
	///��������� ��� ����������������� �������
	SS::Interface::Core::NdxSE::IParametrizedQuery* m_pPrmQueryResult;
	///��������� ��� ���������� ����� ����������
	SS::Interface::Core::NdxSE::TNdxMetaFieldCollection m_NdxMetaFieldCollection;
	///��������� ��� ������
	SS::Interface::Core::IISContainerUM* m_pISContainer;
	///��������� ������������� �������� �������
	wstring m_wszCurrentQuery;
	///��������� ���������
	vector<wstring> m_DocumentStructure;
};

//--------------------------------------------------------------------//

}
}
}
}

#endif //_SS_UNITTESTS
