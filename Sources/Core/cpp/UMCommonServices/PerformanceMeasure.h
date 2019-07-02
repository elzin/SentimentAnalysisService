#pragma once

#include "..\ASCInterface\ICommonServices.h"

namespace SS
{
namespace Core
{
namespace CommonServices
{

//--------------------------------------------------------------------//

///�������� ��������� ������������� ���������� ������� ����
class CTickMeasure
{
public:
	CTickMeasure():m_iStartTick(0), m_iStopTick(0), m_iSumTick(0), m_uiStartsCount(0){};
	virtual ~CTickMeasure(){};

	///���������� �������
	unsigned int m_uiStartsCount;
	///������� �����
	__int64 m_iStartTick;
	///������� �������
	__int64 m_iStopTick;
	///����� ����� ����������
	__int64 m_iSumTick;
};

//--------------------------------------------------------------------//

///���������� ��������� ������� ���������� ������� ����
class CPerformanceMeasure : public SS::Interface::Core::CommonServices::IPerformanceMeasure
{
public:
	typedef std::unordered_map<std::wstring, CTickMeasure> TTickMeasures;

	CPerformanceMeasure();
	virtual ~CPerformanceMeasure();

	///������ �������� ������� ����������
	void	StartCalculation(const wchar_t* szID);
	///������� ������ �� ��������������
	void	ClearCalculation(const wchar_t* szID);
	///������� �������
	void	ClearCalculations();
	///������� �������� ������� ����������
	void	StopCalculation(const wchar_t* szID);
	///������� ������� ����������
	double	GetCalculation(const wchar_t* szID);
	///����������� ������� ����������
	void	ViewCalculation(const wchar_t* szID);
	///����������� ���� ������� ������� ����������
	void	ViewCalculations(void);
	///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
	HRESULT QueryInterface(REFIID pIID, void** pBase); 
	///������������
	ULONG Release();

protected:
	///��������� ������� ������� ����������
	TTickMeasures m_TickMeasures;
};

//--------------------------------------------------------------------//


}
}
}

