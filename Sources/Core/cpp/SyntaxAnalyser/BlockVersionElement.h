//BlockVersionElement.h
#pragma once
#include "BoardCommonTypes.h"
#include "../ASSInterface/Construction.h"
#include "SemanticService.h"

namespace SS
{
namespace Syntax
{
namespace BoardElements
{
	///������� �������� �������.
	class CBlockVersionElement
	{
	public:
		///�����������
		CBlockVersionElement();
		///����������� �����������
		CBlockVersionElement(const CBlockVersionElement & el) {	Assign(&el); };
		///����������
		~CBlockVersionElement(){};
		///������������� ������������� ��������
		void Init(CBoardElement* pElem, PMORPHO pMorpho);
		///��������� �������� ����������� �������� ��������
		void Assign(const CBlockVersionElement* pElem)
		{
			m_morphoFeatureApriori.Assign(&pElem->m_morphoFeatureApriori);
			m_syntaxFeatureAposteriori.Assign(&pElem->m_syntaxFeatureAposteriori);
			m_syntaxFeatureApriori.Assign(&pElem->m_syntaxFeatureApriori);
			m_pMorpho = pElem->m_pMorpho;
			m_isHead = pElem->m_isHead;
			m_iIdGroup = pElem->m_iIdGroup;
			m_oSemanticService = pElem->m_oSemanticService;
		}
	
	public:
		///��������� �� ��������������� �������������� ��������, ���������� ������ �������.
		PMORPHO m_pMorpho;
		///��������������� ���������� (��� ��������������)
		SS::Core::Features::CMorphoFeatureApriori m_morphoFeatureApriori;
		///������������� �������������� ����������.
		SS::Core::Features::CSyntaxFeatureAposteriori m_syntaxFeatureAposteriori;
		///��������� �������������� ����������
		SS::Core::Features::CSyntaxFeatureApriori m_syntaxFeatureApriori;
		///���������, ����� �� ������� � ������ �� ������� ������.
		bool m_isHead;
		///������� ������� ��������� ����� �������������� ��������� ��������.
		int	m_iIdGroup;
		///������������� ��������������
		CSemanticService m_oSemanticService;
	};
}
}
}