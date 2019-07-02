#pragma once

#include ".\eq_calc.h"
#include ".\eq_block.h"
#include ".\subst.h"
#include ".\res.h"
#include ".\ev_factory.h"
#include ".\es_filler.h"
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

///��������� ��������� ���������� ���������� �����������
class CEvaluator : public CFactoryClient<CEvalFactory>, public CConsoleClient
{
public:
	CEvaluator(CEvalFactory* pEvalFactory);
	virtual ~CEvaluator(void);
	
	///�������������� �����������
	void Init(CESFiller* pESFiller);
	///��������� ������� �������
	bool Calculate(void);
	///���������� ������� �������
	bool CalculateNext(void);
	///�������� ��������� ����������� � �����������
	CResultsContainer* ExtractResultsContainer(void);

	///���������� ���������� ������� ������
	void View(void);
	///���������� ������ ��������� �����������
	void ViewResultsContainer(void);
	
protected:
	///������� �� ������� �������� ����������
	//CCalcEquation* m_pEquation;
	CBlockEquation* m_pEquation;
	///������������, ����������� ���������� ������� ��������
	CSubster* m_pSubster;
	///��������� �����������
	CResultsContainer* m_pResultsContainer;
	///������� �������� ���������� �����������
	CResultArgument* m_pCurrResultArgument;

};

//--------------------------------------------------------------------//

}
}
}
}
}