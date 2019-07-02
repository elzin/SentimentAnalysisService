#include "StdAfx.h"
#include ".\expertfragmentationrussian.h"

namespace SS
{
namespace Syntax
{
namespace ExpertModel
{
	//�����������
	CExpertFragmentationRusInd::CExpertFragmentationRusInd()
	{
		//�������
		m_Divisor = L",";
		//���������� ���������
		m_Symbols.push_back(L"(");
		m_Symbols.push_back(L")");
		//���������� ���������
		m_Adverbs.push_back(L"���");
		m_Adverbs.push_back(L"����");
		m_Adverbs.push_back(L"������");
		m_Adverbs.push_back(L"�����");
		m_Adverbs.push_back(L"����");
		m_Adverbs.push_back(L"��������");
		m_Adverbs.push_back(L"����");
		m_Adverbs.push_back(L"���������");
		m_Adverbs.push_back(L"�������");
		//������ �� �������������
		CBaseExpertFragmentation::SetBracketAnalyse(false);
	}

	//��������� ������� �������� ������� �� �����
	bool CExpertFragmentationRusInd::IsConj(BoardElements::BoardElementsIterator elem) const
	{
		return ( /*IsSymbol(elem) ||*/
				 IsMultiSimbol(elem) ||
				 IsAdverb(elem) );
	}

	//�������� ������� ��������
	bool CExpertFragmentationRusInd::IsSymbol(BoardElements::BoardElementsIterator elem) const
	{
		SS_TRY
		{
			if ( find(m_Symbols.begin(), m_Symbols.end(), (*elem)->GetWord()) != m_Symbols.end() )
			{
				(*elem)->SetBeatsBlocks();
				return true;
			}
		}
		SS_CATCH(L"")
		return false;
	}

	///�������� ������� ������ ��������
	bool CExpertFragmentationRusInd::IsMultiSimbol(BoardElements::BoardElementsIterator elem) const
	{
		SS_TRY
		{
			//������ �������
			if ((*elem)->GetWord() != m_Divisor)
				return false;
			
			using namespace SS::Core::Features;
			bool bPretext = false;
		
			//������ �������
			++elem;
			SS::Syntax::BoardElements::PMORPHO pMorpho;
			for (pMorpho = (*elem)->GetFirstMorphoDynamic(); pMorpho; pMorpho = (*elem)->GetNextMorphoDynamic())
			{
				//���� ��� �����������
				if ( (pMorpho->GetMorphoFeature().m_OfficialType.Equal(Values::OfficialType.otConjunction)) ||
					 (pMorpho->GetMorphoFeature().m_PronounClass.Equal(Values::PronounClass.pncInterrogativeRelative)) )
				{
					(*elem)->SetBeatsBlocks();
					(*(--elem))->SetBeatsBlocks();
					return true;
				}
				//�������
				if (pMorpho->GetMorphoFeature().m_OfficialType.Equal(Values::OfficialType.otPretext)) 
				{ bPretext = true; }
			}
			//���� �������� �� ����
			if (!bPretext) return false;
			
			//������ �������
			if (++elem == m_last) return false;
			
			for (pMorpho = (*elem)->GetFirstMorphoDynamic(); pMorpho; pMorpho = (*elem)->GetNextMorphoDynamic())
			{
				//�����������
				if ( pMorpho->GetMorphoFeature().m_PronounClass.Equal(Values::PronounClass.pncInterrogativeRelative) )
				{
					(*elem)->SetBeatsBlocks();
					(*(--elem))->SetBeatsBlocks();
					(*(--elem))->SetBeatsBlocks();
					return true;
				}
			}
		}
		SS_CATCH(L"")
		return false;
	}

	///�������� ������� �������
	bool CExpertFragmentationRusInd::IsAdverb(BoardElements::BoardElementsIterator elem) const
	{
		SS_TRY
		{
			//������ �������
			if ((*elem)->GetWord() != m_Divisor)
				return false;
			//������ �������
			++elem;
			if ( find(m_Adverbs.begin(), m_Adverbs.end(), (*elem)->GetWord()) != m_Adverbs.end() ) 
			{
				(*elem)->SetBeatsBlocks();
				(*(--elem))->SetBeatsBlocks();
				return true;
			}
		}
		SS_CATCH(L"")
		return false;
	}
	
	//���������� ��������� �������� �������� 
	std::wstring CExpertFragmentationRusInd::GetName() const
	{
		return L"ExpertFragmentationRusInd";	
	}

}
}
}