#pragma once
#include "..\ASDInterface\INDXQuery.h"
#include "./types.h"
namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxQuery
{
///	���������� IWord
class CWord: public SS::Interface::Core::NdxSE::IWord
{
public:
	CWord(void);
	//	��������� ����������
	virtual ~CWord(void);
	virtual unsigned int	GetMorphoIndexCount();
	virtual unsigned int	GetMorphoIndex(unsigned int _uiIndex);
	virtual unsigned int	GetSyntaxIndexCount();
	virtual unsigned int	GetSyntaxIndex(unsigned int _uiIndex);
	virtual unsigned int	GetSemanticIndexCount();
	virtual unsigned int	GetSemanticIndex(unsigned int _uiIndex);
	virtual	float			GetLinguisticWeight();
	virtual BOOL			GetObligatoryFlag();
	virtual BOOL			GetAnswerFlag();
	virtual const wchar_t*	GetAsString();
	virtual	const wchar_t*	ToString();
	virtual void			DebugView();
	//	����������
	void					SetObligatoryFlag(bool const	_bValue);
	void					SetAnswerFlag(bool const	_bValue);
	void					SetAsString(const wchar_t*	_wszWord);
	void					AddMorphoIndex(unsigned int _Index);
	void					AddSyntaxIndex(unsigned int _Index);
	void					AddSemanticIndex(unsigned int _Index);
	void					SetLinguisticWeight(float const _weight);
	///	������� ������� ������ �������, ����� �������� ������� �� _source
	void					Fill(SWordIndexes const& _rhs);
	static void				Del(IWord*	_Word);

private:
	///	��������� ���� ����� ��������
	SWordIndexes_vector	m_Indexes;
	///	�������� ������
	unsigned char		m_Flags;
	///	��������� ������������� �����
	wchar_t*			m_wszWord;
	///	��������������� ��� �����
	float				m_LinguisticWeight;
	///	��������� ��� ����� ��� �������
	std::wstring		m_AsString;
};

}
}
}
}


