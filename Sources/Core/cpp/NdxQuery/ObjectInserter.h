#pragma once
#include "./Console.h"
#include "./Word.h"
#include "./Block.h"
#include "./Sequence.h"
#include "./Variant.h"
#include "./SuperTemplate.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxQuery
{

///	����� ��� ����������� �������� ���� � �����
///	������� ����� �������� ������� ������ ����������� � ����������� ������
///	���� ���� ��� �� ���������
///	variant	sequence	word
///			block		word
class CObjectInserter
{
public:
	///	�����������
	__forceinline	CObjectInserter(
		CSuperTemplate*	_pST,
		v_Variant*		_pvVariants)
		:m_pST(_pST), m_pvVariants(_pvVariants)
	{
		if (m_pST == NULL) throw std::wstring(L"ERROR!!!: _pST == NULL !!!");
		if (m_pvVariants == NULL) throw std::wstring(L"ERROR!!!: _pvVariants == NULL !!!");
	}

	///	����������
	__forceinline	~CObjectInserter()
	{
		//	���� ������� �� ��������� � SuperTemplate ������, ��� ������
		if (m_apWord.get()		!= NULL		||
			m_apAndBlock.get()	!= NULL		||
			m_apOrBlock.get()	!= NULL		||
			m_apSequence.get()	!= NULL		||
			m_apVariant.get()	!= NULL)
				ToConsole(L"\n.\nERROR!!!: _pST == NULL !!!\n.\n.");
	}

	///	������ ������� ����� (������ �� NULL)
	__forceinline CWord*	current_word()
	{
		//	���� ������ ������ �� ������
		if (m_apWord.get() == NULL) m_apWord.reset(new CWord());
		//	�����
		return m_apWord.get();
	}

	///	������ ������� ������������������ ����� ���� NULL
	__forceinline CSequence*	current_sequence()
	{
		return m_apSequence.get();
	}

	///	���������� ����� � AND-����
	__forceinline void	Word2AndBlock()
	{
		//	���� ������ ������ �� ������ ������ �� ������
		if (m_apWord.get() == NULL) return;
		//	���� ������ ������ �� ������
		if (m_apAndBlock.get() == NULL) m_apAndBlock.reset(new CBlock());
		//	���������
		m_apAndBlock->AddWord(m_apWord.release());
	}

	///	���������� ����� � OR-����
	__forceinline void	Word2OrBlock()
	{
		//	���� ������ ������ �� ������ ������ �� ������
		if (m_apWord.get() == NULL) return;
		//	���� ������ ������ �� ������
		if (m_apOrBlock.get() == NULL) m_apOrBlock.reset(new CBlock());
		//	���������
		m_apOrBlock->AddWord(m_apWord.release());
	}

	///	���������� ����� � ������������������
	__forceinline void	Word2Sequence()
	{
		//	���� ������ ������ �� ������ ������ �� ������
		if (m_apWord.get() == NULL) return;
		//	���� ������ ������ �� ������
		if (m_apSequence.get() == NULL) m_apSequence.reset(new CSequence());
		//	���������
		m_apSequence->AddWord(m_apWord.release());
	}

	///	���������� AND-���� � SuperTemplate
	__forceinline void	AndBlock2ST()
	{
		//	���� ������ ������ �� ������ ������ �� ������
		if (m_apAndBlock.get() == NULL) return;
		m_pST->SetANDBlock(m_apAndBlock.release());
	}

	///	���������� OR-���� � SuperTemplate
	__forceinline void	OrBlock2ST()
	{
		//	���� ������ ������ �� ������ ������ �� ������
		if (m_apOrBlock.get() == NULL) return;
		//	����������
		m_pST->AddORBlock(m_apOrBlock.release());
	}

	///	���������� ������������������ � �������
	__forceinline void	Sequence2Variant()
	{
		//	���� ������ ���������� �� �������
		if (m_apSequence.get() == NULL) return;
		//	���� ������ ���������� �� ������
		if (m_apVariant.get() == NULL) m_apVariant.reset(new CVariant());
		//	����������
		m_apVariant->AddSequence(m_apSequence.release());
	}

	///	���������� ������� � SuperTemplate
	__forceinline void	Variant2ST()
	{
		//	���� ������ ���������� �� �������
		if (m_apVariant.get() == NULL) return;
		//	����������
		m_pvVariants->push_back(m_apVariant.release());
	}

private:
	///	��������� �� SuperTemplate
	CSuperTemplate*				m_pST;
	///	��������� �� ������ ���������
	v_Variant*					m_pvVariants;
	///	����� �������� ��� ��������
	std::auto_ptr<CWord>		m_apWord;
	std::auto_ptr<CBlock>		m_apAndBlock;
	std::auto_ptr<CBlock>		m_apOrBlock;
	std::auto_ptr<CSequence>	m_apSequence;
	std::auto_ptr<CVariant>		m_apVariant;
};


}
}
}
}