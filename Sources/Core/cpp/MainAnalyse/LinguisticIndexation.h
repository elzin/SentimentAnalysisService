#pragma once

#include "../ASCInterface/ILinguisticProcessor.h"

#include "./LinguisticWorkingInterfaces.h"
#include "./TextIndexation.h"
#include "./TableIndexation.h"

namespace SS
{
namespace LinguisticProcessor
{
namespace Indexation
{
	unsigned int GetLastPositon(SS::Interface::Core::BlackBox::IText * pText);
	unsigned int GetFistPositon(SS::Interface::Core::BlackBox::IText * pText);
	unsigned int GetUnitLastPositon(SS::Interface::Core::BlackBox::IUnit * pUnit);

	class CLinguisticIndexation : public SS::Interface::Core::ILinguisticIndexation

	{
		bool m_bIsTextIndexation;
		bool m_bIsTableIndexation;
		SS::LinguisticProcessor::Indexation::CTextIndexation			m_oTextIndexation;
		SS::LinguisticProcessor::Indexation::CTableIndexation		m_oTableIndexation;
		unsigned int m_uiCurPosition;
		unsigned int uiFistCharPosition;

	public:
		CLinguisticIndexation(void);
		~CLinguisticIndexation(void);
	public:
		///������ �������� ���������� ���������
		HRESULT StartDocumentIndexation();

		/// ���������� ������� ���������� ���������� ���������� ����� ���������� ������ 
		void Init(
			/// ��������� � ������������� �������
			SS::Core::Types::IndexationSearch::TNativeTextForIndexation* pNativeText
			/// ��������� ���������� ������
			, SS::Core::Types::IndexationSearch::TIndexationParams* pIndexationParams
			);

		/// ���������� ������� ���������� ��������� ������� ���������� ������ 
		void Init(
			std::list< std::list<SS::Core::Types::IndexationSearch::TNativeTextForIndexation*> > * p_l_l_NativeText
			/// ��������� ���������� ������
			, SS::Core::Types::IndexationSearch::TIndexationParams* pIndexationParams
			);

		/// ���������� ��������� ������ �������
		/**
		������:
			0 - ���� ���� ��� ����� ��� �������
			1 - ���� ������ ���
			2 - ���� ���� ������
		*/
		unsigned int GenerateNext(
			/// ��������� �� ���������, ������� ���������� ���������
			SS::Interface::Core::CommonContainers::IIndexationResult* pIndexationResult
			);
		///������� �������� ���������� ���������
		HRESULT EndDocumentIndexation();


	public:
		virtual void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
	public:
		void SetMode(SS::Core::Types::IndexationSearch::TLinguisticProcessorMode* pMode);
	private:
		//void SaveText(int iTextNumber, const wchar_t* wzText, const wchar_t* wzTextType);
		//void SaveNativeText(SS::Core::Types::IndexationSearch::TNativeTextForIndexation* pNativeText); 

	};
}
}
}