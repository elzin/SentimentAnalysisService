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
				/// ��������� ��������� � �������� � ������
				class CSMSubjectObjectE :
					public CSMSentenceExpert
				{
				public:
					CSMSubjectObjectE(void);
					~CSMSubjectObjectE(void);
					bool AnalizeSentence();
				};


			}

		}
	}
}