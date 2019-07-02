#pragma once
#include "SMSentenceExpert.h"
#include ".\smmanager.h"

namespace SS
{
	namespace Semantic
	{
		namespace PostAnalysisExperts
		{
			namespace QueryGeneration
			{
				/// ��������� ����� ������� ������ �� ������� ���������������� �������
				class CSMVerbFormCorrector :
					public CSMSentenceExpert
				{
				public:
					CSMVerbFormCorrector(void);
					~CSMVerbFormCorrector(void);
					bool AnalizeSentence();
					bool Init(IText * pIText);
				private:
					/// ������� ��������������� ����� ������� to be
					set<wstring> m_ToBeForms;
					/// ��������� � �������
					SS::Interface::Core::Dictionary::IMorphologyAnalyser * m_pDictionaryInterface;
					
					/// ��������� ����� �������
					void CorrectForm(IUnit * pUnit, IUnit * pAux, bool bPast);

					bool IsVerb(IUnit * pUnit);

				};
			}

		}
	}
}