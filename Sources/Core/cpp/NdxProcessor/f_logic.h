#pragma once
#include ".\logic.h"


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

///������ � ������������ � ���������� �������� ��������
class CFuzzyLogic : public CLogic
{
public:
	CFuzzyLogic(void);
	CFuzzyLogic(ELogicID LogicID);
	virtual ~CFuzzyLogic(void);

	///�������� �������� ������ �� �������� ���������
	SS::Core::NdxSE::NdxProcessor::Containers::CValue* CreateLogicValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, CComplexArgument* pComplexArgument);
	///�������� �������� ��������� �� �������� ������
	void ToResultValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, CResultArgument* pResultArgument);

protected:
	///��������� �������� AND
	void MakeAnd(SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppChangedValue, SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppValue);
	///��������� �������� OR
	void MakeOr(SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppChangedValue, SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppValue);

	///�������� ������� 
	const float m_fBeta;
	///����� ����������� ����
	const float m_fThreshold;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}