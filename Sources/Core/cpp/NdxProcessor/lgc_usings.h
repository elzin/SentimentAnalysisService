#pragma once

#include ".\logic.h"
#include ".\arg_complex.h"

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

///������ ��������� �� ���������� �����, ������������ �������� ��� ����������
class CCompositeLogic : public CLogic
{
public:
	typedef list<CLogic*> TLogicCollection;

	CCompositeLogic(void);
	virtual ~CCompositeLogic(void);

	///��������� ������
	void AddLogic(CLogic* pLogicUsing);
	///������������� ������ ����� ������������
	void Init(SS::Core::NdxSE::NdxProcessor::Extracting::CResultArgument* pResultArgument);
	
	///������� ������� ��������
	SS::Core::NdxSE::NdxProcessor::Extracting::CComplexValue* CreateComplexValue(void);

	///���������� ���� ��������� �������
	void SetIdleCalculation(void);
	///���������� ���� ��������� �������
	void UnsetIdleCalculation(void);

protected:
	///��������� �����, ������� ����� ���������� �������
	TLogicCollection m_LogicCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}