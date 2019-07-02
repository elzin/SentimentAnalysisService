#pragma once


namespace SS
{
namespace Core
{
namespace BlackBox
{

class CRootItem;

class CLeafItem
{
	friend class CRootItem;
public:
	CLeafItem();
	virtual ~CLeafItem();

public:
	///��������� ������� ������ �� ����
	void InsertItem(CLeafItem* pItem);
	///�������� ���� �� ������������� ������ ����� � ���������� ������� ������
	CLeafItem* PopItem();
	///������� ���� ����� ����� � �������� ���� �� ������ ����� ������ ��������
	CLeafItem* ReleaseItem();
	///���������� ������� ������
	CLeafItem* GetRight();
	///���������� ������� �����
	CLeafItem* GetLeft();
	///���������� ������������ �������
	CRootItem* GetParent();

private:
	CLeafItem* m_pLeft;
	CLeafItem* m_pRight;
	CRootItem* m_pParent;
};

}
}
}
