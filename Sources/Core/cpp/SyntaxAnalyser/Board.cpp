#include "stdafx.h"
#include "Board.h"
#include "../ASSInterface/IBlackBoxUnit.h"
#include "../ASSInterface/Constants.h"
#include "../ASSInterface/TDictionaryNames.h"

using namespace std;
using namespace SS::Interface::Core::BlackBox;
using namespace SS::Core::Features;
using namespace SS::Constants;

namespace SS
{
namespace Syntax
{
namespace BoardElements
{
	//�����������
	CBoard::CBoard() : m_pAnalyseParams(NULL), m_eLang(SS::Core::Types::EAnalyseLanguage::ealUndefined)
	{
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories = Values::SyntaxCategories.scSubjectFin;
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scMain);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunct);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scObject);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scSubjectComplement);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctTimeSource);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctTimeFixedPoint);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctTimeEnd);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctTimeDuration);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctPlaceSource);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctPlaceFixedPoint);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctPlaceEnd);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctGoal);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctCause);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctMeasure);
		m_oSyntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scAjunctManner);
	}

	//��������� ���������� ����� ����������
	void CBoard::FillBoard(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
	{
		m_elements.reserve(MAX_WORDS_IN_SENTENCE);

		for (int i = 0; i < MAX_WORDS_IN_SENTENCE; i++)
		{
			CBoardElement* pBoardElement = new CBoardElement(pLoadManager);
			m_elements.push_back(pBoardElement);
		}
		m_MarkerLastElem = m_elements.begin();
	}

	//������������� ����� ������������ �� IText - � (���������� true, ���� ������������ ������ �������)
	bool CBoard::Initialize(ISentence* pSentence)
	{
		SS_TRY
		{
			//��������� �����	
			m_eLang = pSentence->GetLanguage();
			//������� ��������� ������
			m_Blocks.Clear();
			//��������� ������� �� ������ �������
			m_MarkerLastElem = m_elements.begin();
			//������� � �����������
			unsigned int uiPosition = 0;
			//������������� ������� ������������
			Init(pSentence->GetFirstUnit(), uiPosition);
			if ( ElementsBegin() != ElementsEnd() ) 
			{
				m_Blocks.Add()->Init( ElementsBegin(), ElementsEnd() );
				return true;
			}
			return false;
		}
		SS_CATCH(L"")
	}

	///����������
	CBoard::~CBoard()
	{
		if (!m_elements.empty())
		{
			BoardElementsIterator Iter;
			for (Iter = m_elements.begin(); Iter != m_elements.end(); Iter++)
			{ delete (*Iter); }
			m_elements.erase( m_elements.begin(), m_elements.end() );
		}
	}

	//�������� Unit-�, ��� �� �� �� ��� 256-�
	bool CBoard::IsGood(SS::Interface::Core::BlackBox::IUnit* pUnit) const
	{
		if ( m_MarkerLastElem == m_elements.end() )
		{ 
			SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"����������� ����� ����� ����� 255 ����.");
			return false;
		}
		for (IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
		{
			if (pIndex->GetFirstFeature()) 
			{ return true; }
		}
		return false;
	}

	//����� � ������ ������� ����� � ������������� SyntaxFlag
	void CBoard::Init(IUnit* begin, unsigned int & uiLastPosition)
	{
		SS_TRY
		{
			for (IUnit* topUnit = begin; topUnit != NULL; topUnit = topUnit->GetRightUnit())
			{
				if ( topUnit->GetSyntaxFlag() )
				{
					if ( IsGood(topUnit) )
					{
						if ((*m_MarkerLastElem)->Init(topUnit, m_eLang, uiLastPosition)) 
						{
							m_MarkerLastElem++;
							uiLastPosition++;
						}
					}
				}
				else
				{ 
					Init(topUnit->GetLeftChildUnit(), uiLastPosition); 
				}
			}
		}
		SS_CATCH(L"")
	}

	//������� �������� ��� ���� ��������� �����
	void CBoard::CreateVersions()
	{
		SS_TRY
		{
			for (PBLOCK pB = m_Blocks.GetFirst(); pB; pB = m_Blocks.GetNext())
			{ pB->CreateVersions(); }
		}
		SS_CATCH(L"")
	}

	//����������� �������������� ��������� ������ � ������ �������������� ������
	void CBoard::AssignSyntaxInfoToBlackBoxMultilayer()
	{
		SS_TRY
		{
			if ( m_pAnalyseParams && (m_pAnalyseParams->GetSyntaxAnalysisMode() == SS::Core::Types::esamFullWithoutSyntaxTree) )
			{
				for (BoardElementsIterator i = ElementsBegin(); i != ElementsEnd(); ++i)
				{
					(*i)->SetFeatureToUnit();
					(*i)->RemoveUselessMorpho();
				}
				return;
			}
			
			SS::Interface::Core::BlackBox::IUnit* topLevelUnit = NULL;
			for (BoardElementsIterator i = ElementsBegin(); i != ElementsEnd(); ++i)
				(*i)->SetDone(false);
			//������������ ������ � ������ �������������� ���������
			for (BoardElementsIterator i = ElementsBegin(); i != ElementsEnd(); ++i)
			{
				(*i)->SetFeatureToUnit();
				(*i)->RemoveUselessMorpho();

				if (!(*i)->IsHead() && !IsCycle(*i))
				{
					SS::Interface::Core::BlackBox::IUnit* unit = (*i)->GetUnit();
					unit->Pop();
					m_elements[(*i)->GetParentIndex()]->GetUnit()->AddUnitVertical(unit);
				}
				else
				{
					topLevelUnit = (*i)->GetUnit();
                    (*i)->SetHead(true);
				}
                (*i)->SetDone(true);
			}

			if (!topLevelUnit)
			{ return; }

			//for (BoardElementsIterator i = ElementsBegin(); i != ElementsEnd(); ++i)
			//{
			//	if ( !(*i)->IsHead() &&
			//		 ( m_oSyntaxFeatureAposteriori.m_SyntaxCategories.IsIntersectsWith(&(*i)->GetSyntaxFeature().m_SyntaxCategories) ) &&
			//		 ( m_elements[(*i)->GetParentIndex()]->GetSyntaxFeature().m_SyntaxCategories.Equal(Values::SyntaxCategories.scMain) ||
			//		   m_elements[(*i)->GetParentIndex()]->GetSyntaxFeature().m_SyntaxCategories.Equal(Values::SyntaxCategories.scChain) ) )
			//	{
			//		SS::Interface::Core::BlackBox::IUnit* unit = (*i)->GetUnit();
			//		unit->Pop();
			//		topLevelUnit->AddUnitHorizontal( unit );
			//	}
			//}
		}
		SS_CATCH(L"")
	}

    bool CBoard::IsCycle(CBoardElement* pElement, CBoardElement* pBorder/* = 0*/) const
    {
        bool cycle = false;
        if(!pElement->IsHead())
        {
            if(!pBorder)
                pBorder = pElement;
            CBoardElement *pParent = m_elements[pElement->GetParentIndex()];
            if(pParent == pBorder)
                cycle = true;
            else if(pParent->IsDone())
                cycle = IsCycle(pParent, pBorder);
        }
        return cycle;
    }

	//�������� ������ �� ���������, ����������� �����������
	void CBoard::DeleteBlocks()
	{
		m_Blocks.Clear();
	}

	//��������� ���������� ����� ����������, �������� ������ ��������
	int CBoard::HeadDistance(BoardElementsIterator first, BoardElementsIterator last)
	{
		SS_TRY
		{
			if (first == last)
			{ return 0;	}

			int iDistance = 0;
			BoardElementsIterator itElem = first;

			for (itElem; itElem != last; itElem++)
			{
				if ((*itElem)->IsHead())
				{ iDistance++; }
			}
			return iDistance;
		}
		SS_CATCH(L"")
	}

	// �������� ����
	PBLOCK CBoard::AddBlock()
	{
		PBLOCK pBlock = m_Blocks.Add();
		if (pBlock) return pBlock;
		SAVE_LOG(L"���������� ������ ��������� ������������ ������.");
		return NULL;
	}

	///�������� ���������� ���� �� �������� � �������� ��������
	PBLOCK CBoard::GetPrevBlock() const
	{
		return m_Blocks.GetPrev();
	}

	///������� ���� �������
	PBLOCK CBoard::SetCurrentBlock(PBLOCK pBlock) const
	{
		return m_Blocks.SetCurrent(pBlock);
	}

	///���������� ������
	unsigned int CBoard::CountBlock() const
	{
		return m_Blocks.Size();
	}

	///���������� AnalyseParams
	void CBoard::SetAnalyseParams(SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams)
	{
		m_pAnalyseParams = pAnalyseParams;
	}

	///������� ������� ����
	void CBoard::DeleteCurrentBlock()
	{
		m_Blocks.DeleteCurrent();
	}

	///�������� �������� ������� ��������
	CBoardElement* CBoard::GetParent(CBoardElement* pElem)
	{
		CBoardElement* pElemPr = m_elements[pElem->GetParentIndex()];
		if (pElemPr == pElem) 
		{ return NULL; }
		return pElemPr;
	}
	
}
}
}