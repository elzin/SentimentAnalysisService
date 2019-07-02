#pragma once

#include "..\ASSInterface\IBlackBox.h"
using namespace SS::Interface::Core::BlackBox;
using namespace SS::Interface::Core::BlackBox::Query;

#include "..\FeatureLibrary\define.h"
using namespace SS::Core::Features;


namespace SS
{
namespace TransformGenerator
{

/// ����� �������������� ���������������� �� �������� � ������������ �������� ���� IQueryUnitIndexCollection
class CQueryUnitIndexCollection
{
public:
	CQueryUnitIndexCollection(IBlackBoxQueryStorage* pBlackBoxQueryStorage, 
		IQueryUnitIndexCollection* pColl = NULL);
	~CQueryUnitIndexCollection();

public:
	/// ������� ����� ��������� �������� �� ���� � ����
	bool Create(EIndexType type, float flWeight);
	/// ������� ����� ��������� �������� � �������� � ��� ���������� m_pColl
	IQueryUnitIndexCollection* Clone();
	operator IQueryUnitIndexCollection*();
	void Release();
	bool IsEmpty();

private:
	IQueryUnitIndexCollection* m_pColl;
	IBlackBoxQueryStorage* m_pBlackBoxQueryStorage;
};

}
}
