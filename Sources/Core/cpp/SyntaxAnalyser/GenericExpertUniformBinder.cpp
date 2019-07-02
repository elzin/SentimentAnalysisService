#include "stdafx.h"
#include "GenericExpertUniformBinder.h"
#include <algorithm>

namespace SS
{
namespace Syntax
{
namespace ExpertModel
{
	using namespace std;

	CGenericExpertUniformBinderEng::CGenericExpertUniformBinderEng()
	{
		m_conjunctions.push_back( L"and" );
		m_conjunctions.push_back( L"or" );
		m_conjunctions.push_back( L"," );
	}

	//������ �� �����
	bool CGenericExpertUniformBinderEng::PassBoard(BoardElements::CBoard & rBoard, BoardElements::PBLOCK pBlock)
	{
		SS_TRY
		{
			//��������� ����������� �����
			BoardElements::PBLOCK pPrevBlock = rBoard.GetPrevBlock();
			if ( (!pPrevBlock) || pPrevBlock->Empty() ) 
			{ return true; }

			if ( find(m_conjunctions.begin(), m_conjunctions.end(), (*(pBlock->GetFirst()))->GetWord()) == m_conjunctions.end() )
			{ return true; }

			/* ������� �������� (�������) ����� */

			BoardElements::BoardElementsIterator secondUniformMember = pBlock->GetFirst();
			++secondUniformMember;
						
			//���� SubjectFin
			while ( (secondUniformMember != pBlock->GetLast()) && 
			(!(*secondUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal(Values::SyntaxCategories.scSubjectFin) ) ) 
			{ secondUniformMember++; }
			//���� �� ����� SubjectFin �� �����
			if (secondUniformMember == pBlock->GetLast())
			{ return true; }
			
			//����� ���� ������ ���� Noun Pronoun ��� Adjective
			if( ((*secondUniformMember)->GetFirstMorpho()->GetMorphoFeature().m_PartOfSpeechTypes.GetValue() != 
				Values::PartOfSpeechTypes.postNoun.GetValue()) &&
				((*secondUniformMember)->GetFirstMorpho()->GetMorphoFeature().m_PartOfSpeechTypes.GetValue() != 
				Values::PartOfSpeechTypes.postPronoun.GetValue()) && 
				((*secondUniformMember)->GetFirstMorpho()->GetMorphoFeature().m_PartOfSpeechTypes.GetValue() != 
				Values::PartOfSpeechTypes.postAdjective.GetValue()) )
				return true;
			
			/* ������� ����������� (�������) ����� */
			
			//������� ����������� ����� ������ ���� �������� � Noun
			BoardElements::BoardElementsIterator firstUniformMember;
			for (firstUniformMember = pPrevBlock->GetFirst(); firstUniformMember != pPrevBlock->GetLast(); ++firstUniformMember)
			{
				if ( (*firstUniformMember)->GetFirstMorpho()->GetMorphoFeature().m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postNoun) &&
					 (*firstUniformMember)->GetVerElem()->m_isHead )
				{ break; }
			}
			
			if (firstUniformMember == pPrevBlock->GetLast())
			{ return true; }

			if( !(*firstUniformMember)->GetFirstMorpho()->GetMorphoFeature().IsEqualUniformMember(	//������� ���� ����� ��������� �� �����, 
			    ( (*secondUniformMember)->GetFirstMorpho()->GetMorphoFeature() ) ) )				//������� ��������� ������ ������ ����.
			{ return true; }

			//���������� ������� �������� �������� ��������
			m_oSyntaxFeatureAposteriori = (*firstUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori;
			bool bHead = (*firstUniformMember)->GetVerElem()->m_isHead;
			
			//����������� ������� ������� ����� � �������� �������
			(*firstUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent = (unsigned)distance( rBoard.ElementsBegin(), secondUniformMember );
			(*firstUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower = 100;
			(*firstUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories
			 =(*secondUniformMember)->GetSyntaxFeature().m_SyntaxCategories;
			(*firstUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategoryPower = 100;
			(*firstUniformMember)->GetVerElem()->m_isHead = false;

			//���������� ��� ����� � ����������� �������
			//���������� ����������� ������ �������� ������������ ������
			pBlock->AddBlock(pPrevBlock);
			
			//�������������� ������� �������� �������� ��������
			(*firstUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori = m_oSyntaxFeatureAposteriori;
			(*firstUniformMember)->GetVerElem()->m_isHead = bHead;
		}
		SS_CATCH(L"");
		return true;
	}

	bool CGenericExpertUniformBinderFinalEng::PassBoard(BoardElements::CBoard & rBoard, BoardElements::PBLOCK pBlock)
	{
		SS_TRY
		{
			//��������� ����������� �����
			BoardElements::PBLOCK pPrevBlock = rBoard.GetPrevBlock();
			if ( (!pPrevBlock) || pPrevBlock->Empty() ) 
			{ return true; }
			
			//���� ������ ����� �������� ����� �� ����
			if ( find(m_conjunctions.begin(), m_conjunctions.end(), (*(pBlock->GetFirst()))->GetWord()) == m_conjunctions.end() )
			{ return true; }

			const BoardElements::SBlockVersionCharacteristics* prevChar = NULL;
			prevChar = pPrevBlock->GetBestVersion().GetVersionCharacteristics();

			BoardElements::BoardElementsIterator secondUniformMember = pBlock->GetFirst();
			++secondUniformMember;
			
			//����� � ������� ����� (������) ������� ��������� �������� ����� �����
			while ( (secondUniformMember != pBlock->GetLast()) && (!((*secondUniformMember)->IsHead()) || (*secondUniformMember)->BeatsBlocks()) )
			{ ++secondUniformMember; }
				
			//���� ������� �������� ���
			if (secondUniformMember == pBlock->GetLast())
			{ return true; }
			
			/*������*/
			
			CMorphoFeature & secondElemFeature = (*secondUniformMember)->GetFirstMorpho()->GetMorphoFeature();
			bool secondSyntaxUndefined = (*secondUniformMember)->GetSyntaxFeature().m_SyntaxCategories.IsUndefined();
			
			BoardElements::BoardElementsIterator firstUniformMember;
			BoardElements::BoardElementsIterator firstUniformMember1;
			
			bool bNounOnly = AnalisNounOnly(pPrevBlock, secondUniformMember);

			int syntaxValSecond = (*secondUniformMember)->GetSyntaxFeature().m_SyntaxCategories.GetValue();
			if (syntaxValSecond & Values::SyntaxCategories.scMainEntity.GetValue())
			{
				bool isFindMain = false;
				bool isFindVerb = false;
				for (firstUniformMember = pPrevBlock->GetFirst(); firstUniformMember != pPrevBlock->GetLast(); ++firstUniformMember)
				{
					BoardElements::CBoardElement* elem = *firstUniformMember;
					//bool b1 = elem->GetSyntaxFeature1().m_SyntaxCategories.IsContain(Values::SyntaxCategories.scMainEntity.GetValue());
					int i1 = elem->GetSyntaxFeature().m_SyntaxCategories.GetValue() & Values::SyntaxCategories.scMainEntity.GetValue();
					int i2 = elem->GetSyntaxFeature().m_SyntaxCategories.GetValue() & Values::SyntaxCategories.scSubjectFin.GetValue();
					bool b1 = elem->IsSemantic(elem->GetUnit(), Values::TSemanticType.smtPerson);
					//bool b1 =
					//	->GetSyntaxFeature().m_SyntaxCategories.Values::SyntaxCategories.scMainEntity.GetValue()
					wstring str1 = elem->GetUnit()->GetWordFull();
					if ((i1 && (*firstUniformMember)->IsHead()) || (i2 && b1))
				
					{
						firstUniformMember1 = firstUniformMember;
						isFindMain = true;
					}
					if (isFindMain && ((*firstUniformMember)->GetSyntaxFeature().m_SyntaxCategories.GetValue()==
						Values::SyntaxCategories.scMain.GetValue()||
						(*firstUniformMember)->GetFirstMorpho()->GetMorphoFeature().m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postVerb)))
					{
						isFindVerb = true; 
					}											
				}
				//if (firstUniformMember == pPrevBlock->GetLast())
				if (!isFindMain || isFindVerb)
				{ return true; }
				else  
				{ firstUniformMember = firstUniformMember1; }
			}
			//else				
			////���� ������ ���������� ���� ������� ��������, �� ������ ���������� ������ 
			////�������� ��������� (Main) ����������� �����
			//if ( (secondElemFeature.m_PartOfSpeechTypes.GetValue() == Values::PartOfSpeechTypes.postVerb.GetValue()) &&
			//	(prevChar->m_isMainRoot) && 
			//	(secondSyntaxUndefined) &&
			//	(!(bNounOnly)) )
			//{
			//	//���� � ������ ����� Main				
			//	for (firstUniformMember = pPrevBlock->GetFirst(); firstUniformMember != pPrevBlock->GetLast(); ++firstUniformMember)
			//	{
			//		if ( (*firstUniformMember)->GetSyntaxFeature().m_SyntaxCategories.GetValue() == Values::SyntaxCategories.scMain.GetValue() )
			//		{ break; }										
			//		//if (isFindMain && (*firstUniformMember)->GetSyntaxFeature().m_SyntaxCategories.GetValue

			//		//{ break; }
			//	}
			//	if (firstUniformMember == pPrevBlock->GetLast())
			//	{ return true; }
			//}
			////���� ������ ���������� ���� ������� ���������, �� ������ ���������� ������ 
			////�������� ����������, ���������� ���������, ��������� � ����� �����
			//else if ( (*secondUniformMember)->GetFirstMorpho()->GetMorphoFeature().m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postOfficial) &&
			//		((*secondUniformMember)->GetFirstMorpho()->GetMorphoFeature().m_OfficialType.GetValue() & Values::OfficialType.otPretext.GetValue())
			//		&& (!(bNounOnly)) )
			//{
			//	//���� � ������ ����� Adjunct, ���������� ���������, ��������� � ����� �����
			//	if (!prevChar->m_isAdjunct)
			//	{ return true; }
			//	
			//	firstUniformMember = pPrevBlock->GetLast();
			//	while (true)
			//	{
			//		if (firstUniformMember == pPrevBlock->GetFirst())
			//		{ return true;}
			//		
			//		if ( !((*firstUniformMember)->GetFirstMorpho()->GetMorphoFeature().m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postOfficial) &&
			//			((*firstUniformMember)->GetFirstMorpho()->GetMorphoFeature().m_OfficialType.GetValue() & 
			//				Values::OfficialType.otPretext.GetValue())) )
			//		{
			//			firstUniformMember--;
			//			continue;
			//		}

			//		int syntaxVal = (*firstUniformMember)->GetSyntaxFeature().m_SyntaxCategories.GetValue();
			//		if ( syntaxVal & Values::SyntaxCategories.scAjunct.GetValue() ||
			//			syntaxVal & Values::SyntaxCategories.scAjunctCause.GetValue() ||
			//			syntaxVal & Values::SyntaxCategories.scAjunctGoal.GetValue() ||
			//			syntaxVal & Values::SyntaxCategories.scAjunctManner.GetValue() ||
			//			syntaxVal & Values::SyntaxCategories.scAjunctMeasure.GetValue() ||
			//			syntaxVal & Values::SyntaxCategories.scAjunctPlaceEnd.GetValue() ||
			//			syntaxVal & Values::SyntaxCategories.scAjunctPlaceEnd.GetValue() ||
			//			syntaxVal & Values::SyntaxCategories.scAjunctPlaceFixedPoint.GetValue() ||
			//			syntaxVal & Values::SyntaxCategories.scAjunctPlaceSource.GetValue() ||
			//			syntaxVal & Values::SyntaxCategories.scAjunctTimeDuration.GetValue() ||
			//			syntaxVal & Values::SyntaxCategories.scAjunctTimeEnd.GetValue() ||
			//			syntaxVal & Values::SyntaxCategories.scAjunctTimeSource.GetValue() )
			//		{
			//			break;
			//		}
			//		firstUniformMember--;
			//	}
			//}
			////���� ������ ���������� ���� �������� ��������������� ��� ������������
			////� ������ ����� ���� Adjunct, Attribute, SubjectComplement ��� Object, ��������� � ����� �����.
			////���� ������ Adjunct ��� Attribute, ���������� ���������, �� � ������ ����� ���� ObjectOfPreposition, 
			////��������� � ����� ����������� �����. ����� ������ ���������� ������ ����� ��������� �������.
			//else if ( (*secondUniformMember)->GetFirstMorpho()->GetMorphoFeature().m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postNoun) ||
			//		  (*secondUniformMember)->GetFirstMorpho()->GetMorphoFeature().m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postPronoun) )
			//{
			//	firstUniformMember = pPrevBlock->GetLast();
			//	int iSyntaxCategories;
			//	do 
			//	{
			//		--firstUniformMember;
			//		iSyntaxCategories = (*firstUniformMember)->GetSyntaxFeature().m_SyntaxCategories.GetValue();
			//		
			//		//���� ������ ���� Attribute ��� Adjunct
			//		if ( iSyntaxCategories & Values::SyntaxCategories.scAttribute.GetValue() ||
			//			 iSyntaxCategories & Values::SyntaxCategories.scAjunct.GetValue() ||
			//			 iSyntaxCategories & Values::SyntaxCategories.scAjunctCause.GetValue() ||
			//			 iSyntaxCategories & Values::SyntaxCategories.scAjunctGoal.GetValue() ||
			//			 iSyntaxCategories & Values::SyntaxCategories.scAjunctManner.GetValue() ||
			//			 iSyntaxCategories & Values::SyntaxCategories.scAjunctMeasure.GetValue() ||
			//			 iSyntaxCategories & Values::SyntaxCategories.scAjunctPlaceEnd.GetValue() ||
			//			 iSyntaxCategories & Values::SyntaxCategories.scAjunctPlaceEnd.GetValue() ||
			//			 iSyntaxCategories & Values::SyntaxCategories.scAjunctPlaceFixedPoint.GetValue() ||
			//			 iSyntaxCategories & Values::SyntaxCategories.scAjunctPlaceSource.GetValue() ||
			//			 iSyntaxCategories & Values::SyntaxCategories.scAjunctTimeDuration.GetValue() ||
			//			 iSyntaxCategories & Values::SyntaxCategories.scAjunctTimeEnd.GetValue() ||
			//			 iSyntaxCategories & Values::SyntaxCategories.scAjunctTimeSource.GetValue() )
			//		{
			//			//���� Attribute ��� Adjunct �������� ���������
			//			if ( (*firstUniformMember)->GetFirstMorpho()->GetMorphoFeature().m_OfficialType.Equal(Values::OfficialType.otPretext) )
			//			{
			//				//������ ���� ������ ���� ObjectOfPreposition
			//				bool bOOP = false; 
			//				firstUniformMember = pPrevBlock->GetLast();
			//				do 
			//				{
			//					--firstUniformMember;
			//					iSyntaxCategories = (*firstUniformMember)->GetSyntaxFeature().m_SyntaxCategories.GetValue();
			//					if ( iSyntaxCategories & Values::SyntaxCategories.scObjectOfPreposition.GetValue() )
			//					{
			//						bOOP = true;
			//						break;
			//					}
			//				}
			//				while (firstUniformMember != pPrevBlock->GetFirst());
			//				if (bOOP) 
			//				break; //���� ���������� �����
			//				else
			//				return true;
			//			}
			//		}
			//		//���� ������ ���� Object ��� SubjectComplement
			//		else if ( iSyntaxCategories & Values::SyntaxCategories.scObject.GetValue() ||
			//				  iSyntaxCategories & Values::SyntaxCategories.scSubjectComplement.GetValue() ) 
			//		{
			//			break; //���� ���������� �����
			//		}
			//		
			//		//���� ������ �� ���������(� ������� ���������)
			//		if (firstUniformMember == pPrevBlock->GetFirst()) 
			//		{ return true; }
			//	} 
			//	while (firstUniformMember != pPrevBlock->GetFirst());
			//}
			else
			{
				return true;  
			}

			//���������� ������� �������� �������� ��������
			m_oSyntaxFeatureAposteriori = (*secondUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori;
			bool bHead = (*secondUniformMember)->GetVerElem()->m_isHead;
			
			//�������� �������� ������� ����� � �������� �������
			(*secondUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_IdParent = (unsigned)distance( rBoard.ElementsBegin(), firstUniformMember );
			(*secondUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_DependencyPower = 100;
			(*secondUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategories
			 =(*firstUniformMember)->GetSyntaxFeature().m_SyntaxCategories;
			(*secondUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori.m_SyntaxCategoryPower = 100;
			(*secondUniformMember)->GetVerElem()->m_isHead = false;
			
			//���������� ��� ����� � ����������� �������
			//���������� ����������� ������ �������� ������������ ������
			pBlock->AddBlock(pPrevBlock);

			//�������������� ������� �������� �������� ��������
			(*secondUniformMember)->GetVerElem()->m_syntaxFeatureAposteriori = m_oSyntaxFeatureAposteriori;
			(*secondUniformMember)->GetVerElem()->m_isHead = bHead;
		}
		SS_CATCH(L"");
		return true;
	}

	bool CGenericExpertUniformBinderFinalEng::AnalisNounOnly( BoardElements::PBLOCK pBlockPrev, 
															  BoardElements::BoardElementsIterator itElemSecond ) const
	{
		SS_TRY
		{
			bool bIsNoun = false;
			
			/*������� �������� �����*/

			//�������� �� ������� ���������������� (Noun) � �������� ������� (�������) �����
			for (PMORPHO pMorpho = (*itElemSecond)->GetFirstMorphoDynamic(); pMorpho; pMorpho = (*itElemSecond)->GetNextMorphoDynamic())
			{
				if ( pMorpho->GetMorphoFeature().m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postNoun) )
				{ bIsNoun = true; }
			}
			//���� ������� ��������������� ���� �� ����� �� ����� false
			if ( !(bIsNoun) ) { return false; }

			/*������ ����������� �����*/
			
			//�������� �������
			int Avtomat[2][2] = { {1, 1}, 
								  {0, 2} }; //������ ������ ����� �������
			
			int	iState	= 0;
			const int WorkState = 2;
			const int Main		= 0;
			const int Object	= 1;

			BoardElements::BoardElementsIterator itElem;
			//������� ��������� ����������� �����
			for (itElem = pBlockPrev->GetFirst(); ((itElem != pBlockPrev->GetLast()) && (iState < WorkState)); itElem++)
			{
				if ( (*itElem)->GetSyntaxFeature().m_SyntaxCategories.Equal(Values::SyntaxCategories.scMain) )
				{
					iState = Avtomat[Main][iState];
				}
				else if ( (*itElem)->GetSyntaxFeature().m_SyntaxCategories.Equal(Values::SyntaxCategories.scObject) ) 
				{
					iState = Avtomat[Object][iState];
				}
			}

			//���������
			if (iState == WorkState)
			{ return true; }
			else
			{ return false; }
		}
		SS_CATCH(L"")
	}

}
}
}
