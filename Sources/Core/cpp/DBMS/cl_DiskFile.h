#pragma once

#include <string>
#include "fn_Generic.h"

#undef  DBMS_SRC_FILE
#define DBMS_SRC_FILE "cl_DiskFile.h"


/*! \class DiskFileC
	*  \brief ������ � ��������� ������� */
class DiskFileC   {

	public: //

		/// �����������
		DiskFileC();

		/// ����������
		~DiskFileC();

	public:

		/// ����������/�������� ���� � ����� � ��� �����
		VOID SetPathAndName(CONST STLSTR * sFilePath, CONST _TCHAR * sFileName);

		/// �������� ��� ����� (������ ���)
		CONST STLSTR * GetName(VOID) { return(&m_FName); }

		/// �������� ���� � ����� (������ ����)
		CONST STLSTR * GetPath(VOID) { return(&m_FPath); }

		/// �������� ������ ���� � ����� (���� � ���)
		CONST STLSTR * GetFullPath(VOID) { return(&m_FFullPath); }

		/// ��������� ������������� �����
		BOOL ChkDirExistence(VOID);

		/// ������� ��� ������� ����
		HRESULT Open(VOID);

		/// �������� �������� ������
		HRESULT Flush(VOID);

		/// ���������� ������ ��������� ����� �������
		HRESULT Clear(VOID);

		/// ������� ����
		HRESULT Close(BOOL bClearAfterClose = FALSE);

		/// ������� ����
		HRESULT Delete(VOID);

		/// ������������� �� *.* � ~*.*
		HRESULT RenameBack(VOID);

		/// ������������� �� *.*_tmp � *.*
		HRESULT RenameTmp(VOID);

		/// ���������� ����
		HRESULT Move(CONST _TCHAR * sNewFileName);

		/// ��������� ���� ������ �� �������� nFillValue �������� nBytesNum32
		HRESULT Fill(UINT32 nBytesNum32, BYTE nFillValue);

		/// �������� ������� ������� � ����� �� nBytesNum32 ���� �� nFromPosition
		HRESULT SetPosition(UINT32 nBytesNum32, DWORD nFromPosition = FILE_BEGIN);

		/// �������� ������� � �����
		UINT32 GetPosition(VOID);

		/// �������� ������ �����
		UINT32 GetSize(VOID);

		/// ������ �� ����� �� ���������� ��������
		HRESULT ReadAt(UINT32 nBeginOffset, LPVOID pData, INT32 nDataLen);

		/// ������ �� ����� �� �������� ��������
		HRESULT Read(LPVOID pData, DWORD nDataLen);

		/// ������ � ���� �� ���������� ��������
		HRESULT WriteAt(UINT32 nBeginOffset, LPCVOID pData, DWORD nDataLen);

		/// ������ � ���� �� �������� (current_offset - nDataLen)
		HRESULT WriteAtBackOffset(LPCVOID pData, INT32 nDataLen);

		/// ������ � ����� �����
		HRESULT WriteAtEnd(LPCVOID pData, DWORD nDataLen);

		/// ������ ��������������� ����� � ����
		HRESULT  fprintf(CHAR * FormatStr, ...);

	public:

		/// ��� �����
		STLSTR m_FName;

		/// ���� � �����
		STLSTR m_FPath;

		/// ������ ���� � �����
		STLSTR m_FFullPath;

	private: //

		/// ��������� �����
		HANDLE      m_FHandle;

//		UINT32      m_FPos64;
//		DWORD       m_FSectorSize;

		/// ������� ������� ������ OS
		BOOL        m_CoolOsFlag;

		/// ���������� ������� ������
		HRESULT _Write(LPCVOID pData, DWORD nDataLen)   {
			DWORD WrittenDataLen;

			//return(WriteFile(m_FHandle,pData,nDataLen,&WrittenDataLen,NULL) &&  nDataLen==WrittenDataLen);

			if(!WriteFile(m_FHandle,pData,nDataLen,&WrittenDataLen,NULL)/* ||  nDataLen!=WrittenDataLen*/)   {
				return(E_FAIL);
			} else   {
				return(S_OK);
			}
		}

		/// ���������� ������� ������
		HRESULT _Read(LPVOID pData, DWORD nDataLen)   {
			DWORD ReaddenDataLen; // Bad english

			//return(ReadFile(m_FHandle,pData,nDataLen,&ReaddenDataLen,NULL) && nDataLen==ReaddenDataLen);

			if(!ReadFile(m_FHandle,pData,nDataLen,&ReaddenDataLen,NULL)/* || nDataLen!=ReaddenDataLen*/)   {
				return(E_FAIL);
			} else   {
				return(S_OK);
			}
		}
};
