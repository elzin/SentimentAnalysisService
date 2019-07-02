#pragma once
#include "SMSentenceExpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace PostAnalysisExperts
		{
			namespace PostSyntaxAnalysis
			{
			/// ��������� ��������������� �������
			class CSMQuestionParser :
				public CSMSentenceExpert
			{
			public:
				CSMQuestionParser(void);
				~CSMQuestionParser(void);

				bool AnalizeSentence();
				bool Init(IText * pIText);

			private:
				/// ���� �����
				set<wstring> m_StopWords;
				/// ������� ���������_����
				typedef map<UINT,IUnit*> TCategoryUnitTable;
				/// ��� �������
				enum EQuestionType
				{
					eqtNon,
					eqtWhat,
					eqtWhen,
					eqtWhere,
					eqtHow,
					eqtWho,
					eqtWhy
				};
				
				///������������� ��� �����
				SS::Dictionary::Types::TDictionaryIndex m_questSemNumber;
				///������������� ��� �����
				SS::Dictionary::Types::TDictionaryIndex m_questSemFirstName;
				///������������� ��� 2-�� �����
				SS::Dictionary::Types::TDictionaryIndex m_questSemLastName;
				///������������� ��� ��������������
				SS::Dictionary::Types::TDictionaryIndex m_questSemNationality;
				///������������� ��� �����
				//SS::Dictionary::Types::TDictionaryIndex m_questSemBecome;*/
				/// ������� �������������� �����_��� �������
				map<wstring,CSMQuestionParser::EQuestionType> m_QuestionTypeEng;
				/// ������� ��������������� ������ ������� to be
				set<wstring> m_ToBeLiteral;
				/// ������� ���������_����
				TCategoryUnitTable m_CategoryUnitTable;

				/// �������� ��������� ������� ����������� �����
				/** 
					\param pSentence - ����������� � ��������
					\return 			bool - ������, ���� ������ ��������� ���������
				*/
				bool SelectQuestionEnglish(ISentence * pSentence);
				/// ��������� ����������
				/** 
					\param pSentence - ����������� 
				*/
				void ProcessSentence(ISentence * pSentence);
				/// ����������� ��������� ��������� 
				/** 
					\param pHead - ����, �������� ����������� ���������
					\param pGroup - ������ �� ��������� ������� ��������� �������������
					\return bool - ������, ���� ��������� �����������
				*/
				bool CheckWhoCategory(IUnit * pHead, IUnit * pGroup);

				bool CheckWhoCategoryProcess(IUnit * pHead, IUnit * pUnit, IUnit * pGroup=NULL);

				/// ����������� ��������� ��������� 
				/** 
				\param pHead - ����, �������� ����������� ���������
				\param pGroup - ������ �� ��������� ������� ��������� �������������
				\return bool - ������, ���� ��������� �����������
				*/
				bool CheckWhatCategory(IUnit * pHead, IUnit * pGroup);

				bool CheckWhatCategoryProcess(IUnit * pHead, IUnit * pUnit, IUnit * pGroup=NULL);

				/// ������� ������������� ������� �� ������
				/** 
					\param pGroup - ������
				*/
				void PopSemantic(IUnit * pGroup);

				/// ��������� ������������� ����
				/** 
					\param pSentence - �����������
					\param pGroup - ������ �������������� ����
					\param eQType - ��� �������
				*/
				void AdjunctMeasureProcess(ISentence * pSentence, IUnit * pGroup,CSMQuestionParser::EQuestionType eQType);
				/// ��������� ��������� ��������
				/** 
					\param pSentence - �����������
					\param pGroup - ������
					\param eQType - ��� �������
				*/
				void SubjectFinProcess(ISentence * pSentence,IUnit * pGroup,CSMQuestionParser::EQuestionType eQType);
				/// ��������� ��������� SubjectComplement
				/** 
				\param pGroup - ������
				\param eQType - ��� �������
				*/
				void SubjectComplementProcess(IUnit * pGroup,CSMQuestionParser::EQuestionType eQType);
				/// ��������� ��������� �������
				/** 
				\param pSentence - �����������
				\param pGroup - ������
				\param eQType - ��� �������
				*/
				void ObjectProcess(ISentence * pSentence, IUnit * pGroup,CSMQuestionParser::EQuestionType eQType);
				/// ��������� ��������� AjunctTimeDuration
				/** 
				\param pSentence - �����������
				\param pGroup - ������
				\param eQType - ��� �������
				*/
				void AjunctTimeDurationProcess(ISentence * pSentence,IUnit * pGroup,CSMQuestionParser::EQuestionType eQType);
				/// ��������� ��������� Ajunct 
				/**
				\param pSentence - �����������
				\param pGroup - ������
				\param eQType - ��� �������
				*/
				void AjunctProcess(ISentence * pSentence, IUnit * pGroup,CSMQuestionParser::EQuestionType eQType);

				/// ��������� ������� �� �������� ������
				bool KeyQuestionProcess();
				/// ����� � ��������� �������� �� ������
				void FindAndMovePretext(ISentence * pSentence,IUnit * pGroup);

				void MoveToAgjunct(ISentence * pSentence,IUnit * pUnit);

				bool CheckManyMuch(IUnit * pGroup);

				bool CheckAimSemSyntAndMoveToAjunct(ISentence * pSentence,IUnit * pGroup, const Types::SyntaxCategories & oCategory, CSMQuestionParser::EQuestionType eQType);

				/// ��������� ������������� ������ ����� 
				/** 
				\param pUnit - ����
				\param oSemType - ������������� ���
				*/
				void AddSemanticIndex(IUnit * pUnit, SS::Dictionary::Types::TDictionaryIndex & oSemType);
				/// ��������� ����� ��� ������������� ������� ��������������� ��������� �������
				void AddAllTimeIntervalSemantic(IUnit * pUnit);
				/// ��������� ����� ��� ������������� ������� ��������������� ��������� �����
				void AddAllPlaceSemantic(IUnit * pUnit);
				/// ��������� ����� ��� ������������� ������� ��������������� ��������� �������
				void AddAllPersonSemantic(IUnit * pUnit);
				/// ��������� ����� ��� ������������� ������� ��������������� ��������� �������, �� ������ �����!
				void AddAllPersonNameSemantic(IUnit * pUnit);
				/// ��������� ���������� �� �������� ������ ��� ������� what
				/// ���������� true, ���� � ������ ���� ��������� Person
				bool SuperstructureSupport(IUnit * pGroup);
				/// ���������� ������, ��� ������� �����(����) ���������������
				bool IsNoun(IUnit * pUnit);

				bool IsSemanticUndef(SS::Core::Features::CSemanticFeature oSemanticFeature, bool & bPersonUndef, bool & bMeasureUndef);

				void SetDefQuestion() 
				{ 
					if(GetAnalyseParams())
					{
						if((GetAnalyseParams()->GetAnalyseMod()==SS::Core::Types::eamQuery) &&
							(GetAnalyseParams()->GetCurrentSystemMode() == SS::Core::Types::ecsmGlobal))
							GetAnalyseParams()->SetAnalyseResultEx(SS::Core::Types::IndexationSearch::TSearchParams::saEncyclopedia);
					}else
					{
						SAVE_LOG(SS_ERROR AND L"GetAnalyseParams() == NULL" AND __WFUNCTION__);
					}
					//if (m_pBlackboard->GetAnalyseParams()->GetAnalyseMod()==SS::Core::Types::eamRTFQuery)
					//	m_pBlackboard->GetAnalyseParams()->SetAnalyseResultEx(SS::Core::Types::eareGlobalKtoChtoWhoWhatQuestion);	
				} ;
				bool IsFindCall(IUnit * pUnit);
				bool IsFindMainDie();
				void CorrectFuncForPersonServiceSem(IUnit * pHead, IUnit * pUnit,SS::Core::Features::CSemanticFeature oSemanticFeature);

			};
			}
		}
	}
}