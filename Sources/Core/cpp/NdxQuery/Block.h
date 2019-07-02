#pragma once
#include "..\ASDInterface\INDXQuery.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxQuery
{

///	���������� IBlock
/**
	����� ������������ ���� ����, �������� � ������������������
*/
class CBlock :
	public SS::Interface::Core::NdxSE::IBlock
{
public:
	///	�����������
	CBlock(void);

	///	����������
	virtual ~CBlock(void);

	///	��������� ���������� ���� �����
	/**
		\return	���������� ���� � �����
	*/
	virtual unsigned int GetWordCount();

	///	��������� ����� �� ������ (zero-based)
	/**
		�� ���������� �������� ���������!!!
		\param[in]	uiIndex	����� �����
		\return	�����
	*/
	virtual SS::Interface::Core::NdxSE::IWord* GetWord(unsigned int uiIndex);


	virtual	const wchar_t*		ToString();


	virtual void	DebugView();

	///	���������� ����� � ����
	/**
		\param[in]	Word	��������� �� ����������� �����, �� ����������� �� NULL, �� ������ ���� NULL
	*/
	void	AddWord(SS::Interface::Core::NdxSE::IWord*	Word);

	///	�������� ����� �� ���������
	/**
		������������ � STL ���������� ��� ������ � �������
		\param[in]	Block	��������� �� ��������� ������
	*/
	static	void	Del(SS::Interface::Core::NdxSE::IBlock*	Block);

	///	����� �������
	/**
		������� ��� �������� �����, ������ ������
	*/
	void	Clear();

private:
	///	������ ��� �������� ���������� �� �����
	typedef std::vector<SS::Interface::Core::NdxSE::IWord*>	v_Word;
	///	��������� ����
	v_Word			m_Words;
	///	��������� ������������� ��� �������
	std::wstring	m_AsString;
};

}
}
}
}


