//FeatureController.h
#pragma once
#include "../ASSInterface/Construction.h"
#include "../ASSInterface/IDictionaryManager.h"
#include "./BoardElement.h"

namespace SS
{
namespace Syntax
{
namespace ModifiedConstruction
{
	using namespace SS::SyntaxConstructions::Types;
	using namespace SS::Syntax::BoardElements;
		
	///������������ �����, ������� ��� CFeatureController
	class IFeatureController
	{
	public:
		///�������� ������������ ������������� �������� ����� ��������� ��������������� �������� �����������
		virtual bool IsAppropriate(CBoardElement* pElem) = 0;
		///������� ������ �����������
		virtual CConstructionObject* GetConstructionObject() = 0;
		///���������� �������� ��� �������� position
		virtual void InitRange(BoardElementsIterator* pFirstIt, BoardElementsIterator* pLastIt) = 0;
	};
	
	///����� ��� �������� ������������ ������� ����������� � �������� �����
	template<typename TForm, typename TPosition>
	class CFeatureController : public IFeatureController
	{
	private:
		///������ Form
		TForm m_oForm;
		///������ ����������� ��������������� ������� �����������
		CConstructionObject* m_pConObj;
		///������ ������� ��������� ������
		BoardElementsIterator* m_pFirstIt;
		///����������� ������� ��������� ������
		BoardElementsIterator* m_pLastIt;
		///���� �����������
		ExpertModel::ESyntaxBase m_eBase;

	private:
		///�������� ��������������� �������������
		bool IsAppropriateMorpho(CBoardElement* pElem);
		///�������� �������������� �������������
		bool IsAppropriateSyntax(CBoardElement* pElem);
		///�������� ������������� �������������
		bool IsAppropriateSemantic(CBoardElement* pElem);

	public:
		///�����������
		CFeatureController( SS::SyntaxConstructions::Types::CConstructionObject* pConObj,
							SS::Interface::Core::Dictionary::IDictionary* pDictionary,
							ExpertModel::ESyntaxBase eBase);
		///����������
		~CFeatureController(){};
		///�������� ������������ ������������� �������� ����� ��������� ��������������� �������� �����������
		bool IsAppropriate(CBoardElement* pElem);
		///������� ������ �����������
		CConstructionObject* GetConstructionObject() { return m_pConObj; };
		///���������� �������� ��� �������� position
		void InitRange(BoardElementsIterator* pFirstIt, BoardElementsIterator* pLastIt) { m_pFirstIt = pFirstIt; m_pLastIt = pLastIt; };
	};

	///�����������
	template<typename TForm, typename TPosition>
	CFeatureController<TForm, TPosition>::CFeatureController( SS::SyntaxConstructions::Types::CConstructionObject* pConObj,
															  SS::Interface::Core::Dictionary::IDictionary* pDictionary,
															  ExpertModel::ESyntaxBase eBase )
	:
	m_pConObj(pConObj),
	m_pFirstIt(NULL),
	m_pLastIt(NULL),
	m_eBase(eBase)
	{
		SS_TRY
		{
			m_oForm.InitData(pConObj, pDictionary);
		}
		SS_CATCH(L"")
	}

	///�������� ������������ ������������� �������� ����� ��������� ��������������� �������� �����������
	template<typename TForm, typename TPosition>
	bool CFeatureController<TForm, TPosition>::IsAppropriate(CBoardElement* pElem)
	{
		if ( !TPosition::IsAppropriatePosition(pElem, *m_pFirstIt, *m_pLastIt) )
		{ return false; }

		return ( IsAppropriateMorpho(pElem) &&
				 IsAppropriateSyntax(pElem) &&
				 IsAppropriateSemantic(pElem) );
	}

	///�������� ��������������� �������������
	template<typename TForm, typename TPosition>
	bool CFeatureController<TForm, TPosition>::IsAppropriateMorpho(CBoardElement* pElem)
	{
		SS_TRY
		{
			if ( !m_oForm.IsEqualWord(pElem) )
			{ return false; }

			for (PMORPHO pMorpho = pElem->GetFirstMorpho(); pMorpho; pMorpho = pElem->GetNextMorpho())
			{
				if ( m_pConObj->m_MorphoFeatureApriori.IsIntersectsWith(pMorpho->GetMorphoFeature(), pElem->GetLang()) )
				{ return true; }
			}
		}
		SS_CATCH(L"")
		return false;
	}

	///�������� �������������� �������������
	template<typename TForm, typename TPosition>
	bool CFeatureController<TForm, TPosition>::IsAppropriateSyntax(CBoardElement* pElem)
	{
		return m_pConObj->m_SyntaxFeatureApriori.IsIntersectsOrEmpty(&pElem->GetSyntaxFeatureApriori());
	}

	///�������� ������������� �������������
	template<typename TForm, typename TPosition>
	bool CFeatureController<TForm, TPosition>::IsAppropriateSemantic(CBoardElement* pElem)
	{
		if (m_eBase == ExpertModel::sbRussianNQ)
		{ return m_pConObj->m_SemanticFeatureApriori.IsIntersectsOrEmptyDeep(pElem->GetSemanticFeature()); }
		return m_pConObj->m_SemanticFeatureApriori.IsIntersectsOrEmpty(pElem->GetSemanticFeature());
	}

}
}
}