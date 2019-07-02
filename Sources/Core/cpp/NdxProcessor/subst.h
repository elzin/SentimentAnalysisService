#pragma once
#include ".\arg.h"
#include ".\res.h"
#include ".\consoleclient.h"

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

///������������ - ����������� ��������� �������� ��������, ������ ���������
/**�������� ��������, ������� ���� ��������� ����������, ������� ����� ������������� �������� 
��� ������� �������*/
class CSubster : public CConsoleClient
{
public:
	CSubster(void);
	virtual ~CSubster(void);
	
	///����������� �������� ����������
	void IdleSubst(void);
	///�������� ������� ����������� �������� ����������
	void StartSubsting(void);
	///����������� �������� ����������
	bool SubstValues(void);
	///������������ ���������
	void EvaluateResult(CArgument* pResult);
	///���������� ��������� ���������� � ��������������� �� �������� ��������
	TArgValCollection* GetArgValCollection(void){return &m_ArgValCollection;};
	///���������� ����������
	void Reset(void);

	///���������� ���������� ������� ������
	void View(void);
	///���������� ���������� ��������� ��������-��������
	void ViewArgValCollection(void);

protected:
	///���� ����������� ����������� 
	CResultsStack m_ResultsStack;
	///��������� ���������� � ��������������� �� �������� ��������
	TArgValCollection m_ArgValCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}