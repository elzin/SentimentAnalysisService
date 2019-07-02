#pragma once

#include ".\eq_calc.h"
#include ".\eq_block.h"
#include ".\subst.h"
#include ".\console.h"
#include ".\ev_factory.h"

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

class CESFiller : public CFactoryClient<Containers::CContainersFactory>
{
public:
	CESFiller(Containers::CContainersFactory* pCntFactory)	
		:CFactoryClient<Containers::CContainersFactory>(pCntFactory){};
	virtual ~CESFiller(void){};

	///���������� ������� � ������������� ����������� � ����������� ��������	
	virtual void Fill(CCalcEquation* pEquation, CSubster* pSubster){TO_CONSOLE(L"Not overriden!");};
	virtual void Fill(CBlockEquation* pEquation, CSubster* pSubster){TO_CONSOLE(L"Not overriden!");};
	///���������� ���� �������������
	virtual bool IsInited(void){TO_CONSOLE(L"Not overriden!"); return false;};
	///���������� �������� �� �������� ���������� ����������
	virtual void ViewFillingSource(void){TO_CONSOLE(L"Not overriden!");};
};

//--------------------------------------------------------------------//

///����������� - �������� �� ���������� ������ � �������������� ����������� � ����������� ��������
template <class TFillingSource>
class CESFillerEx : public CESFiller
{
public:
	typedef set<CCalcArgument*> TArgCollectionForSubster;

	CESFillerEx(Containers::CContainersFactory* pCntFactory, TFillingSource* pFillingSource)	
		:CESFiller(pCntFactory), m_pFillingSource(pFillingSource){};
	virtual ~CESFillerEx(void){};

	///���������� ������� � ������������� ����������� � ����������� ��������	
	void Fill(CCalcEquation* pEquation, CSubster* pSubster){TO_CONSOLE(L"Not overriden!");};
	///���������� ���� �������������
	bool IsInited(void){return (m_pFillingSource)?true:false;};
	///���������� �������� �� �������� ���������� ����������
	TFillingSource* GetFillingSource(void){return m_pFillingSource;};

protected:
	///��������� ��������� ��� �������������
	void AddForSubster(CCalcArgument* pArgument)
	{
		if(ISNULL(pArgument)) return;

		if(pArgument->GetLeftChild() && !pArgument->GetLeftChild()->IsArgumentIntermediate()){
			m_ArgCollectionForSubster.insert(pArgument->GetLeftChild());
		}
		if(pArgument->GetRightChild() && !pArgument->GetRightChild()->IsArgumentIntermediate()){
			m_ArgCollectionForSubster.insert(pArgument->GetRightChild());
		}
	};

	///���������� ������������� ����������� � ����������� ��������	
	void FillSubster(CSubster* pSubster)
	{
		if(ISNULL(pSubster)) return;

		//��������� ������������ ����������
		for(set<CCalcArgument*>::iterator itArg=m_ArgCollectionForSubster.begin(); itArg!=m_ArgCollectionForSubster.end(); itArg++){
			//ToConsole(L"ArgumentID", (*itArg)->GetMyself()->GetArgumentID());
			FillSubster(pSubster, *itArg);
		}
	};

	///���������� ������������� ���������� � ����������� ��������	
	void FillSubster(CSubster* pSubster, CCalcArgument* pSourceArgument)
	{
		if(ISNULL(pSubster)) return;
		if(ISNULL(pSourceArgument)) return;
		//if(ISNULL(m_pSourceIndexesOffsetTable)) return;
		
		if(!pSourceArgument->IsArgumentIntermediate() && pSourceArgument->GetMyself()){
			//���� �������� �������� � �� ������������� 
			unsigned int uiDocumentFrequency=0;
			unsigned int uiEntryPoint=SS::Core::NdxSE::NdxProcessor::EMPTY_VALUE;
			
			//������ ����� ����� �� ��������� �������� �� ������� �������� �����
			GetFactory()->GetIndexStorage()->GetIndexEntryPointTable()->GetIndexData(
				pSourceArgument->GetMyself()->GetArgumentID(), 
					&uiEntryPoint, &uiDocumentFrequency);
			
			if(uiEntryPoint==EMPTY_VALUE){
				ToConsole(L"EntryPoint is empty, for Index: ", pSourceArgument->GetMyself()->GetArgumentID());
			}

			//��������� ��� ��������� �������������
			pSubster->GetArgValCollection()->push_back(
				new CArgValuesPair(pSourceArgument->GetMyself(), 
					GetFactory()->CreateValuesContainer(uiEntryPoint)));
		}
	};

	///�������� �� �������� ���������� ����������
	TFillingSource* m_pFillingSource;
	///��������� ���������� ��� �������������
	TArgCollectionForSubster m_ArgCollectionForSubster;
};

//--------------------------------------------------------------------//

}
}
}
}
}