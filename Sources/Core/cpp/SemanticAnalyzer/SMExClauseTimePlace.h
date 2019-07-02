#pragma once
#include "smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace IndexationExperts
			{
				class CSMExClauseTimePlace : public CSMSentenceExpert
				{
				public:
					CSMExClauseTimePlace(void);
					~CSMExClauseTimePlace(void);
					bool AnalizeSentence();
					bool Init(IText * pIText);
				protected:
					/// �����, ��� ���� � ������  () 
					set<wstring> m_Words;
					/// ���������� ��� ����� �������
					/** 
					\param sWord - ����� 
					\return 		bool - ������, ���� �������
					*/
					bool IsWord(const TCHAR * sWord);

					void SetSintaxCategoryToUnit(TBoxUnits l_units);
				};
			}
		}
	}
}

