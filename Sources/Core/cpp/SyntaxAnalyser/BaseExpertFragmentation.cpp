//BaseExpertFragmentation.cpp

#include "StdAfx.h"
#include ".\baseexpertfragmentation.h"

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			//�����������
			CBaseExpertFragmentation::CBaseExpertFragmentation() : m_bBracketAnalyse(true)
			{
				m_CommonDivisors.push_back(L";");
				m_CommonDivisors.push_back(L":");
				m_CommonDivisors.push_back(L"(");
				m_sLeftBracket = L"(";
				m_sRightBracket = L")";
				m_sDivisor = L";";
			}
			
			//������ �� �����
			bool CBaseExpertFragmentation::PassBoard(BoardElements::CBoard & rBoard, BoardElements::PBLOCK pBlock)
			{
				SS_TRY
				{
					//������ ������� �������� �����
					BoardElements::BoardElementsIterator itBegin = rBoard.ElementsBegin();
					//������� �� ���������
					m_last = rBoard.ElementsEnd();
					//������� ��� �����					
					rBoard.DeleteBlocks();
					//������� ����� ������
					bool bLeftBracket = false;
					//������� ���������
					for (BoardElements::BoardElementsIterator it = itBegin; it != m_last; ++it)
					{
						CBoardElement *belem = *it;
						if ( !((*it)->IsHead()) )
						{ continue; }
						
						if (m_bBracketAnalyse) 
						{
							//�������� �� ��������
							if (bLeftBracket) 
							{
								if ( (*it)->GetWord() == m_sRightBracket )
								{
									if (pBlock = rBoard.AddBlock()) 
									{ 
										++it;
										pBlock->Init(itBegin, it); 
										if (it == m_last) return true;		
										(*it)->SetBeatsBlocks();
										itBegin = it;
										bLeftBracket = false;
									}
								}
								continue;
							}
							if ((*it)->GetWord() == m_sLeftBracket) 
							{ bLeftBracket = true; }
							//����� �������� �� ��������

							if (it == itBegin) 
								continue;
							if (it == m_last-1) 
								break;
							if ( (find(m_CommonDivisors.begin(), m_CommonDivisors.end(), (*it)->GetWord()) != m_CommonDivisors.end()) || IsConj(it) ) 
							{
								if (pBlock = rBoard.AddBlock()) 
								{ 
									pBlock->Init(itBegin, it); 
									(*it)->SetBeatsBlocks();
									itBegin = it;
								}
							}
						}
						else
						{
							if (it == itBegin) 
								continue;
							if (it == m_last-1) 
								break;
							if ( ((*it)->GetWord() == m_sDivisor) || IsConj(it) ) 
							{
								if (pBlock = rBoard.AddBlock()) 
								{ 
									pBlock->Init(itBegin, it); 
									(*it)->SetBeatsBlocks();
									itBegin = it;
								}
							}
						}
					}
					if (pBlock = rBoard.AddBlock()) 
					{ pBlock->Init(itBegin, m_last); }
				
					return true;
				}
				SS_CATCH(L"")
			}

		}
	}
}