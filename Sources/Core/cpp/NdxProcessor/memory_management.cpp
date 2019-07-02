#include "StdAfx.h"
#include ".\memory_management.h"

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

CNdxHeap::CNdxHeap(void)
:m_hHeap(NULL)
{
	m_hHeap=HeapCreate(HEAP_NO_SERIALIZE, 0, 0);
	ISNULL(m_hHeap);	
}

CNdxHeap::~CNdxHeap(void)
{
	HeapDestroy(m_hHeap);
}

void*	CNdxHeap::Alloc(size_t uiSize)
{
	if(ISNULL(m_hHeap)) return NULL;

	return HeapAlloc(m_hHeap, 0, uiSize);
}

void	CNdxHeap::Free(void* pBuffer)
{
	if(ISNULL(pBuffer)) return;
	HeapFree(m_hHeap, 0, pBuffer);
}

//--------------------------------------------------------------------//

CPool::CPool(CNdxHeap* pHeap, size_t uiBlockSize, unsigned int uiInitBlocksCount, const wchar_t* pwszObjectTypeName)
:m_cuiBlockSize(sizeof(SPoolBlock)+uiBlockSize), m_cpHeap(pHeap), m_uiInitBlocksNumber(uiInitBlocksCount),
m_uiCurrExtentSize(0), m_pCurrExtent(NULL), m_pFreeBlockList(NULL), m_pCurrBlock(NULL),
m_uiCurrBlocksNumber(0), m_uiFreeBlocksNumber(0), m_uiCurrExtentsNumber(0), m_wsObjectTypeName(pwszObjectTypeName)
{
	if(m_uiInitBlocksNumber)
		AddExtent(m_uiInitBlocksNumber);
}

CPool::~CPool(void)
{
	ClearExtents();
}

void* CPool::Alloc(void)
{
	SPoolBlock* pBlock=AllocBlock();
   /* ������ ���� ���������� � ���������. ������� ����� ���, ��� ������ ����
     * �����������, ���������� �������� ��������� �� �������, ������
     * ��������������� �� ���������� �����. ��� ��� ������ ��������� �����
     * ������� ��������� SPoolBlock, ����� ������ ��������� ��������� �� 
     * ���� (p) �� �������.
     */
  	pBlock++;
	return pBlock;
}

void CPool::Free(void* p)
{
	FreeBlock((SPoolBlock*)((unsigned char*)p-sizeof(SPoolBlock)));
}

SPoolBlock* CPool::AllocBlock(void)
{
	++m_uiCurrBlocksNumber;

	if(m_pFreeBlockList){
		--m_uiFreeBlocksNumber;

		SPoolBlock* pBlock=m_pFreeBlockList;
		m_pFreeBlockList=m_pFreeBlockList->m_pNextBlock;
		return pBlock;
	}else
		return GetBlock();
}

SPoolBlock* CPool::GetBlock(void)
{
   //���������, �� �������� �� ������� �������...
	if(m_pCurrBlock==m_pCurrExtent->m_arrBlocks){
      //���� ��������, ��������� ����� �������
      AddExtent((unsigned int)m_uiCurrExtentSize);
	}

    SPoolBlock* pRet=m_pCurrBlock;
		
	//���������� ����� ������������ ���, ��� ����� ���� ����� �����������
	pRet->m_pBlockPool=this;
    
	// ��������� ��������� �� ������� ����, ������� ��� ��� ����� ����� �
    // m_arrBlocks. ��� ��� ������ ����� ������������ � ������, ���������� 
    // �������� m_pCurrent � ��������� �� ���� (unsigned char*). ����� ��������
    // lvalue ����������� ���� ������ �&�.
	(unsigned char*&)m_pCurrBlock-=m_cuiBlockSize;
    
	return pRet;
}

void CPool::FreeBlock(SPoolBlock* pBlock)
{
	--m_uiCurrBlocksNumber;
	++m_uiFreeBlocksNumber;
	pBlock->m_pNextBlock=m_pFreeBlockList;
	m_pFreeBlockList=pBlock;
}

void CPool::AddExtent(unsigned int uiBlocksCount)
{
	// �������� ������ ��� ������� (��������� � �������� � ������� �����).
	SPoolExtent* pExtent=AllocExtent(uiBlocksCount);

    // �������� ��������� �� ���������� ������� � ���������� m_pNextExtent
    // ������ ��������.
	pExtent->m_pNextExtent=m_pCurrExtent;
   
    // ���������� � m_pCurrent ��������� �� ����� ��������� ����.
    // ���� ��������� �������������� ��� ����� ������� ����� ���� ����������
    // ������, ���������� �� �� ������. ���������� � unsigned char* ��������� ��-�� 
    // ����, ��� �������� �������������� � ������. ���� ����� �� �������, �� 
    // �������� C++ �������� ����� ������������� �� ������ ��������� SPoolBlock.
	// - 1 - �.�. �� ������ ���������� �� ������ ���������� ��������.
	// ��� ��� -1 ��������� �� �������� �� �� ����� ��������� ��������.
	m_pCurrBlock=(SPoolBlock*)((unsigned char*)(pExtent->m_arrBlocks) 
      + (uiBlocksCount-1) * m_cuiBlockSize);

    // ������ ����� ������� �������. ��� ����� ���������� �������� 
    // ����� ������ �� ����.
    m_pCurrExtent=pExtent;

    // ���������� ������ �������� �������� 
    m_uiCurrExtentSize=uiBlocksCount;
}

SPoolExtent* CPool::AllocExtent(unsigned int uiBlocksCount)
{
	if(ISNULL(m_cpHeap)) return NULL;

	++m_uiCurrExtentsNumber;

	return (SPoolExtent*)m_cpHeap->Alloc(sizeof(SPoolExtent)+
		uiBlocksCount * m_cuiBlockSize);
}

void CPool::FreeExtent(SPoolExtent* pExtent)
{
	//ToConsole(L"CPool::FreeExtent");
	
	if(ISNULL(m_cpHeap)) return;

	--m_uiCurrExtentsNumber;

	m_cpHeap->Free(pExtent);
	
	//ToConsole(L"End CPool::FreeExtent");
}

void CPool::ClearExtents(void)
{
	//ToConsole(L"CPool::ClearExtents");

	SPoolExtent* pExtent=m_pCurrExtent;
	SPoolExtent* pTemp;
	while(pExtent){
		pTemp=pExtent->m_pNextExtent;
		FreeExtent(pExtent);
		pExtent=pTemp;
	}

	m_pCurrExtent=NULL;
	m_uiCurrExtentSize=0;

	if(m_uiCurrExtentsNumber) 
		TO_CONSOLE(L"Not all Extents cleared");

	//ToConsole(L"End CPool::ClearExtents");
}

void CPool::Reset(void)
{
	//������� ��������
	ClearExtents();

	m_pFreeBlockList=NULL;
	m_pCurrBlock=NULL;
	m_uiCurrBlocksNumber=0;
	m_uiFreeBlocksNumber=0;

	//������� �����
	if(m_uiInitBlocksNumber)
		AddExtent(m_uiInitBlocksNumber);
}

void CPool::ToString(wstring& szValue, unsigned int* puiSize)
{
	wchar_t buf[300];
	wsprintf(buf, L"Pool: \n\tObjects name: %s, \tObjects size: %u, \tAlloc objects count: %u, \tFree objects count: %u, \tAll objects count: %u, \n\tExtents count: %u, \tAprox alloc: %u bytes\n", 
		m_wsObjectTypeName.c_str(),
		m_cuiBlockSize,
		m_uiCurrBlocksNumber, 
		m_uiFreeBlocksNumber,
		m_uiCurrBlocksNumber+m_uiFreeBlocksNumber,
		m_uiCurrExtentsNumber, 
		(m_uiCurrBlocksNumber+m_uiFreeBlocksNumber)*m_cuiBlockSize);
	szValue.append(buf);

	(*puiSize)+=(m_uiCurrBlocksNumber+m_uiFreeBlocksNumber)*m_cuiBlockSize;
}

//--------------------------------------------------------------------//

}
}
}
}
}
