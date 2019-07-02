#pragma once

#include "IInterface.h"
#include "IEnumerator.h"


// guid ��� ���������� ISettingsServer
static const GUID IID_SettingsServer = 
{ 0xa9a80d, 0x594c, 0x4e2c, { 0xb9, 0xeb, 0x27, 0x3d, 0x66, 0xa0, 0x2c, 0x6c } };

// guid ��� ���������� ISettingsServerEdit
static const GUID IID_SettingsServerEdit = 
{ 0xa9a80d, 0x594c, 0x4e2c, { 0xb9, 0xeb, 0x27, 0x3d, 0x66, 0xa0, 0x2c, 0x68 } };

/// guid ��� ������ CSettingsServer ������ GSServer, ��������������� ISettingsServer
static const GUID CLSID_SettingsServer = 
{ 0x82acdfda, 0xeb5b, 0x437a, { 0xb3, 0x96, 0x60, 0xa1, 0xf, 0x26, 0x46, 0x6a } };



// guid ��� ������ CPerformanceMeasure, ������������ IPerformanceMeasure � ������ UMCommonServices
static const GUID CLSID_PerformanceMeasure = 
{ 0x8f58c2c5, 0x5a7c, 0x42c6, { 0x8f, 0x20, 0x4a, 0xc5, 0xff, 0x30, 0x36, 0x93 } };

// guid ��� IPerformanceMeasure
static const GUID IID_PerformanceMeasure = 
{ 0xd4b615f5, 0xa436, 0x4b34, { 0x91, 0x9c, 0xaa, 0x6a, 0x7b, 0x7e, 0x43, 0x52 } };



/// guid ��� ������ CWorkRegister, ������������ IWorkRegister � ������ LoadManager 
static const GUID CLSID_WorkRegister = 
{ 0x2a11d2d5, 0x62e6, 0x4f23, { 0x83, 0x98, 0x7b, 0x6, 0x37, 0xd8, 0x58, 0xb7 } };


/// guid ��� IWorkRegister
static const GUID IID_WorkRegister = 
{ 0xf73fcf35, 0xbf6b, 0x48fa, { 0xaa, 0x9c, 0x20, 0xd0, 0xe0, 0x8e, 0x45, 0x25 } };



/// guid ��� ������ CException, ������������ IException � ������ UMCommonServices
static const GUID CLSID_Exception = 
{ 0x975b6ba0, 0xa7af, 0x432c, { 0x94, 0x5f, 0x55, 0x5b, 0x46, 0x36, 0xad, 0x89 } };

/// guid ��� IException
static const GUID IID_Exception = 
{ 0x872e1e0d, 0xb5b5, 0x4cf4, { 0xad, 0xf8, 0x56, 0x53, 0x1f, 0x3c, 0x45, 0x81 } };


/// guid ��� ������ CLogSingleton, ������������ ILog � ������ UMCommonServices
static const GUID CLSID_Log = 
{ 0x81c6a7f8, 0xc597, 0x4f76, { 0x97, 0xc6, 0xf7, 0xfb, 0x7a, 0xe7, 0xbd, 0xf3 } };

/// guid ��� ILog
static const GUID IID_Log = 
{ 0xb85a5747, 0xfd20, 0x4ff3, { 0x8a, 0x1b, 0x4f, 0x57, 0x90, 0x1d, 0xf3, 0x87 } };

/// guid ��� ������ CServerLog ������ ServerLog, ��������������� IServerLog
static const GUID CLSID_ServerLog = 
{ 0xc11ed496, 0x642f, 0x4fbf, { 0xa5, 0x28, 0x90, 0x4d, 0x93, 0xb0, 0xab, 0xe1 } };

/// guid ��� IServerLog
static const GUID IID_ServerLog = 
{ 0xab9ca0ee, 0x30a2, 0x4895, { 0x91, 0x57, 0xff, 0x4b, 0xb, 0x6e, 0xdf, 0x1 } };

/// guid ��� IFileFinder
static const GUID IID_FileFinder = 
{ 0xab771c1c, 0xf35c, 0x4b30, {0x8d, 0xc4, 0xd8, 0x0e, 0x61, 0xf2, 0xcc, 0xee} };

/// guid ��� ������, ��������������� IFileFinder
static const GUID CLSID_FileFinder = 
{ 0x7ba0ace0, 0x7ee0, 0x484f, {0x82, 0x62, 0x10, 0xff, 0xfd, 0x8d, 0xe3, 0x9b} };


namespace SS
{
namespace Core
{
namespace CommonServices
{

	///��� ������
	enum ETypeError
	{
		///�����������
		eteCritical,
		///�������
		eteNormal
	};
}
}
}

namespace SS
{
namespace Interface
{
namespace Core
{
namespace CommonServices
{
	enum EParameterType
		{
			ptInt,		//int
			ptUInt,		//unsigned int
			ptInt64,	//__int64
			ptString,	//wchar_t*
			ptDouble,	//double
			ptBoolean	//bool
		};
	/// ���������� ������ �������� �������
	class ISettingsServer : public SS::Interface::IBase
	{
	public:
		//������������� ������� ����������
		virtual void SetWorkPath (const wchar_t* sPath) = 0;
		///���������� ������� ��������� �� ����
		virtual void FlushToDisk () = 0;
		///// ������ �������� ���������, ������������� ������ sName. 
		///** ��� ��������� ������������ � EParameterType
		//	���� ��� ������ ����������, �� � puiArrayCount ����� ���������� ��������, 
		//	�������� 0xffffffff (���������� ��������� � �������)
		//*/
		//virtual void* GetParameter(const wchar_t* wszName, SS::Interface::Core::CommonServices::EParameterType* peType, unsigned int* puiArrayCount) = 0;

		/// ������ �������� ���������, ������������� ������ sName. 
		virtual unsigned int GetBoolean(const wchar_t* wszName) = 0;
		/// ������ �������� ���������, ������������� ������ sName. 
		virtual int GetInt(const wchar_t* wszName) = 0;
		/// ������ �������� ���������, ������������� ������ sName. 
		virtual unsigned int GetUInt(const wchar_t* wszName) = 0;
		/// ������ �������� ���������, ������������� ������ sName. 
		virtual void GetString(const wchar_t* wszName, std::wstring* pwsValue) = 0;
		/// ������ �������� ���������, ������������� ������ sName. 
		virtual __int64 GetInt64(const wchar_t* wszName) = 0;
		/// ������ �������� ���������, ������������� ������ sName. 
		virtual double GetDouble(const wchar_t* wszName) = 0;

		/// ��������� �������� ���������, ������������� ������ sName. 
		virtual void SetBoolean(const wchar_t* wszName, bool Value) = 0;
		/// ��������� �������� ���������, ������������� ������ sName. 
		virtual void SetInt(const wchar_t* wszName, int Value) = 0;
		/// ��������� �������� ���������, ������������� ������ sName. 
		virtual void SetUInt(const wchar_t* wszName, unsigned int Value) = 0;
		/// ��������� �������� ���������, ������������� ������ sName. 
		virtual void SetString(const wchar_t* wszName, std::wstring* pwsValue) = 0;
		/// ��������� �������� ���������, ������������� ������ sName. 
		virtual void SetInt64(const wchar_t* wszName, __int64 Value) = 0;
		/// ��������� �������� ���������, ������������� ������ sName. 
		virtual void SetDouble(const wchar_t* wszName, double Value) = 0;

		/// ������ �������� ���������, ������������� ������ sName (�������� �������, ���� ��������� �������� ������������ ������������ sType)
		virtual void GetArray(const wchar_t* wszName, SS::Interface::Core::CommonServices::EParameterType eType, void* pArray) = 0;
		/// ��������� �������� ���������, ������������� ������ sName 
		virtual void SetArray(const wchar_t* wszName, SS::Interface::Core::CommonServices::EParameterType eType, void* pArray) = 0;
	};

	///o��������� �������������� ��������
	class ISettingsServerEdit// : public SS::Interface::IBase
	{
	public:
		///���������� ������ ����������. ��������� - null
		virtual void GetParameterList (std::vector<std::wstring>* pOutSettingsNames, bool bShowPrivate) = 0;
		///���������� ��� ��������� �� ��� �����. ����� ���������� �������������� ���������, �������� �� ��������� �������� ��������
		virtual SS::Interface::Core::CommonServices::EParameterType GetParameterType (const wchar_t* wszName, bool* bIsArray = NULL) = 0;
		///��������� ���������
		virtual bool AddParameter (const wchar_t* wszName, EParameterType eType, bool bIsArray = false, 
					bool bIsPublic = true, bool bIsReadOnly = false) = 0;
		///������� ���������
		virtual void DeleteParameter (const wchar_t* wszName) = 0;
		///���������� �����������
		virtual unsigned int GetPublicity				(const wchar_t* wszName) = 0;
		///���������� ��� �������
		virtual unsigned int GetAccessibility			(const wchar_t* wszName) = 0;
		///������������� ����� ��� ���������	
		virtual void SetParameterName			(const wchar_t* wszName, const wchar_t* wszNewName) = 0;
		///������������� �����������
		virtual void SetParameterPublicity (const wchar_t* wszName, bool bIsPublic) = 0;
		///������������� ��� �������
		virtual void SetParameterAccessibility (const wchar_t* wszName, bool bIsReadOnly) = 0;
		///������������� ���
		virtual void SetParameterType (const wchar_t* wszName, SS::Interface::Core::CommonServices::EParameterType eType) = 0;
		///��������� �������� ��������� � ������
		virtual void AddParameterValue (const wchar_t* wszName, SS::Interface::Core::CommonServices::EParameterType eType, void* pValue) = 0;
	};

	enum ELogEntryType
	{
		etException,
		etInfo,
		etError,
		etAnyType // for categorized query
	};

	enum ELogEntrySeverity
	{
		etCritical,
		etNormal,
		etLow,
		etAnySeverity // for categorized query
	};

	class IServerLog : public SS::Interface::IBase
	{
	public:
		virtual void Save(
			SS::Interface::Core::CommonServices::ELogEntryType LogEntryType,
			SS::Interface::Core::CommonServices::ELogEntrySeverity LogEntrySeverity,
			wchar_t* wszMessage,wchar_t* wszComputerHost,wchar_t* wszServiceHost,
			wchar_t* wszModule,wchar_t* wszClass,wchar_t* wszMethod ) = 0;

		virtual wchar_t* GetMessages() = 0;
		virtual wchar_t* GetMessages(unsigned long lFirstMessage,unsigned long lLastMessage) = 0;
		virtual wchar_t* GetFirstMessages(unsigned long iNumberOfMessages) = 0;
		virtual wchar_t* GetLastMessages(unsigned long iNumberOfMessages) = 0;

		virtual wchar_t* GetCategorizedMessages(
			SS::Interface::Core::CommonServices::ELogEntryType LogEntryType,
			SS::Interface::Core::CommonServices::ELogEntrySeverity LogEntrySeverity,
			wchar_t* wszMessage,wchar_t* wszComputerHost,wchar_t* wszServiceHost,
			wchar_t* wszModule,wchar_t* wszClass,wchar_t* wszMethod ) = 0;

		virtual wchar_t* GetCategorizedMessages(
			unsigned long lFirstMessage,unsigned long lLastMessage,
			SS::Interface::Core::CommonServices::ELogEntryType LogEntryType,
			SS::Interface::Core::CommonServices::ELogEntrySeverity LogEntrySeverity,
			wchar_t* wszMessage,wchar_t* wszComputerHost,wchar_t* wszServiceHost,
			wchar_t* wszModule,wchar_t* wszClass,wchar_t* wszMethod ) = 0;

		virtual wchar_t* GetCategorizedFirstMessages(
			unsigned long iNumberOfMessages,
			SS::Interface::Core::CommonServices::ELogEntryType LogEntryType,
			SS::Interface::Core::CommonServices::ELogEntrySeverity LogEntrySeverity,
			wchar_t* wszMessage,wchar_t* wszComputerHost,wchar_t* wszServiceHost,
			wchar_t* wszModule,wchar_t* wszClass,wchar_t* wszMethod ) = 0;

		virtual wchar_t* GetCategorizedLastMessages(
			unsigned long iNumberOfMessages,
			SS::Interface::Core::CommonServices::ELogEntryType LogEntryType,
			SS::Interface::Core::CommonServices::ELogEntrySeverity LogEntrySeverity,
			wchar_t* wszMessage,wchar_t* wszComputerHost,wchar_t* wszServiceHost,
			wchar_t* wszModule,wchar_t* wszClass,wchar_t* wszMethod ) = 0;

		virtual unsigned long GetNumberOfMessages() = 0;

		virtual void SetWorkpath(wchar_t* wszWorkpath) = 0;

		virtual void CallManagedSaveHandler(
			long LogEntryType,
			long LogEntrySeverity,
			wchar_t* wszMessage,wchar_t* wszComputerHost,
			wchar_t* wszHost,wchar_t* wszModule,
			wchar_t* wszClass,wchar_t* wszMethod) = 0;
	};

	/// ���������� ��������������� 
	class IPerformanceMeasure : public SS::Interface::IBase
	{
	public:
		///������ �������� ������� ����������
		virtual void	StartCalculation(const wchar_t* szID) = 0;
		///������� ������ �� ��������������
		virtual void	ClearCalculation(const wchar_t* szID) = 0;
		///������� �������
		virtual void	ClearCalculations() = 0;
		///������� �������� ������� ����������
		virtual void	StopCalculation(const wchar_t* szID) = 0;
		///������� ������� ����������
		virtual double	GetCalculation(const wchar_t* szID) = 0;
		///����������� ������� ����������
		virtual void	ViewCalculation(const wchar_t* szID) = 0;
		///����������� ���� ������� ������� ����������
		virtual void	ViewCalculations(void) = 0;
	};

	class IWorkRegister : public SS::Interface::IBase
	{
	public:

		///���������� �������� ��������� �� ��� ����� (������ ������)
		virtual std::wstring GetParameter(std::wstring wParametrName) = 0;

		///��������� ������� ����������
		virtual void SetWorkDir(std::wstring wPathToDir) = 0;
	};

	class ILog : public SS::Interface::IBase
	{
	public:

		///������ ������ ���-��������� szMessage �� ����
		virtual void SaveLog(wchar_t* szFirst...) = 0;		
	};

	class IExceptionParams 
	{
	public:

		///��������� ��������� �� ������
		virtual void SetMessage(wchar_t* wszMessage...) = 0;
		///������ ��������� �� ������
		virtual const std::wstring& GetMessage() = 0;		

		///��������� ��� �������, ��������� ������
		virtual void SetFunction(const std::wstring wsFunction) = 0;
		///������ ��� �������, ��������� ������
		virtual const std::wstring& GetFunction() = 0;

		///��������� ��� ����� � �����
		virtual void SetFile(const std::wstring wsFile) = 0;
		///������ ��� ����� � �����
		virtual const std::wstring& GetFile() = 0;

		///��������� ����� ������ � ����� � ����� 
		virtual void SetLine(const long lLine) = 0;
		///������ ����� ������ � ����� � ����� 
		virtual const long GetLine() = 0;

		///��������� ��� ������
		virtual void SetTypeError(const SS::Core::CommonServices::ETypeError eteTypeError) = 0;
		///������ ��� ������
		virtual const SS::Core::CommonServices::ETypeError GetTypeError() = 0;
	};

	class IException : public SS::Interface::IBase,
		virtual public SS::Interface::Enumerators::IEnumerator
	{
	public:

		///���������� ��������� ������ � ������
		virtual SS::Interface::Core::CommonServices::IExceptionParams* Add() = 0;
		
		///������������ ������� ������
		virtual SS::Interface::Core::CommonServices::IExceptionParams* GetCurrent() = 0;

		///���������� � ���� ������ ����������� ������
		virtual std::wstring& ToString() = 0;
	};

	/// ����� ������ (��� ������)
	class IFileFinder : public SS::Interface::IBase
	{
	public:
		/// ���� ����� � ����� (vIgnoreExt ������������ ���������� (������ - ".ext"))
		virtual bool GetFiles(std::wstring& sRootPath, std::wstring& sSubPath, std::vector<std::wstring>* vIgnoreExt, std::vector<std::wstring>* vRelPaths)=0;
	};


}
}
}
}