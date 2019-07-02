#pragma once

#include ".\r_eval.h"
#include ".\res_containers.h"
#include ".\index_storage_hdr.h"
#include ".\index_storage_tbl.h"

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

///��������� ������������ �������� ������������
class CRelevanceEvaluators : 
	public SS::Core::NdxSE::NdxProcessor::Containers::CMasterCollection<CRelevanceEvaluator>,
	public CFactoryClient<SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory>
{
public:
	CRelevanceEvaluators(Containers::CContainersFactory* pContainersFactory);
	CRelevanceEvaluators(Containers::CContainersFactory* pContainersFactory, 
		unsigned int uiIntervalLimitWeight, unsigned int uiIntervalLimitNumber);
	CRelevanceEvaluators(Containers::CContainersFactory* pContainersFactory, 
		bool bCheckSequence, unsigned int uiIntervalLimitWeight, unsigned int uiIntervalLimitNumber);
	CRelevanceEvaluators(Containers::CContainersFactory* pContainersFactory, 
		bool bCheckSequence, unsigned int uiIntervalLimitWeight, unsigned int uiIntervalLimitNumber,
		Containers::CFindResultCollection* pFindResultCollection, Storages::CIndexStorageHeaders* pIndexStorageHeaders);
	CRelevanceEvaluators(Containers::CContainersFactory* pContainersFactory, 
		bool bCheckSequence, unsigned int uiIntervalLimitWeight, unsigned int uiIntervalLimitNumber,
		Containers::CFindResultCollection* pFindResultCollection, 
		Storages::CIndexStorageHeaders* pIndexStorageHeaders, Storages::CIndexStorageTables* pIndexStorageTables);

	virtual ~CRelevanceEvaluators(void);
	
	///��������� ����������� � ���������
	virtual CRelevanceEvaluator* AddEvaluator(unsigned int uiEvaluatorID);
	///��������� ������� ��������� � �����������
	void AddArgumentPosition(CComplexArgument* pComplexArgument, SS::Core::NdxSE::NdxProcessor::Containers::CCoordinateNode_4s* pCoordinateNode);
	///��������� ��� �� �������� � ������� ������������ �������� � �����������
	float Evaluate(unsigned int uiEvalID);
	///���������� ��������� ����������� ����������
	SS::Core::NdxSE::NdxProcessor::Containers::TIntervalCollection* GetBestIntervals(void);
	///��������� ��������� ����������� ����������, ������� �������� ������� �������� �� ����������
	void FillIntervals(CResultArgumentWithIntervals* pResultArgumentWithIntervals);
	///������������� ������� ����� �������������� ���������
	void SetDocumentBasisIndex(unsigned int uiValue);

	///������� ��������� ����������
	void ClearRangedIntervals(void);
	///��������� �������� � ����� ���������
	bool AddInterval(Containers::CInterval* pInterval);
	///���������� ������� ���������� ����������� ����������
	unsigned int GetAddedIntervalsCount(void){return (unsigned int)m_IntervalsByHeadTail.size();};

protected:
	typedef map<unsigned int, Containers::TIntervalCollection*> TRangedIntervalCollection;
	class CCompareInterval
	{
	public:
		unsigned int m_uiHeadPos;
		unsigned int m_uiTailPos;
		bool operator<(const CCompareInterval& Value) const
		{
			if(m_uiHeadPos<Value.m_uiHeadPos)
				return true;
			else if(m_uiHeadPos==Value.m_uiHeadPos){
				if(m_uiTailPos<Value.m_uiTailPos)
					return true;
				else if(m_uiTailPos==Value.m_uiTailPos)
					return false;
			}
			return false;
		}
	
	};
	typedef map<CCompareInterval, Containers::CInterval*> TIntervalsByHeadTail;

	///������ �������� ������������
	enum EEvalProductionMode{
		///����������� �������� � ������
		epmTxtProximity,
		///����������� �������� � ��������
		epmTblProximity,
		///����������� �������� � �������� � ������ ����������
		epmHdrAndTblProximity,
		///����������� �������� � ������ � ������ ����������
		epmHdrAndTxtProximity,
		///����������� �������� � ������ � ������ ���������� ���� � ���� �������
		epmTxtStatProximity,
	};

	///��������� ��������� ���������� � ������������ ���������
	void AddToRangedIntervals();

	///����� �������� ������������
	const EEvalProductionMode m_EvalProductionMode;
	///��������� ����������� ���������� ��������������� �� �����
	TRangedIntervalCollection m_RangedIntervals;
	///��������� ���������� ���������� �� �������� ������ � ������, ��� ����������� ������� ����������
	TIntervalsByHeadTail m_IntervalsByHeadTail;
	///���� ����� �������������������
	const bool m_bCheckSequence;
	///��������� ��� ����������
	unsigned int m_uiIntervalLimitWeight;
	///���������� ���������� ����������, ������� ����� ����������� ��� ������ ������
	unsigned int m_uiIntervalLimitNumber;
	///��������� ����������� ������
	Containers::CFindResultCollection* m_pFindResultCollection;
	///��������� ��������� ����������
	Storages::CIndexStorageHeaders* m_pIndexStorageHeaders;
	///��������� ��������� ������
	Storages::CIndexStorageTables* m_pIndexStorageTables;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}
