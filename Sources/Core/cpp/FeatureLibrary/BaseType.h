#pragma once

namespace SS
{
	namespace Core
	{
		namespace Features
		{
			namespace Base
			{
				/// ������� ����� ��� ���� �������, �������� ���������� � ���� �������������� (���, ���-�� � ����� ��������, ��������� ��������)
				class CBaseType
				{
				public:
					CBaseType(void);
					virtual ~CBaseType(void);

					//virtual unsigned int GetValueCount() = 0;
					///��������� ����� ����
					virtual const char* GetTypeName()  const = 0;
					///��������� ���������� �������� ����
					virtual const char* GetTypeDescription()  const = 0;
					//virtual const char* GetValueName(unsigned int n) = 0;
					//virtual const char* GetValueDescription(unsigned int n) = 0;

					///��������� ���-�� �������� (��� �����)
					virtual unsigned int GetValueCount() const {return 0;};
					//virtual const char* GetTypeName(){return "";};
					//virtual const char* GetTypeDescription(){return "";};
					///��������� ����� �������� �� ������ ��������
					virtual const char* GetValueName(unsigned int n) const {return "";};
					///��������� ���������� �������� �������� �� ������
					virtual const char* GetValueDescription(unsigned int n) const {return "";};
				};
			}
		}
	}
}