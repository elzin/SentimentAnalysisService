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


/// ������ ������� � ������� ���������������
class CRQSimpleAdjunct :
	virtual public CSMQuestionAnalysisR
{
public:
	CRQSimpleAdjunct(void);
	~CRQSimpleAdjunct(void);
	bool AnalyseQuestion(EQuestionType eQType);
};


				}
			}
		}
	}
}