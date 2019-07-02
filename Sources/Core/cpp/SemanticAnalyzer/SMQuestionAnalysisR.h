#pragma once
#include "smquestionanalysis.h"
#include "QuestionBase.h"


namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace Question
			{
				namespace Russian
				{


					/// ������ ������� ��� �������� �����
					class CSMQuestionAnalysisR :
						public CSMQuestionAnalysis
					{
					public:
						CSMQuestionAnalysisR(void);
						~CSMQuestionAnalysisR(void);
						bool AnalizeSentence();
						bool Init(IText * pIText);
						bool Init(CSMManager * pManager, SDescriptionInfo & DInfo);
						virtual bool AnalyseQuestion(EQuestionType eQType);
					protected:
						/// ������� �������� �����_��� �������
						map<UINT,EQuestionType> m_SourceTypeTable;
						/// ����� ��� �������� �� �������� �����
						set<UINT> m_s_WordToRemove;
						/// ������� ��� �������� �� �������� �����
						set<UINT> m_s_VerbToRemove;
						/// ����� - �������� ������� ��������������
						set<UINT> m_s_RusComplexQ;

						CSMQuestionAnalysisR * m_pRQKogda;
						CSMQuestionAnalysisR * m_pRQChto;
						CSMQuestionAnalysisR * m_pRQKakoi;
						CSMQuestionAnalysisR * m_pRQKto;
						CSMQuestionAnalysisR * m_pRQSkolko;

						/// ����������� ��������� (who or name )
						/** 
						\param pHead - ���� �������� ���� ��������� ���������
						\param oUnits - ������ �� ������� ������������ ���������
						\param bNameDef - ���������� �� name_def
						\return 	bool - ������, ���� ���������� name or who def 
						*/
						bool CheckWhoCategory(IUnit * pHead, IUnit * pUnits,bool & bNameDef);
						/// ���������� ��� �������  ��� ��������
						/** 
						\param tDescription - �������� �����������
						\param CExQuestionParser::TMorphoDescription::iterator - �������� �� �������� �����������. ��� ����������������� !
						\return 	CExQuestionParser::EQuestionType - ��� �������
						*/
						EQuestionType DetectQuestionTypeRussian();
						void MarkUnits(EQuestionType eQuestionType);
						void FillGroups();

						bool IsMorphologyCoordinated(IUnit * pU1, IUnit * pU2 , bool bCase, bool bGender , bool bNumber , bool bScipInstrumentalCase=false );

						bool CheckSubjectFin(IUnit * pHead);

						Types::SyntaxCategories LegacyCategoryToEntity(IUnit * pUnit, IUnit * pVerb);

						void MoveToAjunct(IUnit * pGroup);

						/// ������������� ��������� ������� ������� - � eareGlobalKtoChtoWhoWhatQuestion, ��� �������� � "�������������"
						void SetDefQuestion() 
						{ 
							if(GetAnalyseParams())
							{
								if((GetAnalyseParams()->GetAnalyseMod()==SS::Core::Types::eamQuery)&&
									(GetAnalyseParams()->GetCurrentSystemMode() == SS::Core::Types::ecsmGlobal))
									GetAnalyseParams()->SetAnalyseResultEx(SS::Core::Types::IndexationSearch::TSearchParams::saEncyclopedia);
							}else
							{
								SAVE_LOG(SS_ERROR AND L"GetAnalyseParams() == NULL" AND __WFUNCTION__);
							}
						} ;

					};


				}
			}
		}
	}
}