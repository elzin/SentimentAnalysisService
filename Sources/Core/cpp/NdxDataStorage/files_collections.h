#pragma once

#include ".\basisfile.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxDataStorage
{

class CDataUnitFactory;

//--------------------------------------------------------------------//

///��������� ������
class CFilesCollection : public CDataUnit
{
friend class CDataUnitFactory;

protected:
	typedef vector<SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit*> TFiles;

	CFilesCollection(CDataUnitFactory* pDataStorageFactory);
	virtual ~CFilesCollection(void);

public:
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

	//---������ � ����������
	///������� ��� ����� �� ��������� 
	void DeleteFiles(void);
	///��������� ���� � ���������
	bool AddFile(void);
	///���������� ������ �������� �����
	unsigned char GetCurrentFileIndex(void);
	///���������� ������� ���������� ������
	unsigned int GetFilesNumber(void){return (unsigned int)m_FilesCollection.size();};
	///��������� � ������� ����� � ���������
	bool MoveFirstFile(void);
	///��������� � ����� � ���������
	bool MoveToFile(unsigned int uiFileIndex);
	///��������� � ���������� ����� � ���������
	bool MoveLastFile(void);
	///���������� ������� ���� � ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* GetCurrentFile(void);

protected:
	///���������� ��� ����� ���������
	virtual void GenerateFileName(unsigned int uiFileIndex, wstring* pszFileName);
	///������� ���� ���������
	virtual SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* CreateFile(unsigned int uiFileIndex);

	///��������� ������
	TFiles m_FilesCollection;
	///������� ����
	TFiles::iterator m_itCurrentFile;
	///��������� ��� ������������� ����������
	TFiles m_NullCollection;
	///������� ������� ����
	wstring m_szCurrentFilePath;

	///������������ ���������� ������ � ���������
	unsigned int m_uiMaxFilesNumber;
};

//--------------------------------------------------------------------//

///������-����, ������������� �������� ������ ����� �� ���������
class CFilesCollectionEx : public CFilesCollection
{
friend class CDataUnitFactory;

protected:
	CFilesCollectionEx(CDataUnitFactory* pDataStorageFactory);
	virtual ~CFilesCollectionEx(void);
	
public:
	//-----------INdxDataUnit
	///��������� ���� � ������� ������
	bool Open(const wchar_t* pszPath);
	///��������� ���� ������ 
	bool Close(void);
	//-----------Eof-INdxDataUnit

	///���������� ������� ���� � ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* GetCurrentFile(void);

protected:
	///���������� ��������� ���������� ������
	unsigned int ReadDataUnitNumber(void);
	///������������� ��������� ���������� ������
	void WriteDataUnitNumber(void);
};

//--------------------------------------------------------------------//

}
}
}
}