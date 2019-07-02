#pragma once

#include "./IExpertController.h"
#include "../ASSInterface/ISyntaxAnalyzer.h"

#include "./ExpertController.h"

namespace SS
{
	namespace Syntax
	{
		///�����, �������������� �������������� ������ ������.
		class CBaseSyntaxAnalyzer :	public SS::Interface::Core::ISyntaxAnalyzer
		{
		private:
			///���������� ���������
			SS::Syntax::ExpertModel::CExpertController m_ExpertController;
		
		private:
			///���������� �������� ����� �����������
			void Init();
			///����� ����� ���������� ��� ���� ������ ��������.
			void ResetIndexationFlags( SS::Interface::Core::BlackBox::IUnit* first,
									   SS::Interface::Core::BlackBox::IUnit* last );
			///�������� ��� ������� ���������� ����� �������������� ���� �� ���������
			void CreateSyntax(SS::Interface::Core::BlackBox::ISentence* pSentence) const;
		
		public:
			/// �����������
			CBaseSyntaxAnalyzer(SS::Syntax::ExpertModel::ESyntaxBase eBase);
			///���������� �������������� ������ ������
			virtual void AnalyzeNext(SS::Interface::Core::BlackBox::IText* text);
			///���������� �������������� ������ �����������
			virtual void AnalyzeNext(SS::Interface::Core::BlackBox::ISentence* sentence);
			///������������
			ULONG Release();
			///���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������
			HRESULT QueryInterface(REFIID pIID, void** pBase);
			///������������� �� IBase
			void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
			///������������� �� CAnalyseParams
			void SetAnalyseParams(SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams);
		};
	}
}