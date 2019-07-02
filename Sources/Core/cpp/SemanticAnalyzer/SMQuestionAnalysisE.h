#pragma once
#include "smquestionanalysis.h"
#include "MoAmbResolver.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace Question
			{
				namespace English
				{

					class CSMQuestionAnalysisE :
						public CSMQuestionAnalysis
					{
					public:
						CSMQuestionAnalysisE(void);
						~CSMQuestionAnalysisE(void);
						bool AnalizeSentence();
						bool Init(IText * pIText);
					private:

						UINT m_uiToBeSourceIndex;

						CMoAmbResolver m_MoAmbResolver;

						/// ������� - �����_��� �������
						map<wstring,EQuestionType> m_StringQTypeTableEng;

						EQuestionType DetectQuestionType();
						void MarkUnits(EQuestionType eQuestionType);
						bool IsBe(IUnit * pUnit=NULL);

						void FillGroups();

						/// ����� ���������������� � ���������� ���� + �������
						/** 
						\param oUnits - ������ ������
						\param oSemanticFeature - ������������� ����
						\param l_SemValues - ������ ������������� �����
						\return 	bool - ������, ���� � ���������������� ���� ���������

						������� ����� ����� ������ ��������������� �� ��������
						*/
						bool FindMeasurePrep(IUnit * pUnits,SS::Core::Features::CSemanticFeature& oSemanticFeature,list<long>& l_SemValues);
						/// ����������� ��������� (who or name )
						/** 
						\param pHead - ���� �������� ���� ��������� ���������
						\param oUnits - ������ �� ������� ������������ ���������
						\param bNameDef - ���������� �� name_def
						\return 	bool - ������, ���� ���������� name or who def 
						*/
						bool CheckWhoCategory(IUnit * pHead, IUnit * pUnits,bool & bNameDef);
						/// ���� ������ � ������� � ������� �������� ��� ����
						void CorrectPassiveEnglish();

					};


				}
			}
		}
	}
}