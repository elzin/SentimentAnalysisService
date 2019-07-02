//ExpertCoordinate.cpp
#include "StdAfx.h"
#include ".\expertcoordinate.h"

namespace SS
{
namespace Syntax
{
namespace ExpertClause
{
	using namespace SS::Core::Features;
	
	//������ �� ����� 
	bool CExpertCoordinate::PassBoard(CBoard & rBoard, PBLOCK pBlock)
	{
		SS_TRY
		{
			//��������� ������� �����
			PBLOCK pPrevBlock = rBoard.GetPrevBlock();
			if ( (!pPrevBlock) || pPrevBlock->Empty() )
			{ return true; }

			//�������������� ������� �����
			BoardElementsIterator itConjunction = pBlock->GetFirst();
			//���� ������� ������������ �����
			bool IsConj = false;
			//����� ����� BeatsBlock ����-�� ������� ����� ������������ ��������
			for (itConjunction; (itConjunction != pBlock->GetLast()) && ((*itConjunction)->BeatsBlocks()); ++itConjunction)
			{
				//����� �� ������ ����� ������������ �����
				if ( (*itConjunction)->GetFirstMorpho()->GetMorphoFeature().m_ConjunctionType.GetValue() &
					 Values::TConjunctionType.cjtCoordinating.GetValue() )
				{
					IsConj = true;
					break;
				}
			}
			if (!IsConj)
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
			it = itConjunction;
			++it;
			IsMain = false;
			for (it; it != pBlock->GetLast(); ++it)
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
			
			//���������� ������� ��������
			unsigned int iSecondParent = (*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent.GetValue();
			unsigned int iSecondPower = (*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower.GetValue();
			bool bSecondHead = (*itSecondMember)->GetVerElem()->m_isHead;
			unsigned int iConjParent = (*itConjunction)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent.GetValue();
			unsigned int iConjPower = (*itConjunction)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower.GetValue();
			//������ ������� ������� ��� ������
			(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent = (unsigned)distance(rBoard.ElementsBegin(), itFirstMember);
			(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower = 100;
			(*itSecondMember)->GetVerElem()->m_isHead = false;
			(*itConjunction)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent = (unsigned)distance(rBoard.ElementsBegin(), itSecondMember);
			(*itConjunction)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower = 100;
			//���������� ��� �����
			pBlock->AddBlock(pPrevBlock);
			//�������������� ��������
			(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent.SetValue(iSecondParent);
			(*itSecondMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower.SetValue(iSecondPower);
			(*itSecondMember)->GetVerElem()->m_isHead = bSecondHead;
			(*itConjunction)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent.SetValue(iConjParent);
			(*itConjunction)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower.SetValue(iConjPower);
		}
		SS_CATCH(L"")
		return true;
	}
	
	//���������� ��������� �������� ��������
	std::wstring CExpertCoordinate::GetName() const
	{
		return L"ExpertCoordinate";
	}

}
}
}