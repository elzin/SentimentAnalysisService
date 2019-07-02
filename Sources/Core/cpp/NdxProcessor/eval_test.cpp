#include "StdAfx.h"

#ifdef _SS_UNITTESTS

#include ".\eval_test.h"
#include ".\test_const.h"
#include ".\console.h"
//#include "../containers/workregister.h"
//#include ".\ndxindexationmanager.h"
//#include ".\eval.h"
//#include ".\search_factory.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SS::UnitTests::NdxSE::NdxProcessor::Extracting::CEvaluator_test);

namespace SS
{
namespace UnitTests
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Extracting
{

//using namespace SS::Core::NdxSE::NdxProcessor::Extracting;

//--------------------------------------------------------------------//

//void CEvaluator_test::Test(void)
//{
//	//����������� �������� ����
//	UT_STOP_LOGING
//	Indexate();
//	
//	CManagerConnections ManagerConnection;
//	CWorkRegister WorkRegister;
//	CNdxExtractingManager EM;
//
//	//��������� �������� ����
//	EM.SetDatabasePath((char*)WorkRegister.GetParametr(L"PathDataBase").c_str());
//	ManagerConnection.OpenStorage(cszTestBaseName);
//	EM.SetManagerConnections(&ManagerConnection);
//	EM.OpenStorage(cszTestBaseName);
//
//
//	//��������� ����� �� �������� ����
//	Search(&EM);
//	//Search1(&EM);
//
//	//��������� �������� ����
//	EM.CloseStorage();
//	UT_START_LOGING
//}
//
//void CEvaluator_test::Search(SS::Core::Ndx::CNdxExtractingManager* pEM)
//{
//	//������ ���������� �� �����
//	SSearchParameter SearchParameter(10);
//	//SearchParameter.AdjacentSearch(3);
//	SearchParameter.UseStatistic(true, true, false);
//	//SearchParameter.m_isSaveAnswerPositions=true;
//	//SearchParameter.FuzzySearch(0, 0);
//	//SearchParameter.SearchInObtained(SSearchParameter::esiomText);
//
//	//������ ��������� ���������� �������
//	typedef void (SS::UnitTests::Ndx::Extracting::CEvaluator_test::* PMakeRequest)(SS::Core::Ndx::LBaseSearchWords*);
//	PMakeRequest p[]={&CEvaluator_test::MakeRequest, &CEvaluator_test::MakeRequest1, &CEvaluator_test::MakeRequest2, &CEvaluator_test::MakeRequest3, &CEvaluator_test::MakeRequest4, &CEvaluator_test::MakeRequest5, &CEvaluator_test::MakeRequest6, &CEvaluator_test::MakeRequest7};
//	
//	//�������� �� ��������� ���������� �������
//	for(int i=0; i<7; i++){
//		//������� ������
//		LBaseSearchWords BaseSearchWords;
//		(this->*p[i])(&BaseSearchWords);
//		
//		//������� ��������� �������
//		CSearchFactory SearchFactory(
//			pEM->GetIndexationInfo(), 
//			&SearchParameter, 
//			pEM->GetDocNormTable(), 
//			pEM->GetSourceIndexesOffsetTable(), 
//			pEM->GetTextAbsOffsetTable(), 
//			NULL,
//			NULL,
//			&BaseSearchWords);
//		
//		//�������� �����������
//		CEvaluator* pEvaluator=SearchFactory.CreateEvaluator();
//
//		//pEvaluator->View();
//
//		//���������
//		pEvaluator->Calculate();
//
//		pEvaluator->ViewResultsContainer();
//		
//		delete pEvaluator;
//	}
//}
//
//void CEvaluator_test::Search1(SS::Core::Ndx::CNdxExtractingManager* pEM)
//{
//	////������ ��������� ���������� �������
//	//typedef void (SS::UnitTests::Ndx::Extracting::CEvaluator_test::* PMakeRequest)(SS::Core::Ndx::LBaseSearchWords*);
//	//PMakeRequest p[]={&CEvaluator_test::MakeRequest, &CEvaluator_test::MakeRequest1, &CEvaluator_test::MakeRequest2, &CEvaluator_test::MakeRequest3, &CEvaluator_test::MakeRequest4, &CEvaluator_test::MakeRequest5, &CEvaluator_test::MakeRequest6, &CEvaluator_test::MakeRequest7};
//
//	////������ ���������� �� �����
//	//SSearchParameter SearchParameter(10);
//	////SearchParameter.AdjacentSearch(3);
//	//SearchParameter.UseStatistic(true, true, false);
//	////SearchParameter.FuzzySearch(0, 0);
//	////SearchParameter.SearchInObtained(SSearchParameter::esiomText);
//
//	//CResultsContainer* pTempResultsContainer=NULL;
//
//	////�������� �� ��������� ���������� �������
//	//for(int i=1; i<3; i++){
//	//	if(SearchParameter.m_isSearchInObtained)
//	//		ToConsole(L"*- SearchInObtained Mode On -*");
//
//	//	//������� ������
//	//	LBaseSearchWords BaseSearchWords;
//	//	(this->*p[i])(&BaseSearchWords);
//	//	
//	//	//������� ��������� ���������
//	//	CCoordinateConvertor CoordinateConvertor(
//	//		NULL, 
//	//		pEM->GetIndexationInfo(), 
//	//		pEM->GetTextAbsOffsetTable(), NULL);
//	//	
//	//	//������� ��������� �������
//	//	CSearchFactory SearchFactory(
//	//		pEM->GetIndexationInfo(), 
//	//		&SearchParameter, 
//	//		pEM->GetDocNormTable(), 
//	//		pEM->GetSourceIndexesOffsetTable(), 
//	//		pEM->GetTextAbsOffsetTable(), &CoordinateConvertor, pTempResultsContainer);
//	//	
//	//	//������� ������ �������
//	//	CESFillerFromBSW ESFillerFromBSW(&SearchFactory, &BaseSearchWords, pEM->GetIndexationInfo(), pEM->GetSourceIndexesOffsetTable());
//	//	ESFillerFromBSW.ViewFillingSource();
//
//	//	//�������� �����������
//	//	CEvaluator* pEvaluator=SearchFactory.CreateEvaluator();
//
//	//	//������ �����������
//	//	pEvaluator->Init(&ESFillerFromBSW);
//	//	//pEvaluator->View();
//
//	//	//���������
//	//	pEvaluator->Calculate();
//
//	//	pEvaluator->ViewResultsContainer();
//	//	
//	//	//�������� � ����������� ��������� �����������
//	//	pTempResultsContainer=pEvaluator->ExtractResultsContainer();
//	//	//�������� ����� � ���������
//	//	SearchParameter.SearchInObtained(SSearchParameter::esiomText);
//	//	
//	//	delete pEvaluator;
//	//}
//}
//
//void CEvaluator_test::Indexate()
//{
//	//������������ ����������,
//	//���� ����������� � ����� "UT", ��� ��� ����� ���-����
//	//������� ���������� ��������� ��������� ����.
//
//	CManagerConnections ManagerConnection;
//	CWorkRegister WorkRegister;
//	CNdxIndexationManager IM;
//	IBlackBoxTextStorage* pBlackBoxTextStorage=NULL;
//	ManagerConnection.CreateAndRegister(L"./core/linguistics/BlackBox.dll", 
//		CLSID_BlackBoxTextStorage, IID_BlackBoxTextStorage, (void**)&pBlackBoxTextStorage);
//	IText* pText=pBlackBoxTextStorage->CreateText(); 
//	FillText(pText, pBlackBoxTextStorage);
//
//	IText* pText1=pBlackBoxTextStorage->CreateText(); 
//	FillText1(pText1, pBlackBoxTextStorage);
//	
//	//������� ����
//	IM.SetManagerConnections(&ManagerConnection);
//	IM.SetDatabasePath((char*)WorkRegister.GetParametr(L"PathDataBase").c_str());
//	ManagerConnection.OpenStorage(cszTestBaseName);
//	IM.ClearStorage(cszTestBaseName);
//	IM.OpenStorage(cszTestBaseName);
//
//	for(int i=0; i<3; i++){
//		//�����������
//		pText->GetTextFeature()->SetTextNumber(i);
//		IM.StartIndexation(pText);
//		IM.IndexateNext(pText);
//		IM.EndIndexation(false);
//	}
//
//	for(int i=3; i<5; i++){
//		//�����������
//		pText1->GetTextFeature()->SetTextNumber(i);
//		IM.StartIndexation(pText1);
//		IM.IndexateNext(pText1);
//		IM.EndIndexation(false);
//	}
//
//	pText->ReleaseText();
//	pText1->ReleaseText();
//
//	IM.EndIndexation(true);
//	IM.CloseStorage();
//}
//
//void CEvaluator_test::FillText(IText* pText, IBlackBoxTextStorage* pBlackBoxTextStorage)
//{
//	if(ISNULL(pText)) return;
//	if(ISNULL(pBlackBoxTextStorage)) return;
//
//	//���������� ������
//	for(unsigned int i=0; i<1; i++){
//		IParagraph* pParagraph=pBlackBoxTextStorage->CreateParagraph();
//		pText->AddParagraph(pParagraph);
//		ISentence* pSentence=pBlackBoxTextStorage->CreateSentence();
//		pParagraph->AddSentence(pSentence);
//		for(unsigned int w=0; w<2; w++){
//			IUnit* pUnit=pBlackBoxTextStorage->CreateUnit();
//			pSentence->AddUnit(pUnit);
//			pUnit->SetWord(L"xxx");
//			pUnit->m_Tag=0;
//			IIndex* pIndex=pBlackBoxTextStorage->CreateIndex();
//			pUnit->AddIndex(pIndex);
//			pIndex->GetDictionaryIndex()->AppendIndex(w);
//			pIndex->SetIndexationFlag(true);
//		}
//
//		pSentence=pBlackBoxTextStorage->CreateSentence();
//		pParagraph->AddSentence(pSentence);
//		for(unsigned int w=1; w<3; w++){
//			IUnit* pUnit=pBlackBoxTextStorage->CreateUnit();
//			pSentence->AddUnit(pUnit);
//			pUnit->SetWord(L"xxx");
//			pUnit->m_Tag=0;
//			IIndex* pIndex=pBlackBoxTextStorage->CreateIndex();
//			pUnit->AddIndex(pIndex);
//			pIndex->GetDictionaryIndex()->AppendIndex(w);
//			pIndex->SetIndexationFlag(true);
//		}
//
//		pSentence=pBlackBoxTextStorage->CreateSentence();
//		pParagraph->AddSentence(pSentence);
//		for(unsigned int w=3; w<8; w++){
//			IUnit* pUnit=pBlackBoxTextStorage->CreateUnit();
//			pSentence->AddUnit(pUnit);
//			pUnit->SetWord(L"xxx");
//			pUnit->m_Tag=0;
//			IIndex* pIndex=pBlackBoxTextStorage->CreateIndex();
//			pUnit->AddIndex(pIndex);
//			pIndex->GetDictionaryIndex()->AppendIndex(w);
//			pIndex->SetIndexationFlag(true);
//		}
//	}
//}
//
//void CEvaluator_test::FillText1(IText* pText, IBlackBoxTextStorage* pBlackBoxTextStorage)
//{
//	if(ISNULL(pText)) return;
//	if(ISNULL(pBlackBoxTextStorage)) return;
//
//	//���������� ������
//	for(unsigned int i=0; i<1; i++){
//		IParagraph* pParagraph=pBlackBoxTextStorage->CreateParagraph();
//		pText->AddParagraph(pParagraph);
//		ISentence* pSentence=pBlackBoxTextStorage->CreateSentence();
//		pParagraph->AddSentence(pSentence);
//		for(unsigned int w=2; w<3; w++){
//			IUnit* pUnit=pBlackBoxTextStorage->CreateUnit();
//			pSentence->AddUnit(pUnit);
//			pUnit->SetWord(L"xxx");
//			pUnit->m_Tag=0;
//			IIndex* pIndex=pBlackBoxTextStorage->CreateIndex();
//			pUnit->AddIndex(pIndex);
//			pIndex->GetDictionaryIndex()->AppendIndex(w);
//			pIndex->SetIndexationFlag(true);
//		}
//
//	}
//}
//
//void CEvaluator_test::MakeRequest(SS::Core::Ndx::LBaseSearchWords* pBaseSearchWords)
//{
//	if(ISNULL(pBaseSearchWords)) return;
//
//	//����� ������, ���������� ������������
//
//	//------------------------------------------------
//	//������� �������� ������������������ �������
//	SLogic Operators;
//	unsigned int uiSourceIndex=0;
//
//	//((1&(2&3&4)|(5&6))&(7))
//
//	uiSourceIndex=1;
//	Operators.m_sLogicOperator="&";
//	Operators.m_sLeftBrackets="((L";
//	Operators.m_sRightBrackets="";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	uiSourceIndex=2;
//	Operators.m_sLogicOperator="&";
//	Operators.m_sLeftBrackets="(L";
//	Operators.m_sRightBrackets="";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	uiSourceIndex=3;
//	Operators.m_sLogicOperator="&";
//	Operators.m_sLeftBrackets="";
//	Operators.m_sRightBrackets="";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	uiSourceIndex=4;
//	Operators.m_sLogicOperator="|";
//	Operators.m_sLeftBrackets="";
//	Operators.m_sRightBrackets=")";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	uiSourceIndex=5;
//	Operators.m_sLogicOperator="&";
//	Operators.m_sLeftBrackets="(L";
//	Operators.m_sRightBrackets="";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	uiSourceIndex=6;
//	Operators.m_sLogicOperator="&";
//	Operators.m_sLeftBrackets="";
//	Operators.m_sRightBrackets="))";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	uiSourceIndex=7;
//	Operators.m_sLogicOperator="";
//	Operators.m_sLeftBrackets="(L";
//	Operators.m_sRightBrackets="))";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//	//------------------------------------------------
//
//}
//
//void CEvaluator_test::MakeRequest1(SS::Core::Ndx::LBaseSearchWords* pBaseSearchWords)
//{
//	if(ISNULL(pBaseSearchWords)) return;
//
//	//����� ������, ���������� ������������
//
//	//------------------------------------------------
//	//������� �������� ������������������ �������
//	SLogic Operators;
//	unsigned int uiSourceIndex=0;
//
//	//(1&2)
//
//	uiSourceIndex=1;
//	Operators.m_sLogicOperator="&";
//	Operators.m_sLeftBrackets="(L";
//	Operators.m_sRightBrackets="";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	uiSourceIndex=2;
//	Operators.m_sLogicOperator="";
//	Operators.m_sLeftBrackets="";
//	Operators.m_sRightBrackets=")";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	//------------------------------------------------
//
//}
//
//void CEvaluator_test::MakeRequest2(SS::Core::Ndx::LBaseSearchWords* pBaseSearchWords)
//{
//	if(ISNULL(pBaseSearchWords)) return;
//
//	//���������� � �� �� ������������ ��������
//
//	//------------------------------------------------
//	//������� �������� ������������������ �������
//	SLogic Operators;
//	unsigned int uiSourceIndex=0;
//
//	//(1|2)
//
//	uiSourceIndex=1;
//	Operators.m_sLogicOperator="|";
//	Operators.m_sLeftBrackets="(L";
//	Operators.m_sRightBrackets="";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	uiSourceIndex=2;
//	Operators.m_sLogicOperator="";
//	Operators.m_sLeftBrackets="";
//	Operators.m_sRightBrackets=")";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	//------------------------------------------------
//
//}
//
//void CEvaluator_test::MakeRequest3(SS::Core::Ndx::LBaseSearchWords* pBaseSearchWords)
//{
//	if(ISNULL(pBaseSearchWords)) return;
//
//	//���������� � �� � �� �� ������ ��������
//
//	//------------------------------------------------
//	//������� �������� ������������������ �������
//	SLogic Operators;
//	unsigned int uiSourceIndex=0;
//
//	//(0|3)
//
//	uiSourceIndex=0;
//	Operators.m_sLogicOperator="|";
//	Operators.m_sLeftBrackets="(L";
//	Operators.m_sRightBrackets="";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	uiSourceIndex=3;
//	Operators.m_sLogicOperator="";
//	Operators.m_sLeftBrackets="";
//	Operators.m_sRightBrackets=")";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	//------------------------------------------------
//
//}
//
//void CEvaluator_test::MakeRequest4(SS::Core::Ndx::LBaseSearchWords* pBaseSearchWords)
//{
//	if(ISNULL(pBaseSearchWords)) return;
//
//	//���������� �� ������ �������� �� �������
//
//	//------------------------------------------------
//	//������� �������� ������������������ �������
//	SLogic Operators;
//	unsigned int uiSourceIndex=0;
//
//	//(0&3)
//
//	uiSourceIndex=0;
//	Operators.m_sLogicOperator="&";
//	Operators.m_sLeftBrackets="(L";
//	Operators.m_sRightBrackets="";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	uiSourceIndex=3;
//	Operators.m_sLogicOperator="";
//	Operators.m_sLeftBrackets="";
//	Operators.m_sRightBrackets=")";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//	//------------------------------------------------
//
//}
//
//void CEvaluator_test::MakeRequest5(SS::Core::Ndx::LBaseSearchWords* pBaseSearchWords)
//{
//	if(ISNULL(pBaseSearchWords)) return;
//
//	//����� ����� ��� � ����
//
//	//------------------------------------------------
//	//������� �������� ������������������ �������
//	SLogic Operators;
//	unsigned int uiSourceIndex=0;
//
//	//(8)
//
//	uiSourceIndex=8;
//	Operators.m_sLogicOperator="";
//	Operators.m_sLeftBrackets="(L";
//	Operators.m_sRightBrackets=")";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//	//------------------------------------------------
//
//}
//
//void CEvaluator_test::MakeRequest6(SS::Core::Ndx::LBaseSearchWords* pBaseSearchWords)
//{
//	if(ISNULL(pBaseSearchWords)) return;
//
//	//����� ����� ����� ��� � ����, ���� ���� ������� ������� ���
//
//	//------------------------------------------------
//	//������� �������� ������������������ �������
//	SLogic Operators;
//	unsigned int uiSourceIndex=0;
//
//	//(0&8)
//
//	uiSourceIndex=0;
//	Operators.m_sLogicOperator="&";
//	Operators.m_sLeftBrackets="(L";
//	Operators.m_sRightBrackets="";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	uiSourceIndex=8;
//	Operators.m_sLogicOperator="";
//	Operators.m_sLeftBrackets="";
//	Operators.m_sRightBrackets=")";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//	//------------------------------------------------
//
//}
//
//void CEvaluator_test::MakeRequest7(SS::Core::Ndx::LBaseSearchWords* pBaseSearchWords)
//{
//	if(ISNULL(pBaseSearchWords)) return;
//
//	//����� ����� ����� ��� � ����, ���� ���� ������� ���������� ������������
//
//	//------------------------------------------------
//	//������� �������� ������������������ �������
//	SLogic Operators;
//	unsigned int uiSourceIndex=0;
//
//	//(0|8)
//
//	uiSourceIndex=0;
//	Operators.m_sLogicOperator="|";
//	Operators.m_sLeftBrackets="(L";
//	Operators.m_sRightBrackets="";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//
//	uiSourceIndex=8;
//	Operators.m_sLogicOperator="";
//	Operators.m_sLeftBrackets="";
//	Operators.m_sRightBrackets=")";
//	pBaseSearchWords->push_back(CBaseSearchWord(uiSourceIndex, 0.0, Operators, SIndexAttributes()));
//	//------------------------------------------------
//
//}

//--------------------------------------------------------------------//

}
}
}
}
}

#endif //_SS_UNITTESTS
