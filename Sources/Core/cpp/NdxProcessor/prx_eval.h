#pragma once

#include ".\r_eval.h"
#include ".\prx_union.h"

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

///����������� �������� ������������ ���� � ������ �������� 
///���������� ���� � ���������
class CProximityEvaluator_Text : public CRelevanceEvaluator
{
public:
	CProximityEvaluator_Text(unsigned int uiEvalID, bool bCheckSequence, Containers::CContainersFactory* pContainersFactory);
	virtual ~CProximityEvaluator_Text(void);

	///��������� �  ���������� ������� �������� ��������� �� ��������������
	Containers::CWordInSequence* AddPosition(unsigned char ucPositionID, unsigned char ucSequenceID, unsigned char ucPosInSequence, SS::Interface::Core::NdxSE::IWord* pWord);

	///��������� ��� �� �������� � ������� ������������ �������� � �����������
	void Evaluate(unsigned int uiEvalID);

	///���������� ������� �������� ���������
	void ViewIntervalPositions(void);

protected:
	typedef vector<pair<unsigned int, unsigned int> > TEvaledIntervalCollection;

	///���������� ��� ���������
	unsigned int GetIntervalWeight(Containers::CInterval* pInterval);
	///������� �������� ����������
	Containers::CInterval* CreateInterval(unsigned int uiHeadPos, unsigned int uiTailPos);

	//��������� ������� � ��������
	bool ReplaceIntervalPosition(Containers::CWordInSequence* pCommonPosition,
		Containers::TIntervalPositions::iterator* pOldPosition, unsigned int uiPopedPosition);
	///��������� ��������������� ��������
	//void UpdateTempInterval(unsigned int uiHeadPos, unsigned int uiTailPos);
	///������� ���������� 
	bool PrepareEvaluation(unsigned int uiEvalID);
	bool PreparePositions(unsigned int uiEvalID, unsigned int uiIntervalIndex);
	///��������� ���������
	void EvaluateIntervals(void);
	///��������� ��������� ��� ������ � ���� ������
	bool SingleChildEvaluation(void);

	///�������� ������� ���������
	SS::Core::NdxSE::NdxProcessor::Containers::TIntervalPositions m_IntervalPositions;
	///��������� ��� �������� �������� ���������, � ��������� ������� ����� ���������� ��������
	TEvaledIntervalCollection m_EvaledIntervalCollection;
	///��������� ����������� ����
	vector<Containers::CWordUnion*> m_WordUnionCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}
