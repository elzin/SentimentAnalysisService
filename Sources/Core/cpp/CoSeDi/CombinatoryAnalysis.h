#pragma once

#include "..\ASSInterface\ICoSeDi.h"

#include ".\connect.h"

#include ".\CashCoSeDi.h"

#include ".\dboCombinatory.h"

#include "..\ASSInterface\TCoSeDiDataTypes.h"

#include "../ASCInterface/IDBMS.h"
#include "..\ASSInterface\TDictionaryNames.h"




namespace SS
{
	namespace CoSeDi
	{
		namespace SQL
		{
			/// ����� ����������� ���������� �������������� ������� ��� SQL
			class CCombinatoryAnalysis : 
				public SS::CoSeDi::SQL::CConnect,
				public SS::Interface::Core::CoSeDi::ICombinatoryAnalysis				
			{
			public:
				/// �����������
				CCombinatoryAnalysis(SS::CoSeDi::SQL::CCashCoSeDi*	pCashCoSeDi, const wchar_t* szBaseName) : 
				  SS::CoSeDi::SQL::CConnect(szBaseName)
				{
					m_pCashCoSeDi = pCashCoSeDi;					
				}
				/// ����������
				virtual ~CCombinatoryAnalysis(void){};			
			public: // from SS::CoSeDi::Intrefaces::ICombinatoryAnalysis
				/// ���������� ������ ���������� ��� ������������ �����
				/** 
					\param oFormInfo - ���������� �����, ��� �������� ���������� ���������
					\param p_list_CombinationList - ��������� �� ������ �����������
					\return bool - ��������� ���������� ��������
				*/
				bool	GetCombinations(/*in*/ SS::CoSeDi::DataTypes::TFormInfo & oFormInfo, /*out*/SS::CoSeDi::DataTypes::TlistOfCombination * p_list_CombinationList);
				
				/// ������� ���������� � ���������� �� �����
				/** 
					\param p_CombinationInfo - ��������� �� ����������� ����������
					\return 
				*/
				int		CreateCombination(/*in*/ SS::CoSeDi::DataTypes::TCombinationInfo * p_CombinationInfo);
				
				/// ���������� ��� ������� ���������� ��� �� ��������
				/** 
					\param p_CombinationInfo - ��������� �� ���������, �������� ������ ���������� � ����������
					\return 
				*/
				void	GetCombinationInfo(/*out*/ SS::CoSeDi::DataTypes::TCombinationInfo * p_CombinationInfo);	

				/// ������� ������� ���������� �� ����
				bool	DeleteCombination();
			public: // function
				/// ������������� ��������� �� ������� �������� ����������
				/** 
					\param pLoadManager - ��������� �� ������� �������� ����������
				*/				
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS_TRY;

					SS::Core::CommonServices::CBaseCoreClass::SetLoadManager(pLoadManager);
					InitConnection();

					SS_CATCH(L"");
					return ;
				}
			private: // function
				/// ���������� ��������� ������������ ������ ����������
				int GetLastCombinationID();
			private: // variables				
				/*! \var SS::CoSeDi::SQL::CCashCoSeDi					* m_pCashCoSeDi
				*  \brief	- ��������� �� ���     
				*/
				SS::CoSeDi::SQL::CCashCoSeDi								* m_pCashCoSeDi;
				
				/*! \var SS::CoSeDi::SQL::SQL_ACCESS::CPreparedSMaxTCombinatory	* pSMaxTCombinatory
				*  \brief     - ��������� �� �����, ���������� ������������ �������� ID �� �������������
				*/
				SS::CoSeDi::SQL::SQL_ACCESS::Combinatory::CPreparedSMaxTCombinatory	* pSMaxTCombinatory;
				/*! \var SS::CoSeDi::SQL::SQL_ACCESS::Combinatory::CPreparedSMaxTCombinatory	* pSMaxTCombinatory
				*  \brief     - ��������� �� �����, ����������� �������� � �������������
				*/
				SS::CoSeDi::SQL::SQL_ACCESS::Combinatory::CPreparedITCombinatory		* pITCombinatory;
				/*! \var SS::CoSeDi::SQL::SQL_ACCESS::Combinatory::CPreparedSMaxTCombinatory	* pSMaxTCombinatory
				*  \brief     - ��������� �� �����, ���������� ������������� ���������� �� ����
				*/
				SS::CoSeDi::SQL::SQL_ACCESS::Combinatory::CPreparedSTCombinatoryInfo	* pSTCombinatoryInfo;
				/*! \var SS::CoSeDi::SQL::SQL_ACCESS::Combinatory::CPreparedSMaxTCombinatory	* pSMaxTCombinatory
				*  \brief     - ��������� �� �����, ���������� ��� ���������� �� ����
				*/
				SS::CoSeDi::SQL::SQL_ACCESS::Combinatory::CPreparedSAllCombination	* pSAllCombination;

			};
		};
		namespace DBMS
		{

			/// ����� ����������� ���������� �������������� ������� ��� DBMS
			class CCombinatoryAnalysis : 
				public SS::CoSeDi::DBMS::CConnect,
				public SS::Interface::Core::CoSeDi::ICombinatoryAnalysis	
			{
			public:
				/// �����������
				CCombinatoryAnalysis(SS::CoSeDi::DBMS::CCashCoSeDi*	pCashCoSeDi, const wchar_t* szBaseName) :
					SS::CoSeDi::DBMS::CConnect(szBaseName)
				{
					m_pCashCoSeDi = pCashCoSeDi;
				}
				/// ����������
				virtual ~CCombinatoryAnalysis(void)
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

			public: // from SS::CoSeDi::Intrefaces::ICombinatoryAnalysis
				/// ���������� ������ ���������� ��� ������������ �����
				/** 
					\param oFormInfo - ���������� �����, ��� �������� ���������� ���������
					\param p_list_CombinationList - ��������� �� ������ �����������
					\return bool - ��������� ���������� ��������
				*/
				bool	GetCombinations(/*in*/ SS::CoSeDi::DataTypes::TFormInfo & oFormInfo, /*out*/SS::CoSeDi::DataTypes::TlistOfCombination * p_list_CombinationList);
				
				/// ������� ���������� � ���������� �� �����
				/** 
					\param p_CombinationInfo - ��������� �� ����������� ����������
					\return 
				*/
				int		CreateCombination(/*in*/ SS::CoSeDi::DataTypes::TCombinationInfo * p_CombinationInfo);
				
				/// ���������� ��� ������� ���������� ��� �� ��������
				/** 
					\param p_CombinationInfo - ��������� �� ���������, �������� ������ ���������� � ����������
					\return 
				*/
				void	GetCombinationInfo(/*out*/ SS::CoSeDi::DataTypes::TCombinationInfo * p_CombinationInfo);	

				/// ������� ������� ���������� �� ����
				bool	DeleteCombination();
			private:
				/// �������� ���������� � ���������				
				bool InitConnection(void);
			private:
				/*! \var SS::CoSeDi::SQL::CCashCoSeDi								* m_pCashCoSeDi
				*  \brief	- ��������� �� ���     
				*/
				SS::CoSeDi::DBMS::CCashCoSeDi*	m_pCashCoSeDi;
				
				/*! \var SS::CoSeDi::DataTypes::SCombinatoryAccess m_SCombinatoryAccess
				*  \brief     ���������, �������� ���������� ��� ������� � DBMS �������
				*/
				SS::CoSeDi::DataTypes::SCombinatoryAccess m_SCombinatoryAccess;
				/*! \var void       * TableRecord[5];
				*  \brief     ������ ���������� �� ������, ���������� ������ � DBMS �������
				*/
				void       * TableRecord[7];
				/*! \enum EFindMode
				*  \brief     ��������� ����, �� �������� ����� �������������� �����
				*/
				enum EFindMode
				{
					efmByID,
					efmByIDSource
				};

				
			};
		};
	
	};
};
