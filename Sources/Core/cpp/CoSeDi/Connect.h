#pragma once

#include "../ASCInterface/IDBMS.h"
#include "../ASSInterface/ILingvoBaseManager.h"
#include "../ASCInterface/IBaseManager.h"


namespace SS
{
	namespace CoSeDi
	{
		namespace SQL
		{
			/// ����� ���������� �� ���������� � SQL �����
			class CConnect : public SS::Core::CommonServices::CBaseCoreClass
			{

			public:
				/// �����������
				/** 
					\param szBaseName - ��� ����
				*/
				CConnect(const wchar_t* szBaseName);
				/// ����������
				virtual ~CConnect(void);
			protected:
				/// ������������� ���������� � ������				
				bool InitConnection();
				/// �������� ���������� � ������
				void CloseConnection(void);
			
			protected:
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS::Core::CommonServices::CBaseCoreClass::SetLoadManager(pLoadManager);

					m_pLingvoBaseManager = 
						(SS::Interface::Core::ResourceManagers::ILingvoBaseManager*)
						GetLoadManager()->GetInterface(L"./core/linguistics/LingvoBaseManager.dll", CLSID_LinguoBaseManager, IID_LingvoBaseManager);

				};
	
				SS::Interface::Core::ResourceManagers::ILingvoBaseManager *m_pLingvoBaseManager;
				SS::Interface::Core::ResourceManagers::IConnection* m_pConnection;

			protected:
				/*! \var SS::Interface::Core::DBMS::IDataBase * m_pDataBase;
				*  \brief     ����� �������������� ���������� � DBMS �����
				*/
				SS::Interface::Core::DBMS::IDataBase * m_pDataBase;
				
				/*! \var char m_szBaseName[100]
				*  \brief     - �������� ��� ���� ������
				*/
				wchar_t m_szBaseName[100];
			
			};

		};

		namespace DBMS
		{
			/// ����� ���������� �� ���������� � DBMS �����
			class CConnect : public SS::Core::CommonServices::CBaseCoreClass
			{
			public:
				/// �����������
				/** 
					\param szBaseName - ��� ����
				*/
				CConnect(const wchar_t* szBaseName);
				/// ����������
				virtual ~CConnect(void);
			protected:
				/// ������������� ���������� � ������				
				bool InitConnection(std::wstring& wDataTableName);
				/// �������� ���������� � ������			
				void CloseConnection(void);
			protected:
				/*! \var SS::Interface::Core::DBMS::IDataBase * m_pDataBase;
				*  \brief     ����� �������������� ���������� � DBMS �����
				*/
				SS::Interface::Core::DBMS::IDataBase * m_pDataBase;
				/*! \var char m_szBaseName[100]
				*  \brief     - �������� ��� ���� ������
				*/
				wchar_t m_szBaseName[100];

				/*! \var SS::Interface::Core::DBMS::IDataTable * m_pDTable
				*  \brief     ��������� ��� ������ � DBMS ���������
				*/
				SS::Interface::Core::DBMS::IDataTable * m_pDTable;

			protected:

				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS::Core::CommonServices::CBaseCoreClass::SetLoadManager(pLoadManager);

					m_pLingvoBaseManager = 
						(SS::Interface::Core::ResourceManagers::ILingvoBaseManager*)
						GetLoadManager()->GetInterface(L"./core/linguistics/LingvoBaseManager.dll", CLSID_LinguoBaseManager, IID_LingvoBaseManager);

				};
	
				SS::Interface::Core::ResourceManagers::ILingvoBaseManager *m_pLingvoBaseManager;


			};

		};
	};
};
