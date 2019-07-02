#include "StdAfx.h"
#include ".\xmlreader.h"
#pragma warning (disable : 4267)


namespace SS
{
	namespace Core
	{
		namespace Features
		{
			namespace Base
			{
				CXMLReader::CXMLReader(void)
				{
				}

				CXMLReader::~CXMLReader(void)
				{
				}

				///��������� ���������� �������� �������� ���-��
				void CXMLReader::GetIntegerXMLValue(CBaseType* pBaseType, unsigned int value, std::string& sXML) const
				{
					sXML= "";
					AppendTypeHeader(pBaseType, sXML);
					sXML+= "=\"";
					sXML+= pBaseType->GetTypeDescription();
					sXML+= "\">\n";
						sXML+= "	";
						AppendValueHeader(0, pBaseType, sXML);
						sXML+= "=\"";
						sXML+= pBaseType->GetValueDescription(0);
						sXML+= "\">";
						char bff[20];
						sXML+= ltoa(value, bff, 10);
						AppendValueEnd(0, pBaseType, sXML);
						sXML+= "\n";

					AppendTypeEnd(pBaseType, sXML);
					sXML+= "\n";
				}

				///������������ �������� ���-�� �� ���������� ��������
				void CXMLReader::SetIntegerXMLValue(CBaseType* pBaseType, unsigned int* p_value, const std::string& sXML)
				{
					////��� ������ ���� ������, � ������� ��������� ���� �� ������� ����
					std::string s = sXML;
					//GetTypeXMLRegion(pBaseType, sXML, s);

					//if(s.empty()){
					//	SS_THROW(L"�� ������� ������ �������������� � ��� ������: " AND pBaseType->GetTypeName() AND " � � ����� " AND sXML.c_str())
					//}

						unsigned int ulValue = GetValueXMLValue(0, pBaseType, s);
						if(ulValue == 0xFFFFFFFF){
							SS_THROW(L"�� ������� ���� �� �������� �������������� � ��� ������: " AND pBaseType->GetTypeName() AND " � � ����� " AND sXML.c_str())
						}
						*p_value = ulValue;
				}

				///��������� ���������� �������� �������� ���-��
				void CXMLReader::GetMapXMLValue(CBaseType* pBaseType, unsigned int value, std::string& sXML) const
				{
					unsigned int nValues = pBaseType->GetValueCount();
					//unsigned int i = 0;
					unsigned int i = 1;
					sXML= "";
					AppendTypeHeader(pBaseType, sXML);
					sXML+= "=\"";
					sXML+= pBaseType->GetTypeDescription();
					sXML+= "\">\n";
					while(i < nValues){
						sXML+= "	";
						AppendValueHeader(i, pBaseType, sXML);
						sXML+= "=\"";
						sXML+= pBaseType->GetValueDescription(i);
						sXML+= "\">";
						sXML+= GetBit(value, i) ? "1" : "0";
						AppendValueEnd(i, pBaseType, sXML);
						sXML+= "\n";
						i++;
					}

					AppendTypeEnd(pBaseType, sXML);
					sXML+= "\n";
				};

				///������������ �������� ���-�� �� ���������� ��������
				void CXMLReader::SetMapXMLValue(CBaseType* pBaseType, unsigned int* p_value, const std::string& sXML)
				{
					//��� ������ ���� ������, � ������� ��������� ���� �� ������� ����
					std::string s;
					GetTypeXMLRegion(pBaseType, sXML, s);

					if(s.empty()){
						SS_THROW(L"�� ������� ������ �������������� � ��� ������: " AND pBaseType->GetTypeName() AND " � � ����� " AND sXML.c_str())
					}

					unsigned int nValues = pBaseType->GetValueCount();
					unsigned int i = 1;
					//unsigned int i = 0;
					while(i < nValues){
						unsigned char ucBit = GetValueXMLValue(i, pBaseType, s);
						if(ucBit == 0xFF){
							SS_THROW(L"�� ������� ���� �� �������� �������������� � ��� ������: " AND pBaseType->GetTypeName() AND " � � ����� " AND sXML.c_str())
						}
						SetBit(p_value, i, ucBit);
						i++;
					}

				};

				///��������� ���������� �������� ���-��
				void CXMLReader::GetMapString(CBaseType* pBaseType, unsigned int value, std::string& s) const
				{
					unsigned int nValues = pBaseType->GetValueCount();
					unsigned int i = 0;
					s = "";

					while(i < nValues){
						if(GetBit(value, i)){
							s+= pBaseType->GetValueName(i);
							s+= " ";
						}
						i++;
					}
				}

				///��������� ���������� �������� �������� ���-��
				void CXMLReader::GetMapDescription(CBaseType* pBaseType, unsigned int value, std::string& s) const
				{
					unsigned int nValues = pBaseType->GetValueCount();
					unsigned int i = 0;
					s = "";

					while(i < nValues){
						if(GetBit(value, i)){
							s+= pBaseType->GetValueDescription(i);
							s+= " ";
						}
						i++;
					}
				}

				///������ ������ - ��������� ����
				void CXMLReader::AppendTypeHeader(CBaseType* pBaseType, std::string& s) const
				{
					s+= "<";
					s+= pBaseType->GetTypeName();
					s+= " group";
				}
				///������ ������ - ����������� ���
				void CXMLReader::AppendTypeEnd(CBaseType* pBaseType, std::string& s) const
				{
					s+= "</";
					s+= pBaseType->GetTypeName();
					s+= ">";
				}
				///������ ������ - ��������� �������� ��� ������� n
				void CXMLReader::AppendValueHeader(unsigned int n, CBaseType* pBaseType, std::string& s) const
				{
					s+= "<";
					s+= pBaseType->GetValueName(n);
					s+= " type";
				}
				///������ ������ - ����������� �������� ��� ������� n
				void CXMLReader::AppendValueEnd(unsigned int n, CBaseType* pBaseType, std::string& s) const
				{
					s+= "</";
					s+= pBaseType->GetValueName(n);
					s+= ">";
				}

				///������ ��������� ������ ���, ������� ��������� �������� ������ ��������������
				void CXMLReader::GetTypeXMLRegion(CBaseType* pBaseType, const std::string& sXML, std::string& s)
				{
					s = "";
					std::string sType = "";
					AppendTypeHeader(pBaseType, sType);

					int pos = sXML.find(sType);

					if(pos == - 1) return;
					pos = sXML.find(">", pos);
					if(pos == - 1) return;

					sType.clear();
					AppendTypeEnd(pBaseType, sType);

					int posEnd = sXML.find(sType, pos);
					if(posEnd == - 1) return;

					s = sXML.substr(pos + 1, posEnd - pos - 1);
				};

				///������ �������� ����, ���������� �� ��� ������
				unsigned int CXMLReader::GetValueXMLValue(unsigned int n, CBaseType* pBaseType, std::string& sXML) const
				{
					std::string sType = "";
					AppendValueHeader(n, pBaseType, sType);
					int pos = sXML.find(sType);
					if(pos == - 1){
						return 0xFFFFFFFF;
					}
					pos = sXML.find(">", pos);
					if(pos == - 1){
						return 0xFFFFFFFF;
					}

					sType.clear();
					AppendValueEnd(n, pBaseType, sType);

					int posEnd = sXML.find(sType, pos);
					if(posEnd == - 1){
						return 0xFFFFFFFF;
					}

					std::string s;
					s = sXML.substr(pos + 1, posEnd - pos - 1);
					return (unsigned int)atol(s.c_str());
				}

				///������ �������� ���� ��� ������� n
				unsigned char CXMLReader::GetBit(unsigned int value, unsigned int n) const
				{
					return ((value >> n) & 0x00000001);
				};

				///��������� �������� ���� ��� ������� n
				void CXMLReader::SetBit(unsigned int* p_value, unsigned int n, unsigned char ucBit)
				{
					unsigned int i = 0x00000001;
					i = i << n;
					if(ucBit){
						(*p_value) |= i;
					}
					else{
						i = ~i;
						(*p_value) &= i;
					}
				};

			}
		}
	}
}
#pragma warning (default : 4267)
