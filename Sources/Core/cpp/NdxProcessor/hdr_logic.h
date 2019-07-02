#pragma once

#include ".\logic.h"
#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASDInterface\INdxQuery.h"
#include ".\cnt_factory.h"
#include ".\index_container_nodes_s.h"
#include ".\arg_res_hdr.h"

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

///������ ����������, �������� �� ��������� ������
///���������� ����� � �������������� ���������� ��������� �������
class CHeaderLogic : public CLogic 
{
public:
	CHeaderLogic(void);
	virtual ~CHeaderLogic(void);

	///������������� ������ ��� ������������� ������������
	void SetQuery(SS::Interface::Core::NdxSE::IParametrizedQuery* pPrmQueryResult);

	///������������� ������ ����� ������������
	void Init(SS::Core::NdxSE::NdxProcessor::Extracting::CResultArgument* pResultArgument);
	///�������� �������� ������ �� �������� ���������
	SS::Core::NdxSE::NdxProcessor::Containers::CValue* CreateLogicValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, 
		SS::Core::NdxSE::NdxProcessor::Extracting::CComplexArgument* pComplexArgument);
	///�������� �������� ��������� �� �������� ������
	void ToResultValue(SS::Core::NdxSE::NdxProcessor::Containers::CValue* pValue, 
		SS::Core::NdxSE::NdxProcessor::Extracting::CResultArgument* pResultArgument);

	///������������ ���������� ������ � ���������
	static const unsigned int MaxBlockCount=10;

protected:
	typedef vector<Containers::CCoordinateNode_4s*> TCoordinateNodeCollection;
	typedef map<unsigned int, TCoordinateNodeCollection*> TIndexCollection;

	///��������� �������� AND
	void MakeAnd(SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppChangedValue, 
		SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppValue){};
	///��������� �������� OR
	void MakeOr(SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppChangedValue, 
		SS::Core::NdxSE::NdxProcessor::Containers::CValue** ppValue){};
	
	///��������� ��������� ����������
	void FillResult(unsigned int uiEvalID, 
		SS::Core::NdxSE::NdxProcessor::Extracting::CResultArgument_HID* pResultArgument_HID);

	///��������� �������� � ������
	TIndexCollection m_IndexCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}
