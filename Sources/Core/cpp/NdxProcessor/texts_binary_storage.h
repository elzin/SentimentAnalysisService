#pragma once

#include "../ASDInterface/INdxDataStorage.h"
#include "../ASCInterface/ICommonContainers.h"
#include ".\int_containers.h"
#include ".\basis_storage.h"
#include ".\memory_management.h"

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

///������� ����� ��� �������� ����������� �������
class CTextsBinaryStorage : public CBasisStorage
{
public:
	///��������� ������ � ���������
	virtual void AddIndex(SS::Interface::Core::CommonContainers::IServiceIndex* pServiceIndex, unsigned int uiCharPosition) = 0;
	///������������� ��������� ����� ������, ���������� ����������� ����� � ���������
	virtual unsigned int  SetTextBlockComplete(void) = 0;
	///������������� ��������� ������
	virtual unsigned int SetTextComplete(void) = 0;
	///��������� ���� ������ �� ���������
	virtual SS::Interface::Core::CommonContainers::ITextBlockCut* FillTextBlock(SS::Interface::Core::CommonContainers::ITextBlock* pTextBlock, 
			SS::Core::NdxSE::NdxProcessor::Containers::CInterval* pInterval,
			wstring* pwsIndexStorageName) = 0;
	///���������� ���������� �������
	virtual unsigned int GetTextsNumber(void) = 0;

};

//--------------------------------------------------------------------//

///�������� � �������� ����������� �� �������
class CTextsBinaryStorageSimple : public CTextsBinaryStorage
{
public:
	typedef vector<unsigned char> TTextBuffer;

	CTextsBinaryStorageSimple(SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* pNdxVectorStorage);
	virtual ~CTextsBinaryStorageSimple(void);
	
	///������������ ���������� ��������� ����������
	void PrepareIndexing(void){};
	///��������� �������� ��������� �� ��������� ����������
	void CompleteIndexing(void){};
	///��������� �������� ��������� �� ��������� ���������� ���������
	void CompleteDocumentIndexing(void){};

	///��������� ������ � ���������
	void AddIndex(SS::Interface::Core::CommonContainers::IServiceIndex* pServiceIndex, unsigned int uiCharPosition);
	///������������� ��������� ����� ������, ���������� ����������� ����� � ���������
	unsigned int  SetTextBlockComplete(void);
	///������������� ��������� ������
	unsigned int SetTextComplete(void);
	///��������� ���� ������ �� ���������
	SS::Interface::Core::CommonContainers::ITextBlockCut* FillTextBlock(SS::Interface::Core::CommonContainers::ITextBlock* pTextBlock, 
			SS::Core::NdxSE::NdxProcessor::Containers::CInterval* pInterval,
			wstring* pwsIndexStorageName);
	///���������� ���������� �������
	unsigned int GetTextsNumber(void){return m_pNdxVectorStorage->GetIndexesNumber();};

protected:
	///��������� ��������� ����������
	void AddServiceInfo(unsigned char* pServiceInfo, unsigned int uiServiceInfoSize);

	///����� ������� ��������� ����������
	MemoryManagement::CBuffer m_ServiceInfoBuffer;
	///����� �������� ������
	TTextBuffer m_TextBuffer;
	///������ �������� ������ ���������� �������
	unsigned int m_uiServiceIndexBufferSize;
	///������� ���������� ����������� ������ ������
	unsigned int uiCurrentTextBlockNumber;

	///���������� ��������� ��������� ������
	SS::Interface::Core::NdxSE::NdxDataStorage::INdxVectorStorage* m_pNdxVectorStorage;
};

//--------------------------------------------------------------------//

}
}
}
}
}