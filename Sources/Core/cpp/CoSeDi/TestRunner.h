#pragma once

#include "..\ASCInterface\IInterface.h"

namespace SS
{
	namespace UnitTests
	{
		namespace CoSeDi
		{
			class CTestRunner : public SS::Interface::UnitTests::ITestRunner
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
