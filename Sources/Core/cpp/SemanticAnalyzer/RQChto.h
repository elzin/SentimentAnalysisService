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

/// ����� ������� "���"
class CRQChto :
	public CSMQuestionAnalysisR
{
public:
	CRQChto(void);
	~CRQChto(void);
	bool AnalyseQuestion(EQuestionType eQType);
private:
	void DeleteSemantic(IUnit * pUnit);
	void RemoveSubjectObjectIndicesFromUnit();
	void RemoveSubjectObjectIndices(IUnit * pUnit);
};


				}
			}
		}
	}
}