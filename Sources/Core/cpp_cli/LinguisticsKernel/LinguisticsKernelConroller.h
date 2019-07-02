#pragma once

#include "TreeGenerator.h"
#include ".\treecomparator.h"
#include ".\IndexBaseInit.h"

#include "..\..\cpp\ASSInterface\IDictionaryManager.h"

SET_LOAD_MANAGER_DEFINE;

namespace LinguisticsKernel
{
	using namespace System;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Data;
	using namespace System::IO;
	using namespace System::Windows::Forms;
	using namespace System::Xml::Linq;


	///������ ����� ��������� ���������� ��������� ������� � ������������ ������ ��� �������
    public ref class LinguisticsKernelConroller
	{
        SS::Interface::Core::CommonServices::IWorkRegister* m_pIWorkRegister;

		/* ���������� ���������������� ���������� */
		SS::Interface::Core::ILinguisticProcessor*	m_pLinguisticProcessor;

		SS::Interface::Core::Dictionary::IDictionary* m_pDictionary;

		SS::LinguisticProcessor::CSearch^			 m_pSearch;
		SS::LinguisticProcessor::CIndexation^		 m_pIndexation;
		SS::LinguisticProcessor::CQuery*			 m_pQuery;

		SS::Interface::Core::ILinguisticIndexation*	 m_pLinguisticIndexation;
		SS::Interface::Core::ILinguisticQuery*		 m_pLinguisticQuery;
		SS::Interface::Core::ILinguisticSearch*		 m_pLinguisticSearch;
		SS::Interface::Core::ILinguisticShowResults* m_pLinguisticShowResults;

		/*	���������� �����������	*/
		SS::Interface::Core::AMConverter::IAMConverterSyntax* m_pAMConverterSyntax;
		SS::Interface::Core::AMConverter::IAMConverterMorpho* m_pAMConverterMorpho;

		SS::Core::Types::IndexationSearch::TQueryParams* m_pQueryParams;
		///��������� ��������
		CTreeGenerator^ m_pTreeGenerator;
		///������������ ��������
		CTreeComparator^ m_pTreeComparator;

		bool m_bIsInside;

		CIndexBaseInit* m_pIndexBaseInit;

		System::IO::StreamWriter^ logFile;

		SemanticResolution::CoreferenceResolution^    m_pCoreferenceResolution;
		SemanticResolution::SemanticNetwork^          m_pSemanticNetwork;
		SurfaceSyntaxAnalyzer::SurfaceSyntaxAnalyzer^ m_pSurfaceSyntaxAnalyzer;
		CoreferenceResolving::AbbreviationResolver^   m_pAbbreviationResolver;

		/// ���� ������������� ������� �����������
		bool _IsUseGeoNamesDict;

	public:		
		enum class ETreeType
		{
			ettText,	
			ettQuery,	
			ettQueryFinal,
			ettTextIndexation
		};
		ref struct SSearchMode
		{
			bool bAnswer;
			bool bSynonyms;
		};

		LinguisticsKernelConroller(bool useGeoNamesDictionary, int maxEntityLength);
		~LinguisticsKernelConroller(void);

		void Close();

		void DomainUnload(Object^ sender, EventArgs^ e);
		///����������� ����� � ������������ ������� ������������
		void GenerateTreeITextIndexation(String^ sText, TreeView^ pTree, bool bOutside, bool IsGlobal);
		///����������� ������ � ������������ ������� ������������
		void GenerateTreeITextQuery(String^ sQuery, TreeView^ pTree, SSearchMode^ pSearchMode, bool IsGlobal);
		///����������� ������, ��������� �� ��� ������ ������������� � ������������ ������� �������������
		void GenerateTreeIQueryQuery(String^ sQuery, TreeView^ pTree, SSearchMode^ pSeaearchMode, bool IsGlobal);
		///���������� ���������� �������� ���� ��������
		void CompareQueries(String^ sLeftQuery, ETreeType LeftQueryTreeType, SSearchMode^ pLeftSearchMode, String^ sRightQuery, ETreeType RightQueryTreeType, SSearchMode^ pRightSearchMode, TreeView^ pComparationTree, TreeView^ pCoincidenceTree, bool bIsGlobal);
		///������������ ����� �� ������� � ������
		void Search(String^ sQuery, String^ sText, String^ sTextTitle, 
			DataSet^% pResultDataSet, ArrayList^% pArrayList, bool bIsGlobalSearch);
		///������������ ������������ ���������� IShowResult
		void MakeShowResult(String^ sText, TreeView^ pTree);
		void SetParams(bool bIsMorpho, bool bIsSemantic, bool bIsSyntax, bool bIsSynonims, bool bIsInside);
		//���������. ������������ � �������� ��� ����������� �����������
		// ��������� ��������� � ������� XML. �� ���� - ����� (sText), ������ ��������� � ������ ����� \n (synonims), 
		// ���������������� (korefs), ������ �������� � ������, ������� ����� ��������� � �������� (offsets),
		// ��� ������� (sObjType)
		String^ GetXmlDigest(String^ sText, String^ synonims,
			String^ korefs, ArrayList^ offsets, String^ sObjType);
		//���������. ������������ � �������� ��� ����������� ����������� � ������ ���
		 String^ GetSentXMLDigest(String^ sText, ArrayList^ offsets,
			 ArrayList^ themeIDs, String^ dictName);
		//���������. ������������ � ���������� ���������� ����� ��� ��������������� ��������� �����������
		// ����������� ��������� ������� �� ����� ���� ������ ���� ��������.
		void ReinitToneDicts(String^ typeName);
		//���������. ������������ � ���������� ���������� ����� ��� ��������������� ��������� �����������
		// ���������� ������ ����� � �������. ������ ��� ������ ��������, ��� ������� (�������, ���������� � �.�.) � ����������� �����
		void AddWordToDict(String^ typeName, int dict_code, String^ word);
 		//���������. ������������ � ���������� ���������� ����� ��� ���������������� ��������� �����������
		// ���������� ������ ����� ��������
		void GenerateDictLing(String^ typeName);
		
		// ���������� XML �� ������� ��������� � ���������������� ��� ��������� �����.
        String^ GetAllWordFormsXML(String^ word);

		// ���������� ������ ��������� �����
		List<String^>^ GetAllWordForms(String^ word);

		/// ���������� ������ ��������� ����� � ��� ����� ����
		System::Tuple<List<String^>^,
			List<String^>^>^ GetAllWordFormsWithPartsOfSpeech(String^ word);

        // ���������� ���������� ����� �����
        String^ GetNormalWordForm(String^ word);

		// ���������� ��� ��������� ���������� �����
		List<String^>^ GetAllNormalWordForm(String^ word);
         
		/// ��������� RDF ���������
		/// afterSpellChecking - ���� ��������� � ���� XML ����� �������������
		/// baseDate - ������� ���� ��� ���������� ������������� ���
		/// dictGeoNames - ���� ������������� ����������� �������
		XElement^ GetRDF_New(String^ text, bool afterSpellChecking, System::DateTime baseDate, int selectEntitiesMode);
		Linguistics::Core::IText^ GetRDF_New(String^ text, System::DateTime baseDate);

		/// ��������� ������������� ����
		/// rdf - �������� � ���� RDF
		/// generateAllSubthemes - ���� ���������� � ������ ������������
		System::Tuple<System::Collections::Generic::IEnumerable<Lingvistics::Types::ThemeItem^>^,
			System::Collections::Generic::IEnumerable<Lingvistics::Types::LinkItem^>^>^
			GetSemanticNetwork(XElement^ rdf, Linguistics::Coreference::ICoreferenceInfo^ coreferenceInfo, bool generateAllSubthemes);

		/// ���������� RDF
		void FilterRDF(XElement^% rdf);

		/// �������� �������� �� ����
		bool IsTheme(XElement^ entity);

		System::Tuple<XElement^, XElement^>^ ProcessPTS
			(String^ xml, bool isFullRDF, String^ language);

	protected:
		void Init(bool useGeoNamesDictionary, int maxEntityLength);
		/// ��������� ���������� ������
		void FillDataSet(SS::Interface::Core::CommonContainers::ISearchResult* pSearchResult, DataSet^% pResultDataSet, ArrayList^% pArrayList);

        /// �������� ��������� ��������
        void LoadDictionaries();

		/// ��������� �������� �� ����������������� �����
		/*--- [DO NOT USE IT. THIS IS A VERY BAD IDEA]
		void SetConfigurationParams();
		---*/

        /// �������� ���������� �������
        void LoadDictionary(wstring path, vector<vector<wstring>> &dictionaryCollection);
		/// �������� ���� �������� ���������� ������� ����-��������������
		void LoadProfileAdjectives(wstring path);

		bool IsExistWord(String^ sText);
		///����������� �����
		SS::Interface::Core::BlackBox::IText* GenerateITextIndexation(String^ sText, bool bOutside, bool IsGlobal);
		///����������� ������
		SS::Interface::Core::BlackBox::IText* GenerateITextQuery(String^ sQuery, SSearchMode^ pSearchMode, bool IsGlobal);
		///����������� ������
		SS::Interface::Core::BlackBox::Query::IQuery* GenerateIQueryQuery(String^ sQuery, SSearchMode^ pSearchMode, bool IsGlobal);

    private:
		delegate void EntitiesSelector(Linguistics::Core::Content^ content, String^ baseDate);

		Linguistics::Core::IText^ SelectEntities(String^ sText, String^ baseDate);
		void SelectEntitiesOnContent(Linguistics::Core::Content^ content, String^ baseDate, EntitiesSelector^ selector);
		void AddEntityListToContent(Linguistics::Core::Content^ content, List<SimpleEntities::SimpleEntity^>^ entities);

		System::Tuple<String^, Linguistics::Core::IText^, List<PTS::TextRange^>^>^
			ProcessPTSText(String^ xml, bool isFullRDF, String^ language, PTS::SimpleXmlParser^ parser);
		
		// ������������ ��� ��������� ��������� �� ����������� ���������. �� ����� �����, �� ������
		// ���� XML, ���������� �������� ����� ������, ��� �������� ����������� � ��������
		XElement^ GetXmlEntities(String^ sText);

		// ���������� ��� �� ������
		String^ GetHash(String^ sEntText);

		// ���������� ���������� ����� ���� ���� �����������
        String^ GetTextAllNormalForms(String^ text);

		String^ TransliteringText(String^ srcText);

		String^ GetMorphoXML(String^ word);

		List<String^>^ GetTokens(String^ srcText);
		String^ GetMorphoInfo(String^ word);
	};
}