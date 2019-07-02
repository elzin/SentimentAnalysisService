#pragma once

#include "RootItem.h"


namespace SS
{
namespace Core
{
namespace BlackBox
{

class CRootIterateItem : public CRootItem
{
public:
	CRootIterateItem(/*CRootItem* pParent = 0*/);
	virtual ~CRootIterateItem();

public:
	///���������� ��� �������� �������� �� ������ �����
	virtual void OnPopItem(CLeafItem* pItem);
	///���������� ������� �������
	virtual CLeafItem* GetFirstChild();
	///���������� ���������� �������
	virtual CLeafItem* GetLastChild();
	///���������� ���������� �������
	CLeafItem* GetNextChild();
	///���������� ���������� �������
	CLeafItem* GetPrevChild();

private:
	CLeafItem* m_pCurrItem;
	//CRootItem* m_pParent;
};

class CMiddleIterateItem :
		public CRootIterateItem,
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
