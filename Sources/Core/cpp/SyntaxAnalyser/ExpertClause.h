//ExpertClause.h
#pragma once
#include "BaseExpert.h"

namespace SS
{
namespace Syntax
{
namespace ExpertClause
{
	using namespace ExpertModel;
	using namespace SS::Core::Features;
	///������� ��� ������� ����������� ������� ����������� ��������������� ����������� c where/when/why
	class CExpertClauseRelative : public CBaseExpert
	{
	private:
		///��������� ����� � ������ ������������ �����������
		std::vector<std::wstring> m_Words;
		///��� ����������� �������� ���� � ������������ ��������������
		CSyntaxFeatureAposteriori m_oSyntaxFeatureAposterioriSecondMember;
		///��� ����������� �������� ���� � ������������ ��������������
		CSyntaxFeatureAposteriori m_oSyntaxFeatureAposterioriFirstMember;

	public:
		///�����������
		CExpertClauseRelative();
		///����������
		~CExpertClauseRelative(){};
		///������ �� ����� 
		bool PassBoard(CBoard & rBoard, PBLOCK pBlock);
		///���������� ��������� �������� ��������
		std::wstring GetName() const;
	};

	///������� ��� ������� ����������� ������� ����������� ������������������ �����������
	class CExpertClauseAdjunct : public CBaseExpert
	{
	private:
		///��������� ����� � ������ ��������� ��� ������������ �����������
		std::vector<std::wstring> m_Words;
		///��� ����������� �������� ���� � ������������ ��������������
		CSyntaxFeatureAposteriori m_oSyntaxFeatureAposteriori;
		///��� ����������� �������� ���� � ������������ ��������������
		CSyntaxFeatureAposteriori m_oSyntaxFeatureAposterioriNeed;
		///��������� �� �������� ���� (��� ������� �������� �������������� �����)
		enum EActiveBlock
		{
			eFirst,
			eSecond
		} m_eActiveBlock;
		///��������� �������������� ���������
		unsigned int CalcSyntaxCategory(BoardElementsIterator itElem);

	public:
		///�����������
		CExpertClauseAdjunct();
		///����������
		~CExpertClauseAdjunct(){};
		///������ �� ����� 
		bool PassBoard(CBoard & rBoard, PBLOCK pBlock);
		///���������� ��������� �������� ��������
		std::wstring GetName() const;
	};

}
}
}