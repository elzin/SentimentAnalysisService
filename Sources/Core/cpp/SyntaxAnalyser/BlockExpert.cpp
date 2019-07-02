//BlockExpert.cpp

#include "StdAfx.h"
#include ".\blockexpert.h"
#include "../ASSInterface/IDictionaryManager.h"

namespace SS
{
namespace Syntax
{
namespace ExpertModel
{
	///�������� ������ ������-��������
	bool CBlockExpert::ExecuteDetect(IObjectAnalyser* pObjectAnalyser)
	{
		//������� ����� � �����������
		unsigned int iBlockPosition = pObjectAnalyser->GetConstructionObject()->m_ObjectFeature.m_BlockPosition.GetValue();
		
		if (iBlockPosition == 0)
		{
			PBLOCK pBlock;
			//�������� ������-�����
			if (m_pBlockDetect) 
			{
				//while (m_pBlockDetect->SwitchUnionVersion())
				//{
					if (pObjectAnalyser->Run()) 
					{ 
						m_UnionBlocks.push_back(m_pBlockDetect);
						return true; 
					}
				//}
				m_pBoard->SetCurrentBlock(m_pBlockDetect);
				pBlock = m_pBoard->GetNextBlock();
			}
			else
			{ pBlock = m_pBoard->GetFirstBlock(); }
		
			//����� � ��������� ������
			for (pBlock; pBlock; pBlock = m_pBoard->GetNextBlock())
			{
				m_itFirstR = m_itBlockBegin = pBlock->GetFirst();
				m_itLast = m_itBlockEnd = pBlock->GetLast();
				//������				
				//while (pBlock->SwitchUnionVersion())
				//{
					if (pObjectAnalyser->Run())
					{
						//������-����
						m_pBlockDetect = pBlock;
						m_pBlockRight = pBlock;
						m_pBlockLeft = pBlock;
						m_UnionBlocks.push_back(m_pBlockDetect);
						return true;
					}
				//}
			}
			//���� �� ��������
			return false;
		}
		else
		{
			//�������� ������-�����
			if (m_pBlockDetect)
			{
				//while (m_pBlockDetect->SwitchUnionVersion())
				//{
					if (pObjectAnalyser->Run()) 
					{ 
						m_UnionBlocks.push_back(m_pBlockDetect);
						return true; 
					}
				//}
				return false;
			}
			
			//���� ������ ������
			if (m_pBoard->CountBlock() < iBlockPosition)
			{ return false; }
			
			unsigned int iBlockNumber = 0;
			for (PBLOCK pBlock = m_pBoard->GetFirstBlock(); pBlock; pBlock = m_pBoard->GetNextBlock())
			{
				++iBlockNumber;
				if (iBlockNumber == iBlockPosition)
				{
					m_itFirstR = m_itBlockBegin = pBlock->GetFirst();
					m_itLast = m_itBlockEnd = pBlock->GetLast();
					//������				
					//while (pBlock->SwitchUnionVersion())
					//{
						if (pObjectAnalyser->Run())
						{
							//������-����
							m_pBlockDetect = pBlock;
							m_pBlockRight = pBlock;
							m_pBlockLeft = pBlock;
							m_UnionBlocks.push_back(m_pBlockDetect);
							return true;
						}
					//}
					return false;
				}
			}
		}
		return false;
	}
	
	///�������� ������ ��������� ���������
	bool CBlockExpert::ExecuteOther(IObjectAnalyser* pObjectAnalyser)
	{
		//���������� ������ ��� ���������
		unsigned int iBlockSearchScope = pObjectAnalyser->GetConstructionObject()->m_ObjectFeature.m_BlockSearchScope.GetValue();
		//������� ���������� ������
		unsigned int iBlockCount = 0;
		
		if ( pObjectAnalyser->GetConstructionObject()->m_ObjectFeature.m_PositionToDetectedObject.Equal(Values::PositionToDetectedObject.ptdoRight) ||
			 pObjectAnalyser->GetConstructionObject()->m_ObjectFeature.m_PositionToDetectedObject.IsUndefined() )
		{ 
			//�������� �����
			//while (m_pBlockRight->SwitchUnionVersion())
			//{
				if (pObjectAnalyser->Run())
				{ return true; }
			//}
			
			//���������� ������ ����
			m_pBoard->SetCurrentBlock(m_pBlockRight);
			PBLOCK pBlock = m_pBoard->GetNextBlock();
			for (pBlock; pBlock; pBlock = m_pBoard->GetNextBlock())
			{
				if (iBlockCount == iBlockSearchScope)
				{ return false;	}
				//��������� ���������
				m_itFirstR = m_itBlockBegin = pBlock->GetFirst();
				m_itLast = m_itBlockEnd = pBlock->GetLast();
				//while (pBlock->SwitchUnionVersion())
				//{
					if (pObjectAnalyser->Run())
					{ 
						m_pBlockRight = pBlock;
						m_UnionBlocks.push_back(m_pBlockRight);
						return true;
					}
				//}
				++iBlockCount;
			}
		}
		else if ( pObjectAnalyser->GetConstructionObject()->m_ObjectFeature.m_PositionToDetectedObject.Equal(Values::PositionToDetectedObject.ptdoLeft) )
		{
			//�������� �����
			//while (m_pBlockLeft->SwitchUnionVersion())
			//{
				if (pObjectAnalyser->Run())
				{ return true; }
			//}
			
			//���������� ������ ����
			m_pBoard->SetCurrentBlock(m_pBlockLeft);
			PBLOCK pBlock = m_pBoard->GetPrevBlock();
			for (pBlock; pBlock; pBlock = m_pBoard->GetPrevBlock())
			{
				if (iBlockCount == iBlockSearchScope)
				{ return false;	}
				//��������� ���������
				m_itFirst = m_itBlockBegin = pBlock->GetFirst();
				m_itLastL = m_itBlockEnd = pBlock->GetLast();
				//while (pBlock->SwitchUnionVersion())
				//{
					if (pObjectAnalyser->Run())
					{
						m_pBlockLeft = pBlock;
						m_UnionBlocks.insert(m_UnionBlocks.begin(), m_pBlockLeft);
						return true;
					}
				//}
				++iBlockCount;
			}
		}
		return false;
	}
	
	//�������� ������ �����������
	void CBlockExpert::ExecuteAnalysis()
	{
		CBoardElement* pElem;
		BoardElementsIterator itCurrent;
		BoardElementsIterator itDetect;
		m_pBlockDetect = NULL;
		
		IModifiedConstruction::iterator itDetObj(m_pModifiedConstruction->begin());
		IModifiedConstruction::iterator itObj = itDetObj; ++itObj;
		
		while (ExecuteDetect(*itDetObj))
		{
			pElem = (*itDetObj)->GetWorkedElement();
			if (pElem)
			{
				//�������� ���������
				itDetect = m_itBeginBoard + pElem->GetPosition();
				m_itLastL = itDetect;
				m_itFirstR = itDetect + 1;
				m_itBlockBegin = m_itFirst = m_pBlockDetect->GetFirst();
				m_itBlockEnd = m_itLast = m_pBlockDetect->GetLast();
			}
			else
			{ SS_THROW(L"������� ��������������� ������-������� ���������������� �����������."); }

			//�������� ���������
			itObj = itDetObj; ++itObj;
			for (itObj; itObj != m_pModifiedConstruction->end(); ++itObj)
			{
				//��������� IdParent ���������� ������������
				if (pElem)
				{ (*itObj)->SetIdParent(pElem->GetPosition()); }
				else
				{ (*itObj)->SetIdParent(-1); }

				//������
				if ( !ExecuteOther(*itObj) )
				{ break; }
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
							m_itFirst = m_pBlockLeft->GetFirst();
							m_itBlockBegin = m_pBlockLeft->GetFirst();
							m_itBlockEnd = m_pBlockLeft->GetLast();
						}
						else if ( itCurrent >= m_itFirstR)
						{ 
							m_itFirstR = itCurrent + 1; 
							m_itLast = m_pBlockRight->GetLast();
							m_itBlockBegin = m_pBlockRight->GetFirst();
							m_itBlockEnd = m_pBlockRight->GetLast();
						}
						else
						{ SS_THROW(L"������ ���������."); }
					}
				}
			}
			//���������� �����������
			if ( itObj == m_pModifiedConstruction->end() ) 
			{ 
				ApplyConstruction();
				UniteBlocks();
				m_pBlockDetect = m_pBlockRight;
				m_itFirstR = m_pBlockDetect->GetFirst();
			}
			else
			{ 
				m_itFirstR = itDetect + 1;
				//�������� ����������� � �� ����������� � BoardElement-��
				m_pModifiedConstruction->ClearContainersAT();
			}
			
			//�������� ��������� ��� ������ ������ ������-��������
			m_itLast = m_pBlockDetect->GetLast();
			m_itBlockBegin = m_pBlockDetect->GetFirst();
			m_itBlockEnd = m_pBlockDetect->GetLast();	
			
			//������� ������ ������
			m_UnionBlocks.clear();
		}
	}
	
	//������ �� �����
	bool CBlockExpert::PassBoard(CBoard & oBoard, PBLOCK pBlock)
	{
		SS_TRY
		{
			//���� ���� ����
			if (oBoard.CountBlock() == 1) 
			{ return false; }
			
			//������� �����������
			m_itBlockBegin = oBoard.ElementsBegin();
			m_itBlockEnd = oBoard.ElementsEnd();
			
			//�������� ������������ �����������
			if ( !IsApplicable() )
			{ return false;	}
	
			//��������� �����������
			m_pBoard = &oBoard;
			//������ ������� ����� �����������
			m_itBeginBoard = oBoard.ElementsBegin();
			//������� ������ ������
			m_UnionBlocks.clear();
			
			//��������� ������
			ExecuteAnalysis();
		}
		SS_CATCH(L"")
		return false;
	}

	///���������� �����
	void CBlockExpert::UniteBlocks()
	{
		SS_TRY
		{
			if (m_UnionBlocks.size() <= 1) 
			{ SS_THROW(L"�������� ������������ ��������."); }
			std::list<PBLOCK>::iterator it_prev(m_UnionBlocks.begin());
			std::list<PBLOCK>::iterator it(it_prev);
			for (++it; it != m_UnionBlocks.end(); ++it)
			{
				(*it)->AddBlock(*it_prev);
				m_pBoard->SetCurrentBlock(*it_prev);
				m_pBoard->DeleteCurrentBlock();
				it_prev = it;
			}
		}
		SS_CATCH(L"")
	}

}
}
}