#pragma once

#include ".\logic.h"
#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASDInterface\INdxQuery.h"
#include ".\cnt_factory.h"
#include ".\r_evals.h"
#include ".\stat_eval.h"

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
namespace Logics
{

//--------------------------------------------------------------------//

///������ �������� ������������� �����������
class CRelevanceLogic : public CLogic 
{
public:
	CRelevanceLogic(void);
	virtual ~CRelevanceLogic(void);
	
	///������������� ������������� �������� �� ����������
	void UseStatistic(SS::Core::NdxSE::NdxProcessor::Storages::CIndexStatisticStorage* pIndexStorage, unsigned int uiTotalTextsNumber);
	///������������� ������������� �������� �� �������� ������������ � ������ ���������� ����
	void UseStatisticProximity(SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory* pContainersFactory);
	///������������� ������������� �������� �� �������� ������������
	void UseTextProximity(SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory* pContainersFactory, 
		bool bCheckSequence, unsigned int uiIntervalLimitWeight, unsigned int uiIntervalLimitNumber);
	///������������� ������������� �������� �� �������� ������������
	void UseTableProximity(SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory* pContainersFactory, 
		unsigned int uiIntervalLimitWeight, unsigned int uiIntervalLimitNumber);
	///������������� ������������� �������� �� �������� ������������
	void UseTextAndHeadersProximity(SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory* pContainersFactory, 
		Containers::CFindResultCollection* pFindResultCollection, Storages::CIndexStorageHeaders* pIndexStorageHeaders, 
		bool bCheckSequence, unsigned int uiIntervalLimitWeight, unsigned int uiIntervalLimitNumber);
	///������������� ������������� �������� �� �������� ������������
	void UseTableAndHeadersProximity(SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory* pContainersFactory, 
		Containers::CFindResultCollection* pFindResultCollection, Storages::CIndexStorageHeaders* pIndexStorageHeaders, Storages::CIndexStorageTables* pIndexStorageTables, 
		bool bCheckSequence, unsigned int uiIntervalLimitWeight, unsigned int uiIntervalLimitNumber);

	///������������� ������ ��� ������������� ������������
	virtual void SetQuery(SS::Interface::Core::NdxSE::IParametrizedQuery* pPrmQueryResult);

	///������������� ������ ����� ������������
	void Init(SS::Core::NdxSE::NdxProcessor::Extracting::CResultArgument* pResultArgument);
	///�������� �������� ������ �� �������� ���������
	SS::Core::NdxSE::NdxProcessor::Containers::CValue* CreateLogicValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, 
		SS::Core::NdxSE::NdxProcessor::Extracting::CComplexArgument* pComplexArgument);
	///�������� �������� ��������� �� �������� ������
	void ToResultValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, 
		SS::Core::NdxSE::NdxProcessor::Extracting::CResultArgument* pResultArgument);

protected:
	///��������� �������� AND
	void MakeAnd(SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppChangedValue, 
		SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppValue){};
	///��������� �������� OR
	void MakeOr(SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppChangedValue, 
		SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppValue){};

	///��������� ������������ ������������� �������� ������������ ��������
	CRelevanceEvaluators* m_pRelevanceEvaluators;
	///����������� �������������� �������������
	CStatisticEvaluator* m_pStatisticEvaluator;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}
