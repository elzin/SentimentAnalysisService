#pragma	once

#include "BoardCommonTypes.h"
#include "../FeatureLibrary/define.h"
#include "Container.h"

namespace SS
{
	namespace Syntax
	{
		namespace BoardElements
		{
			///�����, ����������� ��������� �������������� ��������������� �������������� ����� 
			class CMorphoFormsFilter
			{
			private:
				//��������� �������������� ����������
				std::list<PMORPHO> m_lstMorphoRemoved;

			private:
				///�����-�������� ��� ��������� ��������������� ���
				class CMorphoComparePredicate
				{
				public:
					///�����������
					CMorphoComparePredicate() : m_pMorphoFeature(NULL) {};
					///��������� ��������������� ��� ��� ����� �������������� ���������
					bool operator()(SS::Core::Features::CMorphoFeature* pMorphoFeature);
					///���������� ����
					void SetMorphoFeature(SS::Core::Features::CMorphoFeature* pMorphoFeature)
					{ m_pMorphoFeature = pMorphoFeature; };
				
				private:
					///������������ MorphoFeature
					SS::Core::Features::CMorphoFeature* m_pMorphoFeature;
				};
				
				///�����-�������� ��� ��������� ��������������� ��� (��� �������� �����)
				class CMorphoComparePredicateRus
				{
				public:
					///�����������
					CMorphoComparePredicateRus() : m_pMorphoFeature(NULL) {};
					///��������� ��������������� ��� ��� ����� �������������� ���������
					bool operator()(SS::Core::Features::CMorphoFeature* pMorphoFeature);
					///���������� ����
					void SetMorphoFeature(SS::Core::Features::CMorphoFeature* pMorphoFeature)
					{ m_pMorphoFeature = pMorphoFeature; };

				private:
					///������������ MorphoFeature
					SS::Core::Features::CMorphoFeature* m_pMorphoFeature;
				};

				///������-��������
				CMorphoComparePredicate m_oPredicate;

				///������-�������� �������
				CMorphoComparePredicateRus m_oPredicateRus;
			
			public:
				///�������� ������� �� ���������������� ���������� �������� ��������������� ����
				void FilterMorphoContainer(CContainer<MORPHO,SIZEMORPHO> & lstMorphoContainer);
				///�������� ������� �� ���������������� ���������� �������� ��������������� ���� (��� �������� �����)
				void FilterMorphoContainerRus(CContainer<MORPHO,SIZEMORPHO> & lstMorphoContainer);
				///��������� � ��������� ��������������� ����, ������� �� �������������� (�������������)
				void RestoreMorphoContainer(CContainer<MORPHO,SIZEMORPHO> & lstMorphoContainer);
			};
			
		}
	}
}