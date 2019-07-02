#pragma once

#include "./smsentenceexpert.h"

#include ".\questionframework.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace Question
			{

				/// ��� ������� �� ��������������� �����
				enum EQuestionType
				{
					eqtNon,
					// English
					eqtEWhat,
					eqtEWhen,
					eqtEWhere,
					eqtEHow,
					eqtEWho,
					eqtEWhy,
					//Russian
					eqtRKto,
					eqtRChto,
					eqtRKogda,
					eqtRKuda,
					eqtROtkuda,
					eqtRGde,
					eqtRKakoi,
					eqtRKakova , 
					eqtRSkolko , 
					eqtRKak,
					eqtRKakManner,
					eqtRPochemu,
					eqtROther
				};



				/// ����� ��������� ������� �������
				class CSMQuestionAnalysis :
					public CSMSentenceExpert
				{
				public:
					CSMQuestionAnalysis(void);
					~CSMQuestionAnalysis(void);
					bool Init(IText * pIText);

					friend class CQuestionBase;

				protected:
					CQuestionFrameWork m_Frame;

					SS::Dictionary::Types::TDictionaryIndex m_semNumber;
					SS::Dictionary::Types::TDictionaryIndex m_semName;
					SS::Dictionary::Types::TDictionaryIndex m_semBecome;
					SS::Dictionary::Types::TDictionaryIndex m_semVPossess;
					SS::Dictionary::Types::TDictionaryIndex m_semVBe;
					SS::Dictionary::Types::TDictionaryIndex m_semLastName;
					SS::Dictionary::Types::TDictionaryIndex m_semFirstName;
					/// �������� �������
					struct SDescriptionInfo {
						/// ��������� �� ��������������� ������
						IUnit* _pAux;
						/// ��������� �� ������ t� be
						IUnit* _pToBe;
						/// ��������� ��  ������
						IUnit* _pVerb;
						/// ��������� �� �������
						IUnit* _pPrep;
						IUnit* _pQuestion;
						IUnit* _pMainEntity;
						IUnit* _pAdditionalEntity;
						IUnit* _pPredicate;
						/// �������������
						void Init(){ _pPrep=NULL; _pAux=NULL; _pVerb=NULL; _pToBe=NULL; _pAdditionalEntity=_pMainEntity=_pQuestion=_pPredicate=NULL; };
						SDescriptionInfo(){ Init(); };
					} m_DInfo;/// 1 ���������� ����� ����


					SMorphoDescription * GetUnitDescription(SS::Interface::Core::BlackBox::IUnit* pUnit=NULL);
					void AddUnitDescription(SS::Interface::Core::BlackBox::IUnit* pUnit,SMorphoDescription & oDescription );


					/// ���������� ������������ �������
					/** 
					\param pUnit - �������
					\return 	bool - ������ - ���� ����������
					*/
					bool IsLegalLexem(IUnit* pUnit);

					/// ��������� �������� �����������
					void ProcessSentence();

					/// ���������� ��������������� ��������� �����
					void AddAllPlaceSemantic(IUnit * pHead);
					void AddAllOrganisationSemantic(IUnit * pHead);
					void AddAllTimeIntervalSemantic(IUnit * pHead);
					void AddAllPersonSemantic(IUnit * pHead, bool bCountry=true);
					void AddAllPersonSemanticInAnimate(IUnit * pHead);
					void AddAcroCitationSemantic(IUnit * pHead);

					/// ������������� ��������� � ����������� �� �������� � ���� ��������������
					/** 
					\param pHead - ���� �������� ���������� ���������
					\param pPrep - ���� � ���������
					\param bPlace - ������, �������������� �����; ����, �������������� �������
					*/
					void SetSyntaxFiltered(IUnit* pHead,IUnit* pPrep,bool bPlace);

					/// ��������� ������������� ��� �����
					void AddToBeIndex(IUnit* pHead,Types::TSVBeType tsType);
					/// ��������� ������������� ��� �����
					void SetToBeIndex(IUnit* pHead,Types::TSVBeType tsType);

					/// ��������� ��������� �������
					/** 
					\param pVerb - ������
					\param oSemanticFeature - ������������ ���������
					\param l_SemValues - ������������ ���������
					\return 	bool - ���� ���� ���������

					�������������� ��������� - ������, ������
					*/
					bool ProcessVerbSemantic(IUnit* pVerb,SS::Core::Features::CSemanticFeature& oSemanticFeature,list<SS::Dictionary::Types::TDictionaryIndex>& l_SemValues);

					/// ����������� ��������� (who or name )
					/** 
					\param pHead - ���� �������� ���� ��������� ���������
					\param oUnits - ������ �� ������� ������������ ���������
					\param bNameDef - ���������� �� name_def
					\return 	bool - ������, ���� ���������� name or who def 
					*/
					bool CheckWhoCategory(IUnit * pHead, IUnit * pUnits,bool & bNameDef);
					/// ��������� ���� �������� ��������� adjunct 
					/** 
					\param pUnit - ���� 
					*/
					void SetSingleSyntax(IUnit* pUnit);

					/// ������������� ��������� ������� ������� - � eareGlobalKtoChtoWhoWhatQuestion, ��� �������� � "�������������"
					/*void SetDefQuestion() 
					{ 
						//if (m_pBlackboard->GetAnalyseParams()->GetAnalyseMod()==SS::Core::Types::eamRTFQuery)
						//	m_pBlackboard->GetAnalyseParams()->SetAnalyseResultEx(SS::Core::Types::eareGlobalKtoChtoWhoWhatQuestion);	
					} ;*/

					void StrictQuery();

					void SimpleQuery();

					void MoveUnitToPredicate(IUnit * pUnit, IUnit * pAfter);



				};


			}
		}
	}
}