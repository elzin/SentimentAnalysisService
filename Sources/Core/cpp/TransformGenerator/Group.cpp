#include "StdAfx.h"
#include ".\Group.h"

#include <tchar.h>

#include "..\FeatureLibrary\define.h"
using namespace SS::Core::Features;

#include "..\ASSInterface\Iterators.h"
using namespace SS::Iterators;


namespace SS
{
namespace TransformGenerator
{

/////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

CGroup::CGroup(IBlackBoxQueryStorage* pBlackBoxQueryStorage, IGroup* pGroup) :
		m_pBlackBoxQueryStorage(pBlackBoxQueryStorage),
		m_pGroup(pGroup),
		m_eCategory(scNull)
{
}

/////////////////////////////////////////////////////////////////////////////////////
// CGroup interface

bool CGroup::Create(IUnit* pTopUnit, const SUnitParams& oParams)
{
	SS_TRY
	{
		// ������� ������ ������
		m_pGroup = m_pBlackBoxQueryStorage->CreateGroup();
		if(!m_pGroup)
			return false;

		// ����������� �������������� ��������������
		m_eCategory = SS::TransformGenerator::GetSyntaxCategory(pTopUnit);

		// ����������� ����������������
		if(!pTopUnit->IsObligatory())
			m_pGroup->SetUnObligatory();

		m_pGroup->SetWeight(pTopUnit->GetWeight());

		// ������������� �������������� � �������������� �������������� ������
		BOOL bIsQuestion = FALSE;
		if(pTopUnit->GetSyntaxFeature())
		{
			m_pGroup->GetSyntaxFeature()->SetSyntaxCategory(pTopUnit->GetSyntaxFeature()->GetSyntaxCategory());

			bIsQuestion = pTopUnit->GetSyntaxFeature()->IsQuestion();
			if(bIsQuestion)
				m_pGroup->GetSyntaxFeature()->SetIsQuestion();
			else
				m_pGroup->GetSyntaxFeature()->SetIsNotQuestion();
		}

		for(CSentenceIterator it = pTopUnit; *it != pTopUnit->GetRightUnit(); ++it)
		{
			// ������� QueryUnit � ��������� ��� � ������, ���� � ���� ��� �����
			CQueryUnit oQueryUnit(m_pBlackBoxQueryStorage, NULL, oParams);
			if(!(*it)->HasChilds())
			{
				// ���� �������������� ������, �� �������� ������ ������ ����
				if(*it == pTopUnit || !(bIsQuestion && (*it)->GetLeftUnit()))
				{
					oQueryUnit.Create(*it, (*it)->GetParentUnit());
					m_pGroup->AddQueryUnit(oQueryUnit);
				}
			}
		}

		return true;
	}
	SS_CATCH(L"")

	Release();
	return false;
}

IGroup* CGroup::Clone()
{
	SS_TRY;

	bool b;
	IGroup* pGroup = InternalClone(true, &b);
	return pGroup;

	SS_CATCH(L"");
	return NULL;
}

IGroup* CGroup::CloneObligatory(bool* pbHasUnobligatoryUnits)
{
	SS_TRY;

	IGroup* pGroup = InternalClone(false, pbHasUnobligatoryUnits);
	return pGroup;

	SS_CATCH(L"");
	return NULL;
}

CGroup::operator IGroup*()
{
	return m_pGroup;
}

void CGroup::Release()
{
	if(m_pGroup)
		m_pGroup->Release();
	m_pGroup = NULL;
}

ESyntacticCategory CGroup::GetSyntaxCategory()
{
	return m_eCategory;
}

void CGroup::ToConsole()
{
	for(IQueryUnit* pQUnit = m_pGroup->GetFirstQueryUnit(); pQUnit; pQUnit = pQUnit->GetNextQueryUnit())
	{
		_tprintf(_T("%s "), pQUnit->GetWord());
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// CGroup functions

IGroup* CGroup::InternalClone(bool bCopyUnobligatory, bool* pbHasUnobligatoryUnits)
{
	SS_TRY;

	if(!bCopyUnobligatory && !m_pGroup->IsObligatory())
	{
		*pbHasUnobligatoryUnits = true;
		return NULL;
	}

	IGroup* pGroup = m_pBlackBoxQueryStorage->CreateGroup();
	if(!pGroup)
		return NULL;

	pGroup->SetSequenceID(m_pGroup->GetSequenceID());
	pGroup->SetWeight(m_pGroup->GetWeight());

	// �������� ����������������
	if(m_pGroup->IsObligatory())
		pGroup->SetObligatory();
	else
		pGroup->SetUnObligatory();

	// �������� �������������� � �������������� �������������� ������
	if(m_pGroup->GetSyntaxFeature())
	{
		pGroup->GetSyntaxFeature()->SetSyntaxCategory(m_pGroup->GetSyntaxFeature()->GetSyntaxCategory());
		if(m_pGroup->GetSyntaxFeature()->IsQuestion())
			pGroup->GetSyntaxFeature()->SetIsQuestion();
		else
			pGroup->GetSyntaxFeature()->SetIsNotQuestion();
	}

	// �������� QueryUnit-�
	for(IQueryUnit* pQUnit = m_pGroup->GetFirstQueryUnit(); pQUnit; pQUnit = pQUnit->GetNextQueryUnit())
	{
		if(!bCopyUnobligatory && !pQUnit->IsObligatory())
		{
			*pbHasUnobligatoryUnits = true;
			continue;
		}

		CQueryUnit oQueryUnit(m_pBlackBoxQueryStorage, pQUnit);
		pGroup->AddQueryUnit(oQueryUnit.Clone());
	}

	// ���� ��� ����� � ������ �������������, ������� ��� ������
	if(pGroup->IsEmpty() && !m_pGroup->IsEmpty())
		pGroup->Release();
	else
		return pGroup;

	SS_CATCH(L"");
	return NULL;
}

}
}
