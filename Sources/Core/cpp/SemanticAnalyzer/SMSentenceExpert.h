#pragma once
#include "smexpert.h"
namespace SS
{
	namespace Semantic
	{
		/// ������� ����� ��� ��������� ���������� � �������������
		class CSMSentenceExpert : public CSMExpert
		{
		public:
			CSMSentenceExpert(void);
			virtual ~CSMSentenceExpert(void);
			/// ������ ������ BlackBox
			/** 
			\return bool - ������ - ���� ������ ������ �������

			����� ������ ��������� � ��������� ���������
			*/
			bool Analize();
			bool Init(IText * pIText);
			
		protected:
			/// ������ �������� �����������
			virtual bool AnalizeSentence()=0;
			/// ��������� ����������������
			set<wstring> m_PreDeterminerStrings;
			/// ������� ��������������� ��������� ���������
			set<wstring> m_StopPretexts;
			/// ������� ��������������� ��������� ��������
			set<wstring> m_AdverbStrings;
			/// ��������� ��� ��������� ����������
			SS::Core::Features::CMorphoFeature m_MorphoFeature;
			/// ��������� ��� ��������� ���������
			SS::Core::Features::CSemanticFeature m_SemanticFeature;

			/// ����� �������� ����� ������� ������ ��� ����������
			/** 
			\param uiDepth - ������� ������ - ���� �� �����
			\param pUnit - ���� ����� ������� ������ �������

			\return 		IUnit - ��������� �� �������
			*/
			IUnit * IsPrepositionBeforeE(UINT uiDepth,IUnit * pUnit,bool bPlaceTime=false);
			/// ������, ���� ���� ���� ����������������
			bool IsPredeterminer(IUnit* pUnit);

			/// ������, ���� ���� ���� �������
			bool IsPretext(IUnit * pUnit);

			/// ������, ���� ���� ���� ������������
			bool IsDeterminer(IUnit * pUnit);

			/// ����� �������� ����� ������� ������ ��� ��������
			/** 
			\param uiDepth - ������� ������ - ���� �� �����
			\param pUnit - ���� ����� ������� ������ �������

			\return 		IUnit - ��������� �� �������
			*/
			IUnit * IsPrepositionBeforeR(UINT uiDepth,IUnit * pUnit);
			
			/// ��������� �������������� ���������, �������� ������ ������� ���� ( ����� ��� �����) 
			/** 
				\param l_Syntax - ������ ���������
				\param bTime - ���: ������ - �����, ���� - ����� 
				\return 			bool - ���� �������������� ������ �� ����
			*/
			bool FilterSyntax(list<Types::SyntaxCategories> & l_Syntax, bool bTime);
			/// ��������� ��� ����� - ���� �������
			bool IsStopPretextOrAimAdverb(bool bStop);
			bool IsConjunction(IUnit * pUnit);
			bool IsUpConjunction();

		};

	}
}