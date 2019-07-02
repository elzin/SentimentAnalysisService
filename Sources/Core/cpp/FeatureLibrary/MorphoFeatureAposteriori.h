#pragma once
#include "morphofeature.h"

namespace SS
{
	namespace Core
	{
		namespace Features
		{
			///����� ��������������� �������������, ��� �������� �������
			class CMorphoFeatureAposteriori :
				public CMorphoFeature
			{
			public:
				CMorphoFeatureAposteriori(void);
				~CMorphoFeatureAposteriori(void);
				CMorphoFeatureAposteriori& operator = (const CMorphoFeatureAposteriori& value)
				{
					Assign(&value);
					return *this;
				}
				CMorphoFeatureAposteriori(const CMorphoFeatureAposteriori& value){
					Init();
					*this = value;
				};

				///������ ��������� ��� ��������������
				const char* GetFeatureName() const {return "MorphoFeatureAposteriori";};
				///������ ��������� �������� ��������������
				const char* GetFeatureDescription() const {return "����� ��������������� �������������, ��� �������� �������";};

			//�������������� ��������������
				/// ����������� �������� ��� ������� ��������������� ���������������
				Types::OperationMod	m_OperationMod;
			private:
				void Init();
			};
		}
	}
}