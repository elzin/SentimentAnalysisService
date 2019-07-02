#pragma once
#include "../ASCInterface/IInterface.h"

#include "./TCoSeDiDataTypes.h"
#include "./TDictionaryNames.h"
#include "./TDictionaryManager.h"


// CoSeDi
/* DBMS */

// {27A3C5DE-5872-45fd-9BFE-26B49122E32C}
static const GUID IID_ICoSeDiManager = 
{ 0x27a3c5de, 0x5872, 0x45fd, { 0x9b, 0xfe, 0x26, 0xb4, 0x91, 0x22, 0xe3, 0x2c } };
// {80AF53BF-019F-48dd-9C97-5AEBD85F1661}
static const GUID CLSID_ICoSeDiManager = 
{ 0x80af53bf, 0x19f, 0x48dd, { 0x9c, 0x97, 0x5a, 0xeb, 0xd8, 0x5f, 0x16, 0x61 } };

// {0A7ADCF2-A19A-44bf-A54B-8D66860E881F}
static const GUID IID_ISemanticClassesTree = 
{ 0xa7adcf2, 0xa19a, 0x44bf, { 0xa5, 0x4b, 0x8d, 0x66, 0x86, 0xe, 0x88, 0x1f } };
// {C4DE2410-7F52-4443-92C2-72A0D7CBAD77}
static const GUID IID_ISemanticAnalysis = 
{ 0xc4de2410, 0x7f52, 0x4443, { 0x92, 0xc2, 0x72, 0xa0, 0xd7, 0xcb, 0xad, 0x77 } };
// {AA78F386-AEDA-48a7-8246-F3701C8EA62F}
static const GUID IID_ICombinatorySemanticAnalysis = 
{ 0xaa78f386, 0xaeda, 0x48a7, { 0x82, 0x46, 0xf3, 0x70, 0x1c, 0x8e, 0xa6, 0x2f } };
// {1B23EFC7-D28E-48aa-BC3B-531330B097BB}
static const GUID CLSID_ISemanticClassesTree = 
{ 0x1b23efc7, 0xd28e, 0x48aa, { 0xbc, 0x3b, 0x53, 0x13, 0x30, 0xb0, 0x97, 0xbb } };
// {C125C518-B6AC-4b1b-8E16-64C55857E11A}
static const GUID CLSID_ISemanticAnalysis = 
{ 0xc125c518, 0xb6ac, 0x4b1b, { 0x8e, 0x16, 0x64, 0xc5, 0x58, 0x57, 0xe1, 0x1a } };
// {29FEFEA0-EF33-4467-AA15-0501E2C361D6}
static const GUID CLSID_ICombinatorySemanticAnalysis = 
{ 0x29fefea0, 0xef33, 0x4467, { 0xaa, 0x15, 0x5, 0x1, 0xe2, 0xc3, 0x61, 0xd6 } };

/*	SQL	*/
// {ACF7D559-82F6-409f-9C20-DB75DDEAA52C}
static const GUID IID_ICoSeDiManagerSQL = 
{ 0xacf7d559, 0x82f6, 0x409f, { 0x9c, 0x20, 0xdb, 0x75, 0xdd, 0xea, 0xa5, 0x2c } };
// {7C0431F6-FC36-49d6-8CEE-644F55F2DD5B}
//static const GUID CLSID_ICoSeDiManagerSQL = 
//{ 0x7c0431f6, 0xfc36, 0x49d6, { 0x8c, 0xee, 0x64, 0x4f, 0x55, 0xf2, 0xdd, 0x5b } };


// {85DA106F-2F91-453f-9C50-A4AB4F342CBC}
static const GUID IID_ISemanticClassesTreeSQL = 
{ 0x85da106f, 0x2f91, 0x453f, { 0x9c, 0x50, 0xa4, 0xab, 0x4f, 0x34, 0x2c, 0xbc } };
// {91BA51C6-28B7-4679-AC05-66273F8CF9C5}
static const GUID CLSID_ISemanticClassesTreeSQL = 
{ 0x91ba51c6, 0x28b7, 0x4679, { 0xac, 0x5, 0x66, 0x27, 0x3f, 0x8c, 0xf9, 0xc5 } };
// {7B04BD34-8016-4a17-952E-6F16A25CC1E3}
static const GUID IID_ISemanticAnalysisSQL = 
{ 0x7b04bd34, 0x8016, 0x4a17, { 0x95, 0x2e, 0x6f, 0x16, 0xa2, 0x5c, 0xc1, 0xe3 } };
// {5E33B65E-6F2F-464f-8A59-7A320403CE84}
static const GUID CLSID_ISemanticAnalysisSQL = 
{ 0x5e33b65e, 0x6f2f, 0x464f, { 0x8a, 0x59, 0x7a, 0x32, 0x4, 0x3, 0xce, 0x84 } };
// {C0DEAA82-351A-41fd-BA6F-56BA43E6432C}
static const GUID IID_ICombinatorySemanticAnalysisSQL = 
{ 0xc0deaa82, 0x351a, 0x41fd, { 0xba, 0x6f, 0x56, 0xba, 0x43, 0xe6, 0x43, 0x2c } };
// {1720155E-0D91-40d6-BFC8-65877ED57B04}
static const GUID CLSID_ICombinatorySemanticAnalysisSQL = 
{ 0x1720155e, 0xd91, 0x40d6, { 0xbf, 0xc8, 0x65, 0x87, 0x7e, 0xd5, 0x7b, 0x4 } };


// {0A918E07-0476-4bd1-A1AD-CDDC1B4D9BAD}
static const GUID CLSID_ICombinatory = 
{ 0xa918e07, 0x476, 0x4bd1, { 0xa1, 0xad, 0xcd, 0xdc, 0x1b, 0x4d, 0x9b, 0xad } };
// {FCB347DF-FBF1-4a7b-A8A6-A6BCAB870F29}
static const GUID IID_ICombinatory = 
{ 0xfcb347df, 0xfbf1, 0x4a7b, { 0xa8, 0xa6, 0xa6, 0xbc, 0xab, 0x87, 0xf, 0x29 } };

// {5FCB4B61-0ECF-4c84-A411-061598CA56A0}
static const GUID CLSID_INumberCombinatory = 
{ 0x5fcb4b61, 0xecf, 0x4c84, { 0xa4, 0x11, 0x6, 0x15, 0x98, 0xca, 0x56, 0xa0 } };
// {8CDE5324-9A98-4195-B3EF-BB05ADFCEA68}
static const GUID IID_INumberCombinatory = 
{ 0x8cde5324, 0x9a98, 0x4195, { 0xb3, 0xef, 0xbb, 0x5, 0xad, 0xfc, 0xea, 0x68 } };



namespace SS
{
namespace Interface
{
namespace Core
{
namespace CoSeDi
{

#define TYPE_DictIndex  SS::Dictionary::Types::TDictionaryIndex
#define TYPE_DictNumber SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber

/**************************************************************************************************************/

#define DEFAULT_CLASS_COLOR 0x00000000

/// ��������� ������ � ������� ������������� �������
class ISemanticClassesTree   {

	public:

		virtual ~ISemanticClassesTree() {};

		/// ������� ������������� �����
		/** 
			\param  IN iParentClassId - ����� ������������� �������������� ������ ( -1 == �������� ���, ����� - ������� � �������� )
			\param  IN psClassName - ��� �������������� ������
			\return TYPE_DictIndex - ����� �������������� ������ ( 0 == o�����)
		*/
		virtual TYPE_DictIndex CreateClass(IN TYPE_DictIndex iParentClassId, IN std::wstring * psClassName, IN UINT32 iColor = DEFAULT_CLASS_COLOR, IN std::wstring * psShortName = NULL) = 0; 

		/// ������� ������������� �����
		/**
			\param  IN   iClassId    - ����� �������������� ������
			\return BOOL ( FALSE == o����� )
		*/
		virtual BOOL DeleteClass(IN TYPE_DictIndex iClassId) = 0;

		/// ������������� ������������� �����
		/**
			\param  IN   iClassId       - ����� �������������� ������
			\param  IN   psNewClassName - ����� ��� �������������� ������
			\return BOOL ( FALSE == o����� )
		*/
		virtual BOOL RenameClass(IN TYPE_DictIndex iClassId, IN std::wstring * psNewClassName, IN UINT32 iNewColor = DEFAULT_CLASS_COLOR, IN std::wstring * psNewShortName = NULL) = 0;


		///// �������� ����� �������������� ������ �� ��� ����� 
		///** 
		//	\param  IN psClassName - ��� �������������� ������
		//	\return ����� �������������� ������  ( -1 == ������ )
		//*/
		//virtual TYPE_DictIndex GetClassIdByName(IN std::wstring * psClassName, IN TYPE_DictNumber eDictNumber) = 0;

		/// �������� ����� �������������� ������ �� ��� ��������� ����� 
		/** 
			\param  IN psClassShortName - �������� ��� �������������� ������
			\return ����� �������������� ������  ( -1 == ������ )
		*/
		virtual TYPE_DictIndex GetClassIdByShortName(IN std::wstring * psClassShortName, IN TYPE_DictNumber eDictNumber) = 0;

		/// �������� ��� �������������� ������ �� ��� ������ 
		/**
			\param  IN   iClassId    - ����� �������������� ������
			\param  OUT  psClassName - ��� �������������� ������
			\return BOOL ( FALSE == o����� )
		*/
		virtual BOOL GetClassNameById(IN TYPE_DictIndex iClassId, OUT std::wstring * psClassName, OUT UINT32 * piColor = NULL, OUT std::wstring * psShortName = NULL) = 0;

		/// �������� ������ ID �������� ������������� �������
		/** 
			\param  IN  iParentClassId - ����� ������������� �������������� ������
			\param  OUT pChildrenList  - ������ ����� �������� ������������� �������
			\return BOOL ( FALSE == o����� )
		*/
		virtual BOOL GetChildren(IN TYPE_DictIndex iParentClassId, OUT std::list<TYPE_DictIndex> * pChildrenList) = 0;

		/// �������� ����� �������������� ������ ��������
		/** 
			\param  iClassId    - ����� �������������� ������
			\return ����� �������������� ������ �������� ( -1 == ������ )
		*/
		virtual TYPE_DictIndex GetClassParentId(IN TYPE_DictIndex iClassId) = 0;

		/// �����. ����� �������������
		virtual BOOL ZMethod(VOID * pDataPtr1 = NULL, VOID * pDataPtr2 = NULL) = 0;

};

/**************************************************************************************************************/
/// ��������� ������ ����������� ����� � ������� ������������� �������
class ISemanticClassesWords   {

	public:

		virtual ~ISemanticClassesWords() {};

	public:

		/// ������������� ����� �������������� ������ ��� ������
		/** 
			\param iCurrentClass - ����� ��������������
		*/
		virtual VOID SetClass(IN TYPE_DictIndex iCurrentClass) = 0;

		/// ���������� ����� �������������� �������������� ������
		/** 
			\param VOID
		*/
		virtual TYPE_DictIndex GetClass(VOID) = 0;

		/// ���������� ������ �������� ������������� ������� �� ������� �����
		/** 
			\param iIDSource - ������ �����
			\param pClassesList - ��������� �� ������ �������� ������������� �������
		*/
		virtual BOOL GetClasses(IN TYPE_DictIndex iIDSource, OUT std::list<TYPE_DictIndex> * pClassesList) = 0;

		/// ���������� ������ ����, ������� ��������� � �������� �������������� ������
		/** 
			\param pIDSourcesList -������ �������� ����, ����������� � �������������� �������������� ������
			TRUE - �������� ���������
		*/
		virtual BOOL GetWords(OUT std::list<TYPE_DictIndex> * pIDSourcesList) = 0;

		/// ��������� ����� � �������� �������������� ������
		/** 
			\param iIDSource - ������ �����
			\return TRUE - �������� ���������
		*/
		virtual BOOL AddWord(IN TYPE_DictIndex iIDSource) = 0;

		/// ������� �����, ����������� ( !!! ������ !!! ) � �������� �������������� ������
		/** 
			\param iIDSource - ������ �����
			\return TRUE - �������� ���������
		*/
		virtual BOOL DeleteWord (IN TYPE_DictIndex iIDSource) = 0;
		
	};


/**************************************************************************************************************/
/// �������� ����� ������� ��� �������������� �������
	class ISemanticAnalysis 
	{	
	public:
		/// �����������
		ISemanticAnalysis(void){};
		/// ����������
		virtual ~ISemanticAnalysis(){};
	public:
		/// ���������� ������ ������������� ������� �� ������� �����
		/** 
			\param oTFormInfo - ������ ������ �����
			\param p_list_OfClass - ��������� �� ������ �������� ������������� �������
		*/
		virtual bool	GetClasses(/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex, /*out*/ std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_Class) = 0;

		/// ���������� ������ ����, ������� ��������� � �������� �������������� ������
		/** 
			\param p_list_FormInfo - ��������� �� ������, ���������� �����, ����������� � �������������� ������
		*/
		virtual void	GetWords(/*out*/ std::list<SS::Dictionary::Types::TDictionaryIndex>* p_l_DictionaryIndex) = 0;	

		/// ��������� ����� � �������� �������������� ������
		/** 
			\param oTFormInfo - ��� ���������� �����, ������� ���������� ��������
			\return ��������� ��������� ���������� ��������
		*/
		virtual bool	AddWord(/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex) = 0;

		/// ������� �����, ����������� � �������� �������������� ������ � ������������� � TFormInfo
		/** 
			\param oTFormInfo - ��� ���������� �����, ������� ���������� �������
			\return bool	- ��������� ��������
		*/
		virtual bool	DeleteWord (/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex) = 0;
		
		/// ������� ������� ������������� ����� 
		virtual bool	DeleteClass(SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber oDictionariesNumber) = 0;

		/// ������� ����� � ��������� � ���� �����
		/** 
			\param oTFormInfo - ��� ���������� �����, ������� ���������� ��������
			\return ��������� ����� ���������� ������
		*/
		virtual int	CreateClassAndAddWord(/*in*/ SS::Dictionary::Types::TDictionaryIndex & oDictionaryIndex) = 0;
		
	public:
		/// ������������� ����� �������������� ������ ��� ������
		/** 
			\param iIDClass - ����� �������������� ������ ��� ������
		*/
		void	SetClass(const /*in*/SS::Dictionary::Types::TDictionaryIndex& oCurrentClass)
		{
			m_oCurrentClass = oCurrentClass;
		}

		/// ���������� ����� �������������� ������ ��� ������
		SS::Dictionary::Types::TDictionaryIndex	GetClass()
		{
			return m_oCurrentClass;
		}

	protected:
		SS::Dictionary::Types::TDictionaryIndex  m_oCurrentClass;
	};


/**************************************************************************************************************/
/// �������� ����� �������, ����������� ��� ������ � ������� �����
	class ISemanticIDSourceTree
	{
	public:
		/// �����������
		ISemanticIDSourceTree(void) {};
		/// ����������
		virtual ~ISemanticIDSourceTree(){};
	public:
		/// ������������� ������ ��������
		/** 
			\param oFullIDSource - ��������������� ������ ��������
		*/
		virtual void SetIDParent(SS::CoSeDi::DataTypes::SFullIDSource& oFullIDSource)
		{
			m_oFullIDSourceParent = oFullIDSource;
		}
		/// ������������� ������ �������
		/** 
			\param oFullIDSource - ��������������� ������ �������
		*/
		virtual void SetIDChild(SS::CoSeDi::DataTypes::SFullIDSource& oFullIDSource)
		{
			m_oFullIDSourceChild = oFullIDSource;
		}
		/// ���������� ������ ��������
		/** 
			\param oFullIDSource - ��������������� ������ ��������
		*/
		virtual void GetIDParent(SS::CoSeDi::DataTypes::SFullIDSource& oFullIDSource)
		{
			oFullIDSource = m_oFullIDSourceParent;
		}

		/// ���������� ������ �������
		/** 
			\param oFullIDSource - ��������������� ������ �������
		*/
		virtual void GetIDChild(SS::CoSeDi::DataTypes::SFullIDSource& oFullIDSource)
		{
			oFullIDSource = m_oFullIDSourceChild;
		}

		/// ���������� ���� ��������� �������� �������
		/** 
			\param plistOfFullIDSource - ��������� �� ������, ���������� ������� ���������
		*/
		virtual void GetParents(std::list<SS::CoSeDi::DataTypes::SFullIDSource>* plistOfFullIDSource) = 0;

		/// ��������� ������� ���� (��������, �������)
		virtual void Add() = 0;

		/// ������� ���� ������� (��������, �������)
		virtual void Delete() = 0;
	protected:
		///	������� ��������	
		SS::CoSeDi::DataTypes::SFullIDSource m_oFullIDSourceParent;
		///	������� �������	
		SS::CoSeDi::DataTypes::SFullIDSource m_oFullIDSourceChild;

	};




/**************************************************************************************************************/
/// ��������� ��� ��������������� �������
	class ISyntaxAnalysis
	{	
	public:
		/// �����������
		ISyntaxAnalysis(void): m_SyntaxInfo(0), m_oDictionaryNumber(SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber::ednUnknown) 
		{
			m_oIDSource.uchIDSuffics = 0;
			m_oIDSource.ushIDRoot = 0;
		};
		/// ����������
		virtual ~ISyntaxAnalysis(){};
	public:
		/// ���������� ������, ���������� �������������� �������������� ��� ������� ������
		/** 
			\param p_list_OfSyntaxInfo - ��������� �� ������, ���������� �������������� �������������� ��� ������� ������
		*/
		virtual void Get(/*out*/std::list<SS::CoSeDi::DataTypes::TSyntaxInfo>* p_list_OfSyntaxInfo)		= 0;

		/// ��������� ������, ���������� �������������� �������������� ��� ������� ������
		/** 
			\param p_list_OfSyntaxInfo - ��������� �� ������, ���������� �������������� �������������� ��� ������� ������
		*/
		virtual void Add(/*in*/std::list<SS::CoSeDi::DataTypes::TSyntaxInfo>* p_list_OfSyntaxInfo)		= 0;

		/// ������� ��� �������������� ���������� ��� ������� ������
		virtual void Delete()												= 0;

		/// ������� ������, ���������� �������������� �������������� ��� ������� ������
		/** 
			\param p_list_OfSyntaxInfo - ��������� �� ������, ���������� �������������� �������������� ��� ������� ������
		*/
		virtual void Delete(/*in*/std::list<SS::CoSeDi::DataTypes::TSyntaxInfo>* p_list_OfSyntaxInfo)	= 0;
		
	public:
		/// ������������� ������ ������ ��� ������
		/** 
			\param oIDSource - ������ ������ 
		*/
		virtual void SetIDSource(SS::CoSeDi::DataTypes::TIDSource oIDSource)
		{
			m_oIDSource = oIDSource;
		};

		/// ���������� ������� ������ ������
		/** 
			\return SS::CoSeDi::DataTypes::TIDSource - ������ ������
		*/
		virtual SS::CoSeDi::DataTypes::TIDSource GetIDSource()
		{
			return m_oIDSource;
		};
		
		/// ������������� ������� ������ �������
		/** 
			\param uchDictionaryNumber - ������ �������
		*/
		virtual void SetDictionaryNumber(SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber oDictionaryNumber)
		{
			m_oDictionaryNumber = oDictionaryNumber;
		};

		/// ���������� ������� ����� �������
		virtual SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber GetDictionaryNumber()
		{
			return m_oDictionaryNumber;
		};
					
	protected:
		///	������� ����� �������	
		SS::Dictionary::DATA_TYPE::NAMES::DictionariesNumber m_oDictionaryNumber;
		///	������� ������ ������	
		SS::CoSeDi::DataTypes::TIDSource	m_oIDSource;
		///	������� TSyntaxInfo	
		SS::CoSeDi::DataTypes::TSyntaxInfo	m_SyntaxInfo;
	};


/**************************************************************************************************************/		

	#include <set>
	#include <unordered_set>
	#include <list>

	/// ��� ������ : ����� ������������ HASH-������ ����������
	typedef std::unordered_set< UINT32 >                     TSetOfHashKeys;

	/// ��� ������ : �������� ��� "������ ������������ HASH-������ ����������"
	typedef std::unordered_set< UINT32 >::const_iterator     TSetOfHashKeysItr;

	/// ��� ������ : ��������������� ������ � ����� �����-����� �����
	struct SSourceAndForm
	{
		SSourceAndForm(UINT32 uiIDSourceVal = 0, UINT32 uiIDFormVal = 0) : IDSource(uiIDSourceVal), IDForm(uiIDFormVal) { }
		UINT32 IDSource;
		UINT32 IDForm;
	};

	template<class _Ty> struct Second_Elem_Greater : public std::binary_function<_Ty, _Ty, bool> { // functor for operator<
		bool operator()(const _Ty & _Left, const _Ty & _Right) const   { // apply operator< to operands
			// return (_Left.second > _Right.second);
			if(((SSourceAndForm *)&_Left)->IDSource == ((SSourceAndForm *)&_Right)->IDSource)   {
				return(((SSourceAndForm *)&_Left)->IDForm > ((SSourceAndForm *)&_Right)->IDForm);
			} else   {
				return(((SSourceAndForm *)&_Left)->IDSource > ((SSourceAndForm *)&_Right)->IDSource);
			}
		}
	};


	/// ��� ������ : ����� ��������������� �������� � ����
	typedef std::set< SSourceAndForm, Second_Elem_Greater< SSourceAndForm > >           TSetOfSourcesAndForms;

	/// ��� ������ : �������� ��� "������ ��������������� �������� � ����"
	typedef std::set< SSourceAndForm, Second_Elem_Greater< SSourceAndForm > >::iterator TSetOfSourcesAndFormsItr;

	/// ��� ������ : ������ "������� ��������������� �������� � ����"
	typedef std::list<        TSetOfSourcesAndForms >            TListOfSetsOfSourcesAndForms;

	/// ��� ������ : �������� ��� ������ "������� ��������������� �������� � ����"
	typedef std::list<        TSetOfSourcesAndForms >::iterator  TListOfSetsOfSourcesAndFormsItr;

	/// ��� ������ : ������ ���������� �� "������ ��������������� �������� � ����"
	typedef std::list<        TSetOfSourcesAndForms *>           TListOfPtrsToSetsOfSourcesAndForms;

	/// ��� ������ : �������� ��� ������ ���������� �� "������ ��������������� �������� � ����"
	typedef std::list<        TSetOfSourcesAndForms *>::iterator TListOfPtrsToSetsOfSourcesAndFormsItr;


	/// ��� ������ : ��������������� ������ � ������� ����� � �����������
	struct SWordPos
	{
		SWordPos(UINT32 id = 0, UINT32 pos = 0) : uiIDSource(id), uiPosition(pos) { }
		UINT32 uiIDSource;
		UINT32 uiPosition;
	};

	/// ��� ������ : ������ ��������������� �������� � ������� ���� � �����������
	typedef std::vector		< SWordPos >                   TIDSourceVector;


	//  --------------------------------------------
	/// ��������� ��� �������������� ������� ������������
	class INumberCombinatory : public virtual SS::Interface::IBase
	{
	public:
		/// ���������� ������ ���������� ��� ������������ ������ ������� IDSource-��
		/** 
			\param  pvSourcesAndForms						- ������ �������� ����� �����������
			\param  p_listCombinationInfo		         - �������� ������ ���������� � �����������
		*/
		virtual void GetCombinationsInfo(
			/*in */ TIDSourceVector* pvSourcesAndForms, 
			/*out*/ std::list<SS::CoSeDi::DataTypes::SCombinationNewInfo> * p_listCombinationInfo) = 0;
	};

	//  --------------------------------------------
	/// ��������� ��� ������ �������������� �������
	class ICombinatory
	{	

	public:				

		/// ���������� ������ ���������� ��� ������������ ������ ������� IDSource-��
		/** 
			\param  itrStartItr_In_ListOfSetsOfSourcesAndForms - ��������� �������� ������
			\param  iNumOfWordsToProcess                 - ����� ������� IDSource-�� ��� ���������
			\param  p_listCombinationInfo                - �������� ������ ���������� � �����������
			\return bool                                 - ��������� ���������� ��������
		*/
		virtual bool GetCombinationsInfo(
			/*in */ TListOfSetsOfSourcesAndFormsItr itrStartItr_In_ListOfSetsOfSourcesAndForms,
			/*in */ UINT iNumOfWordsToProcess,
			/*out*/ std::list<SS::CoSeDi::DataTypes::SCombinationNewInfo> * p_listCombinationInfo) = 0;

		/// ���������� ������ ���������� ��� ������������ ������ ������� IDSource-�� (Mode 2)
		/** 
			\param  itrStartItr_In_ListOfSetsOfSourcesAndForms - ��������� �������� ������
			\param  iNumOfWordsToProcess                       - ����� ������� IDSource-�� ��� ���������
			\param  p_listCombinationInfo                      - �������� ������ ���������� � �����������
			\return bool                                       - ��������� ���������� ��������
		*/
		virtual bool GetCombinationsInfo_2(
			/*in */ TListOfSetsOfSourcesAndFormsItr itrStartItr_In_ListOfSetsOfSourcesAndForms,
			/*in */ UINT iNumOfWordsToProcess,
			/*out*/ std::list<SS::CoSeDi::DataTypes::SCombinationNewInfo> * p_listCombinationInfo) = 0;



		/// ���������� ������ ���������� ��� ������������ ������ ������� IDSource-��
		/** 
			\param  itrBegin_ListOfSetsOfSourcesAndForms - ��������� �������� ������
			\param  itrEnd_ListOfSetsOfSourcesAndForms   - �������� �������� ������
			\param  p_listCombinationInfo          - �������� ������ �������� ���������� � �����������
			\return bool                           - ��������� ���������� ��������
		*/
		virtual bool GetCombinationsInfo(
			/*in */ TListOfSetsOfSourcesAndFormsItr itrBegin_ListOfSetsOfSourcesAndForms,
			/*in */ TListOfSetsOfSourcesAndFormsItr itrEnd_ListOfSetsOfSourcesAndForms,
			/*out*/ std::list<SS::CoSeDi::DataTypes::SCombinationNewInfo> * p_listCombinationInfo) = 0;

		/// ���������� ������ ���������� ��� ������������ ������ ������� IDSource-�� (Mode 2)
		/** 
			\param  itrBegin_ListOfSetsOfSourcesAndForms - ��������� �������� ������
			\param  itrEnd_ListOfSetsOfSourcesAndForms   - �������� �������� ������
			\param  p_listCombinationInfo          - �������� ������ �������� ���������� � �����������
			\return bool                           - ��������� ���������� ��������
		*/
		virtual bool GetCombinationsInfo_2(
			/*in */ TListOfSetsOfSourcesAndFormsItr itrBegin_ListOfSetsOfSourcesAndForms,
			/*in */ TListOfSetsOfSourcesAndFormsItr itrEnd_ListOfSetsOfSourcesAndForms,
			/*out*/ std::list<SS::CoSeDi::DataTypes::SCombinationNewInfo> * p_listCombinationInfo) = 0;

		/// ���������� ������ ����������, ���������� �������� IDSource
		/** 
			\param iIDSource              - �������� IDSource
			\param  p_listCombinationsIDs - �������� ������ �������� ����������
			\return bool                  - ��������� ���������� ��������
		*/
		virtual bool GetCombinationsByIDSource(/*in*/int iIDSource, /*out*/ std::list<int> * p_listCombinationsIDs) = 0;	
		
		/// ���������� ���������� � ����������
		/** 
			\param iIDCombination    - ����� ����������
			\param p_CombinationInfo - ��������� �� ���������, �������� ���������� � ����������
			\return bool             - ��������� ���������� ��������
		*/
		virtual bool GetCombinationInfo(/*in*/int iIDCombination, /*out*/ SS::CoSeDi::DataTypes::SCombinationNewInfo * p_CombinationInfo) = 0;	

		/// ������� ����������
		/** 
			\param p_CombinationInfo - ��������� �� ���������, ���������� ���������� � ����������
			\return bool             - ��������� ���������� ��������
		*/
		virtual bool CreateCombination(/*in out*/ SS::CoSeDi::DataTypes::SCombinationNewInfoForAdd * p_CombinationInfo) = 0;

		/// ������� ����������
		/** 
			\param iIDCombination - ����� ����������
			\return bool          - ��������� ���������� ��������
		*/
		virtual bool DeleteCombination(/*in*/int iIDCombination) = 0;

	};

/// ��������� ��� �������� �������
	class ICoSeDiLoad 
	{
	public:
		/// �����������
		ICoSeDiLoad (void){};
		/// ����������
		virtual ~ICoSeDiLoad (){};
	public:
		///	��������� ��������	
		virtual bool Load() = 0;
		///	������������	
		virtual bool ReLoad() = 0;
		///	�������������� � ��������� ����	
		virtual bool ToBinary() = 0;
		/// ������� �������
		virtual bool Clear()	= 0;
	};
	

/**************************************************************************************************************/

/// ���������, ����������� ������� ����������� ���������� �������������� �������
	class ICoSeDiManager : public virtual SS::Interface::IBase
	{
	public:
		/// �����������
		ICoSeDiManager(void){};
		/// ����������
		virtual ~ICoSeDiManager(){};
	public:
		
		/// ���������� �������� ��� �������� �������
		virtual SS::Interface::Core::CoSeDi::ICoSeDiLoad                * GetLoader() = 0;

		///	���������� �������� ��� �������������� �������
		virtual SS::Interface::Core::CoSeDi::ICombinatory               * GetCombinatory() = 0;

		///	���������� �������� ��� �������������� ������� (���. ������������� �������)
		virtual SS::Interface::Core::CoSeDi::ICombinatory               * GetCombinatoryExtra() = 0;

		///	���������� �������� ��� �������������� ������� ��� ������ � �������������� ����������
		virtual SS::Interface::Core::CoSeDi::ISemanticAnalysis          * GetCombiSynonimsAnalysis() = 0;

		///	���������� �������� ��� �������������� ������� ��� ������ � ����������
		virtual SS::Interface::Core::CoSeDi::ISemanticAnalysis          * GetSynonimsSemanticAnalysis() = 0;

		///	���������� �������� ��� �������������� �������	
		virtual SS::Interface::Core::CoSeDi::ISemanticAnalysis          * GetSemanticAnalysis() = 0;

		///	���������� �������� ��� �������������� �������	
		virtual SS::Interface::Core::CoSeDi::ISemanticAnalysis          * GetRestaurantSemanticAnalysis() = 0;

		///	���������� �������� ��� ��������������� �������	
		virtual SS::Interface::Core::CoSeDi::ISyntaxAnalysis            * GetSyntaxAnalysis() = 0;

		///	���������� �������� ��� ������ � ������� ������������� �������
		virtual SS::Interface::Core::CoSeDi::ISemanticClassesTree       * GetSemanticClassesTree() = 0;

		///	���������� �������� ��� ������ � ��������, ���������� � ������� ������������� �������
		virtual SS::Interface::Core::CoSeDi::ISemanticClassesWords      * GetSemanticClassesWords() = 0;

		///	���������� �������� ��� ������ � �������������� ��������� ���������� �����
		virtual SS::Interface::Core::CoSeDi::ISemanticIDSourceTree      * GetSemanticIDSourceTree() = 0;
	};
}
}
}
}
