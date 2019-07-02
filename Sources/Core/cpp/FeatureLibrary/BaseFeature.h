#pragma once
#include <string>
#include <memory>
#include "BaseType.h"

namespace SS
{
	namespace Core
	{
		namespace Features
		{
			namespace Base
			{
				/// ������� ����� ��� ���� ������� �������������. �������� ����� ���������(��������������) ���������� ������� �������� ��� ���������� �������������
				class CBaseFeature
				{
				public:
					CBaseFeature(void);
					virtual ~CBaseFeature(void);

					/// ��������� �������� ����� ����������
					virtual	void Undefine();
					///������ ��� ���� ���-�� Undefined
					virtual bool IsUndefined() const;

					///��������� ���������� �������� �������� ���-��
					virtual void GetXMLValue(std::string& sXML) const = 0;
					///������������ �������� ���-�� �� ���������� ��������
					virtual void SetXMLValue(const std::string& sXML) = 0;

					///��������� ���������� �������� �������� ���-��
					virtual void ToString(std::string& s) const = 0;

					///��������� �������� ��������������, ��������������� � ����������� �����
					virtual unsigned int GetValue() const;
					///������������ �������� ���-�� �� ��������������� � ����� ��������
					virtual void SetValue(const unsigned int uiValue);

					/// "�������� = " - ����������� �������� ������� ������ ������-�� ����
					virtual void Assign(const CBaseFeature* pValue);

					/// "�������� == " - ���������� �� ��������� ������� ������ ������-�� ����
					virtual bool Equal(const CBaseFeature* pValue) const;
					/// "�������� &= " - ����������� �������� ������� ������ ������-�� ����
					virtual void AssignAND(const CBaseFeature* pValue, bool withoutUndef = false);
					/// "�������� |= " - ����������� �������� ������� ������ ������-�� ����
					virtual void AssignOR(const CBaseFeature* pValue, bool firstValue = false);

					/// �������������� ��������� ������������� (�������� �� ������ �������������� �������� ���������� ��������������)
					virtual bool IsIncludes(const CBaseFeature* pValue) const;

					/// �������������� ����������� ������������� (���� �� ���� ���� ����������� �������� � ���� �������������)
					virtual bool IsIntersectsWith(const CBaseFeature* pValue) const;

					virtual bool IsIntersectsWithout(const CBaseFeature* pValue) const;

					/// ����������� �������������
					virtual bool IsIntersectsOrEmpty(const CBaseFeature* pValue) const;

					/// ���������� � ���� (�������� ����� ��������� CBaseType)
					virtual std::auto_ptr<CBaseType> GetBaseType() const = 0; 

					//�������� �������� ������. �������� ������ (� ��������� ������ ����������)
					std::string GetPrintableDataDescription() const;
					
				protected:
					unsigned int m_value;
				};
			}
		}
	}
}