#pragma once

#include "..\ASSInterface\ICoSeDi.h"
#include ".\CashCoSeDi.h"


namespace SS
{
	namespace CoSeDi
	{
		namespace SQL
		{
			class CCashCoSeDiEx : 
				public SS::Interface::Core::CoSeDi::ICoSeDiLoad,
				public SS::Core::CommonServices::CBaseCoreClass
			{
			public:
				CCashCoSeDiEx(void);
				~CCashCoSeDiEx(void);
			public: // function
				/// ������������� ��������� �� ������� �������� ����������
				/** 
					\param pLoadManager - ��������� �� ������� �������� ����������
					\return void
				*/
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS_TRY
					{
						SS::Core::CommonServices::CBaseCoreClass::SetLoadManager( pLoadManager);

						m_oCashCoSeDiRus.SetLoadManager( pLoadManager);
						m_oCashCoSeDiEng.SetLoadManager( pLoadManager);
					}
					SS_CATCH(L"")
				}
			public:	//	from ILoad
				/// ������� �������
				bool Clear();
				///	��������� ��������	
				bool Load();
				///	������������	
				bool ReLoad();
				///	�������������� � ��������� ����	
				bool ToBinary();
			public:
				SS::CoSeDi::SQL::CCashCoSeDi m_oCashCoSeDiRus;
				SS::CoSeDi::SQL::CCashCoSeDi m_oCashCoSeDiEng;
			};
		};
		namespace DBMS
		{
			class CCashCoSeDiEx : 
				public SS::Interface::Core::CoSeDi::ICoSeDiLoad,
				public SS::Core::CommonServices::CBaseCoreClass
			{
			public:
				CCashCoSeDiEx(void);
				~CCashCoSeDiEx(void);
			public: // function
				/// ������������� ��������� �� ������� �������� ����������
				/** 
					\param pLoadManager - ��������� �� ������� �������� ����������
					\return void
				*/
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS_TRY
					{
						SS::Core::CommonServices::CBaseCoreClass::SetLoadManager( pLoadManager);

						m_oCashCoSeDiRus.SetLoadManager( pLoadManager);
						m_oCashCoSeDiEng.SetLoadManager( pLoadManager);
					}
					SS_CATCH(L"")
				}
			public:	//	from ILoad
				/// ������� �������
				bool Clear();
				///	��������� ��������	
				bool Load();
				///	������������	
				bool ReLoad();
				///	�������������� � ��������� ����	
				bool ToBinary();
			public:
				SS::CoSeDi::DBMS::CCashCoSeDi m_oCashCoSeDiRus;
				SS::CoSeDi::DBMS::CCashCoSeDi m_oCashCoSeDiEng;
			};

		};
	};
};