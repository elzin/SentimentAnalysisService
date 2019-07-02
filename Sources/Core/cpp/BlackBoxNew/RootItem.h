#pragma once

#include "LeafItem.h"


namespace SS
{
namespace Core
{
namespace BlackBox
{

class CRootItem
{
	friend class CLeafItem;
public:
	CRootItem();
	virtual ~CRootItem();

public:
	///��������� ������� �������
	void AddChild(CLeafItem* pItem);
	///������� ���� �����
	void ReleaseChildren();
	///��������� ���� �� ����
	bool IsItemEmpty();
	///������� ����
	virtual CLeafItem* ReleaseItem();
	///���������� ������� �������
	virtual CLeafItem* GetFirstChild();
	///���������� ���������� �������
	virtual CLeafItem* GetLastChild();
	///���������� ��� �������� �������� �� ������ �����
	virtual void OnPopItem(CLeafItem* pItem) { }

private:
	CLeafItem* m_pLeftChild;
	CLeafItem* m_pRightChild;
};

class CMiddleItem : 
		public CRootItem,
		public CLeafItem
{
protected:
	virtual CLeafItem* ReleaseItem()
	{
		CRootItem::ReleaseChildren();
		return CLeafItem::ReleaseItem();
	}
};

}
}
}
