#pragma once

#include ".\index_stat_storage.h"
#include ".\collection_containers.h"
#include ".\index_container_nodes_s.h"
#include ".\arg_complex.h"
#include ".\arg_res.h"

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
//--------------------------------------------------------------------//

///������ ��������������� �����������
class CStatisticIndex
{
public:
	CStatisticIndex(unsigned int uiIndex):m_uiIndex(uiIndex), m_fInversDocumentFrequency(0.0), m_pCoordinateNode(NULL){};

	///��������� ������� � ��������� ������������
	void AddArgumentPosition(CComplexArgument* pComplexArgument, SS::Core::NdxSE::NdxProcessor::Containers::CCoordinateNode_4s* pCoordinateNode);
	///������� ��������� ���������
	void Clear(void){m_pCoordinateNode=NULL;};

	///���������� �������� �������
	unsigned int GetIndex(void){return m_uiIndex;};
	///���������� �������� ������� �������
	float GetInversDocumentFrequency(void){return m_fInversDocumentFrequency;};
	///������������� �������� ������� �������
	void SetInversDocumentFrequency(float fValue){m_fInversDocumentFrequency=fValue;};
	///���������� ������� ��������� ���������
	SS::Core::NdxSE::NdxProcessor::Containers::CCoordinateNode_4s* GetCoordinateContainer(void){return m_pCoordinateNode;};

protected:
	///�������� �������
	const unsigned int m_uiIndex;
	///�������� ������� �������
	float m_fInversDocumentFrequency;
	///������� ��������� ���������
	SS::Core::NdxSE::NdxProcessor::Containers::CCoordinateNode_4s* m_pCoordinateNode;
};

//--------------------------------------------------------------------//

///����������� �������������� �������������, �������� ��������� �������� �������, 
///������ � ������� �� ��� ������� � �������
class CStatisticEvaluator
{
public:
	CStatisticEvaluator(SS::Core::NdxSE::NdxProcessor::Storages::CIndexStatisticStorage* pIndexStorage, unsigned int uiTotalTextsNumber);
	virtual ~CStatisticEvaluator(void);

	///��������� ������ �����������
	void AddIndex(unsigned int uiIndex);
	///��������� ������� � ��������� ������������
	void AddArgumentPosition(CComplexArgument* pComplexArgument, SS::Core::NdxSE::NdxProcessor::Containers::CCoordinateNode_4s* pCoordinateNode);
	///��������� ������� ����� ������� ������� ���������� �� ������� ����������
	unsigned int SetDocumentBasisIndex(unsigned int uiValue);
	///���������
	float Evaluate(unsigned int uiEvalID);
	///������� ���
	void Clear(void);
protected:
	///��������� �������� ������������� ������� � ������
	float CalculateInversDocumentFrequency(unsigned int uiIndex);
	
	typedef map<unsigned int, CStatisticIndex*> TStatisticIndexCollection;
	///��������� � ��������
	SS::Core::NdxSE::NdxProcessor::Storages::CIndexStatisticStorage* m_pIndexStorage;
	///������� ������� ����� ������� ������� ����������
	unsigned int m_uiCurrBasisTextsNumber;
	///���������� ������� � ����
	const unsigned int m_uiTotalTextsNumber;
	///��������� ��������
	TStatisticIndexCollection m_StatisticIndexCollection;
};

//--------------------------------------------------------------------//

}
}
}
}
}
}