#pragma once
#include "semanticfeature.h"

namespace SS
{
	namespace Core
	{
		namespace Features
		{
			///����� ��������������� �������������, ��� �������� �������
			class CSemanticFeatureAposteriori :
				public CSemanticFeature
			{
			public:
				CSemanticFeatureAposteriori(void);
				~CSemanticFeatureAposteriori(void);
				CSemanticFeatureAposteriori& operator = (const CSemanticFeatureAposteriori& value)
				{
					Assign(&value);
					return *this;
				}
				CSemanticFeatureAposteriori(const CSemanticFeatureAposteriori& value){
					Init();
					*this = value;
				};

				///������ ��������� ��� ��������������
				const char* GetFeatureName() const {return "SemanticFeatureAposteriori";};
				///������ ��������� �������� ��������������
				const char* GetFeatureDescription() const {return "����� ������������� �������������, ��� �������� �������";};

				///�������������� ��������������
				///����������� �������� ��� ������� ��������������� ���������������
				Types::OperationMod	m_OperationMod;
				///����� �������� �� �������� ���������� ������������ ���������
				Types::TShiftSemantic m_ShiftSemantic;
				///�������� �� ��������� ��� ShiftSemantic
				enum { DEF_SHIFT = 1000 };

			private:
				void Init();
			};
		}
	}
}