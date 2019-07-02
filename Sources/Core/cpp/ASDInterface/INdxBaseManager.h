#pragma once
#include "..\ASCInterface\IBaseManager.h"
#include "INdxDataStorage.h"

//--------------------------------------------------------------------//

// {BE8CB1C6-4F37-46c6-AAAD-F5D771B9779C}
static const GUID IID_NdxBaseManager = 
{ 0xbe8cb1c6, 0x4f37, 0x46c6, { 0xaa, 0xad, 0xf5, 0xd7, 0x71, 0xb9, 0x77, 0x9c } };


//--------------------------------------------------------------------//

namespace SS
{
namespace Interface
{
namespace Core
{
namespace NdxSE
{

//--------------------------------------------------------------------//

///����� �������� ����������� �������� � ������ ���� ������������������ ����������
namespace ObligatoryStorageNames
{
	///��������� ���������� � ����������������� �������
	const wchar_t TextsInfoStorage[]=L"tinf";
	///��������� ����� � ������� � ���� ������ �����
	const wchar_t TextsPathTreeStorage[]=L"tpinf";
	///��������� ����� ������� � ���� ������� DBMS
	const wchar_t TextsFieldsStorage[]=L"tfld";
}

///���� �������� �������� � ������ ��������� ����
enum ENdxStorageTypes
{
	///��������� ������ �������
	ensTextsIndex,
	///��������� ������ ������� � ��������� ����������
	ensTextsIndexWithStatistic,
	///��������� ������ ���������� �������
	ensHeadersIndex,
	///��������� ������ ������� �������
	ensAthorsIndex,
	///��������� ������ ��� �������
	ensDataIndex,
	///��������� ��������� ����������� ����������������� �������
	ensTextsBinary,
	///��������� ���������� � ����������������� �������
	ensTextsInfo,
	///��������� ����� � ������� � ���� ������ �����
	ensTextsPathTree,
	///��������� ����� ������� � ���� ������� DBMS
	ensTextsFields,
};

//--------------------------------------------------------------------//

///���� ������������ ��������� ��������
enum ENdxStorageConfig
{
	///�������������� ��� �������� �� ���������� ���������
	escUndefined,
	///�������������� �� ���. ������� �����������
	escAbsSentence,
	///�������������� �� ���. ������� ����������� � ��������� ������� ���� 
	escAbsSentence_WC,
	///�������������� �� ������� ������� � ��������� ������� ����
	escText_WC,
	///�������������� �� ������� ������� � ��������� ������� ����, �������������� ��� ������� �������
	escText_WC_ForBig,
	///�������������� �� ������� ������� � ��������� ������� ����, �������������� ��� ��������� �������
	escText_WC_ForSmall,
	///�������������� �� ������� �������
	escText,
	escText_WC_Huge,
};

//--------------------------------------------------------------------//

///��������� ���������� ���������� ������ ���������� ���������� NdxSE
class INdxBaseManager : public SS::Interface::Core::ResourceManagers::IBaseManager
{
public:
	///���������� ������������� ������� ������ ��������� ����,
	///���� � ������� �� ��������� ������������� ������, ���������� ��������
	///���� ���������, ��� ��� ��� ��������� ��� ���� ������� ������
	virtual unsigned int GetCurrentSessionID(void) = 0;

	///���������� ��������� ��������� ����
	virtual void ResetNdxBaseStructure(void) = 0;
	///��������� ��������� � ��������� ����
	virtual void AddNdxBaseUnit(const wchar_t* wszStorageName, ENdxStorageConfig StorageConfig) = 0;
	///���������� ��������� ��������� ���� �� �����
	virtual SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* 
		GetNdxBaseUnit(const wchar_t* wszStorageName) = 0;
	//��� ������ �� ��������� ������ ����
	///���������� ������ � ��������� ��������� ��������� ����
	virtual SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* 
		GetFirstNdxBaseUnit(void) = 0;
	///���������� ��������� �� ������� � ��������� ��������� ��������� ����, 
	//��� ���������� ����� ��� ��� ������ GetFirstNdxBaseUnit ������ NULL
	virtual SS::Interface::Core::NdxSE::NdxDataStorage::INdxDataUnit* 
		GetNextNdxBaseUnit(void) = 0;
};

//--------------------------------------------------------------------//

}
}
}
}