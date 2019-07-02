#include "StdAfx.h"
#include ".\basefeature.h"

namespace SS
{
	namespace Core
	{
		namespace Features
		{
			namespace Base
			{
				CBaseFeature::CBaseFeature(void) : m_value(0)
				{
				}

				CBaseFeature::~CBaseFeature(void)
				{
				}

				/// ��������� �������� ����� ����������
				void CBaseFeature::Undefine()
				{
					m_value = 0;
				}

				///������ ��� ���� ���-�� Undefined
				bool CBaseFeature::IsUndefined() const
				{
					return (m_value == 0);
				};


				///��������� �������� ��������������, ��������������� � ����������� �����
				unsigned int CBaseFeature::GetValue() const
				{
					return m_value;
				}
				///������������ �������� ���-�� �� ��������������� � ����� ��������
				void CBaseFeature::SetValue(const unsigned int uiValue)
				{
					m_value = uiValue;
				}

				/// "�������� = " - ����������� �������� ������� ������ ������-�� ����
				void CBaseFeature::Assign(const CBaseFeature* pValue)
				{
					m_value = pValue->m_value;
				}

				/// "�������� == " - ���������� �� ��������� ������� ������ ������-�� ����
				bool CBaseFeature::Equal(const CBaseFeature* pValue) const
				{
					return (m_value == pValue->m_value);
				}
				/// "�������� &= " - ����������� �������� ������� ������ ������-�� ����
				void CBaseFeature::AssignAND(const CBaseFeature* pValue, bool withoutUndef/* = false*/)
				{
					if (withoutUndef && IsUndefined())
						Assign(pValue);
					else
						m_value &= pValue->m_value;
				}
				/// "�������� |= " - ����������� �������� ������� ������ ������-�� ����
				void CBaseFeature::AssignOR(const CBaseFeature* pValue, bool firstValue/* = false*/)
				{
                    if(!firstValue)
					    m_value |= pValue->m_value;
                    else
                        Assign(pValue);
				}

				/// �������������� ��������� ������������� (�������� �� ������ �������������� �������� ���������� ��������������)
				bool CBaseFeature::IsIncludes(const CBaseFeature* pValue) const
				{
					return ((m_value & pValue->m_value) == pValue->m_value);
				}

				/// �������������� ����������� ������������� (���� �� ���� ���� ����������� �������� � ���� �������������)
				bool CBaseFeature::IsIntersectsWith(const CBaseFeature* pValue) const
				{
					return ((m_value & pValue->m_value) != 0);
				}

				bool CBaseFeature::IsIntersectsWithout(const CBaseFeature* pValue) const
				{
					return (((m_value>>1) & (pValue->m_value>>1)) != 0);
				}

				/// ����������� �������������
				bool CBaseFeature::IsIntersectsOrEmpty(const CBaseFeature* pValue) const
				{
					if( m_value == 1 )
						return true;
					return ((m_value & pValue->m_value) != 0);
				}

				std::string CBaseFeature::GetPrintableDataDescription() const
				{
					std::string Out;
					unsigned int Value = GetValue();
					std::auto_ptr<CBaseType> pType(GetBaseType());
					int n = 0;

					//APL_ASSERT( pType.get() );

					if( !pType->GetValueCount() )
					{
					//��� IntegerFeature
					if( Value != 0 )
					{
						std::string Tmp;
						ToString(Tmp);
		                                    
						Out += pType->GetValueName(Value);
						Out += ": ";
						Out += Tmp;
						++n;
					}
					}
					else
					{
					for( unsigned int i = 1; i < pType->GetValueCount(); ++i )
					{
						if( Value & (1 << i) )
						{
							if( n != 0 ) Out += ", ";
							Out += pType->GetValueName(i);
							++n;
						}
					}
					}


					if( n > 0 ) Out += ';';

					return Out;
				}
			}
		}
	}
}