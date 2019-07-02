#pragma once

#include "..\ASCInterface\iinterface.h"

namespace SS
{
namespace UnitTests
{
namespace NdxSE
{
namespace NdxBaseManager
{

//--------------------------------------------------------------------//

///��������� ��������� ������� ���� ������
class CTestRunner : public SS::Interface::UnitTests::ITestRunner
{
public:
	CTestRunner(void);
	virtual ~CTestRunner(void);

	///������ ������
	void Run();
	///���������� � ���������� � �������� REFIID. 
	/**pBase ����� NULL, ���� ������ ��������� �� ��������������*/
	HRESULT QueryInterface(REFIID refIID, void** pBase);
	///������������
	ULONG Release();
};

//--------------------------------------------------------------------//

}
}
}
}

