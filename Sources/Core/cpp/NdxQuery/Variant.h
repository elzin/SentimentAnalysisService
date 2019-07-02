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

///	���������� IVariant
/**
	������������ ����� ������� �������
*/
class CVariant :
	public SS::Interface::Core::NdxSE::IVariant
{
public:
	///	�����������
	CVariant(void);

	///	����������
	virtual ~CVariant(void);

	///	���������� ����� �������������������
	/**
		\return	����� �������������������
	*/
	virtual unsigned int GetSequenceCount();

	///	���������� ������������������ �� ������. ���� ����� ������������ ���������� NULL
	/**
		\param[in]	uiIndex	����� ������������������
		\return	������������������
	*/
	virtual SS::Interface::Core::NdxSE::ISequence* GetSequence(unsigned int uiIndex);

	virtual	const wchar_t*	ToString();

	virtual void	DebugView();

	///	��������� ������������������
	/**
		\param[in]	Seq	����������� ������������������. ��������� �� ����������� �� NULL, �� ������ ���� NULL
	*/
	void	AddSequence(SS::Interface::Core::NdxSE::ISequence*	Seq);

	///	���������� ��������� �� IVariant
	/**
		���������� ������ �� ���������, ������������ � ���������� STL
		\param[in]	Var	��������� ���������
	*/
	static void Del(SS::Interface::Core::NdxSE::IVariant* Var);

	///	������� ������
	/**
		���������� �������� ������������������
	*/
	void	Clear();

private:
	typedef std::vector<SS::Interface::Core::NdxSE::ISequence*>	v_Sequences;
	///	��������� �������������������
	v_Sequences				m_Sequences;
	///	��������� ��� ����� ��� �������
	std::wstring			m_AsString;
};

///	��� ���������� ��� �������� IVariant*
typedef std::vector<SS::Interface::Core::NdxSE::IVariant*>	v_Variant;

}
}
}
}


