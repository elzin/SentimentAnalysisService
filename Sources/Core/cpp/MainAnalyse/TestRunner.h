#pragma once

#ifdef _SS_UNITTESTS

namespace SS
{
namespace UnitTests
{
namespace MainAnalyse
{

	class CTestRunner :	public SS::Interface::UnitTests::ITestRunner
	{
	public:
		CTestRunner(void);
		~CTestRunner(void);
		//������ ������
		void Run();
		//������������
		ULONG Release();
		//���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
		HRESULT QueryInterface(REFIID pIID, void** pBase); 
	};
}
}
}

#endif //_SS_UNITTESTS