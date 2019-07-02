#pragma once

#include "..\ASSInterface\IBlackBoxSyntaxUnit.h"
using namespace SS::Interface::Core::BlackBox;


namespace SS
{
namespace Core
{
namespace BlackBox
{

class CSyntaxFeature : public ISyntaxFeature
{
public:
	CSyntaxFeature();
	virtual ~CSyntaxFeature();

public:
	///������������� �������������� ��������������
	void SetSyntaxCategory(unsigned int uiSyntaxCategory);
	///������������� �������������� ������������� �������������� 
	void SetSyntaxFeatureAposteriori(SS::Core::Features::CSyntaxFeatureAposteriori* pSyntaxFeatureAposteriori);
	///������������� �������������� ��������������
	void SetSyntaxFeatureApriori(SS::Core::Features::CSyntaxFeatureApriori* pSyntaxFeatureApriori);
	///���������� �������������� ��������������
	unsigned int GetSyntaxCategory();
	///���������� �������������� ������������� �������������� 
	SS::Core::Features::CSyntaxFeatureAposteriori* GetSyntaxFeatureAposteriori();
	///���������� ��������������  �������������� 
	SS::Core::Features::CSyntaxFeatureApriori* GetSyntaxFeatureApriori();
	///������������� ��� ���� ������
	void SetIsQuestion();
	///������������� ��� ���� �� ������
	void SetIsNotQuestion();
	///��������� �������� �� ���� ��������
	unsigned int IsQuestion();
	///������ ������, ���������� ������ � ������
	unsigned int GetMemorySize();

private:
	///������� �������
	bool m_bQuestion;
	///�������������� ���������
	unsigned int m_uiSyntaxCategory;
	///������������� �������������� ����������
	SS::Core::Features::CSyntaxFeatureAposteriori m_SyntaxFeatureAposteriori;
	///��������������  �������������� 
	SS::Core::Features::CSyntaxFeatureApriori m_SyntaxFeatureApriori;
};

}
}
}
