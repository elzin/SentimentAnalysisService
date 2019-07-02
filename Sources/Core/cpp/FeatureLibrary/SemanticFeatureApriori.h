#pragma once
#include "semanticfeature.h"

namespace SS
{
	namespace Core
	{
		namespace Features
		{
			///����� ��������������� ������������� ��� �������������� ������� �����������
			class CSemanticFeatureApriori :
				public CSemanticFeature
			{
			public:
				CSemanticFeatureApriori(void);
				~CSemanticFeatureApriori(void);
				CSemanticFeatureApriori& operator = (const CSemanticFeatureApriori& value)
				{
					Assign(&value);
					return *this;
				}
				CSemanticFeatureApriori(const CSemanticFeatureApriori& value){
					Init();
					*this = value;
				};

				///������ ��������� ��� ��������������
				const char* GetFeatureName() const {return "SemanticFeatureApriori";};
				///������ ��������� �������� ��������������
				const char* GetFeatureDescription() const {return "����� ������������� ������������� ��� �������������� ������� �����������";};

			   //�������������� ��������������
				/// ���������������� ������ ��������������� ���������
				Types::Uniqueness					m_Uniqueness;
				/// ������ �� ������ �������������� �������������� � ����������� ���	������ �������������
				Types::ExistenceMod				m_ExistenceMod;
			private:
				void Init();
			};

		}
	}
}