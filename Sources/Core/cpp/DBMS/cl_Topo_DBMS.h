#pragma once

#include "..\ASCInterface\IDBMS.h"
#include "cl_DTablePhys.h"

using namespace SS::Interface::Core::DBMS;

#undef  DBMS_SRC_FILE
#define DBMS_SRC_FILE "cl_Topo_DBMS.h"


///	����� �������� DBMS (������� � ��������)
class DBManagerTopoC;

///	����� ���� ������
class DBaseTopoC;

///	����� ������� ������
class DTableTopoC;

///	����� ���� ������ (������ � ��������)
class DFieldTopoC;

/*! \class DObjC
	*  \brief ������� ����� ��� ������� ���������: DBManagerTopoC, DBaseTopoC, DTableTopoC, DFieldTopoC
*/
class DObjC   {

	public :

		/// Constructor
		DObjC() : m_HierLevel(0), m_ParentPtr(NULL), m_LockedFlag(FALSE), m_IndexInParentMap(0)   { 
			// OutputDebugString(_T("DObjC +++\n"));
		}
//		~DObjC()   { 
//		  // OutputDebugString(_T("DObjC ---\n"));
//		}

	public :

		/// ������� � ��������
		WORD         m_HierLevel;

		/// ��� ������
		STLSTR       m_Name;

		/// ��������� �� ��������
		DObjC      * m_ParentPtr;

		/// ������ ������� (� ����� �����)
		WORD         m_IndexInParentMap;

		/// ���� "������ �������"
		BYTE         m_LockedFlag;

		/// ����������� ������
		CritSectC    m_oTopoCriticalSection;
};

/*! \class DObjParentTC
	*  \brief ������� ����� ��� ������� ��������� ������� �����: DBManagerTopoC, DBaseTopoC, DTableTopoC
*/
template <typename ChildTypeT> class DObjParentTC : public DObjC   {

	public:

		/// ����� ������� �� ����� �� �����
		typedef std::map < STLSTR, ChildTypeT * >  ChildNameMapT;
		/// ����� ������� �� ����� �� �����
		typedef std::pair< STLSTR, ChildTypeT * >  ChildNamePairT;
		/// ����� ������� �� ����� �� �������
		typedef std::map < WORD,        ChildTypeT * >  ChildIndexMapT;
		/// ����� ������� �� ����� �� �������
		typedef std::pair< WORD,        ChildTypeT * >  ChildIndexPairT;

		// �������� ��� ����� �����
		#define ChildIteratorT ChildIndexMapT::iterator

		/// Consrtructor
		DObjParentTC(CONST _TCHAR * sName, WORD nIndex):
			m_ReferenceCounter(0),
			m_ChildrenNum(0),
			m_ChildCurrent(0),
			m_ChildMoveResult(S_FALSE)   {

			m_ParentPtr        = NULL;
			m_Name             = sName;
			m_IndexInParentMap = nIndex;

			// OutputDebugString(_T("DObjParentTC +++\n"));
		}

		/// Destructor
		~DObjParentTC()   {

			// OutputDebugString(_T("DObjParentTC ---\n"));

			if(m_ReferenceCounter)   {
				if(m_HierLevel!=1 || m_IndexInParentMap!=0)   { // DynamicDataBase
					LogMess(_T("Object <%s> was not closed before destructor call (Reference_Counter != 0)"),m_Name.c_str());
					m_ReferenceCounter = 0;
				}
			}

			for(ChildIndexMapT::const_iterator  ci =m_ChildIndexMap.begin();
															ci!=m_ChildIndexMap.end();
															ci++)   if(ci->second)   delete (ChildTypeT *)ci->second;

			m_ChildIndexMap.clear();
			m_ChildNameMap.clear();
		}

	public:

		/// ������� � �������� �������� ������
		ChildTypeT * AddChild(CONST _TCHAR * sChildName)   {
			ChildTypeT * pC;
			std::pair<ChildNameMapT::iterator,  bool> retN;
			std::pair<ChildIndexMapT::iterator, bool> retI;

			#pragma warning( disable : 4291)
			if((pC = new ChildTypeT(sChildName,m_ChildrenNum))==NULL)   {
				LogFail(_F,ERROR_NOT_ENOUGH_MEMORY,_T("New_Child_Class_Instance was not build(%s::%s)"),m_Name.c_str(),sChildName);
				return(NULL);
			}
			#pragma warning( default : 4291)

			pC->m_ParentPtr=static_cast<DObjC *>(this);
			pC->m_HierLevel=m_HierLevel+1;

			retN = m_ChildNameMap.insert(ChildNamePairT(sChildName,pC));
			retI = m_ChildIndexMap.insert(ChildIndexPairT(m_ChildrenNum,pC));

			if(retN.second && retI.second)   {
				m_ChildrenNum++;
			} else   {
				LogFail(_F,ERROR_NOT_ENOUGH_MEMORY,_T("New_Child_Class_Instance was not inserted in STD::MAP (%s\\%s)Error"),m_Name.c_str(),sChildName);
				delete pC;
				pC=NULL;
			}

			return(pC);
		}

		/// ������� �������� ������
		HRESULT DeleteChild(ChildTypeT * pChild)   {
			size_t iCnt=0;

			iCnt+=m_ChildNameMap.erase(pChild->m_Name);
			iCnt+=m_ChildIndexMap.erase(pChild->m_IndexInParentMap);

			delete pChild;

			if(iCnt==2)   {
				m_ChildrenNum--;
			} else   {
				LogFail(_F,ERROR_NOT_ENOUGH_MEMORY,_T("Child_Class_Instance was not deleted in STD::MAP (%s\\%s)Error"),m_Name.c_str(),pChild->m_Name.c_str());
			}

			return(S_OK);
		}

		/// ����� ������� �� �����
		ChildTypeT * FindChild(CONST _TCHAR * sChildName)   {
			ChildNameMapT::const_iterator ci =  m_ChildNameMap.find(sChildName);
			return((ci!=m_ChildNameMap.end())?(ci->second):(NULL));
		}

		/// ����� ������� �� �������
		ChildTypeT * FindChild(WORD nChildIndex)   {
			ChildIndexMapT::const_iterator ci =  m_ChildIndexMap.find(nChildIndex);
			return((ci!=m_ChildIndexMap.end())?(ci->second):(NULL));
		}

		/// ����������� ���������� ��������� �� ������� �������
		HRESULT MoveFirstChild(VOID)   {
			m_ChildCurrent=0;
			return(m_ChildMoveResult=S_OK);
		}

		/// ����������� ���������� ��������� �� ���������� �������
		HRESULT MoveNextChild(VOID)   {
			if(++m_ChildCurrent==m_ChildrenNum)   {
				m_ChildCurrent--;
				return(m_ChildMoveResult=S_FALSE);
			} else   {
				return(m_ChildMoveResult=S_OK);
			}
		}

		/// ����������� ���������� ��������� �� ����������� �������
		HRESULT MovePrevChild(VOID)   {
			if(m_ChildCurrent==0)   {
				return(m_ChildMoveResult=S_FALSE);
			} else   {
				m_ChildCurrent--;
				return(m_ChildMoveResult=S_OK);
			}
		}

		/// ����������� ���������� ��������� �� ���������� �������� �������
		HRESULT MoveToChild(UINT32  nChildIndex)   {
			if(FindChild(nChildIndex))   {
				m_ChildCurrent=nChildIndex;
				return(m_ChildMoveResult=S_OK);
			} else   {
				return(m_ChildMoveResult=S_FALSE);
			}
		}

		/// ����������� ���������� ��������� �� ���������� ������ �������
		HRESULT MoveToChild(CONST _TCHAR * pChildName)   {

			ChildTypeT * pChild=FindChild(pChildName);

			if(pChild)   {
				m_ChildCurrent=pChild->m_IndexInParentMap;
				return(m_ChildMoveResult=S_OK);
			} else   {
				return(m_ChildMoveResult=S_FALSE);
			}
		}

		/// �������� ��������� (pointer) �� ������� � ������� �������� �������
		HRESULT GetChild(ChildTypeT ** ppChild)   {
			ChildTypeT * pChild=FindChild(m_ChildCurrent);

			if(pChild)   {
				if(m_ChildMoveResult==S_OK)   {
					*ppChild=pChild;
					return(S_OK);
				} else   {
					*ppChild=NULL;
					return(LogFail(_F,ERROR_INVALID_ACCESS,_T("Previous MOVE_TO_CHILD command does not succeeded")));
				}
			} else   {
				*ppChild=NULL;
				return(LogFail(_F,ERROR_INVALID_ACCESS,_T("Expected CHILD_OBJECT was not accessed")));
			}
		}

		/// ���������� ����� ���������� ���������
		HRESULT UnGetChild(ChildTypeT * pChild)   {
			return(S_OK);
		}


	public:

		/// ����� �����
		WORD            m_ChildrenNum;

		/// ������ �������� �������
		WORD            m_ChildCurrent;

		/// ����� ���� �����
		ChildNameMapT   m_ChildNameMap;

		/// ����� �������� �����
		ChildIndexMapT  m_ChildIndexMap;

		/// ��������� �������� ������������ �� �����
		HRESULT         m_ChildMoveResult;

		/// ������� ������ (������� ����� ��������)
		UINT32          m_ReferenceCounter;
};



/*! \class DBManagerTopoC
	*  \brief ����� ���������: �������� ��� ������
*/
class DBManagerTopoC : public SS::Interface::Core::DBMS::IDBManager, public DObjParentTC<DBaseTopoC>   {

	public: //
/*
		DBManagerTopoC(const STLSTR * sName, WORD nIndex) :
			DObjParentTC<DBaseTopoC>(sName,nIndex) { g_pDBManager=this; };
*/
		/// �����������
		DBManagerTopoC() :
			DObjParentTC<DBaseTopoC>(_T(""),0) { m_Initialized=FALSE; };

	public: // Interface

		/// ���������� ��������
		virtual ULONG   Release();

		/// �������� ���������
		virtual HRESULT QueryInterface(REFIID pIID, VOID ** pBase);


	public: // Interface

		/// ���� "������ ������"
		BOOL    IsOpen(VOID) { return(m_ReferenceCounter); }

		/// ���������� ��� �������
		CONST _TCHAR * GetName(VOID) { return(m_Name.c_str()); }

		/// ������ ��������� INI-���� � �� ���� ������� ����� DBMS �� �����
		HRESULT Init(CONST _TCHAR * pFullPathToIniFile, CONST _TCHAR * pFullPathToDbmsBases);

		/// ������� ���������� (�� ��������) ��������� ��� ������ ������ � ������������� ��������� � ������������ ����� ������ "DynamicDataBase" (������ - 0)
		HRESULT InitDynamic(OUT IDataBase ** ppIDataBase = NULL);

		/// ������ ��������� INI-���� � �� ���� ������� ����� DBMS �� �����
		HRESULT Switch(CONST _TCHAR * pFullPathToIniFile, CONST _TCHAR * pFullPathToDbmsBases);

		/// ��������������� �����. ������ ��������� INI-���� � �� ���� ������� ����� DBMS � ������
		HRESULT InitReadDbmsName(CONST _TCHAR * pFullPathToIniFile, CONST _TCHAR * pFullPathToDbmsBases);

		/// ����������� ���������� ��������� �� ������ ���� ������ - <DynamicDataBase> ��� ������������ ������
		HRESULT MoveFirstDataBase(VOID) { return(MoveFirstChild()); }

		/// ����������� ���������� ��������� �� ��������� ���� ������
		HRESULT MoveNextDataBase(VOID) { return(MoveNextChild()); }

		/// ����������� ���������� ��������� �� ���������� ���� ������
		HRESULT MovePrevDataBase(VOID) { return(MovePrevChild()); }

		/// ����������� ���������� ��������� �� ��������� �������� ���� ������ (Idx: 0 - ���� <DynamicDataBase> ��� ������������ ������)
		HRESULT MoveToDataBase(UINT32  nDBaseIndex) { return(MoveToChild(nDBaseIndex)); }

		/// ����������� ���������� ��������� �� ��������� ������ ���� ������
		HRESULT MoveToDataBase(CONST _TCHAR * pDBaseName) { return(MoveToChild(pDBaseName)); }

		/// �������� ��������� (pointer) �� ���� ������ � ������� �������� �������
		IDataBase * OpenDataBase(VOID);

	private:

		/// ����: DBMS ���� ��������������������
		BOOL    m_Initialized; //

		/// ��������������� �����. ������ ��������� INI-���� � �� ���� ������� ����� DBMS � ������
		HRESULT InitReadTopoFile(CONST _TCHAR * pFullPathToIniFile, CONST _TCHAR * pFullPathToDbmsBases);

		/// �������� ������ DBMS �� �����
		HRESULT InitBuildPhysicalImage(VOID);
};


/*! \class DBaseTopoC
	*  \brief ����� ���������: ���� ������
*/
class DBaseTopoC : public SS::Interface::Core::DBMS::IDataBase, public DObjParentTC<DTableTopoC>  {

	public:

		/// �����������
		DBaseTopoC(CONST _TCHAR * sName, WORD nIndex) :
			DObjParentTC<DTableTopoC>(sName,nIndex) {};

	//public:

	//	// ���������� ���� ������
	//	virtual ULONG   Release();

	//	// �������� ���������
	//	virtual HRESULT QueryInterface(REFIID pIID, VOID ** pBase);

	public:

		/// ���� "������ ������"
		BOOL    IsOpen(VOID) { return(m_ReferenceCounter); }

		/// ���������� ��� �������
		CONST _TCHAR * GetName(VOID) { return(m_Name.c_str()); }

		/// �������� ���� ������
		HRESULT Clear(BOOL bClearUserInitializations = TRUE);

		/// ������� ���� ��� �������, ��� ��� �������� ������\n
		HRESULT TryClear(VOID);

		/// ������� ���� ������
		HRESULT Close(VOID);

		/// ����������� ���������� ��������� �� ������ ������� ������
		HRESULT MoveFirstDataTable(VOID) { return(MoveFirstChild()); }

		/// ����������� ���������� ��������� �� ��������� ������� ������
		HRESULT MoveNextDataTable(VOID) { return(MoveNextChild()); }

		/// ����������� ���������� ��������� �� ���������� ������� ������
		HRESULT MovePrevDataTable(VOID) { return(MovePrevChild()); }

		/// ����������� ���������� ��������� �� ��������� �������� ������� ������
		HRESULT MoveToDataTable(UINT32  nDTableIndex) { return(MoveToChild(nDTableIndex)); }

		/// ����������� ���������� ��������� �� ��������� ������ ������� ������
		HRESULT MoveToDataTable(CONST _TCHAR * pDTableName) { return(MoveToChild(pDTableName)); }

		/// �������� ��������� (pointer) �� ������� ������ � ������� �������� �������
		IDataTable * OpenDataTable(VOID);

		/// ����������� ������� ������� ������ �� ��������� ���� � c ��������� ����������� (� �������� �������)
		IDataTable * DynamicDataTableCreate(CONST _TCHAR * pPathToDTable, CONST _TCHAR * pDTableName, INT iInitialSize, ETableGrowTypes eTableGrowType, CONST TDataTableFieldDescription aoFieldDescription[], BOOL bOpenAfterCreation = FALSE);

		/// ������� ����������� ��������� ������� ������
		HRESULT DynamicDataTableOpen(IDataTable * pIDataTable);

		/// ���������� �� ���������� ������ � ����������� ��������� �������� ������
		HRESULT DynamicDataTableRefuse(IDataTable * pDTable);

		/// �������� ������ ���� ������ �� ��������� �����������
		HRESULT GetDataTablesNames(IN CONST _TCHAR * pDirectoryToExplore, OUT std::list< std::wstring > * plstDataTablesNamesList);
		
};

/*! \class DTableTopoC
	*  \brief ����� ���������: ������� ������
*/
class DTableTopoC : public SS::Interface::Core::DBMS::IDataTable, public DObjParentTC<DFieldTopoC>, public DTablePhysC   {

	public: //

		DTableTopoC(CONST _TCHAR * sName, WORD nIndex) : DObjParentTC<DFieldTopoC>(sName,nIndex)  { DTablePhysC::m_TopoPtr = this; }

	public: // Interface

		/// ��������� - "�������"
		BOOL    IsOpen(VOID) { return(m_ReferenceCounter); }

		/// ���������� ��� �������
		CONST _TCHAR * GetName(VOID) { return(m_Name.c_str()); }

		/// �������� ������� ������
		HRESULT Clear(BOOL bClearUserInitializations = TRUE)  { return(DTablePhysC::Clear(bClearUserInitializations)); }

		/// ������� ������� ��� �������, ��� ������� ����� �������� ����� ����\n
		HRESULT TryClear(VOID) { return(DTablePhysC::TryClear()); }

		/// ��������� ������������� ����� ������� (� ������ ����, � �����������, ����� ��������� �����)
		HRESULT SaveBackup(VOID) { return(DTablePhysC::SaveBackup(TRUE)); }

		/// ��������� ������� ������ ������� (���� ���������� ������ �� �����, �� � ������ ����, ������ ��������� �����������)
		HRESULT Save(VOID) { return(DTablePhysC::SaveBackup()); }

		/// ������� ������� ������
		HRESULT Close(BOOL bClearAfterClose = FALSE)  { return(DTablePhysC::Close(bClearAfterClose)); }

		/// ������������� ���������� ������ � �������
		HRESULT AddInit(VOID * ppArrayOfPointersToData[]) { return(DTablePhysC::AddInit(ppArrayOfPointersToData)); }

		/// ������������� ���������� ������ � �������
		HRESULT ChangeInit(VOID * ppArrayOfPointersToData[]) { return(DTablePhysC::ChangeInit(ppArrayOfPointersToData)); }

		/// ���������� ������ � �������
		HRESULT Add(VOID) { return(DTablePhysC::Add()); }

		/// ��������� ����� ������� � �������
		UINT32 GetRecordsNumber(VOID) { return(DTablePhysC::GetRecordsNumber()); }

		/// �������� ������
		HRESULT DeleteRecord(UINT32 nRecordIdx) { return(DTablePhysC::DeleteRecord(nRecordIdx)); }

		/// ��������� ����� ��������� (��������� �� ��������) ������� � �������\n
		UINT32 GetDeletedRecordsNumber(VOID) { return(DTablePhysC::GetDeletedRecordsNumber()); }

		/// ������ ������ �������. ���������� ������� ��������� �� ��������
		HRESULT Shrink(VOID) { return(DTablePhysC::Shrink()); }

		/// ������������� ��������� ������
		HRESULT FindInit(_TCHAR * pKeyName,  VOID * pKeyValue, VOID * ppArrayOfPointersToData[], WORD nFindId = 0) { return(DTablePhysC::FindInit(pKeyName, pKeyValue,ppArrayOfPointersToData,nFindId)); }

		/// ������������� ��������� ������
		HRESULT FindInit(UINT32 nKeyIndex, VOID * pKeyValue, VOID * ppArrayOfPointersToData[], WORD nFindId = 0) { return(DTablePhysC::FindInit(nKeyIndex,pKeyValue,ppArrayOfPointersToData,nFindId)); }

		/// ������������� ��������� ������
		HRESULT FindInitEx(_TCHAR * pKeyName,  VOID * pKeyValue, VOID * ppArrayOfPointersToData[], WORD * pnFindId) { return(DTablePhysC::FindInitEx(pKeyName, pKeyValue,ppArrayOfPointersToData,pnFindId)); }

		/// ������������� ��������� ������
		HRESULT FindInitEx(UINT32   nKeyIndex, VOID * pKeyValue, VOID * ppArrayOfPointersToData[], WORD * pnFindId) { return(DTablePhysC::FindInitEx(nKeyIndex,pKeyValue,ppArrayOfPointersToData,pnFindId)); }

		/// ���������� ������
		HRESULT FindCancel(WORD nFindId = 0) { return(DTablePhysC::FindCancel(nFindId)); }

		/// ����� � �������
		HRESULT Find(WORD nFindId = 0) { return(DTablePhysC::Find(nFindId)); }

		/// ����� ������������ ������
		HRESULT FindOne(WORD nFindId = 0) { return(DTablePhysC::FindOne(nFindId)); }

		/// ��������� ������� ����� �������� ������ �������
		UINT32 GetFoundIdx(WORD nFindId = 0) { return(DTablePhysC::GetFoundIdx(nFindId)); };

		/// ������ ������ � ������
		HRESULT FindStart(WORD nFindId = 0) { return(DTablePhysC::FindStart(nFindId)); }

		/// ��������� ������
		HRESULT FindStop(WORD nFindId = 0) { return(DTablePhysC::FindStop(nFindId)); }

		/// ����� ������������ ������ � ��������� ��
		HRESULT FindOneAndChange(WORD nFindId = 0) { return(DTablePhysC::FindOneAndChange(nFindId)); }

//		HRESULT FindOneAndInc(WORD nFindId = 0)  { return(DTablePhysC::FindOneAndInc(nFindId)); }

		/// ������������� ��������� ������������
		HRESULT ScanInit(UINT32 nStartRecordIdx, VOID * ppArrayOfPointersToData[], WORD nScanId = 0) { return(DTablePhysC::ScanInit(nStartRecordIdx,ppArrayOfPointersToData,nScanId)); }

		/// ������������� ��������� ������������
		HRESULT ScanInitEx(UINT32 nStartRecordIdx, VOID * ppArrayOfPointersToData[], WORD * pnScanId) { return(DTablePhysC::ScanInitEx(nStartRecordIdx,ppArrayOfPointersToData,pnScanId)); }

		/// ���������� ��������� ������������
		HRESULT ScanCancel(WORD nScanId = 0) { return(DTablePhysC::ScanCancel(nScanId)); }

		/// ��������� ���������� ������ ������ ��� ������������
		HRESULT ScanStart(UINT32 nStartRecordIdx, WORD nScanId = 0) { return(DTablePhysC::ScanStart(nStartRecordIdx,nScanId)); }

		/// ���������������� ������������ ������
		HRESULT Scan(WORD nScanId = 0) { return(DTablePhysC::Scan(nScanId)); }

		/// ������� ���� �������� ��������
		HRESULT ScanOne(UINT32 nRecordIdx, WORD nScanId = 0) { return(DTablePhysC::ScanOne(nRecordIdx,nScanId)); }

		/// ��������� ������� ����� ��������������� ������ �������
		UINT32 GetScanedIdx(WORD nScanId = 0) { return(DTablePhysC::GetScanedIdx()); };

		/// ������� ���� �������� �������� � �������� ���
		HRESULT ScanOneAndChange(UINT32 nRecordIdx, WORD nScanId = 0) { return(DTablePhysC::ScanOneAndChange(nRecordIdx,nScanId)); }

		/// �������� ���������������� ��������
		HRESULT SetUserValue(UINT iValueIdx, UINT32 uiValue) { return(DTablePhysC::SetUserValue(iValueIdx,uiValue)); }

		/// �������� ���������������� ��������
		UINT32  GetUserValue(UINT iValueIdx ) { return(DTablePhysC::GetUserValue(iValueIdx)); }

		/// ������������� ��������� ������ � �������� ��������� (������� �������)
		HRESULT SpanFindInit(
			_TCHAR             * pKeyName,
			VOID               * pLowerKeyValue,
			VOID               * pUpperKeyValue,
			std::set< UINT32 > * pSetOfRecordsIndexes,
			WORD                 nFindId = 0,
			std::set< UINT32 > * pSetToIntersectWith = NULL
			) { return(DTablePhysC::SpanFindInit(pKeyName,pLowerKeyValue,pUpperKeyValue,pSetOfRecordsIndexes,nFindId,pSetToIntersectWith)); }

		/// �� �� ��������, ��� � � SpanFindInit(), �� �������� �� ��� ��������� ����, � ������ 
		HRESULT SpanFindInit(
			UINT32               nKeyIndex,
			VOID               * pLowerKeyValue,
			VOID               * pUpperKeyValue,
			std::set< UINT32 > * pSetOfRecordsIndexes,
			WORD                 nFindId = 0,
			std::set< UINT32 > * pSetToIntersectWith = NULL
			) { return(DTablePhysC::SpanFindInit(nKeyIndex,pLowerKeyValue,pUpperKeyValue,pSetOfRecordsIndexes,nFindId,pSetToIntersectWith)); }

		/// �� �� ��������, ��� � � SpanFindInit(), �� ����������� ����, ��� ������� ���� ���������� �������� nFindId
		HRESULT SpanFindInitEx(
			_TCHAR             * pKeyName,
			VOID               * pLowerKeyValue,
			VOID               * pUpperKeyValue,
			std::set< UINT32 > * pSetOfRecordsIndexes,
			WORD               * pnFindId,
			std::set< UINT32 > * pSetToIntersectWith = NULL
			) { return(DTablePhysC::SpanFindInitEx(pKeyName,pLowerKeyValue,pUpperKeyValue,pSetOfRecordsIndexes,pnFindId,pSetToIntersectWith)); }

		/// �� �� ��������, ��� � � SpanFindInit(), �� ����������� ����, ��� ������� ���� ���������� �������� nFindId
		HRESULT SpanFindInitEx(
			UINT32               nKeyIndex,
			VOID               * pLowerKeyValue,
			VOID               * pUpperKeyValue,
			std::set< UINT32 > * pSetOfRecordsIndexes,
			WORD               * pnFindId,
			std::set< UINT32 > * pSetToIntersectWith = NULL
			) { return(DTablePhysC::SpanFindInitEx(nKeyIndex,pLowerKeyValue,pUpperKeyValue,pSetOfRecordsIndexes,pnFindId,pSetToIntersectWith)); }


		/// ��������� �������� ������� ������� (�� ��������� �����, ���������� � SpanFindInit())
		HRESULT SpanFind(WORD nFindId = 0) { return(DTablePhysC::SpanFind(nFindId)); }

};


/*! \class DFieldTopoC
	*  \brief ����� ���������: ���� ������
*/
class DFieldTopoC : public DObjC  {

	public:

		/// �����������
		DFieldTopoC(CONST _TCHAR * sName, WORD nIndex) :
			m_NoFindFlag(FALSE),
			m_IsUnicFlag(FALSE),
			m_IsDataFlag(FALSE),
			m_IndexedFlag(FALSE),
			m_FType(EFieldDataTypes::TYPE_INT32),
			m_FSize(0)
		{
			m_Name  = sName;
			m_IndexInParentMap = nIndex;
		}

	public: //

		/// ������������� ���������� m_FType � m_FSize �������� ����� ����
		BOOL         SetTypeInfo(_TCHAR * pTypeName);

		/// ������������� ���������� m_FType � m_FSize �������� ����� ����
		BOOL         SetTypeInfo(UINT32 iTValue);

		/// �������� ��� ����
		CONST _TCHAR * GetTypeName(VOID);

		/// ��� ����
		EFieldDataTypes   m_FType;

		/// ������ ���� � ������
		INT16            m_FSize;

		/// ���� ������� ������
		BOOL             m_NoFindFlag;

		/// ���� ������������ (���������� �������� ���� ����� ���������� � ������� ������ ���� ���)
		BOOL             m_IsUnicFlag;

		/// ���� ������ (��� ������ � �����������, � ���� ����������� ���������)
		BOOL             m_IsDataFlag;

		/// ���� ������� (����������� ������ � �������� ���������)
		BOOL             m_IndexedFlag;

};





