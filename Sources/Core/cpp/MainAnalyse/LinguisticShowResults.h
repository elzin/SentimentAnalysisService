#pragma once

#include "../ASCInterface/ILinguisticProcessor.h"

#include "../ASSInterface/ILexicaLib.h"
#include "./ResultsEx.h"

#include "..\ASSInterface\IDictionaryManager.h"
using namespace SS::Interface::Core::Dictionary;

#include "..\ASSInterface\TDictionaryManager.h"
using namespace SS::Dictionary::Types;

#include "..\ASSInterface\IMainAnalyse.h"
using namespace SS::Interface::Core::MainAnalyse;

#include "..\ASSInterface\TMainAnalyseTypes.h"
using namespace SS::Core::Types;


namespace SS
{
namespace LinguisticProcessor
{
	class CLinguisticShowResults 
		: public SS::Interface::Core::ILinguisticShowResults
		, public SS::Core::CommonServices::CBaseCoreClass
		, public SS::Interface::Core::Common::CAnalyseParams
	{
		SS::Interface::Core::ILexicaPrimary*						m_pLexicaPrimary;
		IMorphologyAnalyser*												m_pMorphoAnalyzer;
		//IAnalyseParams*														m_pAnalyseParams;

		CResultsEx m_ResultsEx;

		SS::Core::Types::IndexationSearch::TLinguisticProcessorMode m_oMode;

	public:
		CLinguisticShowResults(void);
		~CLinguisticShowResults(void);
	public:
		void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
	public:
		SS::Interface::Core::ILexicaPrimary* GetLexicaPrimary();

		/// ��������� ������� ����� � �������
		/** 
			\param psWord - ��������� �� �����
			\return unsigned int ������ 0, ���� ����� ��� � ���� � 1 ���� ����
		*/
		unsigned int  IsExistWord(const wchar_t* psWord);

		/// ������ ������� ������������, ���� ��������� ������ �������� ������� ���� ��� ���������� ��������� ��������� ����
		void PrepareForView(
			/// ��������� � ������������ ������
			SS::Interface::Core::CommonContainers::ISearchResult* pSearchResult
			/// ��������� ���������� � ������ (���-�� ���������������� ����������� � �.�.)
			, SS::Core::Types::IndexationSearch::TPrepareForViewParams* pPrepareForViewParams
			);

		virtual void GetSourceIndices(const wchar_t* wszWord, std::vector<unsigned int>* pvIndices);

	public:
		void SetMode(SS::Core::Types::IndexationSearch::TLinguisticProcessorMode* pMode)
		{
			m_oMode = *pMode;
		}

	private:
		bool InitDictionary();
	};
}
}