#pragma once

#ifdef _SS_UNITTESTS

#include "../ASCInterface/iinterface.h"

namespace SS
{
namespace UnitTests
{
namespace NdxSE
{
namespace NdxProcessor
{

//--------------------------------------------------------------------//

//��������������� ������� ��� ������
class CUnitTestsUsings
{
public:
	CUnitTestsUsings(void):m_hLoadManager(NULL), m_pLoadManager(NULL){};
	virtual ~CUnitTestsUsings(void){DeleteLoadManager();};

protected:
	///���������� �������� ��������
	virtual SS::Interface::Core::ResourceManagers::ILoadManager* GetLoadManager(void){if(!m_pLoadManager) CreateLoadManager(); return m_pLoadManager;};
	///���������� ���� � ������� ���������� ���� ������
	const wchar_t* GetUTWorkingPath(void);

private:
	///������� �������� ��������
	bool CreateLoadManager(void);
	///������� �������� ��������
	void DeleteLoadManager(void);

	///����� ������ ��������
	HMODULE m_hLoadManager;
	///��������� � ��������� ��������
	SS::Interface::Core::ResourceManagers::ILoadManager* m_pLoadManager;
	///���� � ������� ���������� ���� ������
	wstring wszUTWorkingPath;
};

//--------------------------------------------------------------------//

}
}
}
}

#endif //_SS_UNITTESTS
