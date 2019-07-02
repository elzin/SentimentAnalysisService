#pragma once
#include ".\factory_client.h"
#include ".\cnt_factory.h"
#include ".\lgc_usings.h"

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

class CCalcEquation;
class CBlockEquation;
class CSubster;
class CResultsContainer;
class CResultEquation;
class CResultArgument;
class CResultsChecker;
class CEvaluator;

//--------------------------------------------------------------------//

///������� ��� �������� �������� ��� ����������
class CEvalFactory : public CFactoryClient<SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory>
{
public:
	CEvalFactory(SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory* pContainersFactory);
	virtual ~CEvalFactory(void);

	///������� ��������� ������
	virtual Logics::CCompositeLogic* CreateEquationLogic(void);
	///������� �������������� �������
	virtual CBlockEquation* CreateCalcEquation(void);
	///������� ������� �����������
	virtual CResultEquation* CreateResultEquation(void);
	///������� ��������� �����������
	virtual CResultsChecker* CreateResultsChecker(unsigned int uiValidResultsDepth);
	///������� ������������
	virtual CSubster* CreateSubster(void);
	///������� ��������� �����������
	virtual CResultsContainer* CreateResultsContainer(void);
	///������� �����������
	virtual CEvaluator* CreateEvaluator(void);
	///������� �������� ������� �����������
	virtual CResultArgument* CreateResultArgument(unsigned int uiArgumentID, float fArgumentWeight, unsigned int uiArgumentDepth);
};

//--------------------------------------------------------------------//

}
}
}
}
}