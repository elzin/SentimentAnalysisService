#pragma once
#include "smcausemanner.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace IndexationExperts
			{
				namespace Russian
				{
				

				/// �������������� ������� � �������
				class CSMCauseMannerR :
					public CSMCauseManner
				{
				public:
					CSMCauseMannerR(void);
					~CSMCauseMannerR(void);
					bool AnalizeSentence();
				};

				}
			}
		}
	}
}