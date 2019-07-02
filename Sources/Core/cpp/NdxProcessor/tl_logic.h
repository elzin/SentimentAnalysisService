#pragma once
#include ".\f_logic.h"
#include ".\index_stat_storage.h"
#include ".\iep_storage.h"
//#include "../assinterface/tndxsearchstructs.h"
//#include ".\docnormtable.h"

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

///������ ������ ������� ���� �������� �� �������
class CTextLevelLogic : public CFuzzyLogic
{
public:
	CTextLevelLogic(unsigned int uiAllTextsNumber, 
		SS::Core::NdxSE::NdxProcessor::Storages::CIndexStatisticStorage* pIndexStorage);

	///�������� �������� ������ �� �������� ���������
	SS::Core::NdxSE::NdxProcessor::Containers::CValue* CreateLogicValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, CComplexArgument* pComplexArgument);
	///�������� �������� ��������� �� �������� ������
	void ToResultValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, CResultArgument* pResultArgument);

protected:
	///��������� �������� ������������� ������� � ������
	void CalculateInversDocumentFrequency(CComplexArgument* pComplexArgument);
	///��������� ������� ����� ������� ������� ���������� �� ������� ����������
	unsigned int CalculateTextsBaseNumberFromResultHistory(CResultArgument* pResultArgument);
	///��������� �������� ������� �������������  ����� � ��������� �������� ���������� ���������� � ������� ���������� ������ ���� ������� �� ����� ���������� ���������� � ���������
	float ComputeInversDocumentFrequency(unsigned int uiDocumentsNumber, unsigned int uiDocumentFrequency);


	///���������� ������� � ����
	const unsigned int m_uiAllTextsNumber;
	///�������� ������������� ������� � ������
	float m_fInversDocumentFrequency;

	///���������� �� �������������� ���������
	SS::Core::NdxSE::NdxProcessor::Storages::CIndexStatisticStorage* m_pIndexStorage;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}