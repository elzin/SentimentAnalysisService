#pragma once

#include "..\ASSInterface\ICoSeDi.h"

#include ".\CashCoSeDiEx.h"
#include ".\Combinatory.h"
#include ".\SemanticanAlysisEx.h"
#include ".\SemanticClassesTreeEx.h"
#include ".\SemanticAnalysis.h"
#include ".\SyntaxanAlysisex.h"
#include ".\SemanticClassesTree.h"
#include ".\SemanticClassesWords.h"

#include ".\SemanticIDSourceTreeEx.h"


namespace SS
{
	namespace CoSeDi
	{
		/*! \enum EDataBaseType
		*  \brief     ������ ��������� ����� ��� ������ 
		*/
		enum EDataBaseType
		{
			edbtDBMS,
			edbtSQL
		} ;

		/// ��������� ������ ���������� SS::Interface::Core::CoSeDi::ICoSeDiManager
		class CCoSeDiManager : public SS::Interface::Core::CoSeDi::ICoSeDiManager
		{
		public:			
			/// �����������
			/** 
				\param szBaseName - ��� ����, � ������� ����� ��������
			*/
			CCoSeDiManager();
			/// ����������
			~CCoSeDiManager(void);
		public: // from SS::Interface::IBase 
			///������������
			ULONG Release();
			///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
			HRESULT QueryInterface(REFIID pIID, void** pBase); 
		public: // from SS::SMInterface::IWorkWithManagerConnections
			/// ������������� ��������� �� ������� �������� ���������� 
			/** 
				\param pLoadManager - ��������� �� ������� �������� ����������
			*/
			void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager) 			
			{
				SS::Core::CommonServices::CBaseCoreClass::SetLoadManager(pLoadManager);
			}
		public: 
				/// ���������� �������� ��� �������� �������
				SS::Interface::Core::CoSeDi::ICoSeDiLoad                  * GetLoader();
				///	���������� �������� ��� �������������� �������	
				SS::Interface::Core::CoSeDi::ISemanticAnalysis            * GetSemanticAnalysis();
				///	���������� �������� ��� ��������������� �������
				SS::Interface::Core::CoSeDi::ISyntaxAnalysis              * GetSyntaxAnalysis();
				///	���������� �������� ��� ������ � ������� ������������� �������	
				SS::Interface::Core::CoSeDi::ISemanticClassesTree         * GetSemanticClassesTree();
				///	���������� �������� ��� ������ � ��������, ���������� � ������� ������������� �������	
				SS::Interface::Core::CoSeDi::ISemanticClassesWords        * GetSemanticClassesWords();
				///	���������� �������� ��� ������ � �������������� ��������� ���������� �����	
				SS::Interface::Core::CoSeDi::ISemanticIDSourceTree        * GetSemanticIDSourceTree();
				///	���������� �������� ��� �������������� ������� ��� ������ � �������������� ����������
				SS::Interface::Core::CoSeDi::ISemanticAnalysis            * GetCombiSynonimsAnalysis();
				///	���������� �������� ��� �������������� �������	
				SS::Interface::Core::CoSeDi::ISemanticAnalysis            * GetRestaurantSemanticAnalysis();
				///	���������� �������� ��� �������������� ������� ��� ������ � ����������
				SS::Interface::Core::CoSeDi::ISemanticAnalysis            * GetSynonimsSemanticAnalysis();
				///	���������� �������� ��� �������������� �������	
				SS::Interface::Core::CoSeDi::ICombinatory                 * GetCombinatory();
				///	���������� �������� ��� �������������� ������� (���. ������������� �������)	
				SS::Interface::Core::CoSeDi::ICombinatory                 * GetCombinatoryExtra();
		
				
		private:
			/*! \enum m_eDataBaseType - ��� ���� */
			EDataBaseType m_eDataBaseType;
			/*! \var m_pCashCoSeDiDBMS
			*  \brief     ��� ��� ������ � DBMS ������ ���
			*/
			SS::CoSeDi::DBMS::CCashCoSeDiEx         * m_pCashCoSeDiDBMS;

			/*! \var m_pCashCoSeDiSQL
			*  \brief  ��� ��� ������ � SQL ������ ���
			*/
			SS::CoSeDi::SQL::CCashCoSeDiEx          * m_pCashCoSeDiSQL;

			/*! \var m_pSyntaxAnalysisDBMS
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::DBMS::CSyntaxAnalysis
			*/
			SS::CoSeDi::DBMS::CSyntaxAnalysisEx     * m_pSyntaxAnalysisDBMS;
			
			/*! \var m_pSyntaxAnalysisSQL
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::SQL::CSyntaxAnalysis
			*/
			SS::CoSeDi::SQL::CSyntaxAnalysisEx      * m_pSyntaxAnalysisSQL;
			
			/*! \var m_pCombinatory
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::CCombinatory
			*/
			SS::CoSeDi::DBMS::CCombinatory          * m_pCombinatory;

			/*! \var m_pCombinatoryExtra
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::CCombinatory (���. ������������� �������)
			*/
			SS::CoSeDi::DBMS::CCombinatory          * m_pCombinatoryExtra;
			
			/*! \var m_pSemanticAnalysisDBMS
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::DBMS::CSemanticAnalysisEx
			*/
			SS::CoSeDi::DBMS::CSemanticAnalysisEx   * m_pSemanticAnalysisDBMS;

			/*! \var m_pSemanticAnalysisExtraDBMS
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::DBMS::CSemanticAnalysisEx (���. ������������� �������)
			*/
			SS::CoSeDi::DBMS::CSemanticAnalysisEx   * m_pSemanticAnalysisExtraDBMS;
			
			/*! \var m_pSemanticAnalysisSQL
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::SQL::CSemanticAnalysisEx
			*/
			SS::CoSeDi::SQL::CSemanticAnalysisEx    * m_pSemanticAnalysisSQL;

			/*! \var m_pSemanticAnalysisExtraSQL
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::SQL::CSemanticAnalysisEx (���. ������������� �������)
			*/
			SS::CoSeDi::SQL::CSemanticAnalysisEx    * m_pSemanticAnalysisExtraSQL;

			/*! \var m_pSemanticAnalysis
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::CSemanticAnalysis
			*/
//			SS::CoSeDi::CSemanticAnalysis * m_pSemanticAnalysis;
			
			/*! \var m_pSemanticClassesTree
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::CSemanticClassesTree
			*/
			SS::CoSeDi::CSemanticClassesTree        * m_pSemanticClassesTree;

			/*! \var m_pSemanticClassesWord
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::CSemanticClassesWords
			*/
			SS::CoSeDi::CSemanticClassesWords       * m_pSemanticClassesWords;

//			! \var m_pSemanticClassesTreeDBMS
//			  \brief - ��������� �� ������ ������ SS::CoSeDi::DBMS::CSemanticClassesTree
//			/
//			SS::CoSeDi::DBMS::CSemanticClassesTreeEx * m_pSemanticClassesTreeDBMS;

//			! \var m_pSemanticClassesTreeSQL
//			  \brief - ��������� �� ������ ������ SS::CoSeDi::SQL::CSemanticClassesTree
//			/
//			SS::CoSeDi::SQL::CSemanticClassesTreeEx  * m_pSemanticClassesTreeSQL;

			/*! \var m_pSemanticIDSourceTreeDBMS
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::DBMS::CSemanticIDSourceTree
			*/
			SS::CoSeDi::DBMS::CSemanticIDSourceTreeEx* m_pSemanticIDSourceTreeDBMS;
			
			/*! \var m_pSemanticIDSourceTreeSQL
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::SQL::CSemanticIDSourceTree
			*/
			SS::CoSeDi::SQL::CSemanticIDSourceTreeEx * m_pSemanticIDSourceTreeSQL;
			
			/*! \var m_pSemanticAnalysisDBMS
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::DBMS::CSemanticAnalysisEx
			*/
			SS::CoSeDi::DBMS::CSemanticAnalysisEx    * m_pSemanticCombiSynonimsDBMS;
			
			/*! \var m_pSemanticAnalysisSQL
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::SQL::CSemanticAnalysisEx
			*/
			SS::CoSeDi::SQL::CSemanticAnalysisEx     * m_pSemanticCombiSynonimsSQL;

			/*! \var m_pSemanticAnalysisDBMS
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::DBMS::CSemanticAnalysisEx
			*/
			SS::CoSeDi::DBMS::CSemanticAnalysisEx    * m_pSemanticAnalysisSynonimsDBMS;
			
			/*! \var m_pSemanticAnalysisSQL
			*  \brief - ��������� �� ������ ������ SS::CoSeDi::SQL::CSemanticAnalysisEx
			*/
			SS::CoSeDi::SQL::CSemanticAnalysisEx     * m_pSemanticAnalysisSynonimsSQL;
			

			///*! \var m_szBaseName
			//*  \brief - ������, ���������� ��� ����
			//*/
			//char m_szBaseName[100];

		};
	};

};
