#include "StdAfx.h"
#include ".\prx_eval_tbl.h"
#include <iterator>

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

using namespace SS::Interface::Core::CommonContainers;
using namespace SS::Core::NdxSE::NdxProcessor::Containers;
using namespace SS::Core::NdxSE::NdxProcessor::Extracting;

//--------------------------------------------------------------------//

CRowWords::CRowWords(unsigned int uiMaxWordsCount)
:m_uiMaxWordsCount(uiMaxWordsCount)
{
	Reset();
}

CRowWords::~CRowWords(void)
{
}

void CRowWords::SetWordID(unsigned int uiWordID, unsigned char ucCellID)
{
	//	�������� ������������ ��������
	if (uiWordID >= m_uiMaxWordsCount) return;
	//	��������� ����� � ������ � ������ ����������
	words_by_cell[ucCellID].insert(uiWordID);
	all_words.insert(uiWordID);
}

unsigned int	CRowWords::GetCellWordCount(unsigned int const _id_cell)
{
	//ToConsole(L"PRX_TBL:: GetCellWordCount");
	//	���� �� �������� ������?
	cell_collection::iterator		itf = words_by_cell.find(_id_cell);
	//	���� ����� ������ �� ������� �� ���������� 0
	if (itf == words_by_cell.end()) return 0;
	//	������ �������, ���������� ���������� ���� � ���
	return static_cast<unsigned int>(itf->second.size());
}

unsigned int CRowWords::GetUniqWordsCount(CRowWords* pRowWords1, CRowWords* pRowWords2)
{
	if(!pRowWords1 && !pRowWords2) return 0;
	if(!pRowWords1) return pRowWords2->GetCurrentWordsCount();
	if(!pRowWords2) return pRowWords1->GetCurrentWordsCount();
	
	if(pRowWords1->GetMaxWordsNumber()!=pRowWords2->GetMaxWordsNumber()){
		TO_CONSOLE(L"MaxWordsNumber not equal!!!");
		return 0;
	}

	//	��� ����� ������� ���� ������� � 1-� ������
	unsigned int uiInc = static_cast<unsigned int>(pRowWords1->all_words.size());
	//	�������� �� 2-� ������, ���� � �������� � 1-�. ���� �� ����� �� ����������� �������.
	for(word_collection::iterator	b = pRowWords2->all_words.begin(), e = pRowWords2->all_words.end(); b != e; ++b)
		//	���� ������� ������� ������� �� ������� � �����, ������ �� ����������, ����������� �������
		if (pRowWords1->all_words.find(*b) == pRowWords1->all_words.end()) ++uiInc;

	return uiInc;
}


bool	CRowWords::IsCrossRelevance(
	CRowWords*			_pCapRow, 
	CRowWords*			_pRow)
{
	//ToConsole(L"PRX_TBL: CRowWords::IsCrossRelevance\n");
	//	���� ��� ����� ��� ������ �� ������������� �� �����
	if ((_pCapRow == NULL) || (_pRow == NULL)) return false;
	//	������������ ���������� ���� � ����� � � ������ ������ ���� �����������
	if (_pCapRow->GetMaxWordsNumber() != _pRow->GetMaxWordsNumber()) return false;
	//	������������ ���������� ���� ����� ����� �� ������ ���� ����
	if (_pCapRow->GetMaxWordsNumber() == 0) return false;
	//	���� ������ � ����� ��������� �� ������������� �� �����
	if (_pCapRow == _pRow) return false;

	/*	���������� ����� ���� � ������� ����� � ������
	ToConsole(L"\nPRX_TBL: CRowWords::IsCrossRelevance: ������� �����\n");
	for (cell_collection::iterator	b = _pCapRow->words_by_cell.begin(), e = _pCapRow->words_by_cell.end();
		b != e;
		++b)
	{
		ToConsole(L"\n������: ", static_cast<unsigned int>(b->first));
		for (word_collection::iterator	b2 = b->second.begin(), e2 = b->second.end();
			b2 != e2;
			++b2)
		{
			ToConsole(L"\n����� � ������: ", static_cast<unsigned int>(*b2));
		}

	}

	ToConsole(L"\nPRX_TBL: CRowWords::IsCrossRelevance: ������� ������");
	for (cell_collection::iterator	b = _pRow->words_by_cell.begin(), e = _pRow->words_by_cell.end();
		b != e;
		++b)
	{
		ToConsole(L"\n������: ", static_cast<unsigned int>(b->first));
		for (word_collection::iterator	b2 = b->second.begin(), e2 = b->second.end();
			b2 != e2;
			++b2)
		{
			ToConsole(L"\n����� � ������: ", static_cast<unsigned int>(*b2));
		}
	}
	*/

	//	�������� �� ������� �����
	for (cell_collection::iterator it_cap_b = _pCapRow->words_by_cell.begin(), it_cap_e = _pCapRow->words_by_cell.end();
		it_cap_b != it_cap_e;
		++it_cap_b)
	{
		//	�������� �� ������ ������
		if (it_cap_b->second.empty()) continue;

		//	���� ����� ������ ����� ���� � ������� ������, ��������� � ��������� ������ �����
		if (_pRow->words_by_cell.find(it_cap_b->first) != _pRow->words_by_cell.end()) continue;

		//	�������� �� ������� ����������� ��������� ���� ������� � ����� � ��������� ���� ������.
		//	��������� ������� ����� ����� ���� � ����� � ����� ���� � ������, ��� �����. 
		//	���� ����� ���������� ���� � ������ � ����� ������� ������ ������� ���������� ����, 
		//	������� �����-������������� �� �����������, ��������� � ��������� ������ �����.
		if (it_cap_b->second.size()+			//	����� ���� � ����� �������
			_pRow->GetCurrentWordsCount()		//	����� ���� � ������
			< _pCapRow->GetMaxWordsNumber())	//	������ ������� ���������
				continue;	//	��������� � ��������� ������ �����

		//	��������� ������� ���������� ������ ���� ������ � ����� �������
		word_collection	words_union;	//	����������� ��������� ���� �� ����� ������� � ������

		//	���������� ����� ������ � ����� � ���� ���������
		std::set_union(
			it_cap_b->second.begin(),	//	����� ����� �������, ������
			it_cap_b->second.end(),		//	����� ����� �������, �����
			_pRow->all_words.begin(),	//	����� ������, ������
			_pRow->all_words.end(),		//	����� ������, �����
			std::inserter(words_union, words_union.begin()));

		//	���� ���������� ������ ��������� ���� �� ������������� ����
		if (words_union.size() == _pCapRow->GetMaxWordsNumber())
			return true;
	}

	return false;
}

//--------------------------------------------------------------------//

CTableTournament::CTableTournament(void) :
	m_uiTableIndex(EMPTY_VALUE), m_uiCurrentWordID(EMPTY_VALUE), 
	m_pCapRow(NULL), m_uiRaceWordsCount(EMPTY_VALUE), 
	m_uiCurrentRace(EMPTY_VALUE), m_uiAddedRowsPerRace(0)
{
}

CTableTournament::~CTableTournament(void)
{
	Reset();
}

void CTableTournament::Reset(void)
{
	//ToConsole(L"PRX_TBL: CTableTournament::Reset");
	m_uiTableIndex=EMPTY_VALUE;
	m_uiRaceWordsCount=EMPTY_VALUE;
	m_uiCurrentWordID=EMPTY_VALUE;
	m_uiCurrentRace=EMPTY_VALUE;
	m_uiAddedRowsPerRace=EMPTY_VALUE;
	m_pCapRow=NULL;

	TRowWordsCollection::iterator itRowWords=m_RowWordsCollection.begin();
	while(itRowWords!=m_RowWordsCollection.end()){
		delete itRowWords->second;
		++itRowWords;
	}
	m_RowWordsCollection.clear();
}

CRowWords* CTableTournament::GetCapRow(void)
{
	if(!m_pCapRow && !m_RowWordsCollection.empty()){
		if(m_RowWordsCollection.begin()->first==0)
			m_pCapRow=m_RowWordsCollection.begin()->second;
	}

	return m_pCapRow;
}

void CTableTournament::StartTournament(unsigned int uiTableIndex, unsigned int uiRaceWordsCount, unsigned int uiWordID)
{
	//ToConsole(L"PRX_TBL: CTableTournament::StartTournament");
	//ToConsole(L"CTableTournament::StartTournament", uiTableIndex);
	//ToConsole(L"CTableTournament::StartRace", uiWordID);

	Reset();
	//��������� ��������
	m_uiTableIndex=uiTableIndex;
	m_uiRaceWordsCount=uiRaceWordsCount;
	m_uiCurrentWordID=uiWordID;
	m_uiCurrentRace=0;
	m_uiAddedRowsPerRace=0;
}

bool CTableTournament::NextRace(unsigned int uiWordID)
{
	//ToConsole(L"CTableTournament::NextRace", uiWordID);
	//ToConsole(L"PRX_TBL: CTableTournament::NextRace");

	if(!m_uiAddedRowsPerRace){
		//���� � ���������� ����� �� ���� ���������� �� ����� ������
		//������ �����������
		Reset();
		return false;
	}else{
		//��������� ��������
		m_uiCurrentWordID=uiWordID;
		++m_uiCurrentRace;
		m_uiAddedRowsPerRace=0;
		return true;
	}
}

void CTableTournament::AddTrcID(Containers::CTrcID TrcID)
{
	//ToConsole(L"PRX_TBL: CTableTournament::AddTrcID");
	//!!!����� �������, ��� ������ � �������� 0
	//ToConsole(L"CTableTournament::AddTrcID");
	//TrcID.View();
	//ToConsole(L"RowID", TrcID.GetIDByType(CTrcID::etrcRow));

	bool stringExist = true;
	//�������� ������ � ���������� ������� �����
	TRowWordsCollection::iterator itRowWords=m_RowWordsCollection.find(TrcID.GetIDByType(CTrcID::etrcRow));
	if(itRowWords==m_RowWordsCollection.end()){
		if(TrcID.GetIDByType(CTrcID::etrcRow)==0 || !m_uiCurrentRace){
			//���� ����������� ����� ��� ����� ������ ����� ��������� ��� ��������
			itRowWords=m_RowWordsCollection.insert(TRowWordsCollection::value_type(
				TrcID.GetIDByType(CTrcID::etrcRow), new CRowWords(m_uiRaceWordsCount))).first;
		}else{
			//��� ������� ������ ��������� ��������

			//���� ����� ������ ��� ���������, ����� ����������� ����� ���� � ����� �������
			//����� �������, ��� ������ � �������� 0
			CRowWords* pCapRowWords=GetCapRow();
			if(pCapRowWords && pCapRowWords->GetCurrentWordsCount()==m_uiCurrentRace){
				//���� ����� ����, ��� ���������� �������� �����, ������ ���� � �����
				itRowWords=m_RowWordsCollection.insert(TRowWordsCollection::value_type(
					TrcID.GetIDByType(CTrcID::etrcRow), new CRowWords(m_uiRaceWordsCount))).first;
			}else stringExist = false;
		}
	}

	//���� ����� ������ ���� ��������� ���� ������������� ����� � ������
	if(stringExist){
		//��������� ��� ���������� ����� ������ ���� ��� � ������ ������ ��� � �����
		if(CRowWords::GetUniqWordsCount(GetCapRow(), itRowWords->second)==m_uiCurrentRace){
			itRowWords->second->SetWordID(m_uiCurrentRace, TrcID.GetIDByType(CTrcID::etrcCell));
			//������ ���������, ����������� �������
			++m_uiAddedRowsPerRace;
		}
	}
}

//--------------------------------------------------------------------//

CProximityEvaluator_Table::CProximityEvaluator_Table(unsigned int uiEvalID, bool bCheckSequence, CContainersFactory* pContainersFactory)
:CRelevanceEvaluator(uiEvalID, bCheckSequence, pContainersFactory)
{
	m_itCurrentRowWords = m_NullCollection.end();
}

CProximityEvaluator_Table::~CProximityEvaluator_Table(void)
{
}

Containers::CInterval* CProximityEvaluator_Table::CreateInterval(unsigned int uiTableIndex, unsigned int uiRowIndex)
{
	//� ������ ����������� � ����������� ��������
	//���������� ������ � �������, ������� � �������� ����������
	//������ ������� � ������� ������ � ���� �������
	return new CInterval(uiTableIndex, uiRowIndex);
}

unsigned int CProximityEvaluator_Table::GetIntervalWeight(Containers::CInterval* pInterval)
{
	if(ISNULL(pInterval)) return 0;
	unsigned int uiIntervalLength=pInterval->GetLength();

	//��� ���������� ��� ������ ��� ������ ���� ������� ��������� � ����� ������ ������ �������, 
	//�� ���� ������������ ����������� ���� �������, ����������� � ������� �
	//����������� ������ ������, � ������� ��� ������������
	
	if(m_itCurrentRowWords==m_NullCollection.end()) return 0;

	unsigned int uiEvaluatedWordsCount=GetEvaluatedChildsNumber();
	CRowWords* pCapRow=m_TableTournament.GetCapRow();

	if(m_itCurrentRowWords->first==0){
		//��� ����� ��������� ������� ������ ���� � ��� ��������� ��� �����
		if(m_itCurrentRowWords->second->GetCurrentWordsCount()!=GetEvaluatedChildsNumber())
			return 0;
	}else{
		//���� ������ �� �����, ��������� ��� ��� ����� ������� ���������
		//���� � ������ ���� � �����
		if(CRowWords::GetUniqWordsCount(pCapRow, m_itCurrentRowWords->second)!=uiEvaluatedWordsCount)
			return 0;
		
		//���� ������ �� �����, � ����� ���� � �����, 
		//���������� ��� ��� ������������ � ������ ��� ��� ���� ������
		//���� ��� ��������� �������������

		//	���� ���� �����-�������������, ����� ����� ������� �������������
		if (CRowWords::IsCrossRelevance(pCapRow, m_itCurrentRowWords->second))
		{
			//ToConsole(L"PRX_TBL: CrossRelevance FOUND!!!!!!!!!");
			return 250;
		}
	}

	unsigned int uiCellsCount=(unsigned int)m_itCurrentRowWords->second->GetCellsCount();
	
	if(uiCellsCount==0) return 0;

	float fFillKoef=(float)uiCellsCount/(float)uiEvaluatedWordsCount;

	if(fFillKoef>=0.9)
		return 200;
	else
	if(fFillKoef>=0.7)
		return 180;
	else
	if(fFillKoef>=0.5)
		return 160;
	else
	if(fFillKoef>=0.3)
		return 140;
	else
	if(fFillKoef>0.0)
		return 120;
	else
		return 0;
}

bool CProximityEvaluator_Table::PrepareEvaluation(unsigned int uiEvalID)
{
	m_SortedChildCollection.clear();
	m_SequenceCollection.Init();

	if(m_ChildCollection.empty()){
		TO_CONSOLE(L"Common positions not exist");
		return false;
	}

	//ToConsole(L"uiEvalID", uiEvalID);

	TChildCollection::iterator itSP=m_ChildCollection.begin();
	unsigned int uiRangeID;
	do{
		if((*itSP) && (*itSP)->IsEvaluated()){
			//������� ������� ������ ��� ���� ������ ��������� � �����������
			(*itSP)->ClearPositions();

			uiRangeID=(*itSP)->PrepareMakeCommonPositions(uiEvalID);
			if(uiRangeID==0) return false;
				
			//����� �� �������� ��� ����������� � ����� �� ������ �������, ������ ������ ����
			while(m_SortedChildCollection.find(uiRangeID)!=m_SortedChildCollection.end()){
				++uiRangeID;
			}
			//��������� � ���������
			m_SortedChildCollection.insert(TSortedChildCollection::value_type(uiRangeID, (*itSP)));
		}
	}while(++itSP!=m_ChildCollection.end());

	return !m_SortedChildCollection.empty();
}

void CProximityEvaluator_Table::Evaluate(unsigned int uiEvalID)
{
	unsigned char ucStep=0;
	try{
		bool bResult=false;
		ucStep=0;

		//ToConsole(L"//---------------------");
		//ToConsole(L"DocumentIndex", uiEvalID+m_uiDocumentBasisIndex);

		m_TableTournament.Reset();

		ucStep=1;
		//���������� ������ ����� � �� ���� ������� ��������� �����
		START_TICK(L"CProximityEvaluator_Table::PrepareEvaluation");		
		bResult=PrepareEvaluation(uiEvalID);
		STOP_TICK(L"CProximityEvaluator_Table::PrepareEvaluation");		
		if(!bResult) return;
		
		//�� ������� ���������� ����� ����������� ��������� ����� TRC-���������������
		TSortedChildCollection::iterator itSSP=m_SortedChildCollection.begin();
		if(!itSSP->second) return;	
		START_TICK(L"MakeCommonPositions");
		itSSP->second->MakeCommonPositions(uiEvalID, EMPTY_VALUE, EMPTY_VALUE);
		STOP_TICK(L"MakeCommonPositions");
		//itSSP->second->View();
		
		ucStep=2;
		//���������������, ���������� ��������� ���������� ���� � ���������� �������
		//����� ������ ���������� � ����� �������, � ����� ������, 
		//� ��� ������ ���� � ����� ������ ��� �����.
		CWord::TCommonPositions* pCommonPositions=itSSP->second->GetCurrentPositions();
		CWord::TCommonPositions::iterator itTRC=pCommonPositions->begin();
		while(itTRC!=pCommonPositions->end()){
			itSSP=m_SortedChildCollection.begin();

			//���������� ��������� ����� �������� �������
			CTrcID HeadTrcIDMask(*itTRC);
			HeadTrcIDMask.SetIDByType(CTrcID::etrcCell, 0);
			HeadTrcIDMask.SetIDByType(CTrcID::etrcRow, 0);
			//HeadTrcIDMask.View();

			CTrcID TailTrcIDMask(*itTRC);
			TailTrcIDMask.SetIDByType(CTrcID::etrcCell, 0xff);
			TailTrcIDMask.SetIDByType(CTrcID::etrcRow, 0xffff);
			//TailTrcIDMask.View();
		
			ucStep=3;
			
			//�������� ������
			m_TableTournament.StartTournament(HeadTrcIDMask.GetIDByType(CTrcID::etrcTable), GetEvaluatedChildsNumber(), itSSP->second->GetID());
			
			while(itTRC!=pCommonPositions->end()){
				CTrcID TempTrcID(*itTRC);
				if(HeadTrcIDMask.GetIDByType(CTrcID::etrcTable)!=TempTrcID.GetIDByType(CTrcID::etrcTable)) break;
				//��������� ��� ������ ������ �������
				//TempTrcID.View();
				m_TableTournament.AddTrcID(TempTrcID);
				++itTRC;
			}
			ucStep=4;
			
			if(++itSSP!=m_SortedChildCollection.end()){
				//�������� �� ��������� ������
				do{
					if(itSSP->second){
						if(!m_TableTournament.NextRace(itSSP->second->GetID())){
							//���� ������ ���������� ������ ��������� ����������
							break;
						}

						//��������� TRC-�������������� � ������ ��������� �����
						START_TICK(L"MakeCommonPositions");
						itSSP->second->MakeCommonPositions(uiEvalID, HeadTrcIDMask.GetTrcID(), TailTrcIDMask.GetTrcID());
						STOP_TICK(L"MakeCommonPositions");
						//itSSP->second->View();
						
						if(itSSP->second->GetCurrentPositions()->empty()){ 
							//���� ���� �� � ������ ����� ���, ������ TRC-���������������, ��������� ����������
							m_TableTournament.Reset();
							break;
						}
						
						//������� ������� ����� � ����� ���������
						CWord::TCommonPositions::iterator itTempTRC=itSSP->second->GetCurrentPositions()->begin();
						while(itTempTRC!=itSSP->second->GetCurrentPositions()->end()){
							m_TableTournament.AddTrcID(CTrcID(*itTempTRC));
							++itTempTRC;
						}
					}
				}while(++itSSP!=m_SortedChildCollection.end());
			}

			ucStep=5;

			//��������� ����������
			AddResults();
		}
	
		ucStep=6;

		////���������� ���������
		//ViewIntervalCollection();
		
	}catch(...){
		wchar_t buf[256]=L"";
		wsprintf(buf, L"At step: %u", (unsigned int)ucStep);
		ERR_TO_CONSOLE(erTryCatch, buf);
		throw;
	}

}

void CProximityEvaluator_Table::AddResults(void)
{
	//���� ��� ������ ������, ��������� ���������
	if(m_TableTournament.IsSuccess()){
		m_itCurrentRowWords=m_TableTournament.GetRowWordsCollection()->begin();
		while(m_itCurrentRowWords!=m_TableTournament.GetRowWordsCollection()->end()){
			AddInterval(m_TableTournament.GetTableIndex(), m_itCurrentRowWords->first);
			++m_itCurrentRowWords;
		}
		m_itCurrentRowWords=m_NullCollection.end();
	}
}

Containers::CWordInSequence* CProximityEvaluator_Table::AddPosition(unsigned char ucPositionID, unsigned char ucSequenceID, unsigned char ucPosInSequence, SS::Interface::Core::NdxSE::IWord* pWord)
{
	if(!pWord) return NULL;

	if(pWord->GetObligatoryFlag()){
		//��������� ������ ������������ ���������
		return CRelevanceEvaluator::AddPosition(ucPositionID, ucSequenceID, ucPosInSequence, pWord);
	}
	return NULL;
}

void CProximityEvaluator_Table::AddArgumentPosition(CComplexArgument* pComplexArgument, CCoordinateNode_4s* pCoordinateNode)
{
	if(ISNULL(pComplexArgument)) return;
	if(pComplexArgument->GetAttributes().m_Obligatory != 0){
		//��������� ������ ������������ ���������
		CRelevanceEvaluator::AddArgumentPosition(pComplexArgument, pCoordinateNode);
	}
}

//--------------------------------------------------------------------//

}
}
}
}
}
}
