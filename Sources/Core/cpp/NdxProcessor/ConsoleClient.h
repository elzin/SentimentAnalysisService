#pragma once

#include ".\console.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{

//--------------------------------------------------------------------//

///����������� ��������� ������ � ��������
class CConsoleClient
{
public:
	///������������ � ������
	virtual void ToString(wstring& wszValue, wstring wszOffset){TO_CONSOLE(L"Not overriden!");};
	///������������ � ������
	virtual void ToString(wstring& wszValue){TO_CONSOLE(L"Not overriden!");};
	///���������� ���������� ������� ������
	virtual void View(void)
	{
		wstring wszValue;
		ToString(wszValue);
		ToConsole(wszValue.c_str());
	};
};

//--------------------------------------------------------------------//

}
}
}
}