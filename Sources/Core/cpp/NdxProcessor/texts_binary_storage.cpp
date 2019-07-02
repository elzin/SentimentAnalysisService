#include "StdAfx.h"
#include ".\texts_binary_storage.h"
#include ".\const.h"
#include ".\console.h"
#include <windows.h>
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

using namespace SS::Core::NdxSE::NdxProcessor;
using namespace SS::Interface::Core::NdxSE::NdxDataStorage;
using namespace SS::Interface::Core::CommonContainers;
using namespace SS::Core::NdxSE::NdxProcessor::Containers;

//--------------------------------------------------------------------//

CTextsBinaryStorageSimple::CTextsBinaryStorageSimple(INdxVectorStorage* pNdxVectorStorage) :
	m_pNdxVectorStorage(pNdxVectorStorage), m_ServiceInfoBuffer(8192),
	m_uiServiceIndexBufferSize(0), uiCurrentTextBlockNumber(0)

{
}

CTextsBinaryStorageSimple::~CTextsBinaryStorageSimple(void)
{
}

void CTextsBinaryStorageSimple::AddIndex(IServiceIndex* pServiceIndex, unsigned int uiCharPosition)
{
	if(ISNULL(m_pNdxVectorStorage)) return;

	if(!m_pNdxVectorStorage->IsOpen()){
		TO_CONSOLE(L"TextsInfo not opened!!!");
		return;
	}

	unsigned char* pServiceIndexBuffer=NULL;
	unsigned int uiServiceIndexBufferSize=0;
	unsigned char* arEmptyServiceIndex[5];

	if(pServiceIndex){
		//�������� ����� ���� �� ������
		//ToConsole(L"ServiceIndexSource", (unsigned int)pServiceIndex->GetViewIndex()->m_DictionaryIndex);
		//ToConsole(L"ServiceIndexForm", (unsigned int)pServiceIndex->GetViewIndex()->m_IDForm);
		pServiceIndex->GetInfoBuff((char**)&pServiceIndexBuffer, &uiServiceIndexBufferSize);
	}else{
		//���� ��������� ������ ������, ������ �������� ������ ����
		//ToConsole(L"ServiceIndexSource: 0xffffffff");
		uiServiceIndexBufferSize=5;
		memset(arEmptyServiceIndex, 0xffffffff, sizeof(char*) * uiServiceIndexBufferSize);
		pServiceIndexBuffer=(unsigned char*)arEmptyServiceIndex;
	}

	if(ISNULL(pServiceIndexBuffer)) return;
	if(ISNULL(uiServiceIndexBufferSize)) return;
	
	//������������� ��� ������ ������ ���������� 
	//������� ����������, ���� �� ��� ������ ������
	//��������� ���� ������ ��� ������
	if(m_uiServiceIndexBufferSize==0){
		//������� ������� �����
		m_uiServiceIndexBufferSize=uiServiceIndexBufferSize;
		
		//��������� ��������� ����������
		AddServiceInfo((unsigned char*)&uiServiceIndexBufferSize, sizeof(unsigned int));
	}else{
		//��������� �� ��������� �� ������
		if(m_uiServiceIndexBufferSize!=uiServiceIndexBufferSize){
			TO_CONSOLE(L"ServiceIndexBufferSize has changed!!!")
		}
	}

	//��������� ����� ������� � ����� ������
	unsigned int uiOldSize=(unsigned int)m_TextBuffer.size();
	
	//��������� ����� ���������� �������
	AddServiceInfo(pServiceIndexBuffer, m_uiServiceIndexBufferSize);
	//��������� ����� ��� �������� ������� ������� �������
	AddServiceInfo((unsigned char*)&uiCharPosition, sizeof(unsigned int));
}

void CTextsBinaryStorageSimple::AddServiceInfo(unsigned char* pServiceInfo, unsigned int uiServiceInfoSize)
{
	if(ISNULL(pServiceInfo)) return;
	if(ISNULL(uiServiceInfoSize)) return;
	
	if(uiServiceInfoSize>m_ServiceInfoBuffer.GetBufferSize()-m_ServiceInfoBuffer.GetFilledSize()){
		//��������� ���������� ����� � ����
		m_pNdxVectorStorage->AppendDataChunk(m_ServiceInfoBuffer.GetHeadPtr(), m_ServiceInfoBuffer.GetFilledSize());
		//���������� ��� ����������� ����� ������
		m_ServiceInfoBuffer.Reset();
	}
	
	//������ ������ � �����
	m_ServiceInfoBuffer.PutData(pServiceInfo, uiServiceInfoSize);
}

unsigned int CTextsBinaryStorageSimple::SetTextBlockComplete(void)
{
	//if(!m_TextBuffer.empty()){
	//	//��������� ���������� ����� � ����
	//	m_pNdxVectorStorage->AppendDataChunk(&m_TextBuffer.front(), (unsigned int)m_TextBuffer.size());
	//	//������� ����� ������ ��� ���������� ����
	//	m_TextBuffer.clear();
	//}

	return ++uiCurrentTextBlockNumber;
}

unsigned int CTextsBinaryStorageSimple::SetTextComplete(void)
{
	unsigned int uiTextIndex=EMPTY_VALUE;
	
	if(!uiCurrentTextBlockNumber){
		//���� ������ ������ �� ���� ��������� ������ ��������� ����������
		unsigned int uiEmptyServiceInfo=0;
		AddServiceInfo((unsigned char*)&uiEmptyServiceInfo, sizeof(unsigned int));
	}
	
	//��������� ���������� ����� � ����
	if(m_ServiceInfoBuffer.GetFilledSize())
		m_pNdxVectorStorage->AppendDataChunk(m_ServiceInfoBuffer.GetHeadPtr(), m_ServiceInfoBuffer.GetFilledSize());
	//������������� �� ��������� ������ ���������� ��� ������
	m_pNdxVectorStorage->AppendDataChunkComplete(&uiTextIndex);

	//���������� ��� ����������� ����� ������
	m_ServiceInfoBuffer.Reset();
	//�������� ������ ������ ���������� �������
	m_uiServiceIndexBufferSize=0;
	uiCurrentTextBlockNumber=0;

	return uiTextIndex;
}

ITextBlockCut* CTextsBinaryStorageSimple::FillTextBlock(ITextBlock* pTextBlock, CInterval* pInterval, wstring* pwsIndexStorageName)
{
	if(ISNULL(pTextBlock)) return NULL;
	if(ISNULL(pInterval)) return NULL;
	if(ISNULL(pwsIndexStorageName)) return NULL;
	
	unsigned int uiTextBufferSize=0;
	
	if(pInterval->m_uiHeadPos>pInterval->m_uiTailPos){
		TO_CONSOLE(L"Interval is corrupted, head after tail!!!");
		return NULL;
	}

	//ToConsole(L"TextNumber", pTextBlock->GetTextFeature()->GetTextNumber());
	//pInterval->View();

	//������ ��������� ������ ������
	m_pNdxVectorStorage->MoveToAndGetDataSize(pTextBlock->GetTextFeature()->GetTextNumber(), &uiTextBufferSize);

	if(uiTextBufferSize){
		//���� ������ �������� ������ ������
		
		//���������� ������ ������ ���������� �������
		m_uiServiceIndexBufferSize=0;
		m_pNdxVectorStorage->ReadDataChunk((unsigned char*)&m_uiServiceIndexBufferSize, sizeof(unsigned int));	
		
		//��������!!!!
		//!!!����� � ������ ��������� ������ sizeof(unsigned int) ��� ��� ������ ������ ����������
		//������� �������� ������� ������� ������� �����!!!! 
		//������ ������ ���������� ������ �� ����� ���������� �������, ���� ������������ ��������� ������
		unsigned int uiFullServiceBufferSize=m_uiServiceIndexBufferSize + sizeof(unsigned int);

		//�������� ���������� ��������� ��������
		unsigned int uiServiceIndexesNumber=
			(uiTextBufferSize-sizeof(unsigned int))/(uiFullServiceBufferSize);
		//ToConsole(L"ServiceIndexesNumber", uiServiceIndexesNumber);

		if(pInterval->m_uiHeadPos>=uiServiceIndexesNumber){
			TO_CONSOLE(L"Interval not correct, or t_img storage is corrupted!!! Couldn't extract TextBlockCut");
			ToConsole(L"TextNumber", pTextBlock->GetTextFeature()->GetTextNumber());
			pInterval->View();
			return  NULL;
		}

		if(pInterval->m_uiTailPos>=uiServiceIndexesNumber){
			//���� �������� ������� �� ������� ������ �������� ���
			pInterval->m_uiTailPos=uiServiceIndexesNumber-1;
		}

		//����������� ����� ��� ��������
		m_TextBuffer.assign(uiFullServiceBufferSize*pInterval->GetLength(), 0);
		//��������� � ���������
		m_pNdxVectorStorage->SeekInData(pInterval->m_uiHeadPos*uiFullServiceBufferSize);
		//������ �������� � �����
		m_pNdxVectorStorage->ReadDataChunk((unsigned char*)&m_TextBuffer.front(), (unsigned int)m_TextBuffer.size());	
		
		//������ � ����� ��������� ���������� TextBlock
		ITextBlockCut* pTextBlockCut=pTextBlock->AddBlockCut();

		if(ISNULL(pTextBlockCut)) return NULL;
		IIndexAndPosition* pIndexAndPosition=NULL;
		
		//������������� ��� �����
		pTextBlockCut->SetRelevance(pInterval->m_uiWeight);
		//������������� ��� ���������� ��������� � ������� ������ ����
		pTextBlockCut->SetIndexTypeName(pwsIndexStorageName->c_str());

		unsigned int uiCurrIndex=0;
		unsigned char* pPosInTextBuffer=(unsigned char*)&m_TextBuffer.front();
		unsigned int uiCurrCharPosition=EMPTY_VALUE;
		while(pPosInTextBuffer<=(unsigned char*)&m_TextBuffer.back()){
			//��������� ������ 
			pIndexAndPosition=pTextBlockCut->AddIndexAndPosition();
			if(ISNULL(pIndexAndPosition)){
				return pTextBlockCut;
			}
			//���� ��� ����� � �������
			pIndexAndPosition->GetServiceIndex()->SetInfoBuff((char*)pPosInTextBuffer, m_uiServiceIndexBufferSize);

			//��������� ������� ������� ������� �����
			memcpy((unsigned char*)&uiCurrCharPosition, 
				(pPosInTextBuffer+m_uiServiceIndexBufferSize), sizeof(unsigned int));
			pIndexAndPosition->SetFirstCharPosition(uiCurrCharPosition);

			//��������� ������
			pPosInTextBuffer+=uiFullServiceBufferSize;
		}
		return pTextBlockCut;
	}else{
		TO_CONSOLE(L"TextBufferSize is empty!!!");
		return NULL;
	}
	

}

//--------------------------------------------------------------------//

}
}
}
}
}