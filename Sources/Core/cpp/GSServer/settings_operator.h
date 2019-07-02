#pragma once

#include ".\settings_manager.h"
#include "..\ASCInterface\ICommonServices.h"

namespace SS
{
namespace CommonServices
{

//----------------------------------------------------------------//

///�������� ��������, ��������� �������� � �������� �������� ��������
class  CSettingsOperator :
			public virtual CSettingsManager,
			public SS::Interface::Core::CommonServices::ISettingsServer
{
public:

	//-----------ISettingsServer
	//ISettingsServer implementation
	///��������� ���� � ����� ��������
	void SetWorkPath (const wchar_t* sPath);
	///������ �������� � ���� �� �����
	void FlushToDisk ();

	///�������� ��������� ����������� ���� �� �����
	unsigned int	GetBoolean	(const wchar_t* wszName){
		return (unsigned int)GetParameter<bool>(wszName, SS::Interface::Core::CommonServices::ptBoolean);
	};
	int				GetInt		(const wchar_t* wszName){return GetParameter<int>(wszName, SS::Interface::Core::CommonServices::ptInt);};
	unsigned int	GetUInt		(const wchar_t* wszName){return GetParameter<unsigned int>(wszName, SS::Interface::Core::CommonServices::ptUInt);};
	__int64			GetInt64	(const wchar_t* wszName){return GetParameter<__int64>(wszName, SS::Interface::Core::CommonServices::ptInt64);};
	double			GetDouble	(const wchar_t* wszName){return GetParameter<double>(wszName, SS::Interface::Core::CommonServices::ptDouble);};

	///���������� ��������� ����������� ���� �� �����
	void SetBoolean	(const wchar_t* wszName, bool Value){SetParameter<bool>(Value, wszName, SS::Interface::Core::CommonServices::ptBoolean);};
	void SetInt		(const wchar_t* wszName, int Value){SetParameter<int>(Value, wszName, SS::Interface::Core::CommonServices::ptInt);};
	void SetUInt	(const wchar_t* wszName, unsigned int Value){SetParameter<unsigned int>(Value, wszName, SS::Interface::Core::CommonServices::ptUInt);};
	void SetInt64	(const wchar_t* wszName, __int64 Value){SetParameter<__int64>(Value, wszName, SS::Interface::Core::CommonServices::ptInt64);};
	void SetDouble	(const wchar_t* wszName, double Value){SetParameter<double>(Value, wszName, SS::Interface::Core::CommonServices::ptDouble);};

	///�������� ��������� ���������
	void GetString	(const wchar_t* wszName, std::wstring* pwsValue){OperateParameter(true, wszName, (void*)pwsValue, SS::Interface::Core::CommonServices::ptString, false);};
	///���������� ��������� ���������
	void SetString	(const wchar_t* wszName, std::wstring* pwsValue){OperateParameter(false, wszName, (void*)pwsValue, SS::Interface::Core::CommonServices::ptString, false);};

	///�������� ������-�������� ���������
	void GetArray	(const wchar_t* wszName, SS::Interface::Core::CommonServices::EParameterType peType, void* pArray)
		{OperateParameter(true, wszName, pArray, peType, true);};
	///���������� ������-�������� ���������
	void SetArray	(const wchar_t* wszName, SS::Interface::Core::CommonServices::EParameterType peType, void* pArray)
		{OperateParameter(false, wszName, pArray, peType, true);};
	//-----------Eof-ISettingsServer

};

//----------------------------------------------------------------//

}
}