#pragma once
#include ".\global_pool.h"

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

///������ ���� ��������
class CPoolClient
{
public:
	///���������� ��������� ������ ��� ������� ������, ������ ���������� �����
	void* operator new(size_t size)
	{
		return g_PoolsManager.AllocObject(size);
	}

	///���������� ������������ ������ ��� ������� ������, ������ ������������� �����
	void operator delete(void* p, size_t size)
	{
		return g_PoolsManager.FreeObject(p);
	}
};

//--------------------------------------------------------------------//

}
}
}
}
}