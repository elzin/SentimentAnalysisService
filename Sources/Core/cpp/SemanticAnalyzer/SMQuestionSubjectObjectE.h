#pragma once
#include "./smsentenceexpert.h"

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
					/// ��������� ��������� � �������� � �������
					class CSMQuestionSubjectObjectE :
						public CSMSentenceExpert
					{
					public:
						CSMQuestionSubjectObjectE(void);
						~CSMQuestionSubjectObjectE(void);
						bool AnalizeSentence();
					};
				}
			}

		}
	}
}