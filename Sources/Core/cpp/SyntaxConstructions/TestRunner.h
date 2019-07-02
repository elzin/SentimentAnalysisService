//TestRunner.h
#pragma once
#include "../ASCInterface/IInterface.h"

namespace SS
{
	namespace UnitTests
	{
		namespace SyntaxConstructions
		{
			class CTestRunner : public SS::Interface::UnitTests::ITestRunner
			{
			public:
				///�����������
				CTestRunner(){};
				///����������
				~CTestRunner(){};
				///������ ������
				void Run();
				///������������
				ULONG Release();
				///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
				HRESULT QueryInterface(REFIID pIID, void** pBase); 
			};
		}
	}
}
