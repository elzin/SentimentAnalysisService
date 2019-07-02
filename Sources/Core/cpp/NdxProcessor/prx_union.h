#pragma once
#include ".\prx_pos_containers.h"

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

///����������� ����. �������� ��������� ���� 
///�� � ��� ����� ������ ��������������� ����������
///�������������� ����� ������ ��������� ����������� ������ ���� � �����
class CWordUnion : public CWordInSequence
{
public:
	CWordUnion(unsigned char ucPositionID, CContainersFactory* pContainersFactory, unsigned char ucSequenceID, unsigned char ucPosInSequence);
	virtual ~CWordUnion(void);

	///��������� ����� � �����������
	void AddWord(CWordInSequence* pWord);
	///��������� ������� � ��������� ������������
	void AddArgumentPosition(SS::Core::NdxSE::NdxProcessor::Extracting::CComplexArgument* pComplexArgument, 
		CCoordinateNode_4s* pCoordinateNode);
	//������� ����� ��������� ������� ��� ��������� ���������� � �������� ��������
	void MakeCommonPositions(unsigned int uiEvalSentenceID, 
		unsigned int uiLeftBound = EMPTY_VALUE, unsigned int uiRightBound = EMPTY_VALUE);
	///���������� ������� � ���������� ��������
	void Clear(void);
	///������� ��������� �������
	void ClearPositions(void);
	//���������� ����� �� �������� ����� ������������� ������ CWord
	unsigned int PrepareMakeCommonPositions(unsigned int uiEvalSentenceID);

	///���������� ��� �����������
	float GetUnionWeight(unsigned int* puiHeadPos, unsigned int* puiTailPos);

	///���������� ��� �����������
	unsigned int GetWordsCount(void){return (unsigned int)(m_GrandWordCollection.size()+m_SimpleWordCollection.size());};

protected:
	typedef std::list<CWordInSequence*> TWordCollection;

	///��������� ������ � ��������� �������
	void AddIndex(unsigned int uiIndex){};

	///��������� ���� �����������, ������� ����������� ������ �������������� � �����������
	TWordCollection m_GrandWordCollection;
	///��������� ���� �����������, ������� ����� �� �������������� � �����������
	TWordCollection m_SimpleWordCollection;

	///���������� ����� "������" ���� � �����������
	const unsigned int m_uiDirtyWordsCount;
	///����������� ��������� ����� �� ������ ���� ���� �����������
	const unsigned int m_uiEvalLimitWeightPart;
	///����������� ���� �� ��������
	const unsigned int m_uiDistanceWeightKoef;
	///����������� ������ ���� ���� ����������� 
	const unsigned int m_uiWordsWeightKoef;
	///����������� ������ ���� ����������
	const unsigned int m_uiUnionWeightKoef;
	///����������� ������ ���� ����������
	const unsigned int m_uiGrandWordWeightLimit;
};

//--------------------------------------------------------------------//

}
}
}
}
}


