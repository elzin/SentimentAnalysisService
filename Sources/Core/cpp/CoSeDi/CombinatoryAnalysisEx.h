#pragma once

#include "..\ASSInterface\ICoSeDi.h"
#include ".\CashCoSeDiEx.h"
#include ".\CombinatoryAnalysis.h"


namespace SS
{
	namespace CoSeDi
	{
		namespace SQL
		{

			class CCombinatoryAnalysisEx : 
				public SS::Interface::Core::CoSeDi::ICombinatoryAnalysis,
				public SS::Core::CommonServices::CBaseCoreClass

			{
			public:
				CCombinatoryAnalysisEx(SS::CoSeDi::SQL::CCashCoSeDiEx*	pCashCoSeDi);
				~CCombinatoryAnalysisEx(void);
			public:

				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS_TRY;
					SS::Core::CommonServices::CBaseCoreClass::SetLoadManager( pLoadManager);

					m_oCombinatoryAnalysisRus.SetLoadManager( pLoadManager);
					m_oCombinatoryAnalysisEng.SetLoadManager( pLoadManager);


					SS_CATCH(L"");
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
				SS::CoSeDi::SQL::CCombinatoryAnalysis m_oCombinatoryAnalysisRus;
				SS::CoSeDi::SQL::CCombinatoryAnalysis m_oCombinatoryAnalysisEng;
			};

		};

		namespace DBMS
		{

			class CCombinatoryAnalysisEx : 
				public SS::Interface::Core::CoSeDi::ICombinatoryAnalysis,
				public SS::Core::CommonServices::CBaseCoreClass
			{
			public:
				CCombinatoryAnalysisEx(SS::CoSeDi::DBMS::CCashCoSeDiEx*	pCashCoSeDi);
				~CCombinatoryAnalysisEx(void);
			public:

				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS_TRY;
					SS::Core::CommonServices::CBaseCoreClass::SetLoadManager( pLoadManager);

					m_oCombinatoryAnalysisRus.SetLoadManager( pLoadManager);
					m_oCombinatoryAnalysisEng.SetLoadManager( pLoadManager);


					SS_CATCH(L"");
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
				SS::CoSeDi::DBMS::CCombinatoryAnalysis m_oCombinatoryAnalysisRus;
				SS::CoSeDi::DBMS::CCombinatoryAnalysis m_oCombinatoryAnalysisEng;
			};

		};
	};
};

