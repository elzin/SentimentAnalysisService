#pragma once

#include "..\ASSInterface\IBlackBox.h"
using namespace SS::Interface::Core::BlackBox;
using namespace SS::Interface::Core::BlackBox::Query;

#include "QueryUnitIndexCollection.h"

#include "..\ASSInterface\TDictionaryManager.h"
using namespace SS::Dictionary::Types;

#include "TypeChecker.h"


namespace SS
{
namespace TransformGenerator
{

/// ��������� ���������� IQueryUnit-�
struct SUnitParams
{
	explicit SUnitParams(bool bIDForm = false, bool bUnobligatoryPredicate = false, bool bDoubleIndex = false, CTypeChecker* pTypeChecker = NULL) :
			m_bIDForm(bIDForm),
			m_bUnobligatoryPredicate(bUnobligatoryPredicate),
			m_bDoubleIndex(bDoubleIndex),
			m_pTypeChecker(pTypeChecker)
	{
	}

	bool m_bIDForm;
	bool m_bUnobligatoryPredicate;
	bool m_bDoubleIndex;				// put both generic and non-generic semantic indexes
	CTypeChecker* m_pTypeChecker;
};

/// ��� ���������� ����� ���������, ����������� ��������� ������� CGroup::SetSyntaxCategory!!!
enum ESyntacticCategory
{
	scNull,
	scMainEntity,
	scPredicate, 
	scAdditionalEntity,
	scAjunct
};

ESyntacticCategory GetSyntaxCategory(IUnit* pUnit);

/// ����� �������������� ���������������� �� �������� � ������������ �������� ���� IQueryUnit
class CQueryUnit
{
public:
	CQueryUnit(IBlackBoxQueryStorage* pBlackBoxQueryStorage, IQueryUnit* pQueryUnit = NULL, 
		const SUnitParams& oParams = SUnitParams(false, false));

public:
	/// ������� QueryUnit �� �����
	bool Create(IUnit* pUnit, IUnit* pParentUnit);
	/// ������� ����� QueryUnit � �������� � ���� ���������� m_pQueryUnit
	IQueryUnit* Clone();
	operator IQueryUnit*();
	void Release();

private:
	void AddQueryUnitIndex(IQueryUnitIndexCollection* pQueryUnitIndexCollection, IIndex* pIndex, BOOL bIsQuestion = FALSE);

private:
	const SUnitParams m_oParams;
	IQueryUnit* m_pQueryUnit;
	IBlackBoxQueryStorage* m_pBlackBoxQueryStorage;
	ESyntacticCategory m_eCategory;
};

}
}
