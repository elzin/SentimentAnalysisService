#pragma once
#include "..\ASCInterface\iinterface.h"
#include "./tst_ParametrizedQuery.h"

namespace SS
{
namespace UnitTests
{
namespace NdxSE
{
namespace NdxQuery
{

//--------------------------------------------------------------------//

///	��������� ��������� ������� ���� ������
class CTestRunner : public SS::Interface::UnitTests::ITestRunner
{
public:
	///	�����������
	CTestRunner(void);

	///	����������
	virtual ~CTestRunner(void);

	///	������ ������
	virtual void Run();

	///	���������� � ���������� � �������� REFIID. 
	/**	pBase ����� NULL, ���� ������ ��������� �� ��������������*/
	virtual HRESULT QueryInterface(REFIID refIID, void** pBase);

	///	������������
	virtual ULONG Release();
};

//--------------------------------------------------------------------//

}
}
}
}

