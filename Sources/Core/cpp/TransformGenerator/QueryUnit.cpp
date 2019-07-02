#include "StdAfx.h"
#include ".\QueryUnit.h"
#include ".\QueryUnitIndexCollection.h"

#include "..\ASSInterface\TDictionaryManager.h"
using namespace SS::Dictionary::Types;


namespace SS
{
namespace TransformGenerator
{

/////////////////////////////////////////////////////////////////////////////////////
// Globals

ESyntacticCategory GetSyntaxCategory(IUnit* pUnit)
{
	if(!pUnit)
		return scNull;

	for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
	{
		if(pIndex->GetDictionaryIndex()->GetFirst().GetIndexType() == eitSyntaxIndex)
		{
			unsigned int uiIndex = pIndex->GetDictionaryIndex()->GetFirst().GetId();
			if(uiIndex == Values::SyntaxCategories.scMainEntity.GetSingleValue())
				return scMainEntity;
			else if(uiIndex == Values::SyntaxCategories.scAdditionalEntity.GetSingleValue())
				return scAdditionalEntity;
			else if(uiIndex == Values::SyntaxCategories.scPredicate.GetSingleValue())
				return scPredicate;
			else if(uiIndex == Values::SyntaxCategories.scAjunct.GetSingleValue())
				return scAjunct;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

CQueryUnit::CQueryUnit(IBlackBoxQueryStorage* pBlackBoxQueryStorage, IQueryUnit* pQueryUnit, const SUnitParams& oParams) : 
		m_oParams(oParams),
		m_pQueryUnit(pQueryUnit),
		m_pBlackBoxQueryStorage(pBlackBoxQueryStorage),
		m_eCategory(scNull)
{
}

/////////////////////////////////////////////////////////////////////////////////////
// CQueryUnit interface

bool CQueryUnit::Create(IUnit* pUnit, IUnit* pParentUnit)
{
	SS_TRY
	{
		if(!pUnit)
			return false;

		m_eCategory = GetSyntaxCategory(pParentUnit);

		// ������� ���� ������
		m_pQueryUnit = m_pBlackBoxQueryStorage->CreateQueryUnit();
		if(!m_pQueryUnit)
			return false;

		m_pQueryUnit->SetWord(pUnit->GetWord());

		// ����������� ����������������
		if(!pUnit->IsObligatory())
			m_pQueryUnit->SetUnObligatory();

		m_pQueryUnit->SetWeight(pUnit->GetWeight());

		// ������� ��������������� ���������
		CQueryUnitIndexCollection oMorphoIndexCollection(m_pBlackBoxQueryStorage);
		if(!oMorphoIndexCollection.Create(eitMorphoIndex, 1.0))
		{
			Release();
			return false;
		}

		// ������� �������������� ���������
		CQueryUnitIndexCollection oSyntaxIndexCollection(m_pBlackBoxQueryStorage);
		if(!oSyntaxIndexCollection.Create(eitSyntaxIndex, 1.0))
		{
			Release();
			return false;
		}

		// ������� ������������� ���������
		CQueryUnitIndexCollection oSemanticIndexCollection(m_pBlackBoxQueryStorage);
		if(!oSemanticIndexCollection.Create(eitSemanticIndex, 1.0))
		{
			Release();
			return false;
		}

		// ������� ��������� ���������
		CQueryUnitIndexCollection oSynonimsIndexCollection(m_pBlackBoxQueryStorage);
		if(!oSynonimsIndexCollection.Create(eitSynonymIndex, 1.0))
		{
			Release();
			return false;
		}

		// ��������� ���������
		BOOL bIsQuestion;
		if(pParentUnit)
			bIsQuestion = pParentUnit->GetSyntaxFeature() ? pParentUnit->GetSyntaxFeature()->IsQuestion() : FALSE;
		else
			bIsQuestion = pUnit->GetSyntaxFeature() ? pUnit->GetSyntaxFeature()->IsQuestion() : FALSE;
		for(IIndex* pIndex = pUnit->GetFirstIndex(); pIndex; pIndex = pUnit->GetNextIndex())
		{
			if(pIndex->GetDictionaryIndex())
			{
				switch(pIndex->GetDictionaryIndex()->GetFirst().GetIndexType())
				{
					case eitMorphoIndex:
						// ���� �������� ����� �������������� �-��, �� �������� ��������������� �������
						if(!bIsQuestion)
							AddQueryUnitIndex(oMorphoIndexCollection, pIndex);
						break;
					case eitSyntaxIndex:
						AddQueryUnitIndex(oSyntaxIndexCollection, pIndex);
						break;
					case eitSemanticIndex:
						AddQueryUnitIndex(oSemanticIndexCollection, pIndex, bIsQuestion);
						break;
					case eitSynonymIndex:
						if(!bIsQuestion)
							AddQueryUnitIndex(oSynonimsIndexCollection, pIndex);
						break;
					default:
						break;
				}
			}
		}

		// ��������� ��������������� ��������� � �����
		if(!oMorphoIndexCollection.IsEmpty())
			m_pQueryUnit->AddQueryUnitIndexCollection(oMorphoIndexCollection);
		else
			oMorphoIndexCollection.Release();

		// ��������� �������������� ��������� � �����
		if(!oSyntaxIndexCollection.IsEmpty())
			m_pQueryUnit->AddQueryUnitIndexCollection(oSyntaxIndexCollection);
		else
			oSyntaxIndexCollection.Release();

		// ��������� ������������� ��������� � �����
		if(!oSemanticIndexCollection.IsEmpty())
			m_pQueryUnit->AddQueryUnitIndexCollection(oSemanticIndexCollection);
		else
			oSemanticIndexCollection.Release();

		// ��������� ��������� ��������� � �����
		if(!oSynonimsIndexCollection.IsEmpty())
			m_pQueryUnit->AddQueryUnitIndexCollection(oSynonimsIndexCollection);
		else
			oSynonimsIndexCollection.Release();

		return true;
	}
	SS_CATCH(L"")

	Release();
	return false;
}

IQueryUnit* CQueryUnit::Clone()
{
	IQueryUnit* pQueryUnit = NULL;
	SS_TRY
	{
		// ������� ���� ������
		pQueryUnit = m_pBlackBoxQueryStorage->CreateQueryUnit();
		if(!pQueryUnit)
			return NULL;

		pQueryUnit->SetWord(m_pQueryUnit->GetWord());

		if(m_pQueryUnit->IsObligatory())
			pQueryUnit->SetObligatory();
		else
			pQueryUnit->SetUnObligatory();

		pQueryUnit->SetSequenceID(m_pQueryUnit->GetSequenceID());
		pQueryUnit->SetWeight(m_pQueryUnit->GetWeight());

		// ������� ���������
		CQueryUnitIndexCollection oMorphoIndexCollection(m_pBlackBoxQueryStorage, 
			m_pQueryUnit->GetQueryUnitIndexCollection(eitMorphoIndex));
		CQueryUnitIndexCollection oSyntaxIndexCollection(m_pBlackBoxQueryStorage, 
			m_pQueryUnit->GetQueryUnitIndexCollection(eitSyntaxIndex));
		CQueryUnitIndexCollection oSemanticIndexCollection(m_pBlackBoxQueryStorage, 
			m_pQueryUnit->GetQueryUnitIndexCollection(eitSemanticIndex));
		CQueryUnitIndexCollection oSynonimsIndexCollection(m_pBlackBoxQueryStorage, 
			m_pQueryUnit->GetQueryUnitIndexCollection(eitSynonymIndex));

		// ��������� ��������� � ��������� � �����
		if(!oMorphoIndexCollection.IsEmpty())
			pQueryUnit->AddQueryUnitIndexCollection(oMorphoIndexCollection.Clone());

		if(!oSyntaxIndexCollection.IsEmpty())
			pQueryUnit->AddQueryUnitIndexCollection(oSyntaxIndexCollection.Clone());

		if(!oSemanticIndexCollection.IsEmpty())
			pQueryUnit->AddQueryUnitIndexCollection(oSemanticIndexCollection.Clone());

		if(!oSynonimsIndexCollection.IsEmpty())
			pQueryUnit->AddQueryUnitIndexCollection(oSynonimsIndexCollection.Clone());

		return pQueryUnit;
	}
	SS_CATCH(L"")

	if(pQueryUnit)
		pQueryUnit->ReleaseQueryUnit();

	return NULL;
}

CQueryUnit::operator IQueryUnit*()
{
	return m_pQueryUnit;
}

void CQueryUnit::Release()
{
	if(m_pQueryUnit)
	{
		m_pQueryUnit->ReleaseQueryUnit();
		m_pQueryUnit = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// CQueryUnit functions

void CQueryUnit::AddQueryUnitIndex(IQueryUnitIndexCollection* pQueryUnitIndexCollection, IIndex* pIndex,
								   BOOL bIsQuestion)
{
	SS_TRY;

	if(!pQueryUnitIndexCollection)
		return;

	unsigned int uiTempIndex = pIndex->GetDictionaryIndex()->GetFirst().GetId();
	EIndexType eit = pQueryUnitIndexCollection->GetIndexCollectionType();
	if(eit == eitSyntaxIndex &&
		(uiTempIndex == 0 || 
		uiTempIndex == Values::SyntaxCategories.scMainEntity.GetSingleValue() || 
		uiTempIndex == Values::SyntaxCategories.scAdditionalEntity.GetSingleValue() ||
		uiTempIndex == Values::SyntaxCategories.scPredicate.GetSingleValue() ||
		uiTempIndex == Values::SyntaxCategories.scAjunct.GetSingleValue()))
	{
		// �� ��� �� �������������� �������� ������� � ���������
		return;
	}

	// ������� ������ ���������
	IQueryUnitIndex* pQueryUnitIndex = m_pBlackBoxQueryStorage->CreateQueryUnitIndex();
	if(!pQueryUnitIndex)
		return;

	// ��������� idForm-�
	if(m_oParams.m_bIDForm && m_eCategory == scPredicate)
	{
		for(IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
			pQueryUnitIndex->AddIDForm(pFeature->GetMorphoIndex());
	}

	if(m_oParams.m_pTypeChecker->IsSuperlativeForm(pIndex))
	{
		for(IFeature* pFeature = pIndex->GetFirstFeature(); pFeature; pFeature = pIndex->GetNextFeature())
			pQueryUnitIndex->AddIDForm(pFeature->GetMorphoIndex());
	}

	// ������� �������� �������
	pQueryUnitIndex->SetIndex(pIndex->GetDictionaryIndex()->GetFirst().GetDictionaryIndex());
	if(bIsQuestion)
	{
		pQueryUnitIndex->GetIndex().SetGenericMarker(false);

		// ��� �������� ���� NameDef ��������� ������� ����� ������������� ��������
		if(m_oParams.m_bDoubleIndex)
		{
			IQueryUnitIndex* pInd = m_pBlackBoxQueryStorage->CreateQueryUnitIndex();
			if(pInd)
			{
				pInd->SetIndex(pQueryUnitIndex->GetIndex());
				pInd->GetIndex().SetGenericMarker(true);
				pQueryUnitIndexCollection->AddQueryUnitIndex(pInd);
			}
		}
	}

	// ��������� ������ � ���������
	pQueryUnitIndexCollection->AddQueryUnitIndex(pQueryUnitIndex);

	SS_CATCH(L"");
}

}
}
