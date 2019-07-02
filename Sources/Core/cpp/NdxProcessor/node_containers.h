#pragma once
#include ".\stl.h"
#include ".\console.h"

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

///���� ������ ��� ��������� �������� �����
template <class T>
class CUnChildNode
{
public:
	CUnChildNode(void)
		:m_pMyself(NULL), m_pParent(NULL), m_uiDepth(0), m_bLeaf(true){};

	CUnChildNode(T pMySelf)
		:m_pMyself(pMySelf), m_pParent(NULL), m_uiDepth(0), m_bLeaf(true){};

	virtual ~CUnChildNode(void)
	{
		if(m_pMyself){
			delete m_pMyself;
			m_pMyself=NULL;
		}
	};

	///������������� ������� ����
	void SetDepth(unsigned int uiValue){m_uiDepth=uiValue;};
	///���������� ������� ����
	unsigned int GetDepth(void){return m_uiDepth;};
	///������������� ������������ ����
	virtual void SetParent(CUnChildNode* pValue){m_pParent=pValue;};
	///���������� ������������ ����
	virtual CUnChildNode<T>* GetParent(void){return m_pParent;};
	///���������� ���� �������
	T GetMyself(void){return m_pMyself;};
	///������������� ���� �������
	void SetMyself(T pValue){m_pMyself=pValue;};

	///��������� ���� �� ��������
	bool IsLeaf(void){return m_bLeaf;};
	///��������� ���� �� ��������
	bool IsRoot(void){return !m_uiDepth?true:false;};

protected:
	///���
	T m_pMyself;
	///������������ ����
	CUnChildNode<T>* m_pParent;
	///������� ������� ����
	unsigned int m_uiDepth;
	///���� ��������� ����
	bool m_bLeaf;
};

//--------------------------------------------------------------------//

///���������������� ���� ������ � ���������� ����� ��������������� ��� ������ �� �������
template <class T>
class CTreeNode : public CUnChildNode<T>
{
public:
	typedef map<unsigned int, CTreeNode<T>* > TChilds;
	
	CTreeNode(void)
	{
		m_itCurrChild = m_NullCollection.end();
	}
	CTreeNode(T pMySelf)
		:CUnChildNode<T>(pMySelf)
	{
		m_itCurrChild = m_NullCollection.end();
	}
	
	virtual ~CTreeNode(void)
	{
		DeleteChilds();
	};

	///���������� ��������� ����� ����
	TChilds* GetChilds(void){return &m_Childs;};
	///���������� ���������� ����� ����
	unsigned int GetChildsNumber(void){return m_Childs.size();};

	///���������� ������� ���� �� �������
	virtual CTreeNode<T>* GetChild(unsigned int uiChildID)
	{
		TChilds::iterator itChild=m_Childs.find(uiChildID);
		if(itChild!=m_Childs.end()){
			return itChild->second;
		}else{
			return NULL;
		}
	};

	///��������� ������� ������� ����
	virtual CTreeNode<T>* AddChild(unsigned int uiChildID, CTreeNode<T>* pChildNode)
	{
		if(ISNULL(pChildNode)) return NULL;

		TChilds::iterator itChild=m_Childs.find(uiChildID);
		if(itChild==m_Childs.end()){
			pChildNode->SetParent(this);
			pChildNode->SetDepth(GetDepth()+1);
			m_Childs.insert(TChilds::value_type(uiChildID, pChildNode));
			m_bLeaf=false;
			return pChildNode;
		}else{
			return itChild->second;
		}
	};

	///������� ����� � ����
	void DeleteChilds(void)
	{
		TChilds::iterator itChild=m_Childs.begin();
		while(itChild!=m_Childs.end()){
			if(itChild->second){
				delete itChild->second;
			}
			itChild++;
		}
		m_Childs.clear();
		m_bLeaf=true;
	};

	///������� ������� � ����
	void DeleteChild(unsigned int uiChildID)
	{
		TChilds::iterator itChild=m_Childs.find(uiChildID);
		if(itChild!=m_Childs.end()){
			if(itChild->second) delete itChild->second;

			m_Childs.erase(itChild);

			if(m_Childs.empty()) m_bLeaf=true;
		}
	};
	
	///������ ������� ������� �������
	bool MoveFirstChild(void)
	{
		if(m_Childs.empty()){
			m_itCurrChild=m_NullCollection.end();
			return false;
		}else{
			m_itCurrChild=m_Childs.begin();
			return true;
		}
	};

	///������ ������� ���������� �������
	bool MoveNextChild(void)
	{
		if(m_itCurrChild == m_NullCollection.end()) return false;

		if(++m_itCurrChild!=m_Childs.end()){
			return true;
		}else{
			m_itCurrChild=m_NullCollection.end();
			return false;
		}

	};

	///���������� �������� �������
	CTreeNode<T>* GetCurrentChild(void)
	{
		if(m_itCurrChild==m_NullCollection.end()) return NULL;
		return m_itCurrChild->second;
	};	

	///������� �������� �������
	void DeleteCurrentChild(void)
	{
		if(m_itCurrChild == m_NullCollection.end()) return;
		
		m_itCurrChild=m_Childs.erase(m_itCurrChild);
		
		if(m_itCurrChild==m_Childs.end()) m_itCurrChild==m_NullCollection.end();

		if(m_Childs.empty()) m_bLeaf=true;
	};	

protected:
	///��������� �����
	TChilds m_Childs;
	///������� ������� 
	typename CTreeNode<T>::TChilds::iterator m_itCurrChild;
	///��������� ��� ������������� ����������
	TChilds m_NullCollection;
};

//--------------------------------------------------------------------//

///���� ��������� ������
template <class T>
class CBinTreeNode : public CUnChildNode<T>
{
public:
	CBinTreeNode(void)
		:m_pLeftChild(NULL), m_pRightChild(NULL)
	{};
	CBinTreeNode(T pMySelf)
		:CUnChildNode<T>(pMySelf), m_pLeftChild(NULL), m_pRightChild(NULL)
	{};

	virtual ~CBinTreeNode(void)
	{
		DeleteChilds();
	};

	///��������� ������� ������� ����
	CBinTreeNode<T>* AddChild(CBinTreeNode<T>* pChildNode, bool bLeft)
	{
		if(ISNULL(pChildNode)) return NULL;
		if(bLeft){
			return AddChild(&m_pLeftChild, pChildNode);
		}else{
			return AddChild(&m_pRightChild, pChildNode);
		}
	};

	///��������� ������� ������� ����
	CBinTreeNode<T>* AddChild(CBinTreeNode<T>* pChildNode)
	{
		if(ISNULL(pChildNode)) return NULL;
		if(!m_pLeftChild){
			//���� ����� ��������� ����� ��������
			return AddChild(&m_pLeftChild, pChildNode);
		}
		if(!m_pRightChild){
			//���� ����� ��������� ������ ��������
			return AddChild(&m_pRightChild, pChildNode);
		}

		return NULL;
	};

	///��������� ��� ���� ���� ��� ������
	bool ChildsOccupied(void){return (m_pLeftChild && m_pRightChild)?true:false;};
	///������� � ���� ����� ��� ��������
	void RemoveChilds(void){m_pLeftChild=NULL; m_pRightChild=NULL;};
	///������� � ���� ����� ��� ��������
	void DeleteChilds(void)
	{
		if(m_pLeftChild){
			delete m_pLeftChild;
			m_pLeftChild=NULL; 
		}
		
		if(m_pRightChild){
			delete m_pRightChild;
			m_pRightChild=NULL;
		}
	};
	///������� � ���� ������ ������� ��� ��������
	void RemoveLeftChild(void){m_pLeftChild=NULL;};
	///������� � ���� ������� ������� ��� ��������
	void RemoveRightChild(void){m_pRightChild=NULL;};
	///���������� ������ �������
	virtual CBinTreeNode<T>* GetLeftChild(void){return m_pLeftChild;};
	///���������� ������� �������
	virtual CBinTreeNode<T>* GetRightChild(void){return m_pRightChild;};
	///���������� ������������ ����
	CBinTreeNode<T>* GetParent(void){return (CBinTreeNode<T>*)CUnChildNode<T>::GetParent();};

private:
	///��������� ������� ������� ����
	CBinTreeNode<T>* AddChild(CBinTreeNode<T>** m_ppChildContainer, CBinTreeNode<T>* pChildNode)
	{
		if(!(*m_ppChildContainer)){
			m_bLeaf=false;
			(*m_ppChildContainer)=pChildNode;
			(*m_ppChildContainer)->SetDepth(m_uiDepth+1);
			(*m_ppChildContainer)->SetParent(this);
		}else{
			TO_CONSOLE(L"Child already exist!");
		}

		return (*m_ppChildContainer);
	};

protected:
	///����� �������
	CBinTreeNode<T>* m_pLeftChild;
	///������ �������
	CBinTreeNode<T>* m_pRightChild;
};

//--------------------------------------------------------------------//

///���������������� ���� �������� ������ � ��������� ���������� �����
template <class T>
class CVecTreeNode : public CUnChildNode<T>
{
public:
	typedef vector< CVecTreeNode<T>* > TChilds;
	
	CVecTreeNode(void)
	{
		m_itCurrChild = m_NullCollection.end();
	}
	CVecTreeNode(T pMySelf)
		:CUnChildNode<T>(pMySelf)
	{
		m_itCurrChild = m_NullCollection.end();
	}
	
	virtual ~CVecTreeNode(void)
	{
		DeleteChilds();
	};

	///���������� ������� ����
	TChilds* GetChilds(void){return &m_Childs;};

	///��������� ������� ������� ����
	virtual CVecTreeNode<T>* AddChild(CVecTreeNode<T>* pChildNode)
	{
		if(ISNULL(pChildNode)) return NULL;

		pChildNode->SetParent(this);
		pChildNode->SetDepth(GetDepth()+1);
		m_Childs.push_back(pChildNode);
		m_bLeaf=false;
		return pChildNode;
	};

	///������� ����� � ����
	void DeleteChilds(void)
	{
		TChilds::iterator itChild=m_Childs.begin();
		while(itChild!=m_Childs.end()){
			if(*itChild){
				delete *itChild;
			}
			itChild++;
		}
		m_bLeaf=true;
	};

	///������ ������� ������� �������
	bool MoveFirstChild(void)
	{
		if(m_Childs.empty()){
			m_itCurrChild=m_NullCollection.end();
			return false;
		}else{
			m_itCurrChild=m_Childs.begin();
			return true;
		}
	};

	///������ ������� ���������� �������
	bool MoveNextChild(void)
	{
		if(m_itCurrChild == m_NullCollection.end()) return false;

		if(++m_itCurrChild!=m_Childs.end()){
			return true;
		}else{
			m_itCurrChild=m_NullCollection.end();
			return false;
		}

	};

	///���������� �������� �������
	CVecTreeNode<T>* GetCurrentChild(void)
	{
		if(m_itCurrChild == m_NullCollection.end()) return NULL;
		return *m_itCurrChild;
	};	

protected:
	///��������� �����
	TChilds m_Childs;
	///������� ������� 
	typename CVecTreeNode<T>::TChilds::iterator m_itCurrChild;
	///��������� ��� ������������� ����������
	TChilds m_NullCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}