#pragma once

//#include "..\containers\define.h"

#undef  DBMS_SRC_FILE
#define DBMS_SRC_FILE "fn_Generic.h"

#define _F __FUNCTION__

///	������ ��������� �� ������ � ������ �������
/**
	\param pFuncName  - ��� ������� � ������� ��������� ������
	\param nFailCode  - ��� ������
	\param pFormatStr - ������ ��������������
	\param ...        - ���������� ������ ����������
	\return HRESULT   - ��� ������ nFailCode ��� ��� �� GetLastError()

	������ ��������� �� ������ � ������ �������
	*/
HRESULT LogFail(CHAR * pFuncName, HRESULT nFailCode, _TCHAR * pFormatStr, ...);

///	������ �������� ��������� � ������ �������
/**
	\param pFormatStr - ������ ��������������
	\param ... - ���������� ������ ����������
	\return VOID

	������ �������� ��������� � ������ �������
	*/
VOID LogMess(_TCHAR * pFormatStr, ...);

extern BOOL g_bItIsCDROM;

/// ��������� �������� � CD-ROM ( TRUE == �� )
BOOL IsItCDROM(VOID);


///	������� CHAR-������  � TCHAR-������
/**
	\param   CONST CHAR *
	\return _TCHAR *

	������� CHAR-������  � TCHAR-������
	*/
//_TCHAR * CHAR2TCHAR(CONST    CHAR * pszStr);
_TCHAR * CHAR2TCHAR(CONST CHAR * pszStr, _TCHAR * pszStrDst);

///	������� TCHAR-������  � WCHAR-������
/**
	\param   CONST _TCHAR *
	\return  WCHAR *

	������� TCHAR-������  � WCHAR-������
	*/
//WCHAR * TCHAR2WCHAR(CONST _TCHAR * pszStr);
WCHAR * TCHAR2WCHAR(CONST _TCHAR * pszStr, WCHAR * pszStrDst);

/// �������� ������
/**
	\param   _TCHAR *

	�������� ������
	*/
BOOL DeleteFiles(CONST _TCHAR * pszPath, CONST _TCHAR * pszBackSlashAndMask);

/// ���������� BACKUP-������
/**
	\param   _TCHAR *

	���������� BACKUP-������
	*/
BOOL BakFiles_Save(CONST _TCHAR * pszPath);

/// �������������� BACKUP-������
/**
	\param   _TCHAR *

	�������������� BACKUP-������
	*/
BOOL BakFiles_Restore(CONST _TCHAR * pszPath);

/// ������������� BACKUP-������
/**
	\param   _TCHAR *

	������������� BACKUP-������
	*/
BOOL BakFiles_Exist(CONST _TCHAR * pszPath);


/// STL-��������� 
class CContainer_HMap_Int_Int   {

	public:

		BOOL Add(INT iInt1, VOID * iInt2)   {
			if(Find(iInt1))   {
				return(TRUE);
			} else   {
				_oPair.first  = iInt1;
				_oPair.second = iInt2;
				_oRet=_oMap.insert(_oPair);
				_oItr=_oRet.first;	
				return(_oRet.second==TRUE);
			}
		}

		BOOL Find(INT iInt1)  {
			_oItr=_oMap.find(iInt1);
			return(_oItr!=_oMap.end());
		}

		VOID DeleteFound(VOID)  {
			_oItr=_oMap.erase(_oItr);
		}

		UINT Size(VOID)    { return((UINT)_oMap.size()); }
		VOID Clear(VOID)   {	_oMap.clear();	}
		VOID Start(VOID)   {	_oItr = _oMap.begin(); _iIdx=-1; }
		BOOL Get(VOID)     {	if(++_iIdx) _oItr++; return(_oItr != _oMap.end()); }
		INT  First(VOID)   { return((*_oItr).first); }
		VOID * Second(VOID)  { return((*_oItr).second); }


		typedef std::unordered_map< INT , VOID * > TMap;
		typedef std::pair< INT , VOID * >        TPair;
		typedef TMap::iterator                TItr;
		typedef std::pair<TItr, BOOL>         TRet;

		TMap  _oMap;
		TPair _oPair;
		TItr  _oItr;
		TRet  _oRet; 
		INT   _iIdx;
};



