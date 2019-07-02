#include "StdAfx.h"
#include ".\res.h"
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

using namespace SS::Core::NdxSE::NdxProcessor;
using namespace SS::Core::NdxSE::NdxProcessor::Storages;
using namespace SS::Core::NdxSE::NdxProcessor::Containers;
using namespace SS::Interface::Core::NdxSE::NdxDataStorage; 

//--------------------------------------------------------------------//

CResultsContainer::CResultsContainer(CEvalFactory* pEvalFactory, unsigned int uiGenerationLimitDepth)
:CFactoryClient<CEvalFactory>(pEvalFactory), 
m_uiGenerationLimitDepth(uiGenerationLimitDepth),
m_pDeriveEquation(NULL), m_pLastResult(NULL), m_pResultsChecker(NULL)
{
	//������� ��������� �������
	m_pDeriveEquation=GetFactory()->CreateResultEquation();
	//������� ���������� �����������
	m_pResultsChecker=GetFactory()->CreateResultsChecker(m_uiGenerationLimitDepth);
}


CResultsContainer::~CResultsContainer(void)
{
	if(m_pDeriveEquation)
		delete m_pDeriveEquation;

	if(m_pResultsChecker)
		delete m_pResultsChecker;
}

CResultArgument* CResultsContainer::CreateChildResult(CResultArgument* pParentResult, unsigned int uiOrt)
{
	if(ISNULL(pParentResult)) return NULL;
	if(ISNULL(GetFactory())) return NULL;

	//������� ����� ��������
	CResultArgument* pNewResult=GetFactory()->CreateResultArgument(
			uiOrt, 
			pParentResult->GetMyself()->GetKoeff(), 
			pParentResult->GetDepth()+1);

	//��������� �������� �������
	if(pNewResult==pParentResult->AddChild(pNewResult)){
		//���� ������� ��������� ��������� ���� ��� ������ ��������
		pNewResult->GetMyself()->SetValue(GetFactory()->GetFactory()->CreateCompositeValue(uiOrt, pNewResult->GetDepth()));
	}else{
		//���� ������� ��������� �� ��������� ������� ��������
		delete pNewResult;
		pNewResult=NULL;
	}
	
	return pNewResult;
}


CResultArgument* CResultsContainer::GenerateResult(void)
{
	if(ISNULL(m_pDeriveEquation)) return NULL;

	if(!m_pLastResult){
		//���� ���������� ���������� ��� �� ����, ���������� ������� ��������
		m_pLastResult=m_pDeriveEquation->GetRootArgument();
		//������ ��� ������ ��������
		m_pLastResult->GetMyself()->SetValue(GetFactory()->GetFactory()->CreateCompositeValue(0, 0));
		return m_pLastResult;
	}
	
	SS::Core::NdxSE::NdxProcessor::Containers::CCompositeValue* 
		pValue=m_pLastResult->GetMyself()->GetValue();
	
	if(!pValue->IsEmpty()){
		//���� �������� ���������� ������������ ���������� �� ������
		//� �� �� �������� ���������� ������� ���������� �����������
		//��������� �� ���� ����� �������� ���������
		if(m_pLastResult->GetDepth()<m_uiGenerationLimitDepth){
			//���� �� ������� ����� ��������� ������, ���������

			if(!m_pLastResult->IsProcessed()){
				//���� ���� ��� �� �������������
				//������� ������ �������� �� ������ ������������ �������� 
				if(pValue->MoveFirstOrt()){
					m_pLastResult->SetProcessed();
					//������� �������� ��������� �� ����	
					CResultArgument* pNewResult=CreateChildResult(m_pLastResult, pValue->GetCurrentOrt());
					
					//m_pLastResult->View();

					//��������� ���� �� ��������� ��������
					m_pLastResult=pNewResult;
					return m_pLastResult;
				}else{
					TO_CONSOLE(L"Cann't MoveFirstOrt!!!");
					return NULL;
				}
			}else{
				//���� ���� �������������
				//������� ������ �������� �� ��������� ������������ �������� 
				if(pValue->MoveNextOrt()){
					//������� �������� ��������� �� ����	
					CResultArgument* pNewResult=CreateChildResult(m_pLastResult, pValue->GetCurrentOrt());
					//��������� ���� �� ��������� ��������
					m_pLastResult=pNewResult;
					return m_pLastResult;
				}else{
					//���� ��� ���� ��������� ����������, ������� ��� � ��������� � �������������
					unsigned int uiChildID=m_pLastResult->GetMyself()->GetArgumentID();
					m_pLastResult=m_pLastResult->GetParent();
					if(!m_pLastResult) return NULL;
					//������� �������		
					m_pLastResult->DeleteChild(uiChildID);
					return GenerateResult();
				}
			}
		}else{
			//���� �������� ������� �� �������, ���� ���� � �������������� �������������
			m_pLastResult=m_pLastResult->GetParent();
			return m_pLastResult?GenerateResult():NULL;
		}
	}else{
		//���� �������� ���������� ������������ ���������� ������
		//������ ��������� ������� � �������� ������� ������ 
		//� ���  ������� �� ���������� �������
		unsigned int uiChildID=m_pLastResult->GetMyself()->GetArgumentID();
		m_pLastResult=m_pLastResult->GetParent();

		//m_pLastResult->View();

		if(!m_pLastResult) return NULL;
		//������� �������		
		m_pLastResult->DeleteChild(uiChildID);
		
		return GenerateResult();
	}
}

bool CResultsContainer::CheckResult(CResultArgument* pArgument, CArgument** ppCheckedArgument)
{
	if(ISNULL(pArgument)) return false;
	if(ISNULL(m_pLastResult)) return false;
	if(ISNULL(ppCheckedArgument)) return false;
	if(ISNULL(m_pResultsChecker)) return false;

	if(m_pLastResult!=pArgument){
		(*ppCheckedArgument)=NULL;
		return true;
	}
	
	//��������� ��������� �����������
	return m_pResultsChecker->CheckResult(pArgument, ppCheckedArgument);
}

void CResultsContainer::View(void)
{
	ToConsole(L"//----------ResultsContainer:");
	if(m_pDeriveEquation)
		m_pDeriveEquation->View();

	if(m_pResultsChecker)
		m_pResultsChecker->View();

	ToConsole(L"//-----End-of-ResultsContainer");
}

//--------------------------------------------------------------------//

CResultsContainerWithCorrection::CResultsContainerWithCorrection(CEvalFactory* pEvalFactory, 
		SS::Core::NdxSE::NdxProcessor::Storages::CIndexStorage* pIndexStorage,
		unsigned int uiGenerationLimitDepth, 
		unsigned int uiCorrectionLimitDepth)
:CResultsContainer(pEvalFactory, uiGenerationLimitDepth), 
m_pIndexStorage(pIndexStorage),
m_uiCorrectionLimitDepth(uiCorrectionLimitDepth)
{
	//����� ������� ������� �������� ������� �����������
	m_pDeriveEquation->GetRootArgument()->GetMyself()->SetValue(GetFactory()->GetFactory()->CreateCompositeValue(0, 0));
}

CResultsContainerWithCorrection::~CResultsContainerWithCorrection(void)
{
}

void CResultsContainerWithCorrection::AddCorrectionResult(unsigned int* pBuffer, unsigned int uiBufferSize)
{
	if(ISNULL(m_pIndexStorage)) return;
	if(ISNULL(pBuffer)) return;
	if(ISNULL(m_pDeriveEquation)) return;

	CResultArgument* pResultArgument=m_pDeriveEquation->GetRootArgument();
	if(ISNULL(pResultArgument)) return;

	unsigned int uiSplitCoord=0;

	//� ����� ���������� ���������� ������ � ����� ������ � ����������� �� ������������ �������
	CIndexStorage::TCoordinateLevelInfo* pLevelCollection=m_pIndexStorage->GetCoordinateLevelCollection();
	
	if(pLevelCollection->empty()){
		TO_CONSOLE(L"pLevelsInfo empty possible IndexationInfo not opened!!!");
		return;
	}
	
	CResultArgument* pTempResultArgument=NULL;
	if(!pLevelCollection->empty()){
		CIndexStorage::TCoordinateLevelInfo::iterator itLevelStorage=pLevelCollection->begin();
		do{
			if(ISNULL(pResultArgument)) break;
			SNdxLevelInfo const* pLevelInfo=(*itLevelStorage);

			//����������� �� ���������� ������� ��� ������
			uiSplitCoord=SS::Core::NdxSE::NdxProcessor::CCoordinateConvertor::SplitCoordinate(
				*(pBuffer+pLevelInfo->m_IndexCoordinateType), 
				pLevelInfo->m_ucStartBit,
				pLevelInfo->m_ucBitPerLevel);
			
			//��������� ������� � ������
			if((unsigned int)pLevelInfo->m_IndexCoordinateType<uiBufferSize){

				if(ISNULL(pResultArgument->GetMyself()->GetValue())) return;
				
				//���������� ��� � �������� ����������
				pResultArgument->GetMyself()->GetValue()->SetOrt(uiSplitCoord);
				pTempResultArgument=pResultArgument->GetChild(uiSplitCoord);
				
				if(!pTempResultArgument){
					//������� �������� ��������� �� ����	
					pResultArgument=CreateChildResult(pResultArgument, uiSplitCoord);
				}else{
					pResultArgument=pTempResultArgument;
				}
			}
		}while(++itLevelStorage!=pLevelCollection->end() && pResultArgument);
	}
}

void CResultsContainerWithCorrection::CreateCorrectionTemplate(CResultsContainer* pResultsContainer)
{
	if(ISNULL(pResultsContainer)) return;
	
	if(pResultsContainer->m_pDeriveEquation){
		//������� �� ��� ��� ���� �������
		if(m_pDeriveEquation){ 
			//���� ������� ��� ���� �������, ������� � ��
			delete m_pDeriveEquation;
		}
		
		//������������� ���� ���������� �������� ����������
		m_pDeriveEquation=pResultsContainer->m_pDeriveEquation;
		
		//�������� ���������� �� ������ �������
		m_pDeriveEquation->GetRootArgument()->CutByDepth(m_uiCorrectionLimitDepth);

		//������ ��� ���������
		pResultsContainer->m_pDeriveEquation=NULL;
		m_pLastResult=NULL;
		pResultsContainer->m_pLastResult=NULL;
		
		//m_pDeriveEquation->View();	
	}
}

CResultArgument* CResultsContainerWithCorrection::GenerateResult(void)
{
	if(ISNULL(m_pDeriveEquation)) return NULL;

	if(!m_pLastResult){
		m_pLastResult=m_pDeriveEquation->GetRootArgument();
		return m_pLastResult;
	}

	if(m_pLastResult->GetDepth()>m_uiCorrectionLimitDepth){
		//���� ��������� ������� �������������, ���������� ������� ����������
		return CResultsContainer::GenerateResult();
	}

	Containers::CCompositeValue* pValue=m_pLastResult->GetMyself()->GetValue();
	
	//pValue->View();

	if(!pValue->IsEmpty()){
		//���� �������� ���������� ������������ ���������� �� ������
		//� �� �� �������� ���������� ������� ���������� �����������
		//��������� �� ���� ����� �������� ���������
		if(m_pLastResult->GetDepth()<m_uiGenerationLimitDepth){
			//���� �� ������� ����� ��������� ������, ���������
			if(m_pLastResult->IsLeaf()){
				//���� ���� ���������, ��������� � �������������, 
				//���� ���� ��������� �� �����
				m_pLastResult=m_pLastResult->GetParent();
				return m_pLastResult?GenerateResult():NULL;
			}else{
				//���� ���� �� ��������� 
				//���� ������� �������, �������� ������������� ��� � ����������
				
				if(m_pLastResult->GetCurrentChild()){
					do{
						//��������� ���� ������ ��� � �������� ����������
						if(pValue->HasOrt(
							m_pLastResult->GetCurrentChild()->GetMyself()->GetArgumentID())){
							//���� ������ ��� ���� � ��������, ������ ������� ������

							CResultArgument* pParent=m_pLastResult;
							//������ ������� ������� �����������
							m_pLastResult=m_pLastResult->GetCurrentChild();
							//� �������� ������������� �� ���������� ����� ����� � ���� ������
							pParent->MoveNextChild();
							
							//��������� ������� ���������
							//m_pLastResult->GetMyself()->GetValue()->View();
							return m_pLastResult;
						}
					}while(m_pLastResult->MoveNextChild());
				}
				//���� ��� ���� ��������� ����������, ��������� � �������������
				m_pLastResult=m_pLastResult->GetParent();
				return m_pLastResult?GenerateResult():NULL;
			}
		}else{
			//���� �������� ������� �� �������, ���� ���� � �������������� �������������
			m_pLastResult=m_pLastResult->GetParent();
			return m_pLastResult?GenerateResult():NULL;
		}
	}else{
		//���� �������� ���������� ������������ ���������� ������
		//������ ��������� ������� � �������� ������� ������ 
		//� ���  ������� �� ���������� �������
		m_pLastResult=m_pLastResult->GetParent();
		if(!m_pLastResult) return NULL;
		return GenerateResult();
	}
}

bool CResultsContainerWithCorrection::CheckResult(CResultArgument* pArgument, CArgument** ppCheckedArgument)
{
	bool bResult=CResultsContainer::CheckResult(pArgument, ppCheckedArgument);
	if((*ppCheckedArgument)){
		//���� �������� ������ ���������, ������� ���������
		m_pLastResult->MoveFirstChild();
	}

	return bResult;
}

//--------------------------------------------------------------------//

CResult::CResult(CArgument* pResultArgument)
:m_pResultArgument(pResultArgument)
{
	m_itCurrResultValuesCollection = m_NullCollection.end();
	if(ISNULL(m_pResultArgument)) return;

	//�� ������������ �������� ���������� ��������� ��������� ����������
	SS::Core::NdxSE::NdxProcessor::Containers::CCompositeValue* pCompositeValue=
		static_cast<SS::Core::NdxSE::NdxProcessor::Containers::CCompositeValue*>(m_pResultArgument->GetValue());
	
	if(ISNULL(pCompositeValue)) return;
	
	if(pCompositeValue->MoveFirstOrt()){
		unsigned int uiCollectionID;
		do{
			uiCollectionID=pCompositeValue->GetCurrentOrt();
			//ToConsole(L"uiCollectionID_", uiCollectionID);
			m_ResultCollection.push_back(uiCollectionID);
		}while(pCompositeValue->MoveNextOrt());
		
		m_itCurrResultValuesCollection=m_ResultCollection.begin();
	}
}

CResult::~CResult(void)
{
	m_ResultCollection.clear();
	m_itCurrResultValuesCollection=m_NullCollection.end();
}

unsigned int CResult::GetCurrentEvalID(void)
{
	return (m_itCurrResultValuesCollection==m_NullCollection.end())?EMPTY_VALUE:(*m_itCurrResultValuesCollection);
}

bool CResult::MoveNextEvalID(void)
{
	if(m_itCurrResultValuesCollection==m_NullCollection.end()) return false;
		
	if(++m_itCurrResultValuesCollection!=m_ResultCollection.end()){
		return true;
	}else{
		m_itCurrResultValuesCollection=m_NullCollection.end();
		return false;
	}
}

void CResult::ToString(wstring& szValue, wstring szOffset)
{
	wstring szMyOffset(L"   ");
	szValue.append(szOffset);
	szValue.append(L"//----Result:");

	szValue.append(L"\n"+szOffset+szMyOffset);

	//if(m_pResultArgument)
	//	m_pResultArgument->ToString(szValue);

	szValue.append(L"\n"+szOffset+szMyOffset);
	wchar_t buff[40];
	if(m_itCurrResultValuesCollection!=m_NullCollection.end()){
		wsprintf(buff, L"Curr Collection ID: %u", (*m_itCurrResultValuesCollection));
	}else{
		wsprintf(buff, L"Curr Collection ID: not defined");
	}
	szValue.append(buff);

	szValue.append(szOffset);
	szValue.append(L"//-End-of-Result\n");
}

//--------------------------------------------------------------------//

CResultsStack::CResultsStack(void)
{
}

CResultsStack::~CResultsStack(void)
{
	Clear();
}

void CResultsStack::Clear(void)
{
	while(!m_ResultsStack.empty()){
		if(ISNULL(m_ResultsStack.back())){
			m_ResultsStack.pop_back();
		}else{
			delete m_ResultsStack.back();
			m_ResultsStack.pop_back();
		}
	}
}

void CResultsStack::PushBackResult(CResult* pResult)
{
	if(ISNULL(pResult)) return;
	
	m_ResultsStack.push_back(pResult);
}

void CResultsStack::PopBackResult(void)
{
	if(ISNULL(m_ResultsStack.back())) return;

	delete m_ResultsStack.back();
	m_ResultsStack.pop_back();
}

CResult* CResultsStack::GetBackResult(void)
{
	if(m_ResultsStack.empty()){
		return NULL;
	}else{
		return m_ResultsStack.back();
	}
}

void CResultsStack::View(void)
{
	wstring szValue(L"");
	szValue.reserve(1000);
	wstring szOffset(L"");
	szOffset.reserve(100);

	szValue.append(L"//----------ResultsStack:");

	wchar_t buff[30];
	wsprintf(buff, L"\nStack size: %u", m_ResultsStack.size());
	szValue.append(buff);

	szOffset.append(L"   ");

	TResultsStack::iterator itResult=m_ResultsStack.begin();
	while(itResult!=m_ResultsStack.end()){
		if(ISNULL((*itResult)))	break;
		szValue.append(L"\n");
		(*itResult)->ToString(szValue, szOffset);
		++itResult;
	}
	
	szValue.append(L"\n");
	szValue.append(L"//-----End-of-ResultsStack");
	
	ToConsole(szValue.c_str());
}

//--------------------------------------------------------------------//

}
}
}
}
}