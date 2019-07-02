#pragma once

#include ".\memory_management.h"
#include "..\ASCInterface\services.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace MemoryManagement
{

//--------------------------------------------------------------------//

///�������� ����� - �������� ��������� ��� �������� ������������������ ��������
class CPoolsManager
{
public:
	typedef map<size_t, CPool*> TPoolsCollection;
	
	CPoolsManager(bool bUseStdHeap);
	virtual ~CPoolsManager(void);
	
	///������ �� �����������
	CPoolsManager(const CPoolsManager&){};
	///������ �� �����������
	CPoolsManager& operator==(const CPoolsManager&){return *this;};
	
	///����������� ������� ��������
	void	RegisterClass(const wchar_t* pwszObjectTypeName, size_t uiSize, unsigned int uiInitObjectsCount = 1000);
	///��������� ������
	void*	AllocObject(size_t uiSize);
	///����������� ������
	void	FreeObject(void* p);
	///������� ���� � ���������
	void	ResetPools(void);
	///���������� �� �������
	void View(void);

protected:
	///����������� ������ ��� ������������� ���������� �������
	SS::Core::CommonServices::CManagerLifeTimeForCriticalSection m_CriticalSection;
	///��������� ����� ��������
	TPoolsCollection m_PoolsCollection;
	///������� ���� ���������
	CNdxHeap m_Heap;
	///���� ������������� ����������� ����
	bool m_bUseStdHeap;
};

//--------------------------------------------------------------------//

}
}
}
}
}