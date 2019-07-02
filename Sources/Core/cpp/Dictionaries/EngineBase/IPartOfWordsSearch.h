#pragma once

#include "../../ASCInterface/IInterface.h"
#include "../../ASCInterface/IDBMS.h"
#include "../../ASCInterface/defines.h"
#include "../../ASSInterface/ICommon.h"
#include "../../ASSInterface/TDBMS_Names.h"

USES_LOAD_MANAGER;

#include <string>
#include <vector>

namespace SS   {
	namespace Dictionary   {
		namespace Types   {

						/// �������� ���������� � ����� �����
			struct SPartOfWord   {

				/// ������� � ������� �����
				INT16  PositionInWord;

				/// ������������� ����� (IDSource)
				UINT32 Id;

				/// �����������
				SPartOfWord	() : PositionInWord(0), Id(0)	{}

			}; // struct SPartOfWord   {

			/// �������� ���������� � �������� ���������
			struct SHypothesisInfo   {

				/// ���������� ��������� c ������� ������ �������� � �����
				UINT8  MatchSymbols;

				/// ������������� ����� (IDSource)
				UINT32 Id;         

				/// �����������
				SHypothesisInfo	() : MatchSymbols(0), Id(0)	{}

			}; // struct SHypothesisInfo   {


		} // namespace Types   {



		namespace Core   {

			class IPartOfWordsSearch   {

				public:

					/// ������������� ���� � ������ ������ � ��������� �� ��������� ������� IDataTable (��� ������ Create())
					virtual BOOL Init(
						/// ���� � ������ ������
						CONST _TCHAR * pszPathToDataFiles,
						/// ��������� �� ��������� ������� IDataTable (��� ������ Create())
						SS::Interface::Core::DBMS::IDataTable * pIDataTable) = 0;

					/// C������ �����, ���������� ������ � ������ ������
					virtual BOOL Create(VOID) = 0;

					/// ���������/������������� �������
					virtual BOOL Load(VOID) = 0;

					/// ����������� ������
					virtual BOOL Clear(VOID) = 0;

					/// ����� � ������� ���� ��������� ������� � �����, ��� ���� ��������� ��������� ����� �����, � �������� � ������� ������ ��������� ��������� �������� � �����.
					virtual BOOL GetHypothesis(
						/// ������� ����� ��� ������
						IN CONST WCHAR * pwsPartOfWord,
						/// ������� � �����, � ������� ���������� ������ �����;  �.�. ���� ���������� ����� ����� �abc� ������ ����� 2, �ab� � 1 � �.�.
						IN INT iBeginPosition,
						/// ������ �������� ������, ����� ������� ���������� ������� reserve
						OUT std::vector< SS::Dictionary::Types::SHypothesisInfo > * p_v_HypothesisInfo,
						/// ����������� ���������� ����������, ��� ������� ����� ������������ � <p_v_SHypothesisInfo>
						IN INT iMinMatchSymbols) = 0;

					/// ���� ��� ��������� ���� ������ ���� � �� ��������
					virtual BOOL GetByForm(
						/// ������� ����� ��� ������
						IN CONST WCHAR * pwsPartOfWord,
						/// ������� � �����, � ������� ���������� ������ �����
						IN INT iBeginPosition,
						/// ������ �������� ������, ����� ������� ���������� ������� reserve
						OUT std::vector< SS::Dictionary::Types::SPartOfWord > * p_v_PartOfWord,
						/// �������� ������: �� ������ ����� ��� ���
						IN BOOL isCompleteWord = FALSE) = 0;

					/// ���� ����� ����� �� �������
					virtual BOOL GetFormById(
						/// ������ ��� ������
						IN UINT iID, 
						/// ��������� ����� �����
						OUT std::wstring * pwsPartOfWord) = 0;

			}; // class IPartOfWordsSearch

		} // namespace Core   {
	} // namespace Dictionary   {
} // namespace SS   {
