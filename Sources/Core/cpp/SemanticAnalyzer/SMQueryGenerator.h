#pragma once
#include ".\smmanager.h"
#include "SMSentenceExpert.h"
namespace SS
{
	namespace Semantic
	{
		namespace PostAnalysisExperts
		{
			namespace QueryGeneration
			{
				/// ���������� ������ ������� ��������� �������
				class CSMQueryGenerator :
					public CSMSentenceExpert
				{
				public:
					CSMQueryGenerator(void);
					~CSMQueryGenerator(void);
					bool AnalizeSentence();
					bool Init(IText * pIText);
					/// ��������� ������ ������� ����������
					wstring GetResultQuery(){ return m_sResultQuery; };
				private:
					/// ������ � �������� ����������
					wstring m_sResultQuery;
					SS::Interface::Core::Dictionary::IMorphologyAnalyser * m_pDictionaryInterface;
					/// ����� ������� to be
					set<wstring> m_ToBeForms;
					/// ���� �����
					set<wstring> m_StopWords;

					/// ������ - � ������ ����������
					void ToString();
					/// ��������� ��� ����� - ���� �����
					bool IsStopWord(const TCHAR * sWord);
					//void QuestionProcess(IUnit * pUnit);
					void FillWord(IUnit* pUnit, wstring & wWord);
					bool IsRusDef(IUnit* pUnit);
					///������������ ������ �������
					void ToStringAll();
					///�������� ����� ��� �� �������������� �����
					bool IsQuestion(IUnit* pUnit);

				};
			}
		}
	}
}