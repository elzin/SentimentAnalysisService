#pragma once

#include ".\basis_setting.h"

namespace SS
{
namespace CommonServices
{

///������� ��������
class CSettingFactory
{
public:
	///������� ��������� ��������� ����
	CBasisSetting* CreateSetting(SSettingType SettingType);
	///������� ��������� ��������� ����
	CBasisSetting* CreateSetting(const wchar_t* wszSettingName, SSettingType SettingType);
};

}
}