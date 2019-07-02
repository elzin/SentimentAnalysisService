#pragma once
#include "smsentenceexpert.h"

namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace IndexationExperts
			{
				/// ��������� ����������� ����������� � ������
				class CSMDependentClause :
					public CSMSentenceExpert
				{
				public:
					CSMDependentClause(void);
					~CSMDependentClause(void);
					bool AnalizeSentence();

					bool Init(IText * pIText);
				private:
					/// ������ �����
					typedef list<UINT> TSourceList;
					/// ������ �������
					TSourceList m_SingleTime;
					/// ������ �����
					TSourceList m_SinglePlace;
					/// ������ �������
					TSourceList m_SingleCause;
					/// ������ �������
					TSourceList m_SingleManner;
					/// ������ ��������� ������ �������
					list<TSourceList> m_MultiTime;
					/// ������ ��������� ������ �������
					list<TSourceList> m_MultiManner;
					/// ������ ��������� ������ �������
					list<TSourceList> m_MultiCause;
					/// ��������� ����� 
					list<SS::Dictionary::Types::TDictionaryIndex/*SS::Dictionary::Types::TDictionaryIndex*/> m_SemanticPlace;
					/// ��������� �������
					list<SS::Dictionary::Types::TDictionaryIndex/*SS::Dictionary::Types::TDictionaryIndex*/> m_SemanticTime;

					/// ���������� ������ - ���� ����������� ������������� �� �� �������������� ����
					bool TestNotQuestion();
					/// ������, ���� ������� ����� - ������� ����
					/** 
						\param oSingle - ������ ����� ������� ������
					*/
					bool FindSingleConj(TSourceList & oSingle);
					/// ������, ���� ������� ����� ( � ��� ���������) - ��������� ����
					/** 
						\param oMulti - ������ ����� ��������� ������
					*/
					bool FindMultiConj(list<TSourceList> & oMulti);
					/// ���������� ��� ����� ��������� �����
					void AddPlaceCategory();
					/// ���������� ��� ����� ��������� �������
					void AddTimeCategory();
					/// ���������� ��� ����� ��������� �������
					void AddMannerCategory();
					/// ���������� ��� ����� ��������� �������
					void AddCauseCategory();
					/// ������, ���� � ������� ���� ������
					/**  
						\param pIndex - ������ 
						\param uiSourceIndex - ������
					*/
					bool IsIndexExist(IIndex * pIndex, UINT uiSourceIndex);

				};

			}
		}
	}
}