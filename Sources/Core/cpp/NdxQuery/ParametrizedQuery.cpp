#include "stdafx.h"
#include ".\ObjectInserter.h"
#include ".\ParametrizedQuery.h"
#include ".\Block.h"
#include ".\Sequence.h"
#include ".\Word.h"
#include ".\Variant.h"
#include <iterator>

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxQuery
{
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CParametrizedQuery::CParametrizedQuery(void)
:
m_pSettingsServer(NULL),
m_HasAnswers(FALSE),
m_HasUB(FALSE),
m_HasNonObligatoryWords(FALSE),
m_pSuperTemplate(new CSuperTemplate())
{}

CParametrizedQuery::~CParametrizedQuery(void)
{
	Clear();
}

void CParametrizedQuery::Init(
	SS::Interface::Core::CommonContainers::IQueryResult*	_pQuery,
	SS::Core::Types::IndexationSearch::TSearchParams*	_pSearchParams)
{
	
	if (_pQuery == NULL)
	{
		ToConsole(L"\n.\nERROR!!! pQuery is NULL\n.\n.");
		return;
	}

	if (_pSearchParams == NULL)
	{
		ToConsole(L"\n.\nERROR!!! pSearchParams is NULL\n.\n.");
		return;
	}

	//	��������� �� ������ ��������
	if	(m_pSettingsServer == NULL)
	{
		m_pSettingsServer = (SS::Interface::Core::CommonServices::ISettingsServer*)GetLoadManager()->
			GetInterface(L"./core/GSServer.dll", CLSID_SettingsServer , IID_SettingsServer);
	}

	ToConsole(L"\n.\nPARAMETRIZED QUERY, INIT\n.\n.");
	////////////////////////////////////////////////////////////////////////////
	//���������� 3 ������ ������� �������
	//1. ��� ��������� NdxProcessor::ForcedSearchMode = 7 ��� ��� 
	//_pSearchParams->m_bForceOrSearch = true: "�� �� ���", �� �� AllOr
	//2. ��� ������� ���� � ����� ������� ����� ������ - "Answer �����"
	//3. ����������� �����
	////////////////////////////////////////////////////////////////////////////


	//
	//	����������, ���� �� �������� � ALL OR mode
	//

	//	��������� NdxProcessor::ForcedSearchMode
	bool	IsForcedSearchMode7 = (m_pSettingsServer->GetUInt(L"NdxProcessor::ForcedSearchMode") == 7);

	//	����� ������ OR-�����:
	//	���� pSearchParams.m_bForceOrSearch = true
	//	��� ���� ��������� "NdxProcessor::ForcedSearchMode" = 7 
	bool	bIsSetAllOrMode = _pSearchParams->m_bForceOrSearch || IsForcedSearchMode7;

	//
	//	���������� ���� �� � ������� ������� � Answer �������
	//

	bool	bPresentAnswerFlag = false;
	for(IQI*	i = _pQuery->GetFirstQueryIndex(); i != NULL; i = _pQuery->GetNextQueryIndex())
	{
		if(i->GetAttributes().m_bAnswerIndex){ bPresentAnswerFlag = true; break; }
	}

	//	���������� ����� �������� ��������������� �������
	{
		const unsigned int buffer_size = 512;
		wchar_t	buf[buffer_size];
		unsigned int counter = 0;
		counter += _snwprintf(
			buf+counter,
			buffer_size-counter,
			L"\n.\n.\n��������� ��������������� �������:\n");
		counter += _snwprintf(
			buf+counter,
			buffer_size-counter,
			L"\n(NdxProcessor::ForcedSearchMode == 7)     = %u", (unsigned int)IsForcedSearchMode7);
		counter += _snwprintf(
			buf+counter,
			buffer_size-counter,
			L"\nbPresentAnswerFlag (���� �� ����� ������) = %u", (unsigned int)bPresentAnswerFlag);
		counter += _snwprintf(
			buf+counter,
			buffer_size-counter,
			L"\n_pSearchParams->m_bForceOrSearch          = %u", (unsigned int)_pSearchParams->m_bForceOrSearch);
		counter += _snwprintf(
			buf+counter,
			buffer_size-counter,
			L"\nm_QPSettings.ndxq_EnableObligatoryFlag    = %u", (unsigned int)_pSearchParams->m_QPSettings.ndxq_EnableObligatoryFlag);
		counter += _snwprintf(
			buf+counter,
			buffer_size-counter,
			L"\nm_QPSettings.ndxq_EnableUnionsWords       = %u", (unsigned int)_pSearchParams->m_QPSettings.ndxq_EnableUnionsWords);
		counter += _snwprintf(buf+counter,buffer_size-counter,L"\n.\n.");
		ToConsole(buf);
	}

	//	�������� ������ ����� ���������
	if (bPresentAnswerFlag)
		Init_AnswerMode(_pQuery, _pSearchParams->m_QPSettings);
	else if (bIsSetAllOrMode)
		Init_AllOrMode(_pQuery, _pSearchParams->m_QPSettings);
	else
		Init_Standard(_pQuery, _pSearchParams->m_QPSettings);

	//	����� ������������������� �������
	DebugViewRawQuery(_pQuery);
	//	����� ����������������� �������
	DebugView();
}

SS::Interface::Core::NdxSE::ISuperTemplate* CParametrizedQuery::GetSuperTemplate()
{
	return m_pSuperTemplate.get();
}

unsigned int CParametrizedQuery::GetVariantCount()
{
	return static_cast<unsigned int>(m_Variants.size());
}

BOOL CParametrizedQuery::GetHasAnswers()
{
	return m_HasAnswers;
}

BOOL	CParametrizedQuery::GetHasUnionBlocks()
{
	return m_HasUB;
}

BOOL	CParametrizedQuery::GetHasNonObligatoryWords()
{
	return m_HasNonObligatoryWords;
}

SS::Interface::Core::NdxSE::IVariant* CParametrizedQuery::GetVariant(unsigned int uiIndex)
{
	//	���� ����� ������������ ������ ���������� NULL
	if (uiIndex >= m_Variants.size())
	{
		ToConsole(L"CParametrizedQuery::GetVariant, ������������ ������");
		return NULL;
	}
	//	���������� ������, ���������� uiIndex'��� �������
	return m_Variants[uiIndex];
}

void	CParametrizedQuery::Clear()
{
	m_HasAnswers			= FALSE;
	m_HasUB					= FALSE;
	m_HasNonObligatoryWords	= FALSE;
	m_TransPos_Word.clear();
	m_TransSeqPos_pWord.clear();
	m_AllUnique_Words.clear();
	m_UniqueTrans_Words.clear();
	m_UnionBlocksInfo.clear();
	m_AllUnionWords.clear();
	m_pSuperTemplate->Clear();
	for_each(m_Variants.begin(), m_Variants.end(), CVariant::Del); m_Variants.clear();
}

HRESULT CParametrizedQuery::QueryInterface(REFIID pIID, void** ppBase)
{
	*ppBase = NULL;

	if(pIID == IID_ParametrizedQuery)
		*ppBase = (SS::Interface::Core::NdxSE::IParametrizedQuery*) this;
	else if (pIID == IID_Base)
		*ppBase = (SS::Interface::IBase*) this;

	return (*ppBase == NULL) ? S_FALSE : S_OK;
}

ULONG CParametrizedQuery::Release()
{
	delete this;
	return 0;
}

void CParametrizedQuery::ApplyWordAttributes(s_flagged_word &collection, flagged_word& currentWord)
{
	flagged_word word = currentWord;
	s_flagged_word::iterator current = collection.find(currentWord);
	if(current != collection.end())
	//	����� ����� ���� - ������ ���
	{
		word = *current;
		collection.erase(currentWord);
		word.ApplyWordAttributes(currentWord);
	}
	collection.insert(word);
}

void CParametrizedQuery::Init_AnswerMode(
	SS::Interface::Core::CommonContainers::IQueryResult*				_pQuery,
	SS::Core::Types::IndexationSearch::TQueryParametrizerSettings const&	_Settings)
{
	ToConsole(L"\n.\nPARAMETRIZED QUERY, INIT ANSWER MODE\n.\n.");
	//	�����
	Clear();
	//	������������ ������� �� �����������
	MakeWords(_pQuery);

	m_HasAnswers = TRUE;

	//
	//	��������� AND-���� � OR-����
	//

	//	���������� ����� ��� AND-�����
	s_flagged_word	AndWords;
	//	������������ ����� ��� OR-�����
	flagged_word	OrWord;

	//	�������� �� ��������������
	for(mm_flagged_word::iterator
		itb_trans = m_TransPos_Word.begin(),
		ite_trans = m_TransPos_Word.end();
		itb_trans != ite_trans;
		++itb_trans)
	{
		//	�������� �� ������ � �������������
		for(m_flagged_word::iterator
			itb_word = itb_trans->second.begin(),
			ite_word = itb_trans->second.end();
			itb_word != ite_word;
			++itb_word)
		{
			//	������� �����
			flagged_word& CurrentWord = itb_word->second;
			//	� ����������� �� ������� � �������� ����� ����� ������ ������������ ����� �� �����������
			if (CurrentWord.get_AnswerFlag())
				ApplyWordAttributes(AndWords, CurrentWord);
			else
			{
				//	������� ������� � ���� �����, ������� �����
				OrWord.ApplyWordAttributes(CurrentWord);
				OrWord.MergeWordIndexes(CurrentWord);
			}
		}
	}

	//
	//	�������� AND-����
	//

	//	����������� ��������
	CObjectInserter		INS(m_pSuperTemplate.get(), &m_Variants);

	//	������������� ���������� ����� � ������ � ����
	for(s_flagged_word::iterator
		itb_word = AndWords.begin(),
		ite_word = AndWords.end();
		itb_word != ite_word;
		++itb_word)
	{
		if(itb_word->m_Indexes.Empty()) continue;
		//
		if (_Settings.ndxq_EnableObligatoryFlag) INS.current_word()->SetObligatoryFlag(itb_word->get_ObligatoryFlag());
		INS.current_word()->SetAnswerFlag(itb_word->get_AnswerFlag());//	true
		INS.current_word()->SetAsString(itb_word->get_AsString().c_str());
		INS.current_word()->SetLinguisticWeight(itb_word->get_LingWeight());
		INS.current_word()->Fill(itb_word->m_Indexes);
		//
		INS.Word2AndBlock();
	}
	INS.AndBlock2ST();

	//
	//	�������� OR-����, ��������� �� ������ �����
	//

	if (!OrWord.m_Indexes.Empty())
	{
		if (_Settings.ndxq_EnableObligatoryFlag) INS.current_word()->SetObligatoryFlag(OrWord.get_ObligatoryFlag());
		INS.current_word()->SetAnswerFlag(OrWord.get_AnswerFlag());//	false
		INS.current_word()->SetAsString(OrWord.get_AsString().c_str());
		INS.current_word()->SetLinguisticWeight(OrWord.get_LingWeight());
		INS.current_word()->Fill(OrWord.m_Indexes);
		//
		INS.Word2OrBlock();
		INS.OrBlock2ST();
	}

	//
	//	�������� 1 ������� � 1 ������������������
	//

	if (!m_AllUnique_Words.empty())
	{
		//	���������� ��� ���������� ����� �� ���� �������������, ����������� �� �����
		for(s_flagged_word::iterator
			itb_word = m_AllUnique_Words.begin(),
			ite_word = m_AllUnique_Words.end();
			itb_word != ite_word;
			++itb_word)
		{
			if (itb_word->m_Indexes.Empty()) continue;
			//
			if (_Settings.ndxq_EnableObligatoryFlag) INS.current_word()->SetObligatoryFlag(itb_word->get_ObligatoryFlag());
			INS.current_word()->SetAnswerFlag(itb_word->get_AnswerFlag());
			INS.current_word()->SetAsString(itb_word->get_AsString().c_str());
			INS.current_word()->SetLinguisticWeight(itb_word->get_LingWeight());
			INS.current_word()->Fill(itb_word->m_Indexes);
			//
			INS.Word2Sequence();
		}
		INS.Sequence2Variant();
		INS.Variant2ST();
	}
}

void CParametrizedQuery::Init_Standard(
	SS::Interface::Core::CommonContainers::IQueryResult*				_pQuery,
	SS::Core::Types::IndexationSearch::TQueryParametrizerSettings const&	_Settings)
{
	//
	//	������� ���� ���� �����-������ ���� ������������� ������������ � ����
	//	����� ������� �������� ���� �������������� OR-����.
	//	��� ���������� AND-����� � ���� �� ������ ����� union-������
	//
	ToConsole(L"\n.\nPARAMETRIZED QUERY, INIT STANDARD MODE\n.\n.");
	//	�����
	Clear();
	//	������������ ������� �� �����������
	MakeWords(_pQuery);


	//
	//	�������� ���������
	//

	//	����������� ��������
	CObjectInserter		INS(m_pSuperTemplate.get(), &m_Variants);

	//	�������������
	for(mmm_pflagged_word::iterator
		itb_trans = m_TransSeqPos_pWord.begin(),
		ite_trans = m_TransSeqPos_pWord.end();
		itb_trans != ite_trans;
		++itb_trans)
	{
		//	�� �������������������
		for(mm_pflagged_word::iterator	
			itb_seq = itb_trans->second.begin(), 
			ite_seq = itb_trans->second.end();
			itb_seq != ite_seq;
			++itb_seq)
		{
			//	�� ������ � ������������������
			for(m_pflagged_word::iterator	
				itb_word = itb_seq->second.begin(), 
				ite_word = itb_seq->second.end();
				itb_word != ite_word;
				++itb_word)
			{
				//	�� ������ ������ �����
				if (itb_word->second.get()->m_Indexes.Empty()) continue;
				//
				if (_Settings.ndxq_EnableObligatoryFlag) INS.current_word()->SetObligatoryFlag(itb_word->second.get()->get_ObligatoryFlag());
				INS.current_word()->SetAnswerFlag(itb_word->second.get()->get_AnswerFlag());
				INS.current_word()->SetAsString(itb_word->second.get()->get_AsString().c_str());
				INS.current_word()->SetLinguisticWeight(itb_word->second.get()->get_LingWeight());
				INS.current_word()->Fill(itb_word->second.get()->m_Indexes);
				//
				INS.Word2Sequence();
			}
			//	���������� ���������� � union-������
			if (_Settings.ndxq_EnableUnionsWords)
			{
				if (INS.current_sequence() != NULL) 
					INS.current_sequence()->AssignUnionWordsBlocks(m_UnionBlocksInfo[itb_trans->first][itb_seq->first]);
			}
			//	���������� ������������������ � �������
			INS.Sequence2Variant();
		}
		INS.Variant2ST();
	}

	//	
	//	���������� ��������������� OR-�����, ���������� �� ������ �����,
	//	����������� ������� ���� ���� union-������
	//	(���� ��������� ����������)
	//

	if (_Settings.ndxq_EnableUnionsWords)
	{
		//	����� ���������� ��� ������� union-����
		flagged_word	AllUbIndexesWord;
		for(s_flagged_word::iterator
			itb_word = m_AllUnionWords.begin(),
			ite_word = m_AllUnionWords.end();
			itb_word != ite_word;
			++itb_word)
		{
			//	��������� ��������� �������� ����
			AllUbIndexesWord.ApplyWordAttributes(*itb_word);
			//	���������� � ���� �������
			AllUbIndexesWord.MergeWordIndexes(*itb_word);
		}

		//	
		//	���������� ��������������� OR-����� ������� union-������
		//

		if (!AllUbIndexesWord.m_Indexes.Empty())
		{
			//	����� �������������
			if (_Settings.ndxq_EnableObligatoryFlag) INS.current_word()->SetObligatoryFlag(AllUbIndexesWord.get_ObligatoryFlag());
			INS.current_word()->SetAnswerFlag(AllUbIndexesWord.get_AnswerFlag());
			INS.current_word()->SetAsString(AllUbIndexesWord.get_AsString().c_str());
			INS.current_word()->SetLinguisticWeight(AllUbIndexesWord.get_LingWeight());
			INS.current_word()->Fill(AllUbIndexesWord.m_Indexes);
			//
			INS.Word2OrBlock();
			INS.OrBlock2ST();
		}
	}

	//
	//	���������� AND-�����
	//

	//	� IntersectionWords ��������� ����� ������� ������� �� ���� ��������������
	s_flagged_word	IntersectionWords = m_AllUnique_Words;

	//	���� �������� ��������� union-������, ���������� �� ��������� ���� ����
	//	����� �������� � union-�����.
	if (_Settings.ndxq_EnableUnionsWords)
	{
		s_flagged_word	temp;
		std::set_difference(
			IntersectionWords.begin(),
			IntersectionWords.end(),
			m_AllUnionWords.begin(),
			m_AllUnionWords.end(),
			std::inserter(temp, temp.begin()));
		IntersectionWords.swap(temp);
	}

	//	������ ���������� ���� � ��������������
	ms_flagged_word	TransUniqueWords = m_UniqueTrans_Words;

	//	���� �������� ��������� �����-������, ���������� �� ���������� ������� ���� �������������
	//	����� ������������� �����-������
	if (_Settings.ndxq_EnableUnionsWords)
	{
		for(ms_flagged_word::iterator
			itb_trans = TransUniqueWords.begin(),
			ite_trans = TransUniqueWords.end();
			itb_trans != ite_trans;
			++itb_trans)
		{
			s_flagged_word	temp;
			std::set_difference(
				itb_trans->second.begin(),
				itb_trans->second.end(),
				m_AllUnionWords.begin(),
				m_AllUnionWords.end(),
				std::inserter(temp, temp.begin()));
			itb_trans->second.swap(temp);
		}
	}

	//	�������� �� ���� ��������������, ���� ����� ������� ������� �� ����
	//	��������������
	for(ms_flagged_word::iterator
		itb_trans = TransUniqueWords.begin(),
		ite_trans = TransUniqueWords.end();
		itb_trans != ite_trans;
		++itb_trans)
	{
		//	��������� ���������, ���� ������� ����� ������� ���� �� ���� ��������������
		s_flagged_word		temp;
		//	��. ���������� set_intersection:
		//	� ��������� ����� ������� �� ��������� IntersectionWords!!!
		std::set_intersection(
			IntersectionWords.begin(),
			IntersectionWords.end(),
			itb_trans->second.begin(),
			itb_trans->second.end(),
			std::inserter(temp, temp.begin()));
		IntersectionWords.swap(temp);
	}
	//	� IntersectionWords �������� ����� ������� ���� �� ���� ��������������

	//
	//	��������� AND-����
	//

	for(s_flagged_word::iterator
		itb_word = IntersectionWords.begin(),
		ite_word = IntersectionWords.end();
		itb_word != ite_word;
		++itb_word)
	{
		//	�� ������ ������ ����
		if (itb_word->m_Indexes.Empty()) continue;
		//
		if (_Settings.ndxq_EnableObligatoryFlag) INS.current_word()->SetObligatoryFlag(itb_word->get_ObligatoryFlag());
		INS.current_word()->SetAnswerFlag(itb_word->get_AnswerFlag());
		INS.current_word()->SetAsString(itb_word->get_AsString().c_str());
		INS.current_word()->SetLinguisticWeight(itb_word->get_LingWeight());
		INS.current_word()->Fill(itb_word->m_Indexes);
		//
		INS.Word2AndBlock();
	}
	INS.AndBlock2ST();

	//
	//	���������� OR-������
	//

	//	�������� �� ������ �������������, ���������� � ��� �� ����� ������� 
	//	����� � AND-����
	for(ms_flagged_word::iterator
		itb_trans = TransUniqueWords.begin(),
		ite_trans = TransUniqueWords.end();
		itb_trans != ite_trans;
		++itb_trans)
	{
		//	��������� ����� ����
		s_flagged_word	temp;
		//	���������� ������� �� ��������� ���������
		std::set_difference(
			itb_trans->second.begin(),
			itb_trans->second.end(),
			IntersectionWords.begin(),
			IntersectionWords.end(),
			std::inserter(temp, temp.begin()));
		//	������ ��������� ��������� � ����������� �������������
		itb_trans->second.swap(temp);
	}

	//
	//	�������� OR-������
	//

	//	������ �� ��������������
	for(ms_flagged_word::iterator
		itb_trans = TransUniqueWords.begin(),
		ite_trans = TransUniqueWords.end();
		itb_trans != ite_trans;
		++itb_trans)
	{
		//	������ �� ������
		for(s_flagged_word::iterator
			itb_word = itb_trans->second.begin(),
			ite_word = itb_trans->second.end();
			itb_word != ite_word;
			++itb_word)
		{
			//	�� ������ ������ ����
			if (itb_word->m_Indexes.Empty()) continue;
			//
			if (_Settings.ndxq_EnableObligatoryFlag) INS.current_word()->SetObligatoryFlag(itb_word->get_ObligatoryFlag());
			INS.current_word()->SetAnswerFlag(itb_word->get_AnswerFlag());
			INS.current_word()->SetAsString(itb_word->get_AsString().c_str());
			INS.current_word()->SetLinguisticWeight(itb_word->get_LingWeight());
			INS.current_word()->Fill(itb_word->m_Indexes);
			//
			INS.Word2OrBlock();
		}
		INS.OrBlock2ST();
	}
}

void CParametrizedQuery::Init_AllOrMode(
	SS::Interface::Core::CommonContainers::IQueryResult*				_pQuery,
	SS::Core::Types::IndexationSearch::TQueryParametrizerSettings const&	_Settings)
{
	ToConsole(L"\n\nPARAMETRIZED QUERY, INIT ALL OR MODE\n\n");
	//	�����
	Clear();
	//	������������ ������� �� �����������
	MakeWords(_pQuery);

	//
	//	���������� ������������� ����� ����������� ��������� ��� ������� �������
	//	����� �������� ����� ��� ��������� ������������� ���� ���� �������
	//

	//	����������� ��������
	CObjectInserter		INS(m_pSuperTemplate.get(), &m_Variants);

	flagged_word	SingleWord;
	for(s_flagged_word::iterator
		itb_word = m_AllUnique_Words.begin(),
		ite_word = m_AllUnique_Words.end();
		itb_word != ite_word;
		++itb_word)
	{
		//	��������� �������� � �����
		SingleWord.ApplyWordAttributes(*itb_word);
		//	��������� � ����� �������
		SingleWord.MergeWordIndexes(*itb_word);
	}

	//
	//	�������� ������������� ����� ������������� OR-�����, ����� �� �����������
	//

	if (!SingleWord.m_Indexes.Empty())
	{
		if (_Settings.ndxq_EnableObligatoryFlag) INS.current_word()->SetObligatoryFlag(SingleWord.get_ObligatoryFlag());
		INS.current_word()->SetAnswerFlag(SingleWord.get_AnswerFlag());
		INS.current_word()->SetAsString(SingleWord.get_AsString().c_str());
		INS.current_word()->SetLinguisticWeight(SingleWord.get_LingWeight());
		INS.current_word()->Fill(SingleWord.m_Indexes);
		//
		INS.Word2OrBlock();
		INS.OrBlock2ST();
	}

	//
	//	�������� ������������ ������������������ � ������������ ��������
	//

	for(s_flagged_word::iterator
		itb_word = m_AllUnique_Words.begin(),
		ite_word = m_AllUnique_Words.end();
		itb_word != ite_word;
		++itb_word)
	{
		//	�� ������� ������ ����
		if (itb_word->m_Indexes.Empty()) continue;
		//
		if (_Settings.ndxq_EnableObligatoryFlag) INS.current_word()->SetObligatoryFlag(itb_word->get_ObligatoryFlag());
		INS.current_word()->SetAnswerFlag(itb_word->get_AnswerFlag());
		INS.current_word()->SetAsString(itb_word->get_AsString().c_str());
		INS.current_word()->SetLinguisticWeight(itb_word->get_LingWeight());
		INS.current_word()->Fill(itb_word->m_Indexes);
		//
		INS.Word2Sequence();
	}

	INS.Sequence2Variant();
	INS.Variant2ST();
}

void	CParametrizedQuery::MakeWords(SS::Interface::Core::CommonContainers::IQueryResult* pQuery)
{
	//
	//	������������ ������� �� ��������������� ����������� � ������������ � �� (��������) ����������
	//

	//	��������
	//	������������ ����������� ������� �������������������
	mm_mcth_uc			SequencesBeginsCatcher;
	//	��������� ������� union-������, [ID �����][ID ������][union-block ID](�������)
	mmms_uchar			UnionPositionsInSeqences;
	//	��������� ������� � �������������������
	mms_uchar			PositionsInSequences;

	for(IQI*	i = pQuery->GetFirstQueryIndex();
		i != NULL; 
		i = pQuery->GetNextQueryIndex())
	{
		const SS::Interface::Core::CommonContainers::SQueryIndexAttributes Attribs = i->GetAttributes();
		unsigned int indexPosition = Attribs.m_IndexPosition;

		//	����������� ����������� ����� ������� ��� ������� union-�����
		SequencesBeginsCatcher[Attribs.m_TransformationID][Attribs.m_SequenceID] = Attribs.m_IndexPosition;

		//{
		//	const unsigned int buffer_size = 256;
		//	wchar_t	buf[buffer_size];
		//	unsigned int counter = 0;
		//	counter += _snwprintf(
		//		buf+counter,
		//		buffer_size-counter,
		//		L"\nBeginUBCatcher[%u][%u] = %u\n",
		//		Attribs.m_TransformationID,
		//		Attribs.m_SequenceID,
		//		Attribs.m_IndexPosition);
		//	ToConsole(buf);
		//}

		//	[�������������][�������](�����)
		m_TransPos_Word[Attribs.m_TransformationID][Attribs.m_IndexPosition].AddApplyQueryIndex(i);
		//	���������� � ������ � �������������������
		m_TransSeqPos_pWord[Attribs.m_TransformationID][Attribs.m_SequenceID][Attribs.m_IndexPosition] = 
			&m_TransPos_Word[Attribs.m_TransformationID][Attribs.m_IndexPosition];
		//	��������� ������� � �������������������
		PositionsInSequences[Attribs.m_TransformationID][Attribs.m_SequenceID].insert(indexPosition);
		//	���� ���� ������ union-����� �������� �������

		if (Attribs.m_WordsBlockID != 0)
		{
			//	�������� ��� �����-����� ����
			m_HasUB = TRUE;
			//	���������� ������� � ������� ������� ����� union-�����
			UnionPositionsInSeqences[Attribs.m_TransformationID][Attribs.m_SequenceID][Attribs.m_WordsBlockID].insert(indexPosition);
		}
	}

	//
	//	��������� ���������� � �����-������ � ���, ��������� ��� ����������� �������������
	//	(� ������� ������� ������� � ������ �������)
	//
	//	�������� � ��������� ��� ����� �������� � union-�����
	//

	//	������ �� ��������������
	for(mmms_uchar::iterator
		itb_trans = UnionPositionsInSeqences.begin(),
		ite_trans = UnionPositionsInSeqences.end();
		itb_trans != ite_trans;
		++itb_trans)
	{
		//	������ �� ������������������� � �������������
		for(mms_uchar::iterator
			itb_useq = itb_trans->second.begin(),
			ite_useq = itb_trans->second.end();
			itb_useq != ite_useq;
			++itb_useq)
		{
			//	union-����� � ������������������ �������������
			for(ms_uchar::iterator
				itb_ublock = itb_useq->second.begin(),
				ite_ublock = itb_useq->second.end();
				itb_ublock != ite_ublock;
				++itb_ublock)
			{
				//
				//	��������� ������� ������ � ����� �����-����� � ������������������
				//

				//	��������� ������� union-����� � ������������������
				unsigned int	StartUBPositionInSequence = 0;
				//	��� �� ������������������, ������� ���������� ������������ ��������� ������������������
				//	����� ����������� �������� ������������������ � ����������� �������� ����� union-�����
				//	��� ������ ������ �������� � �������������������
				//
				//	���� �������� �� ����٨� �� �������� � UNION-������ !!!
				//	���� ������������ ������� � union-������, ������� ������� �� ������ �� �������,
				//	�� ����� ��������� �� ������������ �����
				for(unsigned int i = SequencesBeginsCatcher[itb_trans->first][itb_useq->first].get(),//����������� ������� � ������������������
					i_size = *(itb_ublock->second.begin());//����������� ������� ����� union-�����
					i < i_size;
					++i)
				{
					if (PositionsInSequences[itb_trans->first][itb_useq->first].find(i) != 
						PositionsInSequences[itb_trans->first][itb_useq->first].end()) 
							++StartUBPositionInSequence;
				}
				//	��������� ������� union-����� � ������������������ 
				//	(0-������ ������� � ������������������ � �� � �������!)
				unsigned int	pos_begin = StartUBPositionInSequence;

				//{
				//	const unsigned int buffer_size = 256;
				//	wchar_t	buf[buffer_size];
				//	unsigned int counter = 0;
				//	counter += _snwprintf(
				//		buf+counter,
				//		buffer_size-counter,
				//		L"\n*(itb_ublock->second.begin()) = %u\nBeginUBCatcher[itb_trans->first = %u][itb_useq->first = %u].get() = %u",
				//		(unsigned int)(*(itb_ublock->second.begin())),
				//		(unsigned int)itb_trans->first,
				//		(unsigned int)itb_useq->first,
				//		(unsigned int)SequencesBeginsCatcher[itb_trans->first][itb_useq->first].get());
				//	ToConsole(buf);
				//}

				//	�������� ������� ����� union-����� � ������������������ (������������!)
				unsigned int	pos_end = pos_begin + (unsigned int)itb_ublock->second.size() - 1;
				//	��������� � ��������� ���������� � union-�����
				m_UnionBlocksInfo[itb_trans->first][itb_useq->first].push_back(UWB(pos_begin, pos_end));

				//{
				//	const unsigned int buffer_size = 256;
				//	wchar_t	buf[buffer_size];
				//	unsigned int counter = 0;
				//	counter += _snwprintf(
				//		buf+counter,
				//		buffer_size-counter,
				//		L"\nUWB(pos_begin = %u, pos_end = %u), ",
				//		pos_begin,
				//		pos_end);
				//	ToConsole(buf);
				//}

				//
				//	�������� ��������� ��� �����, �������� � �����-����
				//

				//	�������� �� ���� ������ union-�����
				for(s_uchar::iterator
					itb_pos = itb_ublock->second.begin(),
					ite_pos = itb_ublock->second.end();
					itb_pos != ite_pos;
					++itb_pos)
				{
					ApplyWordAttributes(m_AllUnionWords, m_TransPos_Word[itb_trans->first][*itb_pos]);
				}
			}
		}
	}

	//	�������� �� ���� ������, �������� ��������� ��� �����
	for(mm_flagged_word::iterator
		itb_trans = m_TransPos_Word.begin(),
		ite_trans = m_TransPos_Word.end();
		itb_trans != ite_trans;
		++itb_trans)
	{
		for(m_flagged_word::iterator
			itb_pos = itb_trans->second.begin(),
			ite_pos = itb_trans->second.end();
			itb_pos != ite_pos;
			++itb_pos)
		{
			//
			//	�������� ���������� ����� �� ��� �������
			//
			ApplyWordAttributes(m_AllUnique_Words, itb_pos->second);

			//
			//	�������� ���������� ����� � ������ �������������
			//
			ApplyWordAttributes(m_UniqueTrans_Words[itb_trans->first], itb_pos->second);

			//
			//	���������� ������� �������������� ���� � �������
			//
			if (!itb_pos->second.get_ObligatoryFlag()) m_HasNonObligatoryWords = TRUE;
		}
	}
}

void	CParametrizedQuery::DebugView()
{
	ToConsole(ToString());
}

const wchar_t*	CParametrizedQuery::ToString()
{
	m_AsString.assign(L"\nCParametrizedQuery is empty\n");

	const unsigned int buffer_size = 20*1024;
	wchar_t	buf[buffer_size];
	unsigned int counter = 0;
	SS::Interface::Core::CommonContainers::SQueryIndexAttributes	Attribs;

	counter += _snwprintf(
		buf+counter,
		buffer_size-counter, L"\
\n.\n.\n-------------- OPTIMIZED QUERY (NdxQuery.dll) --------\n\
\nHas answers:              %u\
\nHas union-blocks:         %u\
\nHas non-obligatory words: %u\n.",
		(unsigned int)m_HasAnswers,
		(unsigned int)m_HasUB,
		(unsigned int)m_HasNonObligatoryWords);

	if (m_pSuperTemplate.get() != NULL)
	{
		counter += _snwprintf(
			buf+counter,
			buffer_size-counter, L"%s",
			m_pSuperTemplate->ToString());
	}

	if (!m_Variants.empty()) counter += _snwprintf(buf+counter, buffer_size-counter, L"\n.\n[[ VARIANTS ]]\n");

	for(v_Variant::iterator
		itb_var = m_Variants.begin(),
		ite_var = m_Variants.end();
		itb_var != ite_var;
		++itb_var)
	{
		if (*itb_var == NULL)
		{
			counter += _snwprintf(
				buf+counter,
				buffer_size-counter, L"warning! m_Variants contains NULL");
			continue;
		}

		counter += _snwprintf(
			buf+counter,
			buffer_size-counter,
			L"%s",
			(*itb_var)->ToString());
	}

	counter += _snwprintf(
		buf+counter,
		buffer_size-counter,
		L"\n.\n--------- END OF OPTIMIZED QUERY -----------\n.");

	m_AsString.assign(buf);

	return m_AsString.c_str();
}

const wchar_t*	CParametrizedQuery::ToStringRawQuery(SS::Interface::Core::CommonContainers::IQueryResult* pQuery)
{
	m_AsStringRawQuery.clear();

	//	����� ����� ��������
	wchar_t*	inMorpho	= L"morpho  ";
	wchar_t*	inSyntax	= L"syntax  ";
	wchar_t*	inSemantic	= L"semantic";

	const unsigned int buffer_size = 20*1024;
	wchar_t	buf[buffer_size];
	unsigned int counter = 0;
	SS::Interface::Core::CommonContainers::SQueryIndexAttributes	Attribs;
	counter += _snwprintf(
		buf+counter,
		buffer_size-counter, L"\
\n                       RAW QUERY\n.\
\n-------------------------------------------------------------------\
\n    index      .Index Type.LingWeight.trID.seID.wbID.ipos|fOBL.fANS|\
\n-------------------------------------------------------------------");
	for(IQI*	i = pQuery->GetFirstQueryIndex();
		i != NULL; 
		i = pQuery->GetNextQueryIndex())
	{
		wchar_t*	wszIndexTypeName = NULL;
		switch(LingDecoder::get_index_type(i->GetQueryIndex()))
		{
		case LingDecoder::eitMorphoIndex:	wszIndexTypeName = inMorpho; break;
		case LingDecoder::eitSyntaxIndex:	wszIndexTypeName = inSyntax; break;
		case LingDecoder::eitSemanticIndex:	wszIndexTypeName = inSemantic; break;
		default: wszIndexTypeName = inMorpho;
		}
		std::wstring	word( (i->GetQueryWord() == NULL) ? (L"<NULL>") : (i->GetQueryWord()) );
		Attribs = i->GetAttributes();
		counter += _snwprintf(
			buf+counter,
			buffer_size-counter,
			L"\n  %10u   |%10s|%#10.2f|%4u|%4u|%4u|%4u|%4u|%4u| %s",
			i->GetQueryIndex(),
			wszIndexTypeName,
			(double)(i->GetIndexWeight()),
			(unsigned int)Attribs.m_TransformationID,
			(unsigned int)Attribs.m_SequenceID,
			(unsigned int)Attribs.m_WordsBlockID,
			(unsigned int)Attribs.m_IndexPosition,
			(unsigned int)Attribs.m_Obligatory,
			(unsigned int)Attribs.m_bAnswerIndex,
			word.c_str());
	}

	counter += _snwprintf(buf+counter, buffer_size-counter, L"\n");
	m_AsStringRawQuery.assign(buf);

	return m_AsStringRawQuery.c_str();
}

void	CParametrizedQuery::DebugViewRawQuery(SS::Interface::Core::CommonContainers::IQueryResult* pQuery)
{
	ToConsole(ToStringRawQuery(pQuery));
}


}
}
}
}

