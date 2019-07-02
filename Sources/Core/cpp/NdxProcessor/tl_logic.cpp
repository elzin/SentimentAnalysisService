#include "StdAfx.h"
#include ".\tl_logic.h"
#include ".\console.h"
#include ".\arg_res.h"
#include ".\acc_containers.h"
#include ".\coordinate_convertor.h"
#include <math.h>
#include ".\arg_complex.h"

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

CTextLevelLogic::CTextLevelLogic(unsigned int uiAllTextsNumber, CIndexStatisticStorage* pIndexStorage)
:CFuzzyLogic(CLogic::elTextStatistic), 
m_uiAllTextsNumber(uiAllTextsNumber), 
m_pIndexStorage(pIndexStorage), m_fInversDocumentFrequency(0)
{
}

void CTextLevelLogic::CalculateInversDocumentFrequency(CComplexArgument* pComplexArgument)
{
	//������ ��������� �� ����������
	if(!IsActive()) return;

	if(ISNULL(pComplexArgument)) return;
	if(ISNULL(m_pIndexStorage)) return;

	if(pComplexArgument->GetArgumentID()!=EMPTY_VALUE){
		//���� �������� �� �������������, ������� ���� �� ������� - ������� �������������
		unsigned int uiEntryPoint, uiDocumentFrequency;

		//�������� ������� ������������� ������� � ��������� ����������
		m_pIndexStorage->GetIndexEntryPointTable()->GetIndexData(
			pComplexArgument->GetArgumentID(), &uiEntryPoint, &uiDocumentFrequency);

		if(uiDocumentFrequency && m_uiAllTextsNumber){
			//���� �������� ���������� ��������� �������� ������������� ������� � ������
			m_fInversDocumentFrequency=
				ComputeInversDocumentFrequency(m_uiAllTextsNumber, uiDocumentFrequency);
		}
	}
}

CValue* CTextLevelLogic::CreateLogicValue(CValue* pValue, CComplexArgument* pComplexArgument)
{
	//������ ��������� �� ����������
	if(!IsActive()) return NULL;

	if(pValue==NULL) return NULL;
	if(ISNULL(pComplexArgument)) return NULL;

	return NULL;

	////��������� �������� ������������� ������� � ������
	//CalculateInversDocumentFrequency(pComplexArgument);

	//CCompositeValue* pCompositeValue=static_cast<CCompositeValue*>(pValue);

	////������� �����������
	//CAccumulator* pAccumulator=new CAccumulator(pCompositeValue->GetOrtsMaxNumber());
	//pAccumulator->m_uinMean++;
	//
	////������� ��� ��������
	//unsigned int uiCurrentOrt=0;
	////������� ���� ������
	//float fCurrTextRank;
	////�������� ����� � ����������� ����������� �� �����, � ������� ����������� ������
	////����� � ������ ������ �������� �����
	//CSearchBmNode_S::TSentencesCount* pSentencesCounts=((CSearchBmNode_S*)pCompositeValue)->GetSentencesCountBuffer();
	//CSearchBmNode_S::TSentencesCount::iterator itSentencesCount=pSentencesCounts->begin();
	//if(pCompositeValue->MoveFirstOrt()) 
	//{
	//	do{ 
	//		uiCurrentOrt=pCompositeValue->GetCurrentOrt();
	//		
	//		//��������� ���� ������ ������������ ����������� �����������, � ������� ����������� ������
	//		//��������� �������� ������� � ��� �����
	//		fCurrTextRank=(*itSentencesCount)*m_fInversDocumentFrequency*
	//			pComplexArgument->GetKoeff();
	//		
	//		//��������� �����������
	//		pAccumulator->m_vfMean[uiCurrentOrt]=
	//			pAccumulator->m_vfMean[uiCurrentOrt]+ fCurrTextRank;
	//		if(pAccumulator->m_vfMax[uiCurrentOrt]<fCurrTextRank) 
	//			pAccumulator->m_vfMax[uiCurrentOrt]=fCurrTextRank;
	//		
	//		itSentencesCount++;
	//	}while(pCompositeValue->MoveNextOrt());
	//}
	//
	////������� ����������� � �����������
	//pAccumulator->EvalA4ORFromAccumulator(m_fBeta);
	////pAccumulator->View();

	//return pAccumulator;
}

void CTextLevelLogic::ToResultValue(CValue* pValue, CResultArgument* pResultArgument)
{
	//������ ��������� �� ����������
	if(!IsActive()) return;

	if(ISNULL(pValue)) return;
	if(ISNULL(pResultArgument)) return;
	if(ISNULL(pResultArgument->GetMyself())) return;
	if(ISNULL(pResultArgument->GetMyself()->GetValue())) return;

	//���������� ���� ����� ����������
	
	//�������� �������� ����������
	CCompositeValue* pCompositeValue=pResultArgument->GetMyself()->GetValue();
	//�������� ������������ � ������������ ������
	CAccumulator* pAccumulator=static_cast<CAccumulator*>(pValue);
	//��������� ������� ����� ������� ������� ���������� �� ������� ����������
	unsigned int uiCurrTextsBaseNumber=CalculateTextsBaseNumberFromResultHistory(pResultArgument);
	//�������� ���� ����� ��������
	CArgumentEx::TValueOrtsWeightsCollection* 
		pValueOrtsWeightsCollection=pResultArgument->GetMyself()->GetValueOrtsWeights();
	if(pCompositeValue->MoveFirstOrt()) 
	{
		unsigned int uiDocumentNormKoef=0;
		unsigned int uiCurrTextNumber=0;
		unsigned int uiCurrentOrt=0;
		do{
			uiDocumentNormKoef=0;
			uiCurrentOrt=pCompositeValue->GetCurrentOrt();
			//���������� ����� ������
			uiCurrTextNumber=uiCurrTextsBaseNumber+uiCurrentOrt;
			//���� �� ���������� - ������� ����������� �����������
			if(uiCurrTextNumber<m_uiAllTextsNumber) 
			{ 
				//�������� ����������� ����������� �� ����
				uiDocumentNormKoef=m_pIndexStorage->GetDocNormStorage()->GetDocNorm(uiCurrTextNumber);
				float fNorm=*((float*)(&uiDocumentNormKoef));
				if ( fNorm <=0 || fNorm > 10000 ) fNorm=100;
				
				//��������� ���� � ������������
				pAccumulator->m_vfMean[uiCurrentOrt]=
					pAccumulator->m_vfMean[uiCurrentOrt]/fNorm;
				
				//��������� ����������� � ���� ������� ����
				(*pValueOrtsWeightsCollection)[uiCurrentOrt]+=pAccumulator->m_vfMean[uiCurrentOrt];

			}
		}while(pCompositeValue->MoveNextOrt());
	}
}

unsigned int CTextLevelLogic::CalculateTextsBaseNumberFromResultHistory(CResultArgument* pResultArgument)
{
	//������ ��������� �� ����������
	if(!IsActive()) return NULL;

	if(ISNULL(pResultArgument)) return EMPTY_VALUE;
	if(ISNULL(m_pIndexStorage)) return EMPTY_VALUE;
	
	unsigned int uiBaseTextsNumber=0;
	CResultArgument::THistoryBuffer* pHistoryBuffer=pResultArgument->GetHistoryBuffer();
	CResultArgument::THistoryBuffer::iterator itHistoryBuffer=pHistoryBuffer->begin();
	CIndexStorage::TCoordinateLevelInfo* pLevelCollection=m_pIndexStorage->GetCoordinateLevelCollection();
	CIndexStorage::TCoordinateLevelInfo::iterator itLevelStorage=pLevelCollection->begin();
	SNdxLevelInfo const* pLevelInfo=(*itLevelStorage);
	do{
		if(pLevelInfo->m_IndexCoordinateType==SNdxLevelInfo::ictTextAbsNumber){
			//����������� �� ���������� ������� ��� ������
			SS::Core::NdxSE::NdxProcessor::CCoordinateConvertor::InsertToCoordinate(
				&uiBaseTextsNumber,
				(unsigned int)(*itHistoryBuffer), 
				pLevelInfo->m_ucStartBit,
				pLevelInfo->m_ucBitPerLevel);

			if(++itHistoryBuffer==pHistoryBuffer->end()) break;
		}		
	}while(++itLevelStorage!=pLevelCollection->end());

	return uiBaseTextsNumber;
}

float CTextLevelLogic::ComputeInversDocumentFrequency(unsigned int uiDocumentsNumber, unsigned int uiDocumentFrequency)
{
	return (float)log((double)(uiDocumentsNumber+1)/uiDocumentFrequency);
}

//--------------------------------------------------------------------//

}
}
}
}
}
}