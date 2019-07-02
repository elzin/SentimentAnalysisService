#pragma once

#include "..\ASCInterface\IDBMS.h"
#include "fn_Generic.h"
#include "cl_Topo_DBMS.h"
#include "cl_DiskFile.h"
#include "cl_SyncroObjects.h"

#undef  DBMS_SRC_FILE
#define DBMS_SRC_FILE "cl_DTablePhysTree.h"

using namespace SS::Interface::Core::DBMS;

#pragma pack(push,1) // ???

#define DEF_LoIn     0x0001
#define DEF_LoEq     0x0002
#define DEF_LoInEq  (DEF_LoIn | DEF_LoEq)
#define DEF_UpIn     0x0004
#define DEF_UpEq     0x0008
#define DEF_UpInEq  (DEF_UpIn | DEF_UpEq)

///
#define BTREE_DISK_READ_BLOCK  (2*512)

///
#define BTREE_CASH_SIZE        32

///
#define BTREE_NODE_ENTRIES_LIM (  ( (BTREE_DISK_READ_BLOCK - sizeof(UINT32)) / ( sizeof(SBTreeEntry)) ) & 0xFFFE) //


/*! \struct SBTreeEntry
	*  \brief ��������� - �������������-��������� ������� ���� �-������ (��� ���������������� ������)
*/
struct SBTreeEntry   {

	/// ������ �� ������ � HASH-�������
	UINT32 iLinkToHashRecord;

	/// ������ ���� ���������� ������
	INT32  iLinkToBTreeNode;

	/// ���������� ��������
//	UINT32 uiLinkToTableRecord;

};


/*! \struct SBTreeNodeDisk
	*  \brief ��������� ���� �-������ �� ����� (��� ���������������� ������)
*/
struct SBTreeNodeDisk   {

	/// ����� ����� �����
	UINT32      uiEntriesNum;

	/// ������ ����� �����
	SBTreeEntry aoEntriesArr[BTREE_NODE_ENTRIES_LIM];

};


/*! \struct SBTreeNodeMem
	*  \brief ��������� ���� �-������ � ������ (��� ���������������� ������)
*/
struct SBTreeNodeMem : public SBTreeNodeDisk   {

	/// ���� ���������
	BYTE            bChangeFlag;

	/// ������ ���� �� �����
	UINT32          iNodeIdx;

	/// ��������� ��������
	UINT32          iLastOper;

	/// ����� ���������
	UINT32          iHitCnt;

	/// ��������� ���������� ����� ���������
	VOID IncHit(VOID)        { iHitCnt++; }

	/// ���������� ���� ���������
	VOID SetChangeFlag(VOID) { bChangeFlag = TRUE; }

};

#pragma pack(pop)

/*! \struct SBTreeDataDisk
	*  \brief ��������� �-������ �� ����� (��� ���������������� ������)
*/
struct SBTreeDataDisk   {

	/// ����� ����� � ������
	UINT32 m_iNumOfNodes;

	/// ������ ������
	UINT32 m_iTreeHeight;

	/// ������ ��������� ����
	UINT32 m_iTreeRootIdx;

};

/*! \class CIndexTree
	*  \brief �-������ (��� ���������������� ������)
*/
class CIndexTree : public SBTreeDataDisk  {

	public:

		/// ������ ��� �����������
		SBTreeNodeMem         * m_pCashArr;

		/// ����� ��������� � ����
		UINT                    m_iCashNum;

		/// ����� ������� ��������
		UINT32                  m_iCurrOper;

		/// ����� ( �����_����, ������_��_������_���� )
		CContainer_HMap_Int_Int m_oCashMap;

		/// ���� �������
		DiskFileC             * m_pFile;

		/// Ctor
		CIndexTree();

		/// Dtor
		~CIndexTree();

		/// Init
		HRESULT Init(VOID);

		/// ����� ����� ��������
		VOID SetNewOper(VOID)   { if(++m_iCurrOper>100000) m_iCurrOper=0; }

		/// �������� ����� ���� ������ � ���
		SBTreeNodeMem * AddNewNode(VOID);

		/// �������� ���� ������ �� ����� ��� ����
		SBTreeNodeMem * GetNode(UINT32 iNodeIdx);

		/// ������ ������ � ��������� ������
		HRESULT FileOpenAndLoad(DiskFileC * pFile);

		/// ��������� ������ � ��������� ������
		HRESULT FileSaveAndClose(VOID);

		/// ��������� ���������
		HRESULT LoadHeader(VOID);

		/// ��������� ���� � ���
		HRESULT LoadNode(UINT32 iNodeIdx, SBTreeNodeMem * pNode);

		/// ��������� ���������
		HRESULT SaveHeader(VOID);

		/// ��������� ����
		HRESULT SaveNode(SBTreeNodeMem * pNode);

		/// ����� ��������� ������ ����
		SBTreeNodeMem * FindFreeCashCell(VOID);

};


