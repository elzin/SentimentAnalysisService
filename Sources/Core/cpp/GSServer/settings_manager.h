#pragma once

#include "..\ASCInterface\defines.h"
#include "..\ASCInterface\IInterface.h"
#include ".\setting_factory.h"
#include <map>

namespace SS
{
namespace CommonServices
{

//----------------------------------------------------------------//

///�������� ���������� �����������
class CSettingsManager 
{
public:
	typedef std::map<std::wstring, CBasisSetting*> TSettingsCollection;

	CSettingsManager(void);
	virtual ~CSettingsManager(void);

	///���������� ��� ��������� 
	void ResetSettings(void);

protected:
	///�������� � ����������
	void OperateParameter(bool bGetOrSet, const wchar_t* wszName, void* pValue, SS::Interface::Core::CommonServices::EParameterType peType, bool bIsArray);
	///���������� �������� ���������
	template <class T> T GetParameter(const wchar_t* wszName, SS::Interface::Core::CommonServices::EParameterType peType)
	{
		T tValue;
		OperateParameter(true, wszName, (void*)&tValue, peType, false);
		return tValue;
	};
	///������������� �������� ���������
	template <class T> void SetParameter(T tValue, const wchar_t* wszName, SS::Interface::Core::CommonServices::EParameterType peType)
	{
		OperateParameter(false, wszName, (void*)&tValue, peType, false);
	};
	

	///��������� ��������� �� �����
	void LoadSettings(void);
	///��������� ��������� � ����
	void SaveSettings(void);
	///������� ��������� 
	void ClearSettings(void);
	///���������� ��������� �� �����
	CBasisSetting* GetSetting(const wchar_t* wszSettingName);
	///��������� ���������
	bool AddSetting(CBasisSetting* pSetting);
	///����� ����� � ����
	bool WriteToFile(std::vector<unsigned char>* pSettingsBuffer);
	///������ ����� �� ����
	bool ReadFromFile(std::vector<unsigned char>* pSettingsBuffer);
	///��������� ���� � ����� ��������
	void MakeSettingFilePath(std::wstring* pwsFilePath);
	///��������� ������������ ����������� ��������
	bool CheckUpToDate(void);
	///�������� ����� ����
	void EncodeDecodeBuffer(std::vector<unsigned char>* pSettingsBuffer);
	///���������� ���������
	virtual SS::Interface::Core::ResourceManagers::ILoadManager* GetLoader(void) = 0;

	///��������� ��������
	TSettingsCollection m_SettingsCollection;
	///������� ��������
	CSettingFactory m_SettingFactory;
	///���� � ����� ��������
	std::wstring m_wsSettingsFilePath;
	///����� ���������� ��������� ����� ��������
	FILETIME m_LastFileTime;
	///���� ��������
	bool m_bSettingsLoaded;
};

//----------------------------------------------------------------//

}
}