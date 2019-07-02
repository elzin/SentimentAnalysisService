#pragma once
#include ".\const.h"
#include ".\console.h"
#include "..\ASDInterface\INdxDataStorage.h"
#include ".\basisfile.h"
#include ".\file_cash.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxDataStorage
{
class CDataUnitFactory;

//�������� ������� � ������������
#pragma warning( disable : 4250 )

//--------------------------------------------------------------------//

///���� ���������� ����������� ����������� ������
class CACashedFile : public CBasisFile, public SS::Interface::Core::NdxSE::NdxDataStorage::INdxCashedFile
{
friend class CDataUnitFactory;

protected:
	CACashedFile(CDataUnitFactory* pDataStorageFactory);
	virtual ~CACashedFile(void);
	
public:
	//-----------IBase
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	//-----------Eof-IBase

	//-----------INdxDataUnit
	///��������� ���� ������ � ������� ������
	bool Open(const wchar_t* pszPath);
	///��������� ���� ������ 
	bool Close(void);
	///���������� ���� ������ 
	bool Flush(void);
	///�������  ���� ������ 
	void Clear(void);
	///���������� ������ ����� ������ 
	unsigned int GetDataUnitSize(void);
	//-----------Eof-INdxDataUnit

	//-----------INdxFile
	///������ �� ����� �� ������� �������
	void Read(unsigned char* pBuffer, unsigned int uiSize);
	///����� � ���� �� ������� �������
	void Write(unsigned char* pBuffer, unsigned int uiSize);
	///��������� � �����
	void Append(unsigned char* pBuffer, unsigned int uiSize);
	///�������� ������� ������� � �����
	void SeekPos(unsigned int uiOffset, unsigned int uiOrigin);
	///���������� ������� ������� � �����
	unsigned int TellPos(void){return m_uiCurrOffset;};
	//-----------Eof-INdxFile


	//-----------INdxCashedFile
	///�������������� ��������� ����
	void InitCash(unsigned int uiCashBufferSize, unsigned int uiCashMinSizeToFlush){TO_CONSOLE(L"Not supported");};
	///�������� ����
	void Cashed(void){TO_CONSOLE(L"Not supported");};
	///���������� �� ���� ����������� ������ ���� �����
	void FlushFilledBuffers(void);
	//-----------Eof-INdxCashedFile
	
	///����������� ���������� �� �����
	void	View(void);
	///����������� ���������� �� ������� ������� � �����
	void	ViewFilePos(void);

protected:
	///�������� ��� ������ ����������
	FileCash::CFileCash m_IndexModeFileCash;

	///������� �������� � ����� (���������� �� ������)
	unsigned int m_uiCurrOffset;
	///����������� ������ ����, ������� ����� ����������
	unsigned int m_cuiCashMinSizeToFlush;
};

//--------------------------------------------------------------------//

///���� ���������� ����������� ����������� � �������� ������
class CRACashedFile : public CACashedFile
{
friend class CDataUnitFactory;
friend class CDataStorageFactory;

protected:
	CRACashedFile(CDataUnitFactory* pDataStorageFactory);
	virtual ~CRACashedFile(void);
	
public:
	///��������� ���� � ������� ������
	bool	Open(const wchar_t* pszPath);
	///��������� ����
	bool	Close(void);
	/////������ ������ �� �����
	//void	Read(unsigned char* pBuffer, unsigned int uiSize);
	/////������������� ������� ������� � �����
	//void	SeekPos(unsigned int uiOffset, unsigned int uiOrigin);

protected:
	/////������ ������ �� ���� ������
	//void ReadFromCash(unsigned char* pBuffer, unsigned int uiSize);

	///�������� ��� ������ ������
	FileCash::CReadFileCash m_ReadFileCash;
};

//--------------------------------------------------------------------//

#pragma warning( default : 4250 )

}
}
}
}
