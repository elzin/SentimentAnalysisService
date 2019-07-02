#include "StdAfx.h"
#include ".\es_filler_query.h"
#include ".\index_stat_storage.h"
#include <math.h>

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

using namespace SS::Core::NdxSE::NdxProcessor::Storages;
using namespace SS::Interface::Core::CommonContainers;
using namespace SS::Interface::Core::NdxSE;

//--------------------------------------------------------------------//
CESFillerFromQuery::CESFillerFromQuery(Containers::CContainersFactory* pCntFactory, IParametrizedQuery* pPrmQueryResult)
	:CESFillerEx<IParametrizedQuery>(pCntFactory, pPrmQueryResult), m_pSubster(NULL)
{
}

CESFillerFromQuery::~CESFillerFromQuery(void)
{
}

void CESFillerFromQuery::Fill(CBlockEquation* pEquation, CSubster* pSubster)
{
	if(ISNULL(m_pFillingSource)) return;
	if(ISNULL(pEquation)) return;
	if(ISNULL(pSubster)) return;
	
	m_pSubster=pSubster;
	ISuperTemplate			*stemplate = m_pFillingSource->GetSuperTemplate();
	IBlock					*block = NULL;

	if(ISNULL(stemplate)) return;

    //�������� �� OR-������ �������, ���������� �������� ������� ������� 
	for (unsigned int ctr_block = 0, ctr_block_size = stemplate->GetORBlockCount(); ctr_block < ctr_block_size; ++ctr_block)
	{
		block = stemplate->GetORBlock(ctr_block);
		if (ISNULL(block)) return;
		//��������� ������ ���������� �� ����������� �����
		AddArgumentsGroup(pEquation, block, false);
	}

	block = stemplate->GetANDBlock();
	if (ISNULL(block)) return;
	//��������� ������ ���������� �� ����������� �����
	AddArgumentsGroup(pEquation, block, true);
}

void CESFillerFromQuery::AddArgumentsGroup(CBlockEquation* pEquation, IBlock* pBlock, bool bAndBlock)
{
	if(ISNULL(pEquation)) return;
	if(ISNULL(pBlock)) return;

	CArgumentsGroup*		pArgumentsGroup;
	IWord					*word = NULL;
	//	�������� �� ������ AND-����� �������
	for (unsigned int ctr_word = 0, ctr_word_size = pBlock->GetWordCount(); ctr_word < ctr_word_size; ++ctr_word)
	{
		//	AND-����� �������
		word = pBlock->GetWord(ctr_word);
		if (ISNULL(word)) return;
		/*	��� ������ �� �������� �������� �� �������������� �����: ���� �������� ������ � ������������� �������, 
			� ����� �� ������������, �� �� ������������ ���*/
		if (!wcscmp(GetFactory()->GetIndexStorage()->GetIndexStorageName(), L"TABLES") && !word->GetObligatoryFlag()) continue;
		
		//	������ ����� �����
		pArgumentsGroup = new CArgumentsGroup(ctr_word, pEquation->GetEquationLogic(), ctr_word==4?false:true/*word->GetObligatoryFlag()*/);
		
		//������ ���� ����� � pArgumentsGroup
		AddWordToArgumentsGroup(pArgumentsGroup, word);

		//	�������� ����� �� �������
		if (pArgumentsGroup->IsEmpty())
		{
			delete pArgumentsGroup;
		}
		else
		{
			//��������� ��� ������ ����� ��������� AND-����� ��� OR-����� � ����������� �� �����
			bAndBlock?pEquation->AddAndBlock():pEquation->AddOrBlock();
			//��������� AND-�����
			pEquation->AddGroup(pArgumentsGroup);
		}
	}
}

void CESFillerFromQuery::AddWordToArgumentsGroup(CArgumentsGroup* pArgumentsGroup, IWord* pWord)
{
	if(ISNULL(m_pSubster)) return;
	if(ISNULL(pWord)) return;
	if(ISNULL(pArgumentsGroup)) return;

	unsigned int			uiIndexFrequency = 0;
	unsigned int			uiEntryPoint = EMPTY_VALUE;
	CComplexArgument*		pArgument =	NULL;
	SQueryIndexAttributes	QueryIndexAttributes;

	QueryIndexAttributes.m_bAnswerIndex=pWord->GetAnswerFlag();

	//	�������� �� �������� ����� �������
	for (unsigned ctr_index = 0, ctr_index_size = pWord->GetMorphoIndexCount(); ctr_index < ctr_index_size; ++ctr_index)
	{
		//	������ ����� ����� �� ��������� �������� �� ������� �������� ��������, ���������� ��� �������
		GetFactory()->GetIndexStorage()->GetIndexEntryPointTable()->GetIndexData(
			pWord->GetMorphoIndex(ctr_index),	//	������ ����� �������
			&uiEntryPoint,		//	����� �����
			&uiIndexFrequency);	//	�������
		
		//������ ������ � ���������� � ������
		AddIndexToArgumentsGroup(pArgumentsGroup, pWord->GetMorphoIndex(ctr_index), uiEntryPoint, uiIndexFrequency, QueryIndexAttributes);
	}
}

void CESFillerFromQuery::AddIndexToArgumentsGroup(CArgumentsGroup* pArgumentsGroup, 
												  unsigned int uiIndex, unsigned int uiEntryPoint, 
												  unsigned int uiIndexFrequency, SQueryIndexAttributes QueryIndexAttributes)
{
	if(ISNULL(m_pSubster)) return;
	if(ISNULL(pArgumentsGroup)) return;
	
	//	���� ����� ����� ��������
	if ( uiEntryPoint != EMPTY_VALUE)
	{
		//	��������� ������ � �����
		CComplexArgument* pArgument = pArgumentsGroup->AddArgument(
			uiIndex,		//	������
			(float)uiIndexFrequency,		//	�������
			QueryIndexAttributes);		//	�������� �������, ��������

		if(ISNULL(pArgument)) return;

		m_pSubster->GetArgValCollection()->push_back(
			new CArgValuesPair(
				pArgument,
				GetFactory()->CreateValuesContainer(uiEntryPoint)));
	}
	else
	{
		//	���� ����� ����� ������� �� ��������, ����� ����������� �� �� �������
		wchar_t buf[200];
		swprintf(
			buf,
			L"EntryPoint is empty in Storage: %s , for Index: %u", 
			GetFactory()->GetIndexStorage()->GetIndexStorageName(),
			uiIndex);
		ToConsole(buf);
	}
}

void CESFillerFromQuery::ViewFillingSource(void)
{
	wchar_t buf[200];

	if(ISNULL(m_pFillingSource)) return;

	ToConsole(L"Query expression:");

	ISuperTemplate*	stemplate = m_pFillingSource->GetSuperTemplate();
	IBlock*			block = NULL;
	ISequence*		seq = NULL;
	IVariant*		var = NULL;
	IWord*			word = NULL;

	if(ISNULL(stemplate)) return;
	block = stemplate->GetANDBlock();
	if(ISNULL(block)) return;
	ToConsole(L"AND-Block:");

	//	����� AND-�����
	for (unsigned int i = 0, i_size = block->GetWordCount(); i < i_size; ++i)
	{
		word = block->GetWord(i);
		if(ISNULL(word)) return;
		swprintf(buf, L"word %u of AND-block, indexes: ", i);
		ToConsole(buf);
		//	�������� �� �������� �����
		for (unsigned int j = 0, j_size = word->GetMorphoIndexCount(); j < j_size; ++j)
		{
			swprintf(buf, L"%u, (number is %u)", word->GetMorphoIndex(j), j);
			ToConsole(buf);
		}
	}

	ToConsole(L"----------- OR-Blocks: --------------");

	//	�������� �� OR-������
	for (unsigned int i = 0, i_size = stemplate->GetORBlockCount(); i < i_size; ++i)
	{
		block = stemplate->GetORBlock(i);
		if (ISNULL(block)) return;
		swprintf(buf, L"OR-Block %u", i);
		ToConsole(buf);
		//	�������� �� ������ � OR-�����
		for (unsigned int j = 0, j_size = block->GetWordCount(); j < j_size; ++j)
		{
			word = block->GetWord(j);
			if (ISNULL(word)) return;
			swprintf(buf, L"word %u of OR-block, indexes: ", i);
			ToConsole(buf);
			//	�������� �� �������� � �����
			for(unsigned int k = 0, k_size = word->GetMorphoIndexCount(); k < k_size; ++k)
			{
				swprintf(buf, L"%u (number is %u)", word->GetMorphoIndex(k), k);
				ToConsole(buf);
			}
		}
	}

	//	�������� �� ���������
	swprintf(buf, L"Variants count %u", m_pFillingSource->GetVariantCount());
	ToConsole(buf);

	//	�������� �� ���������
	for(unsigned int i = 0, i_size = m_pFillingSource->GetVariantCount(); i < i_size; ++i)
	{
		var = m_pFillingSource->GetVariant(i);
		if (ISNULL(var)) return;
		swprintf(buf, L"variant %u: ", i);
		ToConsole(buf);
		//	������ �� �������������������
		for (unsigned int j = 0, j_size = var->GetSequenceCount(); j < j_size; ++j)
		{
			seq = var->GetSequence(j);
			if (ISNULL(seq)) return;
			swprintf(buf, L"sequence %u of variant %u , words:", j, i);
			ToConsole(buf);
			//	�������� �� �������
			for(unsigned int k = 0, k_size = seq->GetWordCount(); k < k_size; ++k)
			{
				word = seq->GetWord(k);
				if (ISNULL(word)) return;
				swprintf(buf, L"word %u of sequence %u, indexes:", k, j);
				ToConsole(buf);
				//	�������� �� �������� � �����
				for(unsigned int n = 0, n_size = word->GetMorphoIndexCount(); n < n_size; ++n)
				{
					swprintf(buf, L"index %u, (number is %u)", word->GetMorphoIndex(n), n);
					ToConsole(buf);
				}
			}
		}
	}
}

//--------------------------------------------------------------------//

void CESFillerFromQuery_Statistic::Fill(CBlockEquation* pEquation, CSubster* pSubster)
{
	if(ISNULL(m_pFillingSource)) return;
	if(ISNULL(pEquation)) return;
	if(ISNULL(pSubster)) return;

	m_IndexToAndBlock.clear();
	
	//��������� ����������� �����
	CESFillerFromQuery::Fill(pEquation, pSubster);
	
	//������������� ������ � AND-���� ������ 
	//������� �� ���������� �� ������ � OR-����
	if(!m_IndexToAndBlock.empty()){
		ISuperTemplate* pStemplate = m_pFillingSource->GetSuperTemplate();
		if(ISNULL(pStemplate)) return;
		IBlock* pBlock = pStemplate->GetANDBlock();

		unsigned int uiWordIndex=(pBlock==NULL?0:pBlock->GetWordCount());
		unsigned int uiIndexFrequency = 0;
		unsigned int uiEntryPoint = EMPTY_VALUE;
		SQueryIndexAttributes QueryIndexAttributes;

		CArgumentsGroup* pArgumentsGroup = new CArgumentsGroup(uiWordIndex, pEquation->GetEquationLogic(), true);

		for(TIndexCollection::iterator itIndex=m_IndexToAndBlock.begin(); itIndex!=m_IndexToAndBlock.end(); itIndex++){
			//	������ ����� ����� �� ��������� �������� �� ������� �������� ��������, ���������� ��� �������
			GetFactory()->GetIndexStorage()->GetIndexEntryPointTable()->GetIndexData(
				(*itIndex),	//	������ ����� �������
				&uiEntryPoint,		//	����� �����
				&uiIndexFrequency);	//	�������
			
			//������ ������ � ���������� � ������
			AddIndexToArgumentsGroup(pArgumentsGroup, (*itIndex), uiEntryPoint, uiIndexFrequency, QueryIndexAttributes);
		}

		//��������� AND-�����
		pEquation->AddAndBlock();
		pEquation->AddGroup(pArgumentsGroup);
	}
}

void CESFillerFromQuery_Statistic::AddArgumentsGroup(CBlockEquation* pEquation,
	SS::Interface::Core::NdxSE::IBlock* pBlock, bool bAndBlock)
{
	m_bCurrentAndBlock=bAndBlock;
	CESFillerFromQuery::AddArgumentsGroup(pEquation, pBlock, bAndBlock);
}


void CESFillerFromQuery_Statistic::AddWordToArgumentsGroup(CArgumentsGroup* pArgumentsGroup, IWord* pWord)
{
	if(ISNULL(m_pSubster)) return;
	if(ISNULL(pWord)) return;
	if(ISNULL(pArgumentsGroup)) return;

	unsigned int			uiIndexFrequency = 0;
	unsigned int			uiEntryPoint = EMPTY_VALUE;
	CComplexArgument*		pArgument =	NULL;
	SQueryIndexAttributes	QueryIndexAttributes;
	float fIndexWeight;

	unsigned int uiTotalWordsCount=((Storages::CIndexStatisticStorage*)GetFactory()->GetIndexStorage())->GetDocNormStorage()->GetTotalWordsCount();

	QueryIndexAttributes.m_bAnswerIndex=pWord->GetAnswerFlag();

	//	�������� �� �������� ����� �������
	for (unsigned ctr_index = 0, ctr_index_size = pWord->GetMorphoIndexCount(); ctr_index < ctr_index_size; ++ctr_index)
	{
		//	������ ����� ����� �� ��������� �������� �� ������� �������� ��������, ���������� ��� �������
		GetFactory()->GetIndexStorage()->GetIndexEntryPointTable()->GetIndexData(
			pWord->GetMorphoIndex(ctr_index),	//	������ ����� �������
			&uiEntryPoint,		//	����� �����
			&uiIndexFrequency);	//	�������
		
		//��������� ��� ������� � ���������
		fIndexWeight=((float)uiIndexFrequency/(float)uiTotalWordsCount);
		fIndexWeight/=GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_fWordsNormKoef;

		//wchar_t buf[256];
		//swprintf(buf, L"Index: %u, Weight: %f, uiTotalWordsCount: %u, uiIndexFrequency: %u", 
		//	pWord->GetMorphoIndex(ctr_index), fIndexWeight, uiTotalWordsCount, uiIndexFrequency);
		//ToConsole(buf);
		
		if(GetFactory()->GetSearchSettings()->m_SearchSettings.m_EvalRelevanceMode==
			CNdxSearchSettings::SSearchSettings::erWordProximityWithStatistic && 
			fIndexWeight>GetFactory()->GetSearchSettings()->m_SmartSearchSettings.m_fRarityWordLimit && 
			!QueryIndexAttributes.m_bAnswerIndex && !m_bCurrentAndBlock){
			wchar_t buf1[500];
			swprintf(buf1, L"Index: %u is frequent move to AND-Block. Weight: %f, uiTotalWordsCount: %u, uiIndexFrequency: %u", 
				pWord->GetMorphoIndex(ctr_index), fIndexWeight, uiTotalWordsCount, uiIndexFrequency);
			ToConsole(buf1);
			//���� ����� �� ��� �����, ������ ��� ��� � �����
			m_IndexToAndBlock.push_back(pWord->GetMorphoIndex(ctr_index));
		}else{
			//������ ������ � ���������� � ������
			AddIndexToArgumentsGroup(pArgumentsGroup, pWord->GetMorphoIndex(ctr_index), uiEntryPoint, uiIndexFrequency, QueryIndexAttributes);
		}
	}
}

//--------------------------------------------------------------------//

}
}
}
}
}