#pragma once

#include "../ASCInterface/IInterface.h"
#include "./ICommon.h"
#include "./TDictionaryManager.h"


// {05e6e5e0-6b5e-4b2e-955c-51de5af6a45a} 
static const GUID CLSID_IDictionary = 
{ 0x05e6e5e0, 0x6b5e, 0x4b2e, { 0x95, 0x5c, 0x51, 0xde, 0x5a, 0xf6, 0xa4, 0x5a } };

// {d9a37c0a-aabd-47c9-9e90-1b136fd40439} 
static const GUID IID_IDictionary = 
{ 0xd9a37c0a, 0xaabd, 0x47c9, { 0x9e, 0x90, 0x1b, 0x13, 0x6f, 0xd4, 0x04, 0x39 } };

// {34D63D88-DDF4-4e1d-B84C-E01FE12EB1F4}
static const GUID CLSID_IMinimalHypothesisTreeBuilder = 
{ 0x34d63d88, 0xddf4, 0x4e1d, { 0xb8, 0x4c, 0xe0, 0x1f, 0xe1, 0x2e, 0xb1, 0xf4 } };

// {B12A11BB-20B5-4e9f-8E8E-97E34D1336EC}
static const GUID IID_IMinimalHypothesisTreeBuilder = 
{ 0xb12a11bb, 0x20b5, 0x4e9f, { 0x8e, 0x8e, 0x97, 0xe3, 0x4d, 0x13, 0x36, 0xec } };


namespace SS
{
namespace Interface
{
namespace Core
{
namespace Dictionary
{

//��������� �� ������������ ������ ������� ������� ������ �� �������� ����� ����������
//��������������� ��� ����, ������������� � �������. 
//��������� ������ � ������� DBMS::IDataTable 
class IMinimalHypothesisTreeBuilder: public virtual SS::Interface::IBase
{
public:
   /// ����������
	virtual ~IMinimalHypothesisTreeBuilder() {};
	
	/// ������������� (������) ������. ������� ��� �������������� ����������� ����� � ���������������.
	virtual bool Init( SS::Dictionary::Types::TDictNumber DictNumber ) = 0;

	/// ���������� � ������ ����� � ������� ��������������� (������ IDType).
	//���������� ������� ��� ������� ����������� ����� ������� � ��������������� �� ����.
	//    pwReverseWord - ����������� �����. ������������ � ��������������� ���� (������ "����" ���������� �������� "����")
	//    pTypesList - ����� IDType ������� ����� ���� �������� �� ����� Str
	//    ���������: ������� �� �������� ����� (���� ����� ����� ��� ���� � ������ ��� ���� ��� IDType 
   //               � pTypesList �� �������� �������������, ���������� �� ����������)
	virtual bool AddReverseWord( const std::wstring* pwReverseWord, const SS::Dictionary::Types::TTypesList* pTypesList ) = 0;

	/// ���������� ������ � ���������� ��� � ������� 
	virtual void Build() = 0;
};
/// ��������� ������ � ������ ����������������

/// ��������� ������ � ����������� ����� ����������������
class IMorphoTypesCollection
{
public:
	virtual ~IMorphoTypesCollection(){};

	virtual void SetDictionaryNumber(SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber eDictionariesNumber) = 0;
						  
	/// ������� ��� ����������������
	virtual void DeleteType( const SS::Dictionary::Types::TIDType &IDType ) = 0;

	/// ���������� ������ ���������  ���� ����������������
	virtual void GetElements(
		const SS::Dictionary::Types::TIDType &IDType,
		std::list<SS::Dictionary::Types::SMorphoType>* p_l_MorphoTypes
	) = 0;
	
	/// ��������� ������ ��������� 
	/// ����������:
	///		S_OK - �������� ���������� ���� �������. 
	///     E_INVALIDARG - ��������� ������ �������� �� �������
	virtual HRESULT AddElements(std::list<SS::Dictionary::Types::SMorphoType>* p_l_MorphoTypes) = 0;

   ///������ ����� ��� ��� ������ ���������
   /// ����������:
   ///	  S_OK - �������� ���������� ���� �������. 
   ///     E_INVALIDARG - ��������� ������ �������� �� �������
   virtual HRESULT CreateCollection(std::list<SS::Dictionary::Types::SMorphoType>* p_l_MorphoTypes) = 0;

	
	/// ������� ������ ���������
	/// ����������:
	///		S_OK - �������� �������� ���� �������. 
	///     E_INVALIDARG - ��������� ������ ������� �� �������
	virtual HRESULT DeleteElements(std::list<SS::Dictionary::Types::SMorphoType>* p_l_MorphoTypes) = 0;
};


/// ��������� ������ � ������������� �������
class IOneRoot 
{
public:
	virtual ~IOneRoot(){};
public:
	/// ������������� ������ �����
	virtual unsigned int SetDictionaryIndex(SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex) = 0;
	/// ���������� ������ ������������ ���� ��� �������� ������� ������
	virtual void Get(std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_IDSource) = 0;
	/// ��������� ������������ ����� � ��������
	virtual void Add(std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_IDSource) = 0;
	/// ������� ������������ ����� � �������� �����
	virtual void Delete(std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_IDSource) = 0;
};

/// ��������� ������ � �������� ����
class ISource
{
public:
	virtual ~ISource(){};
public:
	/// ������������� ������ �����
	/// ���������� 0 - ����� ������������ ������ � 1 ����� ����������
	virtual unsigned int SetDictionaryIndex(SS::Dictionary::Types::TDictionaryIndex oDictionaryIndex) = 0;
	/// ���������� ��� ��������� ���������� �� ������
	virtual unsigned int Get(SS::Dictionary::Types::SSource* pSource) = 0;
	/// �������� ��� ��������� ���������� ��� ������
	virtual void Add(SS::Dictionary::Types::SSource* pSource) = 0;
	/// ������� ��� ���������� �� ������
	virtual void Delete() = 0;
};

/// ����������� ��������� ������ � �������� ����

class ISourceEx: public ISource
{
public:
   virtual ~ISourceEx(){};

   /// �������� ���������� �� ������� IDSource
   virtual void Update(SS::Dictionary::Types::SSource* pSource) = 0;
};


class IMorphologyAnalyser : 
    public virtual SS::Interface::Core::Common::CAnalyseParams
{
public:
	virtual ~IMorphologyAnalyser(){};
public:
	/// �������� ������� ����� � �������
   virtual bool IsExistWord(/*in*/const wchar_t* wcWord) = 0;


   ///// ����� ������ ��������������� ���������� �� ����� 
   ///// pUnit �������� �� ���� ���������,
   ///// ������ ���������������� ����������� ��������� ������� IUnit::AddIndex() IIndex::SetDictionaryIndex()
   ///// � ��������� IIndex::IFeature (����� AddFeature())
   ///// ���� ��������������� ������ ����� ��������� ��������� ������ IFeature (������ ���������� MorphoIndex() = IDForm,MorphoInfo(),PartOfSpeech())
   ///// �������� ����� ����������� ����� IBlackBoxTextStorage
   ///// ���� ����� ���������, �� � IUnit ���������� ������� ����� AddUnitVertical()AddUnitHorizontal()
   //virtual bool GetWordInfo/*ByWord*/(	
	  ///*in*/ const wchar_t* szWord,
   //   /*in out*/	SS::Interface::Core::BlackBox::IUnit * pUnit,
   //   /*in*/SS::Dictionary::Types::EFindZone eFindZone = SS::Dictionary::Types::efzFullAddNewWords
   //   ) = 0;


   /// ����� ������ ��������������� ���������� �� ����� 
	virtual bool GetWordInfo/*ByWord*/(
		/*in*/const wchar_t* wcWord, 
      /*out*/std::list<SS::Dictionary::Types::TWordInfo>* p_l_WordInfo, 
      /*in*/SS::Dictionary::Types::EFindZone eFindZone = SS::Dictionary::Types::efzFullAddNewWords
		) = 0;
	
   /// ����� ������ ��������������� ���������� �� ������� �����
	virtual bool GetWordInfo/*ByWordIndex*/(
		/*in*/SS::Dictionary::Types::SWordIndex* pWordIndex, 
		/*out*/SS::Dictionary::Types::SWordInfo* pWordInfo
   ) = 0;
	
   /// ����� ����� �� ��� ������� 
   virtual bool GetWord(
	   /*in*/SS::Dictionary::Types::SWordIndex* pWordIndex,
	   /*out*/wchar_t* wcWord
   ) = 0;
	
   /// ����� ������ ����� (����� ����� ��� ���������) �� ��� ������� 
   virtual bool GetWordSource(
      /*in*/const SS::Dictionary::Types::TDictionaryIndex &DictIndex,
      /*out*/wchar_t* wcWordSource
   ) = 0;

   /// ����� ��������� ����� �� ������� ������
    virtual bool GetWordFormsByIDSource(
	/*in*/SS::Dictionary::Types::TDictionaryIndex* pDictionaryIndex,
	/*out*/std::list<SS::Dictionary::Types::TWordInfo>* p_l_WordInfo) = 0;
	
   /// ���������� ��������������� ���������� �� ���� ����������������
	virtual void GetMorphoInfoByIDType(
	/*in*/SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber eDictionariesNumber,
	/*in*/SS::Dictionary::Types::TIDType oIDType, 
	/*in*/SS::Dictionary::Types::TIDForm oIDForm, 
	/*out*/SS::Dictionary::Types::TMorphoInfo* pMorphoInfo, 
	/*out*/SS::Dictionary::Types::TSpecialMorpho* pSpecialMorpho) = 0;
public:
	/// �������� ���������������� ������� � ���, ���������� ���������� � ������� ���������� ������
	virtual void NextText() = 0;
};

/// ��������� ������ �� �������� ���� ��������� ��������
class IWordsList
{
public:
	virtual ~IWordsList(){};
public:
	/// ���������� ����� �������, �� �������� ���������� �������� ������ ����
	virtual void SetDictionaryNumber(/*in*/SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber eDictionariesNumber) = 0;
	/// ������ ����������� ���� ������� ����
	virtual unsigned int GetCount() = 0;
	/// �������� � ������� ����� � ������ (� ������� ���������).
	virtual unsigned int MoveFirst() = 0;
	/// ������� � ���������� ����� � ������ (� ������� ���������).
	/// ���� ��������� ������� true ������������� ����� ����, ���� false �� ���� ������ ���
	virtual unsigned int MoveNext(/*out*/SS::Dictionary::Types::TWordInfo * pWordInfo) = 0;
	/// ������ ������� �����
	virtual void GetWord(/*out*/SS::Dictionary::Types::TWordInfo * pWordInfo) = 0;

};

/// ��������� ���������� ��������������� ��������
class IDictionary: 
	public virtual SS::Interface::IBase,
    public virtual SS::Interface::Core::Common::CAnalyseParams
{
public:
	virtual ~IDictionary(){};
public:
	/// ���������� ��������� ������ � ������������� �������
	virtual SS::Interface::Core::Common::ILoad* GetLoader() = 0;
	
   /// ���������� ��������� ������ � ������������� �������
	virtual IOneRoot* GetOneRoot() = 0;
	
   /// ���������� ��������� ������ � ������ ����������������
	virtual IMorphoTypesCollection* GetMorphoTypesCollection() = 0;
	
   /// ���������� ��������� ��������� � �������������� ���������� �� ������� ����
   /// � ������� �������� ��� ����������� � �������������
	virtual ISource* GetSource() = 0;
	
   /// ���������� ��������� ��������� � �������������� ���������� �� ������� ����
   /// �������� �����������.
   /// ����� ����� ��������� ��� ����� � ��� �� ��������������� ��� � ������� ������� 
   /// ��� � � ������� �����������, ������� ��� �������� ���������� ������������
   /// ��� ����������.
   virtual ISourceEx* GetAbbreviationSource() = 0;

   /// ���������� ��������� ���������������� �������
	virtual IMorphologyAnalyser* GetMorphologyAnalyser() = 0;
	
   /// ���������� ��������� ��� ��������� ������� ���� ������������� ����,
	/// ��� eDictionariesNumber - ����� �������, ��� �������� ���������� ������� ������ ����
	virtual IWordsList* GetWordList() = 0;
};

}
}
}
}