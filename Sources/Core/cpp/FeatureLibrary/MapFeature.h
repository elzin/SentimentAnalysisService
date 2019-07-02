#pragma once
#include "basefeature.h"
#include "XMLReader.h"



#pragma warning (disable : 4267)
namespace SS
{
	namespace Core
	{
		namespace Features
		{
using namespace SS::Core::Features::Base;
			namespace Base
			{
				/// ��������������, ��������������� ��� �������� "���"-������������� (������ ���� (�����������, �������� ��������� ����� ��������� ��������))
				template <
					/// ������ � ����� ����, ���������������� ��� �������� �����-�������� � �������
					unsigned char nBitSize
					/// ����� ���������� ����������� ��������������� ��������� ��������
					, unsigned char nValues
					/// ��� ������, ����������� �� �������� ���������� � ������ (���-��, ����� ��������, ��������� ��������)
					, class TType> class CMapFeature :
					public CBaseFeature
 				{
					static unsigned int m_MaxValue;
				public:
					CMapFeature()
					{
						Undefine();
					};

					CMapFeature(
						///����� �������� ����(����� ����), ������ �������� � 1
						const unsigned char value)
					{
						SetSingleValue(value);
						//unsigned int m_MaxValue(1 << nValues);

						//if(value < m_MaxValue){
						//	m_value = value;
						//}
						//else{
						//	char bff1[20];
						//	char bff2[20];
						//	TType oType;
						//	
						//	SS_THROW((char*)oType.GetTypeName() AND " ����������� Value ������ �����������" AND "MaxMapValue = " AND ltoa(m_MaxValue, bff1, 10) AND " value = " AND ltoa(value, bff2, 10));
						//}
					};

					CMapFeature(
						///�������� ������-�� ����, ������� ����� ��������� ���� ��������������
						const CMapFeature<nBitSize, nValues, TType>& value)
					{
						unsigned int  m_MaxValue((unsigned int)1 << nValues);
						if(value.m_value < m_MaxValue || m_MaxValue==0)
						{
							m_value = value.m_value;
						}
						else
						{
							wchar_t wcBuff1TypeName[100];
							wchar_t bff1[20];
							wchar_t bff2[20];
							TType oType;
							
							mbstowcs(wcBuff1TypeName, (char*)oType.GetTypeName() , strlen(oType.GetTypeName()));
			
							SS_THROW(wcBuff1TypeName AND \
									L" ����������� Value ������ �����������" AND \
									L"MaxMapValue = " AND \
									_ltow_s(m_MaxValue, bff1, 20, 10) AND \
									L" value = " AND \
									_ltow_s(value.m_value, bff2, 20, 10));
						}
					};

					virtual ~CMapFeature(void){};

					///����� �������� �������������� �� Undefined
					void Undefine()
					{
						m_value = 0x00000001;
					};

					///������ ��� ���� ���-�� Undefined
					bool IsUndefined() const
					{
						return (m_value == 0x00000001);
					};

					void FillUp()
					{
						unsigned int m_MaxValue((unsigned int)1 << nValues);
						if(m_MaxValue)
						{
							m_value = m_MaxValue - 1;
						}
						else
						{
							m_value = 0xFFFFFFFF;
						}
					}

					///��������� ���������� �������� ���-��
					void GetValueDescription(std::string& s) const
					{
						TType oType;
						CXMLReader oReader;
						oReader.GetMapDescription(&oType, m_value, s);
					}

					///��������� ���������� �������� ���-��
					std::string GetValueDescription() const
					{
						std::string s;
						TType oType;
						CXMLReader oReader;
						oReader.GetMapDescription(&oType, m_value, s);

						return s;
					};


					///��������� ���������� �������� �������� ���-��
					void GetXMLValue(std::string& sXML) const
					{
						TType oType;
						CXMLReader oReader;
						oReader.GetMapXMLValue(&oType, m_value, sXML);
					};

					///������������ �������� ���-�� �� ���������� ��������
					void SetXMLValue(const std::string& sXML){
						TType oType;
						CXMLReader oReader;
						m_value = 0;
						oReader.SetMapXMLValue(&oType, &m_value, sXML);
						if(m_value == 0)
							m_value = 1;
					};

					///��������� ���������� �������� �������� ���-��
					void ToString(std::string& s) const
					{
						TType oType;
						CXMLReader oReader;
						oReader.GetMapString(&oType, m_value, s);
					};

					///��������� ���������� �������� �������� ���-��
					std::string ToString() const
					{
						std::string s;
						TType oType;
						CXMLReader oReader;
						oReader.GetMapString(&oType, m_value, s);

						return s;
					};

					/////��������� �������� ��������������, ��������������� � ����������� �����
					//unsigned int GetValue() const
					//{
					//	return 0;
					//};
					///������������ �������� ���-�� �� ��������������� � ����� ��������
					void SetValue(const unsigned int uiValue)
					{
						unsigned int m_MaxValue((unsigned int)1 << nValues);
						if(uiValue < m_MaxValue || m_MaxValue==0)
						{
							m_value = uiValue;
						}
						else
						{
							TType oType;

							wchar_t wcBuff1TypeName[100];
							wchar_t wcBuff1[20];
							wchar_t wcBuff2[20];					
							mbstowcs(wcBuff1TypeName, (char*)oType.GetTypeName() , strlen(oType.GetTypeName()));

							SS_THROW( wcBuff1TypeName \
									AND L" SetValue Value ������ �����������" \
									AND L"MaxMapValue = " \
									AND _itow_s(m_MaxValue, wcBuff1, 20, 10) \
									AND L" value = " \
									AND _itow_s(uiValue, wcBuff2, 20, 10) );
							//��������

							SS_THROW(L"");
						}
					};

					///������������� �������� ���� ����� ucValue � 1, ���� ��������� � 0
					/**
						������ ������� ������������� ��� �������������� �� ��������
						�.�. �� �������� �� ������� ������������� ���� ��������
						���� ����� ���� ������ ����������� �����������, ��������� ���������
					*/
					void SetSingleValue(unsigned char ucValue)
					{
						if(ucValue < nValues)
						{
							m_value = 0;
							SetBit(ucValue, 1);
						}
						else
						{
							m_value = 0;
							SetBit(0, 1);
							/*TType oType;

							wchar_t wcBuff1TypeName[100];
							wchar_t bff1[20];
							wchar_t bff2[20];					
							mbstowcs(wcBuff1TypeName, (char*)oType.GetTypeName() , strlen(oType.GetTypeName()));

							SS_THROW(wcBuff1TypeName AND \
									L" SetSingleValue Value ������ �����������" AND \
									L"nValues = " AND \
									_ltow(nValues, bff1, 10) AND \
									L" value = " AND \
									_ltow(ucValue, bff2, 10));*/
						}
					}

					///������ �������� (����� ����, ������� == 1), ��������������� ��� ������ � �������
					/**
						���� � 1 ����� ����� ������ ����, ��������� ���������
					*/
					unsigned char GetSingleValue() const
					{
						unsigned char i = 0;
						unsigned char ucRet = 0xFF;
						while(i < nValues)
						{
							unsigned char ucBit = GetBit(i);
							if(ucBit)
							{
								if(ucRet == 0xFF){
									ucRet = i;
								}
								else
								{
									TType oType;
									wchar_t wcBuff1TypeName[100];
									//wchar_t bff1[20];
									mbstowcs(wcBuff1TypeName, (char*)oType.GetTypeName() , strlen(oType.GetTypeName()));

									//��������
									/*SS_THROW(wcBuff1TypeName AND \
										L" ��� ������� ��������� ������ ���� �������� ������� ���������� ���, ������� � 1, m_value = " AND \
										_ltow(m_value, bff1, 10));*/
								}
							}
							i++;
						}

						if(ucRet == 0xFF)
						{
							TType oType;

							wchar_t wcBuff1TypeName[100];
							wchar_t bff1[20];
							mbstowcs(wcBuff1TypeName, (char*)oType.GetTypeName() , strlen(oType.GetTypeName()));
		
							SS_THROW(wcBuff1TypeName AND \
									L" ��� ������� ��������� ������ ���� �������� ���������� �����, ������� � 1, m_value = " AND \
									_ltow_s(m_value, bff1, 20, 10));
							return 0;
						}
						else
						{
							return ucRet;
						}
					}

					/// "�������� == " - ���������� �� ��������� ������� ������ ������-�� ����
					bool Equal(const CMapFeature<nBitSize, nValues, TType>& Value) const
					{
						return (m_value == Value.m_value);
					}
					/// "�������� = " - ����������� �������� ������� ������ ������-�� ����
					void Assign(const CMapFeature<nBitSize, nValues, TType>& Value)
					{
						m_value = Value.m_value;
					};

					///����������� - �������� �� ���� ��� �������� . ���� ��������� ����� 1 , �� �������, ��� �� ����������, ��� ��� �������� ���� 1 ������������� - ������������.
					bool IsContain(const CMapFeature<nBitSize, nValues, TType>& Value) const
					{
						return ((m_value&(Value.m_value))>1);
					};

					/// �������� ���� �������� value 
					void Remove(const CMapFeature<nBitSize, nValues, TType>& Value)
					{
						unsigned int temp=~Value.m_value;
						m_value &= temp;
					};

				std::auto_ptr<CBaseType> GetBaseType() const { return std::auto_ptr<CBaseType>(new TType()); }
	         
				///���������� �� ������� �����
				unsigned char GetValuesNumber() const
				{
				unsigned char RetVal = 0;

				for( unsigned int Value = m_value; Value; Value >>= 1 )
					RetVal += Value & 0x1; 

				return RetVal;
				}

				/// ������ � ����� ����, ���������������� ��� �������� �����-�������� � �������
				static unsigned char GetBitSize() { return nBitSize; }

				/// ����� ���������� ����������� ��������������� ��������� ��������
				static unsigned char GetValesCount() { return nValues; }

				protected:
					///������ �������� ���� ��� ������� n
					unsigned char GetBit(unsigned int n) const
					{
						return ((m_value >> n) & 0x00000001);
					};

					///��������� �������� ���� ��� ������� n � ucBit (0 ��� 1)
					void SetBit(unsigned int n, unsigned char ucBit)
					{
						unsigned int i = 0x00000001;
						i = i << n;
						if(ucBit)
						{
							m_value |= i;
						}
						else
						{
							i = ~i;
							m_value &= i;
						}
					};

				};


				//����� ������������� ��������� �������� ���� �������� CMapFeature::GetSingleValue �
				//��� ������� ���� ���� �������� ����� ������ (CMapFeature::GetSingleValue � ����� ������ 
				//������ ����������)
				class TMapFeatureSingleValueIterator
				{
					unsigned int m_Mask;
					unsigned char m_SingleValue;
		         
				public:
					TMapFeatureSingleValueIterator(): m_Mask(0), m_SingleValue(0) {}
					explicit TMapFeatureSingleValueIterator( const CBaseFeature &BaseFeature ) { Init(BaseFeature); }
		            
					//������������� ����� ������� ��������.
					//��������� BaseFeature ����� ������� Init �� ����������������  
					void Init( const CBaseFeature &BaseFeature )
					{
					m_Mask = BaseFeature.GetValue(); 
					m_SingleValue = 0;

					Next();
					}

					//������� � ���������� ��������
					void Next()
					{
					//��� ������ ������ ���������� �������� Undefined
					do
					{
						m_Mask >>= 1; 
						++m_SingleValue;
					}
					while( m_Mask && !(m_Mask & 0x1) ); //���� ���� ������� � ���� ������� ��� �� �������
					}

					//����������� �� ��������
					bool IsEnd() const { return !m_Mask; }

					//������� ��������
					unsigned char GetSingleValue() const { return m_SingleValue; }

					//��������� �������� BaseFeature, ��� ����� 
					//CMapFeature::GetSingleValue() == TMapFeatureSingleValueIterator::GetSingleValue()
					void SetValueTo( CBaseFeature &BaseFeature ) const { BaseFeature.SetValue( 0x1 << GetSingleValue() ); } 
				};
			}
		}
	}
}
#pragma warning (default : 4267)
