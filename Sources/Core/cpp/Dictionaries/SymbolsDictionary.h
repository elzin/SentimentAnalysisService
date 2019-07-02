#pragma once

namespace SS{ 
namespace Dictionary{
namespace Virtual{

/**
	������� ��������� ���������� "<BR>" � ��������� ������
*/
class CSymbolsDictionary: public Detail::IBasicMorphologyAnalyser  
{
	static const unsigned int ciBRIndex;
	static const wchar_t *const csBR;

private:
	//�������� ������� �� ����� � IAMConverterMorpho
	int m_MorphoInfo;
	int m_PartOfSpeech;


private:
	/// ��������� ��� ���� SWordInfo
	void FillSWordInfo( 
		const std::wstring &wcWord,
		unsigned int Number,
		SWordInfo &WordInfo,
      bool FirstLetterUpperCase
		) 
	{
		WordInfo.m_wWord = wcWord;
		WordInfo.m_WordIndex.m_DictIndex.SetId(Number) ; 
		WordInfo.m_WordIndex.m_DictIndex.SetDictionaryNumber(DATA_TYPE::NAMES::ednSymbols);
      WordInfo.m_WordIndex.m_DictIndex.SetFirstLetterUpperCase(FirstLetterUpperCase); 
		WordInfo.m_WordIndex.m_IDForm = 0; 
		WordInfo.m_MorphoTypeInfo.m_IDType = 0;
      
      if( Number >= _T('�') && Number <= _T('�') )
      {
         WordInfo.m_SpecialMorpho = WordInfo.m_MorphoTypeInfo.m_MorphoInfo = 0;
      }
      else
      {
         WordInfo.m_SpecialMorpho = m_PartOfSpeech;
		   WordInfo.m_MorphoTypeInfo.m_MorphoInfo = m_MorphoInfo;
      }
	}

	///��������� ����� ��������� �������������� ������� � �������, �.�. ��������� ������ � ������
	static bool GetWordByDictIndex(
		const TDictionaryIndex &Index,
		wchar_t* wcWord
	);										   

	//��������������� ���� �������� wcWord � ������
	static bool ConvertToSymbol( const wchar_t* wcWord, unsigned int &N );

public:
	CSymbolsDictionary(): m_MorphoInfo(0), m_PartOfSpeech(0) {}
	explicit CSymbolsDictionary( IAMConverterMorpho *pAMConverter ): m_MorphoInfo(0), m_PartOfSpeech(0) { Init(pAMConverter); }

	//������������� ����� ������
	void Init( IAMConverterMorpho *pAMConverter );
			  
	
	///////////////////////////////////////////////////////////////////////////////
	//IMorphologyAnalyser

	/// �������� ������� ����� � �������
	bool IsExistWord(/*in*/const wchar_t* wcWord);

   /// ����� ������ ��������������� ���������� �� ����� 
   bool GetWordInfo/*ByWord*/(
      /*in*/const wchar_t* wcWord, 
      /*in*/const wchar_t* wcWordOriginalCase,
      /*in*/bool IsFirstLetterUpperCase,
      /*out*/std::list<TWordInfo>* p_l_WordInfo
      );

	/// ����� ������ ��������������� ���������� �� ������� �����
	bool GetWordInfo/*ByWordIndex*/(
		/*in*/SWordIndex* pWordIndex, 
		/*out*/SWordInfo* pWordInfo
		);


	/// ����� ����� �� ��� ������� 
	/// wcWord - ������ � ����������� ��������� MAX_CHARS_IN_WORD
	bool GetWord(
		/*in*/SWordIndex* pWordIndex,
		/*out*/wchar_t* wcWord
		);

   /// ����� ������ ����� ����� (����� ����� ��� ���������) �� ��� ������� 
   /// wcWord - ������ � ����������� ��������� MAX_CHARS_IN_WORD
   bool GetWordSource(
      /*in*/const TDictionaryIndex &DictIndex,
      /*out*/wchar_t* wcWordSource
   );

	/// ����� ��������� ����� �� ������� ������
	bool GetWordFormsByIDSource(
		/*in*/TDictionaryIndex* pDictionaryIndex,
		/*out*/std::list<TWordInfo>* p_l_WordInfo
		);
};



} //namespace Virtual
} //namespace Dictionary
} //namespace SS
