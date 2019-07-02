#pragma once
#include "./smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{

			/// ��������� �������������� �����
			class CSMFeatureCompute :
				public CSMSentenceExpert
			{
			public:
				CSMFeatureCompute(void);
				~CSMFeatureCompute(void);

				bool AnalizeSentence();
				bool Init(IText * pIText);

			private:
				/// ������, ���� ������� ����� - much,many
				bool m_bMuchMany;
				/// ��������� 
				//long m_semAgent;
				long m_semLastName;
				long m_semFirstName;
				long m_semPlaceIndf;
				/// ��������� ������������� ����������� 
				void ProcessEngFeature(SS::Core::Features::CMorphoFeature & oMorphoFeature);
				/// ��������� ������������� �������� 
				void ProcessRusFeature(SS::Core::Features::CMorphoFeature & oMorphoFeature);
				void Up2SymbolNextLastName();
			};


		}
	}
}