#pragma once

#include "..\ASSInterface\IBlackBox.h"
using namespace SS::Interface::Core::BlackBox;
using namespace SS::Interface::Core::BlackBox::Query;

#include "QueryUnit.h"


namespace SS
{
namespace TransformGenerator
{

/// ����� �������������� ���������������� �� �������� � ������������ �������� ���� IGroup
class CGroup
{
public:
	CGroup(IBlackBoxQueryStorage* pBlackBoxQueryStorage, IGroup* pGroup = NULL);

public:
	/// ������� IGroup �� �����
	bool Create(IUnit* pTopUnit, const SUnitParams& oParams);
	/// ������� ����� ������ � �������� � ��� ���������� m_pGroup
	IGroup* Clone();
	IGroup* CloneObligatory(bool* pbHasUnobligatoryUnits);
	operator IGroup*();
	void Release();

	/// ���������� �������������� ��������� ������
	ESyntacticCategory GetSyntaxCategory();

	void ToConsole();

private:
	IGroup* InternalClone(bool bCopyUnobligatory, bool* pbHasUnobligatoryUnits);

private:
	IGroup* m_pGroup;
	IBlackBoxQueryStorage* m_pBlackBoxQueryStorage;
	ESyntacticCategory m_eCategory;
};

}
}
