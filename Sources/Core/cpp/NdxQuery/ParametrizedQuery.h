#pragma once
#include "..\ASCInterface\ICommonServices.h"
#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASDInterface\INDXQuery.h"
#include ".\Variant.h"
#include ".\SuperTemplate.h"
#include ".\types.h"

namespace SS
{
namespace Core
{
namespace NdxSE
{
namespace NdxQuery
{

///	���������� IParametrizedQuery
/**
	������� ������
	������� ����� Init � ��������� �������� ���������� �����������
	����������� ��������� ������ ��� ��������� ������������������ � ���������
*/
class CParametrizedQuery :
	public SS::Interface::Core::NdxSE::IParametrizedQuery
{
public:
	///	�����������
	CParametrizedQuery(void);

	///	����������
	virtual ~CParametrizedQuery(void);

	/// ������������� ��������, ��������������� ��������������� �����������
	///	������� ������� �������:
	///	���� ����������� ��������� � ss.dat "NdxProcessor::ForceSearchMode" == 7, 
	///	���������� Init_AllOrMode, ��������� ������
	///	���� ���� ������� � �������, ���������� Init_AnswerMode()
	///	���� ��� �������� � �������, ���������� Init_Standard()
	///	\param[in]	pQuery			��������� ������
	///	\param[in]	pSearchParams	��������� ������
	virtual void Init(
		SS::Interface::Core::CommonContainers::IQueryResult*	pQuery,
		SS::Core::Types::IndexationSearch::TSearchParams*	pSearchParams);


	/// ���������� ��������� �� ������������������
	/**
		������������ ��������� ������� �� NULL
		�� ���������� �������� ���������!!!
		\return	��������� �� ������������������
	*/
	virtual SS::Interface::Core::NdxSE::ISuperTemplate* GetSuperTemplate();

	/// ���������� ���������� ��������� �������
	/**
		\return	���������� ��������� �������, ������ ����� ����� ���������� �������������
	*/
	virtual unsigned int GetVariantCount();

	///	���������� ������� �� ������
	///	\return	��������� �� ������� �������
	virtual SS::Interface::Core::NdxSE::IVariant* GetVariant(unsigned int uiIndex);

	
	virtual BOOL	GetHasAnswers();

	virtual BOOL	GetHasUnionBlocks();

	virtual BOOL	GetHasNonObligatoryWords();

	///	���������� � ���������� � �������� REFIID. pBase ����� NULL, ���� ������ ��������� �� ��������������	*/
	virtual HRESULT	QueryInterface(REFIID pIID, void** pBase); 

	///	������������
	virtual ULONG	Release();

	///	������� c��������� � ������
	virtual	const wchar_t*	ToString();

	///	������� ����� ������ � ������
	virtual	const wchar_t*	ToStringRawQuery(SS::Interface::Core::CommonContainers::IQueryResult* pQuery);

	///	���������� ����� ����������� �������
	virtual void	DebugView();

	///	���������� ����� ������������������� �������
	virtual void	DebugViewRawQuery(SS::Interface::Core::CommonContainers::IQueryResult* pQuery);

protected:
	///	��������� �� ������ ��������
	SS::Interface::Core::CommonServices::ISettingsServer*	m_pSettingsServer;
	///	������������������
	auto_ptr<CSuperTemplate>		m_pSuperTemplate;
	/// ��������� ��� �������� ��������
	v_Variant						m_Variants;
	///	���� HasAnswers, ������������ ����� Init(...),
	///	�������� ��������� ���� ��� � ������� ���� ����� ������
	BOOL							m_HasAnswers;
	///	���� ������� �����-������, ������������ ����� Init(...),
	///	�������� ��������� ���� ��� � ������� ���� union-�����
	BOOL							m_HasUB;
	///	���� ������� �������������� ����, ������������ �����  Init(),
	///	�������� ��������� ���� ��� � ������� ���� �������������� �����
	BOOL							m_HasNonObligatoryWords;

	///	������ �������, �� ����������� ������� � �������
	///	\param[in]	pQuery	��������� ������
	void Init_Standard(
		SS::Interface::Core::CommonContainers::IQueryResult*				_pQuery,
		SS::Core::Types::IndexationSearch::TQueryParametrizerSettings const&	_Settings);
	///	������ �������, ����������� ������� � �������
	///	\param[in]	pQuery	��������� ������
	void Init_AnswerMode(
		SS::Interface::Core::CommonContainers::IQueryResult*				_pQuery,
		SS::Core::Types::IndexationSearch::TQueryParametrizerSettings const&	_Settings);
	///	������ �������, �� ���������� �� OR. AND-���� ������
	void Init_AllOrMode(
		SS::Interface::Core::CommonContainers::IQueryResult*				_pQuery,
		SS::Core::Types::IndexationSearch::TQueryParametrizerSettings const&	_Settings);

	//
	//	��������������� ������
	//

	void ApplyWordAttributes(s_flagged_word &collection, flagged_word& currentWord);
	///	������������ ������� �� �����������, ��������� ���������� � ������������������� ����,
	///	� union-������ � �������������������.
	void	MakeWords(SS::Interface::Core::CommonContainers::IQueryResult* pQuery);
	///	��������� ����, ������������� �� [��������������][��������]
	mm_flagged_word			m_TransPos_Word;
	///	��������� ���������� ���������� � ������������� ���� �� �������������������
	///	� ��������������:
	///	[id �������������][id ������������������][������� � �������](��������� �� �����,
	///	���� ����� ��������� � m_TransPos_Word)
	mmm_pflagged_word		m_TransSeqPos_pWord;
	///	���������, ���������� ���������� ����� ���� �� ���� �������������: set(�����)
	///	��� ��������� ���� ����� ���������������
	s_flagged_word			m_AllUnique_Words;
	///	���������, ���������� ���������� ����� � ��������������, ����� ���������������
	ms_flagged_word			m_UniqueTrans_Words;
	///	���������, ���������� ���������� � union-������ � �������������������
	///	[id �������������][id ������������������](������ ��������� � �������� ��������� union-������ � ������������������)
	mmv_UWB					m_UnionBlocksInfo;
	///	��������� � ������� ��������� ���������� ��� ����� union-������, ����� ���������������
	s_flagged_word			m_AllUnionWords;
	///	��������� ������������� ��� ToStirng
	std::wstring			m_AsString;
	///	��������� ������������� ��� ToStirng
	std::wstring			m_AsStringRawQuery;

	///	������� �������
	void	Clear();
};

}
}
}
}


