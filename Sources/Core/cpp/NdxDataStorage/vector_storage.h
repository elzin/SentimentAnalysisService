#pragma once

#include ".\files_collections.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxDataStorage
{

//�������� ������� � ������������
#pragma warning( disable : 4250 )

//--------------------------------------------------------------------//

///�������� ������ �� ���������� �������, ������������ ������������ ������ � ���������� � �����
class CVectorStorage : public CFilesCollection, 
	public SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage
{
friend class CDataUnitFactory;
friend class CDataStorageFactory;

protected:
	CVectorStorage(CDataUnitFactory* pDataStorageFactory);
	virtual ~CVectorStorage(void);

	///���� ������ ���������
	enum EVectorStorageFiles
	{
		///��������� ����
		evsfIndex,
		///���� ������
		evsfData
	};

public:
	//-----------IBase
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	//-----------Eof-IBase

	//-----------INdxDataUnit
	///��������� ���� ������ � ������� ������
	bool Open(const wchar_t* pszPath);
	//-----------Eof-INdxDataUnit

	//---������ ������
	///��������� �� ������ ������, ���������� �� ������
	void	MoveToAndGetDataSize(unsigned int uiIndex, unsigned int* puiDataSizeInFile);
	///������ ��� ������ ����������� �� �������
	void	ReadWholeData(unsigned char* pData, unsigned int uiDataSize);
	///������ ����� ������ ����������� �� �������
	void	ReadDataChunk(unsigned char* pData, unsigned int uiDataSize);
	///������� ������ ������ ����������� �� �������, �������� ��������� �� ������
	void	SeekInData(unsigned int uiOffset);
	

	//---���������� ������
	///��������� ������ � ���������, ���������� ������, �� �������� ����� ��������� ������
	void	AppendWholeData(unsigned char* pData, unsigned int uiDataSize, unsigned int* puiIndex);
	///��������� ����� ������, ��������� �������� ��������� ����������
	void	AppendDataChunk(unsigned char* pData, unsigned int uiDataSize);
	///��������� �������� ��������� ����������, ���������� ������, �� �������� ����� ��������� ������
	void	AppendDataChunkComplete(unsigned int* puiIndex);
	
	//---�������� ������
	///������� ������ �� �������
	void	Delete(unsigned int uiIndex);
	///��������� ������� �� ������ �� �������
	bool	IsDeleted(unsigned int uiIndex);

	///���������� ���������� ��������
	unsigned int GetIndexesNumber(void);

protected:
	///���������� ��� ����� ���������
	void GenerateFileName(unsigned int uiFileIndex, wstring* pszFileName);
	///������� ���� ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* CreateFile(unsigned int uiFileIndex);
	///���������� ��������� ���� 
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* GetIndexFile(void){return m_FilesCollection.empty()?NULL:dynamic_cast<SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile*>(m_FilesCollection[evsfIndex]);};
	///���������� ���� ������
	CFilesCollectionEx* GetDataFile(void){return m_FilesCollection.empty()?NULL:dynamic_cast<CFilesCollectionEx*>(m_FilesCollection[evsfData]);};

	///��������� ������� ����� � ��������� �����
	struct SDataInfo
	{
		///�������� � �����	
		unsigned int m_uiOffsetInFile;
		///������ ������
		unsigned int m_uiDataSize;
		///������ �����
		unsigned char m_ucFileIndex;
		///���� �������� ������
		bool m_bDeleted;
		
		///���������� ���� ���������
		void Reset(void)
		{
			m_uiOffsetInFile=EMPTY_OFFSET;
			m_uiDataSize=0;
			m_ucFileIndex=UC_EMPTY;
			m_bDeleted=false;
		};

		///��������� �� �������
		bool IsEmpty(void)
		{
			if(	m_uiOffsetInFile==EMPTY_OFFSET &&
				m_uiDataSize==0 && 
				m_ucFileIndex==UC_EMPTY &&
				m_bDeleted==false) 
				return true;
			else
				return false;
		};
	};

	///������� ������
	SDataInfo m_CurrDataInfo;
	///������� ���������� �� ����������� ������
	SDataInfo m_CurrAppendedDataInfo;
	///������� �������� ������ ������
	unsigned int m_uiCurrOffsetInData;
	///������� ������ ����������� ������
	unsigned int m_uiCurrDataSize;
	///������������ ������ ������ ����� ������
	unsigned int m_uiMaxDataFileSize;
	///������������ ���������� ������ ������ � ���������
	unsigned int m_uiMaxDataFilesNumber;

};

//--------------------------------------------------------------------//

#pragma warning( default : 4250 )

}
}
}
}