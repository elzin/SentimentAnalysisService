#pragma once
#include "..\ASCInterface\IInterface.h"
#include "..\ASCInterface\ILinguisticProcessor.h"

// {81AFE03D-7E01-49af-B42D-745AB8C37133}
static const GUID	IID_ParametrizedQuery = 
{ 0x81afe03d, 0x7e01, 0x49af, { 0xb4, 0x2d, 0x74, 0x5a, 0xb8, 0xc3, 0x71, 0x33 } };

// {54AA4054-B51C-4efc-B66E-1CC2D7D35134}
static const GUID	CLSID_ParametrizedQuery = 
{ 0x54aa4054, 0xb51c, 0x4efc, { 0xb6, 0x6e, 0x1c, 0xc2, 0xd7, 0xd3, 0x51, 0x34 } };

namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			namespace NdxSE
			{
				class ISuperTemplate;
				class IBlock;
				class IVariant;
				class IWord;
				class ISequence;

				/// ������������������� ������ � ���������� ����������
				/**
					����������� �� IBase ��� ����������� �������� � ������� 
					������ LoadManager
				*/
				class IParametrizedQuery
					: public virtual SS::Interface::IBase
				{
				public:
					/// ������������� ��������, ��������������� ��������������� �����������
					///	\param[in]	pQuery			������
					///	\param[in]	pSearchParams	��������� ������
					virtual void Init(
						SS::Interface::Core::CommonContainers::IQueryResult*	pQuery,
						SS::Core::Types::IndexationSearch::TSearchParams*	pSearchParams) = 0;
					/// \return	��������� �� ������������������
					virtual ISuperTemplate* GetSuperTemplate() = 0;

					/// \return	���������� ���������
					virtual unsigned int GetVariantCount() = 0;
					///	\return	������� �� ������
					virtual IVariant* GetVariant(unsigned int uiIndex) = 0;

					///	\return ������� �� ���� � ����� ������� ������� ���� ������
					virtual BOOL	GetHasAnswers() = 0;

					///	\return ������� �� �����-����� �� ������� ������ (IQueryResult)
					virtual BOOL	GetHasUnionBlocks() = 0;

					///	\return	������� �� ���� ���� �������������� ����� �� ������� ������ (IQueryResult)
					///	(� ���� �������� ������ ����� �� ����������� ����� ��������������)
					virtual BOOL	GetHasNonObligatoryWords() = 0;

					///	������� � ���� ������ ��� ����������
					///	\return	���������� ��������� �� ���������� ������������� ������.
					virtual	const wchar_t*	ToString()=0;

					///	������� � ���� ������ �������������� ������
					///	\return	���������� ��������� �� ���������� ������������� ������.
					virtual	const wchar_t*	ToStringRawQuery(SS::Interface::Core::CommonContainers::IQueryResult* pQuery)=0;

					///	���������� ����� �������� �������������������� �������
					virtual void	DebugView() = 0;
					///	���������� ����� ������������������� ������� (������� ������)
					virtual void	DebugViewRawQuery(SS::Interface::Core::CommonContainers::IQueryResult* pQuery) = 0;
				};

				///	������ (������������������)
				/**
				�������� � ���� ����� ������ ��� ������ ��������� �����������:
					- "�"-���� ����. ����� � ���� ����� ������ �� "�", ��� ���� ��������� � "���"-������� �� "�"
					- ����� "���"-������. ����� � ������ ����� ����� ������ �� "�", ���� "���"-����� ���������� ����� ����� �� "���"
				*/
				class ISuperTemplate
				{
				public:
					///	\return	��������� �� AND-����
					virtual IBlock* GetANDBlock() = 0;
					///	\return ���������� OR-������
					virtual unsigned int GetORBlockCount() = 0;
					///	\return	OR-���� �� ������
					virtual IBlock* GetORBlock(unsigned int uiIndex) = 0;
					///	������� � ���� ������ ��� ����������
					///	\return	���������� ��������� �� ���������� ������������� ������.
					virtual	const wchar_t*	ToString()=0;
					///	���������� ����� �������
					virtual void	DebugView() = 0;
				};

				/// ���� ����, �������� � ������ (������������������)
				/**
					������ ���� �������� ����� ���� (IWord)
					����� ������ ����� ������ �� "�"
				*/
				class IBlock
				{
				public:
					///	\return	���������� ���� � �����
					virtual unsigned int GetWordCount() = 0;
					///	\return	����� �� ������
					virtual IWord* GetWord(unsigned int uiIndex) = 0;
					///	������� � ���� ������ ��� ����������
					///	\return	���������� ��������� �� ���������� ������������� ������.
					virtual	const wchar_t*	ToString()=0;
					///	���������� ����� �������
					virtual void	DebugView() = 0;
				};

				/// ����� �������
				/**
					C���� ������� ������������ ����� ������ ������ ����� ��������, 
					������� ������������� �� ����� �������,
					(��� ������� � ������ ����� ������� ������ �� "���")
				*/
				class IWord
				{
				public:
					///	��������� ���������� ��������������� ��������
					virtual unsigned int	GetMorphoIndexCount() = 0;
					///	��������� ���������������� ������� �� ������
					virtual unsigned int	GetMorphoIndex(unsigned int uiIndex) = 0;
					///	��������� ���������� �������������� ��������
					virtual unsigned int	GetSyntaxIndexCount() = 0;
					///	��������� ��������������� ������� �� ������
					virtual unsigned int	GetSyntaxIndex(unsigned int uiIndex) = 0;
					///	��������� ���������� ������������� ��������
					virtual unsigned int	GetSemanticIndexCount() = 0;
					///	��������� �������������� ������� �� ������
					virtual unsigned int	GetSemanticIndex(unsigned int uiIndex) = 0;

					///	\return ��������������� ��� �����
					virtual	float			GetLinguisticWeight() = 0;

					///	\return ���� ��������������
					virtual BOOL			GetObligatoryFlag() = 0;
					///	\return	���� ������
					virtual BOOL			GetAnswerFlag() = 0;

					///	\return	����� ����� (����� �������� � �����).
					///	������� �� NULL; ���� ������ ��� �� ��������� �� ""
					///	���� � �������� �� ������� ���������� ����� ���� ������ 
					///	��������� �������������, ��� ��� ����� �������������� � �����,
					///	������������� ����� "!"
					virtual const wchar_t*	GetAsString() = 0;

					///	������� � ���� ������ ��� ����������
					///	\return	���������� ��������� �� ���������� ������������� ������.
					virtual	const wchar_t*	ToString()=0;

					///	���������� ����� �������
					virtual void	DebugView() = 0;
				};

				/// "�������" �������
				/**
				������� ������� ������������ ����� ����� ������������������� 
				(ISequence) ����, ������� ����� ������������� � ������� ������ 
				� ������������ �������; ������ ������ ���� ������ �� "�"
				*/
				class IVariant
				{
				public:
					///	\return	����� �������������������
					virtual unsigned int GetSequenceCount() = 0;
					///	\return	������������������ �� ������
					virtual ISequence* GetSequence(unsigned int uiIndex) = 0;
					///	������� � ���� ������ ��� ����������
					///	\return	���������� ��������� �� ���������� ������������� ������.
					virtual	const wchar_t*	ToString()=0;
					///	���������� ����� �������
					virtual void	DebugView() = 0;
				};


				///	��������� ����������� Union-����
				///	� ������������������. Union-���� �� ����� ���� ������
				///	�.�. uiFirstWordNumber � uiLastWordNumber ��������� ��
				///	������ � ����� ������������
#pragma pack(push, 1)
				struct SUnionWordsBlockInSequence
				{
				public:
					///	����� ������� ����� Union-����� (������������)
					unsigned int	uiFirstWordNumber;
					///	����� ���������� ����� Union-����� (������������)
					unsigned int	uiLastWordNumber;
					///	Constructor
					SUnionWordsBlockInSequence(
						unsigned int uiFirst,
						unsigned int uiLast)
					:uiFirstWordNumber(uiFirst), uiLastWordNumber(uiLast)
					{}
				};
#pragma pack(pop)

				/// ������������������ ����
				/**
				������������������ ���� �������� � ���� �����, ������� � �������
				������ ������ ���� � ������������ �������
				�.�. �������� �����2 ����� �����1, � �����1 ����� �����0
				��� ��� ������ ����� ������ �� "�"
				������������������ ����� ��������� ��������� Union-������ ����
				������ � ����� ����� ������ ���������� � ���������� SUnionWordsInSequence
				������� ����� �������� �������� ISequence
				SUnionWordsBlockInSequence �������� �� ISequence � ������� ����������
				��������������� union-������ � ������������������
				*/
				class ISequence
					: public IBlock
				{
				public:
					///	\return	���������� Union-������
					virtual unsigned int GetUnionWordsBlocksCount() = 0;
					///	\return	��������� �������� union-����� �� ������
					virtual SUnionWordsBlockInSequence GetUnionWordsBlock(unsigned int uiIndex) = 0;
					///	���������� �������������� ����� ������-���� �����-����� � ��������� �����-����� � ������ ������
					///	\param[in]	uiIndex	����� ����� (��������� 0..(GetWordCount()-1))
					///	\param[out]	pUnion	���� ��������� ���������� � �����-����� � ������� ������������ �����
					///	���� NULL, �� ������ �� ��������� �� ���������.
					///	\return	true - ����� ���������� ������-���� �����-�����, �� ��������� pUnion ���������
					///	���������� �� ���� �����; false - ����� �� ����������� �������� ����� �����
					virtual BOOL	IsWordInUnion(unsigned int uiIndex, SUnionWordsBlockInSequence* pUnion) = 0;
					///	������� � ���� ������ ��� ����������
					///	\return	���������� ��������� �� ���������� ������������� ������.
					virtual	const wchar_t*	ToString()=0;
					///	���������� ����� �������
					virtual void	DebugView() = 0;
				};
			}
		}
	}
}