#pragma once

#ifdef _SS_UNITTESTS

#include "../ASCInterface/IInterface.h"

namespace SS
{
	namespace UnitTests
	{
		namespace Syntax
		{
			class CTestRunner : public SS::Interface::UnitTests::ITestRunner
			{
			public:
				//������������
				CTestRunner();
				~CTestRunner();
			
				//������ ������
				virtual void Run();
				//������������
				virtual ULONG Release();
				//���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
				virtual HRESULT QueryInterface( REFIID pIID, void** pBase ); 

			};
		}
	}
}

#endif