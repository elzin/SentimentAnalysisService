//ExpertClause.cpp

#include "StdAfx.h"
#include ".\expertclause.h"

namespace SS
{
namespace Syntax
{
namespace ExpertClause
{
	/*******************************ExpertClauseRelative********************************/
	//�����������
	CExpertClauseRelative::CExpertClauseRelative()
	{
		m_Words.push_back(L"where");
		m_Words.push_back(L"when");
		m_Words.push_back(L"why");
	}

	//������ �� ����� 
	bool CExpertClauseRelative::PassBoard(CBoard & rBoard, PBLOCK pBlock)
	{
		SS_TRY
		{
			//��������� ������� �����
			PBLOCK pPrevBlock = rBoard.GetPrevBlock();
			if ( (!pPrevBlock) || pPrevBlock->Empty() ) 
			{ return true; }

			//�������������� �����
			BoardElementsIterator itQuestion = pBlock->GetFirst();
			//���� ������� ������������ �����
			bool IsQuest = false;
			//����� ����� BeatsBlock-�� ������������ ��������
			for (itQuestion; (itQuestion != pBlock->GetLast()) && ((*itQuestion)->BeatsBlocks()); ++itQuestion)
			{
				if ( (find(m_Words.begin(), m_Words.end(), (*itQuestion)->GetWord()) != m_Words.end()) && 
					 !(*itQuestion)->GetVerElem()->m_isHead )
				{
					IsQuest = true;
					break;
				}
			}
			if (!IsQuest)
				return true;
						
			//�������� ������� ����� �� ���������
			if ( !(*itQuestion)->GetSemanticType().IsIntersectsWith(&Values::TSemanticType.smtPlace) &&
				 !(*itQuestion)->GetSemanticType().IsIntersectsWith(&Values::TSemanticType.smtTimeInterval) )
			{ return true; }

			//������� ������� ����� (verb, ��������)
			BoardElementsIterator itSecondMember = itQuestion;
			while (++itSecondMember != pBlock->GetLast())
			{ 
				if ( ((*itSecondMember)->GetFirstMorpho()->GetMorphoFeature().m_PartOfSpeechTypes.GetValue() & 
					  Values::PartOfSpeechTypes.postVerb.GetValue()) && ((*itSecondMember)->GetVerElem()->m_isHead) )
				{ break; }
			}
			if (itSecondMember == pBlock->GetLast())
			{ return true; }

			//������� ������� ����� (noun)
			BoardElementsIterator itFirstMember = pPrevBlock->GetLast();
			do 
			{
				--itFirstMember;
				if ( (*itFirstMember)->GetFirstMorpho()->GetMorphoFeature().m_PartOfSpeechTypes.GetValue() & 
					 Values::PartOfSpeechTypes.postNoun.GetValue() ) 
				{ break; }
				
				if (itFirstMember == pPrevBlock->GetFirst()) 
				{ return true; }
			}
			while (itFirstMember != pPrevBlock->GetFirst());

			//�������� ���������� �� ��������� c itQuestion
			if ( !(*itFirstMember)->GetSemanticType().IsIntersectsWith(&Values::TSemanticType.smtPlace) &&
				 !(*itFirstMember)->GetSemanticType().IsIntersectsWith(&Values::TSemanticType.smtTimeInterval) )
			{ return true; }

			//���������� ������� �������� �������� ��������
			m_oSyntaxFeatureAposterioriSecondMember = (*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori;
			bool bHeadSecondMember = (*itSecondMember)->GetVerElem()->m_isHead;

			//�������� �������� ������� ����� � �������� �������
			(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent = (unsigned)distance(rBoard.ElementsBegin(), itFirstMember);
			(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower = 100;
			(*itSecondMember)->GetVerElem()->m_isHead = false;
			(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories = Values::SyntaxCategories.scAttribute;
			(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategoryPower = 100;
					
			//��������� ������� ������� ����� (verb, ��������)
			BoardElementsIterator itSecondMemberTwo = itSecondMember; 
			while (++itSecondMemberTwo != pBlock->GetLast())
			{ 
				if ( ((*itSecondMemberTwo)->GetFirstMorpho()->GetMorphoFeature().m_PartOfSpeechTypes.GetValue() & 
					 Values::PartOfSpeechTypes.postVerb.GetValue()) && ((*itSecondMemberTwo)->GetVerElem()->m_isHead) )
				{ 
					if ( (rBoard.ElementsBegin() + (*itSecondMemberTwo)->GetParentIndex()) == itSecondMember ) 
					{ SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"�������� �� ������ ���� ����������."); }
					break;
				}
			}
			if (itSecondMemberTwo == pBlock->GetLast())
			{ 
				//���������� ��� �����
				pBlock->AddBlock(pPrevBlock);
				//�������������� ������� �������� �������� ��������
				(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori = m_oSyntaxFeatureAposterioriSecondMember;
				(*itSecondMember)->GetVerElem()->m_isHead = bHeadSecondMember;
				return true; 
			}
			
			//���������� ������� �������� �������� ��������
			unsigned int iSyntaxCategories = (*itSecondMemberTwo)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories.GetValue();
			unsigned int iSyntaxCategoryPower = (*itSecondMemberTwo)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategoryPower.GetValue();
			//���������� ������� �������� �������� ��������
			m_oSyntaxFeatureAposterioriFirstMember = (*itFirstMember)->GetVerElem()->m_syntaxFeatureAposteriori;
			bool bHeadFirstMember = (*itFirstMember)->GetVerElem()->m_isHead;
			
			//��������� ��������
			(*itSecondMemberTwo)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories = Values::SyntaxCategories.scMain;
			(*itSecondMemberTwo)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategoryPower = 100;
			//�������� ������� �������� ��� ������ ������
			(*itFirstMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories = Values::SyntaxCategories.scSubjectFin;
			(*itFirstMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategoryPower = 100;
			(*itFirstMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent = (unsigned)distance(rBoard.ElementsBegin(), itSecondMemberTwo);
			(*itFirstMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower = 100;
			(*itFirstMember)->GetVerElem()->m_isHead = false;
			
			//���������� ��� �����
			pBlock->AddBlock(pPrevBlock);
			
			//�������������� ������� ��������
			(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori = m_oSyntaxFeatureAposterioriSecondMember;
			(*itSecondMember)->GetVerElem()->m_isHead = bHeadSecondMember;
			//�������������� ������� ��������
			(*itFirstMember)->GetVerElem()->m_syntaxFeatureAposteriori = m_oSyntaxFeatureAposterioriFirstMember;
			(*itFirstMember)->GetVerElem()->m_isHead = bHeadFirstMember;
			//�������������� ������� ��������
			(*itSecondMemberTwo)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories.SetValue(iSyntaxCategories);
			(*itSecondMemberTwo)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategoryPower.SetValue(iSyntaxCategoryPower);
		}
		SS_CATCH(L"")
		return true;
	}
	
	//���������� ��������� �������� ��������
	std::wstring CExpertClauseRelative::GetName() const
	{
		return L"ExpertClauseRelative";
	}

	/*******************************ExpertClauseAdjunct********************************/
	///�����������
	CExpertClauseAdjunct::CExpertClauseAdjunct() : m_eActiveBlock(EActiveBlock::eFirst)
	{
		m_Words.push_back(L"where");
		m_Words.push_back(L"when");
		m_Words.push_back(L"how");
		m_Words.push_back(L"why");
		m_Words.push_back(L"while");
	}
	
	//������ �� ����� 
	bool CExpertClauseAdjunct::PassBoard(CBoard & rBoard, PBLOCK pBlock)
	{
		SS_TRY
		{
			//��������� ������� �����
			PBLOCK pPrevBlock = rBoard.GetPrevBlock();
			if ( (!pPrevBlock) || pPrevBlock->Empty() ) 
			{ return true; }
			
			//������������ ����� �� ������ m_Words
			BoardElementsIterator itNeedMember;
			//���� ������� ������������ �����
			bool IsNeed = false;
			//����� ����� BeatsBlock ����-�� ������� ����� ������������ ��������
			for ( itNeedMember = pBlock->GetFirst(); 
				  (itNeedMember != pBlock->GetLast()) && ((*itNeedMember)->BeatsBlocks()); ++itNeedMember )
			{
				if ( ( find(m_Words.begin(), m_Words.end(), (*itNeedMember)->GetWord()) != m_Words.end() ) ||
					 ( (*itNeedMember)->GetFirstMorpho()->GetMorphoFeature().m_ConjunctionType.GetValue() & 
					 Values::TConjunctionType.cjtSubordinating.GetValue() ) ) 
				{
					IsNeed = true;
					m_eActiveBlock = eSecond;
					break;
				}
			}
			//����� ����� BeatsBlock ����-�� ������� ����� ������������ ��������
			if (!IsNeed) 
			{
				itNeedMember = pPrevBlock->GetFirst();
				if ( ( find(m_Words.begin(), m_Words.end(), (*itNeedMember)->GetWord()) != m_Words.end() ) ||
					 ( (*itNeedMember)->GetFirstMorpho()->GetMorphoFeature().m_ConjunctionType.GetValue() & 
					 Values::TConjunctionType.cjtSubordinating.GetValue() ) ) 
				{
					IsNeed = true;
					m_eActiveBlock = eFirst;
				}
			}
			if (!IsNeed)
				return true;
					
			//� ������ ����� ���� Main � ����������� SubjectFin
			BoardElementsIterator itFirstMember;
			BoardElementsIterator itParentMember;
			BoardElementsIterator it;
			bool IsMain = false;
			for (it = pPrevBlock->GetFirst(); it != pPrevBlock->GetLast(); ++it)
			{
				if ( (*it)->GetSyntaxFeature().m_SyntaxCategories.GetValue() &
					 Values::SyntaxCategories.scSubjectFin.GetValue() )
				{
					itFirstMember = it;
					itParentMember = rBoard.ElementsBegin() + (*it)->GetParentIndex();
					while ( (itParentMember != itFirstMember) && pPrevBlock->Contain(itParentMember) )
					{
						if ( (*itParentMember)->GetSyntaxFeature().m_SyntaxCategories.GetValue() &
							 Values::SyntaxCategories.scMain.GetValue() )
						{ 
							IsMain = true;
							break; 
						}
						itFirstMember = itParentMember;
						itParentMember = rBoard.ElementsBegin() + (*itFirstMember)->GetParentIndex();
					}
					if (IsMain)
					{ 
						itFirstMember = itParentMember;
						break; 
					}
				}
			}
			if (it == pPrevBlock->GetLast()) 
			{ return true; }
			
			//�� ������ ����� ���� Main � ����������� SubjectFin
			BoardElementsIterator itSecondMember;
			IsMain = false;
			for (it = pBlock->GetFirst(); it != pBlock->GetLast(); ++it)
			{
				if ( (*it)->GetSyntaxFeature().m_SyntaxCategories.GetValue() &
					 Values::SyntaxCategories.scSubjectFin.GetValue() )
				{
					itSecondMember = it;
					itParentMember = rBoard.ElementsBegin() + (*it)->GetParentIndex();
					while ( (itParentMember != itSecondMember) && pBlock->Contain(itParentMember) ) 
					{
						if ( (*itParentMember)->GetSyntaxFeature().m_SyntaxCategories.GetValue() &
							 Values::SyntaxCategories.scMain.GetValue() )
						{ 
							IsMain = true;
							break; 
						}
						itSecondMember = itParentMember;
						itParentMember = rBoard.ElementsBegin() + (*itSecondMember)->GetParentIndex();
					}
					if (IsMain)
					{ 
						itSecondMember = itParentMember;
						break; 
					}
				}
			}
			if (it == pBlock->GetLast()) 
			{ return true; }
			
			//���������� ������� �������� �������� �������� Need
			m_oSyntaxFeatureAposterioriNeed = (*itNeedMember)->GetVerElem()->m_syntaxFeatureAposteriori;
			//�������� ��������� �����
			if ( m_eActiveBlock == eSecond )
			{
				//���������� ������� �������� �������� �������� Second
				m_oSyntaxFeatureAposteriori = (*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori;
				bool bHeadSecondMember = (*itSecondMember)->GetVerElem()->m_isHead;
				
				//����������� Second ��� First
				(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent = (unsigned)distance(rBoard.ElementsBegin(), itFirstMember);
				(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower = 100;
				(*itSecondMember)->GetVerElem()->m_isHead = false;
				(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories.SetValue(CalcSyntaxCategory(itNeedMember));
				(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategoryPower = 100;
				(*itNeedMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategoryPower = 100;
				//������ ������ ��� ������ ������� (���� ���� �����)
				(*itNeedMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent = (unsigned)distance(rBoard.ElementsBegin(), itSecondMember);
				(*itNeedMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower = 100;
				//���������� ��� �����
				pBlock->AddBlock(pPrevBlock);
				//�������������� ������
				(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori = m_oSyntaxFeatureAposteriori;
				(*itSecondMember)->GetVerElem()->m_isHead = bHeadSecondMember;
			}
			else if ( m_eActiveBlock == eFirst )
			{
				//���������� ������� �������� �������� �������� First
				m_oSyntaxFeatureAposteriori = (*itFirstMember)->GetVerElem()->m_syntaxFeatureAposteriori;
				bool bHeadFirstMember = (*itFirstMember)->GetVerElem()->m_isHead;
				
				//����������� First ��� Second
				(*itFirstMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent = (unsigned)distance(rBoard.ElementsBegin(), itSecondMember);
				(*itFirstMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower = 100;
				(*itFirstMember)->GetVerElem()->m_isHead = false;
				(*itFirstMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories.SetValue(CalcSyntaxCategory(itNeedMember));
				(*itFirstMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategoryPower = 100;
				(*itNeedMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategoryPower = 100;
				//������ ������ ��� ������ ������� (���� ���� �����)
				(*itNeedMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent = (unsigned)distance(rBoard.ElementsBegin(), itFirstMember);
				(*itNeedMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower = 100;
				//���������� ��� �����
				pBlock->AddBlock(pPrevBlock);
				//�������������� ������
				(*itFirstMember)->GetVerElem()->m_syntaxFeatureAposteriori = m_oSyntaxFeatureAposteriori;
				(*itFirstMember)->GetVerElem()->m_isHead = bHeadFirstMember;
			}
			//�������������� ������
			(*itNeedMember)->GetVerElem()->m_syntaxFeatureAposteriori = m_oSyntaxFeatureAposterioriNeed;
		}
		SS_CATCH(L"")
		return true;
	}
	
	//���������� ��������� �������� ��������
	std::wstring CExpertClauseAdjunct::GetName() const
	{
		return L"ExpertClauseAdjunct";
	}

	///��������� �������������� ���������
	unsigned int CExpertClauseAdjunct::CalcSyntaxCategory(BoardElementsIterator itElem)
	{
		SS_TRY
		{
			if ( (*itElem)->GetWord() == L"where" ) 
			{
				(*itElem)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories = Values::SyntaxCategories.scAjunctPlaceFixedPoint;
				return Values::SyntaxCategories.scAjunctPlaceFixedPoint.GetValue();
			}
			else if ( (*itElem)->GetWord() == L"when" || (*itElem)->GetWord() == L"while" )
			{
				(*itElem)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories = Values::SyntaxCategories.scAjunctTimeFixedPoint;
				return Values::SyntaxCategories.scAjunctTimeFixedPoint.GetValue();
			}
			else if ( (*itElem)->GetWord() == L"how" ) 
			{
				(*itElem)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories = Values::SyntaxCategories.scAjunctManner;
				return Values::SyntaxCategories.scAjunctManner.GetValue();
			}
			else if ( (*itElem)->GetWord() == L"why" ) 
			{
				(*itElem)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories = Values::SyntaxCategories.scAjunctCause;
				return Values::SyntaxCategories.scAjunctCause.GetValue();
			}
			else if ( (*itElem)->GetWord() == L"though" || (*itElem)->GetWord() == L"unless" ) 
			{
				(*itElem)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories = Values::SyntaxCategories.scAjunct;
				return Values::SyntaxCategories.scAjunct.GetValue();
			}
			else if ( (*itElem)->GetWord() == L"if" || (*itElem)->GetWord() == L"weather" ) 
			{
				(*itElem)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories = Values::SyntaxCategories.scAjunct;
				(*itElem)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories.AssignOR(&Values::SyntaxCategories.scObject); 
				return (Values::SyntaxCategories.scAjunct.GetValue() | Values::SyntaxCategories.scObject.GetValue());
			}
			else
			{
				return 0;
			}
		}
		SS_CATCH(L"")
	}

}
}
}