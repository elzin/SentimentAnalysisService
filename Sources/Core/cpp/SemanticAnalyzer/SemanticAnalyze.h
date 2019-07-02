#pragma once

#include "../ASSInterface/ISemanticAnalyze.h"
#include "SMManager.h"


namespace SS
{
	namespace Core
	{
		class CSemanticAnalyze:
			public SS::Interface::Core::ISemanticAnalyze
		{
		public:
			CSemanticAnalyze(void);
			~CSemanticAnalyze(void);
			//IBase
			///���������� � ���������� � �������� REFIID. 
			/**pBase ����� NULL, ���� ������ ��������� �� ��������������*/
			HRESULT QueryInterface(REFIID pIID, void** pBase); 
			///������������
			ULONG Release();

			//void Init(
			//	///��������� �������
			//	SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams);

			///������ ��������� ����� ������ � ��������� ���������� � pText
			bool AnalyseNext(
				///��� ���� ���������� ���������
				SS::Interface::Core::BlackBox::IText* pText);

			/// ���������� ������ �� ������������� �������
			/** 
			\param pQuery - ��������� ���������� ����������� ������ (��������� � ���������� pQuery)
			\return bool - ������ - ���� �� ���� ������

			�� ������ ���� ������� ������ ���� ������ ����� Init � ���������� - ������ ������� , ����� 
			AnalyseNext(...)
			*/
			bool QueryToSearchString(SS::Interface::Core::BlackBox::IText* pQuery,
				std::wstring * pSearchString);

			bool SyntaxQuestionPostProcess(SS::Interface::Core::BlackBox::IText* pQuery);

			void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);

			void SetAnalyseParams(SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams);


		private:

			SS::Semantic::CSMManager m_SemanticAnalyzeManager;

			SS::Interface::Core::BlackBox::IText * m_pIText;
			//SS::Interface::Core::MainAnalyse::IAnalyseParams* m_pAnalyseParams;
		};

	}
}

