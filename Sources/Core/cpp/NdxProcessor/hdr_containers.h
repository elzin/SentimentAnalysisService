#pragma once

#include ".\const.h"
#include ".\console.h"
#include ".\res_containers.h"
#include ".\hdr_logic.h"
#include ".\int_containers.h"

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

///���������� �� ������������ ���������
#pragma pack(push,1)  // Fix packing size 
struct SHeaderPositions
{
	SHeaderPositions(void):m_uiHeadPosition(EMPTY_VALUE), m_uiTailPosition(EMPTY_VALUE), m_uiBoundPosition(EMPTY_VALUE){};

	///���������� ����� ���������
	unsigned int GetHeaderLength(void){return m_uiTailPosition-m_uiHeadPosition;};
	///���������� ����� ���� ������� ���������
	unsigned int GetAffectedZoneLength(void){return m_uiBoundPosition-m_uiTailPosition;};

	///������������ � ������
	void ToString(wstring& wszValue)
	{
		wchar_t buf[100];
		wsprintf(buf, L"Head: %u, Tail: %u, Bound: %u", m_uiHeadPosition, m_uiTailPosition, m_uiBoundPosition);
		wszValue.assign(buf);
	};

	///�������� ������� (������)
	unsigned int m_uiHeadPosition;
	///��������� ������� (�����)
	unsigned int m_uiTailPosition;
	///��������� ������� (������������ ������� ���� ������� ���������)
	///EMPTY_VALUE �������� �������� �������� ����� ���������
	unsigned int m_uiBoundPosition;
};
#pragma pack(pop)

//--------------------------------------------------------------------//

///����� �������������� ���������, ��������� �������� ���������� ������� ����������
#pragma pack(push,1)  // Fix packing size 
template <unsigned int LevelsNumber>
class CHeaderID
{
public:
	CHeaderID(void){Reset();};
	CHeaderID(unsigned int uiHeaderID)
	{
		Reset();
		
		unsigned short* pucValue=(unsigned short*)&uiHeaderID;
		unsigned int uiLevelsNumber=0;
		do{
			m_arrHeaderLevels[LevelsNumber-(uiLevelsNumber+1)]=*pucValue;
			pucValue++;
		}while(++uiLevelsNumber<LevelsNumber);
	};

	void operator=(const CHeaderID& HeaderID)
	{
		memcpy(m_arrHeaderLevels, HeaderID.m_arrHeaderLevels, LevelsNumber*sizeof(unsigned short));
	};

	bool operator==(const CHeaderID& HeaderID) const
	{
		return memcmp(m_arrHeaderLevels, HeaderID.m_arrHeaderLevels, LevelsNumber*sizeof(unsigned short))==0?true:false;
	};

	///�������� ������ ���������� ������ �� ����� ��������� �������
	bool operator<(const CHeaderID& HeaderID) const
	{
		unsigned int uiLevelNumber=0;
		unsigned int uiLeftValue=0;
		unsigned int uiRightValue=0;
		do{
			uiLeftValue=GetValueAtLevel(uiLevelNumber);
			uiRightValue=HeaderID.GetValueAtLevel(uiLevelNumber);
			if(uiRightValue==0 && uiLeftValue!=0) return true;
		}while(++uiLevelNumber<LevelsNumber);
		
		return false;
	};

	///���������� ���������� �������������� ���������
	void Reset(void){memset(m_arrHeaderLevels, 0, LevelsNumber*sizeof(unsigned short));};
	///��������� ������������� ��������� �� ������
	bool IsEmpty(void){return m_arrHeaderLevels[0]==0?true:false;};
	
	///������� �� �������� ������������ ���������
	CHeaderID MakeParentHeader(void)
	{
		CHeaderID HeaderID(GetID());
		unsigned int uiLevelNumber=LevelsNumber;
		while(uiLevelNumber--!=0){
			if(HeaderID.m_arrHeaderLevels[uiLevelNumber]!=0){
				HeaderID.m_arrHeaderLevels[uiLevelNumber]=0;
				break;
			}
		}
		return HeaderID;
	};

	///���������� ������� ���������
	unsigned int GetHeaderLevel(void)
	{
		unsigned int uiLevelNumber=LevelsNumber;
		while(uiLevelNumber--!=0){
			if(m_arrHeaderLevels[uiLevelNumber]!=0)	return uiLevelNumber;
		}
		return EMPTY_VALUE;
	};

	///����������� �������� �������������� ��������� �� ������� ������
	void IncAtLevel(unsigned int uiLevelValue)
	{
		if(uiLevelValue<LevelsNumber){
			//����������� ������� �������� ������
			m_arrHeaderLevels[uiLevelValue]++;
			//���������� ��� ������
			while(++uiLevelValue<LevelsNumber) m_arrHeaderLevels[uiLevelValue]=0;
		}else{
			TO_CONSOLE(L"Too big level number!!!");
			ToConsole(L"uiLevelValue", uiLevelValue);
		}
	};

	///���������� �������� �������������� ���������
	unsigned int GetID(void)
	{
		unsigned int uiValue=0;
		unsigned int uiLevelsNumber=0;
		do{
			uiValue|=((unsigned int)m_arrHeaderLevels[uiLevelsNumber])<<(LevelsNumber-(uiLevelsNumber+1))*16;
		}while(++uiLevelsNumber<LevelsNumber);
		return uiValue;
	};
	
	///��������� �������� �� ������������� ������������� �� ������ ������
	bool IsAtSameLevel(CHeaderID* pHeaderID)
	{
		if(ISNULL(pHeaderID)) return false;
		unsigned int uiLevelNumber=0;
		unsigned int uiLeftValue=0;
		unsigned int uiRightValue=0;
		do{
			uiLeftValue=GetValueAtLevel(uiLevelNumber);
			uiRightValue=pHeaderID->GetValueAtLevel(uiLevelNumber);
			if(!((uiRightValue==0 && uiLeftValue==0) ||
				(uiRightValue!=0 && uiLeftValue!=0))) return false;
		}while(++uiLevelNumber<LevelsNumber);

		return true;
	};

	///���������� �������� �� �������� ������
	unsigned int GetValueAtLevel(unsigned int uiLevelValue) const
	{
		if(uiLevelValue>=LevelsNumber){
			TO_CONSOLE(L"Too big level number!!!");
			ToConsole(L"uiLevelValue", uiLevelValue);
			return 0;
		}else{
			return m_arrHeaderLevels[uiLevelValue];
		}
	};
	
	///���������� ������������� �������� ��������� �� ������������ �� ������������� ������
	///���������� ��� �� ������� ���������
	unsigned int GetIDTillLevel(unsigned int uiLevelValue)
	{
		if(uiLevelValue>=LevelsNumber){
			TO_CONSOLE(L"Too big level number!!!");
			ToConsole(L"uiLevelValue", uiLevelValue);
			return 0;
		}

		unsigned int uiValue=0;
		unsigned int uiLevelsNumber=0;
		do{
			uiValue|=((unsigned int)m_arrHeaderLevels[uiLevelsNumber])<<(LevelsNumber-(uiLevelsNumber+1))*16;
		}while(++uiLevelsNumber<=uiLevelValue);
		return uiValue;
	};

	///������������ � ������
	void ToString(wstring& wszValue)
	{
		wchar_t buf[100];
		wszValue.assign(L"HID: ");
		unsigned int uiLevelNumber=0;
		do{
			wsprintf(buf, L"%u ", GetValueAtLevel(uiLevelNumber));
			wszValue.append(buf);
		}while(++uiLevelNumber<LevelsNumber);
	};

	///����������� ������� ������
	void View(void)
	{
		wstring wszValue;
		ToString(wszValue);
		ToConsole(wszValue.c_str());
	};

protected:
	///������ ������������ �������������� ���������
	unsigned short m_arrHeaderLevels[LevelsNumber];
};
#pragma pack(pop)

typedef CHeaderID<cuiHeaderLevelsNumber> CLevelHeaderID;

//--------------------------------------------------------------------//

///���������� � ���������
#pragma pack(push,1)  // Fix packing size 
struct SHeaderInfo
{
	void operator=(const SHeaderInfo& HeaderInfo)
	{
		m_HeaderID=HeaderInfo.m_HeaderID;
		memcpy((unsigned char*)&m_HeaderPositions, (unsigned char*)&HeaderInfo.m_HeaderPositions, sizeof(SHeaderPositions));
	};

	///������������ � ������
	void ToString(wstring& wszValue)
	{
		wszValue.assign(L"SHeaderInfo: ");
		wstring wszTemp;
		m_HeaderID.ToString(wszTemp);
		wszValue.append(wszTemp);

		m_HeaderPositions.ToString(wszTemp);
		wszValue.append(wszTemp);
	};

	///������������� ���������
	CLevelHeaderID m_HeaderID;
	///���������� �� ������������ ���������
	SHeaderPositions m_HeaderPositions;
};
#pragma pack(pop)

//--------------------------------------------------------------------//

///���������� �� ���������� ���������
class CDocumentHeadersInfo : public CConsoleClient
{
public:
	///��������� ���������� ���������
	typedef vector<SHeaderInfo> THeaderInfoCollection;
	
	///��������� ������� ��������� �� �������������� ���������
	void UpdateHeaderPosition(unsigned int uiPosition);
	///���������� ��������� ���������� ���������
	THeaderInfoCollection* GetHeaderInfoCollection(void){return &m_HeaderInfoCollection;};
	///���������� ���������� 
	void Reset(void){m_CurrentHeaderID.Reset(); m_HeaderInfoCollection.clear();};
	///���������� ������������� �������� ���������
	CLevelHeaderID* GetCurrentHeaderID(void){return &m_CurrentHeaderID;};
	///�������������� ������������� �������� ��������� �� ������ ������
	bool IncCurrentHeaderID(unsigned int uiHeaderLevel);

	///������������ � ������
	void ToString(wstring& wszValue);

protected:
	///������������� �������� ���������
	CLevelHeaderID m_CurrentHeaderID;
	///��������� ���������� ���������
	THeaderInfoCollection m_HeaderInfoCollection;
};

//--------------------------------------------------------------------//

//��������� ����� ���������, �������� �������� ������
//������� ��������� ����� � ������ ���������������� ���� � ���������
template <unsigned int WordsNumber>
class CHeaderWords
{
public:
	CHeaderWords(void){Reset();};

	///���������� ���� ����������� �����
	void SetWordID(unsigned int uiWordID)
	{
		if(uiWordID<WordsNumber){
			m_arrWordsIDs[uiWordID]=true;
		}
	};
	///���������� ���������� 
	void Reset(void){memset(m_arrWordsIDs, 0, WordsNumber);};
	///���������� ������������� ���������
	CLevelHeaderID* GetHeaderID(void){return &m_HeaderID;};
	///���������� ������������ ���������� ����
	unsigned int GetMaxWordsNumber(void){return WordsNumber;}
	///��������� ���� �� ����� � ����� ���������������
	bool IsWordExist(unsigned int uiWordID)
	{
		if(uiWordID<WordsNumber){
			return m_arrWordsIDs[uiWordID];
		}
		return false;
	};

	///������������ � ������
	void ToString(wstring& wszValue)
	{
		wchar_t buf[100];
		wszValue.assign(L"CHeaderWords: ");
		wstring wszTemp;
		m_HeaderID.ToString(wszTemp);
		wszValue.append(wszTemp);
		wszValue.append(L" WordIDs: ");
		for(unsigned int k=0; k<GetMaxWordsNumber(); k++){
			if(IsWordExist(k)){
				wsprintf(buf, L"%u ", k);
				wszValue.append(buf);
			}
		}
	};

protected:
	///�������� ������
	bool m_arrWordsIDs[WordsNumber];
	///������������� ���������
	CLevelHeaderID m_HeaderID;
};

//--------------------------------------------------------------------//

///���� ������ ����������, �������� ����� ���������
///� ���� ���� �����, ����������� ���������
class CHeaderNode : public CConsoleClient,
	public CTreeNode< CHeaderWords<Extracting::Logics::CHeaderLogic::MaxBlockCount>* >
{
public:
	CHeaderNode(CLevelHeaderID* pHeaderID);

	//��������� ����������� ���� 
	void InsertHeaderNode(unsigned int uiWordID, CLevelHeaderID* pHeaderID);
	//���������� ������� ���������
	unsigned int GetHeaderLevel(void){return GetDepth();};
	///������������ � ������
	void ToString(wstring& wszValue, wstring wszOffset);
	///������������ � ������
	void ToString(wstring& wszValue){
		wstring wszOffset;
		ToString(wszValue, wszOffset);
	};
};

//--------------------------------------------------------------------//

///������ ���������� ���������, 
//�������� ���� ��������� � �������� �� ����������
class CHeadersTree : public CConsoleClient
{
public:
	///����� ������ ����������
	typedef vector<CHeaderNode*> THeadersBranch;

	CHeadersTree(unsigned int uiDocumentIndex);
	virtual ~CHeadersTree(void);

	///������ ������ �� ��������� ���� � �����������
	//void BuildTree(CFindResult::TBlockHIDCollection* pBlockHIDCollection);
	///��������� ���� � ������
	void AddNodes(vector<unsigned int>* pWordIDCollection, CFindResult::THIDCollection* pHIDCollection);

	///��������������� �� ��������� ����� ������
	bool MoveFirstBranch(void);
	///��������� � ��������� ����� ������
	bool MoveNextBranch(void);
	///���������� �������������� ���� ������� ����� � ������� ���� �����
	CHeaderNode* GetCurrentLastHeaderAndWordsIDs(CHeaderWords<Extracting::Logics::CHeaderLogic::MaxBlockCount>* pHeaderBranchWords);

	///������������ � ������
	void ToString(wstring& wszValue);

protected:

	///������������� ���������
	const unsigned int m_uiDocumentIndex;
	///�������� ����, ������� ���������
	CHeaderNode* m_pRootNode;
	///������� ����� ����������
	THeadersBranch m_CurrentBranch;
};

//--------------------------------------------------------------------//

///��������� ��������� c ��������������� ���������
class CIntervalAndHeader : public CInterval 
{
public:
	CIntervalAndHeader(void){};
	CIntervalAndHeader(unsigned int uiHeadPos, unsigned int uiTailPos, unsigned int uiWeight = 0)
		:CInterval(uiHeadPos, uiTailPos, uiWeight){};

	void operator=(const CIntervalAndHeader& IntervalAndHeader)
	{
		m_HeaderID=IntervalAndHeader.m_HeaderID;
		m_uiHeadPos=IntervalAndHeader.m_uiHeadPos;
		m_uiTailPos=IntervalAndHeader.m_uiTailPos;
		m_uiWeight=IntervalAndHeader.m_uiWeight;
	};

	///������� ����� ������� ������
	CIntervalAndHeader* Clone(void)
	{
		CIntervalAndHeader* pIntervalAndHeader=new CIntervalAndHeader(m_uiHeadPos, m_uiTailPos, m_uiWeight);
		pIntervalAndHeader->m_HeaderID=m_HeaderID;
		return pIntervalAndHeader;
	}

	///������������� ���������
	CLevelHeaderID m_HeaderID;
};

//--------------------------------------------------------------------//

}
}
}
}
}
