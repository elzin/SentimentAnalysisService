#include "StdAfx.h"
#include ".\res_check_cnv.h"
#include ".\arg_res_int.h"
#include ".\arg_res_hdr.h"

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

//--------------------------------------------------------------------//

CResultsCheckerWithConvertion::CResultsCheckerWithConvertion(unsigned int uiValidResultsDepth, 
		unsigned int uiFinalResultsMaxNumber, CSearchResultFiller* pSearchResultFiller)
:CResultsChecker(uiValidResultsDepth), 
m_uiFinalResultsMaxNumber(uiFinalResultsMaxNumber),
m_uiFinalResultsCurrentNumber(0),
m_pSearchResultFiller(pSearchResultFiller)
{
}

CResultsCheckerWithConvertion::~CResultsCheckerWithConvertion(void)
{
}

bool CResultsCheckerWithConvertion::CheckResult(CResultArgument* pArgument, CArgument** ppCheckedArgument)
{
	if(ISNULL(pArgument)) return false;
	if(ISNULL(ppCheckedArgument)) return false;

	//�������� �������� ���������:
	//�� ������� 
	//�� ������������������
	//�� ���������� �������

	//��������� �� ������� �����������
	if(m_uiFinalResultsCurrentNumber>=m_uiFinalResultsMaxNumber){
		//���� ��������� ����� ����������� ������� �� ����
		TO_CONSOLE(L"Results limit exceeded");
		ToConsole(L"Results Number", m_uiFinalResultsCurrentNumber);
		
		//���������� ���������
		(*ppCheckedArgument)=NULL;
		return false;
	}

	if(pArgument->GetMyself()->GetValue()->IsEmpty()){
		//���� �������� ���������� ������ �� �� ������ ��������
		(*ppCheckedArgument)=NULL;
		return true;
	}

	if(pArgument->GetDepth()==m_uiValidResultsDepth && 
		!pArgument->GetMyself()->GetValue()->IsEmpty()){
		//���� ��������� ��������� �� ���������� �������
		//� ��� �������� �� ������, ����� ��� ��������������
		if(m_pSearchResultFiller){
			//���� ����� ����� ������������ �������� � �������� ����������

			//������� ��������� ����� ������ �������
			CResultArgument::THistoryBuffer TempHistoryBuffer(*(pArgument->GetHistoryBuffer()));
			TempHistoryBuffer.push_back(0);
			//��������� ������� ������������ ���������� � �������� ����������
			m_pSearchResultFiller->StartAddCoordinate((&TempHistoryBuffer.front()), (unsigned int)TempHistoryBuffer.size());
			
			//�������� ���� ��� �������� ����������
			CArgumentEx::TValueOrtsWeightsCollection* pValueOrtsWeightsCollection=pArgument->GetMyself()->GetValueOrtsWeights();
			
			//�������� �� ����� �������� ��������� � ��������� �������� ���������
			SS::Core::NdxSE::NdxProcessor::Containers::CCompositeValue* pValue=pArgument->GetMyself()->GetValue();
			if(pValue->MoveFirstOrt()){
				unsigned int uiCurrentOrt=0;
				do{
					uiCurrentOrt=pValue->GetCurrentOrt();
					//��������� � �������� ��������� � ��������� � ���������
					m_pSearchResultFiller->AddCoordinate(uiCurrentOrt, 
						pValueOrtsWeightsCollection->at(uiCurrentOrt));

					//��������� ������� ���������� �����������
					//���� ���� ����� ������� �������� ���������� ����� �����������
					//������ �� ������ ��� ��� ������������� ��������� ���������� ����������
					//����, ���� ����� �����, ����� ������ �������� ���������� ����� �����
					++m_uiFinalResultsCurrentNumber;
				}while(pValue->MoveNextOrt());
			}
		}
	
		//�� �������� ����� ��������� �� �������
		(*ppCheckedArgument)=NULL;
		return true;
	}
	
	//��������� ������ ��������, ���������� ���
	(*ppCheckedArgument)=pArgument->GetMyself();
	return true;
}

void CResultsCheckerWithConvertion::View(void)
{
	ToConsole(L"//---CResultsCheckerWithConvertion:");
	
	ToConsole(L"ValidResultsDepth", m_uiValidResultsDepth+1);
	ToConsole(L"FinalResultsNumber", m_uiFinalResultsCurrentNumber);
	ToConsole(L"Max FinalResultsNumber", m_uiFinalResultsMaxNumber);

	ToConsole(L"//---End-of-CResultsCheckerWithConvertion");
}

//--------------------------------------------------------------------//

CResultsCheckerWithIntervalConvertion::CResultsCheckerWithIntervalConvertion(unsigned int uiValidResultsDepth, 
		unsigned int uiFinalResultsMaxNumber, CSearchResultFiller* pSearchResultFiller)
:CResultsCheckerWithConvertion(uiValidResultsDepth, uiFinalResultsMaxNumber, pSearchResultFiller)
{
}

bool CResultsCheckerWithIntervalConvertion::CheckResult(CResultArgument* pArgument, CArgument** ppCheckedArgument)
{
	if(ISNULL(pArgument)) return false;
	if(ISNULL(ppCheckedArgument)) return false;

	//�������� �������� ���������:
	//�� ������� 
	//�� ������������������
	//�� ���������� �������

	//��������� �� ������� �����������
	if(m_uiFinalResultsCurrentNumber>=m_uiFinalResultsMaxNumber){
		//���� ��������� ����� ����������� ������� �� ����
		TO_CONSOLE(L"Results limit exceeded");
		ToConsole(L"Results Number", m_uiFinalResultsCurrentNumber);
		
		//���������� ���������
		(*ppCheckedArgument)=NULL;
		return false;
	}

	if(pArgument->GetMyself()->GetValue()->IsEmpty()){
		//���� �������� ���������� ������ �� �� ������ ��������
		(*ppCheckedArgument)=NULL;
		return true;
	}

	if(pArgument->GetDepth()==m_uiValidResultsDepth && 
		!pArgument->GetMyself()->GetValue()->IsEmpty()){
		//���� ��������� ��������� �� ���������� �������
		//� ��� �������� �� ������, ����� ��� ��������������
		if(m_pSearchResultFiller){
			//���� ����� ����� ������������ �������� � �������� ����������

			//������� ��������� ����� ������ �������
			CResultArgument::THistoryBuffer TempHistoryBuffer(*(pArgument->GetHistoryBuffer()));
			TempHistoryBuffer.push_back(0);
			//��������� ������� ������������ ���������� � �������� ����������
			m_pSearchResultFiller->StartAddCoordinate((&TempHistoryBuffer.front()), (unsigned int)TempHistoryBuffer.size());
			
			//�������� ���� ��� �������� ����������
			CArgumentEx::TValueOrtsWeightsCollection* pValueOrtsWeightsCollection=pArgument->GetMyself()->GetValueOrtsWeights();
			
			//�������� ��������� ���������� �����������
			CResultArgumentWithIntervals* pResultArgumentWithIntervals=static_cast<CResultArgumentWithIntervals*>(pArgument);
			CResultArgumentWithIntervals::TResultIntervalCollection* pResultIntervalCollection=pResultArgumentWithIntervals->GetResultIntervalCollection();
			if(!pResultIntervalCollection || pResultIntervalCollection->empty()){
				//�� �������� ����� ��������� �� �������
				(*ppCheckedArgument)=NULL;
				return true;

			}
			CResultArgumentWithIntervals::TResultIntervalCollection::iterator itResultIntervals=pResultIntervalCollection->begin();

			//�������� �� ����� �������� ��������� � ��������� �������� ���������
			float fWeight=0.0;
			SS::Core::NdxSE::NdxProcessor::Containers::CCompositeValue* pValue=pArgument->GetMyself()->GetValue();
			if(pValue->MoveFirstOrt()){
				unsigned int uiCurrentOrt=0;
				do{
					uiCurrentOrt=pValue->GetCurrentOrt();
					
					if(uiCurrentOrt<pValueOrtsWeightsCollection->size()){
						fWeight=pValueOrtsWeightsCollection->at(uiCurrentOrt);
					}else{
						fWeight=0.0;
					}

					//��������� � �������� ��������� � ��������� � ���������
					bool bResult=m_pSearchResultFiller->AddCoordinate(uiCurrentOrt, 
						fWeight, *itResultIntervals);
					
					//��������� ������� ���������� �����������
					//���� ���� ����� ������� �������� ���������� ����� �����������
					//������ �� ������ ��� ��� ������������� ��������� ���������� ����������
					//����, ���� ����� �����, ����� ������ �������� ���������� ����� �����
					++m_uiFinalResultsCurrentNumber;

					//��������� �� ������� �����������
					if(!bResult){
						//���� ��������� ����� ����������� ������� �� ����
						TO_CONSOLE(L"Results limit by intervals exceeded");
						ToConsole(L"Results Number", m_uiFinalResultsCurrentNumber);
						
						//���������� ���������
						(*ppCheckedArgument)=NULL;
						return false;
					}
				}while(pValue->MoveNextOrt() && ++itResultIntervals!=pResultIntervalCollection->end());
			}
		}
	
		//�� �������� ����� ��������� �� �������
		(*ppCheckedArgument)=NULL;
		return true;
	}
	
	//��������� ������ ��������, ���������� ���
	(*ppCheckedArgument)=pArgument->GetMyself();
	return true;
}

//--------------------------------------------------------------------//

CResultsCheckerWithHIDConvertion::CResultsCheckerWithHIDConvertion(unsigned int uiValidResultsDepth, 
		unsigned int uiFinalResultsMaxNumber, CSearchResultFiller* pSearchResultFiller)
:CResultsCheckerWithConvertion(uiValidResultsDepth, uiFinalResultsMaxNumber, pSearchResultFiller)
{
}

bool CResultsCheckerWithHIDConvertion::CheckResult(CResultArgument* pArgument, CArgument** ppCheckedArgument)
{
	if(ISNULL(pArgument)) return false;
	if(ISNULL(ppCheckedArgument)) return false;

	//�������� �������� ���������:
	//�� ������� 
	//�� ������������������
	//�� ���������� �������

	//��������� �� ������� �����������
	if(m_uiFinalResultsCurrentNumber>=m_uiFinalResultsMaxNumber){
		//���� ��������� ����� ����������� ������� �� ����
		TO_CONSOLE(L"Results limit exceeded");
		ToConsole(L"Results Number", m_uiFinalResultsCurrentNumber);
		
		//���������� ���������
		(*ppCheckedArgument)=NULL;
		return false;
	}

	if(pArgument->GetMyself()->GetValue()->IsEmpty()){
		//���� �������� ���������� ������ �� �� ������ ��������
		(*ppCheckedArgument)=NULL;
		return true;
	}

	if(pArgument->GetDepth()==m_uiValidResultsDepth && 
		!pArgument->GetMyself()->GetValue()->IsEmpty()){
		//���� ��������� ��������� �� ���������� �������
		//� ��� �������� �� ������, ����� ��� ��������������
		if(m_pSearchResultFiller){
			//���� ����� ����� ������������ �������� � �������� ����������

			//������� ��������� ����� ������ �������
			CResultArgument::THistoryBuffer TempHistoryBuffer(*(pArgument->GetHistoryBuffer()));
			TempHistoryBuffer.push_back(0);
			//��������� ������� ������������ ���������� � �������� ����������
			m_pSearchResultFiller->StartAddCoordinate((&TempHistoryBuffer.front()), (unsigned int)TempHistoryBuffer.size());
			
			//�������� ���� ��� �������� ����������
			CArgumentEx::TValueOrtsWeightsCollection* pValueOrtsWeightsCollection=pArgument->GetMyself()->GetValueOrtsWeights();
			
			//�������� ��������� ���������� �����������
			CResultArgument_HID* pResultArgument_HID=static_cast<CResultArgument_HID*>(pArgument);
			CResultArgument_HID::TBlocksCollection* pResultBlocksCollection=pResultArgument_HID->GetResultBlocksCollection();
			if(!pResultBlocksCollection || pResultBlocksCollection->empty()){
				//�� �������� ����� ��������� �� �������
				(*ppCheckedArgument)=NULL;
				return true;

			}
			CResultArgument_HID::TBlocksCollection::iterator itResultBlocks=pResultBlocksCollection->begin();

			//�������� �� ����� �������� ��������� � ��������� �������� ���������
			float fWeight=0.0;
			SS::Core::NdxSE::NdxProcessor::Containers::CCompositeValue* pValue=pArgument->GetMyself()->GetValue();
			if(pValue->MoveFirstOrt()){
				unsigned int uiCurrentOrt=0;
				do{
					uiCurrentOrt=pValue->GetCurrentOrt();
					
					if(uiCurrentOrt<pValueOrtsWeightsCollection->size()){
						fWeight=pValueOrtsWeightsCollection->at(uiCurrentOrt);
					}else{
						fWeight=0.0;
					}

					//��������� � �������� ��������� � ��������� � ���������
					bool bResult=m_pSearchResultFiller->AddCoordinate(uiCurrentOrt, 
						fWeight, *itResultBlocks);
					
					//��������� ������� ���������� �����������
					//���� ���� ����� ������� �������� ���������� ����� �����������
					//������ �� ������ ��� ��� ������������� ��������� ���������� ����������
					//����, ���� ����� �����, ����� ������ �������� ���������� ����� �����
					++m_uiFinalResultsCurrentNumber;

					//��������� �� ������� �����������
					if(!bResult){
						//���� ��������� ����� ����������� ������� �� ����
						TO_CONSOLE(L"Results limit by intervals exceeded");
						ToConsole(L"Results Number", m_uiFinalResultsCurrentNumber);
						
						//���������� ���������
						(*ppCheckedArgument)=NULL;
						return false;
					}
				}while(pValue->MoveNextOrt() && ++itResultBlocks!=pResultBlocksCollection->end());
			}
		}
	
		//�� �������� ����� ��������� �� �������
		(*ppCheckedArgument)=NULL;
		return true;
	}
	
	//��������� ������ ��������, ���������� ���
	(*ppCheckedArgument)=pArgument->GetMyself();
	return true;
}

//--------------------------------------------------------------------//

}
}
}
}
}