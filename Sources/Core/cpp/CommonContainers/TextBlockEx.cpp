//TextBlockEx.cpp
#include "StdAfx.h"
#include "textblockex.h"
#include "IndexAndPosition.h"
//��� ������������� IText-�
#include "..\ASSInterface\IBlackBoxDictionaryIndex.h"
#include "..\ASSInterface\IBlackBoxIndex.h"
#include "..\ASSInterface\TDictionaryNames.h"
#include "..\ASSInterface\TDictionaryManager.h"
#include "..\ASSInterface\Constants.h"
#ifdef _SS_UNITTESTS
	#include <iostream>
#endif

namespace SS
{
namespace Core
{
namespace CommonContainers
{

//������������
CTextBlockEx::CTextBlockEx(ILoadManager* pLoadManager) 
	: m_pBlackBoxTextStorage(NULL)
	, m_pLoadManager(NULL)
{
	SS_TRY
	{
		if (pLoadManager)
		{
			m_pLoadManager = pLoadManager;
			InitConnection();
		}		
	}
	SS_CATCH(L"")
}

CTextBlockEx::~CTextBlockEx()
{
}

void CTextBlockEx::InitConnection()		
{
	SS_TRY
	{
		m_pBlackBoxTextStorage = (IBlackBoxTextStorage*) m_pLoadManager->GetInterface(L"./core/linguistics/BlackBox.dll", CLSID_BlackBoxTextStorage, IID_BlackBoxTextStorage);
	}
	SS_CATCH(L"")
}

void CTextBlockEx::CopyTextFeature(ITextFeature* ptfTo,ITextFeature* ptfFrom)	// �������� TextFeature	
{
	SS_TRY
	{
		unsigned int uiSize;
		char* pBuff;
		ptfFrom->GetTextFeatureBuff(&pBuff, &uiSize);
		ptfTo->SetTextFeatureBuff(pBuff, uiSize);
	}
	SS_CATCH(L"")
}


void CTextBlockEx::UpdateRelevance()
{
	SS_TRY
	{
		CTextBlock::UpdateRelevance();

		unsigned int iRelevanceMax = 0; 
		for(ITextBlockCut* pTextBlockCut = GetFirstBlockCut(); pTextBlockCut; pTextBlockCut = GetNextBlockCut())
		{
			if(iRelevanceMax < pTextBlockCut->GetRelevance())
			{ iRelevanceMax = pTextBlockCut->GetRelevance(); }			
		}

		iRelevanceMax = ((iRelevanceMax / SS::Constants::RELEVANCE_MULTIPLIER) * SS::Constants::RELEVANCE_MULTIPLIER);
		iRelevanceMax += GetRelevance();
		SetRelevance(iRelevanceMax);
	}
	SS_CATCH(L"")
}

/// ������������� ������� IndicsationIndex � ServiceIndex
void CTextBlockEx::SetIndexes(ITextBlockCut* pTextBlockCut, IUnit* pUnit)
{
	SS_TRY
	{
		if (UINT_MAX == pUnit->GetPosition())
		{ return; }
		//�������� IIndexAndPosition
		CIndexAndPosition* pIndexAndPosition = dynamic_cast<CIndexAndPosition*> (pTextBlockCut->AddIndexAndPosition());
		pIndexAndPosition->SetUnit(pUnit);
	}
	SS_CATCH( (wchar_t*)pUnit->GetWord() )
}

//������������� �� CTextBlock
ITextFeature* CTextBlockEx::GetTextFeature()
{
	SS_TRY
	{
		ITextFeature* pTextFeature = NULL;
		pTextFeature = CTextBlock::GetTextFeature();
		pTextFeature->SetLoadManager(m_pLoadManager);
		return pTextFeature;
	}
	SS_CATCH(L"")
}

//������ ITextBlockEx
void CTextBlockEx::SetIText(IText* pText, bool bIsCopyTextFeature)// ����������� ������������ IText - � (�������� ��������� CommonContainers)
{
	SS_TRY
	{							
		using SS::Interface::Core::BlackBox::IParagraph;
		using SS::Interface::Core::BlackBox::ISentence;
		using SS::Interface::Core::CommonContainers::ITextBlockCut;
							
		IParagraph*		pParagraph = NULL;
		ISentence*		pSentence = NULL;
		IUnit*			pCurrUnit = NULL;
		IUnit*			pRightUnit = NULL;
		IUnit*			pChildUnit = NULL;
		ITextBlockCut*	pTextBlockCut = NULL;
			
		if (bIsCopyTextFeature)
		{ CopyTextFeature(GetTextFeature(), pText->GetTextFeature()); }
							
		//************************* ������� IText - � *****************************//
		pParagraph = pText->GetFirstParagraph();
		while (pParagraph)								
		{
			pTextBlockCut = AddBlockCut();
			ParagraphToCut(pParagraph, pTextBlockCut);
			pSentence = pParagraph->GetFirstSentence();
			while (pSentence)
			{
				pCurrUnit = pSentence->GetFirstUnit();
				//������� Unit - ��
				while (pCurrUnit)
				{
					pChildUnit = pCurrUnit->GetLeftChildUnit();
					if (pChildUnit)
					{
						pCurrUnit = pChildUnit;
						continue;	
					}
					SetIndexes(pTextBlockCut, pCurrUnit);
					pRightUnit = pCurrUnit->GetRightUnit();
					while (pRightUnit == NULL)
					{
						pCurrUnit = pCurrUnit->GetParentUnit();
						if (pCurrUnit == NULL)
						{ break; }
						SetIndexes(pTextBlockCut, pCurrUnit);
						pRightUnit = pCurrUnit->GetRightUnit();
					}
					pCurrUnit = pRightUnit;
				}
				//����� ����� Unit - ��
				pSentence = pSentence->GetNextSentence();
				//ViewTextBlockCut(pTextBlockCut);
			}
			pParagraph = pParagraph->GetNextParagraph();
		}
	}
	SS_CATCH(L"")
}

void CTextBlockEx::ViewTextBlockCut(ITextBlockCut* pTextBlockCut)
{
	SS_TRY
	{
		unsigned int uirevPosition = 0, uirevPositionFirstChar = 0;
		IIndexAndPosition * pIndexAndPosition = pTextBlockCut->GetFirstIndexAndPosition();
		while(pIndexAndPosition)
		{

#ifdef _SS_UNITTESTS

			if(uirevPosition > pIndexAndPosition->GetPosition())
			{
				SAVE_LOG(SS_WARNING AND L"uirevPosition > pCurrUnit->GetPosition()" AND __WFUNCTION__);
			}

			if(uirevPositionFirstChar > pIndexAndPosition->GetFirstCharPosition())
			{
				SAVE_LOG(SS_WARNING AND L"uirevPositionFirstChar > pCurrUnit->GetFirstCharPosition()" AND __WFUNCTION__);
			}

			uirevPositionFirstChar = pIndexAndPosition->GetFirstCharPosition();
			uirevPosition = pIndexAndPosition->GetPosition();
			wchar_t wsFromIToW1[20];
			wchar_t wsToMsg1[1000];
			wcscpy(wsToMsg1, L"������� �������� ����� = ");
			wcscat(wsToMsg1, _itow(pIndexAndPosition->GetPosition(), wsFromIToW1, 10));		
			wcscat(wsToMsg1, L" ������� ������� ������� �������� ����� = ");
			wcscat(wsToMsg1, _itow(pIndexAndPosition->GetFirstCharPosition(), wsFromIToW1, 10));		
			wcscpy(wsToMsg1, L" ������� ����� : ");					
			wcscat(wsToMsg1, pIndexAndPosition->GetWord());		
			wcscat(wsToMsg1, L" ������ : ");					
			wcscat(wsToMsg1, _itow(pIndexAndPosition->GetServiceIndex()->GetViewIndex()->m_DictionaryIndex , wsFromIToW1, 10));		
			wcscat(wsToMsg1, L" ����� ������� : ");					
			wcscat(wsToMsg1, _itow((pIndexAndPosition->GetServiceIndex()->GetViewIndex()->m_DictionaryIndex >> 24) , wsFromIToW1, 10));				

			SAVE_LOG(SS_MESSAGE AND wsToMsg1 AND __WFUNCTION__);
#endif
			pIndexAndPosition = pTextBlockCut->GetNextIndexAndPosition();
		}
	}
	SS_CATCH(L"")
}

//����������� ������������ IText - � (�������� ��������� IText)
IText* CTextBlockEx::GenerateIText()	
{
	SS_TRY
	{
		SS::Interface::Core::CommonContainers::ITextBlockCut*		pTextBlockCut = NULL;
		SS::Interface::Core::CommonContainers::IIndexAndPosition*	pIndexAndPosition = NULL;
		SS::Interface::Core::BlackBox::IText*						pText = NULL;
		SS::Interface::Core::BlackBox::IParagraph*					pParagraph = NULL;
		SS::Interface::Core::BlackBox::ISentence*					pSentence = NULL;
		SS::Interface::Core::BlackBox::IUnit*						pUnit = NULL;
		CIndexAndPosition*														pCIndexAndPosition = NULL;
				
		//������ IText 
		pText = m_pBlackBoxTextStorage->CreateText();						
		
		//*************** ����������� TextFeature *******************
		CopyTextFeature(pText->GetTextFeature(), GetTextFeature());

		pTextBlockCut = GetFirstBlockCut();
		while (pTextBlockCut)
		{
			//������ IParagraph
			pParagraph = m_pBlackBoxTextStorage->CreateParagraph();				
			pText->AddParagraph(pParagraph);

			//������ ISentence
			pSentence = m_pBlackBoxTextStorage->CreateSentence();				
			pParagraph->AddSentence(pSentence);

			//����������� � �������� ���������� �� ����-����
			CutToParagraph(pTextBlockCut, pParagraph);
			
			pIndexAndPosition = pTextBlockCut->GetFirstIndexAndPosition();
			while (pIndexAndPosition)
			{
				pCIndexAndPosition = dynamic_cast<CIndexAndPosition*>(pIndexAndPosition);
				if (pUnit = pCIndexAndPosition->GetUnit()) 
				{
					//�� ������� Unit
					pCIndexAndPosition->NotDeleteUnit();
					if (pCIndexAndPosition->IsValid()) 
					{
						pSentence->AddUnit(pUnit);
					}
					else
					{
						pUnit->ReleaseUnitHorizontal();
					}
				}
				pIndexAndPosition = pTextBlockCut->GetNextIndexAndPosition();
			}
			pTextBlockCut = GetNextBlockCut();
		}
		return pText;
	}
	SS_CATCH(L"")
}

///������������ ������ ���������������� ����������
void CTextBlockEx::SetLinguisticProcessorMode(TLinguisticProcessorMode* pLinguisticProcessorMode)
{
	SS_TRY
	{
		if (pLinguisticProcessorMode)
		{ m_LinguisticProcessorMode = (*pLinguisticProcessorMode); }
	}
	SS_CATCH(L"")
}

///����������� � ����-��� ���������� �� ��������
void CTextBlockEx::ParagraphToCut( SS::Interface::Core::BlackBox::IParagraph* pParagraph,
								   SS::Interface::Core::CommonContainers::ITextBlockCut* pTextBlockCut )
{
	pTextBlockCut->SetIndexTypeName(pParagraph->GetIndexTypeName());
	pTextBlockCut->SetRelevance(pParagraph->GetRelevance());
	pTextBlockCut->SetLevel(pParagraph->GetLevel());
	pTextBlockCut->SetNumber(pParagraph->GetNumber());
	pTextBlockCut->SetType(pParagraph->GetType());
}

///����������� � �������� ���������� �� ����-����
void CTextBlockEx::CutToParagraph( SS::Interface::Core::CommonContainers::ITextBlockCut* pTextBlockCut,
								   SS::Interface::Core::BlackBox::IParagraph* pParagraph )
{
	pParagraph->SetIndexTypeName(pTextBlockCut->GetIndexTypeName());
	pParagraph->SetRelevance(pTextBlockCut->GetRelevance());
	pParagraph->SetLevel(pTextBlockCut->GetLevel());
	pParagraph->SetNumber(pTextBlockCut->GetNumber());
	pParagraph->SetType(pTextBlockCut->GetType());
}

///������� ������� � ��������� (������� ���� � ������ ������)
ITextBlockCut* CTextBlockEx::AddBlockCut()
{
	SS_TRY
	{
		ITextBlockCut *pTextBlockCut = NULL;
		pTextBlockCut = m_pContainersFactory->CreateTextBlockCut(m_pBlackBoxTextStorage, &m_LinguisticProcessorMode);
		CTextBlock::AddCut(pTextBlockCut);
		return pTextBlockCut;
	}
	SS_CATCH(L"")
}

}
}
}