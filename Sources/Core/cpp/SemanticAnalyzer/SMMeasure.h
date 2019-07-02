#pragma once
#include "smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{

///��������� ������������� ���� 
class CSMMeasure :
	public CSMSentenceExpert
{
public:
	CSMMeasure(void);
	~CSMMeasure(void);
	bool AnalizeSentence();
	bool Init(IText * pIText);
private:

	set<long> * m_s_Time;
	bool m_bManyMeasureUnits;

	/// ������, ���� ���� ����� ��������� �������
	bool IsSemTime();
	
	/// ��������� ����� �������
	/** 
		\param l_Units - ���������
		\return 	bool - ������ - ���� ������� 
	*/
	bool AddDigitsFront(TBoxUnits & l_Units);
	/// ��������� ����� �����
	/** 
		\param l_Units - ���������
		\return 	bool - ������ - ���� �������
	*/
	bool AddDigitsBack(TBoxUnits & l_Units);
	/// ���������� ������ ������ , ��� �� ��������� ���� � ���������
	/** 
		\param l_Units - ������
		\param oMeasure - ���������
	*/
	void ProcessMeasure(TBoxUnits & l_Units, Types::TSMeasureType oMeasure);

	/// �������� ����������� ���� end of � ���������� � ������
	bool AddOfFront(TBoxUnits & l_Units);
	/// ���������� ������ ������ , ��� �� ��������� ������� �  ��������� ���������
	/** 
	\param l_Units - ������
	*/	
	void ProcessTimeFixedPoint(TBoxUnits & l_Units, IUnit * pUnit);
	
	/// ������, ���� ���� ����� ��������� �����
	bool IsSemNumber(IUnit * pUnit=NULL);

	/// ��������� c ���������� �������
	void TimeProcess();

	/// ��������� c ���������� ������� � ����
	void MeasureTimeProcess();
	
	/// ��������� c ���������� ����
	void MeasureProcess();

	/// ��������� c ���������� ����
	void MeasureProcessEx();

	/// ������, ���� ���������� ������ AjunctMeasure
	bool IsSetMeasure();

	bool SubTimeProcess();

	bool AddOfBack(TBoxUnits & l_Units);

	void MoveToAjunctTime();

	/// ���������� ������ ������ , ��� �� ��������� ������� � ���������� ��������� undef
	void SecondProcessTimeFixedPoint(TBoxUnits & l_Units);

	bool CheckAimWords();
	bool IsTire();
	bool FindFirstTire();
	bool IsFindNumberSemTime(TBoxUnits & l_Units);

};


		}
	}
}