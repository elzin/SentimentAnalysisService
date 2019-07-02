#pragma once

#include ".\list_containers.h"
#include ".\basis_containers.h"
#include ".\pool_client.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Containers
{

//--------------------------------------------------------------------//

///���� ������ � ������������ ����������������� ���������� � ������� ������
///������ ����� �� ������ 0xff 
#pragma pack(push,1)  // Fix packing size 

template <unsigned char DataSize>
class CBinaryBlock : public CUnidirListItem< CBinaryBlock<DataSize> >
	, public SS::Core::NdxSE::NdxProcessor::MemoryManagement::CPoolClient
{
public:
	CBinaryBlock(void):m_ucCurrentPos(0){};
		
	///��������� ������ � ����� �����, ���������� ������ ����������� ������
	///����� ����� � �� ������� �� ��� �����
	unsigned int PushBack(unsigned char* pucData, unsigned int uiDataSize)
	{
		if(ISNULL(pucData)) return 0;
		if(ISNULL(uiDataSize)) return 0;

		unsigned int uiAvailableSize=DataSize-m_ucCurrentPos;
		if(uiDataSize<uiAvailableSize)	uiAvailableSize=uiDataSize;
		
		memcpy(m_arrData+m_ucCurrentPos, pucData, uiAvailableSize);
		m_ucCurrentPos+=uiAvailableSize;

		return uiAvailableSize;
	};

	///���������� ������ � ����� �����, ���������� ������ ��������� ������
	///� ����� ����� �� ����������� ���� ������
	unsigned int PopBack(unsigned char* pucData, unsigned int uiDataSize)
	{
		if(ISNULL(pucData)) return 0;
		if(ISNULL(uiDataSize)) return 0;

		unsigned int uiAvailableSize=m_ucCurrentPos;
		if(uiDataSize<uiAvailableSize)	uiAvailableSize=uiDataSize;
		
		memcpy(pucData, m_arrData+(m_ucCurrentPos-uiAvailableSize), uiAvailableSize);
		m_ucCurrentPos-=uiAvailableSize;

		return uiAvailableSize;
	}

	///��������� �� �������
	inline bool IsEmpty(void){ return (m_ucCurrentPos != 0); };
	///��������� �� �������������
	inline bool IsFull(void){ return (m_ucCurrentPos>=DataSize); };
	///���������� ��������� ������
	unsigned int GetFreeSize(void){return (DataSize - m_ucCurrentPos);};
	///���������� ���������� ������
	unsigned char GetFilledSize(void){return m_ucCurrentPos;};
	///������������� ���������� ������
	void SetFilledSize(unsigned char ucValue){m_ucCurrentPos=ucValue;};
	///���������� ��������� �� ������
	unsigned char* GetDataPtr(void){return m_arrData;};
	
protected:
	///����� � �������
	unsigned char m_arrData[DataSize];	
	///������� ������� � ������
	unsigned char m_ucCurrentPos;
};
#pragma pack(pop)

//--------------------------------------------------------------------//

///������� ����� ������ ���������� ������� �� ������, ��������� ������
template <unsigned char BlockSize>
class CBlockBuffer : 
	public CBinaryContainer
	//,	public SS::Core::NdxSE::NdxProcessor::MemoryManagement::CPoolClient
{
public:
	CBlockBuffer(void):m_BinaryBlocksNumber(0), m_pTailBinaryBlock(NULL){};
	~CBlockBuffer(void){Reset();};

	///���������� ������ ��������� ������
	unsigned int GetBinaryBufferSize(void)
	{
		if(!m_pTailBinaryBlock) return 0;
		return (m_BinaryBlocksNumber-1)*BlockSize+m_pTailBinaryBlock->GetFilledSize();
	};

	///��������� ������ � �����
	void PushBack(unsigned int uiValue)
	{
		unsigned int uiTemp=uiValue;
		PushBack((unsigned char*)&uiTemp, sizeof(unsigned int));
	};
	

	///��������� ������ � �����
	virtual void PushBack(unsigned char* pucData, unsigned int uiDataSize)
	{
		if(ISNULL(pucData)) return;
		if(ISNULL(uiDataSize)) return;
		
		if(!m_pTailBinaryBlock) AddBinaryBlock();

		//� ����� ��������� ������, 
		//���� ������ �� ������� ��������� ���� � ���������� � ����������� ������� 
		unsigned int uiTempSize=0;
		while(true){
			uiTempSize+=m_pTailBinaryBlock->PushBack(pucData+uiTempSize, uiDataSize-uiTempSize);

			if(uiTempSize<uiDataSize)
				AddBinaryBlock();
			else
				break;
		}
	};

	///���������� ������ � �����
	virtual void PopBack(unsigned char* pucData, unsigned int uiDataSize)
	{
		if(ISNULL(pucData)) return;
		if(ISNULL(uiDataSize)) return;
		if(!m_pTailBinaryBlock) return;

		if(uiDataSize>(m_BinaryBlocksNumber-1)*BlockSize+m_pTailBinaryBlock->GetFilledSize()) return;
		
		//� ����� ���������� ������, ���� ������� ���� ������ ������� � ��� 
		unsigned int uiTempSize=0;
		unsigned int uiPopedSize=0;
		unsigned char* pucCurr=pucData+uiDataSize;
		while(true){
			uiTempSize=m_pTailBinaryBlock->GetFilledSize();
			if(uiTempSize>uiDataSize-uiPopedSize) uiTempSize=uiDataSize-uiPopedSize;

			pucCurr-=uiTempSize;
			uiPopedSize+=m_pTailBinaryBlock->PopBack(pucCurr, uiTempSize);

			if(uiPopedSize>=uiDataSize){
				break;
			}else{
				PopBinaryBlock();
			}
		}

		if(m_pTailBinaryBlock->GetFilledSize()==0) PopBinaryBlock();
	};

	///���������� ���� � �����
	virtual unsigned char PopByte(void)
	{
		while(m_pTailBinaryBlock && m_pTailBinaryBlock->IsEmpty())	
				PopBinaryBlock();
		
		if(!m_pTailBinaryBlock) return UC_EMPTY;

		unsigned char ucTemp=0;
		m_pTailBinaryBlock->PopBack(&ucTemp, sizeof(unsigned char));

		return ucTemp;
	};

	///������� 4 ����� � ������ � ��������� ������ ����������
	virtual void PushBackEncoded(unsigned int uiValue)
	{
		//������ 7-�� ����� � ������, �������� ���� ����� ��������� �������� ���
		unsigned char ucBytesNumber=m_pByteAlignCompress->GetNeededBytesNumber(uiValue);
		unsigned char i=0;
		unsigned char ucTemp;
		while(i<ucBytesNumber){
			ucTemp=(uiValue&arrMasks[i])>>arrOffsets[i];
			if(!(i==ucBytesNumber-1)){
				//���������
				ucTemp=m_pByteAlignCompress->m_cucSignBit|ucTemp;
			}
			PushBack(&ucTemp, sizeof(unsigned char));
			i++;
		}
	};

	///���������� ����������
	virtual void Reset(void)
	{
		CBinaryBlock<BlockSize>* pTempBinaryBlock=NULL;
		while(m_pTailBinaryBlock){
			pTempBinaryBlock=m_pTailBinaryBlock->GetNextItem();
			delete m_pTailBinaryBlock;
			m_pTailBinaryBlock=pTempBinaryBlock;
		}
		m_pTailBinaryBlock=NULL;
		m_BinaryBlocksNumber=0;
	};

	///����� ���������� ���������� � ����
	unsigned int Write(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage)
	{
		if(ISNULL(pNdxStorage)) return 0;
		
		unsigned int uiWritedBytes=0;
		//����� ���������� ������
		uiWritedBytes+=WriteCompressed(pNdxStorage, m_BinaryBlocksNumber);

		//����� ������ �������� �����
		CBinaryBlock<BlockSize>* pBinaryBlock=GetTailBinaryBlock();
		unsigned char ucFilledSize=pBinaryBlock->GetFilledSize();
		pNdxStorage->Append((unsigned char*)&ucFilledSize, sizeof(unsigned char));
		uiWritedBytes+=sizeof(unsigned char);
		while(pBinaryBlock){
			//����� ��������� ���� � �������
			unsigned char* pBuffer=pBinaryBlock->GetDataPtr();
			pNdxStorage->Append(pBuffer, ucFilledSize);
			uiWritedBytes+=ucFilledSize;
			ucFilledSize=BlockSize;
			pBinaryBlock=pBinaryBlock->GetNextItem();
		}

		return uiWritedBytes;
	};

	///������ ���������� ���������� �� �����
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage)
	{
		if(ISNULL(pNdxStorage)) return;

		//������ ���������� ������
		m_BinaryBlocksNumber=ReadCompressed(pNdxStorage);
		
		//������ ������ �������� �����
		unsigned char ucFilledSize; 
		pNdxStorage->Read((unsigned char*)&ucFilledSize, sizeof(unsigned char));
		
		//������ ����� � �������, ��������� ������ ������
		CBinaryBlock<BlockSize>* pBinaryBlock=NULL;
		unsigned int i=m_BinaryBlocksNumber;
		while(i){
			if(pBinaryBlock){ 
				//���� ���� �� ������ ��������� � �������� � ������
				pBinaryBlock->SetNextItem(new CBinaryBlock<BlockSize>());
				pBinaryBlock=pBinaryBlock->GetNextItem();
			}else{
				m_pTailBinaryBlock=new CBinaryBlock<BlockSize>();
				pBinaryBlock=GetTailBinaryBlock();
			}
			
			//������ ���������� �����
			pNdxStorage->Read(pBinaryBlock->GetDataPtr(), ucFilledSize);
			pBinaryBlock->SetFilledSize(ucFilledSize);

			ucFilledSize=BlockSize;
			--i;
		}
	};

	///����������� �� ������
	unsigned int FromBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize)
	{
		if(ISNULL(pBuffer)) return 0;
		if(ISNULL(uiBufferSize)) return 0;
		
		//������ ���������� ������
		unsigned int uiReadedBytesNumber=0;
		unsigned int uiWorkedBytesNumber;
		m_BinaryBlocksNumber=m_pByteAlignCompress->Decode(pBuffer, uiBufferSize, 0, &uiWorkedBytesNumber);
		pBuffer+=uiWorkedBytesNumber;	
		uiReadedBytesNumber+=uiWorkedBytesNumber;

		//������ ������ �������� �����
		unsigned char ucFilledSize; 
		memcpy((unsigned char*)&ucFilledSize, pBuffer, sizeof(unsigned char));
		pBuffer+=sizeof(unsigned char);
		uiReadedBytesNumber+=sizeof(unsigned char);

		//������ �����, ��������� ������ ������
		CBinaryBlock<BlockSize>* pBinaryBlock=NULL;
		unsigned int i=m_BinaryBlocksNumber;
		while(i){

			if(pBinaryBlock){ 
				//���� ���� �� ������ ��������� � �������� � ������
				pBinaryBlock->SetNextItem(new CBinaryBlock<BlockSize>());
				pBinaryBlock=pBinaryBlock->GetNextItem();
			}else{
				m_pTailBinaryBlock=new CBinaryBlock<BlockSize>();
				pBinaryBlock=GetTailBinaryBlock();
			}
			
			//������ ���������� �����
			memcpy(pBinaryBlock->GetDataPtr(), pBuffer, ucFilledSize);
			pBuffer+=ucFilledSize;
			pBinaryBlock->SetFilledSize(ucFilledSize);
			uiReadedBytesNumber+=ucFilledSize;

			ucFilledSize=BlockSize;
			--i;
		}
		return 	uiReadedBytesNumber;
	}

	///������� � �����
	void ToBinaryBuffer(CByteAlignCompress::TBytesBuffer* pBytesBuffer)
	{
		if(ISNULL(pBytesBuffer)) return;
		
		//����� ���������� ������
		m_pByteAlignCompress->EncodeToBuffer(m_BinaryBlocksNumber, pBytesBuffer);

		//����� ������ �������� �����
		CBinaryBlock<BlockSize>* pBinaryBlock=GetTailBinaryBlock();
		unsigned char ucFilledSize=pBinaryBlock->GetFilledSize();
		pBytesBuffer->push_back(ucFilledSize);
		unsigned int uiTemp=0;
		while(pBinaryBlock){
			//����� ��������� ���� � �������
			unsigned char* pBuffer=pBinaryBlock->GetDataPtr();

			uiTemp=(unsigned int)pBytesBuffer->size();
			pBytesBuffer->resize(uiTemp+ucFilledSize);
			memcpy(&pBytesBuffer->front()+uiTemp, pBuffer, ucFilledSize);

			ucFilledSize=BlockSize;
			pBinaryBlock=pBinaryBlock->GetNextItem();
		}
	}

protected:
	///���������� ��������� ����
	CBinaryBlock<BlockSize>* GetTailBinaryBlock(void){return m_pTailBinaryBlock;};
	///��������� CPosBinaryBlock � �����
	virtual void AddBinaryBlock(void)
	{
		CBinaryBlock<BlockSize>* pTempBinaryBlock=new CBinaryBlock<BlockSize>();
		pTempBinaryBlock->SetNextItem(m_pTailBinaryBlock);
		m_pTailBinaryBlock=pTempBinaryBlock;
		m_BinaryBlocksNumber++;
	};

	///���������� CPosBinaryBlock � �����
	virtual void PopBinaryBlock(void)
	{
		CBinaryBlock<BlockSize>* pTempBinaryBlock=m_pTailBinaryBlock;
		m_pTailBinaryBlock=m_pTailBinaryBlock->GetNextItem();
		delete pTempBinaryBlock;
		--m_BinaryBlocksNumber;
	};

	///��������� ����
	CBinaryBlock<BlockSize>* m_pTailBinaryBlock;
	///��������� ������ ������� �������� ��������� ������� 
	unsigned int m_BinaryBlocksNumber;
};

//--------------------------------------------------------------------//

///������� ����� ������ ���������� ������� �� ������, ��������� �������, 
///����� ����������� ����������������� � ������ ����� �� ���� ��������� �� �������� ����
///����������� ����������� PopBack, ����� ������ ���������
///����������� ����������� ������ ������ ���� ����� ������ ������ ���� ���������� ������ �����
template <unsigned char BlockSize>
class CBlockBufferPusher : 
	public CBlockBuffer<BlockSize>
{
public:
	CBlockBufferPusher(void):m_pHeadBinaryBlock(NULL){};
	
	//-----------------------------
	//��� ������� �� ��������������
	///���������� ������ � �����
	void PopBack(unsigned char* pucData, unsigned int uiDataSize){TO_CONSOLE(L"Proxed");};
	///���������� ���� � �����
	unsigned char PopByte(void){TO_CONSOLE(L"Proxed"); return 0;};
	///������ ���������� ���������� �� �����
	void Read(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage){TO_CONSOLE(L"Proxed");};
	///����������� �� ������
	unsigned int FromBinaryBuffer(unsigned char* pBuffer, unsigned int uiBufferSize){TO_CONSOLE(L"Proxed"); return 0;};
	//-----------------------------

	///���������� ����������
	void Reset(void)
	{
		CBinaryBlock<BlockSize>* pTempBinaryBlock=NULL;
		while(m_pHeadBinaryBlock){
			pTempBinaryBlock=m_pHeadBinaryBlock->GetNextItem();
			delete m_pHeadBinaryBlock;
			m_pHeadBinaryBlock=pTempBinaryBlock;
		}

		m_pTailBinaryBlock=NULL;
		m_pHeadBinaryBlock=NULL;
		m_BinaryBlocksNumber=0;
	};

	///����� ���������� ���������� � ����
	unsigned int Write(SS::Interface::Core::NdxSE::NdxDataStorage::INdxLevelStorage* pNdxStorage)
	{
		if(ISNULL(pNdxStorage)) return 0;

		unsigned int uiWritedBytes=0;
		CBinaryBlock<BlockSize>* pBinaryBlock=GetHeadBinaryBlock();
		while(pBinaryBlock){
			//����� ��������� ���� � �������
			pNdxStorage->Append(pBinaryBlock->GetDataPtr(), pBinaryBlock->GetFilledSize());
			uiWritedBytes+=pBinaryBlock->GetFilledSize();
			pBinaryBlock=pBinaryBlock->GetNextItem();
		}

		return uiWritedBytes;
	};

	///������� � �����
	void ToBinaryBuffer(CByteAlignCompress::TBytesBuffer* pBytesBuffer)
	{
		if(ISNULL(pBytesBuffer)) return;
		
		CBinaryBlock<BlockSize>* pBinaryBlock=GetHeadBinaryBlock();
		unsigned int uiTemp=0;
		while(pBinaryBlock){
			//����� ��������� ���� � �������
			uiTemp=(unsigned int)pBytesBuffer->size();
			pBytesBuffer->resize(uiTemp+pBinaryBlock->GetFilledSize());
			memcpy(&pBytesBuffer->front()+uiTemp, pBinaryBlock->GetDataPtr(), pBinaryBlock->GetFilledSize());

			pBinaryBlock=pBinaryBlock->GetNextItem();
		}

	}

protected:
	///���������� �������� ����
	CBinaryBlock<BlockSize>* GetHeadBinaryBlock(void){return m_pHeadBinaryBlock;};

	///��������� CPosBinaryBlock � �����
	void AddBinaryBlock(void)
	{
		CBinaryBlock<BlockSize>* pTempBinaryBlock=new CBinaryBlock<BlockSize>();
		if(!m_pHeadBinaryBlock){
			m_pHeadBinaryBlock=m_pTailBinaryBlock=pTempBinaryBlock;
		}else{
			m_pTailBinaryBlock->SetNextItem(pTempBinaryBlock);
			m_pTailBinaryBlock=pTempBinaryBlock;
		}

		m_BinaryBlocksNumber++;
	};
	///���������� CPosBinaryBlock � �����
	void PopBinaryBlock(void){};

	///�������� ����
	CBinaryBlock<BlockSize>* m_pHeadBinaryBlock;
};

//--------------------------------------------------------------------//

}
}
}
}
}