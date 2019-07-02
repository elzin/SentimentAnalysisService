#pragma once

#include "..\ASSInterface\ICoSeDi.h"
#include ".\SyntaxAnalysis.h"


namespace SS
{
	namespace CoSeDi
	{
		namespace SQL
		{
			class CSyntaxAnalysisEx : 
				public SS::Interface::Core::CoSeDi::ISyntaxAnalysis,
				public SS::Core::CommonServices::CBaseCoreClass
			{
			public:
				CSyntaxAnalysisEx(SS::CoSeDi::SQL::CCashCoSeDi*	pCashCoSeDi);
				~CSyntaxAnalysisEx(void);
			public:
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS_TRY
					{
						SS::Core::CommonServices::CBaseCoreClass::SetLoadManager( pLoadManager);

						m_oSyntaxAnalysisRus.SetLoadManager( pLoadManager);
						m_oSyntaxAnalysisEng.SetLoadManager( pLoadManager);
					}
					SS_CATCH(L"")
				}

			public:
				/// ������������� ������ ������ ��� ������
				/** 
					\param oIDSource - ������ ������ 
				*/
				void SetIDSource(SS::CoSeDi::DataTypes::TIDSource oIDSource)
				{
					SS::Interface::Core::CoSeDi::ISyntaxAnalysis::SetIDSource(oIDSource);
					m_oSyntaxAnalysisRus.SetIDSource(oIDSource);
					m_oSyntaxAnalysisEng.SetIDSource(oIDSource);

				};

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
				SS::CoSeDi::SQL::CSyntaxAnalysis m_oSyntaxAnalysisRus;
				SS::CoSeDi::SQL::CSyntaxAnalysis m_oSyntaxAnalysisEng;

			};
		};

		namespace DBMS
		{
			class CSyntaxAnalysisEx : 
				public SS::Interface::Core::CoSeDi::ISyntaxAnalysis,
				public SS::Core::CommonServices::CBaseCoreClass
			{
			public:
				CSyntaxAnalysisEx(SS::CoSeDi::DBMS::CCashCoSeDi*	pCashCoSeDi);
				~CSyntaxAnalysisEx(void);
			public:
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS_TRY
					{
						SS::Core::CommonServices::CBaseCoreClass::SetLoadManager( pLoadManager);

						m_oSyntaxAnalysisRus.SetLoadManager( pLoadManager);
						m_oSyntaxAnalysisEng.SetLoadManager( pLoadManager);
					}
					SS_CATCH(L"")
				}
			public:
				/// ������������� ������ ������ ��� ������
				/** 
					\param oIDSource - ������ ������ 
				*/
				void SetIDSource(SS::CoSeDi::DataTypes::TIDSource oIDSource)
				{
					SS::Interface::Core::CoSeDi::ISyntaxAnalysis::SetIDSource(oIDSource);
					m_oSyntaxAnalysisRus.SetIDSource(oIDSource);
					m_oSyntaxAnalysisEng.SetIDSource(oIDSource);

				};
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
				SS::CoSeDi::DBMS::CSyntaxAnalysis m_oSyntaxAnalysisRus;
				SS::CoSeDi::DBMS::CSyntaxAnalysis m_oSyntaxAnalysisEng;
			};
		};

	};
};