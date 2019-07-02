#pragma once

#include "../ASCInterface/IInterface.h"
#include "./BaseManagerTest.h"

namespace SS
{
namespace UnitTests
{
namespace ResourceManagers
{
class CTestRunner : public SS::Interface::UnitTests::ITestRunner
{
private:
	CBaseManagerTest* m_pBaseManagerTest;
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