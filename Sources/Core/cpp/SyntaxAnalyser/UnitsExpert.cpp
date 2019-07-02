#include "stdafx.h"
#include "UnitsExpert.h"

namespace SS
{
namespace Syntax
{
namespace ExpertModel
{
	//�������� ������ �����������
	void CUnitsExpert::ExecuteAnalysis(PBLOCK pBlock)
	{
		CBoardElement* pElem;
		BoardElementsIterator itCurrent;
		BoardElementsIterator itDetect;

		IModifiedConstruction::iterator itDetObj(m_pModifiedConstruction->begin());
		IModifiedConstruction::iterator itObj = itDetObj; ++itObj;

		while ( (*itDetObj)->Run() )
		{
			pElem = (*itDetObj)->GetWorkedElement();
			if (pElem)
			{
				//�������� ���������
				itDetect = m_itBeginBoard + pElem->GetPosition();
				m_itLastL = itDetect;
				m_itFirstR = itDetect + 1;
			}
			else
			{ 
				SS_THROW(L"������� ��������������� ������-������� ���������������� �����������."); 
			}

			//�������� ���������
			itObj = itDetObj; ++itObj;
			for (itObj; itObj != m_pModifiedConstruction->end(); ++itObj)
			{
				//��������� IdParent ���������� ������������
				if (pElem)
				{ 
					(*itObj)->SetIdParent(pElem->GetPosition()); 
				}
				else
				{ 
					(*itObj)->SetIdParent(-1); 
				}

				//������
				if ( !(*itObj)->Run() )
				{ 
					break;
				}
				else
				{
					pElem = (*itObj)->GetWorkedElement();
					if (pElem)
					{
						//�������� ���������
						itCurrent = m_itBeginBoard + pElem->GetPosition();
						if ( itCurrent < m_itLastL )
						{ 
							m_itLastL = itCurrent; 
						}
						else if ( itCurrent >= m_itFirstR)
						{
							m_itFirstR = itCurrent + 1; 
						}
						else
						{ 
							SS_THROW(L"������ ���������."); 
						}
					}
				}
			}
			//���������� �����������
			if ( itObj == m_pModifiedConstruction->end() )
			{ 
				//���� ����������� �� ������� (� � �������� ��)
				if ( m_pModifiedConstruction->IsAT() )
				{ 
					pBlock->IncCountATExpert();
					ApplyConstruction(pBlock->GetCountATExpert());
				}
				else
				{
					ApplyConstruction();
				}
			}
			else
			{
				//�������� ����������� � �� ����������� � BoardElement-��
				m_pModifiedConstruction->ClearContainersAT();
			}

			//�������� ��������� ��� ������ ������
			m_itFirst = itDetect;
			m_itLastL = m_itLast;
			m_itFirstR = itDetect + 1;
		}
	}
	
	//������ �� �����
	bool CUnitsExpert::PassBoard(CBoard & oBoard, PBLOCK pBlock)
	{
		SS_TRY
		{
			//������ ������� ����� �����������
			m_itBeginBoard = oBoard.ElementsBegin();
			//������� �����
			m_itBlockBegin = pBlock->GetFirst();
			m_itBlockEnd = pBlock->GetLast();
			//������� ���������
			m_itFirst = m_itFirstR = m_itBlockBegin;
			m_itLast = m_itLastL = m_itBlockEnd;

			//�������� ������������ �����������
			if ( !m_bIsAmbiguity )
			{
				if (m_isCheckedApplication && !m_isApplicable)
				{ 
					return true;
				}
				else if (!m_isCheckedApplication)
				{
					m_isCheckedApplication = true;
					if ( !IsApplicable() )
					{
						m_isApplicable = false;
						return true;
					}
					else
					{ 
						m_isApplicable = true; 
					}
				}
			}
			//��������� ������
			ExecuteAnalysis(pBlock);
		}
		SS_CATCH(L"")
		return false;
	}

}
}
}





