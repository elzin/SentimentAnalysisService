#pragma once

#include "IInterface.h"
#include <set>
#include <list>
#include <algorithm>
#include <functional>

// #include <tchar.h>
#undef      _TCHAR
#define     _TCHAR wchar_t

// --------------------------------------------------------------------------------
// GUIDs & IIDs :

/// ������������� ������ DBMS
static const GUID CLSID_DBMS = { 0xac10aa0c, 0xa04a, 0x49de, { 0xb3, 0x21, 0xb8, 0x46, 0x7c, 0xc2, 0xb9, 0x2f } };

/// ������������� ���������� DBMS (��-�� - ������������� ���������� DBManager)
#define      IID_DBMS IID_DBManager // For compatibility 

/// ������������� ���������� DBManager
static const GUID IID_DBManager = { 0xa97222fc, 0xd98d, 0x49f5, { 0xb9, 0x78, 0xc5, 0x97, 0xa9, 0x76, 0x7b, 0xd4 } };

/// ������������� ���������� DBMS DataBase
static const GUID IID_DataBase = { 0xa66bf09b, 0x5a3c, 0x4b60, { 0x91, 0xe9, 0x42, 0xbb, 0xf1, 0xd5, 0xa1, 0xbd } };

// --------------------------------------------------------------------------------

namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			namespace DBMS
			{

				// --------------------------------------------------------------------------------
				// ������� ���������� ������������ �������

//				class IBase;      // ������� ������������ ����� �� "IBase.h"
				class IDBManager; // ��������� IDBManager (upper level)
				class IDataBase;  // ��������� IDataBase
				class IDataTable; // ��������� IDataTable (lower level)

				// --------------------------------------------------------------------------------
				// ������ ���������� ������������ �������

				// --------------------------------------------------------------------------------
				// NOTE: 
				//
				//    ��� ������ ����������� ������������ HRESULT, 
				//    ���������� ������ ���������: S_OK, S_FALSE � E_FAIL.
				//    S_OK �������� OK, S_FALSE �������� ������������� ��������� (��� ������),
				//    E_FAIL �������� ��������� ������, ���������������� ������� � ������� �������.

				// --------------------------------------------------------------------------------
				// 
				// --------------------------------------------------------------------------------

				/*! \interface IDBManager
				*   \brief     ��������� ��������� ��� ������ (DB Manager interface)
				*/
				class IDBManager : public virtual SS::Interface::IBase   {

				public:

					/// ���������� ���� "�����������������"
					virtual BOOL IsOpen(VOID) = 0;

					/// ���������� ��� �������
					virtual CONST _TCHAR * GetName(VOID) = 0;

					/// ������ ���������������� ���� � ������� ���������� � �������� ���������, ��������������� �� ���������� pFullPathToDbmsBases ����
					/** 
						\param pFullPathToIniFile
						\param pFullPathToDbmsBases
						\return virtual HRESULT
					 
					������ ���������������� ���� � ������� ���������� � �������� ���������, ��������������� �� ���������� pFullPathToDbmsBases ����
					*/
					virtual HRESULT Init(CONST _TCHAR * pFullPathToIniFile, CONST _TCHAR * pFullPathToDbmsBases) = 0;

					/// ������� ���������� (�� ��������) ��������� � ������������ ����� ������ "DynamicDataBase" (������ 0) -  ��� ������ ������ � ������������� ���������  
					/** 
						\param pIDataBase - ���� �� NULL, �� ���� "DynamicDataBase" ����� ������� � ��������� ����� ������� � ���������� ���������
						\return virtual HRESULT
					 
					������� ���������� (�� ��������) ��������� � ������������ ����� ������ "DynamicDataBase" (������ 0) -  ��� ������ ������ � ������������� ���������  

					*/
					virtual HRESULT InitDynamic(OUT IDataBase ** ppIDataBase = NULL) = 0;

					/// ����������� ������� �������� DBMS �� ����������� �� ���������. �������� ����� Init(), � ������, ����� �� ��� �� ���������.
					/** 
						\param pFullPathToIniFile
						\param pFullPathToDbmsBases
						\return virtual HRESULT
					 
					����������� ������� �������� DBMS �� ����������� �� ���������. �������� ����� Init(), � ������, ����� �� ��� �� ���������.
					*/
					virtual HRESULT Switch(CONST _TCHAR * pFullPathToIniFile, CONST _TCHAR * pFullPathToDbmsBases) = 0;

					/// ���������� �������_��������� �� ������ ���� ������
					virtual HRESULT MoveFirstDataBase(VOID) = 0;

					/// ���������� �������_��������� �� ��������� ���� ������
					virtual HRESULT MoveNextDataBase(VOID) = 0;

					/// ���������� �������_��������� �� ���������� ���� ������
					virtual HRESULT MovePrevDataBase(VOID) = 0;

					/// ���������� �������_��������� �� ��������� (��������) ���� ������
					virtual HRESULT MoveToDataBase(UINT32  nDBaseIndex) = 0;

					/// ���������� �������_��������� �� ��������� (������) ���� ������
					virtual HRESULT MoveToDataBase(CONST _TCHAR * pDBaseName) = 0;

					/// �������� ��������� �� ��������� ���� ������ � ������� ��������_���������
					virtual IDataBase * OpenDataBase(VOID) = 0;

				};

				// --------------------------------------------------------------------------------
				// 
				// --------------------------------------------------------------------------------

				/// ������������ ����� ������ ����� ������ (��� IDataBase::GreateDataTable())
				typedef enum EFieldDataTypes   {

					TYPE_INT32   = 0, // 32-�_�������_����� 
					TYPE_BYTE_10 = 1, // 10-�_��������_���������
					TYPE_STRING  = 2, // ������ std::string
					TYPE_VECTOR  = 3, // ������ std::vector<BYTE>
					TYPE_WSTRING = 4, // ������ std::wstring
					TYPE_UINT32  = 5, // 32-�_�������_�����������_����� 

					TYPE_FINAL = 100  // ����������� ������-���

				};

				/// ������������ ����� ������������� ����� ������ (��� IDataBase::GreateDataTable())
				typedef enum EFieldModificatorTypes   {
					MOD_COMMON  = 0x0000, // ������� ��������. (������������ �������� c ������������ ������).
					MOD_IS_UNIC = 0x0001, // �������� � ��������� ���� ����� �����������. ������ ������ ����� ���������� �� ����� ����� ������, � ����� ���������� ������ S_FALSE � ������, ����� �������� �������� ���� � ������� ��� ����. �������� ������ �� ���� ���������� ������ "NEXT". (������ �������������: ������� � ���������� ������)    
					MOD_NO_FIND = 0x0002, // ��� ������ �� ������� ����. �������� ������ �� ���� ���������� ������ "NEXT". (������ �������������: ��������� ������ � �����������, ��������� �� ������� �������)   
					MOD_IS_DATA = 0x0004, // ��� ������ �� ������� ����. �������� ��������� ����� � ������ ������ INT32 � BYTE_10. �������� ��������� � ������� ����� HASH-������� (������������� �������� ����� �������� ����������� !!!). �������� ������ �� ���� ���������� ������ "NEXT". (������ �������������: �� �������������, �� �������� ������)   
					MOD_INDEXED = 0x0008, // �������� ����� �� ��������� ��������� (SpanFind()). ������������ ��� ���������� � ������ ������������� ( ������: MOD_COMMON | MOD_INDEXED)
					MOD_FINAL   = 0x8000  // ����������� ������-�����������

				};

				/// ������������ ����� ����� ������ (��� IDataBase::GreateDataTable())
				typedef enum ETableGrowTypes   {

					GROW_EVEN = 0, // ����������� �� ����� �� ������
					GROW_DOWN = 1, // ��������� � 2 ����
					GROW_UP   = 2  // ����������� � 2 ����

				};

				/// �������� ���� ������� (��� IDataBase::GreateDataTable())
				struct TDataTableFieldDescription   {
					_TCHAR *               szFieldName;
					UINT32                 etFieldType;        // See enum <EFieldDataTypes> above
					UINT32                 etFieldModificator; // See enum <EFieldModificatorTypes> above
				};

				// --------------------------------------------------------------------------------
				// 
				// --------------------------------------------------------------------------------

				/*! \interface IDataBase
				*   \brief     ��������� ���� ������ (DataBase interface)
				*/
				class IDataBase   { // : public virtual SS::Interface::IBase   {

				public:

					/// ���������� ���� "�����������������"
					virtual BOOL IsOpen(VOID) = 0;

					/// ���������� ��� �������
					virtual CONST _TCHAR * GetName(VOID) = 0;

					/// �������/���������������� ���� ������
					/** 
						\param bClearUserInitializations
						\return virtual HRESULT
					 
					�������/���������������� ���� ������\n
					���������� ����� ��������� �� ��������� ���� ������ �������� �������������� \n
					���������� ����� ����������� �� ���������� ������ ������ �������� ��������������� \n
					�������� ������� �������� ���������.\n
					���� bClearUserInitializations == TRUE, �� ���������� ������������� ������������� (AddInit(), FindInit(), � ��.) ��������.
					*/
					virtual HRESULT Clear(BOOL bClearUserInitializations = TRUE) = 0;

					/// ������� ���� ��� �������, ��� ��� �������� ������\n
					/** 
						\return virtual HRESULT : S_OK - ���� �������, S_FALSE - ���� �� �������, �.�. �� ������� ��� ����������
					 
					������� ���� ��� �������, ��� ��� �������� ������\n
					*/
					virtual HRESULT TryClear(VOID) = 0;

					/// ��������� ������ � ��������� ����� ���������� �� ��������� ���� ������
					/** 
						\return virtual HRESULT
					 
					��������� ������ � ��������� ����� ���������� �� ��������� ���� ������\n
					���������� ����� ��������� �� ��������� ���� ������ ���������� ���������������� \n
					���������� ����� ����������� �� ���������� ������ ������ ���������� ����������������� \n
					*/
					virtual HRESULT Close(VOID) = 0;

					/// ���������� �������_��������� �� ������ ������� � ����
					virtual HRESULT MoveFirstDataTable(VOID) = 0;

					/// ���������� �������_��������� �� ��������� ������� � ����
					virtual HRESULT MoveNextDataTable(VOID) = 0;

					/// ���������� �������_��������� �� ���������� ������� � ����
					virtual HRESULT MovePrevDataTable(VOID) = 0;

					/// ���������� �������_��������� �� ��������� (��������) ������� � ����
					virtual HRESULT MoveToDataTable(UINT32  nDTableIndex) = 0;

					/// ���������� �������_��������� �� ��������� (������) ������� � ����
					virtual HRESULT MoveToDataTable(CONST _TCHAR * pDTableName)  = 0;

					/// �������� ��������� �� ��������� ������� � ������� ��������_���������
					virtual IDataTable * OpenDataTable(VOID) = 0;

					// --------------------------------------------------------
					// ������ ������ � ����������� ���������� ��������� ������
					// 

					/// ����������� ������� ������� ������ �� ��������� ���� � c ��������� ����������� (� �������� �������)
					virtual IDataTable * DynamicDataTableCreate(CONST _TCHAR * pPathToDTable, CONST _TCHAR * pDTableName, INT iInitialSize, ETableGrowTypes eTableGrowType, CONST TDataTableFieldDescription aoFieldDescription[], BOOL bOpenAfterCreation = FALSE) = 0;

					/// ������� ����������� ��������� ������� ������
					virtual HRESULT DynamicDataTableOpen(IDataTable * pIDataTable) = 0;

					/// ���������� �� ���������� ������ � ����������� ��������� �������� ������
					virtual HRESULT DynamicDataTableRefuse(IDataTable * pDTable) = 0;

					/// �������� ������ ���� ������ �� ��������� �����������
					virtual HRESULT GetDataTablesNames(IN CONST _TCHAR * pDirectoryToExplore, OUT std::list< std::wstring > * plstDataTablesNamesList) = 0;

				};

				// --------------------------------------------------------------------------------
				// 
				// --------------------------------------------------------------------------------

				/*! \interface IDataTable
				*   \brief     ��������� ������� ������ (DataTable interface)
				*/
				class IDataTable   { // : public virtual SS::Interface::IBase   {

				public:

					/// ���������� ���� "�����������������"
					virtual BOOL IsOpen(VOID) = 0;

					/// ���������� ��� �������
					virtual CONST _TCHAR * GetName(VOID) = 0;

					/// ��������� ������������� ����� ������� (� ������ ����, � �����������, ����� ��������� �����)
					/** 
						\return virtual HRESULT
					 
					��������� ������������� ����� ������� (� ������ ����, � �����������, ����� ��������� �����)\n
					*/
					virtual HRESULT SaveBackup(VOID) = 0;

					/// ��������� ������� ������ ������� (���� ���������� ������ �� �����, �� � ������ ����, ������ ��������� �����������)
					/** 
						\return virtual HRESULT
					 
					��������� ������� ������ ������� (���� ���������� ������ �� �����, �� � ������ ����, ������ ��������� �����������)\n
					*/
					virtual HRESULT Save(VOID) = 0;

					/// �������/���������������� �������\n
					/** 
						\param bClearUserInitializations
						\return virtual HRESULT
					 
					�������/���������������� �������\n
					���������� ����� ��������� �� ��������� ������� �������� ��������������.\n
					�������� ������� �������� ���������.\n
					���� bClearUserInitializations == TRUE, �� ���������� ������������� ������������� (AddInit(), FindInit(), � ��.) ��������.
					*/
					virtual HRESULT Clear(BOOL bClearUserInitializations = TRUE) = 0;

					/// ������� ������� ��� �������, ��� ������� ����� �������� ����� ����\n
					/** 
						\return virtual HRESULT : S_OK - ������ �������, S_FALSE - ������ �� �������, �.�. �� ��� ����������
					 
					������� ������� ��� �������, ��� ������� ����� �������� ������� ����� ����\n
					*/
					virtual HRESULT TryClear(VOID) = 0;

					/// ��������� ������ � ��������� ����� ���������� �� ��������� �������.\n
					/** 
						\param bClearAfterClose
						\return virtual HRESULT
					 
					��������� ������ � ��������� ����� ���������� �� ��������� �������.\n
					������� ����� ���� �������.\n
					���������� ����� ��������� �� ��������� ������� ���������� ����������������.
					*/
					virtual HRESULT Close(BOOL bClearAfterClose = FALSE) = 0;

					// -------------------------------------------------------
					
					/// ������������� ��������� ���������� ������� � �������
					/** 
						\param ppArrayOfPointersToData[]
						\return virtual HRESULT
					 
					������������� ��������� ���������� ������� � �������\n
					�������� ���� ������ "VOID"-���������� �� ����������,	������� ����� ��������� ������ ����� �������\n
					���������� ����� ������ �������� � ��������� �������� � ��� ��������� ����������.
					*/
					virtual HRESULT AddInit(VOID * ppArrayOfPointersToData[]) = 0;

					/// ���������� ������ � �������
					/** 
						\return virtual HRESULT
					 
					���������� ������ � �������\n
					� ������� ������������ ������ ����������� �� ����������, ���������� � AddInit()
					*/
					virtual HRESULT Add(VOID) = 0;

					/// ��������� ����� ������� � �������
					/** 
						\return virtual UINT32
					 
					��������� ����� ������� � �������\n
					*/
					virtual UINT32 GetRecordsNumber(VOID) = 0;

					/// �������� ������
					/** 
						\param nRecordIdx
						\return virtual HRESULT ���������� S_OK ��� S_FALSE � ������ ����� ��������� ������ ���.

					�������� ������\n
					������ ���������� �� ��������. � ����������� ��� �� ������������ ������� ������ � ������������\n
					�������� �������� �� ������ ������ ���������� ������������� ��� ����� ��������� ������� > 25% ���\n
					��� ����� ������ ������ Shrink()\n
					*/
					virtual HRESULT DeleteRecord(UINT32 nRecordIdx) = 0;

					/// ��������� ����� ��������� (��������� �� ��������) ������� � �������
					/** 
						\return virtual UINT32
					 
					��������� ����� ��������� (��������� �� ��������) ������� � �������\n
					*/
					virtual UINT32 GetDeletedRecordsNumber(VOID) = 0;

					/// ������ ������ �������. ���������� ������� ��������� �� ��������
					/** 
						\return virtual HRESULT ���������� S_OK, S_FAIL ��� S_FALSE � ������, ����� ������ �� �����.

					������ ������ �������. ���������� ������� ��������� �� ��������\n
					����� ������� ������ ������� ������ ���� �������\n
					*/
					virtual HRESULT Shrink(VOID) = 0;

					// -------------------------------------------------------
					
					/// ������������� ��������� ������
					/** 
						\param pKeyName ������ ��� ��������� ����.\n
						\param pKeyValue ������ ��������� �� ���������� � ������� ����� ���������� �������� ����� ������.\n
						\param ppArrayOfPointersToData[] ������ ������ "VOID"-���������� �� ���������� � ������� ����� �������� ������ ����� �������.\n
						\param nFindId - ������������� ������������ ������. ������������ �������� �� 128 �������. �� ��������� ��� ������ �������� � ������� ������������� ������.\n
						\return virtual HRESULT
					 
					������������� ��������� ������.\n
					���� ��� �� ����� ������������ ����, �� �� ��������� � ppArrayOfPointersToData[] ����� ���� ����������� � NULL.\n
					���������� ������ ������ �������� � ��������� �������� � ��� ��������� ���������� � ������ � ����� ������ Find().\n
					*/
					virtual HRESULT FindInit(_TCHAR * pKeyName, VOID * pKeyValue, VOID * ppArrayOfPointersToData[], WORD nFindId = 0) = 0;

					/// �� �� ��������, ��� � � FindInit(), �� �������� �� ��� ��������� ����, � ������ 
					virtual HRESULT FindInit(UINT32 nKeyIndex, VOID * pKeyValue, VOID * ppArrayOfPointersToData[], WORD nFindId = 0) = 0;

					/// �� �� ��������, ��� � � FindInit(), �� ����������� ����, ��� ������� ���� ���������� �������� nFindId
					virtual HRESULT FindInitEx(_TCHAR * pKeyName, VOID * pKeyValue, VOID * ppArrayOfPointersToData[], WORD * pnFindId) = 0;

					/// �� �� ��������, ��� � � FindInit(), �� ����������� ����, ��� ������� ���� ���������� �������� nFindId
					virtual HRESULT FindInitEx(UINT32   nKeyIndex, VOID * pKeyValue, VOID * ppArrayOfPointersToData[], WORD * pnFindId) = 0;

					/// ����� �� ������ �� ��������� nFindId
					/** 
						\param nFindId ������������� ������������ ������.
						\return virtual HRESULT
					*/
					virtual HRESULT FindCancel(WORD nFindId = 0) = 0;

					/// ����� � ��������� �������� ������� ������� (�� �������� �����, ���������� � FindInit())
					/** 
						\param nFindId - ������������� ������������ ������. ������������ �������� �� 128 �������. �� ��������� ��� ������ �������� � ������� ������������� ������.
						\return virtual HRESULT
					 
					����� � ��������� �������� ������� ������� (�� �������� �����, ���������� � FindInit())\n
					������ ������������ �� ���������� �������� � FindInit(). \n
					���������� S_OK � ������ �������� ������ � ��������� ��� S_FALSE � ������ ����� ������� ��� ��� ������ ���.\n
					����� ����������� S_FALSE ���������������, ��� ��������� ����� Find() ����� �������� � ����� ��������� �����, ���������� � FindInit()
					*/
					virtual HRESULT Find(WORD nFindId = 0) = 0;
				
					/// ����� � ��������� ������������ ������ ������� (�� �������� �����, ���������� � FindInit())
					/** 
						\param nFindId - ������������� ������������ ������. ������������ �������� �� 128 �������. �� ��������� ��� ������ �������� � ������� ������������� ������.
						\return virtual HRESULT
					 
					����� � ��������� ������������ ������ ������� (�� �������� �����, ���������� � FindInit())\n
					������ ������������ �� ���������� �������� � FindInit(). \n
					���������� S_OK � ������ �������� ������ � ��������� ���	S_FALSE � ������ ����� ����� ������ ���.\n
					��������� ������ Find???() ����� �������� � ����� ��������� �����.
					*/
					virtual HRESULT FindOne(WORD nFindId = 0) = 0;

					/// ��������� ������� ����� �������� ������ �������
					/** 
						\param nFindId - ������������� ������������ ������.
						\return virtual UINT32
					 
					��������� ������� ����� �������� ������ �������.\n
					���������� ������ ��� 0xFFFFFFFF � ������ ������.\n
					*/
					virtual UINT32 GetFoundIdx(WORD nFindId = 0) = 0;

					/// �������������� �������.
					/** 
						\param nFindId - ������������� ������������ ������. ������������ �������� �� 128 �������. �� ��������� ��� ������ �������� � ������� ������������� ������.\n
						\return virtual HRESULT ���������� S_OK � ������ ���� �������� �������� ����� � ������� ���� ��� S_FALSE - � ������ ���������� ������ (����������� ����� Find() ��� �� ������ S_FALSE).\n
					 
					�����������, ��� ����������� ����� Find() ����� �������� � �����
					��������� ����� (���������� � FindInit()), ���������� �� ����,
					���������� ���������� ����� (Find()==S_FALSE) ��� ��� (Find()==S_OK).\n
					!!! ����� ������� �������� ������ ����� ������ ��� ���� ����������.\n
					������ ������ ������� ������ �� ������������
					*/

					virtual HRESULT FindStart(WORD nFindId = 0) = 0;
					
					/// �������������� �������.
					/** 
						\param nFindId - ������������� ������������ ������. ������������ �������� �� 128 �������. �� ��������� ��� ������ �������� � ������� ������������� ������.\n
						\return virtual HRESULT ���������� S_OK ��� E_FAIL � ������ ��������� nFindId.\n
					 
					�����������, ��� ����������� ����� Find() ����� �������� � ����� ��������� ����� (���������� � FindInit()),
					���������� �� ����,	���������� ���������� ����� (Find()==S_FALSE) ��� ��� (Find()==S_OK).\n
					!!! ����������� ����� ������� ������ �������� �����  - �� ���������.\n
					������ ������ ������� ������ �� ������������\n
					*/
					virtual HRESULT FindStop(WORD nFindId = 0) = 0;

					// -------------------------------------------------------

					/// ������������� ��������� ������ � �������� ��������� (������� �������)
					/** 
						\param nKeyIndex            - ������ ��� ��������� ����.\n
						\param pLowerKeyValue       - ������ ��������� �� ���������� � ������� ����� ���������� �������� ������ ������� ���������.\n
						\param pUpperKeyValue       - ������ ��������� �� ���������� � ������� ����� ���������� �������� ������� ������� ���������.\n
						\param pSetOfRecordsIndexes - ������ STL::SET � ������� ����� �������� ������� ����� ��������������� �������� ������.\n
						\param nSpanFindId          - ������������� ������������ ������. ������������ �������� �� 16 �������. �� ��������� ��� ������ �������� � ������� ������������� ������.\n
						\param pSetToIntersectWith  - ������ STL::SET ����������� � ������� - ���� ����������� ������� ��� ��������� � pSetOfRecordsIndexes.\n
						\return virtual HRESULT.\n
					 
					������������� ��������� ������ � �������� ��������� (������� �������)\n
					���������� ������ ������ �������� � ��������� �������� � ��� ��������� ���������� � ������������� ������ ������ FindSpan().\n
					*/
					virtual HRESULT SpanFindInit(
						_TCHAR             * pKeyName,
						VOID               * pLowerKeyValue,
						VOID               * pUpperKeyValue,
						std::set< UINT32 > * pSetOfRecordsIndexes,
						WORD                 nSpanFindId = 0,
						std::set< UINT32 > * pSetToIntersectWith = NULL
						) = 0;

					/// �� �� ��������, ��� � � SpanFindInit(), �� �������� �� ��� ��������� ����, � ������ 
					virtual HRESULT SpanFindInit(
						UINT32               nKeyIndex,
						VOID               * pLowerKeyValue,
						VOID               * pUpperKeyValue,
						std::set< UINT32 > * pSetOfRecordsIndexes,
						WORD                 nSpanFindId = 0,
						std::set< UINT32 > * pSetToIntersectWith = NULL
						) = 0;

					/// �� �� ��������, ��� � � SpanFindInit(), �� ����������� ����, ��� ������� ���� ���������� �������� nSpanFindId
					virtual HRESULT SpanFindInitEx(
						_TCHAR             * pKeyName,
						VOID               * pLowerKeyValue,
						VOID               * pUpperKeyValue,
						std::set< UINT32 > * pSetOfRecordsIndexes,
						WORD               * pnSpanFindId,
						std::set< UINT32 > * pSetToIntersectWith = NULL
						) = 0;

					/// �� �� ��������, ��� � � SpanFindInit(), �� ����������� ����, ��� ������� ���� ���������� �������� nSpanFindId
					virtual HRESULT SpanFindInitEx(
						UINT32               nKeyIndex,
						VOID               * pLowerKeyValue,
						VOID               * pUpperKeyValue,
						std::set< UINT32 > * pSetOfRecordsIndexes,
						WORD               * pnSpanFindId,
						std::set< UINT32 > * pSetToIntersectWith = NULL
						) = 0;


					/// ��������� �������� ������� ������� (�� ��������� �����, ���������� � SpanFindInit())
					/** 
						\param nSpanFindId - ������������� ������������ ������. ������������ �������� �� 16 �������. �� ��������� ��� ������ �������� � ������� ������������� ������.
						\return virtual HRESULT
					 
					��������� �������� ������� ������� (�� ��������� �����, ���������� � SpanFindInit())\n
					������ ������������ � STL::SET �������� � SpanFindInit(). \n
					���������� S_OK � ������ �������� ������ � ��������� ��� S_FALSE � ������ ����� ������� ���.\n
					*/
					virtual HRESULT SpanFind(WORD nSpanFindId = 0) = 0;

					// -------------------------------------------------------

					/// ������������� ��������� ���������
					/** 
						\param nStartRecordIdx - ������ ������ ������� � ������� �������� ������������.\n
						\param ppArrayOfPointersToData[] - ������ ������ "VOID"-���������� �� ���������� � ������� ����� �������� ������ ����� �������.\n
						\param nScanId - ������������� ������������ ���������.
						\return virtual HRESULT ���������� S_OK ��� S_FALSE � ������ ��������� ������ ���.\n
					 
					������������� ��������� ���������\n
					������ �������� nStartRecordIdx ������ ������ ������ � ������� ����� ����� ��������\n
					������ �������� ppArrayOfPointersToData ������ ������ "VOID"-���������� �� ���������� �
					������� ����� �������� ������ ����� �������.\n
					���� ��� �� ����� ������������ ����, �� �� ��������� ����� ���� ����������� � NULL\n
					���������� ��������� �������� � ������ � ����� ������ Scan().\n
					*/
					virtual HRESULT ScanInit(UINT32 nStartRecordIdx, VOID * ppArrayOfPointersToData[], WORD nScanId = 0) = 0;

					/// �� �� ��������, ��� � � ScanInit(), �� ����������� ����, ��� ������� ���� ���������� �������� nScanId
					virtual HRESULT ScanInitEx(UINT32 nStartRecordIdx, VOID * ppArrayOfPointersToData[], WORD * pnScanId) = 0;

					/// ����� �� ��������� �� ��������� nScanId
					/** 
						\param nScanId ������������� ������������ ���������.
						\return virtual HRESULT
					*/
					virtual HRESULT ScanCancel(WORD nScanId = 0) = 0;

					/// ������������� ���������� ������� ��������� ���������
					/** 
						\param nStartRecordIdx - ������ ������ ������� � ������� �������� ������������.\n
						\param nScanId - ������������� ������������ ���������.
						\return virtual HRESULT ���������� S_OK ��� S_FALSE � ������ ��������� ������ ���.\n
					*/
					virtual HRESULT ScanStart(UINT32 nStartRecordIdx, WORD nScanId = 0) = 0;

					/// �������� � ��������� ������� ������� (�� �������� �������, ��������� � ScanInit())
					/** 
						\param nScanId - ������������� ������������ ���������.
						\return virtual HRESULT ���������� S_OK ��� S_FALSE � ������ ����� ������� ������ ���.
					 
					�������� � ��������� ������� ������� (�� �������� �������, ��������� � ScanInit())\n
					������ ������������ �� ���������� �������� � ScanInit(). 
					*/
					virtual HRESULT Scan(WORD nScanId = 0) = 0;
					
					/// ��������� ������������ ������� �������
					/** 
						\param nRecordIdx - ����� ����������� ������
						\param nScanId    - ������������� ������������ ���������.
						\return virtual HRESULT ���������� S_OK ��� S_FALSE � ������ ����� �������� ������ ���.
					 
					��������� ������������ ������� �������\n
					������ ������������ �� ���������� �������� � ScanInit(). \n
					*/
					virtual HRESULT ScanOne(UINT32 nRecordIdx, WORD nScanId = 0) = 0;

					/// ��������� ������� ����� ��������������� ������ �������
					/** 
						\param nScanId - ������������� ������������ ���������.
						\return virtual UINT32
					 
					��������� ������� ����� ��������������� ������ �������.\n
					���������� ������ ��� 0xFFFFFFFF � ������ ������.\n
					*/
					virtual UINT32 GetScanedIdx(WORD nScanId = 0) = 0;

					// -------------------------------------------------------

					/// ������������� ��������� ���������
					/** 
						\param ppArrayOfPointersToData[]
						\return virtual HRESULT
					 
					������������� ��������� ���������\n
					�������� ���� ������ "VOID"-���������� �� ����������,	������� ����� ��������� ����� ������ ����� �������
					���� ��� �� ����� �������� ������������ ����, �� �� ��������� ����� ���� ����������� � NULL. \n
					���������� ��������� ������ ������� �������� � ���������
					�������� � ��� ��������� ���������� � ������ ������� FindOneAndChange() ��� ScanOneAndChange().\n
					���������� ������ �� ���� �������, ������� ����� ����������� IS_DATA.
					*/
					virtual HRESULT ChangeInit(VOID * ppArrayOfPointersToData[]) = 0;

					/// ����� (�� �������� �����, ���������� � FindInit()) � ��������� ������������ ������ �������
					/** 
						\return virtual HRESULT ���������� S_OK � ������ �������� ������ � ��������� ��� S_FALSE � ������ ����� ����� ������ ��� ��� E_FAIL ��� �������� ����������.
					 
					����� (�� �������� �����, ���������� � FindInit()) � ��������� ������������ ������ �������\n
					������ ��� ��������� ������� �� ���������� �������� � ChangeInit(). \n
					���������� ������ �� ���� �������, ������� ����� ����������� IS_DATA.\n
					��������� ������ Find???() ����� �������� � ����� ��������� �����.
					*/
					virtual HRESULT FindOneAndChange(WORD nFindId = 0) = 0;

					/// ����� (�� �������� �����, ���������� � FindInit()) � ��������� ��������
					/** 
						\return virtual HRESULT ���������� S_OK � ������ �������� ������ � ��������� ��� S_FALSE � ������ ����� ����� ������ ��� ��� E_FAIL ��� �������� ����������.
					 
					����� (�� �������� �����, ���������� � FindInit()) � ��������� ��������\n
					���������� ������� ������� ����������� IS_DATA � ������ �� ������ ������.\n
					��������� ������ Find???() ����� �������� � ����� ��������� �����.
					*/
					// virtual HRESULT FindOneAndInc(WORD nFindId = 0) = 0;

					/// ��������� ������������ ������ �������
					/** 
						\param nRecordIdx
						\return virtual HRESULT ���������� S_OK � ������ �������� ������ � ��������� ���	S_FALSE � ������ ����� ����� ������ ��� ��� E_FAIL ��� �������� ����������.
					 
					��������� ������������ ������ �������\n
					������ ��� ��������� ������� �� ���������� �������� � ChangeInit(). \n
					���������� ������ �� ���� �������, ������� ����� ����������� IS_DATA.\n
					*/
					virtual HRESULT ScanOneAndChange(UINT32 nRecordIdx, WORD nScanId = 0) = 0;

					/// ��������� � ������ ������� ���������������� �������� (���� �� 16-� ���������)
					/** 
						\param iValueIdx - ������ �������� [0..15]
						\param uiValue   - ��������
						\return virtual HRESULT
					*/
					virtual HRESULT SetUserValue(UINT iValueIdx, UINT32 uiValue) = 0;

					/// �������� �� ������ ������� ���������������� �������� (���� �� 16-� ���������)
					/** 
						\param iValueIdx - ������ �������� [0..15]
						\return virtual UINT32 
					*/
					virtual UINT32  GetUserValue(UINT iValueIdx ) = 0;
				};
			}
		}
	}
}
