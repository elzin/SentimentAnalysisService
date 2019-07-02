#pragma once
#include "..\ASSInterface\ILingvoBaseManager.h"
#include <atldbcli.h>


namespace SS
{
namespace Core
{
namespace ResourceManagers
{

	/// ��������� ����������� � SQL-�����
	/** ������������ �������� � ���������� ���������� � SQL-����� */
	class CConnection :
		public SS::Interface::Core::ResourceManagers::IConnection
	{

		/// true, ���� ���������� �������
		bool m_IsOpen;

		/// ���������� � �����
		ATL::CDataSource m_currentDB;
		/// ������ ������ � �����
		ATL::CSession	m_currentSession;

	public:

		CConnection(void);
		virtual ~CConnection(void);

		/// ��������� ���������� � sql-����� 
		/** 
			\param wszName ��� ������������
			\param wszPassword ������ ������������
			\param wszLocation �������� ����
			\param wszDataSource �������� ��������� ������ (��� SQL-�������)
			\return bool true, ���� ���������� ������ �������
			
		������� ������� ���������� � SQL - �����
		*/
		bool Open(wchar_t* wszName, wchar_t* wszPassword, wchar_t* wszLocation, wchar_t* wszDataSource);

		/// ��������� ���������� 
		/** 
			
		������������ �������� ���������� � SQL-����� 
		*/
		void Close();

		/// ���������, ������� �� ����������
		/** 
			\return bool ���� true, �� ���������� �������
			
		���������, ������� �� ���������� � SQL-����� 
		*/
		bool IsOpen();

		/// ���������� ������ ���������� 
		/** 
			\return ATL::CSession* ������ ����������
		
		*/
		ATL::CSession* GetSession();

		/// ���������� ���������� 
		/** 
			\return ULONG ��������� �������� �� �����
			
		������ delete this ����������� 
		*/
		ULONG Release(){delete this;return 0;};

		/// ������������� ������ �������� ���������� 
		/** 
			\return bool true, ���� ������������ ������ �������
			
		��� ������������ ������������ ������� ����������
		*/
		bool ReOpenSession();

		/// ���������� ����� ������ �� ������ 
		/** 
			\return int ����� ������ �� ������
			
		������������ ��� �������� (���� ����� ������ �� ����� ����, ������� ������ �� �������)
		*/
		int CountSessionRef();
	};  
}
}
}
