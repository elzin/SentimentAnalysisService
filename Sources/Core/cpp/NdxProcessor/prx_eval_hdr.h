#pragma once

#include ".\prx_eval.h"
#include ".\prx_eval_tbl.h"
#include ".\res_containers.h"
#include ".\hdr_containers.h"
#include ".\index_storage_hdr.h"
#include ".\index_storage_tbl.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Extracting
{
namespace Logics
{

//--------------------------------------------------------------------//

///����������� �������� ������������ � ������ ����������� ������ � ����������
///�������� ������ �� ��������� ������ �� ����������
///��������� �������� �������� ���� ������������� � ������ ���������� ���������
///� ����������� ���������� ������� ����������� � ����������� �� ���������
template <class TBaseEvaluator>
class CProximityEvaluator_Hdr : public TBaseEvaluator
{
public:
	CProximityEvaluator_Hdr(Containers::CFindResultCollection* pFindResultCollection, 
			Storages::CIndexStorageHeaders* pIndexStorageHeaders, 
			unsigned int uiEvaluatorID, 
			bool bCheckSequence, 
			SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory* pContainersFactory) :
		TBaseEvaluator(uiEvaluatorID, bCheckSequence, pContainersFactory),
		m_pFindResultCollection(pFindResultCollection), m_pHeadersTree(NULL), 
		m_pIndexStorageHeaders(pIndexStorageHeaders), m_uiCurrentHeadersWordsCount(0), 
		m_uiCurrentDocumentIndex(0), m_bAllWordsInHeader(false)
	{
	};

	virtual ~CProximityEvaluator_Hdr(void)
	{
		if(m_pHeadersTree) delete m_pHeadersTree;
	
		TIndexPositions::iterator itIndexPositions=m_IndexPositions.begin();
		while(itIndexPositions!=m_IndexPositions.end()){
			delete itIndexPositions->second;
			itIndexPositions++;
		}

	}

	///��������� ��� �� �������� � ������� ������������ �������� � �����������
	void Evaluate(unsigned int uiEvalID)
	{
		if(ISNULL(m_pIndexStorageHeaders)) return;
		if(ISNULL(m_pFindResultCollection)) return;
		
		m_uiCurrentDocumentIndex=m_uiDocumentBasisIndex+uiEvalID;
		//ToConsole(L"m_uiCurrentDocumentIndex", m_uiCurrentDocumentIndex);
		
		int a=0;
		if(m_uiCurrentDocumentIndex==43660){
			a=43660;
		}

		//�������� ��������������� ��������� ������
		CFindResult* pFindResult=m_pFindResultCollection->GetFindResult(m_uiCurrentDocumentIndex);
		if(ISNULL(pFindResult)) return;

		//������ ������ ���������� ���������
		FillHeadersTree(pFindResult);

		//������� ������, �������� ����� ����������, ���������� �� ������ ���������� �����������
		//������� ��� ������� ��������, ���������� ����� �����, ������ ��������� � ���������, 
		//����������� �������� � ������ ������������ �����������
		if(m_pHeadersTree->MoveFirstBranch()){

			SHeaderPositions HeaderPositions;
			CHeaderWords<CHeaderLogic::MaxBlockCount> TotalHeaderWords;
			CHeaderNode* pLowerHeaderNode=NULL; 

			do{
				//�������� �������������� ���� ������� ����� � ������� ���� �����
				pLowerHeaderNode=m_pHeadersTree->GetCurrentLastHeaderAndWordsIDs(&TotalHeaderWords);
				if(!pLowerHeaderNode) break;

				ResetEvaluatedChildsNumber();

				//���������� ����� ����� ������ ���������� � ���������� ��������
				m_bAllWordsInHeader=true;
				TChildCollection::iterator itSP=m_ChildCollection.begin();
				unsigned int i=0;
				m_uiCurrentHeadersWordsCount=0;
				while(itSP!=m_ChildCollection.end()){	
					if((*itSP)){
						(*itSP)->SetEvaluated(!TotalHeaderWords.IsWordExist(i));
						if(TotalHeaderWords.IsWordExist(i)) ++m_uiCurrentHeadersWordsCount;
						else m_bAllWordsInHeader=false;
					}
					++itSP; ++i;
				}
				
				if(m_uiCurrentHeadersWordsCount!=0){
					//��������� ������� �� �������� ���������
					m_pIndexStorageHeaders->FillHeaderPositions(m_uiCurrentDocumentIndex, 
						pLowerHeaderNode->GetMyself()->GetHeaderID(), &HeaderPositions);
					
					//������������� ������� � ������������� ������� ���������
					m_CurrentBoundInterval.m_uiHeadPos=HeaderPositions.m_uiTailPosition;
					m_CurrentBoundInterval.m_uiTailPos=HeaderPositions.m_uiBoundPosition;
					CLevelHeaderID* pHeaderID=pLowerHeaderNode->GetMyself()->GetHeaderID();
					m_CurrentBoundInterval.m_HeaderID=(*pHeaderID);
					
					if(m_bAllWordsInHeader){
						//���� ��� ����� � ���������, ��������� �������������� �������� ������������� ���������
						AddInterval(m_CurrentBoundInterval.m_uiHeadPos, m_CurrentBoundInterval.m_uiHeadPos);
					}else{
						//��������� �������� �������� ���� � �������� ��������
						TBaseEvaluator::Evaluate(uiEvalID);
					}
				}
			}while(m_pHeadersTree->MoveNextBranch());
		}else{
			//���� ���������� ���, ��������� ������� �����
			m_CurrentBoundInterval.m_uiHeadPos=0;
			m_CurrentBoundInterval.m_uiTailPos=EMPTY_VALUE;

			//��������� �������� �������� ���� � �������� ��������
			TBaseEvaluator::Evaluate(uiEvalID);
		}
	}

protected:

	///���������� ��� ���������
	unsigned int GetIntervalWeight(Containers::CInterval* pInterval)
	{
		if(m_bAllWordsInHeader){
			//���� ��� ����� � �������� �������� ���������� �������������
			//����� �������� �� ������
			return 100;
		}else{
			return TBaseEvaluator::GetIntervalWeight(pInterval);
		}
	}

	//���������� ��� ������������ ��������� ������ �������� � ������ ���������
	unsigned char GetHeaderDistanceWeight(unsigned int uiDistanceToHeader)
	{
		//��� ��������� ������� �� ������� ���������� ����� � ��������� �����
		//����� ��� ���������� ������������� (����������) ������� ���������

		if((int)uiDistanceToHeader<0 || uiDistanceToHeader>m_uiMaxIntervalLength) return 0;
		
		//������ 128 ������� �������
		if(uiDistanceToHeader==0)
			return 100;
		else
		if(uiDistanceToHeader<=2)
			return 98;
		else
		if(uiDistanceToHeader<=5)
			return 90;
		else
		if(uiDistanceToHeader<=7)
			return 85;
		else
		if(uiDistanceToHeader<=10)
			return 70;
		else
		if(uiDistanceToHeader<=12)
			return 65;
		else
		if(uiDistanceToHeader<=20)
			return 55;
		else
		if(uiDistanceToHeader<=40)
			return 30;
		else
		if(uiDistanceToHeader<=60)
			return 20;
		else
		if(uiDistanceToHeader<=80)
			return 10;
		else
		if(uiDistanceToHeader<=100)
			return 5;
		else
		if(uiDistanceToHeader<=m_uiMaxIntervalLength)
			return 2;
		else
			return 0;
	}
	
	///��������� ��������� �������� � ���������
	void FillIndexPositions(void)
	{
		if(m_IndexPositions.empty()){
			//���������� ��������� ������� ����, �������� ������� ����, ������� �������� ��������������� ������� 
			TChildCollection::iterator itSP=m_ChildCollection.begin();
			Containers::CWord::TIndexPositionsCollection* pIndexesCollection=NULL;
			while(itSP!=m_ChildCollection.end()){	
				if((*itSP)){
					pIndexesCollection=(*itSP)->GetIndexesCollection();
					Containers::CWord::TIndexPositionsCollection::iterator itIndex=pIndexesCollection->begin();		
					while(itIndex!=pIndexesCollection->end()){
						//�������� ������
						TIndexPositions::iterator itIndexPositions=m_IndexPositions.find(itIndex->first);
						if(itIndexPositions==m_IndexPositions.end()){
							itIndexPositions=m_IndexPositions.insert(TIndexPositions::value_type(itIndex->first, new TPositions())).first;
						}

						//������ ������� �������
						itIndexPositions->second->push_back((*itSP)->GetID());
					
						itIndex++;
					}
				}
				++itSP;
			}
		}
	}

	///��������� ������ ����������
	void FillHeadersTree(Containers::CFindResult* pFindResult)
	{
		if(ISNULL(pFindResult)) return;
		
		FillIndexPositions();

		if(m_pHeadersTree) delete m_pHeadersTree;

		//������ ������ ���������� ���������
		m_pHeadersTree=new CHeadersTree(pFindResult->GetTextIndex());

		//���������� ������� �����������, �������� �� ���, �������� ��������������� ����������
		//�� ����������, ��������� � ������ ������� ������� (������������� �����) � ��������� HID
		TIndexPositions::iterator itIndexPositions=m_IndexPositions.begin();
		CFindResult::THIDCollection* pHIDCollection=NULL;
		while(itIndexPositions!=m_IndexPositions.end()){
			//�������� ��������� ��������������� ���������� �� �������
			pHIDCollection=pFindResult->GetHIDCollection(itIndexPositions->first);
			if(pHIDCollection){
				m_pHeadersTree->AddNodes(itIndexPositions->second, pHIDCollection);
			}
			itIndexPositions++;
		}
		
		//if(m_uiCurrentDocumentIndex==17383)
		//m_pHeadersTree->View();
	}

	///��������� ����������� ������
	Containers::CFindResultCollection* m_pFindResultCollection;
	///��������� ��������� ����������
	Storages::CIndexStorageHeaders* m_pIndexStorageHeaders;

	///������� ������ ����������
	Containers::CHeadersTree* m_pHeadersTree;
	///������� ��������������� ��������, �������������� ��������� �� ������ �������� �� ��� �������
	Containers::CIntervalAndHeader m_CurrentBoundInterval;
	///���������� ���� � ������� ����� ����������
	unsigned int m_uiCurrentHeadersWordsCount;
	///������� ������ ���������
	unsigned int m_uiCurrentDocumentIndex;
	///���� ���� ��� ��� ����� � ���������
	bool m_bAllWordsInHeader;

	typedef vector<unsigned int> TPositions;
	typedef map<unsigned int, TPositions*> TIndexPositions;
	///��������� �������� � ��������� � ��������������, ����������� ��� ������� ���������� �����������
	///� ������ ������� �������� ����� ����������
	TIndexPositions m_IndexPositions;
};

//--------------------------------------------------------------------//

///����������� �������� ���� � ������� � ������ ����������
class CProximityEvaluator_HdrText : public CProximityEvaluator_Hdr<CProximityEvaluator_Text>
{
public:
	CProximityEvaluator_HdrText(Containers::CFindResultCollection* pFindResultCollection, Storages::CIndexStorageHeaders* pIndexStorageHeaders, unsigned int uiEvaluatorID, bool bCheckSequence, SS::Core::NdxSE::NdxProcessor::Containers::CContainersFactory* pContainersFactory)
		:CProximityEvaluator_Hdr<CProximityEvaluator_Text>(pFindResultCollection, pIndexStorageHeaders, uiEvaluatorID, bCheckSequence, pContainersFactory){};

protected:
	///������� �������� ����������
	Containers::CInterval* CreateInterval(unsigned int uiHeadPos, unsigned int uiTailPos);
};

//--------------------------------------------------------------------//

///����������� �������� ���� � ������� � ������ ����������
class CProximityEvaluator_HdrTable : public CProximityEvaluator_Hdr<CProximityEvaluator_Table>
{
public:
	CProximityEvaluator_HdrTable(
		Storages::CIndexStorageTables* pIndexStorageTables,
		Containers::CFindResultCollection* pFindResultCollection, 
		Storages::CIndexStorageHeaders* pIndexStorageHeaders, 
		unsigned int uiEvaluatorID, bool bCheckSequence, 
		Containers::CContainersFactory* pContainersFactory)
		:CProximityEvaluator_Hdr<CProximityEvaluator_Table>(pFindResultCollection, pIndexStorageHeaders, uiEvaluatorID, bCheckSequence, pContainersFactory), m_pIndexStorageTables(pIndexStorageTables){};

protected:
	///������� ���������
	Containers::CInterval* CreateInterval(unsigned int uiTableIndex, unsigned int uiRowIndex);
	
	///��������� ��������� ������
	Storages::CIndexStorageTables* m_pIndexStorageTables;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}
