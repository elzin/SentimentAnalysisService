#pragma once
#include "./smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace English
			{
				/// ��������� ��������� �����������
				class CSMPassiveE :
					public CSMSentenceExpert
				{
				public:
					CSMPassiveE(void);
					~CSMPassiveE(void);
					bool AnalizeSentence();
					bool Init(IText * pIText);
				private:

					SS::Core::Features::CMorphoFeature m_MorphoFeature;
					/// ������ ������ ������� to be
					UINT m_uiBeSourceIndex;
					/// ������, ���� ����� - ����� ������� "be"
					bool IsBeForm(IUnit * pUnit);

				};

			}
		}
	}
}