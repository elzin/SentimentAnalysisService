#pragma once
//#include "..\assinterface\WorkWithManagerConnection.h"
#include "..\ASSInterface\IAMConverter.h"
#include "..\assinterface\iblackbox.h"
//#include "..\ASSInterface\IDateVirtualDictionary.h"
#include "..\ASSInterface\IDictionaryManager.h"
#include ".\smexpertgroup.h"
#include "..\ASCInterface\services.h"

#include "SMPostSyntax.h"
#include "SMQueryG.h"
#include "SMIndaxation.h"
#include "SMQuestion.h"
#include "..\ASCInterface\services.h"

#include ".\OfficialVirtualSemanticDictionary.h"


namespace SS
{
	namespace Semantic
	{
		class CSMExpert;

		class CSMManager
			: virtual public SS::Core::CommonServices::CBaseCoreClass
			, virtual public SS::Interface::Core::Common::CAnalyseParams
		/// ��������� ���������� - ������������ ��������� �� ����������, ���������� ���������
			//public SS::Core::Classes::CWorkWithManagerConnection
		{
		public:
			CSMManager(void);
			~CSMManager(void);
			
			void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
			/// ���������� ������
			/** 
				\param str - ������
			*/
			void SetQueryString(wstring & str){ m_sQuery=str; };

			SS::Interface::Core::AMConverter::IAMConverterMorpho * GetAMConverterMorpho(){return m_pIAMCMorpho;};
			SS::Interface::Core::AMConverter::IAMConverterSemantic * GetAMConverterSemantic(){return m_pIAMCSemantic;};
			SS::Semantic::VirtualDictionaries::COfficialVirtualSyntaxDictionary * GetOfficialVirtualSyntax(){ return m_pOfficialVirtualSyntax; };
			SS::Interface::Core::BlackBox::IBlackBoxTextStorage * GetBlackBoxTextStorage(){ return m_pIBlackBoxFactory;};
			SS::Interface::Core::Dictionary::IMorphologyAnalyser * GetDictionaryInterface(){ return m_pDictionaryInterface; };

			/// �������� ������ ����� ���������� 
			/** 
				\param pIText - ����������� ������
			*/
			void AnalizeQuestion(SS::Interface::Core::BlackBox::IText * pIText);
			/// �������������� ������� � ������ �������
			/** 
				\param pIText - ����������� ������
				\return 			wstring - ������ ����������
			*/
			void CollectQuestion(SS::Interface::Core::BlackBox::IText * pIText, std::wstring * pSearchString);
	
			/// ���������� ������� ���� ����������
			void IndexateText(SS::Interface::Core::BlackBox::IText * pIText);
			/// ������ �������
			void QuestionAnalysis(SS::Interface::Core::BlackBox::IText * pIText);

		private:
			///��������������� ��������� 
			SS::Interface::Core::AMConverter::IAMConverterMorpho * m_pIAMCMorpho;
			///������������� ���������
			SS::Interface::Core::AMConverter::IAMConverterSemantic * m_pIAMCSemantic;
			SS::Interface::IBase * m_pVirtualDictionaries;
			SS::Semantic::VirtualDictionaries::COfficialVirtualSyntaxDictionary * m_pOfficialVirtualSyntax;
			SS::Interface::Core::BlackBox::IBlackBoxTextStorage * m_pIBlackBoxFactory;
			SS::Interface::Core::Dictionary::IMorphologyAnalyser * m_pDictionaryInterface;
			/// ������ ������� 
			wstring m_sQuery;
			/// ��� �������� � �������
			std::list<CSMExpert*> m_AllExperts;
			/// �������� ��� �������������� ������� ����� ����������
			Groups::CSMPostSyntax m_QuestionParse;
			/// �������� ��� ����� ����������
			Groups::CSMQueryG m_QuestionGenerator;

			/// �������� ��� ����������
			Groups::CSMIndaxation m_IndaxationGroup;
			/// �������� ��� ������� �������
			Groups::CSMQuestion m_QuestionGroup;



		};
	}
}