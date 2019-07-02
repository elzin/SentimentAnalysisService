#pragma once

#include <string>
#include <list>

#include "../ASCInterface/TDictionaryIndex.h"

namespace SS
{
namespace Dictionary
{
namespace Types
{

/// ������ ������ �����
struct SWordIndex
{
	TDictionaryIndex m_DictIndex;
	TIDForm          m_IDForm;
	SWordIndex() : m_IDForm(0)
	{}

	bool operator == (const SWordIndex & value) const	
	{
		return ((m_DictIndex.GetDictionaryIndex() == value.m_DictIndex.GetDictionaryIndex())&&
				(m_IDForm ==	value.m_IDForm)
				) ? true : false;
	}

	SWordIndex& operator= (const SWordIndex& value)
	{
		m_DictIndex.SetDictionaryIndex(value.m_DictIndex.GetDictionaryIndex());
		m_IDForm = value.m_IDForm;
		
		return *this;
	}
};

/// ��������������� ���������� ������
struct SMorphoTypeInfo
{
	TIDType		m_IDType;
	TMorphoInfo m_MorphoInfo;
	SMorphoTypeInfo() : m_IDType(0), m_MorphoInfo(0)
	{}
};

/// �������� ������ ���������� �� ������
struct SSource
{
	TDictionaryIndex  m_DictIndex;
	std::wstring	  m_wSource;
	SMorphoTypeInfo   m_MorphoTypeInfo;

};

/// �������� ������ ���������� � ���� ����������������
struct SMorphoType 
{
	TIDEnding		m_IDEnding;
	TIDForm			m_IDForm;
	TSpecialMorpho	m_SpecialMorpho;
	SMorphoTypeInfo m_MorphoTypeInfo;

	SMorphoType() : m_IDEnding(0), m_IDForm(0), m_SpecialMorpho(0)
	{}
};

/// ������ ��������������� ���������� � ������� �����
struct SWordInfo  
{
	std::wstring	m_wWord;
	TSpecialMorpho	m_SpecialMorpho;
	SWordIndex      m_WordIndex; 
	SMorphoTypeInfo m_MorphoTypeInfo;
    bool            m_NewWord;

	SWordInfo():   m_SpecialMorpho(0), m_NewWord(0)
	{
	}

};

/// ������ ��������������� ���������� � ��������� �����
typedef std::list<SWordInfo> TWordInfo;


//���������� ������� ������ � IMorphologyAnalyser
enum EFindZone
{
    /*  ����� �� ���� ��������, ������� ������� ����� ����, ���� ����� ����������, �������� � ������� ����� ���� */
    efzFullAddNewWords,		
    
    /*	������ ����� �� ���� ��������, ������� ������� ����� ����, ���� ����� ����������, � ������� ����� ���� �� ���������*/
    efzOnlySearch,			
    
    /*	������ ����� � ������ ������� ����������� */
    efzAbbreviation,		
    
    /* ����� � ����������� � ������ */
    efzBaseDictionary,		
    
    /*	������ ����� � ������� ����� ���� */
    efzNewWord,

    /* ����� � ������, ������������� � ����������� */
    efzBaseAndAbbreviation,
    
    /*  ����� �� ���� ��������, ������� ������� ����� ���� � ����������� ��������� ����, ���� ����� ����������, �������� � ������� ����� ���� */
    efzFullAddNewWordsCompound
};

}
}
}