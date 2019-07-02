#pragma once

#include "..\ASDInterface\INdxSearchEngine.h"
#include "..\ASCInterface\ICommonServices.h"
#include ".\eval.h"
#include ".\search_factory.h"
#include ".\sr_filler.h"
#include ".\storage_manager.h"
#include ".\res_containers.h"
#include ".\text_info_manager.h"


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

///��������� ����������� ������ �� ��������� ����
class CExtractingManager :  public SS::Interface::Core::NdxSE::INdxSearchEngineFind
{
	
	Extracting::CTextInfoManager* m_pTextInfoManager;
public:
	CExtractingManager(void);
	virtual ~CExtractingManager(void);

	///�������������� �������� �������� ����������
	void Init(SS::Core::NdxSE::NdxProcessor::Storages::CStorageManager* pStorageManager,
		SS::Interface::Core::CommonServices::ISettingsServer* pSettingsServer, 
		Extracting::CTextInfoManager* pTextInfoManager);

	///������ ������ ������, �������� ��������� ����������� ������ 
	//��� �� ��������� ��������� ������ ����� ������ ����������
	HRESULT StartFindSession(
		///��������� ����������� ������ 
		SS::Interface::Core::IISContainerUM* pISContainer);

	///������� ������ ������, ���������� � ��������� �������� � StartFindSession ���������� ������ 
	HRESULT EndFindSession(void);
	///������� ������ ������, ���������� � ��������� �������� � StartFindSession ���������� ������ 
	///��� ������������ ����������� ������ ������ �� ����� ������� ��������
	HRESULT EndFindByFieldSession(void);

	///���������� ����� � ������� ��������� ����, � ����� �� ������� �� ��� ������� 
	bool FindNext(SS::Interface::Core::CommonContainers::ISearchResult* pSearchResult);

	///����� � ��������� ��������� �� �������
	HRESULT Find(
		///��� ���������� ���������, ��� ��������� �����
		const wchar_t* wszIndexStorageName,
		///��������� ���������� �������
		SS::Interface::Core::NdxSE::IParametrizedQuery* pPrmQueryResult,
		///����� ��������� ������
		SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams, 
		///��������� ������ ���������� ������
		SS::Interface::Core::NdxSE::CNdxSearchSettings* pSearchSettings);

	///����� � ������� ���� ����� �� �������
	HRESULT Find(
		///��������� ����-����� ��������� (������)
		SS::Interface::Core::NdxSE::TNdxMetaFieldCollection* pNdxMetaFieldCollection,
		///����� ��������� ������
		SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams, 
		///��������� ������ ���������� ������
		SS::Interface::Core::NdxSE::CNdxSearchSettings* pSearchSettings);
protected:
	/// ���������� ��������� ���� �� �����
	SS::Interface::Core::CommonContainers::ITextBlock* GetTextBlock(wstring& wsIndexStorageName,
		SS::Core::NdxSE::NdxProcessor::Containers::CFindResult* pFindResult);

	///������� ��������� ��������� ������ (�� ����� ��������� ��������)
	void ClearTextBlocksStorageCollection();

	///������ ���������� ������
	SS::Interface::Core::IISContainerUM* m_pISContainer;

	///��������� ����� ��������� ��������� ������
	typedef map<wstring, SS::Interface::Core::CommonContainers::ITextBlock*> TTextBlocksStorageCollection;

	///��� ������� ��������� ��������� ���� ��������� ����.
	TTextBlocksStorageCollection m_TextBlocksStorageCollection;

	///����� � ��������� ��������� �� �������
	HRESULT ComplexFind(
		const wchar_t* wszIndexStorageName,
		SS::Interface::Core::NdxSE::IParametrizedQuery*	pPrmQueryResult,
		SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams, 
		SS::Interface::Core::NdxSE::CNdxSearchSettings* pSearchSettings,
		Containers::CFindResultCollection::EAddingMode ResultsAddingMode);
	///����� � ��������� ��������� �� �������
	bool FindByQuery(
		const wchar_t* wszIndexStorageName,
		SS::Interface::Core::NdxSE::IParametrizedQuery*	pPrmQueryResult,
		SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams, 
		SS::Interface::Core::NdxSE::CNdxSearchSettings* pSearchSettings,
		Containers::CFindResultCollection::EAddingMode ResultsAddingMode);

	///������� ��������� � ������
	/**
	\param[in]	wszIndexStorageName		�������� ���������
	\param[in]	pCommonSearchParameter	��������� ������
	\param[in]	pSearchSettings			��������� ������
	\return	�������� ����������
	*/
	bool PrepareToFind(
		const wchar_t* wszIndexStorageName,
		SS::Core::Types::IndexationSearch::TSearchParams* pCommonSearchParameter,
		SS::Interface::Core::NdxSE::CNdxSearchSettings* pSearchSettings);

	///���������� �������� ������
	void Reset(void);

	//��������� ��������� ������ � ����������� �� ������� ������
	void FillSearchResult(SS::Interface::Core::CommonContainers::ITextBlock* pTextBlock, 
			Containers::CInterval* pInterval, wstring* pwsIndexStorageName, unsigned int uiResultGroupID);
private:
	///������� ������
	SS::Interface::Core::NdxSE::IParametrizedQuery* m_pCurrentPrmQueryResult;

	///����������� - ��������� ��������� ���������� ���������� �����������
	CEvaluator* m_pEvaluator;

	///��������� �������
	CSearchFactory* m_pSearchFactory;

	///��������� ��� ������ � �����������
	SS::Interface::Core::CommonServices::ISettingsServer* m_pSettingsServer;

	///�������� ���������� �������� ��������� ����
	SS::Core::NdxSE::NdxProcessor::Storages::CStorageManager* m_pStorageManager;

	///��������� ������� ������� ����������� 
	///(����������� �� ���� ����������� ����������� �� ��� ������ ������ ������� ����� �����)
	///���������� ������� ���������� ������������� � ������� �����������
	CSearchResultFiller::TResultsTextsNumbers m_ResultsTextsNumbers;

	///������ ���������� ������
	Containers::CFindResultCollection m_SessionFindResults;
};

//--------------------------------------------------------------------//

}
}
}
}
}