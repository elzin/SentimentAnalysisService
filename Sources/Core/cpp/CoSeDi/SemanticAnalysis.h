#pragma once

#include "..\ASSInterface\ICoSeDi.h"
#include ".\CashCoSeDi.h"
#include ".\connect.h"
#include ".\dboSemantic.h"

namespace SS
{
	namespace CoSeDi
	{
		using namespace SS::CoSeDi::DataTypes;

		namespace SQL
		{
			using namespace SS::CoSeDi::SQL::SQL_ACCESS::Semantic;
		
			/// ����� ���������� �� ��������� � ���������� ������������� ���������� � ����� �� SQL ����
			class CSemanticAnalysis : 
				public SS::CoSeDi::SQL::CConnect,
				public SS::Interface::Core::CoSeDi::ISemanticAnalysis
			{
			public:
				/// �����������
				/** 
					\param SS::CoSeDi::DBMS::CCashCoSeDi*pCashCoSeDi - ��������� �� ���
					\param szBaseName - ��� ����
				*/
				CSemanticAnalysis(SS::CoSeDi::SQL::CCashCoSeDi*	pCashCoSeDi, const wchar_t* szBaseName) : 
				  SS::CoSeDi::SQL::CConnect(szBaseName)
				{
					m_pCashCoSeDi = pCashCoSeDi;
				};
				/// ����������
				virtual ~CSemanticAnalysis(void){};
			public: // from SS::Interface::Core::CoSeDi::ISemanticAnalysis
				/// ���������� ������ ������������� ������� �� ������� �����
				/** 
					\param oTFormInfo - ������ ������ �����
					\param p_list_OfClass - ��������� �� ������ �������� ������������� �������
				*/
				bool	GetClasses(/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex, /*out*/ std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_Class);

				/// ���������� ������ ����, ������� ��������� � �������� �������������� ������
				/** 
					\param p_list_FormInfo - ��������� �� ������, ���������� �����, ����������� � �������������� ������
				*/
				void	GetWords(/*out*/ std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_DictionaryIndex);	

				/// ��������� ����� � �������� �������������� ������
				/** 
					\param oTFormInfo - ��� ���������� �����, ������� ���������� ��������
					\return ��������� ��������� ���������� ��������
				*/
				bool	AddWord(/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex);

				/// ������� �����, ����������� � �������� �������������� ������ � ������������� � TFormInfo
				/** 
					\param oTFormInfo - ��� ���������� �����, ������� ���������� �������
					\return bool	- ��������� ��������
				*/
				bool	DeleteWord (/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex);
				
				/// ������� ������� ������������� ����� 
				bool	DeleteClass(SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber oDictionariesNumber);

				/// ������� ����� � ��������� � ���� �����
				/** 
					\param oTFormInfo - ��� ���������� �����, ������� ���������� ��������
					\return ��������� ����� ���������� ������
				*/
				int	CreateClassAndAddWord(/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex);

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
			private:
				/*! \var SS::CoSeDi::SQL::CCashCoSeDi								* m_pCashCoSeDi
				*  \brief	- ��������� �� ���     
				*/
				SS::CoSeDi::SQL::CCashCoSeDi				* m_pCashCoSeDi;	
			
			};

						/// ����� ���������� �� ��������� � ���������� ������������� ���������� � ����� �� SQL ����
			class CSemanticAnalysisSynonims : 
				public SS::CoSeDi::SQL::CConnect,
				public SS::Interface::Core::CoSeDi::ISemanticAnalysis
			{
			public:
				/// �����������
				/** 
					\param SS::CoSeDi::DBMS::CCashCoSeDi*pCashCoSeDi - ��������� �� ���
					\param szBaseName - ��� ����
				*/
				CSemanticAnalysisSynonims(SS::CoSeDi::SQL::CCashCoSeDi*	pCashCoSeDi, const wchar_t* szBaseName) : 
				  SS::CoSeDi::SQL::CConnect(szBaseName)
				{
					m_pCashCoSeDi = pCashCoSeDi;
				};
				/// ����������
				virtual ~CSemanticAnalysisSynonims(void){};
			public: // from SS::Interface::Core::CoSeDi::ISemanticAnalysis
				/// ���������� ������ ������������� ������� �� ������� �����
				/** 
					\param oTFormInfo - ������ ������ �����
					\param p_list_OfClass - ��������� �� ������ �������� ������������� �������
				*/
				bool	GetClasses(/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex, /*out*/ std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_Class);

				/// ���������� ������ ����, ������� ��������� � �������� �������������� ������
				/** 
					\param p_list_FormInfo - ��������� �� ������, ���������� �����, ����������� � �������������� ������
				*/
				void	GetWords(/*out*/ std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_DictionaryIndex);	

				/// ��������� ����� � �������� �������������� ������
				/** 
					\param oTFormInfo - ��� ���������� �����, ������� ���������� ��������
					\return ��������� ��������� ���������� ��������
				*/
				bool	AddWord(/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex);

				/// ������� �����, ����������� � �������� �������������� ������ � ������������� � TFormInfo
				/** 
					\param oTFormInfo - ��� ���������� �����, ������� ���������� �������
					\return bool	- ��������� ��������
				*/
				bool	DeleteWord (/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex);
				
				/// ������� ������� ������������� ����� 
				bool	DeleteClass(SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber oDictionariesNumber);

				/// ������� ����� � ��������� � ���� �����
				/** 
					\param oTFormInfo - ��� ���������� �����, ������� ���������� ��������
					\return ��������� ����� ���������� ������
				*/
				int	CreateClassAndAddWord(/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex);


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
			private:
				/*! \var SS::CoSeDi::SQL::CCashCoSeDi								* m_pCashCoSeDi
				*  \brief	- ��������� �� ���     
				*/
				SS::CoSeDi::SQL::CCashCoSeDi				* m_pCashCoSeDi;	
			
			};

		};
		namespace DBMS
		{
			/// ����� ���������� �� ��������� � ���������� ������������� ���������� � ����� �� DBMS ����
			class CSemanticAnalysis : 
				public SS::Interface::Core::CoSeDi::ISemanticAnalysis,
				public SS::CoSeDi::DBMS::CConnect
			{
			public:
				/// �����������
				/** 
					\param SS::CoSeDi::DBMS::CCashCoSeDi*pCashCoSeDi - ��������� �� ���
					\param szBaseName - ��� ����
				*/
				CSemanticAnalysis(SS::CoSeDi::DBMS::CCashCoSeDi* pCashCoSeDi, const wchar_t* szBaseName, std::wstring wTableName) :
				  SS::CoSeDi::DBMS::CConnect(szBaseName), m_wDataTableName(wTableName)
				{
					m_pCashCoSeDi = pCashCoSeDi;
					m_SSemanticsAccess.DictionaryNumber = 0;
					m_SSemanticsAccess.IDClass = 0;
					m_SSemanticsAccess.IDSource = 0;
					TableRecord[0] = NULL;
					TableRecord[1] = NULL;
					TableRecord[2] = NULL;
				};
				/// ����������
				virtual ~CSemanticAnalysis(void)
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
					SS_TRY
					{
						SS::Core::CommonServices::CBaseCoreClass::SetLoadManager(pLoadManager);
						InitConnection();
					}
					SS_CATCH(L"")
					
				}

			public: // from SS::Interface::Core::CoSeDi::ISemanticAnalysis				

				/// ���������� ������ ������������� ������� �� ������� �����
				/** 
					\param oTFormInfo - ������ ������ �����
					\param p_list_OfClass - ��������� �� ������ �������� ������������� �������
				*/
				bool	GetClasses(/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex, /*out*/ std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_Class);

				/// ���������� ������ ����, ������� ��������� � �������� �������������� ������
				/** 
					\param p_list_FormInfo - ��������� �� ������, ���������� �����, ����������� � �������������� ������
				*/
				void	GetWords(/*out*/ std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_DictionaryIndex);	

				/// ��������� ����� � �������� �������������� ������
				/** 
					\param oTFormInfo - ��� ���������� �����, ������� ���������� ��������
					\return ��������� ��������� ���������� ��������
				*/
				bool	AddWord(/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex);

				/// ������� �����, ����������� � �������� �������������� ������ � ������������� � TFormInfo
				/** 
					\param oTFormInfo - ��� ���������� �����, ������� ���������� �������
					\return bool	- ��������� ��������
				*/
				bool	DeleteWord (/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex);
				
				/// ������� ������� ������������� ����� 
				bool	DeleteClass(SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber oDictionariesNumber);

				/// ������� ����� � ��������� � ���� �����
				/** 
					\param oTFormInfo - ��� ���������� �����, ������� ���������� ��������
					\return ��������� ����� ���������� ������
				*/
				int	CreateClassAndAddWord(/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex);

			
			private:
				/// ������������� ���������� � ���������				
				bool InitConnection();				
			private:
				/*! \var SS::CoSeDi::SQL::CCashCoSeDi								* m_pCashCoSeDi
				*  \brief	- ��������� �� ���     
				*/
				SS::CoSeDi::DBMS::CCashCoSeDi	* m_pCashCoSeDi;				

				SSemanticsAccess m_SSemanticsAccess;
				/*! \var void       * TableRecord[3];
				*  \brief     ������ ���������� �� ������, ���������� ������ � DBMS �������
				*/
				void* TableRecord[3];
				/*! \enum EFindMode
				*  \brief     ��������� ����, �� �������� ����� �������������� �����
				*/
				enum EFindMode
				{
					efmByIDClass,
					efmByIDSource
				};

				/*	��� �������	*/
				std::wstring m_wDataTableName;		
			};
		};
	};
};

