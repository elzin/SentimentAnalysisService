#pragma once

#include "basefeature.h"
#include "XMLReader.h"
namespace SS
{
	namespace Core
	{
		namespace Features
		{
			namespace Base
			{
				/// ��������������, ��������� ������� ������� unsigned int ��������
				template <class TType> class CIntegerFeature :
					public CBaseFeature
				{
				public:
					CIntegerFeature(void)
					{
						m_value = 0;
					};

					CIntegerFeature(const unsigned int value)
					{
						m_value = value;
					};

					~CIntegerFeature(void)
					{
					};

					//�������� ���������� � ����
					operator const unsigned int( ) const 
					{
						return m_value;
					}

					///��������� ���������� �������� �������� ���-��
					void GetXMLValue(std::string& sXML) const
					{
						TType oType;
						CXMLReader oReader;
						oReader.GetIntegerXMLValue(&oType, m_value, sXML);
					};

					///������������ �������� ���-�� �� ���������� ��������
					void SetXMLValue(const std::string& sXML){
						TType oType;
						CXMLReader oReader;
						oReader.SetIntegerXMLValue(&oType, &m_value, sXML);
					};

					///��������� ���������� �������� �������� ���-��
					void ToString(std::string& s) const
					{
						char bff[20];
						s = _ltoa_s(m_value, bff, 20, 10);
					};

				std::auto_ptr<CBaseType> GetBaseType() const { return std::auto_ptr<CBaseType>(new TType()); }
				};
			}
		}
	}
}