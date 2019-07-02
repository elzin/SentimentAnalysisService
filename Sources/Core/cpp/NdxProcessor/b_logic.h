#pragma once
#include ".\logic.h"
#include <math.h>


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

///������ � ������������ � ���������� ������� ������
class CBooleanLogic : public CLogic
{
public:
	CBooleanLogic(void);
	CBooleanLogic(ELogicID LogicID);
	virtual ~CBooleanLogic(void);

	///�������� �������� ������ �� �������� ���������
	SS::Core::NdxSE::NdxProcessor::Containers::CValue* CreateLogicValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, CComplexArgument* pComplexArgument);
	///�������� �������� ��������� �� �������� ������
	void ToResultValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, CResultArgument* pResultArgument);

protected:
	///��������� �������� AND
	void MakeAnd(SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppChangedValue, SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppValue);
	///��������� �������� OR
	void MakeOr(SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppChangedValue, SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppValue);
	///��������� �������������� ��������� ���
	float EvalResultWeight(float fInputWeight){return floor((fInputWeight/(m_fResultMaxWeight/100)));};

	///������������ ��� ���������� ������������ �� ������� ������
	float m_fResultMaxWeight;
};

//--------------------------------------------------------------------//

///������� ������ � ������ ��������� � ������� ������������
class CBooleanLogicWithSentencesAdjacent : public CBooleanLogic
{
public:
	CBooleanLogicWithSentencesAdjacent(int iSizeAdjacent/*, 
		SS::Core::Ndx::SSearchParameter::EAdjacentSearchIntervalType IntervalType*/);
	virtual ~CBooleanLogicWithSentencesAdjacent(void);

protected:
	///��������� �������� AND
	void MakeAnd(SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppChangedValue, SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppValue);
	
	///����� ��������� 
	int m_iSizeAdjacent;
	/////��� ���������
	//SS::Core::Ndx::SSearchParameter::EAdjacentSearchIntervalType m_IntervalType;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}