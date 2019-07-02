//QueryResultEx.cpp

#include "StdAfx.h"
#include ".\queryresultex.h"
#include "..\ASSInterface\TDictionaryNames.h"
#include "..\ASSInterface\Constants.h"
#include "../[libs]/_Paths.h"

namespace SS
{
namespace Core
{
namespace CommonContainers
{

//������������
CQueryResultEx::CQueryResultEx() : m_uiQueryUnitID(0), 
	                               m_pQuery(NULL), 
								   m_IsSynonimCollection(false),
								   m_IsMorphoCollection(false),
								   m_bOneUnit(false),
								   m_pDictionary(NULL)
{
	m_oDataID.Init();
	m_LinguisticProcessorMode.Init();
}

CQueryResultEx::~CQueryResultEx()
{
}

HRESULT CQueryResultEx::QueryInterface(REFIID pIID, void** pBase)	//���������� � ���������� � �������� REFIID. 
																	//pBase ����� NULL, ���� ������ ��������� �� ��������������
{
	if (pIID==IID_QueryResult)
	{
		*pBase = (IQueryResult*)this;
	}
	else if (pIID==IID_QueryResultEx)
	{
		*pBase = (IQueryResultEx*)this;
	}
	else if ( pIID == IID_Base )
	{
		*pBase = static_cast< SS::Interface::IBase* >( this );
	}
	else
	{
		*pBase = NULL;
	}
	return S_OK;
}

//����������� ������
bool CQueryResultEx::ApplyLinguisticProcessorMode(IQueryUnitIndexCollection* pCollection)
{
	SS_TRY
	{
		switch (pCollection->GetIndexCollectionType()) 
		{
		case SS::Interface::Core::BlackBox::eitSyntaxIndex :
				if ( (m_LinguisticProcessorMode.GetAnalyseDepthParams())->IsSyntax() ) 
				{ return true; }
				break;
		case SS::Interface::Core::BlackBox::eitSemanticIndex :
				if ( (m_LinguisticProcessorMode.GetAnalyseDepthParams())->IsSemantic() ) 
				{ return true; }
				break;
		case SS::Interface::Core::BlackBox::eitSynonymIndex :
				if ( (m_LinguisticProcessorMode.GetAnalyseDepthParams())->IsSynonims() ) 
				{ return true; }
				break;
		case SS::Interface::Core::BlackBox::eitMorphoIndex :
				if ( ((m_LinguisticProcessorMode.GetAnalyseDepthParams())->IsSynonims()) && (m_IsSynonimCollection) ) 
				{ 
					return false;
				}
				else if ( (m_LinguisticProcessorMode.GetAnalyseDepthParams())->IsMorpho() ) 
				{ 
					return true; 
				}
				break;
		default:
				SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"����������� ��� �������");
		}
		return false;
	}	
	SS_CATCH(L"")
}

///���������� ������� ��������� �������-��������
void CQueryResultEx::SearchSynonimCollection(IQueryUnit* pQueryUnit)
{
	SS_TRY
	{					
		IQueryUnitIndexCollection* pCollection = pQueryUnit->GetFirstQueryUnitIndexCollection();
		for (pCollection; pCollection; pCollection = pCollection->GetNextQueryUnitIndexCollection())
		{
			if (pCollection->GetIndexCollectionType() == SS::Interface::Core::BlackBox::eitSynonymIndex) 
			{
				m_IsSynonimCollection = true;
				return;
			}				
		}
		m_IsSynonimCollection = false;
	}	
	SS_CATCH(L"")
}

///���������� ������� �����-��������� � Unit-�
void CQueryResultEx::SearchMorphoCollection(IQueryUnit* pQueryUnit)
{
	SS_TRY
	{
		IQueryUnitIndexCollection* pCollection = pQueryUnit->GetFirstQueryUnitIndexCollection();
		for (pCollection; pCollection; pCollection = pCollection->GetNextQueryUnitIndexCollection())
		{
			if (pCollection->GetIndexCollectionType() == SS::Interface::Core::BlackBox::eitMorphoIndex) 
			{
				m_IsMorphoCollection = true;
				return;
			}				
		}
		m_IsMorphoCollection = false;
	}
	SS_CATCH(L"")
}

void CQueryResultEx::ApplyCollections(IQueryUnitIndexCollection* pQueryUnitIndexCollection, IQueryIndex** ppqiFirst, IQueryIndex** ppqiLast)
{
	SS_TRY
	{
		if ( !(ApplyLinguisticProcessorMode(pQueryUnitIndexCollection)) )
		{ return; }
		SS::Interface::Core::CommonContainers::SQueryIndexAttributes oQueryIndexAttributes;
		unsigned int iLeftBrackets = 0;
		unsigned int iRightBrackets = 0;
		char chOperator = '|';	
		IQueryIndex*		pCurrQueryIndex = NULL;
		
		IQueryUnitIndex*	pQueryUnitIndex = pQueryUnitIndexCollection->GetFirstQueryUnitIndex();
		IQueryUnitIndex*	pQueryUnitIndexFirst = pQueryUnitIndex;
		while (pQueryUnitIndex)
		{
			//�������� ������ � ���������
			pCurrQueryIndex = AddQueryIndex();
			if (pQueryUnitIndex == pQueryUnitIndexFirst)
				(*ppqiFirst) = pCurrQueryIndex;
			pCurrQueryIndex->SetQueryIndex( (pQueryUnitIndex->GetIndex().GetDictionaryIndexWithoutFlags()));
			pCurrQueryIndex->SetOperator(chOperator);
			  oQueryIndexAttributes.m_SequenceID = m_oDataID.GetSequenceID();
			  oQueryIndexAttributes.m_TransformationID = m_oDataID.uiTransformationID;
			  oQueryIndexAttributes.m_IndexPosition = m_uiQueryUnitID;
			  oQueryIndexAttributes.m_Obligatory = m_oDataID.IsObligatory;
			  if (m_bOneUnit) 
			  { oQueryIndexAttributes.m_WordsBlockID = 0; }
			  else
			  { oQueryIndexAttributes.m_WordsBlockID = m_oDataID.uiGroupCount; }
			  if (!m_IsMorphoCollection) 
			  { oQueryIndexAttributes.m_bAnswerIndex = 1; }
			pCurrQueryIndex->SetAttributes(oQueryIndexAttributes);
			pCurrQueryIndex->SetQueryWord(m_strWord.c_str());
			pCurrQueryIndex->SetIndexWeight(m_oDataID.fUnitWeight);

			pQueryUnitIndex = pQueryUnitIndex->GetNextQueryUnitIndex();
		}
		if (!pCurrQueryIndex)
			return;
		(*ppqiLast) = pCurrQueryIndex;
		(*ppqiLast)->SetOperator(0);
		iLeftBrackets = (*ppqiFirst)->GetLeftBrackets();
		iLeftBrackets++;
		(*ppqiFirst)->SetLeftBrackets(iLeftBrackets);
		iRightBrackets = (*ppqiLast)->GetRightBrackets();
		iRightBrackets++;
		(*ppqiLast)->SetRightBrackets(iRightBrackets);
	}
	SS_CATCH(L"")
}

void CQueryResultEx::ApplyUnits(IQueryUnit* pQueryUnit, IQueryIndex** ppqiFirst, IQueryIndex** ppqiLast)
{
	SS_TRY
	{
		unsigned int iLeftBrackets = 0;
		unsigned int iRightBrackets = 0;
		char chOperator = '&';
		IQueryUnitIndexCollection*	pQueryUnitIndexCollection = NULL;
		IQueryUnitIndexCollection*	pQueryUnitIndexCollectionFirst = NULL;
		IQueryIndex*				pFirstQueryIndex = NULL;
		IQueryIndex*				pLastQueryIndex = NULL;
						
		SearchSynonimCollection(pQueryUnit);
		SearchMorphoCollection(pQueryUnit);
		
		pQueryUnitIndexCollection = pQueryUnit->GetFirstQueryUnitIndexCollection();
		pQueryUnitIndexCollectionFirst = pQueryUnitIndexCollection;
		while (pQueryUnitIndexCollection)
		{
			//��������� ���������
			ApplyCollections(pQueryUnitIndexCollection, &pFirstQueryIndex, &pLastQueryIndex);
			if (!pFirstQueryIndex)
			{
				if (pQueryUnitIndexCollection == pQueryUnitIndexCollectionFirst)
				{
					pQueryUnitIndexCollection = pQueryUnitIndexCollection->GetNextQueryUnitIndexCollection();
					pQueryUnitIndexCollectionFirst = pQueryUnitIndexCollection;
					continue;
				}
				pQueryUnitIndexCollection = pQueryUnitIndexCollection->GetNextQueryUnitIndexCollection();
				continue;
			}
			if (pQueryUnitIndexCollection == pQueryUnitIndexCollectionFirst)
			{ (*ppqiFirst) = pFirstQueryIndex; }
			
			pLastQueryIndex->SetOperator(chOperator);
			(*ppqiLast) = pLastQueryIndex;
			
			pQueryUnitIndexCollection = pQueryUnitIndexCollection->GetNextQueryUnitIndexCollection();
		}
		if (!(*ppqiLast))
			return;
		(*ppqiLast)->SetOperator(0);
		iLeftBrackets = (*ppqiFirst)->GetLeftBrackets();
		iLeftBrackets++;
		(*ppqiFirst)->SetLeftBrackets(iLeftBrackets);
		iRightBrackets = (*ppqiLast)->GetRightBrackets();
		iRightBrackets++;
		(*ppqiLast)->SetRightBrackets(iRightBrackets);
	}
	SS_CATCH(L"")
}

void CQueryResultEx::ApplyGroups(IGroup* pGroup, IQueryIndex** ppqiFirst, IQueryIndex** ppqiLast)
{
	SS_TRY
	{
		unsigned int iLeftBrackets = 0;
		unsigned int iRightBrackets = 0;
		char chOperator = '&';
		IQueryUnit*		pQueryUnit = NULL;
		IQueryUnit*		pQueryUnitFirst = NULL;
		IQueryIndex*	pFirstQueryIndex = NULL;
		IQueryIndex*	pLastQueryIndex = NULL;
				
		pQueryUnit = pGroup->GetFirstQueryUnit();
		pQueryUnitFirst = pQueryUnit;
		while (pQueryUnit)
		{
			//��������� �������� IsObligatory
			m_oDataID.IsObligatory = pQueryUnit->IsObligatory();
			//��������� ���
			m_oDataID.fUnitWeight = pQueryUnit->GetWeight();
			//����� ����� �������
			FindQueryWord(pQueryUnit);
			//��������� ����
			ApplyUnits(pQueryUnit, &pFirstQueryIndex, &pLastQueryIndex);
			if (!pFirstQueryIndex)
			{
				if (pQueryUnit == pQueryUnitFirst)
				{
					pQueryUnit = pQueryUnit->GetNextQueryUnit();
					pQueryUnitFirst = pQueryUnit;
					continue;
				}
				pQueryUnit = pQueryUnit->GetNextQueryUnit();
				continue;
			}
			if (pQueryUnit == pQueryUnitFirst)
			{ (*ppqiFirst) = pFirstQueryIndex; }
			
			pLastQueryIndex->SetOperator(chOperator);
			(*ppqiLast) = pLastQueryIndex;
			
			//����� ���������� ����� �����
			m_uiQueryUnitID++;
			pQueryUnit = pQueryUnit->GetNextQueryUnit();
		}
		if (!(*ppqiLast))
			return;
		(*ppqiLast)->SetOperator(0);
		iLeftBrackets = (*ppqiFirst)->GetLeftBrackets();
		iLeftBrackets++;
		(*ppqiFirst)->SetLeftBrackets(iLeftBrackets);
		iRightBrackets = (*ppqiLast)->GetRightBrackets();
		iRightBrackets++;
		(*ppqiLast)->SetRightBrackets(iRightBrackets);
	}
	SS_CATCH(L"")
}

void CQueryResultEx::ApplyTransform(ITransformation* pTransformation, IQueryIndex** ppqiFirst, IQueryIndex** ppqiLast)
{
	SS_TRY
	{
		unsigned int iLeftBrackets = 0;
		unsigned int iRightBrackets = 0;
		char chOperator = '&';	
		IGroup*			pGroup = NULL;
		IGroup*			pGroupFirst = NULL;
		IQueryIndex*	pFirstQueryIndex = NULL;
		IQueryIndex*	pLastQueryIndex = NULL;
				
		pGroup = pTransformation->GetFirstGroup();
		pGroupFirst = pGroup;
		while (pGroup)
		{
			//�������� ���������� ������ � ������
			ControlCountUnitInGroup(pGroup);
			//��������� ������
			m_oDataID.uiGroupCount++;
			//��������� ��������� SequenceID
			if ( m_oDataID.uiRealSequenceID != pGroup->GetSequenceID() ) 
			{
				m_oDataID.uiRealSequenceID = pGroup->GetSequenceID();
				m_oDataID.bChangeRealSequenceID = true;
			}
			//��������� ������
			ApplyGroups(pGroup, &pFirstQueryIndex, &pLastQueryIndex);
			if (!pFirstQueryIndex)
			{
				if (pGroup == pGroupFirst)
				{
					pGroup = pGroup->GetNextGroup();
					pGroupFirst = pGroup;
					continue;
				}
				pGroup = pGroup->GetNextGroup();
				continue;
			}
			if (pGroup == pGroupFirst)
			{ (*ppqiFirst) = pFirstQueryIndex; }
			
			pLastQueryIndex->SetOperator(chOperator);
			(*ppqiLast) = pLastQueryIndex;
			
			pGroup = pGroup->GetNextGroup();
		}
		if (!(*ppqiLast))
			return;
		(*ppqiLast)->SetOperator(0);
		iLeftBrackets = (*ppqiFirst)->GetLeftBrackets();
		iLeftBrackets++;
		(*ppqiFirst)->SetLeftBrackets(iLeftBrackets);
		iRightBrackets = (*ppqiLast)->GetRightBrackets();
		iRightBrackets++;
		(*ppqiLast)->SetRightBrackets(iRightBrackets);
	}
	SS_CATCH(L"")
}

//������ ������
void CQueryResultEx::SetIQuery(IQuery* pQuery)		// ����������� ������������ IQuery
{
	SS_TRY
	{
		unsigned int iLeftBrackets = 0;
		unsigned int iRightBrackets = 0;
		char chOperator = '|';
		
		//��������� ������
		m_oDataID.DataIdToZero();
							
		ITransformation*	pTransformation = NULL;
		ITransformation*	pTransformationFirst = NULL;
		IQueryIndex*		pFirstQueryIndex = NULL;
		IQueryIndex*		pLastQueryIndex = NULL;
		IQueryIndex*		pqiFirst = NULL;
		IQueryIndex*		pqiLast = NULL;
		
		m_pQuery = pQuery;
		Clear();
		pTransformation = pQuery->GetFirstTransformation();
		pTransformationFirst = pTransformation;
		while (pTransformation)
		{
			m_uiQueryUnitID = 0;
			m_oDataID.uiGroupCount = 0;
			//��������� �������������
			ApplyTransform(pTransformation, &pFirstQueryIndex, &pLastQueryIndex);
			if (!pFirstQueryIndex)
			{
				if (pTransformation == pTransformationFirst)
				{
					pTransformation = pTransformation->GetNextTransformation();
					pTransformationFirst = pTransformation;
					continue;
				}
				pTransformation = pTransformation->GetNextTransformation();
				continue;
			}
			if (pTransformation == pTransformationFirst)
			{ pqiFirst = pFirstQueryIndex; }
			
			pLastQueryIndex->SetOperator(chOperator);
			pqiLast = pLastQueryIndex;
		
			//��������� �������������
			m_oDataID.uiTransformationID++;
			m_oDataID.bChangeTransformID = true;

			pTransformation = pTransformation->GetNextTransformation();
		}
		if (!pqiLast)
		{
			SAVE_LOG( SS_WARNING AND __WFUNCTION__ AND L"������� �� ����� �� ������ ������� !");
			return;
		}
		pqiLast->SetOperator(0);
		iLeftBrackets = pqiFirst->GetLeftBrackets();
		iLeftBrackets++;
		pqiFirst->SetLeftBrackets(iLeftBrackets);
		iRightBrackets = pqiLast->GetRightBrackets();
		iRightBrackets++;
		pqiLast->SetRightBrackets(iRightBrackets);

		//�������� ������
		Show();
		//ShowWords();
	}
	SS_CATCH(L"")
}

///������� IQuery �������������� � ������� SetIQuery
IQuery* CQueryResultEx::GetIQuery()
{
	return m_pQuery;
}

///������������ ���������� �������
void CQueryResultEx::SetQueryParams(TQueryParams* pQueryParams)
{
	SS_TRY
		if (pQueryParams)
		{
			m_QueryParams = (*pQueryParams);
		}
	SS_CATCH(L"")
}

///������������ ������ ���������������� ����������
void CQueryResultEx::SetLinguisticProcessorMode(TLinguisticProcessorMode* pLinguisticProcessorMode)
{
	SS_TRY
		if (pLinguisticProcessorMode)
		{
			m_LinguisticProcessorMode = (*pLinguisticProcessorMode);
		}
	SS_CATCH(L"")
}

//��������� ��������� ID
void CQueryResultEx::SDataID::DataIdToZero()
{
	uiRealSequenceID = 0;
	uiVirtualSequenceID = 0;
	uiTransformationID = 0;
	bChangeRealSequenceID = false;
	bChangeTransformID = true;
	fUnitWeight = 0;
}

//������ SequenceID � ������ �������������
unsigned int CQueryResultEx::SDataID::GetSequenceID()
{
	SS_TRY
	{
		if ( bChangeRealSequenceID ) 
		{ uiVirtualSequenceID++; }
		
		if ( bChangeTransformID )
		{ uiVirtualSequenceID = 0; }
		
		bChangeTransformID = false;
		bChangeRealSequenceID = false;
		
		return uiVirtualSequenceID;
	}
	SS_CATCH(L"")
}

void CQueryResultEx::Show()
{
	SS_TRY
	{	
		std::string sResults = "������ : ";

		for(SS::Interface::Core::CommonContainers::IQueryIndex* pQueryIndex = this->GetFirstQueryIndex(); pQueryIndex;
			pQueryIndex = this->GetNextQueryIndex())
		{
			int iLeft = pQueryIndex->GetLeftBrackets();
			while(iLeft != 0)
			{
				sResults += "(";
				iLeft--;
			}
			char szTo[20];
			sResults += _itoa(pQueryIndex->GetQueryIndex(), szTo, 10);
			sResults += "< ";
			sResults += "-";
			sResults += _itoa(pQueryIndex->GetAttributes().m_IndexPosition, szTo, 10);
			sResults += "-";
			sResults += _itoa(pQueryIndex->GetAttributes().m_SequenceID, szTo, 10);
			sResults += "-";
			sResults += _itoa(pQueryIndex->GetAttributes().m_TransformationID, szTo, 10);
			sResults += "-";
			sResults += _itoa(pQueryIndex->GetAttributes().m_Obligatory, szTo, 10);
			sResults += "> ";
			int iRight = pQueryIndex->GetRightBrackets();
			while(iRight != 0)
			{
				sResults += ")";
				iRight--;
			}
			sResults += pQueryIndex->GetOperator();							
		}
		USES_CONVERSION;
		std::wstring ws = A2W(sResults.c_str());
		SL_OUT_DEBUG_STR (ws.c_str());
	}
	SS_CATCH(L"")
}

///����������� ����� �������
void CQueryResultEx::FindQueryWord(IQueryUnit* pQueryUnit)
{
	SS_TRY
	{
		IQueryUnitIndexCollection*	pCollection = NULL;
		IQueryUnitIndex*			pIndex = NULL;
		
		//������� �����
		m_strWord = pQueryUnit->GetWord();
		//���������
		for ( pCollection = pQueryUnit->GetFirstQueryUnitIndexCollection(); pCollection; 
			  pCollection = pCollection->GetNextQueryUnitIndexCollection() )
		{
			//��������� �������������
			if (pCollection->GetIndexCollectionType() == SS::Interface::Core::BlackBox::eitMorphoIndex) 
			{
				//���� ���� ������
				if (pIndex = pCollection->GetFirstQueryUnitIndex()) 
				{
					//���� ���� ����������� �������������
					if (!m_strWord.empty()) 
						return;
					//���� ��� ������������ �������������
					wchar_t Word[50];
					SS::Dictionary::Types::SWordIndex oWordIndex;
					oWordIndex.m_DictIndex.SetDictionaryIndex(pIndex->GetIndex().GetDictionaryIndex());
					SS::Interface::Core::Dictionary::IMorphologyAnalyser* pMorphologyAnalyser = NULL;
					pMorphologyAnalyser = m_pDictionary->GetMorphologyAnalyser();
					if ( pMorphologyAnalyser->GetWord(&oWordIndex, Word) ) 
					{
						m_strWord = Word;
						return;
					}
					else
					{ 
						SAVE_LOG(L"��� ������������ �������������.");
						return;
					}
				}
			}
		}
	}
	SS_CATCH(L"")
}

///����� ���� �������
void CQueryResultEx::ShowWords()
{
	SS_TRY
	{
		ITransformation*			pTransformation = NULL;
		IGroup*						pGroup = NULL;
		IQueryUnit*					pQueryUnit = NULL;
		std::wstring				strWords;
				
		//������ ������ �������������
		if ( !(pTransformation = m_pQuery->GetFirstTransformation()) )
			return;
	
		//������
		for ( pGroup = pTransformation->GetFirstGroup(); pGroup; pGroup = pGroup->GetNextGroup() )
		{
			//�����
			for ( pQueryUnit = pGroup->GetFirstQueryUnit(); pQueryUnit; pQueryUnit = pQueryUnit->GetNextQueryUnit() )
			{
				FindQueryWord(pQueryUnit);
				strWords += m_strWord;
				strWords += L" + ";
			}
		}
		//�������� ������� ( + ) � �����
		unsigned int iSize = strWords.size();
		if (iSize >= 3)
		{
			--iSize;
			strWords.erase(strWords.begin() + iSize);
			--iSize;
			strWords.erase(strWords.begin() + iSize);
			--iSize;
			strWords.erase(strWords.begin() + iSize);
		}
		//������ � ���
		SAVE_LOG((wchar_t*)strWords.c_str() AND __WFUNCTION__);
	}
	SS_CATCH(L"")
}

///������������� ����� �� CBaseCoreClass
void CQueryResultEx::SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
{
	CBaseCoreClass::SetLoadManager(pLoadManager);
	m_pDictionary = (SS::Interface::Core::Dictionary::IDictionary*) 
	pLoadManager->GetInterface( DICTIONARIES_DLL_PATH, CLSID_IDictionary, IID_IDictionary);
}

///������� ���������� Unit-�� � ����� ������
void CQueryResultEx::ControlCountUnitInGroup(IGroup* pGroup)
{
	unsigned int iCount = 0;
	for (IQueryUnit* pQueryUnit = pGroup->GetFirstQueryUnit(); pQueryUnit; pQueryUnit = pQueryUnit->GetNextQueryUnit())
	{
		++iCount;
		if (iCount > 1)
		{
			m_bOneUnit = false;
			return;
		}
	}
	m_bOneUnit = true;
}


}
}
}


















