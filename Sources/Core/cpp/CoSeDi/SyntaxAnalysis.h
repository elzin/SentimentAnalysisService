#pragma once

#include "..\ASSInterface\ICoSeDi.h"
#include ".\CashCoSeDi.h"
#include ".\connect.h"
#include ".\dboSyntax.h"


namespace SS
{
	namespace CoSeDi
	{
		namespace SQL
		{
			/// ����� ����������� ������ � ����� �������� �������������� ����������
			class CSyntaxAnalysis :
				public SS::CoSeDi::SQL::CConnect,
				public SS::Interface::Core::CoSeDi::ISyntaxAnalysis
			{
			public:
				/// ����������
				virtual ~CSyntaxAnalysis(void)
				{
				};
				/// �����������
				/** 
					\param SS::CoSeDi::DBMS::CCashCoSeDi*pCashCoSeDi - ��������� �� ���
					\param szBaseName - ��� ����
				*/
				CSyntaxAnalysis(SS::CoSeDi::SQL::CCashCoSeDi*	pCashCoSeDi, const wchar_t* szBaseName) : SS::CoSeDi::SQL::CConnect(szBaseName)   
				{
					m_pCashCoSeDi = pCashCoSeDi;
				};
			public: // function
				/// ������������� ��������� �� ������� �������� ����������
				/** 
					\param pLoadManager - ��������� �� ������� �������� ����������
					\return void
				*/	
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS_TRY;
					SS::Core::CommonServices::CBaseCoreClass::SetLoadManager(pLoadManager);
					InitConnection();
					SS_CATCH(L"");
				}
			public: // from SS::CoSeDi::Intrefaces::ISyntaxAnalysis
								/// ���������� ������, ���������� �������������� �������������� ��� ������� ������
				/** 
					\param p_list_OfSyntaxInfo - ��������� �� ������, ���������� �������������� �������������� ��� ������� ������
				*/
				void Get(/*out*/std::list<SS::CoSeDi::DataTypes::TSyntaxInfo>* p_list_OfSyntaxInfo);

				/// ��������� ������, ���������� �������������� �������������� ��� ������� ������
				/** 
					\param p_list_OfSyntaxInfo - ��������� �� ������, ���������� �������������� �������������� ��� ������� ������
				*/
				void Add(/*in*/std::list<SS::CoSeDi::DataTypes::TSyntaxInfo>* p_list_OfSyntaxInfo);

				/// ������� ��� �������������� ���������� ��� ������� ������
				void Delete();

				/// ������� ������, ���������� �������������� �������������� ��� ������� ������
				/** 
					\param p_list_OfSyntaxInfo - ��������� �� ������, ���������� �������������� �������������� ��� ������� ������
				*/
				void Delete(/*in*/std::list<SS::CoSeDi::DataTypes::TSyntaxInfo>* p_list_OfSyntaxInfo);
				
			private:
				/*! \var SS::CoSeDi::SQL::CCashCoSeDi								* m_pCashCoSeDi
				*  \brief	- ��������� �� ���     
				*/
				SS::CoSeDi::SQL::CCashCoSeDi				* m_pCashCoSeDi;							
			};
		};

		namespace DBMS
		{
			/// ����� ����������� ������ � ����� �������� �������������� ����������
			class CSyntaxAnalysis : 
				public SS::CoSeDi::DBMS::CConnect,
				public SS::Interface::Core::CoSeDi::ISyntaxAnalysis
			{
			public:
				/// �����������
				/** 
					\param SS::CoSeDi::DBMS::CCashCoSeDi*pCashCoSeDi - ��������� �� ���
					\param szBaseName - ��� ����
				*/
				CSyntaxAnalysis(SS::CoSeDi::DBMS::CCashCoSeDi*	pCashCoSeDi, const wchar_t* szBaseName) : 
				  SS::CoSeDi::DBMS::CConnect(szBaseName)
				{
					m_pCashCoSeDi = pCashCoSeDi;
					m_SSyntaxAccess.DictionaryNumber = 0;
					m_SSyntaxAccess.IDSource = 0;
					m_SSyntaxAccess.SyntaxInfo = 0;
					TableRecord[0] = NULL;
					TableRecord[1] = NULL;
					TableRecord[2] = NULL;
				};
				/// ����������
				virtual ~CSyntaxAnalysis(void)
				{
				};
			public: // function
				/// ������������� ��������� �� ������� �������� ����������
				/** 
					\param pLoadManager - ��������� �� ������� �������� ����������
					\return void
				*/	
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS::Core::CommonServices::CBaseCoreClass::SetLoadManager(pLoadManager);
					InitConnection();
				}
			public: // from SS::CoSeDi::Intrefaces::ISyntaxAnalysis
								/// ���������� ������, ���������� �������������� �������������� ��� ������� ������
				/** 
					\param p_list_OfSyntaxInfo - ��������� �� ������, ���������� �������������� �������������� ��� ������� ������
				*/
				void Get(/*out*/std::list<SS::CoSeDi::DataTypes::TSyntaxInfo>* p_list_OfSyntaxInfo);

				/// ��������� ������, ���������� �������������� �������������� ��� ������� ������
				/** 
					\param p_list_OfSyntaxInfo - ��������� �� ������, ���������� �������������� �������������� ��� ������� ������
				*/
				void Add(/*in*/std::list<SS::CoSeDi::DataTypes::TSyntaxInfo>* p_list_OfSyntaxInfo);

				/// ������� ��� �������������� ���������� ��� ������� ������
				void Delete();

				/// ������� ������, ���������� �������������� �������������� ��� ������� ������
				/** 
					\param p_list_OfSyntaxInfo - ��������� �� ������, ���������� �������������� �������������� ��� ������� ������
				*/
				void Delete(/*in*/std::list<SS::CoSeDi::DataTypes::TSyntaxInfo>* p_list_OfSyntaxInfo);
			private:	
				/// ������������� ���������� � ���������
				bool	InitConnection(void);
			private:
				/*! \var SS::CoSeDi::DataTypes::SSyntaxAccess m_SSyntaxAccess;
				*  \brief     - ���������, ���������� ���� ��� ������� � ��������
				*/
				SS::CoSeDi::DataTypes::SSyntaxAccess m_SSyntaxAccess;

				/*! \var SS::CoSeDi::SQL::CCashCoSeDi								* m_pCashCoSeDi
				*  \brief	- ��������� �� ���     
				*/
				SS::CoSeDi::DBMS::CCashCoSeDi	* m_pCashCoSeDi;		
				
				/*! \var void       * TableRecord[2];
				*  \brief     ������ ���������� �� ������, ���������� ������ � DBMS �������
				*/
				void* TableRecord[3];

				/*! \enum EFindMode
				*  \brief     ��������� ����, �� �������� ����� �������������� �����
				*/
				enum EFindMode
				{
					efmByIDSource
				};

			};
		};
	};
};
