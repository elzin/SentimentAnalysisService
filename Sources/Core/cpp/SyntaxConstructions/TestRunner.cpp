//TestRunner.cpp
#include "StdAfx.h"
#include "./testrunner.h"
#include "SyntaxConstructionsTest.h"
#include "./FillSQL.h"

namespace SS
{
	namespace UnitTests
	{
		namespace SyntaxConstructions
		{

			//������ ������
			void CTestRunner::Run()
			{
				CoInitialize(NULL);				
				#ifdef _SS_UNITTESTS
				{
					//������ � �������
					//CSyntaxConstructionsTest oSyntaxConstructionsTest(GetLoadManager());
					//oSyntaxConstructionsTest.TestToBinary();
					CFillSQL oFillSQL;
					oFillSQL.SetLoadManager(GetLoadManager());
					oFillSQL.Fill();
					//��������
					std::cout << "press key";
					char ch;
					ch = getchar();
				}
				#endif
				CoUninitialize();
			}

			//���������� ������
			ULONG CTestRunner::Release()
			{
				delete this;
				return 0;
			}

			//�������� ���������
			HRESULT CTestRunner::QueryInterface(REFIID pIID, void** pBase)
			{
				if(pIID == IID_TestRunner)
				{
					*pBase = (SS::Interface::UnitTests::ITestRunner*)this;
				}
				else if (pIID == IID_Base)
				{
					*pBase = (SS::Interface::IBase*)( this );
				}
				else
				{
					*pBase = NULL;
				}
				return S_OK;
			}

		}
	}
}