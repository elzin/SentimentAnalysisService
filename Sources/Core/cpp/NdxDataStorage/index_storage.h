#pragma once

#include ".\files_collections.h"
#include ".\level_storage.h"

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

///��������� ���������
class CNdxStorage : public CFilesCollection, public virtual SS::Interface::Core::NdxSE::NdxDataStorage::INdxStorage
{
friend class CDataUnitFactory;
friend class CDataStorageFactory;

protected:
	CNdxStorage(CDataUnitFactory* pDataStorageFactory);
	virtual ~CNdxStorage(void);

	///���� ��������� �������
	enum EIndexStorageUnits
	{
		///������� ����� �����
		eisuEPTable,
		///��������� ������� ����������
		eisuTextImages,
		eisuTextImages_TextsOffsets,
		eisuTextImages_TextBlocksOffsets,
		eisuTextImages_TextBlocksContent,
		///��������� ���������� � ��������� ������� ���������
		eisuLevelsInfo,
		///��������� ��������� ��������
		eisuCoordinates,
		///������� ���� ����������
		eisuNormTable,
		///��������� ������ ��������
		eisuFreqUnit
	};

public:


	//-----------IBase
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	//-----------Eof-IBase

	//-----------INdxDataUnit
	///������� ���� ������ 
	void Create(const wchar_t* pszDataUnitName, const wchar_t* pszDataUnitExt);
	///��������� ���� � ������� ������
	bool Open(const wchar_t* pszPath);
	//-----------Eof-INdxDataUnit

	//-----------INdxStorage
	///���������� ��������� ����� ����� � ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxTableStorage* GetEntryPointsStorage(void);
	///���������� ��������� ������� ����������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* GetTextImagesStorage(void);
	///���������� ��������� ������� ����������
	void GetTextImagesStorages(SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile** ppNdxTextsOffsets, 
		SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile** ppNdxTextBlocksOffsets, 
		SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage** ppNdxTextBlocksContent);
	///���������� ��������� ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* GetCoordinateStorage(void);

	///��������� ���������� �� ������������� ������
	void AddLevelInfo(SS::Interface::Core::NdxSE::NdxDataStorage::SNdxLevelInfo* pNdxLevelInfo);
	///���������� ���������� �� ������������� ������ �� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::SNdxLevelInfo const* GetLevelInfo(unsigned int uiLevelNumber);
	///���������� ����� ������������ �������
	unsigned int GetLevelsNumber(void){return (unsigned int)m_NdxLevelInfoCollection.size();};
	//-----------Eof-INdxStorage

protected:
	///���������� ��� ����� ���������
	void GenerateFileName(unsigned int uiFileIndex, wstring* pszFileName);
	///������� ���� ���������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* CreateFile(unsigned int uiFileIndex);
	///������� ������� ����� �����
	void CreateEntryPointsStorage(SS::Interface::Core::NdxSE::NdxDataStorage::INdxTableStorage* pTableStorage);
	///��������� ���������� � ��������� �������
	void UpdateLevelsInfo(void);
	///��������� ���������� � ��������� �������
	void SaveLevelsInfo(void);

	///���������� � ��������� �������
	vector<SS::Interface::Core::NdxSE::NdxDataStorage::SNdxLevelInfo> m_NdxLevelInfoCollection;
};

//--------------------------------------------------------------------//

#pragma warning( default : 4250 )

}
}
}
}
