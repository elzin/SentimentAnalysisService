#pragma once

#include ".\index_storage.h"
#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASDInterface\TNdxSearchEngineTypes.h"
#include ".\int_containers.h"
#include ".\res_containers.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Extracting
{

//--------------------------------------------------------------------//

///��������� ��������� ����������� ������
class CSearchResultFiller
{
public:
	typedef list<unsigned int> TResultsTextsNumbers;

	CSearchResultFiller(SS::Core::NdxSE::NdxProcessor::Containers::CFindResultCollection* pSearchResultCollection, 
		SS::Core::NdxSE::NdxProcessor::Storages::CIndexStorage* pIndexStorage, 
		TResultsTextsNumbers* pResultsTextsNumbers, unsigned int uiResultsIntervalRange, 
		SS::Interface::Core::NdxSE::CNdxSearchSettings::SSearchSettings::EStorageUsingMode StorageUsingMode);
	virtual ~CSearchResultFiller(void);

	///��������� ���������� �� ������ ������ �������
	void AddCoordinate(unsigned int* puiBuffer, unsigned int uiBufferSize, float fRelevance);
	///��������� ���������� ��������� ��� ������� ����������, 
	void StartAddCoordinate(unsigned int* puiBuffer, unsigned int uiBufferSize);
	///��������� ���������� �� ��������� ������������ �������
	void AddCoordinate(unsigned int uiLastValue, float fRelevance);
	///��������� ���������� �� ��������� ������������ �������, � ���������� ����������
	bool AddCoordinate(unsigned int uiLastValue, float fRelevance, 
		SS::Core::NdxSE::NdxProcessor::Containers::TIntervalCollection* pIntervalCollection);
	///��������� ���������� �� ��������� ������������ �������, � ���������� ��������������� ������
	bool AddCoordinate(unsigned int uiLastValue, float fRelevance, 
		SS::Core::NdxSE::NdxProcessor::Containers::CFindResult::TBlockHIDCollection* pBlockHIDCollection);
	
	///���������� �������� ��������� �����������
	SS::Core::NdxSE::NdxProcessor::Containers::CFindResultCollection* GetCurrSearchResultCollection(void){return m_pCurrSearchResultCollection;};
	///������������� �������� ��������� �����������
	void SetCurrSearchResultCollection(SS::Core::NdxSE::NdxProcessor::Containers::CFindResultCollection* pSearchResult){m_pCurrSearchResultCollection=pSearchResult;};
	///���������� ���������� �� ��������� �������
	Storages::CIndexStorage* GetIndexStorage(void){return m_pIndexStorage;};
	///���������� ��������� ������� ������� ����������� 
	TResultsTextsNumbers* GetResultsTextsNumbers(void){return m_pResultsTextsNumbers;};
	///���������� ��������� ����������� ������
	static void ViewSearchResult(SS::Interface::Core::CommonContainers::ISearchResult* pSearchResult, set<unsigned int>* pQueryIndexes = NULL);
	///���������� �������
	static void ViewTextBlockCut(
		SS::Interface::Core::CommonContainers::ITextBlockCut* pTextBlockCut, 
		bool bViewWords, bool bViewIndexes);

protected:
	///��������� ����������� ������
	SS::Core::NdxSE::NdxProcessor::Containers::CFindResultCollection* m_pCurrSearchResultCollection;
	///��������� �������� � ����������� �� ��������� ������� ���������
	SS::Core::NdxSE::NdxProcessor::Storages::CIndexStorage* m_pIndexStorage;

	///��������� ������� ������� ����������� 
	///(����������� �� ���� ����������� ����������� �� ��� ������ ������ ������� ����� �����)
	///���������� ������� ���������� ������������� � ������� �����������
	TResultsTextsNumbers* m_pResultsTextsNumbers;
	///������ ���������, � ������� ����� ����������� ���������
	unsigned int m_uiResultsIntervalRange;

	///������� ����� ������ � ���������
	unsigned int m_uiCurrTextNumber;
	unsigned int m_uiCurrTextBlockCutNumber;
	
	///������� ����� ������������� �������� ��� ������
	SS::Interface::Core::NdxSE::CNdxSearchSettings::SSearchSettings::EStorageUsingMode m_StorageUsingMode;
};

//--------------------------------------------------------------------//

}
}
}
}
}