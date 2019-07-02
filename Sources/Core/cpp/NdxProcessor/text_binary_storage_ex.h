#pragma once

#include "../ASDInterface/INdxDataStorage.h"
#include "../ASCInterface/ICommonContainers.h"
#include ".\texts_binary_storage.h"
#include ".\int_containers.h"
#include ".\basis_storage.h"
#include ".\memory_management.h"
#include ".\byte_align.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Storages
{

//--------------------------------------------------------------------//

///��������� ����, �������� ��������� ������ ����
class CTextBlock
{
public:
	///��������� ������ � ����
	void AddIndex(SS::Interface::Core::CommonContainers::IServiceIndex* pServiceIndex, unsigned int uiCharPosition);
	///��������� ITextBlockCut ������� �� ���������� �����, ���� �� ��������� ��������� �� �������� ���� ���������� �����
	///���������� ���������� ������������� ����������� ������
	unsigned int FillTextBlockCut(SS::Interface::Core::CommonContainers::ITextBlockCut* pTextBlockCut, unsigned int uiHeadPos = 0, unsigned int uiTailPos = 0xffffffff);
	///������ ���� � ����, ���������� ���������� ���������� ����
	unsigned int AddToFile(SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* pFile);
	///�������� ���� �� �����
	void FillFromFile(SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* pFile, unsigned int uiTextBlockBinarySize);
	///���������� ������� ���������� ���� � �����
	__inline unsigned int GetCurrentWordsNumber(void){return (unsigned int)m_si_offset.size();};
	
protected:
	///���������� � ������� ��������� ����
	__inline void Reset(void)
	{
		m_positions.clear();
		m_si_offset.clear();
		m_si_data.clear();
	};

	///	���������������� ��� ������ � �������� ������� ByteAlign
	//�� ����� Containers::CByteAlignCompress	m_ByteAlignCompress;
	///	����� �������
	std::vector<unsigned int>		m_positions;
	///	����� ����� ������ ��������� ��������
	std::vector<unsigned short>		m_si_offset;
	///	����� ������ ��������� ��������
	std::vector<unsigned char>		m_si_data;
};

//--------------------------------------------------------------------//

///�������� � �������� ����������� �� �������
///������� �� 3 ��������:
///	��������� �������� �� ������� ������ ������
///	��������� �������� �� ����� �������
///	��������� ������ �������
///��� �������� �������, ���: 
//����� ������� �� ������, ������ ����, ����� ���������� �������� N ���� (��������� �������)
class CTextsBinaryStorageEx : public CTextsBinaryStorage
{
public:
	CTextsBinaryStorageEx(SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* pNdxTextsOffsets,
		SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* pNdxTextBlocksOffsets,
		SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* pNdxTextBlocksContent);
	virtual ~CTextsBinaryStorageEx (void);

	///������������ ���������� ��������� ����������
	void PrepareIndexing(void){};
	///��������� �������� ��������� �� ��������� ����������
	void CompleteIndexing(void){};
	///��������� �������� ��������� �� ��������� ���������� ���������
	void CompleteDocumentIndexing(void){};

	///��������� ������ � ���������
	void AddIndex(SS::Interface::Core::CommonContainers::IServiceIndex* pServiceIndex, unsigned int uiCharPosition);
	///������������� ��������� ����� ������, ���������� ����������� ����� � ���������
	//�� ������������
	unsigned int  SetTextBlockComplete(void){return 0;};
	///������������� ��������� ������
	unsigned int SetTextComplete(void);
	///��������� ���� ������ �� ���������
	SS::Interface::Core::CommonContainers::ITextBlockCut* FillTextBlock(SS::Interface::Core::CommonContainers::ITextBlock* pTextBlock, 
			SS::Core::NdxSE::NdxProcessor::Containers::CInterval* pInterval,
			wstring* pwsIndexStorageName);
	///���������� ���������� �������
	unsigned int GetTextsNumber(void);
	
	//���������
	///������������ ���������� ���� � ��������� �����
	static const unsigned int m_uiMaxWordsNumberInTextBlock=1000;
	///���� ������ ��������� ������
	static const bool m_bCompressTextBlocks=true;

protected:
	///���������� �� ���������� �����
	struct STextBlockInfo
	{
		///�������� �� ��������� ����
		unsigned int m_uiTextBlockOffset;
		///������ ���������� �����
		unsigned int m_uiTextBlockSize;
	};

	///������ ��������� ���� �� ����
	void MoveDownTextBlock(void);

	///������� ���� ������
	CTextBlock m_CurrentTextBlock;
	///������� ���������� ������ � ������� ������
	unsigned int m_uiCurrentTextBlocksNumber;

	///��������� �������� �� ������� ������ ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* m_pNdxTextsOffsets;
	///��������� �������� �� ����� �������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxFile* m_pNdxTextBlocksOffsets;
	///��������� ������ �������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* m_pNdxTextBlocksContent;
};

//--------------------------------------------------------------------//

}
}
}
}
}