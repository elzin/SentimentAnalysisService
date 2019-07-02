#pragma once

#include ".\r_eval.h"

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

///����������� ���������� � ������ ���� ������
class CProximityEvaluator_Answer : public CRelevanceEvaluator
{
public:
	CProximityEvaluator_Answer(unsigned int uiEvaluatorID, Containers::CContainersFactory* pContainersFactory);
	virtual ~CProximityEvaluator_Answer(void);

	///��������� �  ���������� ������� �������� ��������� �� ��������������
	Containers::CWordInSequence* AddPosition(unsigned char ucPositionID, unsigned char ucSequenceID, unsigned char ucPosInSequence, SS::Interface::Core::NdxSE::IWord* pWord);
	///��������� ������� � ��������� ������������
	void AddArgumentPosition(CComplexArgument* pComplexArgument, Containers::CCoordinateNode_4s* pCoordinateNode);

	///��������� ��� �� �������� � ������� ������������ �������� � �����������
	void Evaluate(unsigned int uiEvalID);

protected:
	typedef vector<Containers::CWordWithStatistic*> TWordsCollection;
	typedef map<unsigned int, Containers::CWordWithStatistic*> TSortedWordsCollection;

	///���������� ���� ����
	void ResetWordsWeights(void);
	///��������� ��������� � ������ ���� ������
	bool EvaluateWithAnswers(unsigned int uiEvalID);
	///������� ����� ������� � �����������
	bool PrepareAnswersWords(unsigned int uiEvalID);
	///������� ����� � �����������
	bool PrepareCommonWords(unsigned int uiEvalID);
	///��������� ������� ���� ������, ���� ��������
	bool EvaluateNextPositions(unsigned int uiEvalID, unsigned int uiLimitBound);
	///���������� ����������� ������� ����������
	unsigned int GetResultCenterPosition(void);
	///���������� ���������� ������ ���� �������� �������
	unsigned int GetRarityWordsCount(void);

	///������� �������� ����������
	Containers::CInterval* CreateInterval(unsigned int uiHeadPos, unsigned int uiTailPos);
	///���������� ��� ���������
	unsigned int GetIntervalWeight(Containers::CInterval* pInterval);

	///������� ���� �������
	TWordsCollection m_AnswerWords;
	///��������� ���� �������� ����������
	TSortedWordsCollection m_CurrentResultWords;
	///��������� ���� �� �����
	TSortedWordsCollection m_WordsByRangeID;
	
	///���������� ������ ���� �������� �������
	unsigned int m_uiRarityWordsCount;
	///���������� ������ ���� � ������� ���������
	unsigned int m_uiCurrDocumentRarityWordsCount;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}
