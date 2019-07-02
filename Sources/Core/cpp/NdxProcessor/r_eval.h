#pragma once

#pragma once

#include ".\collection_containers.h"
#include ".\int_containers.h"
#include ".\prx_pos_containers.h"
#include ".\arg_res_int.h"
#include "..\ASDInterface\INDXQuery.h"

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

///��������� �������������������, � ������������ �� ��������
class CSequences
{
public:
	typedef vector<SS::Core::NdxSE::NdxProcessor::Containers::TIntervalPositions::iterator> TSequence; 
	typedef vector<TSequence*> TSequenceCollection; 

	CSequences(void);
	virtual ~CSequences(void);
	
	///��������� ������� � ������������������ !���������� ���������������!
	void AddPosition(unsigned char ucSequenceID, unsigned char ucPosInSequence);
	///��������� ��������� ������� ��������� �� �������������� �������������������
	bool CheckOnSequences(Containers::TIntervalPositions::iterator* pitIntervalPos);
	///��������� �������� �� ������ ������� ������������������ � ��������� ������� ���������
	bool IsSequencesBreaked(Containers::SIntervalPos* pIntervalPos);
	///��������� ��������� �������������������
	void UpdateSequences(Containers::SIntervalPos* pIntervalPos, Containers::TIntervalPositions::iterator itIntervalPos);
	///������� �����������������
	void Clear(void);
	///���� �����������������
	void Init(void);

	///��������� ��������� ��� ������������� ����������
	SS::Core::NdxSE::NdxProcessor::Containers::TIntervalPositions& GetNullCollection()
	{
		return m_NullCollection;
	}

protected:
	///�������� ������������������ ��� ������ �������
	CSequences::TSequence* GetSequence(Containers::SIntervalPos* pIntervalPos);

	///��������� ��������� � ��������� �������������������
	TSequenceCollection m_SequenceCollection;
	///��������� ��� ������������� ����������
	SS::Core::NdxSE::NdxProcessor::Containers::TIntervalPositions m_NullCollection;
};

//--------------------------------------------------------------------//

class CRelevanceEvaluators;

///����������� ������������� �� ������������ ���� � ���������
///�������� ��������� ����, � ����� ���������� �� ����������������� �� ������������
class CRelevanceEvaluator : 
	public SS::Core::NdxSE::NdxProcessor::Containers::CMasterCollection<SS::Core::NdxSE::NdxProcessor::Containers::CWordInSequence>,
	public CFactoryClient<SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory>
{
public:
	CRelevanceEvaluator(unsigned int uiEvalID, bool bCheckSequence, Containers::CContainersFactory* pContainersFactory);
	virtual ~CRelevanceEvaluator(void);

	///��������� �  ���������� ������� �������� ��������� �� ��������������
	virtual Containers::CWordInSequence* AddPosition(unsigned char ucPositionID, unsigned char ucSequenceID, unsigned char ucPosInSequence, SS::Interface::Core::NdxSE::IWord* pWord);
	///��������� ������� � ��������� ������������
	void AddArgumentPosition(CComplexArgument* pComplexArgument, Containers::CCoordinateNode_4s* pCoordinateNode);
	///��������� ��� �� �������� � ������� ������������ �������� � �����������
	virtual void Evaluate(unsigned int uiEvalID) = 0;
	///������������� ������� ����� �������������� ���������
	void SetDocumentBasisIndex(unsigned int uiValue){m_uiDocumentBasisIndex=uiValue;};
	///������������� ��������� ����������� ��� ���������� �����������
	void SetOwner(CRelevanceEvaluators* pRelevanceEvaluatorsOwner){m_pRelevanceEvaluatorsOwner=pRelevanceEvaluatorsOwner;};

	///��������� ��� "�������" ����������
	static const unsigned int m_uiGoodIntervalLimitWeight=80;
	///������������ ���������� ������� ����������
	static const unsigned int m_uiGoodIntervalsLimitNumber=20;
	///����������� �������� ����� ���������
	static const unsigned int m_uiMaxIntervalLength=128;

protected:
	typedef map<unsigned int, SS::Core::NdxSE::NdxProcessor::Containers::CWordInSequence*> TSortedChildCollection;

	///���������� ��� ���������
	virtual unsigned int GetIntervalWeight(Containers::CInterval* pInterval){return 0;};
	///������� �������� ����������
	virtual Containers::CInterval* CreateInterval(unsigned int uiHeadPos, unsigned int uiTailPos) = 0;
	///��������� �������� � ���������
	void AddInterval(unsigned int uiHeadPos, unsigned int uiTailPos);

	///���������� ������� ���������� ���� ����������� � ����������
	unsigned int GetEvaluatedChildsNumber(void);
	///���������� ������� ���������� ���� ����������� � ����������
	void ResetEvaluatedChildsNumber(void){m_uiEvaluatedChildsNumber=EMPTY_VALUE;};

	///��������� ��������� � ��������� �������������������
	CSequences m_SequenceCollection;
	///��������� ��� �������� �������� ��������������� CWord
	TSortedChildCollection m_SortedChildCollection;
	///������� ���������� ���� ����������� � ����������
	unsigned int m_uiEvaluatedChildsNumber;
	///������� ����� �������������� ���������
	unsigned int m_uiDocumentBasisIndex;
	///�������� ������������
	CRelevanceEvaluators* m_pRelevanceEvaluatorsOwner;

	///���� ����� �������������������
	const bool m_bCheckSequence;

	///������� ���������� ������� ����������
	unsigned int m_uiGoodIntervalsNumber;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}
