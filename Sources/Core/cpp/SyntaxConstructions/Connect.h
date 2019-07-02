#pragma once
#include <map>

#include "../ASCInterface/IDBMS.h"
#include "../ASSInterface/ILingvoBaseManager.h"
#include "../ASCInterface/IBaseManager.h"

namespace SS
{
	/// ����� ���������� �� ���������� � SQL �����
	class CConnectSQL : public SS::Core::CommonServices::CBaseCoreClass
	{
	private:
		///������������� ���������� � ������				
		bool InitConnection();
		///�������� ���������� � ������
		void CloseConnection();
	
	protected:
		///C������� ��� ���� ������
		wchar_t m_szBaseName[100];
		SS::Interface::Core::ResourceManagers::ILingvoBaseManager*	m_pLingvoBaseManager;
		SS::Interface::Core::ResourceManagers::IConnection*			m_pConnection;
		///����� �������������� ���������� � DBMS �����
		SS::Interface::Core::DBMS::IDataBase*						m_pDataBase;
	
	public:
		///�����������
		CConnectSQL(wchar_t* szBaseName);
		///����������
		virtual ~CConnectSQL();
		///������������� ��������� �� ������� �������� ����������
		void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
	};

	///����� ���������� �� ���������� � DBMS �����
	class CConnectDBMS : public SS::Core::CommonServices::CBaseCoreClass
	{
	private:
		///��������� ������ ��� ����
		std::map<std::wstring, SS::Interface::Core::DBMS::IDataTable*> m_mapTables;

	private:
		///��������� ���������� � ����� DBMS			
		void InitConnection();
		///�������� ���������� � ����� DBMS			
		void CloseConnection();
	
	protected:
		///�������� ��� ���� ������
		wchar_t m_szBaseName[100];
		///��������� �� ������� DBMS �������
		SS::Interface::Core::DBMS::IDataTable*						m_pDTable;
		///��������� �� ���� DBMS
		SS::Interface::Core::DBMS::IDataBase*						m_pDataBase;
		///����� �������������� ���������� � DBMS �����
		SS::Interface::Core::ResourceManagers::ILingvoBaseManager*	m_pLingvoBaseManager;

	protected:
		///�����������
		CConnectDBMS(wchar_t* szBaseName);
		///����������
		virtual ~CConnectDBMS();
		///���������� ���������� � ��������
		void SetTable(std::wstring & wTableName);
	
	public:	
		///���������� LoadManager (������������ �����)
		void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
	};

};
