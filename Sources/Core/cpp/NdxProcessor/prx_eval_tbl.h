#pragma once

#include ".\r_eval.h"
#include ".\tbl_containers.h"

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
class CTableTournament;

///��������� ���� ������
class CRowWords
{
public:
	///	ctr
	CRowWords(unsigned int uiMaxWordsCount);
	///	dtr
	~CRowWords(void);
	///���������� ���� ����������� �����
	void SetWordID(unsigned int uiWordID, unsigned char ucCellID);
	///��������� ��� �� ����� ����������
	bool IsFull(void){ return (all_words.size() == m_uiMaxWordsCount) ? (true) : (false); };
	///���������� ���������� 
	void Reset(void){ all_words.clear(); words_by_cell.clear(); };
	///���������� ������������ ���������� ����
	unsigned int	GetMaxWordsNumber(void){return m_uiMaxWordsCount;}
	///���������� ������� ���������� ������������ ����
	unsigned int	GetCurrentWordsCount(void){return static_cast<unsigned int>(all_words.size());}
	///���������� ������� ���������� �����
	unsigned int	GetCellsCount(void){return (unsigned int)words_by_cell.size();}
	///	���������� ���������� ���� � �������� ������
	unsigned int	GetCellWordCount(unsigned int const _id_cell);
	///���������� ���������� ���� � ����� �������, �������������� ����� �� �����������
	static unsigned int GetUniqWordsCount(CRowWords* pRowWords1, CRowWords* pRowWords2);

	///	����������, ������� �� �����-������������� ��� �������� ������ (�������� _row)
	/**
	"�����-�������������" ("�����" � ������ "�����") ����������� ����� �����
	����������� ���� ������ (�������� _Row) 
	� ���� ����� (�������� _CapRow) ���������� �������,
	��� ���������� ���� �� ����������� ������ � �������, ��� ������ ��������� ����.
	���� � �������� ����� � ������ ������ ���� � �� �� ������, �����-������������� �� ����� (������� false).
	\param[in]	_CapRow			������-�����
	\param[in]	_Row			��������������� ������
	\return	true - ������������� � ������ ����
	*/
	static bool	IsCrossRelevance(
		CRowWords*			_pCapRow, 
		CRowWords*			_pRow);

	
protected:
	///����� ���������� ����� � �������
	const unsigned int m_uiMaxWordsCount;
	///	��������� ���������� �������� unsigned int
	typedef std::set<unsigned int>						word_collection;
	///	����� "����� ������ - ��������� ���� � ������"
	typedef std::map<unsigned int, word_collection >	cell_collection;
	///	��������� ���� � ������������ � ��������; pair<����� ������, ��������� ���� � ������>
	cell_collection										words_by_cell;
	///	��������� ���� ���������� ���� ������
	word_collection										all_words;
};

//--------------------------------------------------------------------//

///��������� ������, ��� ��������� ����������� ����� �������
///� ���� ����������� ����� � ���������������� ����� � �����
///������ �������� � ��������� �����, � ��������� ��� ���������
///������ �� ������ ������� ������������� ������� �������
class CTableTournament
{
public:
	typedef std::map<unsigned int, CRowWords*> TRowWordsCollection;

	CTableTournament(void);
	~CTableTournament(void);
	
	///��������� ������
	void StartTournament(unsigned int uiTableIndex, unsigned int uiRaceWordsCount, unsigned int uiWordID);
	///��������� ����� ����� ��� ������� �������, ���� ������ false ������ ���������� ��������
	bool NextRace(unsigned int uiWordID);
	///��������� ������
	void Reset(void);
	///�������� �������
	bool IsSuccess(void){return (!m_RowWordsCollection.empty() && m_uiAddedRowsPerRace!=0)?true:false;};

	///��������� ��������������� ������
	void AddTrcID(Containers::CTrcID TrcID);
	///���������� ��������� ����� �� �������
	TRowWordsCollection* GetRowWordsCollection(void){return &m_RowWordsCollection;};
	///���������� ������������� �������
	unsigned int GetTableIndex(void){return m_uiTableIndex;};
	///���������� ������ ����� �������
	CRowWords* GetCapRow(void);

protected:
	
	///������������� �������
	unsigned int m_uiTableIndex;
	///��������� ����� �� �������
	TRowWordsCollection m_RowWordsCollection;
	///������ ����� �������
	CRowWords* m_pCapRow;
	///������������� �������� �����
	unsigned int m_uiCurrentWordID;
	///���������� ���� ����������� � �������
	unsigned int m_uiRaceWordsCount;
	///����� ������� ��������
	unsigned int m_uiCurrentRace;
	///����� ������� ��������
	unsigned int m_uiAddedRowsPerRace;
};

//--------------------------------------------------------------------//

///����������� �������� ������������ ���� � �������� ���������
class CProximityEvaluator_Table : public CRelevanceEvaluator
{
public:
	CProximityEvaluator_Table(unsigned int uiEvalID, bool bCheckSequence, Containers::CContainersFactory* pContainersFactory);
	virtual ~CProximityEvaluator_Table(void);

	///��������� �  ���������� ������� �������� ��������� �� ��������������
	Containers::CWordInSequence* AddPosition(unsigned char ucPositionID, unsigned char ucSequenceID, unsigned char ucPosInSequence, SS::Interface::Core::NdxSE::IWord* pWord);
	///��������� ������� � ��������� ������������
	void AddArgumentPosition(CComplexArgument* pComplexArgument, Containers::CCoordinateNode_4s* pCoordinateNode);
	///��������� ��� �� �������� � ������� ������������ �������� � �����������
	void Evaluate(unsigned int uiEvalID);

protected:

	///������� ���������
	Containers::CInterval* CreateInterval(unsigned int uiTableIndex, unsigned int uiRowIndex);
	///���������� ��� ���������
	unsigned int GetIntervalWeight(Containers::CInterval* pInterval);

	///������� ���������� 
	bool PrepareEvaluation(unsigned int uiEvalID);
	///��������� ����������
	void AddResults(void);

	///��������� ������� ���������� �������� �����
	Containers::CWord::TCommonPositions m_CurrentCellIDs;
	///��������� ������
	CTableTournament m_TableTournament;
	///������� ������-���������
	CTableTournament::TRowWordsCollection::iterator m_itCurrentRowWords;
	///��������� ��� ������������� ����������
	CTableTournament::TRowWordsCollection m_NullCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}
