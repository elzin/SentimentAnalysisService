#pragma once

#include ".\arg_res.h"
#include ".\int_containers.h"

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

class CResultArgumentWithIntervals : public CResultArgument
{
public:
	typedef vector<SS::Core::NdxSE::NdxProcessor::Containers::TIntervalCollection*> TResultIntervalCollection;

	CResultArgumentWithIntervals(unsigned int uiArgumentID = SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE, float fKoeff = 1.0);
	virtual ~CResultArgumentWithIntervals(void);
	
	///���������� ��������� ���������� �����������
	TResultIntervalCollection* GetResultIntervalCollection(void){return &m_ResultIntervalCollection;};
	
protected:
	///��������� ���������� �����������, ��������� ��������� ������ ��� �������� �����������
	TResultIntervalCollection m_ResultIntervalCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}