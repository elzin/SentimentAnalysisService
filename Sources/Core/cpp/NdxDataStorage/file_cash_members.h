#pragma once

#include ".\const.h"
#include ".\console.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxDataStorage
{
namespace FileCash
{

//--------------------------------------------------------------------//

///����� � �������
class CBuffer
{
public:
	CBuffer(unsigned int uiBufferIndex, unsigned int uiBufferSize)
		:m_uiBufferIndex(uiBufferIndex), 
		m_pBegin((unsigned char*)malloc(uiBufferSize)), 
		m_pFree(m_pBegin), m_pEnd(m_pBegin+uiBufferSize), m_pCurrent(NULL){};

	virtual ~CBuffer(void){if(m_pBegin) free(m_pBegin);};
	
	///���������� ������ ������
	unsigned int GetBufferId(void){return m_uiBufferIndex;};
	///���������� ������ ������������ � ������
	unsigned int GetFilledSize(void)
	{
		return (unsigned int)(m_pFree-m_pBegin);
	};
	///���������� ������ ������
	unsigned int	GetBufferSize(void){return (unsigned int)(m_pEnd-m_pBegin);};
	///���������� ��������� �� ������ ������
	unsigned char*	GetBuffer(void){return m_pBegin;};
	
	///�������� ������ ������
	void Resize(unsigned int uiNewSize);
	///������������� ������� � ������
	void SeekFromFront(unsigned int uiOffset);
	///������������� ������� � ������
	void SeekFromBack(unsigned int uiOffset);
	///����� ������ � �����, ���������� ������ �����������
	unsigned int Write(unsigned char* pucData, unsigned int uiSize);
	///��������� ������ � �����, ���������� ������ ������������
	unsigned int Append(unsigned char* pucData, unsigned int uiSize);
	///������ ������ �� �����, ���������� ������ ������������
	unsigned int Read(unsigned char* pucData, unsigned int uiSize);
	
	///����������� ������ � ������
	void ToString(wstring& wsValue);

protected:
	///������ ������
	const unsigned int m_uiBufferIndex;

	///��������� �� ������
	unsigned char* const m_pBegin;
	///��������� �� ��������� �����
	unsigned char*	m_pFree;
	///��������� �� ������� �����
	unsigned char*	m_pCurrent;
	///��������� �� ��������� �����
	unsigned char* const m_pEnd;
};

//--------------------------------------------------------------------//

///��������� �����
template <class T>
class CCircularBuffer
{
public:
	CCircularBuffer(unsigned int uiBufferSize)
		:m_uiBufferSize(uiBufferSize), m_pHead(NULL), m_pTail(NULL), m_uiCurrentSize(0)
	{
		m_pBuffer=new T*[uiBufferSize];
		memset((void*)m_pBuffer, 0, sizeof(T*)*uiBufferSize);
	};
	
	virtual ~CCircularBuffer(void)
	{
		delete[] m_pBuffer;
	};
	
	///���������� ������� ���������� ���������
	unsigned int GetSize(void){return m_uiCurrentSize;};
	///���������� ������� �� �������
	T* GetByIndex(unsigned int uiIndex)
	{
		if(uiIndex>=m_uiCurrentSize) return NULL;
		if(m_pHead+uiIndex>m_pBuffer+m_uiBufferSize-1)
			return *(m_pTail-(m_uiCurrentSize-uiIndex-1));
		else
			return *(m_pHead+uiIndex);
	};
	///���������� �������� �������
	T* GetHead(void){return m_pHead?*m_pHead:NULL;};
	///���������� ��������� �������
	T* GetTail(void){return m_pTail?*m_pTail:NULL;};

	///��������� ������� � �����, ���� "�������� ������ �������" ���������� ��������� �� ����
	T* PushBack(T* pT)
	{
		if(!m_uiBufferSize) return NULL;
		if(!m_pHead){
			//��� ������� ���� ������� ���������
			InitPtrs();
		}
		
		//��������� � ���������� ��������
		m_pTail=NextPtr(m_pTail);
		T* pPoped=NULL;
		if(m_pHead==m_pTail && GetSize()!=0){
			//���� ����� �� ������, ����������� ������
			pPoped=PopFront();
		}
		//������� �������
		(*m_pTail)=pT;
		//����������� ������
		++m_uiCurrentSize;
		//���������� �����������
		return pPoped;
	};

	///������� ������� � ������
	T* PopFront(void)
	{
		if(!m_pHead) return NULL;
		T* pPoped=(*m_pHead);
		(*m_pHead)=NULL;
		
		//��������� � ��������� ���� ��� ��� ���������� ����������
		if(m_pHead==m_pTail && GetSize()==1)
			m_pHead=m_pTail=NULL;
		else
			m_pHead=NextPtr(m_pHead);

		--m_uiCurrentSize;
		return pPoped;
	};
	
	///������� ������� � ������
	T* PopBack(void)
	{
		if(!m_pTail) return NULL;
		//������� ������
		T* pPoped=(*m_pTail);
		(*m_pTail)=NULL;
		
		//��������� � ����������� ���� ��� ��� ���������� ����������
		if(m_pHead==m_pTail)
			m_pHead=m_pTail=NULL;
		else
			m_pTail=PrevPtr(m_pTail);

		--m_uiCurrentSize;
		return pPoped;
	};
	
protected:
	///�������������� ���������
	void InitPtrs(void)
	{
		m_pHead=m_pBuffer;
		m_pTail=m_pBuffer+m_uiBufferSize-1;
	};

	///����������� � ���������� ���������
	T** NextPtr(T** pT)
	{
		if(pT==m_pBuffer+m_uiBufferSize-1){
			return m_pBuffer;
		}else{
			return ++pT;
		}
	};

	///����������� � ���������� ���������
	T** PrevPtr(T** pT)
	{
		if(pT<=m_pBuffer){
			return m_pBuffer+m_uiBufferSize-1;
		}else{
			return --pT;
		}
	};

	///��������� �� �����
	T** m_pBuffer;
	///��������� �� ������
	T** m_pHead;
	///��������� �� �����
	T** m_pTail;
	///������� ���������� ���������
	unsigned int m_uiCurrentSize;

	///������ ����������� ������
	const unsigned int m_uiBufferSize;
};

//--------------------------------------------------------------------//

///������� � ����
class CCashPosition
{
public:
	///������� �����
	unsigned int m_uiBufferIndex;
	///������� �������� � ������� ������
	unsigned int m_uiBufferOffset;

	CCashPosition(void)
		:m_uiBufferIndex(SS::Core::NdxSE::NdxDataStorage::EMPTY_VALUE), 
		m_uiBufferOffset(SS::Core::NdxSE::NdxDataStorage::EMPTY_VALUE){};
	
	///���������� ������� � ������
	void Clear(void)
	{
		m_uiBufferIndex=SS::Core::NdxSE::NdxDataStorage::EMPTY_VALUE;
		m_uiBufferOffset=SS::Core::NdxSE::NdxDataStorage::EMPTY_VALUE;
	}

	///�������� �� ������ ������� 
	bool IsEmpty(void)
	{
		return (m_uiBufferIndex==SS::Core::NdxSE::NdxDataStorage::EMPTY_VALUE ||
			m_uiBufferOffset==SS::Core::NdxSE::NdxDataStorage::EMPTY_VALUE)?true:false;
	}

	///������� ������� �� �������
	void View(void)
	{
		ToConsole(L"CCashPosition:");
		ToConsole(L"m_uiBufferIndex", m_uiBufferIndex);
		ToConsole(L"m_uiBufferOffset", m_uiBufferOffset);
	}

};

//--------------------------------------------------------------------//

}
}
}
}
}