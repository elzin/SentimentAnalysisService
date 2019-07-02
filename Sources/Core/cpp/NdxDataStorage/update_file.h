#pragma once

#include ".\cashed_files.h"
#include ".\files_collections.h"

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

///���� ����������� ������
class CUpdateFile : public CFilesCollection
{
friend class CDataUnitFactory;
 
protected:
	CUpdateFile(CDataUnitFactory* pDataStorageFactory);
	virtual ~CUpdateFile(void);

	///���� ������ ���������
	enum EUpdateStorageFiles
	{
		///���� ��������
		eusfOffsets,
		///���� ��������� ��������
		eusfFreeOffsets,
		///���� ������
		eusfData
	};

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
	//-----------Eof-INdxDataUnit

	///�������� � ����� ������
	void	SeekPosInData(unsigned int uiOffset, unsigned int uiOrigin);
	///������ � ���� ������
	void	WriteData(unsigned char* pBuffer, unsigned int uiSize);
	
	//������ ������
	///��������� �� ������ ������, ���������� �� ������
	void	StartRead(unsigned int uiOffset, unsigned int* puiDataSizeInFile);
	///������ ����� ������ ������� �������
	void	Read(unsigned char* pData, unsigned int uiDataSize);
	///��������� ������ ��������� ������ ��������� ������
	void	StopRead(unsigned int* puiReadedDataSize);

	//���������� ������
	///��������� �� ������ ������, ���������� �� ��������
	void	StartAppend(unsigned int* puiOffset);
	///��������� ����� ������ ������� �������
	void	Append(unsigned char* pData, unsigned int uiDataSize);
	///��������� ���������� ��������� ������ ����������� ������
	void	StopAppend(unsigned int* puiAppendedDataSize);

	///�������� ������
	void DeleteData(unsigned int uiOffset);
	
	///���������� ������ ������������ ������ (��������� ����, �����������)
	unsigned int GetWorkedDataSize(void){return m_uiWorkedDataSize;};
	
	///���������� ������� � �����
	void ViewFilePos(void);

	///���������, ������� ���������� ������, ��������������� ����������
	bool Shrink(void);

protected:
	///���������� � ������
	struct SDataInfo
	{
		///�������� �� ������
		unsigned int m_uiDataOffset;
		///������ ������
		unsigned int m_uiDataSize;
	};
	typedef vector<SDataInfo> TDataInfoCollection;
	
	///�������� ������ ������ �� TDataInfoCollection, ������������ ������ �� ������� 
	//����� ������ � �����
	void ShrinkData(TDataInfoCollection* pDataInfoCollection, 
		SS::Interface::Core::NdxSE::NdxDataStorage::INdxCashedFile* pDataFile,
		SS::Interface::Core::NdxSE::NdxDataStorage::INdxCashedFile* pNewDataFile);
	///��������� ���� ������ �������
	void ReplaceDataFile(SS::Interface::Core::NdxSE::NdxDataStorage::INdxCashedFile* pNewDataFile);

	///������� ������� � ���������� ��������
	unsigned int SeekToFreeOffset(void);
	///������ ��������� ��������
	void MoveUpFreeOffsets(void);
	///���������� �� ���� ��������� ��������
	void MoveDownFreeOffsets(void);
	///��������� ��������� ��������
	void AddFreeOffset(unsigned int uiOffset);

	///���������� ��� ����� ���������
	void GenerateFileName(unsigned int uiFileIndex, wstring* pszFileName);
	///������� ���� ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* CreateFile(unsigned int uiFileIndex);
	///���� �������� �� ������ ��������: �������� �� ������|������ ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* GetOffsetsFile(void)
	{
		//return m_FilesCollection.empty()?NULL:dynamic_cast<SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile*>(m_FilesCollection[eusfOffsets]);
		if(!m_pOffsetFile){
			m_pOffsetFile=m_FilesCollection.empty()?NULL:dynamic_cast<SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile*>(m_FilesCollection[eusfOffsets]);
		}

		return m_pOffsetFile;
	};
	///���� ��������� ��������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* GetFreeOffsetsFile(void){return m_FilesCollection.empty()?NULL:dynamic_cast<SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile*>(m_FilesCollection[eusfFreeOffsets]);};
	///���� ������ ������ 
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxCashedFile* GetDataFile(void)
	{
		//return m_FilesCollection.empty()?NULL:dynamic_cast<SS::Interface::Core::NdxSE::NdxDataStorage::INdxCashedFile*>(m_FilesCollection[eusfData]);

		if(!m_pDataFile){
			m_pDataFile=m_FilesCollection.empty()?NULL:dynamic_cast<SS::Interface::Core::NdxSE::NdxDataStorage::INdxCashedFile*>(m_FilesCollection[eusfData]);
		}

		return m_pDataFile;
	};
	///������� ����� ���� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxCashedFile* CreateAndOpenNewDataFile(void);

	///��������� �� ���� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxCashedFile* m_pDataFile;
	///��������� �� ���� �������� �� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* m_pOffsetFile;

	///������ ��������� ��������
	vector<unsigned int> m_FreeOffsets;

	///����������� ��������� ������ ������������ ������ (��������� ����, �����������)
	unsigned int m_uiMaxWorkedDataSize;
	///������ ������������ ������ (��������� ����, �����������)
	unsigned int m_uiWorkedDataSize;
	///������������ ������ ������������� ����������� � ��������� ���� ������
	const unsigned int m_cuiMaxWorkedDataSize;

	///������ ����� ��� ������� ����� ����������
	const unsigned int m_cuiDataSizeToShrink;
	///������� ��������� ������ ��� ������� ����� ����������
	const unsigned int m_cuiDeletedDataPercentageToShrink;
	///����� ��������� ������
	unsigned int m_uiDeletedOffsetsNumber;
};

//--------------------------------------------------------------------//

}
}
}
}