#pragma once

#include "..\ASCInterface\ICommonServices.h"
#include ".\setting_value.h"

namespace SS
{
namespace CommonServices
{

//----------------------------------------------------------------//

#pragma pack(push,1)  // Fix packing size 
///��� ���������
struct SSettingType
{
	///��� �������� ���������
	SS::Interface::Core::CommonServices::EParameterType m_eSettingType;
	///���� ��������� �������
	bool m_bIsArray;
};
#pragma pack(pop)

//----------------------------------------------------------------//

#pragma pack(push,1)  // Fix packing size 
///�������� ���������
struct SSettingAttributes
{
	SSettingAttributes(void):m_bPublic(true), m_bReadOnly(false)
	{
		m_SettingType.m_eSettingType = SS::Interface::Core::CommonServices::EParameterType::ptInt;
		m_SettingType.m_bIsArray = false;
	};
	///��� ���������
	SSettingType m_SettingType;
	///���� ������ ������� � ���������
	bool m_bPublic;
	///���� ������� �� ������ ���������
	bool m_bReadOnly;
};
#pragma pack(pop)

//----------------------------------------------------------------//

///������� ���������
class CBasisSetting
{
public:
	CBasisSetting(const wchar_t* wszSettingName, SSettingType SettingType);
	virtual ~CBasisSetting() {};

	///���������� �������� ���������
	const wchar_t* GetSettingName(void){return m_SettingName.GetValue()->c_str();};
	///���������� ��� ���������
	SSettingType GetSettingType(void){return m_SettingAttributes.m_SettingType;};
	///���������� ���� ������ ������� � ���������
	bool IsPublic(void){return m_SettingAttributes.m_bPublic;};
	///������������� ���� ������ ������� � ���������
	void SetPublic(bool bValue){m_SettingAttributes.m_bPublic=bValue;};
	///���������� ���� ������� �� ������ ���������
	bool IsReadOnly(void){return m_SettingAttributes.m_bReadOnly;};
	///���������� ���� ������� �� ������ ���������
	void SetReadOnly(bool bValue){m_SettingAttributes.m_bReadOnly=bValue;};

	///���������� �������� ���������
	virtual bool GetSettingValue(void* pOutValue, SS::Interface::Core::CommonServices::EParameterType eSettingType, bool bIsArray) = 0;
	///������������� �������� ���������
	virtual bool SetSettingValue(void* pInValue, SS::Interface::Core::CommonServices::EParameterType eSettingType, bool bIsArray) = 0;

	///��������� ��������� � �������� ���
	virtual void ToBinary(std::vector<unsigned char>* pBuffer) = 0;
	///��������� ��������� �� ������
	virtual void FromBinary(unsigned char* pucBuffer, unsigned int uiBufferSize, unsigned int* puiReadedSize) = 0;
	
	///�������� �������� ���������
	virtual void CopyValue(CBasisSetting* pSetting) = 0;

protected:
	///��������� ���������
	SSettingAttributes m_SettingAttributes;
	///�������� ���������
	CStringValue m_SettingName;
};

//----------------------------------------------------------------//

}
}