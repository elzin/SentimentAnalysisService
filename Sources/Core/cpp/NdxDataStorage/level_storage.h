#pragma once

#include ".\update_file.h"

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

///��������� ������ � ������������
class CLevelStorage : public CFilesCollectionEx, public SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage
{
friend class CDataUnitFactory;
 
protected:
	CLevelStorage(CDataUnitFactory* pDataStorageFactory);
	virtual ~CLevelStorage(void);

public:
	//-----------IBase
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	//-----------Eof-IBase

	//-----------INdxDataUnit
	///��������� ���� � ������� ������
	bool Open(const wchar_t* pszPath);
	//-----------Eof-INdxDataUnit

	//-----------INdxLevelStorage
	///����������� �� ��������� ������
	void	SeekPos(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pOffset, unsigned int uiOrigin);
	///���������� ������� � ��������� ������
	void	TellPos(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pOffset);

	//���������� ������ �� ��������� ������
	///�������� ������ �� ������ �������
	bool	StartRead(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pOffset, unsigned int* puiDataSizeInFile);
	///������ � �����
	void	Read(unsigned char* pBuffer, unsigned int uiSize);
	///����������� ������, ���������� ������ ������������
	void	StopRead(unsigned int* puiReadedDataSize);
	
	//���������� ���������� � ��������� ������
	///�������� ���������� ����������� ������
	void	StartCompleteDataAppend(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pOffset);
	///�������� ���������� ������������� ������
	void	StartUnCompleteDataAppend(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pOffset);
	///���������� ������ ������
	void	Append(unsigned char* pBuffer, unsigned int uiSize);
	///����������� ����������, ���������� ������ ������������
	void	StopAppend(unsigned int* puiAppendedDataSize);

	///���������� ������ ���������� ���������� ������
	unsigned int GetAppendedUnCompleteDataSize(void);
	///������������� � ���������� ���������� ������
	void	SeekPosInAppendedUnCompleteData(unsigned int uiOffset, unsigned int uiOrigin);
	///����� ����� ������ � ���������� ���������� ������
	void	WriteInAppendedUnCompleteData(unsigned char* pBuffer, unsigned int uiSize);

	///�������� �� ��������� ������
	void	Delete(SS::Interface::Core::NdxSE::NdxDataStorage::SCompositeOffset* pOffset);
	
	///��������� ����� ���������
	void	UpdateData(void);
	//-----------Eof-INdxLevelStorage

protected:
	///���������� ��� ����� ���������
	void GenerateFileName(unsigned int uiFileIndex, wstring* pszFileName);
	///������� ���� ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* CreateFile(unsigned int uiFileIndex);
	///���������� ���� ����������� ������ ���������
	CUpdateFile* GetUpdateFile(void);

	///������������ ������ ����� ���������
	const unsigned int	m_cuiMaxFileSize;
	///������������ ���������� ������ � ���������
	const unsigned int	m_cuiMaxFilesNumber;
};

//--------------------------------------------------------------------//

#pragma warning( default : 4250 )

}
}
}
}