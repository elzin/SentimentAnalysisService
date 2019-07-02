#include "StdAfx.h"
#include ".\cashed_files.h"

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

CACashedFile::CACashedFile(CDataUnitFactory* pDataStorageFactory)
:CBasisFile(pDataStorageFactory), m_IndexModeFileCash(cuiCommonFileBufferSize, cuiMaxBufferNumber), 
m_uiCurrOffset(EMPTY_OFFSET), 
m_cuiCashMinSizeToFlush(cuiCashMinSizeToFlush)
{
}

CACashedFile::~CACashedFile(void)
{
}

HRESULT CACashedFile::QueryInterface(REFIID pIID, void** pBase)
{
	if(pIID==IID_NdxFile){
		*pBase=(INdxFile*)this;
	}else if(pIID==IID_NdxCashedFile){
		*pBase=(INdxCashedFile*)this;
	}else{
		*pBase=NULL;
	}

	return S_OK;
}

bool CACashedFile::Open(const wchar_t* pszPath)
{
	if(CBasisFile::Open(pszPath)){
		m_IndexModeFileCash.Init(this);
		m_IndexModeFileCash.SetFileOffset(CBasisFile::GetDataUnitSize());
		return true;
	}else{
		return false;
	}
}

bool CACashedFile::Close(void)
{
	//���������� ��� ��� ��������
	m_IndexModeFileCash.FlushToFile();
	m_uiCurrOffset=EMPTY_OFFSET;

	return CBasisFile::Close();
}

bool CACashedFile::Flush(void)
{
	if(m_IndexModeFileCash.GetFilledSize()>=m_cuiCashMinSizeToFlush){
		//���� ��� ������ ������ ������, ���������� ��� � ����
		m_IndexModeFileCash.FlushToFile();
	}

	//������ ��� �� ����
	return CBasisFile::Flush();
}

void CACashedFile::Append(unsigned char* pBuffer, unsigned int uiSize)
{
	//��������� ������ � ���
	m_IndexModeFileCash.AddData(pBuffer, uiSize);
	m_uiCurrOffset=m_IndexModeFileCash.GetFileOffset()+m_IndexModeFileCash.TellPos();
}

void	CACashedFile::Read(unsigned char* pBuffer, unsigned int uiSize)
{
	//��������� � ����� ����� ����� ��������� ������������� ������
	if(m_IndexModeFileCash.GetFileOffset()>TellPos()){
		//���� ������� ������� ��������� � �����

		//���������� ������� ������ ���� � �����
		unsigned int uiAvailableFileSize=m_IndexModeFileCash.GetFileOffset()-TellPos();
		
		if(uiAvailableFileSize>=uiSize){
			//���� ������ ����������, ������ �� �� �����
			CBasisFile::Read(pBuffer, uiSize);
			//������� ������� �������
			m_uiCurrOffset+=uiSize;
		}else{
			//���� ������ �� ����������, ������ �� �� �����, � ����� �� ����
			CBasisFile::Read(pBuffer, uiAvailableFileSize);

			//������ ��������� �� ����
			m_IndexModeFileCash.SeekPos(0, SEEK_SET);
			m_IndexModeFileCash.Read(pBuffer+uiAvailableFileSize, uiSize-uiAvailableFileSize);

			//������� ������� �������
			m_uiCurrOffset=m_IndexModeFileCash.GetFileOffset()+m_IndexModeFileCash.TellPos();
		}

	}else{
		//���� ������� ������� ��������� � ����
		//������ � ����
		m_IndexModeFileCash.Read(pBuffer, uiSize);
		//������� ������� �������
		m_uiCurrOffset=m_IndexModeFileCash.GetFileOffset()+m_IndexModeFileCash.TellPos();
	}
}

void CACashedFile::Write(unsigned char* pBuffer, unsigned int uiSize)
{
	//��������� � ����� ����� ����� ��������� ������������� ������
	if(m_IndexModeFileCash.GetFileOffset()>TellPos()){
		//���� ������� ������� ��������� � �����

		//���������� ������� ������ ���� � �����
		unsigned int uiAvailableFileSize=m_IndexModeFileCash.GetFileOffset()-TellPos();
		
		if(uiAvailableFileSize>=uiSize){
			//���� ������ ����������, ����� ����� � ����
			CBasisFile::Write(pBuffer, uiSize);
			//������� ������� �������
			m_uiCurrOffset+=uiSize;
		}else{
			//���� ������ �� ����������, ����� � ���� �����, � ����� � ���
			CBasisFile::Write(pBuffer, uiAvailableFileSize);
			//����� ��������� � ���
			m_IndexModeFileCash.SeekPos(0, SEEK_SET);
			m_IndexModeFileCash.Write(pBuffer+uiAvailableFileSize, uiSize-uiAvailableFileSize);
			//������� ������� �������
			m_uiCurrOffset=m_IndexModeFileCash.GetFileOffset()+m_IndexModeFileCash.TellPos();
		}
	}else{
		//���� ������� ������� ��������� � ����
		//����� � ���
		m_IndexModeFileCash.Write(pBuffer, uiSize);
		//������� ������� �������
		m_uiCurrOffset=m_IndexModeFileCash.GetFileOffset()+m_IndexModeFileCash.TellPos();
	}
}

void	CACashedFile::SeekPos(unsigned int uiOffset, unsigned int uiOrigin)
{
	if(uiOffset==EMPTY_OFFSET){
		ERR_TO_CONSOLE(erFileIO, L"Invalid offset!!!");
		ToConsole(L"uiOrigin", uiOrigin);
		ToConsole(GetDataUnitName());
		return;
	}

	switch(uiOrigin){
	case SEEK_SET:
		//���������� ���������������� �� ������ �����
		if(uiOffset>=m_IndexModeFileCash.GetFileOffset()){
			//���� ��������� ������� ��������� � ����, ��������������� � ���	
			m_IndexModeFileCash.SeekPos(uiOffset-m_IndexModeFileCash.GetFileOffset(), SEEK_SET);
		}else{
			//���� ��������� ������� ��������� � �����, ��������������� � ���	
			CBasisFile::SeekPos(uiOffset, SEEK_SET);
		}

		//��������� ������� ������� � �����
		m_uiCurrOffset=uiOffset;
		break;
	case SEEK_CUR:
		//������������� ���������������� �� ������� ������� � �����
		if(m_uiCurrOffset!=EMPTY_OFFSET){
			//���� ������� ������� � ����� �������...
			//���������� ������� ��������� ������� �� ������ �����
			unsigned int uiNewOffset=(unsigned int)((int)m_uiCurrOffset+(int)uiOffset);

			if(uiNewOffset>=m_IndexModeFileCash.GetFileOffset()){
				//���� ��������� ������� ��������� � ����, ��������������� � ���	
				//(�������� ����� �� ���������� ��� ��� �������� �������������)
				m_IndexModeFileCash.SeekPos(uiOffset, SEEK_CUR);
			}else{
				//���� ��������� ������� ��������� � �����, ��������������� � ���	
				CBasisFile::SeekPos(uiOffset, SEEK_CUR);
			}

			//��������� ������� ������� � �����
			m_uiCurrOffset=uiNewOffset;
		}
		break;
	case SEEK_END:
		ERR_TO_CONSOLE(erFileIO, L"Not supported");
		break;
	default:
		ERR_TO_CONSOLE(erFileIO, L"Undefined origin!!!");
		break;
	}
}

void CACashedFile::Clear(void)
{
	CBasisFile::Clear();
	m_IndexModeFileCash.Clear();
	m_IndexModeFileCash.SetFileOffset(0);
	m_uiCurrOffset=0;
}

unsigned int CACashedFile::GetDataUnitSize()
{
	return (m_IndexModeFileCash.GetFileOffset()+m_IndexModeFileCash.GetFilledSize());
}

void	CACashedFile::FlushFilledBuffers(void)
{
	//���������� ���������� ������ ����
	m_IndexModeFileCash.FlushFilledBuffersToFile();
}

void CACashedFile::View(void)
{
	m_IndexModeFileCash.View();
	CBasisFile::View();
}

void CACashedFile::ViewFilePos(void)
{
	m_IndexModeFileCash.View();
	CBasisFile::View();
}

//--------------------------------------------------------------------//

CRACashedFile::CRACashedFile(CDataUnitFactory* pDataStorageFactory)
:CACashedFile(pDataStorageFactory), m_ReadFileCash(cuiReadFileBufferSize)
{
}

CRACashedFile::~CRACashedFile(void)
{
}

bool	CRACashedFile::Open(const wchar_t* pszPath)
{
	if(CACashedFile::Open(pszPath)){
		m_ReadFileCash.Init(this);
		m_ReadFileCash.SetFileOffset(0);
		return true;
	}else{
		return false;
	}
}

bool	CRACashedFile::Close(void)
{
	m_ReadFileCash.Clear();
	return CACashedFile::Close();
}

//void	CRACashedFile::Read(unsigned char* pBuffer, unsigned int uiSize)
//{
//	//��������� � ����� ����� ����� ��������� ������������� ������
//	if(m_IndexModeFileCash.GetFileOffset()>TellPos()){
//		//���� ������� ������� ��������� � �����
//
//		//���������� ������� ������ ���� � �����
//		unsigned int uiAvailableFileSize=CBasisFile::GetDataUnitSize()-TellPos();
//		
//		if(uiAvailableFileSize>=uiSize){
//			//���� ������ ����������, ������ �� �� �����
//			ReadFromCash(pBuffer, uiSize);
//			//������� ������� �������
//			m_uiCurrOffset+=uiSize;
//		}else{
//			//���� ������ �� ����������, ������ �� �� �����, � ����� �� ���� ����������
//			ReadFromCash(pBuffer, uiAvailableFileSize);
//			//������ ��������� �� ���� ����������
//			m_IndexModeFileCash.SeekPos(0, SEEK_SET);
//			m_IndexModeFileCash.Read(pBuffer+uiAvailableFileSize, uiSize-uiAvailableFileSize);
//			//������� ������� �������
//			m_uiCurrOffset=m_IndexModeFileCash.GetFileOffset()+m_IndexModeFileCash.TellPos();
//		}
//	}else{
//		//���� ������� ������� ��������� � ��������� ����
//		//������ �� ����
//		m_IndexModeFileCash.Read(pBuffer, uiSize);
//		//������� ������� �������
//		m_uiCurrOffset=m_IndexModeFileCash.GetFileOffset()+m_IndexModeFileCash.TellPos();
//	}
//}
//
//void CRACashedFile::ReadFromCash(unsigned char* pBuffer, unsigned int uiSize)
//{
//	//������ �� ����
//	unsigned int uiDataSizeInCash=0;
//	unsigned int uiWorkedSize=0;
//	unsigned char* pucCurrBufPos=pBuffer;
//	do{
//		//�������� ������ ������ � ����
//		uiDataSizeInCash=m_ReadFileCash.GetFilledSize()-m_ReadFileCash.TellPos();
//		
//		if(uiWorkedSize+uiDataSizeInCash<uiSize){
//			//���� � ���� ��������� ������, ��� ����� ������
//			//������ ������� ������� ���� � ����
//			if(uiDataSizeInCash){
//				m_ReadFileCash.Read(pucCurrBufPos, uiDataSizeInCash);
//				pucCurrBufPos+=uiDataSizeInCash;
//				uiWorkedSize+=uiDataSizeInCash;
//			}
//			
//			//���������� � ����� � ���������� ������
//			m_ReadFileCash.SetFileOffset(m_ReadFileCash.GetFileOffset()+m_ReadFileCash.GetFilledSize());
//			m_ReadFileCash.FillFromFile();
//		}else{
//			//���� � ���� ��������� ����������, ����� ����� ���� ��������� �����, ������
//			m_ReadFileCash.Read(pucCurrBufPos, uiSize-uiWorkedSize);
//			//���������� ������ ���� �����
//			uiWorkedSize=uiSize;
//		}
//	}while(uiWorkedSize<uiSize);
//}
//
//void	CRACashedFile::SeekPos(unsigned int uiOffset, unsigned int uiOrigin)
//{
//	if(uiOffset==EMPTY_OFFSET){
//		TO_CONSOLE(L"Invalid offset!!!");
//		ToConsole(L"uiOrigin", uiOrigin);
//		ToConsole(GetDataUnitName());
//		return;
//	}
//
//	switch(uiOrigin){
//	case SEEK_SET:
//
//		//���������� ���������������� �� ������ �����
//		if(uiOffset>=m_IndexModeFileCash.GetFileOffset()){
//			//���� ��������� ������� ��������� � ����, ��������������� � ���	
//			m_IndexModeFileCash.SeekPos(uiOffset-m_IndexModeFileCash.GetFileOffset(), SEEK_SET);
//		}else{
//			//���� ��������� ������� ��������� � �����, ��������������� � ���	
//			CBasisFile::SeekPos(uiOffset, SEEK_SET);
//			//���� ������� ���� ������
//			m_ReadFileCash.SetFileOffset(uiOffset);
//			//��������� ��� ������ ������� �� �����
//			m_ReadFileCash.FillFromFile();
//		}
//
//		//��������� ������� ������� � �����
//		m_uiCurrOffset=uiOffset;
//		break;
//	case SEEK_CUR:
//		//������������� ���������������� �� ������� ������� � �����
//		if(m_uiCurrOffset!=EMPTY_OFFSET){
//			//���� ������� ������� � ����� �������...
//			//���������� ������� ��������� ������� �� ������ �����
//			unsigned int uiNewOffset=(unsigned int)((int)m_uiCurrOffset+(int)uiOffset);
//
//			if(uiNewOffset>=m_IndexModeFileCash.GetFileOffset()){
//				//���� ��������� ������� ��������� � ����, ��������������� � ���	
//				//(�������� ����� �� ���������� ��� ��� �������� �������������)
//				m_IndexModeFileCash.SeekPos(uiOffset, SEEK_CUR);
//			}else{
//				//���� ��������� ������� ��������� � �����, ��������������� � ���	
//				CBasisFile::SeekPos(uiOffset, SEEK_CUR);
//				//���� ������� ���� ������
//				m_ReadFileCash.SetFileOffset(uiNewOffset);
//				//��������� ��� ������ ������� �� �����
//				m_ReadFileCash.FillFromFile();
//			}
//
//			//��������� ������� ������� � �����
//			m_uiCurrOffset=uiNewOffset;
//		}
//		break;
//	case SEEK_END:
//		TO_CONSOLE(L"Not supported");
//		break;
//	default:
//		TO_CONSOLE(L"Undefined origin!!!");
//		break;
//	}
//}

//--------------------------------------------------------------------//

}
}
}
}
