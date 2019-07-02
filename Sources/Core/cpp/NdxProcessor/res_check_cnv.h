#pragma once
#include ".\res_check.h"
#include ".\sr_filler.h"

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

///��������� ����������� � ������������ �������� ��������������� ����������� 
//� �������� � � ��������� � ������������ �� ���������� �����������
class CResultsCheckerWithConvertion : public CResultsChecker
{
public:
	CResultsCheckerWithConvertion(unsigned int uiValidResultsDepth = 0, 
		unsigned int uiFinalResultsMaxNumber = 0,
		CSearchResultFiller* pSearchResultFiller = NULL);
	virtual ~CResultsCheckerWithConvertion(void);

	///������������� ����������
	void Init(void){m_uiFinalResultsCurrentNumber=0;};
	///��������� ��������� �� ������������
	bool CheckResult(CResultArgument* pArgument, CArgument** ppCheckedArgument);
	///���������� ���������� ������� ������
	void View(void);

protected:
	///��������� ����������� � ��������
	CSearchResultFiller* m_pSearchResultFiller;
	///������� ���������� ����������� ������������� �����������
	unsigned int m_uiFinalResultsCurrentNumber;
	///������������ ����� ����������� ������������� �����������
	const unsigned int m_uiFinalResultsMaxNumber;
};
//--------------------------------------------------------------------//

///��������� ����������� � ������������ �������� ��������������� ����������� 
//� �������� � ��������� � ������������ �� ���������� �����������,
//������������ ��� ����������� ����������
class CResultsCheckerWithIntervalConvertion : public CResultsCheckerWithConvertion
{
public:
	CResultsCheckerWithIntervalConvertion(unsigned int uiValidResultsDepth = 0, 
		unsigned int uiFinalResultsMaxNumber = 0,
		CSearchResultFiller* pSearchResultFiller = NULL);

	///��������� ��������� �� ������������
	bool CheckResult(CResultArgument* pArgument, CArgument** ppCheckedArgument);
};

//--------------------------------------------------------------------//

///��������� ����������� � ������������ �������� ��������������� ����������� 
//� �������� � ��������� � ������������ �� ���������� �����������,
//������������ ��� ����������� ����������
class CResultsCheckerWithHIDConvertion: public CResultsCheckerWithConvertion
{
public:
	CResultsCheckerWithHIDConvertion(unsigned int uiValidResultsDepth = 0, 
		unsigned int uiFinalResultsMaxNumber = 0,
		CSearchResultFiller* pSearchResultFiller = NULL);

	///��������� ��������� �� ������������
	bool CheckResult(CResultArgument* pArgument, CArgument** ppCheckedArgument);
};

//--------------------------------------------------------------------//

}
}
}
}
}