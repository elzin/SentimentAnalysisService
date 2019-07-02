#pragma once

#include ".\const.h"
#include ".\console.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace MemoryManagement
{

//--------------------------------------------------------------------//

///������� ��������� ����
class CNdxHeap
{
public:
	CNdxHeap(void);
	virtual ~CNdxHeap(void);
	
	///���������� ����
	void*	Alloc(size_t uiSize);
	///����������� ����
	void	Free(void* pBuffer);

protected:
	///��������� ����
	HANDLE m_hHeap;	
};

//--------------------------------------------------------------------//
class CPool;
///���� ������, ������ ��������� � ����
struct SPoolBlock
{
	///��������� �� ��������� ����
	SPoolBlock* m_pNextBlock;
	///��������� �� ��� �����
	CPool* m_pBlockPool;
};

//--------------------------------------------------------------------//

///������� - ����������� ������ ������ ������, ���������� � ����
struct SPoolExtent
{
	///��������� �� ��������� �������
	SPoolExtent* m_pNextExtent;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4200)
#endif
	///����������� ������ ������ ��������
	SPoolBlock	m_arrBlocks[0];
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

//--------------------------------------------------------------------//

///��� - �������� ������ ���������, ��� �������� ������������� �������
class CPool
{
public:
	CPool(CNdxHeap* pHeap, size_t uiBlockSize, unsigned int uiInitBlocksCount, const wchar_t* pwszObjectTypeName);
	virtual ~CPool(void);
	
	///�������� ������ ��� ������
	void* Alloc(void);
	///����������� ������ �������
	void Free(void* p);
	///���������� ������ �������� ����	
	size_t GetPoolBlockSize(void){return m_cuiBlockSize;};
	///���������� ��� ������� ���������� �� ������
	void Reset(void);

	///����������� � ������
	void ToString(wstring& szValue, unsigned int* puiSize);

protected:
	///��������� ����� �������
	void AddExtent(unsigned int uiBlocksCount);
	///������� �������
	SPoolExtent* AllocExtent(unsigned int uiBlocksCount);
	///������� �������
	void FreeExtent(SPoolExtent* pExtent);
	///������� ������ ���������
	void ClearExtents(void);
	
	///������� ���� ������ � ��������
	SPoolBlock* AllocBlock(void);
	///����������� ���� ������ � ��������
	void FreeBlock(SPoolBlock* pBlock);
	///�������� ���� ������ �� ��������
	SPoolBlock* GetBlock(void);
	
	///������� ���� ����
	CNdxHeap* const m_cpHeap;
	///���������� ������ ������� ���������
	size_t m_uiCurrExtentSize;
	///������ ����� ������ ��� ������� ����
	const size_t m_cuiBlockSize;
	///������� ������� ����
	SPoolExtent* m_pCurrExtent;
	///������� ���� �������� ��������
	SPoolBlock*	m_pCurrBlock;
	///������ ������������� ������
	SPoolBlock*	m_pFreeBlockList;

	///���������� ����� ��������
	unsigned int m_uiCurrBlocksNumber;
	///���������� ������������� ��������
	unsigned int m_uiFreeBlocksNumber;
	///���������� ������������� ���������
	unsigned int m_uiCurrExtentsNumber;
	///���������� ������ �������� �� ���������
	unsigned int m_uiInitBlocksNumber;
	
	///�������� ���� �������
	wstring m_wsObjectTypeName;
};

//--------------------------------------------------------------------//

///����� � �������
class CBuffer
{
public:
	CBuffer(unsigned int uiBufferSize)
	:m_pBegin((unsigned char*)malloc(uiBufferSize)), m_pFree(m_pBegin), m_pEnd(m_pBegin+uiBufferSize){};
	virtual ~CBuffer(void){if(m_pBegin) free(m_pBegin);};
	
	///���������� ������ ������������ � ������
	unsigned int GetFilledSize(void)
	{
		return (unsigned int)(m_pFree-m_pBegin);
	};
	///���������� ��������� �� ������
	unsigned char*	GetHeadPtr(void){return m_pBegin;};
	///���������� ��������� �� ��������� ����� � ������
	unsigned char*	GetFreePtr(void){return m_pFree;};
	///������������� ��������� �� ��������� ����� � ������
	void SetFreePtr(unsigned char* pFree)
	{
		if(pFree<m_pBegin && pFree>m_pEnd){
			TO_CONSOLE(L"Invalid Free Pointer");
		}else{
			m_pFree=pFree;
		}
	};
	///���������� ������ ������
	unsigned int	GetBufferSize(void){return (unsigned int)(m_pEnd-m_pBegin);};
	///�������� � ����� ������
	bool PutData(unsigned char* pData, unsigned int uiDataSize)
	{
		if(!pData || !uiDataSize) return false;
		
		//��������� ���� �� ����� ��� ������
		if(m_pEnd-m_pFree<(int)uiDataSize) return false;
		
		//�������� ������ �������� ���������
		memcpy(m_pFree, pData, uiDataSize);
		m_pFree+=uiDataSize;
		return true;
	}
	///���������� ����� ����� ������ ���� �������� � ������
	void Reset(void){m_pFree=m_pBegin;}

protected:
	///��������� �� ������
	unsigned char* const m_pBegin;
	///��������� �� ��������� �����
	unsigned char*	m_pFree;
	///��������� �� ��������� �����
	unsigned char* const m_pEnd;
};

//--------------------------------------------------------------------//

}
}
}
}
}