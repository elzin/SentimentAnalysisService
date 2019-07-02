#pragma once

#include ".\const.h"
#include ".\console.h"
#include "..\ASDInterface\INdxDataStorage.h"
#include ".\data_unit.h"

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

///������� ���� ��������� ����
class CBasisFile : public CDataUnit, public virtual SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile
{
friend class CDataUnitFactory;
friend class CDataStorageFactory;

protected:
	CBasisFile(CDataUnitFactory* pDataStorageFactory);
	virtual ~CBasisFile(void);
	
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
	unsigned int TellPos(void);
	///����������� ����� � �����
	void Reserve(unsigned int uiSize);
	///���������������, ���������� ����
	bool Rename(const wchar_t* pszNewName, const wchar_t* pszPath);
	///��������� ����� ����� �� ����������
	bool	IsBad(void);
	///���������� ����� �����
	HANDLE	GetFileHandle(void){return m_FHandle;};
	//-----------Eof-INdxFile
	bool IsCDROM(VOID);

	///��������� ���������� ������� ������
	virtual void	View(void);
	///��������� ������� ������� � �����
	virtual void	ViewFilePos(void);


protected:
	///�������� �����
    HANDLE	m_FHandle;

};

//--------------------------------------------------------------------//

#pragma warning( default : 4250 )

}
}
}
}