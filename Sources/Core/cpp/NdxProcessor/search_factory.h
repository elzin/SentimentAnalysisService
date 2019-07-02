#pragma once

#include ".\ev_factory.h"
#include ".\sr_filler.h"
#include ".\es_filler_query.h"
#include ".\res.h"
#include ".\lgc_usings.h"
#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASCInterface\TCoommonTypes.h"
#include "..\ASDInterface\TNdxSearchEngineTypes.h"
#include "..\ASDInterface\INDXQuery.h"
#include ".\storage_manager.h"

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

///��������� ���������
struct SSearchSettings
{
	///����� ��������� ������
	SS::Core::Types::IndexationSearch::TSearchParams m_CommonSettings;
	///��������� ������ ��������� ������
	SS::Interface::Core::NdxSE::CNdxSearchSettings m_EngineSettings;
};

//--------------------------------------------------------------------//

///������� ��� �������� �������� ��� ������
class CSearchFactory : public CEvalFactory
{
public:
	CSearchFactory(
		const wchar_t* wszIndexStorageName,
		Storages::CStorageManager* pStorageManager, 
		Containers::CFindResultCollection* pSearchResult,
		CSearchResultFiller::TResultsTextsNumbers* pResultsTextsNumbers,
		SS::Interface::Core::NdxSE::IParametrizedQuery* pPrmQueryResult,
		SS::Core::Types::IndexationSearch::TSearchParams* pSearchParameter, 
		SS::Interface::Core::NdxSE::CNdxSearchSettings* pSearchSettings);
	virtual ~CSearchFactory(void);

	///������� ������ ���������� �������
	Logics::CCompositeLogic* CreateEquationLogic(void);
	///������� ��������� �����������
	CResultsContainer* CreateResultsContainer(void);
	///������� ��������� �����������
	CResultsChecker* CreateResultsChecker(unsigned int uiValidResultsDepth);
	///������� �������� ������� �����������
	CResultArgument* CreateResultArgument(unsigned int uiArgumentID, float fArgumentWeight, unsigned int uiArgumentDepth);
	///������� �����������
	CEvaluator* CreateEvaluator(void);
	///������� �������������� �������
	CBlockEquation* CreateCalcEquation(void);

	///���������� ��������� ����������� � ��������
	CSearchResultFiller* GetConvertorToLinearResults(void){return m_pConvertorToLinearResults;};
	///���������� ����������� ������ (�� �� ��������� �������)
	CESFiller* GetESFiller(void){return m_pESFillerFromQuery;};

	///���������� ������� ��������� ���������
	SSearchSettings* GetSearchSettings(void){return &m_SearchSettings;};

protected:
	///������� ��������� ���������
	SSearchSettings m_SearchSettings;
	
	///��������� ����������� � ��������
	CSearchResultFiller* m_pConvertorToLinearResults;
	///����������� ������ (�� �� ��������� �������)
	CESFillerFromQuery* m_pESFillerFromQuery;
	///�������� ���������� �������� ��������� ����
	Storages::CStorageManager* m_pStorageManager;
};

//--------------------------------------------------------------------//

}
}
}
}
}