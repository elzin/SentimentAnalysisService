#include "StdAfx.h"
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

//������� ���������� �������� �����, � ������������ 
//������ ����������� ������ �������� �������� 
//false - ��� ������ ����, true - ��� ������� ����������� new-delete
CPoolsManager g_PoolsManager(false/*true*/);

//--------------------------------------------------------------------//

}
}
}
}
}