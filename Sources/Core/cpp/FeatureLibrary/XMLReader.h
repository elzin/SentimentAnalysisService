#pragma once

#include "BaseType.h"
#include <string>

namespace SS
{
	namespace Core
	{
		namespace Features
		{
			namespace Base
			{
				///�����, ��������������� ��� ������������ ������/������ ��� ������ ��������
				class CXMLReader
				{
				public:
					CXMLReader(void);
					~CXMLReader(void);

					///��������� ���������� �������� �������� ���-��
					void GetMapXMLValue(CBaseType* pBaseType, unsigned int value, std::string& sXML) const;
					///������������ �������� ���-�� �� ���������� ��������
					void SetMapXMLValue(CBaseType* pBaseType, unsigned int* p_value, const std::string& sXML);

					///��������� ���������� �������� ���-��
					void GetMapString(CBaseType* pBaseType, unsigned int value, std::string& s) const;

					///��������� ���������� �������� �������� ��������������
					void GetMapDescription(CBaseType* pBaseType, unsigned int value, std::string& s) const;

					///��������� ���������� �������� �������� ���-��
					void GetIntegerXMLValue(CBaseType* pBaseType, unsigned int value, std::string& sXML) const;
					///������������ �������� ���-�� �� ���������� ��������
					void SetIntegerXMLValue(CBaseType* pBaseType, unsigned int* p_value, const std::string& sXML);
				protected:

					///������ ������ - ��������� ����
					void AppendTypeHeader(CBaseType* pBaseType, std::string& s) const;
					///������ ������ - ����������� ���
					void AppendTypeEnd(CBaseType* pBaseType, std::string& s) const;

					///������ ������ - ��������� �������� ��� ������� n
					void AppendValueHeader(unsigned int n, CBaseType* pBaseType, std::string& s) const;
					///������ ������ - ����������� �������� ��� ������� n
					void AppendValueEnd(unsigned int n, CBaseType* pBaseType, std::string& s) const;
					///������ ��������� ������ ���, ������� ��������� �������� ������ ��������������
					void GetTypeXMLRegion(CBaseType* pBaseType, const std::string& sXML, std::string& s);
					///������ �������� ����, ���������� �� ��� ������
					unsigned int GetValueXMLValue(unsigned int n, CBaseType* pBaseType, std::string& sXML) const;

					///������ �������� ���� ��� ������� n
					unsigned char GetBit(unsigned int value, unsigned int n) const;

					///��������� �������� ���� ��� ������� n
					void SetBit(unsigned int* p_value, unsigned int n, unsigned char ucBit);
				};
			}
		}
	}
}