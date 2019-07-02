#pragma once

#include "IntegerFeature.h"
namespace SS
{
	namespace Core
	{
		namespace Features
		{
			namespace Base
			{
				/// �������������� ���� "�������", ��������� �������� �� 0 �� 100
				template <class TType> class CPercentFeature :
					public CIntegerFeature<TType>
				{
				public:
					CPercentFeature()
					{
						SetValue(0);
					};

					CPercentFeature(const unsigned int value)
					{
						SetValue(value);
					};
					///������������ �������� ���-�� �� ��������������� � ����� ��������
					void SetValue(const unsigned int uiValue){
						if(uiValue <= 100){
							m_value = uiValue;
						}
						else{
							SS_THROW(L"����������� �������� ���� ������� 100");
						}
					}

					/// "�������� = " - ����������� �������� ������� ������ ������-�� ����
					void Assign(const CBaseFeature* pValue){
						SetValue(pValue->GetValue());
					};

					/// "�������� &= " - ����������� �������� ������� ������ ������-�� ����
					void AssignAND(const CBaseFeature* pValue){SS_THROW(L"������������ ��������");};
					/// "�������� |= " - ����������� �������� ������� ������ ������-�� ����
					void AssignOR(const CBaseFeature* pValue){SS_THROW(L"������������ ��������");};

					/// �������������� ��������� ������������� (�������� �� ������ �������������� �������� ���������� ��������������)
					bool IsIncludes(const CBaseFeature* pValue) const {
						return Equal(pValue);
					};

					/// �������������� ����������� ������������� (���� �� ���� ���� ����������� �������� � ���� �������������)
					bool IsIntersectsWith(const CBaseFeature* pValue) const {
						return Equal(pValue);
					};
				};
			}
		}
	}
}
