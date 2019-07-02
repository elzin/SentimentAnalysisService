#pragma once

#include ".\basis_containers.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxProcessor
{
namespace Containers
{

//--------------------------------------------------------------------//

///��������� ��� ���������� ������ ��� ����������� � ������ �������� ��������
struct CAccumulator : public SS::Core::NdxSE::NdxProcessor::Containers::CValue
{
public:
	CAccumulator(unsigned int uiNumber=0);
	CAccumulator& operator=(const float fVal);

	///������������� � ������ ��������� uiNumber
	void Init(int uiNumber=0);
	///�������� �� ������� ��������
	bool isEmpty();
	///�������� �������������
	bool MergeAccumulators(CAccumulator& oAcc);
	///���������� ��� �������� �R
	bool EvalA4ORFromAccumulator(float fBeta);
	///���������� ��� �������� AND
	bool EvalA4ANDFromAccumulator(float fBeta);

	///������������ � ������
	void ToString(wstring& szValue);
	///���������� ���������� ������� ������
	void View(void);

	///����� ������������� ������������� �������� ���������
	std::vector<float> m_vfMax;
	///����� ������������� ����������� �������� ���������
	std::vector<float> m_vfMin;
	///����� ������������� ������� �������� ���������
	std::vector<float> m_vfMean;
	///����� ���������
	unsigned int m_uiNumberOfElements;
	///����� ����������� �������� ��������� (��������)
	unsigned int m_uinMean;
	///���� ������� 
	bool m_isEmpty;

};

//--------------------------------------------------------------------//

}
}
}
}
}