#pragma once
#include "morphofeature.h"

namespace SS
{
	namespace Core
	{
		namespace Features
		{
			///����� ��������������� ������������� ��� �������������� ������� �����������
			class CMorphoFeatureApriori :
				public CMorphoFeature
			{
			public:
				CMorphoFeatureApriori(void);
				~CMorphoFeatureApriori(void);
				CMorphoFeatureApriori& operator = (const CMorphoFeatureApriori& value)
				{
					Assign(&value);
					return *this;
				}
				CMorphoFeatureApriori(const CMorphoFeatureApriori& value){
					Init();
					*this = value;
				};

				///������ ��������� ��� ��������������
				const char* GetFeatureName() const {return "MorphoFeatureApriori";};
				///������ ��������� �������� ��������������
				const char* GetFeatureDescription() const {return "����� ��������������� ������������� ��� �������������� ������� �����������";};

			//�������������� ��������������
				/// ���������������� ������ ��������������� ���������
				Types::Uniqueness					m_Uniqueness;
				/// ������ �� ������ �������������� �������������� � ����������� ���	������ �������������
				Types::ExistenceMod				m_ExistenceMod;
				/// ����� ������� ��������������� �������������
				Types::TDetectWordAnalyzeMode		m_DetectWordAnalyzeMode;
			private:
				void Init();
			};

		}
	}
}