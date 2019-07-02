#include "StdAfx.h"
#include ".\update_file.h"
#include ".\data_storages_factory.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxDataStorage
{

using namespace SS::Interface::Core::NdxSE::NdxDataStorage;

//--------------------------------------------------------------------//

CUpdateFile::CUpdateFile(CDataUnitFactory* pDataStorageFactory) :
	CFilesCollection(pDataStorageFactory),
	m_cuiMaxWorkedDataSize(cuiMaxWorkedBoundDataSize), m_pDataFile(NULL), m_pOffsetFile(NULL),
	m_cuiDeletedDataPercentageToShrink(200), m_cuiDataSizeToShrink(1000000000), m_uiDeletedOffsetsNumber(0),
	m_uiMaxWorkedDataSize(0), m_uiWorkedDataSize(0)
{
}

CUpdateFile::~CUpdateFile(void)
{
}

void CUpdateFile::ViewFilePos(void)
{
	if(ISNULL(GetOffsetsFile())) return;
	if(ISNULL(GetDataFile())) return;
	if(ISNULL(GetFreeOffsetsFile())) return;
	
	//GetOffsetsFile()->ViewFilePos();
	//GetDataFile()->ViewFilePos();
	//GetFreeOffsetsFile()->View();
}

bool CUpdateFile::Open(const wchar_t* pszPath)
{
	if(ISNULL(pszPath)) return false;

	//������� ���� ��������
	AddFile();
	//���� ��������� ��������
	AddFile();
	//������� ���� ������
	AddFile();
	
	return CFilesCollection::Open(pszPath);
}

bool CUpdateFile::Close(void)
{
	//����� ��������� ��������
	if(m_uiDeletedOffsetsNumber!=0) Shrink();
	
	//��������� ��� ������
	return CFilesCollection::Close();
}

void CUpdateFile::GenerateFileName(unsigned int uiFileIndex, wstring* pszFileName)
{
	pszFileName->assign(GetDataUnitName());
	switch((EUpdateStorageFiles)uiFileIndex){
	case eusfOffsets:
		pszFileName->append(L"_off");
		break;
	case eusfFreeOffsets:
		pszFileName->append(L"_of~");
		break;
	case eusfData:
		pszFileName->append(L"_d");
		break;
	default:
		pszFileName->append(L"_udf");
		TO_CONSOLE(L"Unknown index!!!");
		break;
	}
}

INdxDataUnit* CUpdateFile::CreateFile(unsigned int uiFileIndex)
{
	wstring szNewFileName;
	//���������� ��� �����
	GenerateFileName(uiFileIndex, &szNewFileName);

	if(ISNULL(GetDataStorageFactory())) return NULL;

	switch((EUpdateStorageFiles)uiFileIndex){
	case eusfOffsets: case eusfFreeOffsets:
		{
			//������� ����
			INdxFile* pFile=GetDataStorageFactory()->CreateBasisFile();
			pFile->Create(szNewFileName.c_str(), GetDataUnitExt());
			return pFile;
		}
		break;
	case eusfData:
		{
			//������� ����
			INdxCashedFile* pFile=GetDataStorageFactory()->CreateCashedFile();
			pFile->Create(szNewFileName.c_str(), GetDataUnitExt());
			return pFile;
		}
		break;
	default:
		TO_CONSOLE(L"Unknown index!!!");
		return NULL;
		break;
	}
}

bool CUpdateFile::Flush(void)
{
	if(ISNULL(GetOffsetsFile())) return false;
	if(ISNULL(GetDataFile())) return false;
	if(ISNULL(GetDataStorageFactory())) return false;
	
	unsigned int uiTotalOffsetsNumber=GetOffsetsFile()->GetDataUnitSize()/sizeof(SDataInfo);
	unsigned int uiDeletedDataPercentage=
		(unsigned int)(((float)m_uiDeletedOffsetsNumber)/(((float)uiTotalOffsetsNumber)/100));

	if(m_uiDeletedOffsetsNumber!=0 &&
		(m_cuiDataSizeToShrink<GetDataFile()->GetDataUnitSize() || 
		m_cuiDeletedDataPercentageToShrink<uiDeletedDataPercentage)){
		//���� ����������� ��������, ��������
		Shrink();
		ToConsole(L"-------------Shrink-------------");
		ToConsole(L"DataFileSize", GetDataFile()->GetDataUnitSize());
		ToConsole(L"DeletedDataPercentage", uiDeletedDataPercentage);
	}else{
		//���� �������� �� �����������, ���������� ������ � �����
		//���������� �� ���� ��������� ������ ����� ��������
		GetOffsetsFile()->Flush();
		GetDataFile()->Flush();
		//����� �� ���� ��������� ��������
		MoveDownFreeOffsets();
	}

	return true;
}

bool CUpdateFile::Shrink(void)
{
	//ToConsole(L"CUpdateFile::Shrink");
	//ToConsole(GetDataUnitName().c_str());
	
	if(ISNULL(GetOffsetsFile())) return false;
	if(ISNULL(GetDataFile())) return false;
	if(ISNULL(GetDataStorageFactory())) return false;
	
	try{
		if(!GetOffsetsFile()->GetDataUnitSize()){
			//���� �������� ��� �������� � �������
			Clear();
			return true;
		}
		
		//������� � ��������� ����� ���� ������
		INdxCashedFile* pNewDataFile=CreateAndOpenNewDataFile();

		//�������� ���� ��������
		INdxFile* pOffsetsFile=GetOffsetsFile();
		TDataInfoCollection DataInfoCollection;
		unsigned int uiMaxDataInfoCount=100000;
		unsigned int uiTemp=0;
		unsigned int uiAvailableDataInfoCount=0;
		unsigned int uiOffsetFileSize=pOffsetsFile->GetDataUnitSize();
		//� ����� ������ ����� �������� � �������� �� ��� ������
		unsigned int uiCurrentPos=0;
		pOffsetsFile->SeekPos(0, SEEK_SET);
		do{
			uiAvailableDataInfoCount=(uiOffsetFileSize-uiCurrentPos)/sizeof(SDataInfo);
			if(uiAvailableDataInfoCount>uiMaxDataInfoCount) uiAvailableDataInfoCount=uiMaxDataInfoCount;
			
			//����������� �����
			DataInfoCollection.resize(uiAvailableDataInfoCount);
			uiTemp=uiAvailableDataInfoCount*sizeof(SDataInfo);

			//������ ��������
			pOffsetsFile->Read((unsigned char*)&DataInfoCollection.front(), uiTemp);

			//��������
			ShrinkData(&DataInfoCollection, GetDataFile(), pNewDataFile);

			//������������ ����������� ���������� �� ���������
			pOffsetsFile->SeekPos(uiCurrentPos, SEEK_SET);
			pOffsetsFile->Write((unsigned char*)&DataInfoCollection.front(), uiTemp);
			
			//��������� �������
			uiCurrentPos=pOffsetsFile->TellPos();
		}while(uiCurrentPos<uiOffsetFileSize);

		//���������� �� ���� ��������� ������ ����� ��������
		GetOffsetsFile()->Flush();
		//����� �� ���� ��������� ��������
		MoveDownFreeOffsets();
		m_uiDeletedOffsetsNumber=0;
		//��������� ���� ������ ����� ��������������
		pNewDataFile->Flush();
		ReplaceDataFile(pNewDataFile);
		return true;
	
	}catch(...){
		//������� ����� ��� ������������� ������
		ERR_TO_CONSOLE(erTryCatch, L" ");
		throw;
	}
}

void CUpdateFile::ReplaceDataFile(INdxCashedFile* pNewDataFile)
{
	if(ISNULL(pNewDataFile)) return;

	GetDataFile()->Clear();
	GetDataFile()->Close();
	if(!pNewDataFile->Rename(GetDataFile()->GetDataUnitName(), m_szCurrentFilePath.c_str()))
		TO_CONSOLE(L"Rename failed!!!");
	
	GetDataFile()->Release();
	m_FilesCollection[eusfData]=pNewDataFile;
	m_pDataFile=pNewDataFile;
}

INdxCashedFile* CUpdateFile::CreateAndOpenNewDataFile(void)
{
	//������� � ��������� ����� ���� ��� ������
	wstring szNewDataFile(GetDataFile()->GetDataUnitName());
	szNewDataFile.append(L"~");
	INdxCashedFile* pNewDataFile=GetDataStorageFactory()->CreateCashedFile();
	pNewDataFile->Create(szNewDataFile.c_str(), GetDataUnitExt());
	unsigned int uiNewDataFileCurrCashSize=0;
	if(!pNewDataFile->Open(m_szCurrentFilePath.c_str())){
		pNewDataFile->Release();
		pNewDataFile=NULL;
		TO_CONSOLE(L"Cann't open new bound data file");
		ToConsole(szNewDataFile.c_str());
	}

	return pNewDataFile;
}

void CUpdateFile::ShrinkData(TDataInfoCollection* pDataInfoCollection, INdxCashedFile* pDataFile, INdxCashedFile* pNewDataFile)
{
	if(ISNULL(pDataInfoCollection)) return;
	if(ISNULL(pDataFile)) return;
	if(ISNULL(pNewDataFile)) return;
	
	TDataInfoCollection::iterator itDataInfo=pDataInfoCollection->begin();
	unsigned int uiNewDataOffset=EMPTY_OFFSET;
	unsigned char* pucData=NULL;
	while(itDataInfo!=pDataInfoCollection->end()){
		
		if(itDataInfo->m_uiDataOffset!=EMPTY_OFFSET){
			//���� �������� ��������, �������� � ���

			//����� � ���� �������� ����� �������� �� ������
			uiNewDataOffset=pNewDataFile->GetDataUnitSize();

			//��������� �� ������
			GetDataFile()->SeekPos(itDataInfo->m_uiDataOffset, SEEK_SET);
			
			//�������� ����� ��� ������
			pucData=(unsigned char*)malloc(itDataInfo->m_uiDataSize);

			//������ ������ �� ����� � �����
			GetDataFile()->Read(pucData, itDataInfo->m_uiDataSize);
			
			//��������� ������ � ����� ���� ������
			pNewDataFile->Append(pucData, itDataInfo->m_uiDataSize);
			
			//��������� �������� �� ������
			itDataInfo->m_uiDataOffset=uiNewDataOffset;
	
			//����������� ����� ��� ������
			if(pucData) free(pucData);
		}else{
			//��� ���������� ������ ���������� ������
			itDataInfo->m_uiDataSize=EMPTY_VALUE;
		}
		
		//��������� � ���������� ��������
		itDataInfo++;
	}
}

void	CUpdateFile::Clear(void)
{
	CFilesCollection::Clear();

	m_FreeOffsets.clear();
	m_uiMaxWorkedDataSize=0;
	m_uiWorkedDataSize=0;
}

void CUpdateFile::MoveUpFreeOffsets(void)
{
	if(ISNULL(GetFreeOffsetsFile())) return;
	INdxFile* pFreeOffsetsFile=GetFreeOffsetsFile();
	unsigned int uiFileSize=pFreeOffsetsFile->GetDataUnitSize();

	if(uiFileSize){
		pFreeOffsetsFile->SeekPos(0, SEEK_SET);

		pFreeOffsetsFile->Read((unsigned char*)&m_uiDeletedOffsetsNumber, sizeof(unsigned int));
		uiFileSize-=sizeof(unsigned int);
		
		if(uiFileSize!=0){
			//������ ��������� ��������� ��������
			m_FreeOffsets.resize(uiFileSize/sizeof(unsigned int));	
			pFreeOffsetsFile->Read((unsigned char*)&m_FreeOffsets.front(), uiFileSize);
		}
	}
}

void CUpdateFile::MoveDownFreeOffsets(void)
{
	if(ISNULL(GetFreeOffsetsFile())) return;
	INdxFile* pFreeOffsetsFile=GetFreeOffsetsFile();
	pFreeOffsetsFile->Clear();

	pFreeOffsetsFile->Write((unsigned char*)&m_uiDeletedOffsetsNumber, sizeof(unsigned int));

	//����� ��������� ��������� ��������
	if(m_FreeOffsets.size()){
		pFreeOffsetsFile->Write((unsigned char*)&m_FreeOffsets.front(), (unsigned int)(m_FreeOffsets.size()*sizeof(unsigned int)));
	}
	
	pFreeOffsetsFile->Flush();
}

void CUpdateFile::AddFreeOffset(unsigned int uiOffset)
{
	if(uiOffset!=EMPTY_OFFSET){
		m_FreeOffsets.push_back(uiOffset);
		//ToConsole(L"AddFreeOffset", (unsigned int)m_FreeOffsets.size());
	}
}

unsigned int CUpdateFile::SeekToFreeOffset(void)
{
	if(ISNULL(GetOffsetsFile())) return EMPTY_OFFSET;
	unsigned int uiOffset=EMPTY_OFFSET;

	if(m_FreeOffsets.empty()){
		//���� ����� �������� ������ � �����
		uiOffset=GetOffsetsFile()->GetDataUnitSize();
	}else{
		uiOffset=m_FreeOffsets.back();
		m_FreeOffsets.pop_back();
		//ToConsole(L"SeekToFreeOffset", (unsigned int)m_FreeOffsets.size());
	}

	GetOffsetsFile()->SeekPos(uiOffset, SEEK_SET);	
	return uiOffset;
}

void	CUpdateFile::StartRead(unsigned int uiOffset, unsigned int* puiDataSizeInFile)
{
	if(ISNULL(GetOffsetsFile())) return;
	if(ISNULL(GetDataFile())) return;
	if(ISNULL(puiDataSizeInFile)) return;

	unsigned int uiDataOffset=EMPTY_OFFSET;
	unsigned int uiReadedDataSize=EMPTY_VALUE;
	unsigned char ucStep=0;

	try{
	
		START_TICK(L"SeekPos");
		//��������� �� �������� ��������
		GetOffsetsFile()->SeekPos(uiOffset, SEEK_SET);
		ucStep++;

		//������ �������� �� ������ � ����� ������
		GetOffsetsFile()->Read((unsigned char*)&uiDataOffset, sizeof(unsigned int));
		ucStep++;

		//������ ������ ������ � ����� ������
		GetOffsetsFile()->Read((unsigned char*)&uiReadedDataSize, sizeof(unsigned int));
		ucStep++;
		STOP_TICK(L"SeekPos");
		
		//������ ������� ��� ������
		m_uiMaxWorkedDataSize=uiReadedDataSize;
		m_uiWorkedDataSize=0;
		*puiDataSizeInFile=uiReadedDataSize;
		ucStep++;
		
		START_TICK(L"DataFile_SeekPos");
		//��������� �� ������
		GetDataFile()->SeekPos(uiDataOffset, SEEK_SET);
		STOP_TICK(L"DataFile_SeekPos");
		ucStep++;
	
	}catch(...){
		wchar_t buf[500]=L"";
		switch(ucStep){
		case 0:
			wcscpy(buf, L"GetOffsetsFile()->SeekPos");
			break;
		case 1:
			wcscpy(buf, L"GetOffsetsFile()->Read1");
			break;
		case 2:
			wcscpy(buf, L"GetOffsetsFile()->Read2");
			break;
		case 3:
			wcscpy(buf, L"*puiDataSizeInFile=uiReadedDataSize");
			break;
		case 4:
			wcscpy(buf, L"GetDataFile()->SeekPos");
			break;
		default:
			wcscpy(buf, L"Unknown place");
			break;
		}
		ERR_TO_CONSOLE(erTryCatch, buf);
		ToConsole(GetDataUnitName());	
		//GetDataFile()->ViewFilePos();
		//GetOffsetsFile()->ViewFilePos();
		ToConsole(L"uiOffset", uiOffset);	
		ToConsole(L"uiDataOffset", uiDataOffset);	
		ToConsole(L"uiReadedDataSize", uiReadedDataSize);	
		ToConsole(L"m_uiMaxWorkedDataSize", m_uiMaxWorkedDataSize);	

		throw;
	}
}

void	CUpdateFile::Read(unsigned char* pData, unsigned int uiDataSize)
{
	if(ISNULL(GetDataFile())) return;
	if(ISNULL(pData)) return;
	if(ISNULL(uiDataSize)) return;

	if(ISNULL(m_uiMaxWorkedDataSize)){
		ERR_TO_CONSOLE(erFileIO, L"StartRead was not called!!!");
		return;
	}
	
	if(m_uiMaxWorkedDataSize<=m_uiWorkedDataSize){ 
		ERR_TO_CONSOLE(erFileIO, L"No more Data!!!");
		ToConsole(L"m_uiMaxWorkedDataSize", m_uiMaxWorkedDataSize);
		ToConsole(L"m_uiWorkedDataSize", m_uiWorkedDataSize);
		ToConsole(L"GetOffsetsFile()", GetOffsetsFile()->TellPos());
		ToConsole(L"GetDataFile()", GetDataFile()->TellPos());
		ToConsole(GetDataUnitName());
		return;
	}

	try{

		GetDataFile()->Read(pData, uiDataSize);
		m_uiWorkedDataSize+=uiDataSize;

	}catch(...){
		ERR_TO_CONSOLE(erTryCatch, GetDataUnitName());
		//GetDataFile()->ViewFilePos();
		ToConsole(pData, uiDataSize);	
		ToConsole(L"uiDataSize", uiDataSize);	
		ToConsole(L"m_uiMaxWorkedDataSize", m_uiMaxWorkedDataSize);	
		ToConsole(L"m_uiWorkedDataSize", m_uiWorkedDataSize);	
		throw;
	}

}

void	CUpdateFile::StopRead(unsigned int* puiReadedDataSize)
{
	if(ISNULL(puiReadedDataSize)) return;

	if(ISNULL(m_uiMaxWorkedDataSize)){
		ERR_TO_CONSOLE(erFileIO, L"StartRead was not called!!!");
		return;
	}
	
	*puiReadedDataSize=m_uiWorkedDataSize;

	//���������� �������
	m_uiMaxWorkedDataSize=0;
	m_uiWorkedDataSize=0;
}

void	CUpdateFile::StartAppend(unsigned int* puiOffset)
{
	if(ISNULL(GetOffsetsFile())) return;
	if(ISNULL(GetDataFile())) return;
	if(ISNULL(puiOffset)) return;

	m_uiMaxWorkedDataSize=m_cuiMaxWorkedDataSize;
	m_uiWorkedDataSize=0;
	unsigned int uiDataOffset=EMPTY_OFFSET;	
	
	try{

		//�������� ��������� �������� � ����� �������� � ��������������� �� ���
		(*puiOffset)=SeekToFreeOffset();

		//���������� �������� ������
		uiDataOffset=GetDataFile()->GetDataUnitSize();
		
		//������� �������� �� ������ � ���� ��������
		GetOffsetsFile()->Write((unsigned char*)&uiDataOffset, sizeof(unsigned int));

	}catch(...){
		ERR_TO_CONSOLE(erTryCatch, GetDataUnitName());
		//GetDataFile()->ViewFilePos();
		//GetOffsetsFile()->ViewFilePos();
		ToConsole(L"uiDataOffset", uiDataOffset);	
		ToConsole(L"puiOffset", *puiOffset);	
		throw;
	}

}

void	CUpdateFile::Append(unsigned char* pData, unsigned int uiDataSize)
{
	if(ISNULL(GetDataFile())) return;
	if(ISNULL(pData)) return;
	if(ISNULL(uiDataSize)) return;

	if(ISNULL(m_uiMaxWorkedDataSize)){
		ERR_TO_CONSOLE(erFileIO, L"StartAppend was not called!!!");
		return;
	}
	
	if(m_uiMaxWorkedDataSize<=m_uiWorkedDataSize){ 
		ERR_TO_CONSOLE(erFileIO, L"Too much appended data!!!");
		return;
	}

	try{
	
		GetDataFile()->Append(pData, uiDataSize);
		m_uiWorkedDataSize+=uiDataSize;

	}catch(...){
		ERR_TO_CONSOLE(erTryCatch, GetDataUnitName());
		//GetDataFile()->ViewFilePos();
		ToConsole(pData, uiDataSize);	
		ToConsole(L"uiDataSize", uiDataSize);	
		ToConsole(L"m_uiMaxWorkedDataSize", m_uiMaxWorkedDataSize);	
		ToConsole(L"m_uiWorkedDataSize", m_uiWorkedDataSize);	
		throw;
	}
}

void	CUpdateFile::StopAppend(unsigned int* puiAppendedDataSize)
{
	if(ISNULL(GetOffsetsFile())) return;
	if(ISNULL(puiAppendedDataSize)) return;

	if(ISNULL(m_uiMaxWorkedDataSize)){
		ERR_TO_CONSOLE(erFileIO, L"StartAppend was not called!!!");
		return;
	}
	try{

		//������� ������ ����������� ������ � ���� ��������
		GetOffsetsFile()->Write((unsigned char*)&m_uiWorkedDataSize, sizeof(unsigned int));
		*puiAppendedDataSize=m_uiWorkedDataSize;

		//���������� �������
		m_uiMaxWorkedDataSize=0;
		m_uiWorkedDataSize=0;

	}catch(...){
		//���������� �������
		m_uiMaxWorkedDataSize=0;
		m_uiWorkedDataSize=0;

		ERR_TO_CONSOLE(erTryCatch, GetDataUnitName());
		//GetOffsetsFile()->ViewFilePos();
		ToConsole(L"m_uiWorkedDataSize", m_uiWorkedDataSize);	
		throw;
	}
}

void CUpdateFile::DeleteData(unsigned int uiOffset)
{
	if(uiOffset==EMPTY_OFFSET) return;

	unsigned int uiDataOffset=EMPTY_OFFSET;
	unsigned int uiDataSize=EMPTY_VALUE;
	
	try{

		//�������� �������� �������� �� ������
		GetOffsetsFile()->SeekPos(uiOffset, SEEK_SET);

		//���������� ������ �������� �� ������ � �� ������
		GetOffsetsFile()->Write((unsigned char*)&uiDataOffset, sizeof(unsigned int));

		//��������� ������ ��������� ������
		GetOffsetsFile()->Read((unsigned char*)&uiDataSize, sizeof(unsigned int));
		++m_uiDeletedOffsetsNumber;

		//��������� �������� ��� ���������
		AddFreeOffset(uiOffset);

	}catch(...){
		ERR_TO_CONSOLE(erTryCatch, GetDataUnitName());
		//GetOffsetsFile()->ViewFilePos();
		ToConsole(L"uiOffset", uiOffset);	
		throw;
	}

}

void	CUpdateFile::SeekPosInData(unsigned int uiOffset, unsigned int uiOrigin)
{
	if(ISNULL(GetDataFile())) return;
	if(uiOffset==EMPTY_OFFSET){
		TO_CONSOLE(L"uiOffset==EMPTY_OFFSET!!!");
		return;
	}

	GetDataFile()->SeekPos(uiOffset, uiOrigin);
}

void	CUpdateFile::WriteData(unsigned char* pBuffer, unsigned int uiSize)
{
	if(ISNULL(GetDataFile())) return;
	if(ISNULL(pBuffer)) return;
	
	GetDataFile()->Write(pBuffer, uiSize);

}

//--------------------------------------------------------------------//

}
}
}
}