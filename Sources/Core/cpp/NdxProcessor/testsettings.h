#pragma once

namespace tsett
{
///	������ ���-����� � ������� ��������� ��� ���������
static const wchar_t*	wszSettings			= L"SETTINGS";
///	���������� ��������
static const wchar_t*	wszInvalidValue		= L"__INVALID_VALUE__";
///	������ ������
static const wchar_t*	wszEmptyString		= L"";
///	����
static const wchar_t*	wszSlash			= L"\\";
///	ini-file extension 
static const wchar_t*	wszIniExt			= L".ini";

static const wchar_t*	wcszKey_PathWork = L"PATH_WORK";
static const wchar_t*	wcszKey_PathDatabase = L"PATH_DATABASE";
static const wchar_t*	wcszKey_NameInd = L"NAME_IND";
static const wchar_t*	wcszKey_TxtQueries = L"QUERIES_FILE_NAME";

///	����� ��� ������ � �����������
///	������ � ������ � ���-���� ���������� ������ � Load � Save
class CSettings
{
public:
	///	ctr
	CSettings()
	{
		std::wstring	sCompName = GetCompName();
		std::wstring	sExeDir = GetExeDir();
		//	�������� ����� �����
		if (sCompName.length() == 0) return;
		//	�������� ���������� ��� ����� EXE
		if (sExeDir.length() == 0) return;
		//	���������� ��� ���-�����
		m_sFullIniFileName = 
			sExeDir+
			std::wstring(wszSlash)+
			sCompName+
			std::wstring(wszIniExt);
	}

	///	dtr
	~CSettings(void){}

	///	\param[in]	_Dest		������ ���� ��������� ���������
	///	\param[in]	_KeySource	�� ������ ����� ��������� ������
	///	\return	���������� ������. � ������ �������� _dest = ""
	bool	SettingRead(std::wstring&	_Dest, const wchar_t*  _KeySource)
	{
		//	�������� �������
		_Dest.assign(wszEmptyString);
		//	�������� ������������� ����� ���-�����
		if (m_sFullIniFileName.length() == 0) return false;

		DWORD dwBytesWritten = ::GetPrivateProfileStringW(
			wszSettings,
			_KeySource,
			wszInvalidValue,
			m_wcBuffer,
			m_dwBufferSize,
			m_sFullIniFileName.c_str());

		if ((dwBytesWritten == (m_dwBufferSize - 1)) || (dwBytesWritten == (m_dwBufferSize - 2)))
		{
			_Dest.assign(wszEmptyString);
			return false;
		}

		_Dest.assign(m_wcBuffer, dwBytesWritten);
		return true;
	}

	///	����������-�������� ���-����� �� ��������� ����.
	///	\param[in]	_KeyDest	���� � ���-����� ���� ���������� ������
	///	\param[in]	_Source		�� ����� ������ ��������� ������
	///	\return	����������.
	bool	SettingWrite(const wchar_t*  _KeyDest, std::wstring const&	_Source)
	{
		//	�������� ������������� ����� ���-�����
		if (m_sFullIniFileName.length() == 0) return false;

		return (FALSE != ::WritePrivateProfileStringW(
			wszSettings,
			_KeyDest,
			_Source.c_str(),
			m_sFullIniFileName.c_str()));
	}

	///	��������� ���������� ��� ����� EXE-����, ��� �����
	///	\return	���������� ��� ����� ��� ����� EXE-����
	static std::wstring	GetExeDir()
	{
		wchar_t			buf[MAX_PATH];
		unsigned int	name_len = ::GetModuleFileNameW(NULL, buf, MAX_PATH);
		if (name_len == 0) return std::wstring(wszEmptyString);

		//	���� ����, �������� ��� �����
		for (unsigned int i = name_len; i > 0; --i)
		{
			name_len = i-1;
			if (buf[name_len] == L'\\') break;
		}

		if(name_len == 0) return std::wstring(wszEmptyString);
		return std::wstring(buf, name_len);
	}

	///	��������� ����� ����������
	///	\return	��������� ::GetComputerName(), ��� ����������
	static std::wstring	GetCompName()
	{
		wchar_t	buf[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD size = MAX_COMPUTERNAME_LENGTH+1;
		BOOL	res = ::GetComputerNameW(buf, &size);
		if (res == FALSE) return std::wstring(wszEmptyString);
		return std::wstring(buf, size);
	}

private:
	///	���� � ���-����� ��������
	std::wstring			m_sFullIniFileName;
	///	������ ������ ��� ������
	static const DWORD		m_dwBufferSize = 1024;
	///	����� ��� ������
	wchar_t					m_wcBuffer[m_dwBufferSize];
};
}	//namespace tsett