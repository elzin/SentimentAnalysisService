#pragma once
#include "smadverbialmodifier.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace Russian
			{
/// ��������� � ������ ������������� ����� � ������� �� ��������� 
class CSMAdverbialModifierR :
	public CSMAdverbialModifier
{
public:
	CSMAdverbialModifierR(void);
	~CSMAdverbialModifierR(void);
	bool AnalizeSentence();
protected:
	/// ��������� ��������� ����� � ��������
	void AddGenetiveRussian(TBoxUnits & l_Units);
};


			}
		}
	}
}