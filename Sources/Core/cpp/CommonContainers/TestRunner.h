#pragma once

#ifdef _SS_UNITTESTS

#include "../ASCInterface/IInterface.h"
#include "./UnitTests/ContainersTest.h"

namespace SS
{
	namespace UnitTests
	{
		namespace CommonContainers
		{
			class CTestRunner : public SS::Interface::UnitTests::ITestRunner
			{
			private:
				CContainersTest* m_pContainersTest;
			public:
				//������������
				CTestRunner();
				~CTestRunner();
				//������ ������� �������
				virtual void Run();					//������ ������
				virtual ULONG Release();			//������������
				virtual HRESULT QueryInterface( REFIID pIID, void** pBase );	//���������� � ���������� � �������� REFIID. 
																				//pBase ����� NULL, ���� ������ ��������� �� ��������������
			};
		}
	}
}

#endif //_SS_UNITTESTS