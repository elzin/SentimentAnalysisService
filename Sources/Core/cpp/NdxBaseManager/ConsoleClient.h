#pragma once

#include ".\console.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxBaseManager
{

//--------------------------------------------------------------------//

///����������� ��������� ������ � ��������
class CConsoleClient
{
public:
	///������������ � ������
	virtual void ToString(string& szValue, string szOffset){TO_CONSOLE("Not overriden!");};
	///������������ � ������
	virtual void ToString(string& szValue){TO_CONSOLE("Not overriden!");};
	///���������� ���������� ������� ������
	virtual void View(void){TO_CONSOLE("Not overriden!");};
};

//--------------------------------------------------------------------//

}
}
}
}