#pragma once

#include "..\ASCInterface\IDBMS.h"
#include "fn_Generic.h"
#include "cl_Topo_DBMS.h"
#include "cl_DiskFile.h"
#include "cl_SyncroObjects.h"
#include "cl_DTablePhysTree.h"

#undef  DBMS_SRC_FILE
#define DBMS_SRC_FILE "cl_DTablePhys.h"

using namespace SS::Interface::Core::DBMS;

///	�������� ��������� �� ������ ������������
#define DUMMY_USER_ARRAY_OF_POINTERS_TO_DATA   (VOID **)(NULL+1)

///	������ DBMS
#define DBMS_VERSION   350

///	��� ����� ���-�������
#define F_NAME_HASH     _T("DT_HashArr.dta")

///	��� ����� �������
#define F_NAME_RECORDS  _T("DT_RecordsArr.dta")

///	��� ����� ��������� � ��������� �������
#define F_NAME_VALUES   _T("DT_ValuesArr.dta")

///	��� ����� ����������
#define F_NAME_STAT     _T("DT_Statistics.txt")

///	������ ��������� ������� ��� ������� ���������� ��������� Shrink()
#define SHRINK_PERCENT                         25

///	������ ����������� ������ ��� ������ ������� ������� ������ ��� ������
#define STR_BUFF_INI_SIZE                      32

///	������������ ������ ������ ��� �������
#define STR_BUFF_MAX_SIZE                     (64*1024) - 1

///	������ ���������� ���������� � �������
#define SIZE_OF_TABLE_INFO                     512   // Size of RECORD_PTR record

///	������ ��������� �� ������
#define SIZE_OF_RECORD_OFFSET                  4   // Size of RECORD_PTR record

///	������ ������ ��� ��������� �� ������
#define SIZE_OF_VALUE_OFFSET                   4   // Size of NAME_PTR field of RECORD_UNIT

///	������ ��������� �� ��������� �������
#define SIZE_OF_NEXT_OFFSET                    4   // Size of NEXT_PTR field of RECORD_UNIT

///	������ ����������� ������ �������
#define SIZE_OF_RECORD_UNIT                    (SIZE_OF_VALUE_OFFSET + SIZE_OF_NEXT_OFFSET) // Size of full RECORD_UNIT

///	����� ��� ������� ����� ������ � ���-������� (������� ���� ���-�����)
#define HASH_IDX_HIGH_BITS_MASK                0xFF000000

///	������� ��� ������ ������ ������������� � ���������� ������
#define HASH_BLOCKS_GROW_UP_START              2

///	������ ������ � ���-�������
#define ZERO_HASH_RECORD                       0xFFFFFFFF

///	������ �������� ��������� (NEXT) ������ � �������
#define ZERO_NEXT_RECORD_IDX                   0xFFFFFFFF

///	����. ����� ��������������� ������
#define FIND_LIM                               64

///	����. ����� ��������������� ���������
#define SCAN_LIM                               64

///	����. ����� ��������������� ������ � ���������
#define SPAN_FIND_LIM                          16

///	����. ����� ����������� ���������������� ��������
#define USER_VALUES_LIM                        16

/////	�������� <FinfId> ��� ������� Scan()
//#define GET_RECORD_DATA_FIND_ID_FOR_SCAN       FIND_LIM


/*! \struct SHashBlockInfo
	*  \brief �������� ��������� ������ DTablePhysC
*/
struct SHashBlockInfo   {
	/// ����� �������� ��������� � �����
	UINT32 uiHashBlockSize;

	/// ����� ������� ��� ��������� � �����
	UINT32 uiHashBlockVolume;

	/// ������ ����� � ������
	UINT32 uiHashBlockVolumeInBytes;

	/// ����� �������� ��������� ������� ����������� ���������� � ������� ������
	UINT32 uiHashBlockGlobalLimit;

	/// �������� ������ �����
	UINT32 uiOffsetOfStartOfHashBlock;

	/// �������� ����� �����
	UINT32 uiOffsetOfEndOfHashBlock;
};

/*! \struct SRecordField
	*  \brief ���������� � ������ ������� (�������� ��������� ������ DTablePhysC)
*/
struct SRecordField   {
	/// �������� � ����� ����� ��� �������� ��������
	UINT32 StrValueOffsetOrNumValue;

	/// �������� ��������� (NEXT) ������ � �������
	UINT32 NextRecordOffset;
};

/*! \struct SFieldInfo
	*  \brief ���������� � ���� ������� (�������� ��������� ������ DTablePhysC)
*/
struct SFieldInfo   {

	/// ��� ������
	EFieldDataTypes  eType;

	/// ������ ����
	UINT32          iIndex;

	/// ������ ����
	UINT32          iSize;

	/// ��������������� ����� ����������� ������ (std:string & std:vector)
	UINT16          wValueMiddleSize;

	/// ���� ����� ������ �� ��������� �������
	BOOL            bHasNextFlag;

	/// �� ���� ��� ������
	BOOL            bNoFindFlag;

	/// ���� - ����������
	BOOL            bIsUnicFlag;

	/// ���� - ������
	BOOL            bIsDataFlag;

	/// ���� - ����������������
	BOOL            bIndexedFlag;

	/// �������� ������ ���� � ������
	UINT32          iRecordFieldBegOffset;

	/// ��������� �� ������ � ������
	SRecordField  * pRecordFieldPtr;

	/// ��������� ����
	DiskFileC       oIndexFile;

	/// ��������� ������ � ������
	CIndexTree      oIndexTree;

	/// ��������� �� ��� ����
	CONST _TCHAR  * pszFieldName;

	/// ��������� �� ��� ���� ����
	CONST _TCHAR  * pszTypeName;


};

#pragma pack(push,8) // ???

/*! \struct SDTableInfo
	*  \brief �������� ���������� � ������� ������
*/
struct SDTableInfo   {
	/// ������ DBMS
	UINT32 m_DbmsVersion;

	/// ����������� ����� �������
	UINT32 m_TableCheckSum;

	/// ����� ����� ������
	UINT32 m_DataGlobalLen;

	/// ����� Hash-������
	UINT32 m_HashBlocksNum;

	/// ����� "������������" ���������
	UINT32 m_HashElemsNum;

	/// ����� �������
	UINT32 m_RecordsNum;

	/// ����� ������� ���������� �� ��������
	UINT32 m_DeletedRecordsNum;

	/// ����������: ����� ������� � ��������� ���-�����
	UINT32 m_ReTryNum;

	/// ����������: ����� ��������� ���������� ���-�����
	UINT32 m_ReReadNum;

	/// ����������: ����� ��������� ���������� ������� ������ ��� ���������
	UINT32 m_ReValueNum;

	/// ����������� ������ ������������
	UINT32 m_UserValues[USER_VALUES_LIM];

};

#pragma pack(pop)


/*! \class DTablePhysC
	*  \brief ���������� ����� DataTable
*/
class DTablePhysC   : public SDTableInfo  {

	/// ������������� �����
	friend class DTableTopoC;

	/// ������������� �����
	friend class DFieldTopoC;

	public: //

		/// �����������
		DTablePhysC();

		/// ����������
		~DTablePhysC();

	public: //

		/// ��������� �������������
		HRESULT SetDTFilesPathsAndNames(VOID);

		/// ������� ��� ������� DataTable. Return: HRESULT
		HRESULT Open(VOID);

		/// ������� DataTable. Return: HRESULT
		HRESULT Close(BOOL bClearAfterClose = FALSE);

		/// ��������� BACKUP-����� �������
		HRESULT SaveBackup(BOOL bSaveAnyTable = FALSE);

		/// �������� �������
		HRESULT Clear(BOOL bClearUserInitializations = TRUE);

		/// ������� ������� ��� �������, ��� ������� ����� �������� ����� ����\n
		HRESULT TryClear(VOID);

		/// ������������� ��������� ����������
		HRESULT AddInit(VOID * ppArrayOfPointersToData[]);

		/// ��������� ������ ��� ���������� ������ ������� � ������ ���������� �� ��� ����������
		VOID **  AllocRecordDataStorage(VOID);

		/// ������������ ������ ���������� ������ ������� � ������ ���������� �� ��� ����������
		HRESULT  FreeRecordDataStorage(VOID ** ppvppArrayOfPointersToData);

		/// ������������� ���������
		HRESULT ChangeInit(VOID * ppArrayOfPointersToData[]);

		/// ���������� ������ � �������
		HRESULT Add(VOID);

		/// ������������� ��������� ������
		HRESULT FindInit(_TCHAR * pKeyName,  VOID * pKeyValue, VOID * ppArrayOfPointersToData[], WORD nFindId = 0);

		/// ������������� ��������� ������
		HRESULT FindInit(UINT32   nKeyIndex, VOID * pKeyValue, VOID * ppArrayOfPointersToData[], WORD nFindId = 0);

		/// ������������� ��������� ������ � ��������� �������������� ������
		HRESULT FindInitEx(_TCHAR * pKeyName,  VOID * pKeyValue, VOID * ppArrayOfPointersToData[], WORD * pnFindId);

		/// ������������� ��������� ������ � ��������� �������������� ������
		HRESULT FindInitEx(UINT32   nKeyIndex, VOID * pKeyValue, VOID * ppArrayOfPointersToData[], WORD * pnFindId);

		/// ������������ �������������� ������
		HRESULT FindCancel(WORD nFindId = 0);

		/// ����� ������ � �������
		HRESULT Find(WORD nFindId = 0);

		/// ����� � ������ ������
		HRESULT FindAndChange(WORD nFindId = 0);

		/// ����� ����� ����� ������
		HRESULT FindStart(WORD nFindId = 0);

		/// ������� �������� ������
		HRESULT FindStop(WORD nFindId = 0);

		/// ����� ����� ������
		HRESULT FindOne(WORD nFindId = 0);

		/// ����� ����� ������ � ��������� ��
		HRESULT FindOneAndChange(WORD nFindId = 0);

//		HRESULT FindOneAndInc(WORD nFindId = 0);

		/// ������������� ��������� ������������
		HRESULT ScanInit(UINT32 nStartRecordIdx, VOID * ppArrayOfPointersToData[], WORD nScanId = 0);

		/// ������������� ��������� ������������
		HRESULT ScanInitEx(UINT32 nStartRecordIdx, VOID * ppArrayOfPointersToData[], WORD * pnScanId);

		/// ����� �� ��������� �� ��������� nScanId
		HRESULT ScanCancel(WORD nScanId = 0);

		/// ��������� ��������� ������� ��� ������������
		HRESULT ScanStart(UINT32 nStartRecordIdx, WORD nScanId = 0);

		/// ���������������� ������������ �������
		HRESULT Scan(WORD nScanId = 0);

		/// ���������������� ������������ ������� � ��������� ��
		HRESULT ScanAndChange(WORD nScanId = 0);

		/// ������������ ����� ������
		HRESULT ScanOne(UINT32 nRecordIdx, WORD nScanId = 0);

		/// ������������ ����� ������ � ��������� ��
		HRESULT ScanOneAndChange(UINT32 nRecordIdx, WORD nScanId = 0);

		/// ��������� ������� ����� �������� ������ �������
		UINT32 GetFoundIdx(WORD nFindId = 0);

		/// ��������� ������� ����� ��������������� ������ �������
		UINT32 GetScanedIdx(WORD nScanId = 0);

		/// �������� ������
		HRESULT DeleteRecord(UINT32 nRecordIdx);

		/// ��������� ����� ������� � �������
		UINT32 GetRecordsNumber(VOID);

		/// ��������� ����� ��������� (��������� �� ��������) ������� � �������\n
		UINT32 GetDeletedRecordsNumber(VOID);

		/// ������ ������ �������. ���������� ������� ��������� �� ��������
		HRESULT Shrink(VOID);

		/// ��������� � ������ ������� ���������������� �������� (���� �� 16-� ���������). <iValueIdx> - ������ �������� [0..15]
		HRESULT SetUserValue(UINT iValueIdx, UINT32 uiValue);

		/// �������� �� ������ ������� ���������������� �������� (���� �� 16-� ���������). <iValueIdx> - ������ �������� [0..15]
		UINT32  GetUserValue(UINT iValueIdx);

		/// ������������� ��������� ������ � �������� ��������� (������� �������)
		HRESULT SpanFindInit(
			_TCHAR             * pKeyName,
			VOID               * pLowerKeyValue,
			VOID               * pUpperKeyValue,
			std::set< UINT32 > * pSetOfRecordsIndexes,
			WORD                 nFindId = 0,
			std::set< UINT32 > * pSetToIntersectWith = NULL
			);

		/// �� �� ��������, ��� � � SpanFindInit(), �� �������� �� ��� ��������� ����, � ������ 
		HRESULT SpanFindInit(
			UINT32               nKeyIndex,
			VOID               * pLowerKeyValue,
			VOID               * pUpperKeyValue,
			std::set< UINT32 > * pSetOfRecordsIndexes,
			WORD                 nFindId = 0,
			std::set< UINT32 > * pSetToIntersectWith = NULL
			);

		/// �� �� ��������, ��� � � SpanFindInit(), �� ����������� ����, ��� ������� ���� ���������� �������� nFindId
		HRESULT SpanFindInitEx(
			_TCHAR             * pKeyName,
			VOID               * pLowerKeyValue,
			VOID               * pUpperKeyValue,
			std::set< UINT32 > * pSetOfRecordsIndexes,
			WORD               * pnFindId,
			std::set< UINT32 > * pSetToIntersectWith = NULL
			);

		/// �� �� ��������, ��� � � SpanFindInit(), �� ����������� ����, ��� ������� ���� ���������� �������� nFindId
		HRESULT SpanFindInitEx(
			UINT32               nKeyIndex,
			VOID               * pLowerKeyValue,
			VOID               * pUpperKeyValue,
			std::set< UINT32 > * pSetOfRecordsIndexes,
			WORD               * pnFindId,
			std::set< UINT32 > * pSetToIntersectWith = NULL
			);


		///
		HRESULT SpanFindCancel(WORD nFindId);

		/// ��������� �������� ������� ������� (�� ��������� �����, ���������� � SpanFindInit())
		HRESULT SpanFind(WORD nFindId = 0);


	public:

		/// ������������ �� ������ ���� ������
		HRESULT Switch(VOID);

		/// ���������� ��������� ������ �������
		VOID    SetStartSize(UINT32 iStartSize);

		/// ���������� �������� �� ���������� ������� ��������� BACKUP-����� �������
		VOID    SetSaveAfterValue(UINT32 iSaveAfterValue)   {	m_SaveAfterValue=iSaveAfterValue; }

		/// ���������� ����� �����
		VOID    SetGrowModeS(_TCHAR * pModeStr);

		/// ���������� ����� �����
		VOID    SetGrowModeI(UINT32 iModeVal)   { m_HashGrowMode = iModeVal; }

		/// ����������� ������ ���-������
		VOID    ReCountHashInfoArray(VOID);

		/// ���������� ���������������� ����
		HRESULT SetDynamicInfo(CONST _TCHAR * pszDynamicPath);

		/// ������� ����������
		static  HRESULT MkDir(CONST _TCHAR * pDirName);

		/// ��������� ������������� ����������
		static  BOOL ChkDirExistence(CONST _TCHAR * pDirName);

		std::string  m_sTableIniStructure;

	private:

		/// ���� ���-�������
		DiskFileC fH;

		/// ���� �������
		DiskFileC fR;

		/// ���� ��������� � ��������� ������
		DiskFileC fV;

		/// ���� ����������
		DiskFileC fS;

	private: //

		/// ���� � ������ �������
		STLSTR             m_Path;

		/// ���� � ������������ �������
		STLSTR             m_DynamicPath;

		// ��� ������������ �������
		// STLSTR          m_DynamicName;

		/// ������������� ������ �������
		DTableTopoC      * m_TopoPtr;

		/// ���������� � ���-������
		SHashBlockInfo   * m_HashInfoArr;

		/// ���������� � �����
		SFieldInfo       * m_FieldsInfoArr;

		/// ����� ����� (�����)
		UINT32             m_FieldsNum;

		/// ����� �������� ����� (�����)
		UINT32             m_KeyFieldsNum;

		/// ������ ������� � �������� �������
		SRecordField     * m_RecordArr;

		/// ������ ������ �������
		UINT32             m_RecordSize;

		/// ��������� �� ����� ������
		UINT32             m_RecordNewPtr;

		/// ������ ������ �������� � ����� ��������� � ��������� ������
		UINT32             m_ValueNewPtr;

		/// ������ ������ ��������
		BYTE             * m_ValueBuff;

		/// ����� ������ ������ ��������
		UINT32             m_ValueBuffLen;

		/// ���� ������� ��� ������ Close()
		BOOL               m_ClearFlag;

		/// ���� �������� ���������/������������� ������������
		BOOL               m_bClearUserInitializations;

		/// �������  - ������������
		BOOL               m_bTableIsDynamic;

		/// �������  - ��������
		BOOL               m_bTableIsTemporary;

		/// ������� ����� ���������� ����
		BOOL               m_bTableHasUnicFields;

		//BOOL             m_bIncFlag;

		/// ������� ������������� ������
		WORD               m_Find_CurrId;

		/// ������� �������� ����� (��� ������ FindId)
		UINT32             m_Find_RecordFieldIdx[FIND_LIM+1];

		/// Cvtotybz �������� ������� (��� ������ FindId)
		UINT32             m_Find_RecordNextOffs[FIND_LIM+1];

		/// �������  �������� ������� (��� ������ FindId)
		UINT32             m_Find_RecordFoundIdx[FIND_LIM+1];

		/// ������ ������ (Find/FindOne/FindStart) (��� ������ FindId)
		BOOL               m_Find_AnswerNoMore[FIND_LIM+1];

		/// ��������� �� ����� ������ ���������� � FindInit() (��� ������ FindId)
		CONST VOID       * m_Find_KeyValuePtr[FIND_LIM+1];

		// ------------------------------------------------------------

		/// ��������� �� ������� ���������� ���������� � FindInit() (��� ������ FindId)
		VOID            ** m_Find_ppArrayOfPointersToData[FIND_LIM];

		/// ��������� �� ������ ���������� ���������� � AddInit()
		VOID            ** m_Add_UserDataPointers;

		/// ��������� �� ������ ���������� ���������� � ChangeInit()
		VOID            ** m_Change_UserDataPointers;

		/// ��������� �� ������� ���������� ���������� � ScanInit()
		VOID            ** m_Scan_ppArrayOfPointersToData[SCAN_LIM];

		/// ������ ������� ����������� ������
		UINT32             m_Scan_RecordIdx[SCAN_LIM];

		/// ����� ����� ���-�������
		UINT32             m_HashGrowMode;

		/// ��������� ������ ���-������� �������� �������������
		UINT32             m_HashBlockStartUserSize;

		/// ��������� ������ ���-������� (��������)
		UINT32             m_HashStartVolume;

		/// ��������� BACKUP-����� ������� ����� ������ m_SaveAfterValue �������
		UINT32             m_SaveAfterValue;

		/// ������� ������� �� BACKUP-���������
		UINT32             m_SaveAfterCnt;


		/// ���������� � �������
		SDTableInfo      * m_InfoPtr;

	private: //

		/// ���������� ����� �������� ��� ���������� ����
		HRESULT SaveNewValue(SFieldInfo * pFieldInfo, BYTE * pValuePtr, WORD nValueLen);

		/// ����� �� ����� � ��������� ����������
		HRESULT FindKeyAndAdd(SFieldInfo * pFieldInfo, BYTE * pValue, WORD nValueLen, BOOL bAddFlag = FALSE);

		/// �������� ������ ������ �������
		HRESULT GetRecordData(VOID * pDataPtrArr[], WORD nId, BOOL bFindMode);

		/// ���������� ������ ������ �������
		HRESULT SetRecordData(VOID * pDataPtrArr[], WORD nId, BOOL bFindMode);

		/// �������� ��������������� ����������
		VOID    ClearUserSetings(VOID);

		/// ����� ��������� ������������� ������
		BOOL    GetFreeFindId(WORD * pnFindId);

		/// ����� ��������� ������������� ���������
		BOOL    GetFreeScanId(WORD * pnScanId);

		/// ����� ��������� ������������� Span-������
		BOOL    GetFreeSpanFindId(WORD * pnFindId);

		/// ���������� ����������� �����, ������ ������ � �.�.
		VOID    SetInternalInfo(VOID);

		/// ����������� ������
		CritSectC          m_oCriticalSection;

		// -----------------------------------------------------

		/// ���������������/��������� ��������� ��������
		UINT32             m_oNodeValue_UINT32;

		/// ���������������/��������� ��������� ��������
		BYTE               m_oNodeValue_BYTE_ARR[10];

		/// ���������������/��������� ��������� ��������
		std::string        m_oNodeValue_STRING;

		/// ���������������/��������� ��������� ��������
		std::wstring       m_oNodeValue_WSTRING;

		/// ���������������/��������� ��������� ��������
		std::vector<BYTE>  m_oNodeValue_VECTOR;

		/// ��������� �� ���������������/��������� ��������� ��������
		BYTE             * m_pNodeValue_PTR;

		BYTE       * m_pCurrNodeValuePtr;
//		WORD         m_iCurrNodeValueLen;
		INT32        m_iCurrNodeHashIdx;
		INT32        m_iCurrNodeTableIdx;
		INT32        m_iCurrFoundRecordIdx;
		INT32        m_iCurrFoundRecordNextOffs;

		// -------------------------------------------------

		/// ������� �������� ����� (��� ������ SpanFindId)
		UINT32             m_SpanFind_RecordFieldIdx[  SPAN_FIND_LIM];

		/// ��������� �� ������ ������� ������ ���������� � SpanFindInit() (��� ������ SpanFindId)
		CONST VOID       * m_SpanFind_LowerKeyValuePtr[SPAN_FIND_LIM];

		/// ��������� ���. ������ ������� ������
		CONST VOID       * m_SpanFind_CurrLowerKeyValuePtr;

		/// ��������� �� ������� ������� ������ ���������� � SpanFindInit() (��� ������ SpanFindId)
		CONST VOID       * m_SpanFind_UpperKeyValuePtr[SPAN_FIND_LIM];

		/// ��������� ���. ������� ������� ������
		CONST VOID       * m_SpanFind_CurrUpperKeyValuePtr;

		/// ��������� �� STL::SET ���������� � SpanFindInit()
		std::set<UINT32> * m_SpanFind_UserSetPointers[SPAN_FIND_LIM];

		/// ��������� �� STL::SET ���������� ��� �������� INTERSECT
		std::set<UINT32> * m_SpanFind_IntersectPointers[SPAN_FIND_LIM];

		std::set<UINT32> * m_SpanFind_CurrIntersectPointer;

		/// ��������� �� ������� ���������� � ���� ������ 
		SFieldInfo       * m_SpanFind_FieldInfoPtr;
		
		/// ��������� �� ������� ������
		CIndexTree       * m_SpanFind_CurrBTreePtr;

		/// ��������� �� ������ �������� ������
		// SBTreeNodeMem   * m_SpanFind_CurrBTreeArr; !!!

		/// ������� FindId
		UINT32             m_SpanFind_FindId;

		// -------------------------------------------------------------

		/// ���������� ����� ������ � ���������� ����� ���� ������
		BOOL    NodeAdd(UINT32 iHashIdx);

		/// ��������� �������
		INT32   NodeInsertR(UINT32 iNodeIdx, UINT32 iHashIdx, UINT32 m_iTreeHeight);

		/// "���������" ����
		INT32   NodeSplit(UINT32 iNodeIdx);

		/// ����� �� ��������� ��������� � ��������� ������ (���������� �����)
		VOID    NodeSearchR(UINT32 iNodeIdx, UINT32 m_iTreeHeight, BOOL bNeedCheck = TRUE);
		
		/// �������� �������� ���� ������
		HRESULT NodeGetValue(UINT32 iRecordNum);

		/// �������� �������� ���� ������ �� HASH-�������
		HRESULT NodeGetValueViaHash(UINT32 iHashIdx);

		// ��������� "LowerOrEqual"
		// BOOL    NodeValueLE(SFieldInfo * pFieldInfo, BYTE * pValuePtr, WORD iValueLen);

		/// ��������� "Lower"
		BOOL    NodeValueL(VOID);

		/// ������ ���� � ���������� ������ ������ �������
		BOOL    NodeEstimateAndSaveInfo(UINT32 iLinkToHashRecord, BOOL bNeedCheck = TRUE);

		/// ������ ���� �� ��������� � ��������
		UINT32  NodeCheckInterval(UINT32 iLinkToHashRecord);



};
