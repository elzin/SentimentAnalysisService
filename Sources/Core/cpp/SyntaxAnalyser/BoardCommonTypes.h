#pragma once
#include <vector>
#include <list>

namespace SS
{
	namespace Syntax
	{
		namespace BoardElements
		{
			class CBlock;
			class CBoardElement;
			class CBlockVersionElement;
			class CMorphoListElement;
						
			///��������� ��������� �����
			typedef std::vector<CBoardElement*> BoardCollection;
			///�������� ��� ���������� ��������� �����
			typedef std::vector<CBoardElement*>::iterator BoardElementsIterator;
			///��������� �� ����
			typedef CBlock* PBLOCK;
			///������� ����������
			typedef CMorphoListElement  MORPHO;
			///��������� �� ������� ����������
			typedef CMorphoListElement* PMORPHO;
			///������� ��������
			typedef CBlockVersionElement  VERELEMENT;
			///��������� �� ������� ��������
			typedef CBlockVersionElement* PVERELEMENT;

			///������ ���������� ����������
			#define SIZEMORPHO 24

			///�������������� ��������, �������� �� �� ���������
			struct SBlockVersionCharacteristics
			{
				///���������� �������� ���������
				int m_headCount;
				///���������� ���������, ������� �� ��������� �������������� ���������
				int m_unfilledCount;
				///���������� ���������
				int m_mainCount;
				///���������� ����������
				int m_SFinCount;
				///���������� ���������� � �����������
				int m_SComplCount;
				///�������� ��������� �������� ���������
				bool m_isMainRoot;
				///�������� ��������� �������� ������
				bool m_isVerbRoot;
				///�������� �������� ����������
				bool m_isSFin;
				///�������� �������� Chain
				bool m_isChain;
				///�������� �������� ��������� ����� ���������� � ���������
				bool m_isInfBetween;
				///�������� �������� ������
				bool m_isVerbMet;
				///�������� �������� ���������� ����� �������
				bool m_isAdjAfterVerb;
				///�������� �������� ���������� �� �������, �� �� � ������ ��������
				bool m_isAdjBeforeVerb;
				///�������� �������� ������������������ �� �������, ���������� � ���������� � �����������
				bool m_isVerbAdjSCompl;
				///�������� �������� �����-���� Adjunct
				bool m_isAdjunct;
				///���������� Object � ��������
				int m_ObjectCount;
			};
		}
	}
}

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			///������������ ������������ ��� �������������� �����������
			enum ESyntaxBase
			{
				sbStandart,
				sbRussianNQ
			};
		}
	}
}