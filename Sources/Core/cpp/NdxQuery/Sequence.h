#pragma once
#include "..\ASDInterface\INDXQuery.h"
#include ".\types.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxQuery
{

///	���������� ISequence
/**
	����� ������������ ������������������ ����
*/
class CSequence :
	public SS::Interface::Core::NdxSE::ISequence
{
public:
	///	ctr
	CSequence(void);

	//	���������
	virtual ~CSequence(void);
	virtual unsigned int GetWordCount();
	virtual SS::Interface::Core::NdxSE::IWord* GetWord(unsigned int uiIndex);
	virtual unsigned int GetUnionWordsBlocksCount();
	virtual SS::Interface::Core::NdxSE::SUnionWordsBlockInSequence GetUnionWordsBlock(unsigned int uiIndex);
	virtual BOOL	IsWordInUnion(unsigned int uiIndex, SS::Interface::Core::NdxSE::SUnionWordsBlockInSequence* pUnion);
	virtual	const wchar_t*	ToString();
	virtual void	DebugView();

	//	����������
	///	���������� �����. ���� NULL �� �� ���������
	void	AddWord(SS::Interface::Core::NdxSE::IWord*	Word);
	///	���������� �������� union-�����
	void	AddUnionWordsBlock(SS::Interface::Core::NdxSE::SUnionWordsBlockInSequence const& UnionWordsBlock);
	///	������� ������, ������������ � ���� �������� union-������ �� UnionBlockInfo
	void	AssignUnionWordsBlocks(v_UWB& UnionBlockInfo);
	///	�������� ������� �� ���������
	static void	Del(ISequence*	Seq);
	///	������� �������
	void	Clear();

private:
	///	������ ��� �������� ���������� �� �����
	typedef std::vector<SS::Interface::Core::NdxSE::IWord*>	v_Word;
	///	��������� ����
	v_Word	m_Words;
	///	������ ��� �������� ���������� union-������
	typedef std::vector<SS::Interface::Core::NdxSE::SUnionWordsBlockInSequence>	v_UWB;
	///	��������� union-�������������������
	v_UWB	m_UnionWordsBlocks;
	///	��������� ������������� ��� �������
	std::wstring	m_AsString;
};

}
}
}
}


