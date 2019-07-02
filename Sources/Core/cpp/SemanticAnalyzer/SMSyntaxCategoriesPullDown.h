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
				/// ������� ��������� ��������� � �������������� �������
				class CSMSyntaxCategoriesPullDown :
					public CSMSentenceExpert
				{
				public:
					CSMSyntaxCategoriesPullDown(void);
					~CSMSyntaxCategoriesPullDown(void);
					bool AnalizeSentence();
				private:
					/// ������� ��������
					UINT m_uiValue;
					/// ������� ����� ����
					UINT m_uiCurrentBitNumber;
					/// ������ ����� �� ���������
					UINT GetFirstCategoryValue();
					/// ��������� ������ ���������
					UINT GetNextCategoryValue();

					bool IsCategory(UINT uiSingleValue);
				};
			}
		}
	}
}