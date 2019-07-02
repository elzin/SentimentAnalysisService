#pragma once

#include "..\ASSInterface\ICoSeDi.h"

#include ".\BaseCashCoSeDi.h"

#include ".\connect.h"
#include ".\dboCoSeDi.h"

using namespace SS::CoSeDi::DataTypes;

namespace SS
{
	namespace CoSeDi
	{
		namespace SQL
		{
			/// SQL-��� TKC			
			class CCashCoSeDi : 
				public SS::Interface::Core::CoSeDi::ICoSeDiLoad, 
				public SS::CoSeDi::CBaseCashCoSeDi,
				public SS::CoSeDi::SQL::CConnect
			{
			public:
				/// ����������� 
				/** 
					\param szBaseName - ��� ����					
				*/
				CCashCoSeDi(const wchar_t * szBaseName) :  SS::CoSeDi::SQL::CConnect(szBaseName), m_bIsLoad(false)
				{
				}
				/// ����������
				virtual ~CCashCoSeDi(void)
				{
				}			
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
				/// ��������� ������ � ���
				/** 
					\param uiIDSource - ������ ������
					\param ewr - ������� � ������� ��������� ������
					\return bool - ��������� ���������� ��������
				*/
				bool AddIDSource(unsigned int uiIDSource, SS::CoSeDi::DataTypes::EWorkRegion ewr);
			private:										
				/// ��������� ������� SemanticClassesTree � �������� ���
				/** 
					\return bool - ��������� ���������� ��������
				*/
				bool ToBinarySemanticClassesTree();

				/// ��������� ������� SemanticClassesWords � �������� ���
				/** 
					\return bool - ��������� ���������� ��������
				*/
				bool ToBinarySemanticClassesWords();

				/// ��������� ������� SynonimsSemantics � �������� ���
				/** 
					\return bool - ��������� ���������� ��������
				*/
				bool ToBinarySynonimsSemantics();

				/// ��������� ������� Semantics � �������� ���
				/** 
					\return bool - ��������� ���������� ��������
				*/
				bool ToBinarySemantics();

				/// ��������� ������� SemanticsExtra � �������� ���
				/** 
					\return bool - ��������� ���������� ��������
				*/
				bool ToBinarySemanticsExtra();

				/// ��������� ��� � �������� ���
				/** 
					\return bool - ��������� ���������� ��������
				*/
				bool ToBinaryExistence();


				/// ��������� ������� Combinatory � ����� �������� ���
				/** 
					\return bool - ��������� ���������� ��������
				*/
				bool ToBinaryCombinatory();

				/// ��������� ������� CombinatoryExtra � ����� �������� ���
				/** 
					\return bool - ��������� ���������� ��������
				*/
				bool ToBinaryCombinatoryExtra();

				/// ��������� ������� CombiSynonyms � �������� ���
				/** 
					\return bool - ��������� ���������� ��������
				*/
				bool ToBinaryCombiSynonyms();

				/// ��������� ��������� � �������� ���
				/** 
					\return bool - ��������� ���������� ��������
				*/
				bool ToBinarySyntax();
				/// ��������� ������� SemanticIDSourceTree � �������� ���
				/** 
					\return bool - ��������� ���������� ��������
				*/
				bool ToBinarySemanticIDSourceTree();
			private:						
				/*! \var bool m_bIsLoad
				*  \brief     ��������� �������� �� ���
				*/
				bool m_bIsLoad;
			};
		};
///////////////////////////////////////////////////////////////////////////////////////////////////
		namespace DBMS
		{
			/// DBMS-��� TKC		
			class CCashCoSeDi : public SS::Interface::Core::CoSeDi::ICoSeDiLoad, 
				public SS::CoSeDi::CBaseCashCoSeDi,
				public SS::CoSeDi::DBMS::CConnect
			{
			public:
				/// ����������� 
				/** 
					\param szBaseName - ��� ����					
				*/
				CCashCoSeDi(const wchar_t * szBaseName) : SS::CoSeDi::DBMS::CConnect(szBaseName), m_bIsLoad(false)
				{
					m_SExistence.IDExistence = 0;
					m_SExistence.IDSource = 0;
				}				
				/// ����������
				virtual ~CCashCoSeDi(void)
				{		
				}							

			public: // function
				/// ������������� ��������� �� ������� �������� ����������
				/** 
					\param pLoadManager - ��������� �� ������� �������� ����������
				*/				
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS::Core::CommonServices::CBaseCoreClass::SetLoadManager(pLoadManager);
					InitConnection();
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
			private:						
				/// ������������� ���������� � ���������
				bool InitConnection();
			
			private:						
				/*! \var bool m_bIsLoad
				*  \brief     ��������� �������� �� ���
				*/
				bool m_bIsLoad;		

				/*! \var SS::CoSeDi::DataTypes::SExistence m_SExistence
				*  \brief     ��������� ������������ ������� ������ � �� �������������
				*/
				SS::CoSeDi::DataTypes::SExistence m_SExistence;
				/*! \var void* TableRecord[2];
				*  \brief     ������ ���������� �� ������, ���������� ������ � DBMS �������
				*/
				//--UNUSED-- void* TableRecord[2];	
				
			};
		};
	};
};

