#pragma once

#include ".\es_filler.h"
#include ".\index_storage.h"
#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASDInterface\INDXQuery.h"

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

///����������� - �������� �� ���������� ������ � �������������� ����������� ������ ���������� ��� ��� ������� IQueryResult
class CESFillerFromQuery : 
	public CESFillerEx<SS::Interface::Core::NdxSE::IParametrizedQuery>
{
public:
	CESFillerFromQuery(
		Containers::CContainersFactory* pCntFactory, 
		SS::Interface::Core::NdxSE::IParametrizedQuery* pPrmQueryResult);

	virtual ~CESFillerFromQuery(void);

	///���������� ������� � ������������� ����������� � ����������� ��������	
	void Fill(CCalcEquation* pEquation, CSubster* pSubster){};
	void Fill(CBlockEquation* pEquation, CSubster* pSubster);
	///���������� ��������� LBaseSearchWords
	void ViewFillingSource(void);
protected:
	///��������� ������ ���������� �� ����������� �����
	virtual void AddArgumentsGroup(CBlockEquation* pEquation, 
		SS::Interface::Core::NdxSE::IBlock* pBlock, bool bAndBlock);
	///��������� ����� � ������ ����������
	virtual void AddWordToArgumentsGroup(CArgumentsGroup* pArgumentsGroup, 
		SS::Interface::Core::NdxSE::IWord* pWord);
	///��������� ������ � ������ ����������
	void AddIndexToArgumentsGroup(CArgumentsGroup* pArgumentsGroup, 
									unsigned int uiIndex, unsigned int uiEntryPoint, unsigned int uiIndexFrequency, 
									SS::Interface::Core::CommonContainers::SQueryIndexAttributes QueryIndexAttributes);

	///������� ������������ ����������
	CSubster* m_pSubster;
};

//--------------------------------------------------------------------//

///����������� �������, ��������� ���������� �������� ��� ����������
class CESFillerFromQuery_Statistic : public CESFillerFromQuery
{
public:
	CESFillerFromQuery_Statistic(Containers::CContainersFactory* pCntFactory, 
		SS::Interface::Core::NdxSE::IParametrizedQuery* pPrmQueryResult) :
			CESFillerFromQuery(pCntFactory, pPrmQueryResult),
			m_bCurrentAndBlock(false)
	{
	};

	///���������� ������� � ������������� ����������� � ����������� ��������	
	void Fill(CBlockEquation* pEquation, CSubster* pSubster);

protected:
	typedef list<unsigned int> TIndexCollection;

	///��������� ������ ���������� �� ����������� �����
	void AddArgumentsGroup(CBlockEquation* pEquation, 
		SS::Interface::Core::NdxSE::IBlock* pBlock, bool bAndBlock);
	///��������� ����� � ������ ����������
	void AddWordToArgumentsGroup(CArgumentsGroup* pArgumentsGroup, 
		SS::Interface::Core::NdxSE::IWord* pWord);
	
	///��������� �������� ������� ����� �������� � AndBlock
	TIndexCollection m_IndexToAndBlock; 
	bool m_bCurrentAndBlock;
};

//--------------------------------------------------------------------//

}
}
}
}
}