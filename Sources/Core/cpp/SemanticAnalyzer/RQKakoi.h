#pragma once
#include "smquestionanalysisr.h"

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

/// ������ ������� "�����"
class CRQKakoi :
	virtual public CSMQuestionAnalysisR
{
public:
	CRQKakoi(void);
	~CRQKakoi(void);
	bool AnalyseQuestion(EQuestionType eQType);
};


				}
			}
		}
	}
}