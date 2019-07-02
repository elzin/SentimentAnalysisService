#pragma once

#include "..\ASCInterface\IDBMS.h"
#include "ICommon.h"
#include <atldbcli.h>


///// guid ��� ������, ��������������� ILingvoBaseManager (������ LingvoBaseManager)
//static const GUID CLSID_LinguoBaseManager = 
//{ 0xba24bf91, 0xfe10, 0x4729, { 0x9b, 0xa4, 0x16, 0x59, 0x24, 0x43, 0x21, 0xff } };

// guid ��� ���������� ILingvoBaseManager
static const GUID IID_LingvoBaseManager = 
{ 0x54aec5c1, 0x39e9, 0x4bc0, { 0xa3, 0xdb, 0xca, 0xd2, 0xa, 0x77, 0xb, 0x85 } };

// {8C09D01A-9361-4069-BF0F-28BFF80BFE49}
static const GUID CLSID_ConnectionManager = 
{ 0x8c09d01a, 0x9361, 0x4069, { 0xbf, 0xf, 0x28, 0xbf, 0xf8, 0xb, 0xfe, 0x49 } };

// {3D95BDDF-5B78-431b-8B54-603C10186F04}
static const GUID IID_ConnectionManager = 
{ 0x3d95bddf, 0x5b78, 0x431b, { 0x8b, 0x54, 0x60, 0x3c, 0x10, 0x18, 0x6f, 0x4 } };


namespace SS
{
namespace Interface
{
namespace Core
{
namespace ResourceManagers
{

	class ISubConnection;
	class CConnection;

	/// ����� ���������
	/** �������� ��������� "�������" */
	class ICommon
	{
	public:

		
		/*! \fn Close
		*  \brief  ��������� ���
		*/
		virtual void Close()=0;

		virtual ~ICommon(){};
	};

	/// ��������� ����������� � SQL-�����
	/** ������������ �������� � ���������� ���������� � SQL-����� */
	class IConnection
	{
	public:

		/// ��������� ���������� � sql-����� 
		/** 
			\param wszName ��� ������������
			\param wszPassword ������ ������������
			\param wszLocation �������� ����
			\param wszDataSource �������� ��������� ������ (��� SQL-�������)
			\return bool true, ���� ���������� ������ �������
			
		������� ������� ���������� � SQL - �����
		*/
		virtual bool Open(wchar_t* wszName, wchar_t* wszPassword, wchar_t* wszLocation, wchar_t* wszDataSource)=0;

		/// ��������� ���������� 
		/** 
			
		������������ �������� ���������� � SQL-����� 
		*/
		virtual void Close()=0;


		/// ���������, ������� �� ����������
		/** 
			\return bool ���� true, �� ���������� �������
			
		���������, ������� �� ���������� � SQL-����� 
		*/
		virtual bool IsOpen()=0;

		/// ���������� ������ ���������� 
		/** 
			\return ATL::CSession* ������ ����������
		
		*/
		virtual ATL::CSession* GetSession()=0;

		/// ������������� ������ �������� ���������� 
		/** 
			\return bool true, ���� ������������ ������ �������
			
		��� ������������ ������������ ������� ����������
		*/
		virtual bool ReOpenSession()=0;

		/// ���������� ����� ������ �� ������ 
		/** 
			\return int ����� ������ �� ������
			
		������������ ��� �������� (���� ����� ������ �� ����� ����, ������� ������ �� �������)
		*/
		virtual int CountSessionRef()=0;

		/// ���������� ���������� 
		/** 
			\return ULONG ��������� �������� �� �����
			
		������ delete this ����������� 
		*/
		virtual ULONG Release()=0;

		/// ���������� ������ ����������� �� ������ ������, ����� ����-������ ��������� ������� delete �� ��������� �� ������ ���������
		virtual ~IConnection(){};
	};

	/// ���������� �������������
	/** ������������� ��������� � ������-������ ���������� � SQL-����� � ����������
	��� ����, ����� ������� ������� ����������*/
	class ISubConnection 
	{
	public:

		/// ��������� �������������
		/** 
			\param pConnection - ����������, �������� ����������� �������������
			\return bool - ���� true, �������� ������ �������
		*/
		virtual bool SubOpen(IConnection* pConnection)=0;
		
		/// ��������� ������������� 
		virtual void SubClose()=0;

		virtual ~ISubConnection(){};
	};

	class ILingvoBaseManager : public virtual IBase
	{
	public:
		///// ��������� ���� ������������� ���� �� ������������ ������ 
		///** 
		//	\param BaseType - ��� ����, (���������������,  � �.�.) \see SS::MANAGER::Constants
		//	\param BaseGroup - ������, � ������� ��������� ���� (���������� �� DBMS � SQL-����) \see SS::MANAGER::Constants
		//*/
		//virtual void Close(const wchar_t* BaseType, const wchar_t* BaseGroup)=0;

		///// ��������� ���� ������������� ���� �� ������������ ������  
		///** 
		//	\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		//	\param BaseGroup - ������, � ������� ��������� ���� (���������� �� DBMS � SQL-����) \see SS::MANAGER::Constants
		//	\return bool - ���� true, �� ���� �������
		//*/
		//virtual bool Open(const wchar_t* BaseType, const wchar_t* BaseGroup)=0;

		///// ��������� ������������ ��� ��� �� ���� �����
		///** 
		//	\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		//*/
		//virtual void Close(const wchar_t* BaseType)=0;

		///// ��������� ������������ ��� ���
		///** 
		//	\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		//	\return bool - ���� true, �� ���� �������
		//*/
		//virtual bool Open(const wchar_t* BaseType)=0;

		/// ��������� ������������ �������� ���������� � �������������
		virtual void Close()=0;

		/// ��������� ������������, �� �������� ���������� � �������������
		/** 
			\return bool - ���� true, �� �������� ������ �������
		*/
		virtual bool Open()=0;

		/// ���������� ��� ��������� ���������
		/** 
			\return const wchar_t* ������ �� ��� ��������� ���������
		*/
		virtual const wchar_t* GetNameActiveStorage()=0;

		///// ������ ��� ��������� ���������
		///** 
		//	\param StorageName ��� ��������� ��������� (����� ���� Ind70ZMDF045DF...)
		//	\return bool - true, ���� �������� ��������� ������� ������
		//*/
		//virtual bool OpenStorage(const wchar_t* StorageName)=0;

		///// ���������� SubConnection 
		///** 
		//	\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		//	\param pSubConnection - �������������, \see ISubConnection
		//	
		//��������� � ���������� ������������� � ����� ������������������ 
		//(��� �������������) �������� ������� ������
		//*/
		//virtual void Register(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::ISubConnection* pSubConnection)=0;

		///// �������� SubConnection
		///** 
		//	\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
		//	\param pSubConnection - �������������, \see ISubConnection
		//	
		//������� ����� ������������������ ������������� 
		//*/
		//virtual void UnRegister(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::ISubConnection* pSubConnection)=0;

		/// ������������� ������ �� ���� DBMS-������ \see SS::MANAGER::Constants
		/** 
			\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
			\param ptssConnection - ��������� �� ������ � ����� DBMS
			
		���� ����� ������ ����� ����, ���� ����������� � ������������ ��������, ���������� � ��� 
		*/
		virtual void UnRegisterDeleteAndClose(const wchar_t* BaseType, SS::Interface::Core::DBMS::IDataBase** ptssConnection) = 0;

		/// �������� ��������, �������������� ����� ���� ������������� ���� � ������� ������� ���������� � ������������
		/** 
			\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
			\param ptssConnection - ��������� �� ������ � ����� DBMS
			
		������� ��������� ������ (���� ����� ��� �� ������, � ��������� ������ ���������� ��� ���������),
		��������������� ����� ���� ������������� ���� DBMS-������ � ���������� ��������� �� ���� � ���������� ��������� 
		*/
		virtual void CreateOpenAndRegister(const wchar_t* BaseType, SS::Interface::Core::DBMS::IDataBase** ptssConnection)=0;

		/// �������� ��������, �������������� ����� ���������� ������������� ���� � ������� ������� ���������� � ������������
		/** 
			\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
			\param ptssConnection - ��������� ��� ������ � ����������� � SQL-�����
			
		������� ��������� ������ (���� ����� ��� �� ������, � ��������� ������ ���������� ��� ���������),
		��������������� ����� ���������� ������������� ���� SQL-������ � ���������� ��������� �� ���� � ���������� ��������� 
		*/
		virtual void CreateOpenAndRegister(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::IConnection** ptssConnection)=0;


		/// ������������� ������ �� ���������� SQL-������ \see SS::MANAGER::Constants
		/** 
			\param BaseType - ��� ����, (��������������� � �.�.) \see SS::MANAGER::Constants
			\param ptssConnection - ��������� �� ������ � ����� SQL
			
		���� ����� ������ ����� ����, ���������� ����������� � ������������ ��������, ���������� � ��� 
		*/
		virtual void UnRegisterDeleteAndClose(const wchar_t* BaseType, SS::Interface::Core::ResourceManagers::IConnection** ptssConnection)=0;


		virtual ~ILingvoBaseManager(){};
	};



	/// �������� ����������
	class IConnectionManager 
		: public virtual IBase
		, public SS::Interface::Core::Common::IConnection
	{
	public:
		virtual void Register(SS::Interface::Core::Common::IConnection * pConnection) = 0;
	};



}
}
}
}
