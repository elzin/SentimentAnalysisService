#include "StdAfx.h"
#include ".\files_collections.h"
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

CFilesCollection::CFilesCollection(CDataUnitFactory* pDataStorageFactory)
:CDataUnit(pDataStorageFactory), 
m_uiMaxFilesNumber(cuiMaxFilesNumber)
{
	m_itCurrentFile = m_NullCollection.end();
}

CFilesCollection::~CFilesCollection(void)
{
	DeleteFiles();
}

bool CFilesCollection::Open(const wchar_t* pszPath)
{
	if(IsOpen()){
		TO_CONSOLE(L"FilesCollection already opened, close before!!!")
		return false;
	}

	m_szCurrentFilePath=pszPath;
	
	for(TFiles::iterator itCurrFile=m_FilesCollection.begin(); itCurrFile!=m_FilesCollection.end(); itCurrFile++){
		if((*itCurrFile)!=NULL){ 
			(*itCurrFile)->Open(m_szCurrentFilePath.c_str());
		}else{
			m_bIsOpen=false;
			return false;			
		}
	}
		
	//���������� ���� ���� ��� ���������� ����� ����� �����������
	m_bIsOpen=true;

	//��������������� �� ������ �����
	return MoveFirstFile();
}

bool CFilesCollection::Close(void)
{
	if(!IsOpen()) return true;

	for(TFiles::iterator itCurrFile=m_FilesCollection.begin(); itCurrFile!=m_FilesCollection.end(); itCurrFile++){
		if((*itCurrFile)!=NULL){ 
			(*itCurrFile)->Close();
		}
	}
	
	m_szCurrentFilePath.clear();
	m_bIsOpen=false;
	
	return true;
}

bool CFilesCollection::Flush(void)
{
	for(TFiles::iterator itCurrFile=m_FilesCollection.begin(); itCurrFile!=m_FilesCollection.end(); itCurrFile++){
		if((*itCurrFile)!=NULL){ 
			(*itCurrFile)->Flush();
		}
	}
	
	return true;
}

void CFilesCollection::Clear(void)
{
	for(TFiles::iterator itCurrFile=m_FilesCollection.begin(); itCurrFile!=m_FilesCollection.end(); itCurrFile++){
		if((*itCurrFile)!=NULL){ 
			(*itCurrFile)->Clear();
		}
	}
}

unsigned int CFilesCollection::GetDataUnitSize(void)
{
	unsigned int uiTotalSize=0;
	for(TFiles::iterator itCurrFile=m_FilesCollection.begin(); itCurrFile!=m_FilesCollection.end(); itCurrFile++){
		if((*itCurrFile)!=NULL){ 
			uiTotalSize+=(*itCurrFile)->GetDataUnitSize();
		}
	}
	
	return uiTotalSize;
}

void CFilesCollection::DeleteFiles(void)
{
	if(IsOpen()) Close();

	for(TFiles::iterator itCurrFile=m_FilesCollection.begin(); itCurrFile!=m_FilesCollection.end(); itCurrFile++){
		if((*itCurrFile)!=NULL){ 
			(*itCurrFile)->Release();
		}
	}

	m_FilesCollection.clear();
	m_itCurrentFile=m_NullCollection.end();
}

void CFilesCollection::GenerateFileName(unsigned int uiFileIndex, wstring* pszFileName)
{	
	wchar_t buf[20];
	_itow(uiFileIndex, buf, 10);

	pszFileName->assign(GetDataUnitName());
	pszFileName->append(L"_");
	pszFileName->append(buf);
}

INdxDataUnit* CFilesCollection::CreateFile(unsigned int uiFileIndex)
{
	//���������� ��� �����
	wstring szNewFileName;
	GenerateFileName((unsigned int)m_FilesCollection.size(), &szNewFileName);
	
	if(ISNULL(GetDataStorageFactory())) return NULL;

	//������� ����
	INdxFile* pFile=GetDataStorageFactory()->CreateBasisFile();
	pFile->Create(szNewFileName.c_str(), GetDataUnitExt());
	//������������� ��������� �������������
	pFile->SetBackupSettings(m_BackupSettings.m_CompressMode, m_BackupSettings.m_WriteMode);
	return pFile;
}

bool CFilesCollection::AddFile(void)
{	
	INdxDataUnit* pDataUnit=NULL;
	
	if(m_FilesCollection.size()>=m_uiMaxFilesNumber){
		TO_CONSOLE(L"Cann't add more files to collection size limit exceeded");
		return false;
	}

	//������� ����
	pDataUnit=CreateFile((unsigned int)m_FilesCollection.size());
	
	if(ISNULL(pDataUnit)) return false;

	//��������� ���� � ���������
	m_FilesCollection.push_back(pDataUnit);

	if(IsOpen()){
		//���� ��������� ����� �������, ��������� � ����		
		if(!pDataUnit->Open(m_szCurrentFilePath.c_str())){
			//�� ����������� ����������� ��� �� ���������
			pDataUnit->Release();
			m_FilesCollection.pop_back();
			return false;
		}
	}

	return true;
}

unsigned char CFilesCollection::GetCurrentFileIndex(void)
{
	if(m_FilesCollection.empty() || m_itCurrentFile==m_NullCollection.end()){
		return UC_EMPTY;
	}else{
		return (unsigned char)(m_itCurrentFile-m_FilesCollection.begin());
	}
}

bool CFilesCollection::MoveFirstFile(void)
{
	if(!m_FilesCollection.empty()){
		m_itCurrentFile=m_FilesCollection.begin();
		return true;
	}else{
		TO_CONSOLE(L"m_FilesCollection is empty");
		return false;
	}
}

bool CFilesCollection::MoveLastFile(void)
{
	if(!m_FilesCollection.empty()){
		m_itCurrentFile=--m_FilesCollection.end();
		return true;
	}else{
		TO_CONSOLE(L"m_FilesCollection is empty");
		return false;
	}
}

INdxDataUnit* CFilesCollection::GetCurrentFile(void)
{
	if(m_itCurrentFile!=m_NullCollection.end()){
		return (*m_itCurrentFile);
	}else{
		return NULL;
	}
}

bool CFilesCollection::MoveToFile(unsigned int uiFileIndex)
{
	if(uiFileIndex<m_FilesCollection.size()){
		m_itCurrentFile=(m_FilesCollection.begin()+uiFileIndex);
		return true;
	}else{
		TO_CONSOLE(L"Too big uiFileIndex");
		return false;
	}
}

//--------------------------------------------------------------------//

CFilesCollectionEx::CFilesCollectionEx(CDataUnitFactory* pDataStorageFactory)
:CFilesCollection(pDataStorageFactory)
{
}

CFilesCollectionEx::~CFilesCollectionEx(void)
{
}

bool CFilesCollectionEx::Open(const wchar_t* pszPath)
{
	m_szCurrentFilePath.assign(pszPath);

	INdxDataUnit* pDataUnit=NULL;

	//��������� ���� � ����������� ������ � ���������
	unsigned int uiDataUnitNumber=ReadDataUnitNumber();
	//���� ������ � ������ ��� ������� ���� �� ���� ���������
	if(!uiDataUnitNumber) uiDataUnitNumber++;

	//��������� ����� ���������
	unsigned int i=0;
	while(i<uiDataUnitNumber){
		//������� ����
		pDataUnit=CreateFile((unsigned int)m_FilesCollection.size());

		if(ISNULL(pDataUnit)) return false;

		//��������� ���� � ������ ������
		pDataUnit->Open(m_szCurrentFilePath.c_str());
		//���� ��� ��������� ��������� ���� � ���������
		m_FilesCollection.push_back(pDataUnit);
		i++;
	}
	
	//���������� ���� ��������
	m_bIsOpen=true;

	//��������������� �� ������ �����
	return MoveFirstFile();
}

bool CFilesCollectionEx::Close(void)
{
	//���� ��� �������
	if(!IsOpen()) return true;
	//���������� ���������� ������, ���� ����������
	//� ���� �� ��������� � ������� �����������
	if (ReadDataUnitNumber() != GetFilesNumber())
	{ WriteDataUnitNumber(); }
	//�����������
	return CFilesCollection::Close();
}

INdxFile* CFilesCollectionEx::GetCurrentFile(void)
{
	return dynamic_cast<INdxFile*>(CFilesCollection::GetCurrentFile());
}

unsigned int CFilesCollectionEx::ReadDataUnitNumber(void)
{
	//��������� ��������� � ����������� ������ � ���������
	unsigned int uiDataUnitNumber=0;
	INdxFile* pDataUnitNumber=GetDataStorageFactory()->CreateBasisFile();
	if(ISNULL(pDataUnitNumber)) return 0;
	pDataUnitNumber->Create(GetDataUnitName(), GetDataUnitExt());
	pDataUnitNumber->Open(m_szCurrentFilePath.c_str());
	pDataUnitNumber->SeekPos(0, SEEK_SET);
	pDataUnitNumber->Read((unsigned char*)&uiDataUnitNumber, sizeof(unsigned int));
	pDataUnitNumber->Close();
	pDataUnitNumber->Release();
	return uiDataUnitNumber;
}

void CFilesCollectionEx::WriteDataUnitNumber(void)
{
	//��������� ��������� � ����������� ������ � ���������
	unsigned int uiDataUnitNumber=GetFilesNumber();
	INdxFile* pDataUnitNumber=GetDataStorageFactory()->CreateBasisFile();
	if(ISNULL(pDataUnitNumber)) return;
	pDataUnitNumber->Create(GetDataUnitName(), GetDataUnitExt());
	pDataUnitNumber->Open(m_szCurrentFilePath.c_str());
	pDataUnitNumber->SeekPos(0, SEEK_SET);
	pDataUnitNumber->Write((unsigned char*)&uiDataUnitNumber, sizeof(unsigned int));
	pDataUnitNumber->Close();
	pDataUnitNumber->Release();
}

//--------------------------------------------------------------------//

}
}
}
}