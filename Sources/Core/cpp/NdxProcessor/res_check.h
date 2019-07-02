#pragma once
#include ".\arg_res.h"

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

//--------------------------------------------------------------------//

///��������� ����������� 
class CResultsChecker : public CConsoleClient
{
public:
	CResultsChecker(unsigned int uiValidResultsDepth)
		:m_uiValidResultsDepth(uiValidResultsDepth){};
	virtual ~CResultsChecker(void){};
	
	///������������� ����������
	virtual void Init(void){};
	///��������� ��������� �� ������������
	virtual bool CheckResult(CResultArgument* pArgument, CArgument** ppCheckedArgument);
	///���������� ������� �������� �����������
	unsigned int GetValidResultsDepth(void){return m_uiValidResultsDepth;}; 
	///���������� ���������� ������� ������
	void View(void);

protected:
	///������� �������� �����������
	const unsigned int m_uiValidResultsDepth; 
};

//--------------------------------------------------------------------//

}
}
}
}
}