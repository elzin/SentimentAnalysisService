#pragma once
#include "..\ASDInterface\INDXQuery.h"
#include ".\Block.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxQuery
{

///	���������� ISuperTemplate
/**
	������������������. �������� ���� ����� AND-������ � ������ OR-������.
*/
class CSuperTemplate :
	public SS::Interface::Core::NdxSE::ISuperTemplate
{
public:
	///	�����������
	CSuperTemplate(void);

	///	����������
	virtual ~CSuperTemplate(void);

	///	��������� ����� AND
	///	����� ��������� �� AND-����, ����� �������� NULL ���� AND-���� �� ����������
	///	\return	��������� �� AND-����
	virtual SS::Interface::Core::NdxSE::IBlock* GetANDBlock();
	
	///	����� ���������� OR-������
	///	\return	���������� OR-������
	virtual unsigned int GetORBlockCount();

	///	��������� ����� �� ������ (���� ����� ������������, ������� NULL)
	///	���� ����� ����������, ������� �� ������� NULL
	///	\param[in]	uiIndex	����� OR-�����
	///	\return	��������� �� OR-����
	virtual SS::Interface::Core::NdxSE::IBlock* GetORBlock(unsigned int uiIndex);

	virtual	const wchar_t*	ToString();

	///	���������� ����� ����� �������
	virtual void	DebugView();

	///	����� AND-����. ���� �� ������ ����������� �� ������������
	///	\param[in]	Block	��������������� AND-����
	void	SetANDBlock(SS::Interface::Core::NdxSE::IBlock*	pBlock);

	///	��������� OR-����
	///	\param[in]	Block	����, ����������� � ���������. ���� Block == NULL �� �� �����������.
	void	AddORBlock(SS::Interface::Core::NdxSE::IBlock*	pBlock);

	///	������� �������
	///	���������� AND-���� � OR-�����
	void	Clear();

private:
	///	AND-����
	std::auto_ptr<SS::Interface::Core::NdxSE::IBlock>	m_AndBlock;
	///	������ ��� �������� ���������� �� �����
	typedef std::vector<SS::Interface::Core::NdxSE::IBlock*>	v_Block;
	///	��������� ���������� �� OR-�����
	v_Block											m_OrBlocks;
	///	��������� ������������� ��� �������
	std::wstring	m_AsString;
};

}
}
}
}


