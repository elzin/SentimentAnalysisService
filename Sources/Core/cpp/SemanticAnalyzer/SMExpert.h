#pragma once
#include "..\ASSInterface\IAMConverter.h"
#include "..\assinterface\iblackbox.h"

#include "StringService.h"
#include ".\lexemtype.h"
#include ".\types.h"

#include ".\OfficialVirtualSemanticDictionary.h"
#include "..\assinterface\IDictionaryManager.h"
#include "..\assinterface\TDictionaryNames.h"


using namespace SS::Interface::Core::BlackBox;

namespace SS
{
	namespace Semantic
	{
		class CSMManager;

		typedef list<IUnit*> TBoxUnits;
		/// ��������� ������ ��
		struct SCurrentPosition
		{
			IText * _pIText;
			IParagraph * _pParagraph;
			ISentence * _pSentence;
			IUnit * _pUnit;
		};
	
		/// ����� ��������� � ��������� ����� ����������������
		class CSMExpert : virtual public SS::Interface::Core::Common::CAnalyseParams
		{
		public:
			CSMExpert(void);
			virtual ~CSMExpert(void);
			
			/// ������ ������ BlackBox
			/** 
				\return bool - ������ - ���� ������ ������ �������
			 
			����� ������ ��������� � ��������� ���������
			*/
			virtual bool Analize()=0;
			
			///������������� �������� ������� pIText
			virtual bool Init(IText * pIText);

			///���������� �������� ��������
			wstring& GetDescription()
			{ 
				return m_sDescription; 
			};

			///������������� ��������� �� �������� �������
			void SetSMManager(CSMManager * pManager);

			/// ������, ���� ������ ������� �����������
			bool IsExecuteExpert(SS::Core::Types::EAnalyseLanguage eAnalyseLanguage)
			{
				if(eAnalyseLanguage==SS::Core::Types::ealUndefined) return true;
				if(m_AnalyseLanguage==SS::Core::Types::ealUndefined) return true;
				return (eAnalyseLanguage == m_AnalyseLanguage) ; 
			};


			void SetCurrentSentence(ISentence * pSentence){ m_pCurrentSentence=pSentence; };

		protected:
			/// ��������� �������� ��������
			wstring m_sDescription;
			///��������������� ��������� 
			SS::Interface::Core::AMConverter::IAMConverterMorpho * m_pIAMCMorpho;
			///������������� ���������
			SS::Interface::Core::AMConverter::IAMConverterSemantic * m_pIAMCSemantic;
			/// ������� ���������
			SS::Semantic::VirtualDictionaries::COfficialVirtualSyntaxDictionary * m_pOfficialVirtualSyntax;
			/// ������� ���� �����
			SS::Interface::Core::BlackBox::IBlackBoxTextStorage * m_pIBlackBoxFactory;
			/// �������� �� ������ �� ��������� 
			CSMManager * m_pSMManager;
			///����� � �������
			IText * m_pIText;
			/// ������� ��������
			IParagraph * m_pCurrentParagraph;
			/// ������� �����������
			ISentence * m_pCurrentSentence;
			/// ������� ����
			IUnit * m_pCurrentUnit;
			/// ������� ������ �������� �����
			IIndex * m_pCurrentIndex;
			/// ������
			SCurrentPosition m_oMem;
			/// ������1
			SCurrentPosition m_oMem1;
			/// ������2
			SCurrentPosition m_oMem2;
			/// ��������� �����
			SS::Semantic::CStringService m_StringService;
			/// ����������� ���� ������
			CLexemType m_LexemType;
			/// ���� �������
			SS::Core::Types::EAnalyseLanguage m_AnalyseLanguage;
			/// ��������� ���������� ��� ������� CollectMorpho
			SS::Core::Features::CMorphoFeature m_MorphoFeatureCollect;
			/// ������, ���� ������� ���������������
			bool m_bInit;

			/// ���������� ������, ���� ����� �������
			bool IsQuestionMode(){ return false;};
			/// ������, ���� ����� ������� �� �������� ������
			bool IsStrictMode(){ return false; };
			/// ��������� ������� �������
			void Mem();
			/// ������� � ���������� �������
			void GotoMem();
			void Mem1();
			void GotoMem1();
			void Mem2();
			void GotoMem2();
			/// ������� � ����� � ������ 1 �����������
			void GotoUnit(IUnit * pUnit);
			/// ������� ���� � ���������� ������, ���� ���� ����� �������, ���� � ��������� ������ ( ������� ���������� ����������)
			bool HideCurrentUnit();


			/// ������������� �������� �� ������ ��������
			bool GetFirstParagraph();
			/// ��������� ��������
			bool GetNextParagraph();
			/// ������ ����������� �������� ���������
			bool GetFirstSentence();
			/// ��������� �����������
			bool GetNextSentence();
			/// ������ ���� �������� �����������
			IUnit * GetFirstUnit();
			/// ��������� ���� �������� �����������
			IUnit * GetLastUnit();
			/// ��������� ����
			IUnit * GetNextUnit();
			/// ��������� ���� � ������ �����
			IUnit * GetNextUnitWithChild();
			/// ���������� ����
			IUnit * GetPrevUnit();
			/// ������ ������ �����
			IIndex * GetFirstIndex(IUnit * pUnit=NULL);
			/// ��������� ������
			IIndex * GetNextIndex(IUnit * pUnit=NULL);

		private:
			/// ��������� �������������� �����
			/** 
				\param uiFeature - ��������������
				\param pUnit=NULL  - �����
			*/
			void AddFeature(UINT uiFeature, IUnit * pUnit=NULL);
		protected:
			void AddFeature(CommonFeature eFeature,IUnit * pUnit=NULL);
			void AddFeature(ERusFeature eFeature,IUnit * pUnit=NULL);
			void AddFeature(EEngFeature eFeature,IUnit * pUnit=NULL);

			/// ������, ���� ����� �������� ������ ��������������
			/** 
			\param uiFeature - ��������������
			\param pUnit=NULL  - �����
			*/
			//private:

			bool IsContainFeature(UINT uiFeature, IUnit * pUnit=NULL);
			bool IsContainFeature(CommonFeature eFeature,IUnit * pUnit=NULL);
			bool IsContainFeature(ERusFeature eFeature,IUnit * pUnit=NULL);
			bool IsContainFeature(EEngFeature eFeature,IUnit * pUnit=NULL);

			void RemoveFeature(CommonFeature eFeature,IUnit * pUnit=NULL);

			void SetSpecialType(TSpecialUnitType eSpecialType, IUnit * pUnit=NULL);
			bool SpecialTypeEquals(TSpecialUnitType eSpecialType, IUnit * pUnit=NULL);
			
			//void SetSyntaxType(TSyntaxUnitType eSyntaxType, IUnit * pUnit=NULL);
			//bool SyntaxTypeEquals(TSyntaxUnitType eSyntaxType, IUnit * pUnit=NULL);
			
			/// ������������� ���� ���������� - ������, ���� ���� ������ � �������������� ���������
			/** 
				\param pUnit=NULL - ����� 
				\param bFlag=true - ����
			*/
			void SetSyntax(IUnit * pUnit=NULL, bool bFlag=true);
			/// ���������� �������� ����� ����������
			bool IsSyntax(IUnit * pUnit=NULL);
			/// ������, ���� ������� ����� ���� ������� � �����������
			bool IsPrepositionSyntax(IUnit * pUnit=NULL);
			/// �������� � ��������� ��������������� ��������������
			/** 
				\param oMorphoFeature - ���������
				\param pUnit=NULL - ����
			*/
			void CollectMorphoFeature(SS::Core::Features::CMorphoFeature & oMorphoFeature, IUnit * pUnit=NULL);
			/// �������� ������������� ������� ����� � ���������
			/** 
			\param pUnit - ����
			\param oSemanticFeature - ���������
			\return 			bool - ������, ���� ��������� ����
			*/
			bool CollectSemanticFeature(SS::Core::Features::CSemanticFeature & oSemanticFeature, IUnit * pUnit=NULL);
			/// ��������� ����� ������ ������ ���������� �������������� ����
			/** 
			\param oSemType - ������������� ��� ������� ����� ��������
			\param l_Sem - ������ ����������� ������������� ��������
			\return 			bool - ������, ���� ���� ���������� �������
			*/
			bool KeepSpecifedSemanticTypes(const SS::Core::Features::Types::TSemanticType & oSemType, list<SS::Dictionary::Types::TDictionaryIndex> & l_Sem);

			/// ���������� ������ �������� ������ �����
			/** 
				\param pWord - ����� 
				\param l_Sources - ������ �������� 
				\return 			bool - ������ - ���� ������ �� ���� 
			*/
			bool GetWordSourceIndices(const TCHAR * pWord,list<UINT> & l_Sources);
			/// ���������� ���������� �����
			/** 
				\param pWord - ����� 
				\param l_Info - ����������
				\return 			bool - ������ , ���� ���������� � ����� ����
			*/
			bool GetWordMorphoInfo(const TCHAR * pWord,list<SS::Dictionary::Types::TWordInfo> & l_Info);
			/// ���������� ����� � ���������� 
			/** 
				\param oUnits - ������ ������
				\return 			IUnit * - ���� �������� ������
			*/
			IUnit * JoinUpUnits(TBoxUnits & oUnits);


			/// ���������� �������������� ��������� �����
			/** 
				\param pUnit - ����
				\param oCategory - ���������
			*/
			void SetSyntaxCategory(IUnit * pUnit, const Types::SyntaxCategories & oCategory);
			/// ���������� �������������� ��������� �����
			/** 
			\param pUnit - ����
			\param oCategory - ���������
			*/
			void AddSyntaxCategory(IUnit * pUnit, const Types::SyntaxCategories & oCategory);
			/// ������� �������������� ��������� � �����
			/** 
			\param pUnit - ����
			\param oCategory - ���������
			*/
			void DeleteSyntaxCategory(IUnit * pUnit, const Types::SyntaxCategories & oCategory);
			/// ��������� ������� �������������� ��������� � �����
			/** 
			\param pUnit - ����
			\param oCategory - ���������
			*/
			bool IsContainSyntaxCategory(IUnit * pUnit, const Types::SyntaxCategories & oCategory);
			/// ��������� ������ �������������� ��������� �����
			/** 
			\param pUnit
			\param l_oCategory
			*/
			void AddSyntaxCategoryIndices(list<Types::SyntaxCategories> & l_oCategory, IUnit * pUnit=NULL);
			/// ��������� ������ �������������� ��������� �����
			/** 
			\param pUnit
			\param l_oCategory
			*/
			void AddSyntaxCategoryIndices(list<UINT> & l_oCategory, IUnit * pUnit=NULL);
			void RemoveSyntaxCategoryIndices(list<UINT> & l_oCategory, IUnit * pUnit=NULL);
			/// ��������� ������ �������������� ��������� �����
			/** 
			\param pUnit
			\param oCategory
			*/
			void AddSyntaxCategoryIndex(const Types::SyntaxCategories & oCategory, IUnit * pUnit=NULL);
			/// ������� ������ ��������� � �����
			/** 
				\param oCategory - ���������
				\param pUnit=NULL - ����
			*/
			void RemoveSyntaxCategoryIndex(const Types::SyntaxCategories & oCategory, IUnit * pUnit=NULL);
			bool IsContainSyntaxCategoryIndex(const Types::SyntaxCategories & oCategory, IUnit * pUnit=NULL);
			/// ���� ������ � ������ �������� �������
			/** 
				\param uiIndex - ������ ������� ( ������ ) 
				\param pUnit - ����� 
				\return 			IIndex * - ������ 
			*/
			IIndex * FindIndex(UINT uiIndex, IUnit * pUnit=NULL ); 
			/// ��������� ������ �����
			/** 
				\param uiIndex - ������
				\param pUnit - ����
			*/
			void AddIndex(SS::Dictionary::Types::TDictionaryIndex uiIndex, IUnit * pUnit=NULL );
			/// ������� ������������� ������� � ����� � ��������� �� � ������ 
			/** 
				\param pUnit - ����
				\param l_Sem - ������ � ������� ����� �������� ��������� �������
			*/
			void RemoveSemanticIndicesFromUnit(list<SS::Dictionary::Types::TDictionaryIndex> & l_Sem, IUnit * pUnit=NULL);

			/// ������������� ������������� ������� �����
			/** 
				\param pUnit - ����
				\param l_Sem - ������������� �������
			*/
			void SetSemanticIndices(list<SS::Dictionary::Types::TDictionaryIndex> & l_Sem, IUnit * pUnit=NULL);

			/// ������������� ������������� ������� �����
			/** 
				\param pUnit - ����
				\param l_Sem - ������������� �������
			*/
			void SetSemanticIndicesWithOutGeneric(list<SS::Dictionary::Types::TDictionaryIndex> & l_Sem, IUnit * pUnit=NULL);


			/// ��������� ������������� ������� �����
			/** 
				\param lSem - ���������
				\param pUnit=NULL - ����
			*/
			void AddSemanticIndex(SS::Dictionary::Types::TDictionaryIndex  lSem,  IUnit * pUnit=NULL);
			/// �������� ������� ���������� �������������� �������
			/** 
				\param lSem -���������
				\param pUnit=NULL - ����
				\return 			bool - ������, ���� ���� ��������� ���������
			*/
			bool IsContainSemanticIndex(long  lSem,  IUnit * pUnit=NULL);
			/// ��������� �������������� ������ �����
			/** 
				\param pUnit - ���� 
				\param uiIndex - ������
			*/
			void AddSyntaxIndex(UINT uiIndex,IUnit * pUnit=NULL);
			/// ������ ���� ������ �������������
			bool IsSemanticIndex(IIndex* pIndex);
			/// ������ ���� ������ ���������������
			bool IsMorphoIndex(IIndex* pIndex=NULL);
};

	}
}

