#pragma once

#include ".\index_storage.h"

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

///��������� ��������� � ���������� �������� ����������
class CStatisticNdxStorage : public CNdxStorage, public SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorageWithStatistic
{
friend class CDataUnitFactory;
friend class CDataStorageFactory;

protected:
	CStatisticNdxStorage(CDataUnitFactory* pDataStorageFactory);
	virtual ~CStatisticNdxStorage(void);

public:
	//-----------IBase
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	//-----------Eof-IBase

	//-----------INdxDataUnit
	///������� ���� ������ 
	void Create(const wchar_t* pszDataUnitName, const wchar_t* pszDataUnitExt);
	//-----------Eof-INdxDataUnit

	//-----------INdxStorageWithStatistic
	///���������� ��������� ������ ��������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* GetIndexFrequencyStorage(void);
	///���������� ��������� ���� ���������� �������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* GetDocumentNormStorage(void);
	//-----------Eof-INdxStorageWithStatistic

protected:
	///���������� ��� ����� ���������
	void GenerateFileName(unsigned int uiFileIndex, wstring* pszFileName);
	///������� ���� ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* CreateFile(unsigned int uiFileIndex);
};

//--------------------------------------------------------------------//

#pragma warning( default : 4250 )

}
}
}
}
