#pragma once

#include "..\ASCInterface\IInterface.h"
#include "..\ASCInterface\IDBMS.h"

//--------------------------------------------------------------------//

// {3BFF5350-43FE-4cdc-BE3B-AFBA7E313F6A}
static const GUID IID_NdxDataUnit = 
{ 0x3bff5350, 0x43fe, 0x4cdc, { 0xbe, 0x3b, 0xaf, 0xba, 0x7e, 0x31, 0x3f, 0x6a } };
// {9347830D-AC34-494a-96CC-77612F37D0FD}
static const GUID IID_NdxFile = 
{ 0x9347830d, 0xac34, 0x494a, { 0x96, 0xcc, 0x77, 0x61, 0x2f, 0x37, 0xd0, 0xfd } };
// {688048D0-6852-44f8-B65D-69973100E22D}
static const GUID IID_NdxCashedFile = 
{ 0x688048d0, 0x6852, 0x44f8, { 0xb6, 0x5d, 0x69, 0x97, 0x31, 0x0, 0xe2, 0x2d } };
// {3E8E2375-D5F8-4d2e-8596-273A356C987A}
static const GUID IID_NdxLevelStorage = 
{ 0x3e8e2375, 0xd5f8, 0x4d2e, { 0x85, 0x96, 0x27, 0x3a, 0x35, 0x6c, 0x98, 0x7a } };
// {184C06D1-01F3-41a6-99AF-48A661C7B63E}
static const GUID IID_NdxStorage = 
{ 0x184c06d1, 0x1f3, 0x41a6, { 0x99, 0xaf, 0x48, 0xa6, 0x61, 0xc7, 0xb6, 0x3e } };
// {7B0FD902-A48A-471d-A0FA-EF5ED4509CEC}
static const GUID IID_NdxVectorStorage = 
{ 0x7b0fd902, 0xa48a, 0x471d, { 0xa0, 0xfa, 0xef, 0x5e, 0xd4, 0x50, 0x9c, 0xec } };
// {85974587-0B3C-4e3e-8AEF-71EFE7269E1B}
static const GUID IID_NdxTableStorage = 
{ 0x85974587, 0xb3c, 0x4e3e, { 0x8a, 0xef, 0x71, 0xef, 0xe7, 0x26, 0x9e, 0x1b } };

// {CB80571B-F1C3-4987-81DF-E10D91C65AD2}
static const GUID IID_NdxDataStorageFactory = 
{ 0xcb80571b, 0xf1c3, 0x4987, { 0x81, 0xdf, 0xe1, 0xd, 0x91, 0xc6, 0x5a, 0xd2 } };
// {4864DAD8-7C86-495a-AF37-25B4E2E7DAF0}
static const GUID CLSID_NdxDataStorageFactory  = 
{ 0x4864dad8, 0x7c86, 0x495a, { 0xaf, 0x37, 0x25, 0xb4, 0xe2, 0xe7, 0xda, 0xf0 } };

//--------------------------------------------------------------------//

namespace SS
{
namespace Interface
{
namespace Core
{
namespace NdxSE
{
namespace NdxDataStorage
{

//--------------------------------------------------------------------//

///��������� �������������
struct SBackupSettings
{
	SBackupSettings(void):m_CompressMode(cmCompressible), m_WriteMode(wmRandom){};

	///����� ������ ����� ��� ������
	enum ECompressMode
	{
		///���� ����� �������
		cmCompressible,
		///���� �����������
		cmUncompressible,
	} m_CompressMode;
	
	///����� ������ � ����
	enum EWriteMode
	{
		///��������
		wmRandom,
		///���������� � �����
		wmAppend,
	} m_WriteMode;
	
	void ToString(std::wstring& wsValue)
	{
		wsValue.assign(L"_");

		if(m_WriteMode==wmRandom)
			wsValue.append(L"r");
		else if(m_WriteMode==wmAppend)
			wsValue.append(L"a");

		if(m_CompressMode==cmCompressible)
			wsValue.append(L"c");
		else if(m_CompressMode==cmUncompressible)
			wsValue.append(L"u");
	};
};

//--------------------------------------------------------------------//

///��������� ������ � ������� ������ ������ ��������� ����
class INdxDataUnit : public virtual SS::Interface::IBase
{
public:				
	///������� ���� ������ 
	virtual void Create(const wchar_t* pszDataUnitName, const wchar_t* pszDataUnitExt) = 0;
	///��������� ���� ������ � ������� ������
	virtual bool Open(const wchar_t* pszPath) = 0;
	///��������� ���� ������ 
	virtual bool Close(void) = 0;
	///���������� ���� ������ 
	virtual bool Flush(void) = 0;
	///�������  ���� ������ 
	virtual void Clear(void) = 0;
	///���������� ������ ����� ������ 
	virtual unsigned int GetDataUnitSize(void) = 0;
	///��������� ������ �� ���� ������ 
	virtual bool IsOpen(void) = 0;
	///���������� ��� ����� ������ 
	virtual const wchar_t*	GetDataUnitName(void) = 0;
	///���������� ���������� ����� ������ 
	virtual const wchar_t* GetDataUnitExt(void) = 0;
	///������������� ��������� �������������
	virtual void SetBackupSettings(SBackupSettings::ECompressMode CompressMode, SBackupSettings::EWriteMode WriteMode) = 0;
};

//--------------------------------------------------------------------//


///��������� ������ � ������� ��������� ������
class INdxFile : public virtual INdxDataUnit
{
public:				
	///������ �� ����� �� ������� �������
	virtual void Read(unsigned char* pBuffer, unsigned int uiSize) = 0;
	///����� � ���� �� ������� �������
	virtual void Write(unsigned char* pBuffer, unsigned int uiSize) = 0;
	///��������� � �����
	virtual void Append(unsigned char* pBuffer, unsigned int uiSize) = 0;
	///�������� ������� ������� � �����
	virtual void SeekPos(unsigned int uiOffset, unsigned int uiOrigin) = 0;
	///���������� ������� ������� � �����
	virtual unsigned int TellPos(void) = 0;
	///����������� ����� � �����
	virtual void Reserve(unsigned int uiSize) = 0;
	///���������������, ���������� ����
	virtual bool Rename(const wchar_t* pszNewName, const wchar_t* pszPath) = 0;
	///��������� ����� ����� �� ����������
	virtual bool IsBad(void) = 0;
	///���������� ����� �����
	virtual HANDLE	GetFileHandle(void) = 0;
};

//--------------------------------------------------------------------//

///��������� ������ � ��������� ������ �������������� ����������� ������-������
class INdxCashedFile : public virtual INdxFile
{
public:
	///�������������� ��������� ����
	virtual void InitCash(unsigned int uiCashBufferSize, unsigned int uiCashMinSizeToFlush) = 0;
	///�������� ����
	virtual void Cashed(void) = 0;
	///���������� �� ���� ����������� ������ ���� �����
	virtual void FlushFilledBuffers(void) = 0;
};

//--------------------------------------------------------------------//

///�������� �������� �� ���� ������, � ������ ������������� �� ���������� ������
#pragma pack(push,1)  // Fix packing size 
struct SCompositeOffset
{
	///�������� � �����
	unsigned int uiOffset;
	///������ �����
	unsigned char ucFileIndex;

	///�������� ������
	bool operator<(const SCompositeOffset& RightValue) const
	{
		if(ucFileIndex==RightValue.ucFileIndex){
			return uiOffset<RightValue.uiOffset?true:false;
		}
		return ucFileIndex<RightValue.ucFileIndex?true:false;
	};

};
#pragma pack(pop)

//--------------------------------------------------------------------//

///���������� �� ���������� ������
struct SNdxLevelInfo
{
	///��� ���������� ������� � ������
	enum EIndexCoordinateType
	{
		///����� ����������� � ���������
		ictSentenceAbsNumber,
		///����� ������ � ���������
		ictTextAbsNumber,
		///����� ��������� � ������
		ictParagraphNumber,
		///����� ����������� � ���������
		ictSentenceNumber,
		///����� ����������� � ������
		ictSentenceInTextNumber,
		///����� ����� � �����������
		ictWordNumber,
		///����� ����� � ������
		ictWordInTextNumber,
	};

	///��� �������� ������ (��� ���������������, � ����������������)
	enum ELevelControlType
	{
		//������������
		lctUndefined,	
		//�������� ������� ����	 
		lctWords,
		//�������� ���������� �����������
		lctSentences,	
		//�������� ���������
		lctCoordinates	
	};

	///����� ������
	unsigned char m_ucLevelNumber;
	///��� ����������, ������� ������ �������
	EIndexCoordinateType m_IndexCoordinateType;
	///��� ������ ������ ������ ����������
	unsigned char m_ucStartBit;
	///���������� ����� ���������� �� �������
	unsigned char m_ucBitPerLevel;
	///��� ����, ��� ������������ ������ �������
	ELevelControlType m_eControlType;
	///��� ����, ��� �������������� ������ �������
	ELevelControlType m_eControlByType;
};

//--------------------------------------------------------------------//
///��������� ������ � ���������� ������ ��������� ������
class INdxLevelStorage : public virtual INdxDataUnit
{
public:		
	///����������� �� ��������y ��������� ������
	virtual void	SeekPos(SCompositeOffset* pOffset, unsigned int uiOrigin) = 0;
	///���������� ������� � ��������� ��������� ������
	virtual void	TellPos(SCompositeOffset* pOffset) = 0;

	//���������� ������ �� ��������� ��������� ������
	///�������� ������ �� ������ �������
	virtual bool	StartRead(SCompositeOffset* pOffset, unsigned int* puiDataSizeInFile) = 0;
	///������ � �����
	virtual void	Read(unsigned char* pBuffer, unsigned int uiSize) = 0;
	///����������� ������, ���������� ������ ������������
	virtual void	StopRead(unsigned int* puiReadedDataSize) = 0;
	
	//���������� ���������� � ��������� ��������� ������
	///�������� ���������� ������������ ������
	virtual void	StartCompleteDataAppend(SCompositeOffset* pOffset) = 0;
	///�������� ���������� ���������� ������
	virtual void	StartUnCompleteDataAppend(SCompositeOffset* pOffset) = 0;
	///���������� ������ ������
	virtual void	Append(unsigned char* pBuffer, unsigned int uiSize) = 0;
	///����������� ����������, ���������� ������ ������������
	virtual void	StopAppend(unsigned int* puiAppendedDataSize) = 0;

	///���������� ������ ���������� ���������� ������
	virtual unsigned int GetAppendedUnCompleteDataSize(void) = 0;
	///������������� � ���������� ���������� ������
	virtual void	SeekPosInAppendedUnCompleteData(unsigned int uiOffset, unsigned int uiOrigin) = 0;
	///����� ����� ������ � ���������� ���������� ������
	virtual void	WriteInAppendedUnCompleteData(unsigned char* pBuffer, unsigned int uiSize) = 0;

	///�������� �� ��������� ������
	virtual void	Delete(SCompositeOffset* pOffset) = 0;
	
	///��������� ������ � ��������� ��������� ������
	virtual void	UpdateData(void) = 0;
};

//--------------------------------------------------------------------//

///��������� ������ � ��������� ���������� ������
class INdxTableStorage : public virtual INdxDataUnit
{
public:				
	typedef std::vector<SS::Interface::Core::DBMS::TDataTableFieldDescription> TTableFieldCollection;

	///��������� ���� � �������
	virtual HRESULT AddField(SS::Interface::Core::DBMS::TDataTableFieldDescription* pDataTableFieldDescription) = 0;
	///���������� ��������� ����� �������
	virtual TTableFieldCollection* GetFieldsCollection(void) = 0;

	///�������������� ������� ������ � ����
	virtual HRESULT InitFind(wchar_t* pKeyName, void* pKeyValue, void* ArrayOfPointersToData[], unsigned short* pusFindId = 0) = 0;
	///���� � ������� ��������� ��� �� ������������ ��������� ���� ����� �� ���������� ��������
	virtual HRESULT Find(unsigned int uiFindId = 0) = 0;
	///���� � ������� ���� ��� �� ����������� �������
	virtual HRESULT FindOne(unsigned int uiFindId = 0) = 0;

	///�������������� ������� ������������� ������ � ����
	virtual HRESULT SpanFindInit(wchar_t* pKeyName, void* pLowerKeyValue, void* pUpperKeyValue, 
		std::set<unsigned int>* pSetOfRecordsIndexes, unsigned short* pusFindId = 0) = 0;
	///���� � ������� ������ ��������������� SpanFindInit
	virtual HRESULT SpanFind(unsigned int uiFindId = 0) = 0;

	///���������� ������ ������ ������� �������� ����� ������� ������� ������
	virtual unsigned int GetFoundRecordIndex(unsigned int uiFindId = 0) = 0;
	///������� ������ ������� �� �������
	virtual void DeleteRecord(unsigned int uiRecordIndex) = 0;
	///�������������� ������� ������������ �������
	virtual HRESULT InitScan(long nStartRecordIdx, void* ArrayOfPointersToData[]) = 0;
	///���������� ��������� ������ �������
	virtual HRESULT Scan(void) = 0;
	///���������� ������ ������� �� �������
	virtual HRESULT ScanOne(unsigned int uiRecordIndex) = 0;
	///�������������� �������� ���������� ������ � �������.
	virtual HRESULT InitAdd(void* ArrayOfPointersToData[]) = 0;
	///��������� ������ � �������
	virtual HRESULT Add(void) = 0;
	///�������������� �������� ��������� ���� ����� �������.
	virtual HRESULT InitModify(void* ArrayOfPointersToData[]) = 0;
	///������� � �������� ������ � �������
	virtual HRESULT FindOneAndChange(void) = 0;
};

//--------------------------------------------------------------------//

///��������� ������ � ��������� ���������� ������
class INdxVectorStorage : public virtual INdxDataUnit
{
public:				
	//���������� ������ �� ���������� ��������� ������
	///��������� �� ������ ������ �� �������, ���������� �� ������
	virtual void	MoveToAndGetDataSize(unsigned int uiIndex, unsigned int* puiDataSizeInFile) = 0;
	///������ ��� ������ ����������� �� �������
	virtual void	ReadWholeData(unsigned char* pData, unsigned int uiDataSize) = 0;
	///������ ����� ������ ����������� �� �������
	virtual void	ReadDataChunk(unsigned char* pData, unsigned int uiDataSize) = 0;
	///������� ������ ������ ����������� �� �������, �������� ��������� �� ������
	virtual void	SeekInData(unsigned int uiOffset) = 0;
	
	//���������� ���������� � ��������� ��������� ������
	///��������� ������ � ���������, ���������� ������, �� �������� ����� ��������� ������
	virtual void	AppendWholeData(unsigned char* pData, unsigned int uiDataSize, unsigned int* puiIndex) = 0;
	///��������� ����� ������, ��������� �������� ��������� ����������
	virtual void	AppendDataChunk(unsigned char* pData, unsigned int uiDataSize) = 0;
	///��������� �������� ��������� ����������, ���������� ������, �� �������� ����� ��������� ������
	virtual void	AppendDataChunkComplete(unsigned int* puiIndex) = 0;
	
	///������� ������ �� �������
	virtual void	Delete(unsigned int uiIndex) = 0;
	///��������� ������� �� ������ �� �������
	virtual bool	IsDeleted(unsigned int uiIndex) = 0;

	///���������� ���������� ��������
	virtual unsigned int GetIndexesNumber(void) = 0;
};

//--------------------------------------------------------------------//

///��������� ������ � ���������� ��������� ������
class INdxStorage : public virtual INdxDataUnit
{
public:
	///���������� ��������� ����� ����� � ������
	virtual INdxTableStorage* GetEntryPointsStorage(void) = 0;
	///���������� ��������� ������� ����������
	virtual INdxVectorStorage* GetTextImagesStorage(void) = 0;
	///���������� ��������� ������� ����������
	virtual void GetTextImagesStorages(INdxFile** ppNdxTextsOffsets, INdxFile** ppNdxTextBlocksOffsets, INdxVectorStorage** ppNdxTextBlocksContent) = 0;
	///���������� ��������� ���������
	virtual INdxLevelStorage* GetCoordinateStorage(void) = 0;

	///��������� ���������� �� ������������� ������
	virtual void AddLevelInfo(SNdxLevelInfo* pNdxLevelInfo) = 0;
	///���������� ���������� �� ������������� ������ �� ������
	virtual SNdxLevelInfo const* GetLevelInfo(unsigned int uiLevelNumber) = 0;
	///���������� ����� ������������ �������
	virtual unsigned int GetLevelsNumber(void) = 0;
};

//--------------------------------------------------------------------//

///��������� ������ � ���������� ��������� ������
class INdxStorageWithStatistic : public virtual INdxStorage
{
public:
	///���������� ��������� ������ ��������
	virtual INdxVectorStorage* GetIndexFrequencyStorage(void) = 0;
	///���������� ��������� ���� ���������� �������
	virtual INdxFile* GetDocumentNormStorage(void) = 0;
};

//--------------------------------------------------------------------//

class INdxDataStorageFactory : public virtual SS::Interface::IBase
{
public:				
	///������� ������� ��������� ����
	virtual INdxFile* CreateNdxFile(void) = 0;
	///������� ��������� ���� �������������� ����������� ������-������
	virtual INdxCashedFile* CreateNdxCashedFile(void) = 0; 
	///������� ��������� ��������� ������
	virtual INdxTableStorage* CreateNdxTableStorage(void) = 0;
	///������� ��������� ��������� ������
	virtual INdxVectorStorage* CreateNdxVectorStorage(void) = 0;
	///������� ��������� ��������� ������
	virtual INdxStorage* CreateNdxStorage(void) = 0;
	///������� ��������� ��������� ������ � ���������� ����������
	virtual INdxStorageWithStatistic* CreateNdxStorageWithStatistic(void) = 0;

};

//--------------------------------------------------------------------//

}
}
}
}
}