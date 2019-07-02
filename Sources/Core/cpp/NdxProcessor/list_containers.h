#pragma once

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Containers
{

//--------------------------------------------------------------------//

///���������������� ����� ����������������� ������
template <class TItemType>
class CUnidirListItem
{
public:
	CUnidirListItem(void):m_pNextItem(NULL){};
	virtual ~CUnidirListItem(void){};

	///���������� ��������� ���� � ������
	TItemType* GetNextItem(void){return m_pNextItem;};
	///������������� ��������� ���� � ������
	void SetNextItem(TItemType* pNextItem){m_pNextItem=pNextItem;};

protected:
	///��������� ����
	TItemType* m_pNextItem;
};

//--------------------------------------------------------------------//

///���������������� ����� ���������������� ������
template <class TItemType>
class CBidirListItem : public CUnidirListItem<TItemType>
{
public:
	CBidirListItem(void):m_pPrevItem(NULL){};
	virtual ~CBidirListItem(void){};

	///���������� ���������� ���� � ������
	TItemType* GetPrevItem(void){return m_pPrevItem;};
	///������������� ���������� ���� � ������
	void SetPrevItem(TItemType* pPrevItem){m_pPrevItem=pPrevItem;};

protected:
	///���������� ����
	TItemType* m_pPrevItem;
};

//--------------------------------------------------------------------//

///��������� ������ ������
template <class TListItem>
class CListContainer
{
public:
	CListContainer(void):m_pFirstItem(NULL), m_pLastItem(NULL){};
	virtual ~CListContainer(void){};

	///���������� ������ ���� � ������
	TListItem* GetFirstItem(void){return m_pFirstItem;};
	///���������� ��������� ���� � ������
	TListItem* GetLastItem(void){return m_pLastItem;};
	///��������� ������ �� �������
	bool IsEmptyList(void){return (m_pFirstItem==NULL && m_pLastItem==NULL)?true:false;};

	///������� ������
	void DeleteItems(void)
	{
		TListItem* pItem=m_pFirstItem;
		TListItem* pTempItem=NULL;
		while(pItem){
			pTempItem=pItem->GetNextItem();
			delete pItem;
			pItem=pTempItem;
		}

		//�������� ��������� �� ����� ������
		m_pFirstItem=NULL;
		m_pLastItem=NULL;
	}	

protected:
	///������ ����
	TListItem* m_pFirstItem;
	///��������� ����
	TListItem* m_pLastItem;

};

//--------------------------------------------------------------------//

}
}
}
}
}