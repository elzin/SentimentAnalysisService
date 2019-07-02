#pragma once

#include "..\\libs\\Serialization.hpp"
#include "IXML.h"
#include <list>

namespace SS
{
namespace Statistics
{
namespace Types
{
	using SS::Lib::SetSerializeXMLString;
   using SS::Lib::CWriteArchive;


   //�������� �� ������ Object � ������� ��������� ����� Serialize XML ������ OutXML � 
   //��������� ��������� ���� RootName
   //���������� �� SS::Lib::SetSerializeXMLString ��� ��� ���������� 
   //�������� 3 ����� ����� �������
   template< class Object, class CharT >
   void GetSerializeXMLString( Object &Object, const CharT *RootName, std::basic_string<CharT> &OutXML )
   {
      std::basic_stringstream<CharT> Stream;
      CWriteArchive<CharT> Archive(Stream);
      Stream.precision(3);
      Stream.flags( std::ios::fixed );
      Archive.Save( RootName, Object );
      OutXML = Stream.str();
   }

	
	/// ����� (������������ ��� ������ ������ �������, ����� ������ ������� ����������� ��� ������ ����������)
	class TNativeSymbols
	{
		const wchar_t* m_wcSymbols;
	public:
		TNativeSymbols() : m_wcSymbols(0)	{};
		/// ������ �����
		const wchar_t* GetSymbols()
		{
			return m_wcSymbols;
		}
		/// ������ �����
		void SetSymbols(const wchar_t* wc)
		{
			m_wcSymbols = wc;
		}
	};


	class TResultType
	{
		int		m_iGlobal;
		int		m_iUnique;
		int		m_iCombinations;
		double	m_dPersent;

	public:

		TResultType() : m_iGlobal(0), m_iUnique(0), m_iCombinations(0), m_dPersent(0.0) {}

		int    GetGlobalNumber() { return m_iGlobal; }
		void   SetGlobalNumber(int iGlobal) { m_iGlobal = iGlobal; }

		int    GetUniqueNumber() { return m_iUnique; }
		void   SetUniqueNumber(int iUnique) { m_iUnique = iUnique; }

		int    GetCombinationsNumber() { return m_iCombinations; }
		void   SetCombinationsNumber(int iCombinations) { m_iCombinations = iCombinations; }

		double GetResultsInPercent() { return m_dPersent; }
		void   SetResultsInPercent(double	dPersent) { m_dPersent = dPersent; }

		template< class Archive > void Serialize( Archive &A ) {
			A.Element( _T("Global"),       m_iGlobal );
			A.Element( _T("Unique"),       m_iUnique );
			A.Element( _T("Combinations"), m_iCombinations );
			A.Element( _T("Persent"),      m_dPersent );
		}
	};

	class TResultType_GP
	{
		int		m_iGlobal;
		double	m_dPersent;

	public:

		TResultType_GP() : m_iGlobal(0), m_dPersent(0.0) {}

		int    GetGlobalNumber() { return m_iGlobal; }
		void   SetGlobalNumber(int iGlobal) { m_iGlobal = iGlobal; }

		double GetResultsInPercent() { return m_dPersent; }
		void   SetResultsInPercent(double	dPersent) { m_dPersent = dPersent; }

		template< class Archive > void Serialize( Archive &A ) {
			A.Element( _T("Global"),       m_iGlobal );
			A.Element( _T("Persent"),      m_dPersent );
		}
	};

	/// ���������� � ���������
	struct TSymbolsSequenceInfo   
	{
		/// ���������
		std::wstring Sequence;

		/// �����������
		TResultType Values;

		void GetXML(std::wstring * pwXML) {       GetSerializeXMLString(*this, _T("SymbolsSequenceInfo"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("SymbolsSequenceInfo"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.Element( _T("Sequence"), Sequence );
			A.Group(   _T("Values"),     Values );
		}
	};

	/// ������ � ����������� � ���������
	struct SSymbolsSequenceInfoList   
	{
		std::list< TSymbolsSequenceInfo >           m_ListOfSymbolsSequenceInfo;		
		std::list< TSymbolsSequenceInfo >::iterator m_ListItr;

		void GetXML(std::wstring * pwXML) {       GetSerializeXMLString(*this, _T("SymbolsSequenceInfoList"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("SymbolsSequenceInfoList"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.STLContainerGroup( _T("SymbolsSequenceInfoList"), _T("Item"), m_ListOfSymbolsSequenceInfo );
		}
	};


	/// ���������� � ����� ����
	struct TPOSInfo   
	{
		/// �����
		std::wstring Word;

		/// ����� ����
		std::wstring POSName;

		/// �����������
		UINT         Number;

		void GetXML(std::wstring * pwXML) {       GetSerializeXMLString(*this, _T("POSInfo"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("POSInfo"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.Element( _T("Word"),    Word );
			A.Element( _T("POSName"), POSName );
			A.Element( _T("Number"),  Number );
		}
	};

	/// ������ � ����������� � ������ ����
	struct SPOSInfoList   
	{
		std::list< TPOSInfo >           m_ListOfPOSInfo;		
		std::list< TPOSInfo >::iterator m_ListItr;		

		void GetXML(std::wstring * pwXML) {       GetSerializeXMLString(*this, _T("POSInfoList"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("POSInfoList"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.STLContainerGroup( _T("POSInfo"), _T("Item"), m_ListOfPOSInfo );
		}
	};

	// ---------------------------------------------------------------------------------

	// NEW 20_04_06 (begin)
	/// ���������� ������� ���� � ������ � �� ������ ����
	struct TOrderInfo   
	{
		/// �����
		std::wstring Word;

		/// ����� ����
		std::wstring POSName;

		void GetXML(std::wstring * pwXML) {       GetSerializeXMLString(*this, _T("OrderInfo"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("OrderInfo"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.Element( _T("Word"),    Word );
			A.Element( _T("POSName"), POSName );
		}
	};

	/// ������ � ����������� � ������� ���� � ������ � �� ������ ����
	struct SOrderInfoList   
	{
		std::list< TOrderInfo >           m_ListOfOrderInfo;		
		std::list< TOrderInfo >::iterator m_ListItr;		

		void GetXML(std::wstring * pwXML) {       GetSerializeXMLString(*this, _T("OrderInfoList"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("OrderInfoList"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.STLContainerGroup( _T("OrderInfo"), _T("Item"), m_ListOfOrderInfo );
		}
	};
	// NEW 20_04_06 (end)



	/// ��������� ��������� ���������� � ����������� ������������ ������ ���� � ������
	class TPartOfSpeachParameters : public SS::Interface::Common::IXMLStorage
	{
		TResultType m_VerbsAll;
		TResultType m_VerbsActive;
		TResultType m_VerbsPassive;
		TResultType m_VerbsActiveIndef;
		TResultType m_VerbsTransitive;
		TResultType m_VerbsIntransitive;
		TResultType m_VerbsTransitIndef;
		TResultType m_VerbsPast;
		TResultType m_VerbsPresent;
		TResultType m_VerbsFuture;
		TResultType m_VerbsUndefTime;

		TResultType m_VerbsParticiple;
		TResultType m_VerbsDeepr;
		TResultType m_VerbsPersonal;
		TResultType m_VerbsInfinitive;
		TResultType m_VerbsImperative;

		TResultType m_NounsAll;
		TResultType m_NounsNominal;
		TResultType m_NounsProper;
		TResultType m_NounsAnimate;
		TResultType m_NounsInanimate;
		TResultType m_NounsUndefAnimate;

		TResultType m_Adjectives;
		TResultType m_Numerals;
		TResultType m_Numbers;
		TResultType m_Adverbs;
		TResultType m_Pronouns;
		TResultType m_Prepositions;
		TResultType m_Conjunctions;
		TResultType m_Particles;
		TResultType m_Interjections;
		TResultType m_Predicatives;
		TResultType m_Symbols;
		TResultType m_DifferentPartOfSpeaches;
//		TResultType m_ForeignWords;
		TResultType m_UnidentifiedWords;

	public:

		/// ����� ���� ��������                    
		TResultType* GetVerbsAll()      { return &m_VerbsAll; }

		/// ����� �������� ��������          
		TResultType* GetVerbsActive()   { return &m_VerbsActive; }

		/// ����� ��������� ��������          
		TResultType* GetVerbsPassive()  { return &m_VerbsPassive; }

		/// ����� �������� � �������������� �����������          
		TResultType* GetVerbsActiveIndef()   { return &m_VerbsActiveIndef; }

		/// ����� ���������� ��������          
		TResultType* GetVerbsTransitive()   { return &m_VerbsTransitive; }

		/// ����� ������������ ��������          
		TResultType* GetVerbsIntransitive()  { return &m_VerbsIntransitive; }

		/// ����� �������� � �������������� ������������� 
		TResultType* GetVerbsTransitIndef()   { return &m_VerbsTransitIndef; }

		/// ����� �������� ���������� �������
		TResultType* GetVerbsPast()  { return &m_VerbsPast; }

		/// ����� �������� ���������� �������
		TResultType* GetVerbsPresent()  { return &m_VerbsPresent; }

		/// ����� �������� �������� �������
		TResultType* GetVerbsFuture()  { return &m_VerbsFuture; }

		/// ����� �������� � �������������� ��������
		TResultType* GetVerbsUndefTime()  { return &m_VerbsUndefTime; }

		// NEW 3_04_06 (begin)

			// ����� �������� � ����� ���������
			TResultType* GetVerbsParticiple()  { return &m_VerbsParticiple; }

			// ����� �������� � ����� ������������
			TResultType* GetVerbsDeepr()  { return &m_VerbsDeepr; }

			// ����� �������� � ������ ����� 
			TResultType* GetVerbsPersonal()  { return &m_VerbsPersonal; }

			// ����� �������� � ����� ����������
			TResultType* GetVerbsInfinitive()  { return &m_VerbsInfinitive; }

			// ����� �������� � ������������� ����� 
			TResultType* GetVerbsImperative()  { return &m_VerbsImperative; }

		// NEW (end)

		/// ����� ���������������          
		TResultType* GetNounsAll()         { return &m_NounsAll; }

		/// ����� ������������� ���������������          
		TResultType* GetNounsNominal()   { return &m_NounsNominal; }

		/// ����� ����������� ���������������          
		TResultType* GetNounsProper()   { return &m_NounsProper; }

		/// ����� ������������ ���������������          
		TResultType* GetNounsAnimate()   { return &m_NounsAnimate; }

		/// ����� �������������� ���������������          
		TResultType* GetNounsInanimate()   { return &m_NounsInanimate; }

		/// ����� ��������������� ��� ��������������         
		TResultType* GetNounsUndefAnimate()   { return &m_NounsUndefAnimate; }

		/// ����� ��������������          
		TResultType* GetAdjectives()    { return &m_Adjectives; }

		/// ����� ������������          
		TResultType* GetNumerals()      { return &m_Numerals; }

		/// ����� �����          
		TResultType* GetNumbers()      { return &m_Numbers; }

		/// ����� �������               
		TResultType* GetAdverbs()       { return &m_Adverbs; }

		/// ����� �����������           
		TResultType* GetPronouns()      { return &m_Pronouns; }

		/// ����� ���������             
		TResultType* GetPrepositions()  { return &m_Prepositions; }

		/// ����� ������                
		TResultType* GetConjunctions()  { return &m_Conjunctions; }

		/// ����� ������                
		TResultType* GetParticles()     { return &m_Particles; }

		/// ����� ����������            
		TResultType* GetInterjections() { return &m_Interjections; }

		/// ����� ������������          
		TResultType* GetPredicatives()  { return &m_Predicatives; }

		/// ����� ��������        
		TResultType* GetSymbols()       { return &m_Symbols; }

		/// ����� ���� ����������� � ������ ������ ����
		TResultType* GetDifferentPartOfSpeaches()  { return &m_DifferentPartOfSpeaches; }

//		/// ����� ����������� ����
//		TResultType* GetForeignWords() { return &m_ForeignWords; }

		/// ����� ������������ ������ ����
		TResultType* GetUnidentifiedWords() { return &m_UnidentifiedWords; }

		//IXMLStorage
		void GetXML(std::wstring * pwXML) { GetSerializeXMLString(*this, _T("PartOfSpeachParameters"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("PartOfSpeachParameters"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.Group( _T("VerbsAll"),                m_VerbsAll );

			A.Group( _T("VerbsActive"),             m_VerbsActive );
			A.Group( _T("VerbsPassive"),            m_VerbsPassive );
			A.Group( _T("VerbsActiveInfef"),        m_VerbsActiveIndef );

			A.Group( _T("VerbsTransitive"),         m_VerbsTransitive );
			A.Group( _T("VerbsIntransitive"),       m_VerbsIntransitive );
			A.Group( _T("VerbsTransitIndef"),       m_VerbsTransitIndef );

			A.Group( _T("VerbsPast"),               m_VerbsPast );
			A.Group( _T("VerbsPresent"),            m_VerbsPresent );
			A.Group( _T("VerbsFuture"),             m_VerbsFuture );
			A.Group( _T("VerbsUndefTime"),          m_VerbsUndefTime );

			A.Group( _T("VerbsParticiple"),         m_VerbsParticiple );
			A.Group( _T("VerbsDeepr"),              m_VerbsDeepr );
			A.Group( _T("VerbsPersonal"),           m_VerbsPersonal );
			A.Group( _T("VerbsInfinitive"),         m_VerbsInfinitive );
			A.Group( _T("VerbsImperative"),         m_VerbsImperative );

			A.Group( _T("NounsAll"),                m_NounsAll );
			A.Group( _T("NounsNominal"),            m_NounsNominal );
			A.Group( _T("NounsProper"),             m_NounsProper );
			A.Group( _T("NounsAnimate"),            m_NounsAnimate );
			A.Group( _T("NounsInanimate"),          m_NounsInanimate );
			A.Group( _T("NounsUndefAnimate"),       m_NounsUndefAnimate );

			A.Group( _T("Adjectives"),              m_Adjectives );
			A.Group( _T("Numerals"),                m_Numerals );
			A.Group( _T("Numbers"),                 m_Numbers );
			A.Group( _T("Adverbs"),                 m_Adverbs );
			A.Group( _T("Pronouns"),                m_Pronouns );
			A.Group( _T("Prepositions"),            m_Prepositions );
			A.Group( _T("Conjunctions"),            m_Conjunctions );
			A.Group( _T("Particles"),               m_Particles );
			A.Group( _T("Interjections"),           m_Interjections );
			A.Group( _T("Predicatives"),            m_Predicatives );
			A.Group( _T("Symbols"),                 m_Symbols );
			A.Group( _T("DifferentPartOfSpeaches"), m_DifferentPartOfSpeaches );
//			A.Group( _T("Foreign"),                 m_ForeignWords );
			A.Group( _T("UnidentifiedWords"),       m_UnidentifiedWords );
			
		}

	};


	class TQuantitiveTextParameters : public SS::Interface::Common::IXMLStorage
	{
		TResultType m_ParagraphsCount;
		TResultType m_SentensesCount;
		TResultType m_WordsCount;
		TResultType m_WordsUnCommonCount;
		TResultType m_EndingsCount;
		TResultType m_LettersAllCount;
		TResultType m_LettersVowelsCount;
		TResultType m_LettersConsonantsCount;
//		TResultType m_LettersOther;
	public:

		/// ����� ����������                    
		TResultType* GetParagraphsCount()        { return &m_ParagraphsCount; }

		/// ����� ����������� 
		TResultType* GetSentensesCount()         { return &m_SentensesCount; }

		/// ����� ����                    
		TResultType* GetWordsCount()             { return &m_WordsCount; }

		/// ����� ����, ��������� �� ����� �������������������� �����������
		TResultType* GetWordsUnCommonCount()     { return &m_WordsUnCommonCount; }

		/// ����� ���������                    
		TResultType* GetEndingsCount()           { return &m_EndingsCount; }

		/// ����� ���� � ������ ����
		TResultType* GetLettersAllCount()        { return &m_LettersAllCount; }

		/// ����� ������� ����
		TResultType* GetLettersVowelsCount()     { return &m_LettersVowelsCount; }

		/// ����� ��������� ����
		TResultType* GetLettersConsonantsCount() { return &m_LettersConsonantsCount; }

		/// ����� ������ ���� ( �� ���� )
//		TResultType* GetLettersOtherCount()      { return &m_LettersOther; }

		/// ��������� �� ������ ��� 32-� ������� ����
		// TResultType* GetArrOf32RusLetters()   { return m_ArrOf32RusLetters; };

		/// ��������� �� ������ �������� ��� 32-� ������� ����
		// int * GetArrOf32RusIndexes()          { return m_ArrOf32RusIndexes; };


		//IXMLStorage
		void GetXML(std::wstring *pwXML) { GetSerializeXMLString(*this, _T("QuantitiveTextParameters"), *pwXML); }
		void SetXML(const std::wstring *pwXML) { SetSerializeXMLString(*this, _T("QuantitiveTextParameters"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.Group( _T("ParagraphsCount"),        m_ParagraphsCount );
			A.Group( _T("SentensesCount"),         m_SentensesCount );
			A.Group( _T("WordsCount"),             m_WordsCount );
			A.Group( _T("WordsUnCommonCount"),     m_WordsUnCommonCount );
			A.Group( _T("EndingsCount"),           m_EndingsCount );
			A.Group( _T("LettersAllCount"),        m_LettersAllCount );
			A.Group( _T("LettersVowelsCount"),     m_LettersVowelsCount );
			A.Group( _T("LettersConsonantsCount"), m_LettersConsonantsCount );
//			A.Group( _T("LettersOther"),           m_LettersOther );
		}
	};

	class TAverageLengthTextParameters : public SS::Interface::Common::IXMLStorage
	{
		double m_dParagraphLengthInSentences;
		double m_dSentenceLengthInWords;
		double m_dWordLengthInSyllables;
		double m_dWordLengthInSymbols;
		double m_dSyllableLengthInSymbols;
	public:
		/// ������� ����� ���������, ���������� � ������������
		double GetParagraphLengthInSentences(void) { return m_dParagraphLengthInSentences; }

		/// ������� ����� ���������, ���������� � ������������
		void SetParagraphLengthInSentences(double dParagraphLengthInSentences) { m_dParagraphLengthInSentences = dParagraphLengthInSentences; }

		/// ������� ����� �����������, ���������� � ������
		double GetSentenceLengthInWords(void) { return m_dSentenceLengthInWords; }

		/// ������� ����� �����������, ���������� � ������
		void SetSentenceLengthInWords(double dSentenceLengthInWords) { m_dSentenceLengthInWords = dSentenceLengthInWords; }

		/// ������� ����� �����, ���������� � ������
		double GetWordLengthInSyllables(void) { return m_dWordLengthInSyllables; }

		/// ������� ����� �����, ���������� � ������
		void SetWordLengthInSyllables(double dWordLengthInSyllables) { m_dWordLengthInSyllables = dWordLengthInSyllables; }

		/// ������� ����� �����, ���������� � ��������
		double GetWordLengthInSymbols(void) { return m_dWordLengthInSymbols; }

		/// ������� ����� �����, ���������� � ��������
		void SetWordLengthInSymbols(double dWordLengthInSymbols)  { m_dWordLengthInSymbols = dWordLengthInSymbols; }

		/// ������� ����� �����, ���������� � ��������
		double GetSyllableLengthInSymbols(void) { return m_dSyllableLengthInSymbols; }
		/// ������� ����� �����, ���������� � ��������

		void SetSyllableLengthInSymbols(double dSyllableLengthInSymbols) { m_dSyllableLengthInSymbols = dSyllableLengthInSymbols; }

		//IXMLStorage
		void GetXML(std::wstring * pwXML) { GetSerializeXMLString(*this, _T("AverageLengthTextParameters"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("AverageLengthTextParameters"), *pwXML); } 

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.Element( _T("ParagraphLengthInSentences"), m_dParagraphLengthInSentences );
			A.Element( _T("SentenceLengthInWords"), m_dSentenceLengthInWords );
			A.Element( _T("WordLengthInSyllables"), m_dWordLengthInSyllables );
			A.Element( _T("WordLengthInSymbols"), m_dWordLengthInSymbols );
			A.Element( _T("SyllableLengthInSymbols"), m_dSyllableLengthInSymbols );
		}
	};

	class TTextIndexes : public SS::Interface::Common::IXMLStorage
	{
		double m_dFleschKincaidGradeLevel;
		double m_dFleschReadingEase;
		double m_dFogIndex;
		double m_dErtelIndex;
		double m_dTreigerIndex;
		double m_dKODIndex;
		double m_dRhythmIndex;
		double m_dReflectiveIndex;

		// !!! Z-Indexes

//		double m_dZIndexSOS;
//		double m_dZIndexSs;
//		double m_dZIndexDe;
//		double m_dZIndexSi;
//		double m_dZIndexPr;
//		double m_dZIndexSu;
//		double m_dZIndexFl;
		double m_dZIndexGl;
		double m_dZIndexSu;
		double m_dZIndexAd;
		double m_dZIndexMe;
		double m_dZIndexAv;
		double m_dZIndexUIR;
		double m_dZIndexULM;
		double m_dZIndexNe;
		double m_dZIndexPr;
//		double m_dZIndexIR;
//		double m_dZIndexDF;
		double m_dZIndexLR;
		double m_dZIndexLT;

	public:

		/// ������ �����
		double GetFleschKincaidGradeLevel(void)   { return m_dFleschKincaidGradeLevel; }
		void   SetFleschKincaidGradeLevel(double dFleschKincaidGradeLevel)   { m_dFleschKincaidGradeLevel = dFleschKincaidGradeLevel; }

		/// ������ �����, ������������ �������� ������
		double GetFleschReadingEase(void)   { return m_dFleschReadingEase; }
		void   SetFleschReadingEase(double dFleschReadingEase)   { m_dFleschReadingEase = dFleschReadingEase; }

		/// ������ �����
		double GetFog(void)   { return m_dFogIndex; }
		void   SetFog(double dFogIndex)   { m_dFogIndex = dFogIndex; }

		/// ����������� �������� (��) - ��������� ���������� �������� � ���������� ��������������
		double GetTreigerIndex(void)   { return m_dTreigerIndex; }
		void   SetTreigerIndex(double dTreigerIndex)   { m_dTreigerIndex = dTreigerIndex; }

		/// ����������� ��������������� �������� (���) - ��������� ���������� �������� � ���������� ���������������
		double GetKODIndex(void)   { return m_dKODIndex; }
		void   SetKODIndex(double dKODIndex)   { m_dKODIndex = dKODIndex; }

		/// ��, ��� ������ ������������� ������, � ��������� ���������� ���� � ��������� �-���������� (� ������� ������� �������������) � ������ ���������� ���� � ������� ������.
		double GetErtelIndex(void)   { return m_dErtelIndex; }
		void   SetErtelIndex(double dErtelIndex)   { m_dErtelIndex = dErtelIndex;	}

		/// ����������� ����������� (��������� ����� ������ � ����� ����)
		double GetRhythmIndex(void)   { return m_dRhythmIndex; }
		void   SetRhythmIndex(double dRhythmIndex)   { m_dRhythmIndex = dRhythmIndex;	}

		/// ������ ��������������
		double GetReflectiveIndex(void)   { return m_dReflectiveIndex; }
		void   SetReflectiveIndex(double dReflectiveIndex)   { m_dReflectiveIndex = dReflectiveIndex; }


		// !!! Z-Indexes

		/// ���������� ������� ����� ��������� ����. ���������� ��� ��������� ���������� ������ � ���������� ���� � ������. �� ������� ���������� ������ ������������������ ���������� � ������ ������ �� ���� ����������, � �������������� �������������� � ���������������� ����. ���������� �������������� ���� ��������� � ������� ����� � ��� ���� ������� �� ���������� ������� ����, ��� ������ ���������������� ����. 
		//double GetZIndexSOS(void)   { return m_dZIndexSOS; }
		//void   SetZIndexSOS(double dZIndexSOS)   { m_dZIndexSOS = dZIndexSOS;	}

		/// ���������� �������������. ����������� ���������� ����� �������� ������ � ����� ������. ������ ������ ����� ���� ����������� ��� �������������� ����������� � ��������������� ������� ������.
		//double GetZIndexSs(void)   { return m_dZIndexSs; }
		//void   SetZIndexSs(double dZIndexSs)   { m_dZIndexSs = dZIndexSs;	}

		/// ���������� ���������. ������������ ���������� ����� �������������������� ������ � ����� ��������� � ������. � ���������� ������� � �������������� ������ ���� ������������� ������� ����������� � �������������� ���������, ��� � ���������� � ������ ����� ����.
		//double GetZIndexDe(void)   { return m_dZIndexDe; }
		//void   SetZIndexDe(double dZIndexDe)   { m_dZIndexDe = dZIndexDe;	}

		/// ������ ��������������. ���������� ��� ��������� ����� ������������������ ������ � ����� �����������������. ���������� �������� �� ������� ���������� ����������� ����� �������������� ���������� �������������� � ������ ���������� �����.
		//double GetZIndexSi(void)   { return m_dZIndexSi; }
		//void   SetZIndexSi(double dZIndexSi)   { m_dZIndexSi = dZIndexSi;	}

		/// ������  �����������. ����������� ��� ��������� ����� ��������� � ����� ��������� � ������ (������������� ��������� ������� ������������ ��������� �����). ���������� �������� ������� ������� ���������� ��� ���������� � �������������� ����, ���������� � ��� ������ � ���������������� ����.
		//double GetZIndexPr(void)   { return m_dZIndexPr; }
		//void   SetZIndexPr(double dZIndexPr)   { m_dZIndexPr = dZIndexPr;	}

		/// ������ �����������. ������������ ���������� ����� ��������� (�������������������� � ������������������) � ����� ��������� � ������. �� ������� ������� ��������� �����������  ���������� � �������������� ���� �� ������  ���������������� ����.
		//double GetZIndexSu(void)   { return m_dZIndexSu; }
		//void   SetZIndexSu(double dZIndexSu)   { m_dZIndexSu = dZIndexSu;	}

		/// ������ ������������. ���������� ���������� ����� ���������� ������ � ����� ��������� � ������. �� ������� ��������� ��������� ������������������ ������ ���������� � ������ ����, �������������� � ���������� ����.
		//double GetZIndexFl(void)   { return m_dZIndexFl; }
		//void   SetZIndexFl(double dZIndexFl)   { m_dZIndexFl = dZIndexFl;	}

		/// ������ ������������. ������������ ���������� ���� ���������� ���� (������������� �����, ���������, ���������, ��������� � ������������) � ������ ����� ���� ��������� � ������. �� ����� ��������� ������ ���������� ���� � ������� ����������� ��������� ���������� � �������������� ������ ����.
		double GetZIndexGl(void)   { return m_dZIndexGl; }
		void   SetZIndexGl(double dZIndexGl)   { m_dZIndexGl = dZIndexGl;	}

		/// ������ ���������������. ������������  ���������� ����� ����������� � ������ ���� ��������������� � ������ ����� ��������� � ������. ���������� � �������������� ������ ������ ����������� ���������� �� ����� ����  ��������������� �� ������ ���������������� �������.
		double GetZIndexSu(void)   { return m_dZIndexSu; }
		void   SetZIndexSu(double dZIndexSu)   { m_dZIndexSu = dZIndexSu;	}

		/// ������ �������������. ������������ ��� ��������� ����� ���� �������������� � ������ ����� ��������� � ������. ����� ������� �������� ���������� 0,08. �� ������� ��������� ���������� � �������������� ���� ����� ����������� ��������� ������ � ���������������� ����.
		double GetZIndexAd(void)   { return m_dZIndexAd; }
		void   SetZIndexAd(double dZIndexAd)   { m_dZIndexAd = dZIndexAd;	}

		/// ������ �������������� (������������). ����������� ��� ��������� ����� ������������ ���� (������������ ���������: ������, �������������� � ������������� �����������-���������������; ��������������, ������������, �������������� ������������ ��������������; ������, ����������, ������������ ������������ �������; ������������ ������������),  � ������ ����� ��������� � ������. ������ ������������� ���������������� ���� ����������� ��������� ���������� �������������� ������.
		double GetZIndexMe(void)   { return m_dZIndexMe; }
		void   SetZIndexMe(double dZIndexMe)   { m_dZIndexMe = dZIndexMe;	}

		/// ������ �����������������. ������������ ��� ��������� ������������ ���� � ������ ����� ��������� � ������. �������������� ������������ ����� �������� � ���������� ������� ����� �������� ��� ������, ������ �������� �������� ���������� ������������ � ��������� ��������. ������ ���������������� ������ ����� �������� ������������ ��������, ��� ���������� � �������������� ������.
		double GetZIndexAv(void)   { return m_dZIndexAv; }
		void   SetZIndexAv(double dZIndexAv)   { m_dZIndexAv = dZIndexAv;	}

		/// ������ ������������ ������������� (������������) ������ ����� ���������������� � ����������� ����������������. ������������ ��� ��������� ���������� ���� ������������� (������������) ������ � ������ ����� ���� �������� ���� ��������������� � ����������� ��������������� � ������. ���� �������� ��������� �������������� ���������� � ������ ����. ���� ������������� ������  ����� ���� �������� ���� � ������ ���������������� ���� ����������� ������, ��� � ����������. ��� ���� �������������� ���� � ��� ���� ����� �������� ��������� ������������ ������, ��� ����������, ���������� ���������� ���� �� ��������� � ������ �����.
		double GetZIndexUIR(void)   { return m_dZIndexUIR; }
		void   SetZIndexUIR(double dZIndexUIR)   { m_dZIndexUIR = dZIndexUIR;	}

		/// ������ ������������ ������ �����������. ������������ ��� ��������� ���������� ������ ����������� � ���������� ���� ������������ ��������� � ������. ������ ���� �� ������� ��������� ����� �������� ������� �������������, ��� ����������.
		double GetZIndexULM(void)   { return m_dZIndexULM; }
		void   SetZIndexULM(double dZIndexULM)   { m_dZIndexULM = dZIndexULM;	}

		/// ������ �������. ������������ ���������� ����� ��������� ������ � ����� ��������� � ����� ���� ��������� ������. ���������� �������� �� ������� ��������� �������� � ������� ����������-�������� ����� ����, �  ��������� � ������������� ���������� ����. 
		double GetZIndexNe(void)   { return m_dZIndexNe; }
		void   SetZIndexNe(double dZIndexNe)   { m_dZIndexNe = dZIndexNe;	}

		/// ������ ���������������. ������������ ���������� ����� �������������  ������ � ����� ������ � �����������. � ������ ���������������� ���� �������� ������� ��������� ���������, ���������� � ���������� ���� ����������-�������� �����.
		double GetZIndexPr(void)   { return m_dZIndexPr; }
		void   SetZIndexPr(double dZIndexPr)   { m_dZIndexPr = dZIndexPr;	}

		/// ������ ������������� ��������������. ������������ ���������� ����� ������� � ����� ����� ������ � �����������. ������������ �������� ����������� ��� �� ��������������� ������� ������ � ����� �������.
		//double GetZIndexIR(void)   { return m_dZIndexIR; }
		//void   SetZIndexIR(double dZIndexIR)   { m_dZIndexIR = dZIndexIR;	}

		/// ������ ����� �����. ������������ ���������� ����� ���� � ������ � ���������� ���������� � ��� ������� � ���������� �������������.  � ���������������� ������ ���� ����� � ������� ������, ��� � �������������� ���� ��������������� ���������.
		//double GetZIndexDF(void)   { return m_dZIndexDF; }
		//void   SetZIndexDF(double dZIndexDF)   { m_dZIndexDF = dZIndexDF;	}

		/// ������ ������������ ������������. ������������ ��� ��������� ����� ������ ������ � ������ � ����� ���� ���������. �������������� ������ ������� � ��������� ������ ����� ��������� ��-�� ���������������� ����������, ������������� ������ ������������ ����� � �������������� ����� ����.  �������� ������� �������� ������� ������� ����������� � �������������� � ���������� ����. � ���������� ���� ��������������� ��� �������������� � �������� ������� �������� �������, �������  ���������� � ����������� � �������������� ������������� ���������, ��� �������� � ����������� ��������� ������� ����������.  � �� �� ����� ���������� ���������, ��� ������������ ������� ���������� �������� �������� ����������� ��� �������� �� ������ ������ � �����������. � ����������� ������ ���������� ���������, � ����������� � �������� �������������. ������� ��� ������������� ������������ ��� ��������� ����������� ������� ������� �������� ������ �� ������ �����������������.
		double GetZIndexLR(void)   { return m_dZIndexLR; }
		void   SetZIndexLR(double dZIndexLR)   { m_dZIndexLR = dZIndexLR;	}

		/// ������ ����������� �������������. ������������ ������������� ��������� �������� �������������� ����. � ���������� ������ ���� �� ����� �������� ������ ������ �������� ������ ����� �������� ������ ���� �������� �����. ����������������  ������ � ���������� ������ ����������� ����� ���������� � ����������� ���������, ��� ��������������. � ����� ������ ���� � ������������� ����� ����� ����������, ��� ���������� ���� ��� �������������� ������ �������.
		double GetZIndexLT(void)   { return m_dZIndexLT; }
		void   SetZIndexLT(double dZIndexLT)   { m_dZIndexLT = dZIndexLT;	}


		//IXMLStorage
		void GetXML(std::wstring * pwXML) { GetSerializeXMLString(*this, _T("TextIndexes"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("TextIndexes"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.Element( _T("FleschKincaidGradeLevel"), m_dFleschKincaidGradeLevel );
			A.Element( _T("FleschReadingEase"),       m_dFleschReadingEase );
			A.Element( _T("FogIndex"),                m_dFogIndex );
			A.Element( _T("ErtelIndex"),              m_dErtelIndex );
			A.Element( _T("TreigerIndex"),            m_dTreigerIndex );
			A.Element( _T("KODIndex"),                m_dKODIndex );
			A.Element( _T("RhythmIndex"),             m_dRhythmIndex );
			A.Element( _T("ReflectiveIndex"),         m_dReflectiveIndex );

			// !!! Z-Indexes

//			A.Element( _T("ZIndexSOS"),               m_dZIndexSOS);
//			A.Element( _T("ZIndexSs"),                m_dZIndexSs);
//			A.Element( _T("ZIndexDe"),                m_dZIndexDe);
//			A.Element( _T("ZIndexSi"),                m_dZIndexSi);
//			A.Element( _T("ZIndexPr"),                m_dZIndexPr);
//			A.Element( _T("ZIndexSu"),                m_dZIndexSu);
//			A.Element( _T("ZIndexFl"),                m_dZIndexFl);
			A.Element( _T("ZIndexGl"),                m_dZIndexGl);
			A.Element( _T("ZIndexSu"),                m_dZIndexSu);
			A.Element( _T("ZIndexAd"),                m_dZIndexAd);
			A.Element( _T("ZIndexMe"),                m_dZIndexMe);
			A.Element( _T("ZIndexAv"),                m_dZIndexAv);
			A.Element( _T("ZIndexUIR"),               m_dZIndexUIR);
			A.Element( _T("ZIndexULM"),               m_dZIndexULM);
			A.Element( _T("ZIndexNe"),                m_dZIndexNe);
			A.Element( _T("ZIndexPr"),                m_dZIndexPr);
//			A.Element( _T("ZIndexIR"),                m_dZIndexIR);
//			A.Element( _T("ZIndexDF"),                m_dZIndexDF);
			A.Element( _T("ZIndexLR"),                m_dZIndexLR);
			A.Element( _T("ZIndexLT"),                m_dZIndexLT);

		}
	};

	class IStatisticsParameters : public SS::Interface::Common::IXMLStorage
	{

	private:

		TTextIndexes                  m_oTextIndexes;
		TAverageLengthTextParameters  m_oAverageLengthTextParameters;
		TPartOfSpeachParameters       m_oPartOfSpeachParameters;
		TQuantitiveTextParameters     m_oQuantitiveTextParameters;

		SSymbolsSequenceInfoList      m_oUnCommonWords;         // ����� ��������� �� ����� ����������. �����������

		//SSymbolsSequenceInfoList      m_oBigrammsByAlphabet;    // �������� �� ��������
		//SSymbolsSequenceInfoList      m_oTrigrammsByAlphabet;   // ��������� �� �������� 
		//SSymbolsSequenceInfoList      m_oBigrammsByQuantity;    // �������� �� ���-��
		//SSymbolsSequenceInfoList      m_oTrigrammsByQuantity;   // ��������� �� ���-��
		//SSymbolsSequenceInfoList      m_oLettersAlphabet;       // ����� �� ��������
		//SSymbolsSequenceInfoList      m_oLettersOrdered;        // ����� �� �������������

		SSymbolsSequenceInfoList      m_oBigramms;              // �������� �� ��������
		SSymbolsSequenceInfoList      m_oTrigramms;             // ��������� �� �������� 
		SSymbolsSequenceInfoList      m_oLetters;               // ����� �� ��������

		SSymbolsSequenceInfoList      m_oSymbolList;            // nSymbol - ����� �������� ( ! " , . - )
		SPOSInfoList                  m_oPOSInfoList;           // ���������� � ������ ����
		SOrderInfoList                m_oOrderInfoList;         // ���������� � ������� ���� � ������ � �� ������ ����

	public:

		TTextIndexes                 * GetTextIndexes()                   { return &m_oTextIndexes; }
		TAverageLengthTextParameters * GetAverageLengthTextParameters()   { return &m_oAverageLengthTextParameters; }
		TPartOfSpeachParameters      * GetPartOfSpeachParameters()        { return &m_oPartOfSpeachParameters; }
		TQuantitiveTextParameters    * GetQuantitiveTextParameters()      { return &m_oQuantitiveTextParameters; }

		SSymbolsSequenceInfoList     * GetUnCommonWords()                 { return &m_oUnCommonWords; }

		//SSymbolsSequenceInfoList     * GetBigrammsByAlphabet()            { return &m_oBigrammsByAlphabet; }
		//SSymbolsSequenceInfoList     * GetTrigrammsByAlphabet()           { return &m_oTrigrammsByAlphabet; }
		//SSymbolsSequenceInfoList     * GetBigrammsByQuantity()            { return &m_oBigrammsByQuantity; }
		//SSymbolsSequenceInfoList     * GetTrigrammsByQuantity()           { return &m_oTrigrammsByQuantity; }
		//SSymbolsSequenceInfoList     * GetLettersAlphabet()               { return &m_oLettersAlphabet; }
		//SSymbolsSequenceInfoList     * GetLettersOrdered()                { return &m_oLettersOrdered; }

		SSymbolsSequenceInfoList     * GetBigramms()                      { return &m_oBigramms; }
		SSymbolsSequenceInfoList     * GetTrigramms()                     { return &m_oTrigramms; }
		SSymbolsSequenceInfoList     * GetLetters()                       { return &m_oLetters; }

		SSymbolsSequenceInfoList     * GetSymbolList()                    { return &m_oSymbolList; }
		SPOSInfoList                 * GetPOSInfoList()                   { return &m_oPOSInfoList; }

		// NEW 20_04_06 
		SOrderInfoList               * GetOrderInfoList()                 { return &m_oOrderInfoList; }

		//IXMLStorage
		void GetXML(std::wstring * pwXML) { GetSerializeXMLString(*this, _T("StatisticsParameters"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("StatisticsParameters"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A )    {
			A.Group( _T("TextIndexes"),                 m_oTextIndexes );
			A.Group( _T("AverageLengthTextParameters"), m_oAverageLengthTextParameters );
			A.Group( _T("PartOfSpeachParameters"),      m_oPartOfSpeachParameters );
			A.Group( _T("QuantitiveTextParameters"),    m_oQuantitiveTextParameters );

			A.Group( _T("UnCommonWords"),               m_oUnCommonWords );

			//A.Group( _T("BigrammsByAlphabet"),          m_oBigrammsByAlphabet ); 
			//A.Group( _T("TrigrammsByAlphabet"),         m_oTrigrammsByAlphabet );
			//A.Group( _T("BigrammsByQuantity"),          m_oBigrammsByQuantity ); 
			//A.Group( _T("TrigrammsByQuantity"),         m_oTrigrammsByQuantity );
			//A.Group( _T("LettersAlphabet"),             m_oLettersAlphabet );
			//A.Group( _T("LettersOrdered"),              m_oLettersOrdered );

			A.Group( _T("Bigramms"),                    m_oBigramms ); 
			A.Group( _T("Trigramms"),                   m_oTrigramms );
			A.Group( _T("Letters"),                     m_oLetters );

			A.Group( _T("SymbolList"),                  m_oSymbolList );
			A.Group( _T("POSInfoList"),                 m_oPOSInfoList );
			A.Group( _T("OredrInfoList"),               m_oOrderInfoList );
	  }
	};

// ------------------------------------------------------------------

	/// ���������� � ������� ������������� ����
	struct TWordFrequencyInfo   
	{
		/// �����
		std::wstring    sWord;

		/// ��� ����� ����. ��. ���� <IStatisticsCollector.h>
		UINT            iPOS;

		/// �����������
		TResultType_GP  oValues;

		void GetXML(std::wstring * pwXML) {       GetSerializeXMLString(*this, _T("WordFrequencyInfo"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("WordFrequencyInfo"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.Element( _T("Word"),   sWord );
			A.Element( _T("POS"),    iPOS );
			A.Group(   _T("Values"), oValues );
		}
	};

	/// ������ � ����������� � ������� ������������� ����
	struct SWordFrequencyInfoList   
	{
		std::list< TWordFrequencyInfo >           m_WordFrequencyInfoList;		
		std::list< TWordFrequencyInfo >::iterator m_ListItr;

		void GetXML(std::wstring * pwXML) {       GetSerializeXMLString(*this, _T("WordFrequencyInfoList"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("WordFrequencyInfoList"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.STLContainerGroup( _T("WordFrequencyInfoList"), _T("Item"), m_WordFrequencyInfoList );
		}
	};

	/// ����� � ����������� � ������� ������������� ����
	class IWordFrequencyParameters : public SS::Interface::Common::IXMLStorage
	{

	private:

		SWordFrequencyInfoList m_oWordFrequencyInfoList;  // ������ � ����������� � ������� ������������� ����
		UINT                   m_iGlobalNumberOfWords;    // ����� ����� ����

	public:

		SWordFrequencyInfoList * GetWordFrequencyInfoList(VOID)       { return &m_oWordFrequencyInfoList; }
		UINT                     GetGlobalNumberOfWords(VOID)   { return(m_iGlobalNumberOfWords); }
		VOID                     SetGlobalNumberOfWords(UINT iNum)   { m_iGlobalNumberOfWords = iNum; }


		//IXMLStorage
		void GetXML(std::wstring * pwXML) { GetSerializeXMLString(      *this, _T("WordFrequencyParameters"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("WordFrequencyParameters"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A )    {
			A.Group(   _T("WordFrequencyInfoList"),                 m_oWordFrequencyInfoList );
			A.Element( _T("GlobalNumberOfWords"),                   m_iGlobalNumberOfWords );
	  }
	};


// ------------------------------------------------------------------

	/// ���������� � ��������� �����
	struct TSemanticsInfo   
	{
		/// �����
		std::wstring    sWord;

		/// ������������� �����
		UINT32          iSemClass;

		/// �����������
		TResultType_GP  oValues;

		void GetXML(std::wstring * pwXML) {       GetSerializeXMLString(*this, _T("SemanticsInfo"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("SemanticsInfo"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.Element( _T("Word"),     sWord );
			A.Element( _T("SemClass"), iSemClass );
			A.Group(   _T("Values"),   oValues );
		}
	};

	/// ������ � ����������� � ������� ������������� ����
	struct SSemanticsInfoList   
	{
		std::list< TSemanticsInfo >           m_SemanticsInfoList;		
		std::list< TSemanticsInfo >::iterator m_ListItr;

		void GetXML(std::wstring * pwXML) {       GetSerializeXMLString(*this, _T("SemanticsInfoList"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("SemanticsInfoList"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A ) 
		{
			A.STLContainerGroup( _T("SemanticsInfoList"), _T("Item"), m_SemanticsInfoList );
		}
	};

	/// ����� � ����������� � ������� ������������� ����
	class ISemanticsParameters : public SS::Interface::Common::IXMLStorage
	{

	private:

		SSemanticsInfoList m_oSemanticsInfoList;  // ������ � ����������� � ������� ������������� ����
		UINT               m_iGlobalNumberOfWords;    // ����� ����� ����

	public:

		SSemanticsInfoList * GetSemanticsStatisticsInfoList(VOID)       { return &m_oSemanticsInfoList; }
		UINT                 GetGlobalNumberOfWords(VOID)   { return(m_iGlobalNumberOfWords); }
		VOID                 SetGlobalNumberOfWords(UINT iNum)   { m_iGlobalNumberOfWords = iNum; }


		//IXMLStorage
		void GetXML(std::wstring * pwXML) { GetSerializeXMLString(      *this, _T("SemanticsParameters"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("SemanticsParameters"), *pwXML); }

		template< class Archive >
		void Serialize( Archive &A )    {
			A.Group(   _T("SemanticsInfoList"),   m_oSemanticsInfoList );
			A.Element( _T("GlobalNumberOfWords"), m_iGlobalNumberOfWords );
	  }
	};


	// -------------------------------------------------------


	/// 
	struct SMarkerInfo
	{
		std::wstring    sMarkerName;
		UINT            iMarkerCnt;
		DOUBLE          iMarkerFreq;

		void GetXML(std::wstring * pwXML) {       GetSerializeXMLString( *this, _T("MarkerInfo"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString( *this, _T("MarkerInfo"), *pwXML); }

		template< class Archive > void Serialize( Archive &A ) {
			A.Element( _T("MarkerName"), sMarkerName );
			A.Element( _T("MarkerCnt"),  iMarkerCnt );
			A.Element( _T("MarkerFreq"), iMarkerFreq );
		}
	};

	/// ��������� ���. ������ � ���������
	struct TSemClassSubTree   
	{

		std::wstring                              m_ClassName;        // 
		UINT                                      m_Index;            // IDSource ������ ( ������ - � ������� �������)
		std::wstring                              m_ClassShortName;   //
		UINT                                      m_MarkersInBaseNum; //
		UINT                                      m_MarkersNum;       //
		UINT                                      m_MarkersNumGlobal;
		UINT                                      m_MarkersRecurNum;
		UINT                                      m_MarkersRecurNumGlobal;
		DOUBLE                                    m_MarkersFreqGlobal; 
		std::list  <SMarkerInfo>                  m_MarkersList;
//		std::list  <SMarkerInfo>::iterator        m_MarkersListItr;
		UINT                                      m_SubClassesNum;
		std::list< TSemClassSubTree >             m_SubClassesTree;		
//		std::list< TSemClassSubTree >::iterator   m_SubClassesTreeItr;

		void GetXML(std::wstring * pwXML)       { GetSerializeXMLString(*this, _T("SemClassSubTree"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString(*this, _T("SemClassSubTree"), *pwXML); }

		template< class Archive > void Serialize( Archive &A )   {
			A.Element(           _T("ClassName"),                  m_ClassName );             // ��� ������
			A.Element(           _T("Index"),                      m_Index );                 // IDSource ������ ( ������ - � ������� �������)
			A.Element(           _T("ClassShortName"),             m_ClassShortName );        // �������� ��� ������
			A.Element(           _T("SubClassesNum"),              m_SubClassesNum );         // ����� ���������� 
			A.STLContainerGroup( _T("SubClassesTree"), _T("Item"), m_SubClassesTree );        // STLContainerGroup
			A.Element(           _T("MarkersInBaseNum"),           m_MarkersInBaseNum );      // ����� ����� �������� ������� ������ � ����
			A.Element(           _T("MarkersNum"),                 m_MarkersNum );            // ����� ���������� �������� ������� ������ � ������ ()
			A.Element(           _T("MarkersNumGlobal"),           m_MarkersNumGlobal );      // ����� ����       �������� ������� ������ � ������
//			A.Element(           _T("MarkersRecurNum"),            m_MarkersRecurNum );       // ����� ���������� �������� ������� ������ � ����������� � ������
//			A.Element(           _T("MarkersRecurNumGlobal"),      m_MarkersRecurNumGlobal ); // ����� ����       �������� ������� ������ � ����������� � ������
			A.Element(           _T("MarkersFreqGlobal"),          m_MarkersFreqGlobal );     // ��������� ����� ���� �������� ������� ������ � ������ � ����� ������ (��� <MarkerFreq> � <struct SMarkerInfo>, ������ ��� ���� �������������) 
			A.STLContainerGroup( _T("MarkersList"),    _T("Item"), m_MarkersList );           // STLContainerGroup
		}
	};

	/// �������� ����� ������ ���. ����� � ���������
	class ISemClassSubTreeWithMarkers : public SS::Interface::Common::IXMLStorage
	{

	private:

		TSemClassSubTree m_RootSemClass;

	public:

		TSemClassSubTree * GetSemClassSubTreeWithMarkers(VOID)       { return &m_RootSemClass; }

		//IXMLStorage
		void GetXML(std::wstring * pwXML)       { GetSerializeXMLString( *this, _T("SemClassSubTreeWithMarkers"), *pwXML); }
		void SetXML(const std::wstring * pwXML) { SetSerializeXMLString( *this, _T("SemClassSubTreeWithMarkers"), *pwXML); }

		template< class Archive > void Serialize( Archive &A )   {
			A.Group( _T("RootSemClass"), m_RootSemClass );
	  }
	};

}
}
}