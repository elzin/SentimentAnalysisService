#pragma once
#include ".\cnt_factory.h"
#include ".\index_container_nodes_s.h"
#include ".\arg_complex.h"
#include ".\logged_index_container.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Containers
{

//--------------------------------------------------------------------//

///������� � ���������� ��������
class CWord : public CFactoryClient<CContainersFactory>
{
public:
	typedef set<unsigned int> TCommonPositions;
	typedef map<unsigned int, CCoordinateNode_4s*> TIndexPositionsCollection;
	typedef list<CPosCnt*> TIndexPositionsList;

	CWord(unsigned char ucPositionID, CContainersFactory* pContainersFactory, const wchar_t* wszWord, float fWordWeight);
	virtual ~CWord(void);

	///���������� ������������� �������
	unsigned char GetID(void){return m_ucPositionID;};
	///������ �����
	const wchar_t*  GetString(void){return m_wsWord.c_str();};
	///���������� ��� �����
	virtual float GetWeight(void){return m_fWordWeight;};

	///��������� ������ � ��������� �������
	virtual void AddIndex(unsigned int uiIndex);
	///��������� ������� � ��������� ������������
	virtual void AddArgumentPosition(SS::Core::NdxSE::NdxProcessor::Extracting::CComplexArgument* pComplexArgument, 
		CCoordinateNode_4s* pCoordinateNode);
	//������� ����� ��������� ������� ��� ��������� ���������� � �������� ��������
	virtual void MakeCommonPositions(unsigned int uiEvalSentenceID, 
		unsigned int uiLeftBound = EMPTY_VALUE, unsigned int uiRightBound = EMPTY_VALUE);
	//������� ����� ��������� ������� ��� ��������� ���������� � �������� ��������
	void MakePositions(unsigned int uiEvalSentenceID, TCommonPositions* pResultPositions,
		unsigned int uiLeftBound = EMPTY_VALUE, unsigned int uiRightBound = EMPTY_VALUE);
	///���������� ������� � ���������� ��������
	virtual void Clear(void);
	///������� ��������� �������
	virtual void ClearPositions(void);
	///���������� ��������� ������� ������� �������
	TCommonPositions* GetCurrentPositions(void){return &m_CurrentPositions;};
	///����������� �� ������ ������� �� ��������� �������
	virtual unsigned int CurrentPositionsPopFront(void);
	///����������� �� ������ ������� �� ��������� �������
	unsigned int GetNearPosition(unsigned int uiCenterPosition);

	///�������������� �������� �������� ����� �������
	//���������� ����� �� �������� ����� ������������� ������ CWord
	virtual unsigned int PrepareMakeCommonPositions(unsigned int uiEvalSentenceID);
	//���������� ��������� �������� �����
	TIndexPositionsCollection* GetIndexesCollection(void){return &m_IndexCollection;};
	///������������� ������� ����������� � ������� ���������
	void SetCurrentEvalPosition(unsigned int uiValue){m_uiCurrentEvalPosition=uiValue;};

	///���������� ��������� ������� ������� �������
	void View(void);

	///��������� ������� �������������� �������� � ������������
	///������������ ��� ���������� ���������������� ������������ ��������
	static CLoggedIndexContainer* m_pLoggedIndexContainer;

protected:
	///������� ���������� ���������� �� m_IndexPositionsCollection
	void RemoveEqualPosConataners(void);
	///��������� m_IndexPositionsCollection
	bool MakeIndexPositionsCollection(unsigned int uiEvalID);
	///��������� ��������� �����������
	unsigned int EvaluateRangeId(void);

	///������������� �������
	const unsigned char m_ucPositionID;
	///������ �����
	const wstring m_wsWord;
	///��� �����
	float m_fWordWeight;

	///��������� �������� � ���������
	TIndexPositionsCollection m_IndexCollection;
	///��������� ������� ������� �������
	TCommonPositions m_CurrentPositions;
	///��������� ������������ �������� �� ������� ����� ������������� ����� �������
	TIndexPositionsList m_IndexPositionsCollection;
	///������� ����������� � ������� ���������
	unsigned int m_uiCurrentEvalPosition;
};

//--------------------------------------------------------------------//

///������� � ������������������
class CWordInSequence : public CWord
{
public:
	CWordInSequence(unsigned char ucPositionID, CContainersFactory* pContainersFactory, const wchar_t* wszWord, float fWordWeight, unsigned char ucSequenceID, unsigned char ucPosInSequence);
	virtual ~CWordInSequence(void);

	///���������� ������������� ������������������ � ������� ������ �������
	unsigned char GetSequenceID(void){return m_ucSequenceID;};
	///���������� ������������� ������� � ������������������, � ������� ������ �������
	unsigned char GetPosInSequence(void){return m_ucPosInSequence;};
	///����������� ���� ������� ������� � ����������
	bool IsEvaluated(void){return m_bEvaluated;};
	///������������� ���� ������� ������� � ����������
	void SetEvaluated(bool bValue){m_bEvaluated=bValue;};
	///	������������� ���� ��������� ����������������
	void SetObligatory(bool const bOblitatory){m_Obligatory = bOblitatory;};
	///	���������� ���� ��������� ����������������
	bool GetObligatory(void){return m_Obligatory;};

	///���������� ���������� �� �������
	void View(void);

protected:
	///������������� ������������������, � ������� ������ �������
	const unsigned char m_ucSequenceID;
	///������������� ������� � ������������������, � ������� ������ �������
	const unsigned char m_ucPosInSequence;
	///���� ������� ������� � ����������
	bool m_bEvaluated;
	///���� ��������� ����������������
	bool m_Obligatory;
};


//--------------------------------------------------------------------//

///��������� ����� � ������������ ��������� �������������� �������������
class CWordWithStatistic : public CWordInSequence
{
public:
	CWordWithStatistic(unsigned char ucPositionID, CContainersFactory* pContainersFactory, const wchar_t* wszWord, float fWordWeight, bool bAnswerWord);

	///��������� ������
	void AddIndex(unsigned int uiIndex);

	///���������� ��������� ��� ����� � ��������� ���������
	float GetAbsFrequencyWeight(void){return m_fAbsFrequencyWeight;};
	///���������� ��� �����
	float GetWeight(void);
	///���������� ��� �����
	void ResetWeight(void){m_fTotalWordWeight=EmptyWeight;};
	///��������� ��� ������� � ������ ���������
	void EvaluateWeight(unsigned int uiEvalID);
	///���������� ���� ����� ������
	bool IsAnswerWord(void){return m_bAnswerWord;};

	///����������� ����������� �������� ���������
	static unsigned int m_uiCurrentDocumentNormKoef;
	///���������� ���������� � ����
	static unsigned int m_uiTotalDocumentsNumber;
	///������� �������������� �������������
	static unsigned int m_uiCurrentEvalID;

	///������ ��� �����
	const static int EmptyWeight=-1;

protected:
	///��������� IDF �������
	float CalculateIndexIDF(unsigned int uiIndex, unsigned int uiTotalDocumentsNumber);

	///����� ��� �����
	float m_fTotalWordWeight;
	///��������� ��� ����� � ��������� ���������
	float m_fAbsFrequencyWeight;
	///���� ����� ������
	bool m_bAnswerWord;

	///����������� �������� ���������������� ���� ����
	const float m_fWordsLingvoWeightKoef;
};

//--------------------------------------------------------------------//

}
}
}
}
}
