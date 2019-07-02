#include "StdAfx.h"
#include ".\stat_eval.h"
#include <math.h>
#include ".\coordinate_convertor.h"

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

using namespace SS::Core::NdxSE::NdxProcessor::Containers;
using namespace SS::Core::NdxSE::NdxProcessor::Storages;
using namespace SS::Interface::Core::NdxSE::NdxDataStorage; 

//--------------------------------------------------------------------//

void CStatisticIndex::AddArgumentPosition(CComplexArgument* pComplexArgument, CCoordinateNode_4s* pCoordinateNode)
{
	if(pComplexArgument->GetArgumentID()==m_uiIndex){
		m_pCoordinateNode=pCoordinateNode;
	}else{
		TO_CONSOLE(L"Invalid index!!!");
		ToConsole(L"This index", m_uiIndex);
		ToConsole(L"Argument index", pComplexArgument->GetArgumentID());
	}
}

//--------------------------------------------------------------------//

CStatisticEvaluator::CStatisticEvaluator(CIndexStatisticStorage* pIndexStorage, unsigned int uiTotalTextsNumber)
:m_pIndexStorage(pIndexStorage), m_uiTotalTextsNumber(uiTotalTextsNumber), m_uiCurrBasisTextsNumber(0)
{
}

CStatisticEvaluator::~CStatisticEvaluator(void)
{
	TStatisticIndexCollection::iterator itIndex=m_StatisticIndexCollection.begin();
	do{
		if(itIndex->second){	
			delete itIndex->second;
		}
	}while(++itIndex!=m_StatisticIndexCollection.end());
	m_StatisticIndexCollection.clear();
}

void CStatisticEvaluator::AddIndex(unsigned int uiIndex)
{
	//��������� ������� � ���������
	TStatisticIndexCollection::iterator itStatisticIndex=m_StatisticIndexCollection.find(uiIndex);
	if(itStatisticIndex==m_StatisticIndexCollection.end()){
		itStatisticIndex=m_StatisticIndexCollection.insert(TStatisticIndexCollection::value_type(uiIndex, new CStatisticIndex(uiIndex))).first;
	}

	//���������� ��������� ������� �������
	itStatisticIndex->second->SetInversDocumentFrequency(CalculateInversDocumentFrequency(itStatisticIndex->second->GetIndex()));
}

void CStatisticEvaluator::AddArgumentPosition(CComplexArgument* pComplexArgument, CCoordinateNode_4s* pCoordinateNode)
{
	if(ISNULL(pComplexArgument)) return;

	TStatisticIndexCollection::iterator itStatisticIndex=m_StatisticIndexCollection.find(pComplexArgument->GetArgumentID());
	if(itStatisticIndex!=m_StatisticIndexCollection.end()){
		itStatisticIndex->second->AddArgumentPosition(pComplexArgument, pCoordinateNode);
	}

}

float CStatisticEvaluator::CalculateInversDocumentFrequency(unsigned int uiIndex)
{
	float fTemp=0.0;
	if(ISNULL(m_pIndexStorage)) return fTemp;
	if(uiIndex==EMPTY_VALUE) return fTemp;

	//���� �������� �� �������������, ������� ���� �� ������� - ������� �������������
	unsigned int uiEntryPoint, uiDocumentFrequency;

	//�������� ������� ������������� ������� � ��������� ����������
	m_pIndexStorage->GetIndexEntryPointTable()->GetIndexData(uiIndex, &uiEntryPoint, &uiDocumentFrequency);

	if(uiDocumentFrequency && m_uiTotalTextsNumber){
		//���� �������� ���������� ��������� �������� ������������� ������� � ������
		fTemp=(float)(m_uiTotalTextsNumber/uiDocumentFrequency);
	}

	return fTemp;
}

unsigned int CStatisticEvaluator::SetDocumentBasisIndex(unsigned int uiValue)
{
	m_uiCurrBasisTextsNumber=uiValue;
	return m_uiCurrBasisTextsNumber;
}

float CStatisticEvaluator::Evaluate(unsigned int uiEvalID)
{

	float fQueryWeightInText=0.0;
	float fIndexWeight=0.0;

	if(m_uiCurrBasisTextsNumber==EMPTY_VALUE){
		return fQueryWeightInText;
	}

	unsigned int uiTextID=m_uiCurrBasisTextsNumber+uiEvalID;

	if(uiTextID>=m_uiTotalTextsNumber){
		TO_CONSOLE(L"Invalid TextID");
		ToConsole(L"uiTextID", uiTextID);
		return fQueryWeightInText;
	}

	/*
	//������ ��������������� ���� ������� ���������� �� ������� ��������� ������
	//TFxIDF(Q, D)=( 1/log(L) ) * Summ(log(t+1)*log(N/n)), ���
	//Q - ������� ������
	//D - ������� ��������
	//L - ����� ��������� D � �������� (����� ���������)
	//Summ - ����� ��� ���� �������� �������
	//t - ������� ������� � ��������� D
	//N - ���������� ���������� � ���������
	//n - ���������� ���������� � ������� ����������� ������ ������
	*/

	//�������� ����������� ����������� ��� ������� ���������
	unsigned int uiDocumentNormKoef=m_pIndexStorage->GetDocNormStorage()->GetDocNorm(uiTextID);
	float fNorm=(float)(uiDocumentNormKoef);
	
	if(fNorm!=0){
		//��������� ���� �������� � ��������� ��
		float fIndexTextFrequency=0.0;
		float fFreqIncreaseKoef=0.0;
		CPosCnt* pPosCnt=NULL;
		TStatisticIndexCollection::iterator itIndex=m_StatisticIndexCollection.begin();
		do{
			if(itIndex->second && itIndex->second->GetCoordinateContainer()){	
				pPosCnt=dynamic_cast<CPosCnt*>(itIndex->second->GetCoordinateContainer()->GetChild(uiEvalID));
				if(pPosCnt){
					//�������� ������� ������� � ������ ���������
					fIndexTextFrequency=(float)pPosCnt->GetOrtsNumber();
					
					//�������� ������� � ����������� �� ������������ ��������� �����������
					fFreqIncreaseKoef=(float)pPosCnt->GetFreqIncreaseKoef();
					if(fFreqIncreaseKoef!=0){
						fIndexTextFrequency+=fFreqIncreaseKoef*(fIndexTextFrequency/100);
					}

					//��������� ��� ������� (TFxIDF(Q, D))
					fIndexWeight=log(fIndexTextFrequency+1)*
						log(itIndex->second->GetInversDocumentFrequency()+1);
					
					//��������� � ������ ����
					fQueryWeightInText+=fIndexWeight;
				}
			}
		}while(++itIndex!=m_StatisticIndexCollection.end());
		
		//��������� ���������� ���
		fQueryWeightInText=fQueryWeightInText/log(fNorm);
	}

	fQueryWeightInText=fQueryWeightInText*100;
	return fQueryWeightInText>=1000?(1000-1):fQueryWeightInText;
}

void CStatisticEvaluator::Clear(void)
{
	TStatisticIndexCollection::iterator itIndex=m_StatisticIndexCollection.begin();
	do{
		if(itIndex->second){	
			itIndex->second->Clear();
		}
	}while(++itIndex!=m_StatisticIndexCollection.end());
}

//--------------------------------------------------------------------//

}
}
}
}
}
}