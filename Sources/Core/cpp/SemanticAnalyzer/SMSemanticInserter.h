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
				/// �������� ������������� ������� �������������� ������ (��� �������� when, where )
				class CSMSemanticInserter :
					public CSMSentenceExpert
				{
				public:
					CSMSemanticInserter(void);
					~CSMSemanticInserter(void);
					bool AnalizeSentence();
					bool Init(IText * pIText);
				private:

					list<SS::Dictionary::Types::TDictionaryIndex> m_l_SemanticIndicesTime;
					list<SS::Dictionary::Types::TDictionaryIndex> m_l_SemanticIndicesPlace;
					list<SS::Dictionary::Types::TDictionaryIndex> m_l_SemanticIndicesOrganization;
					long m_lsemNumber;


				};
			}

		}
	}
}