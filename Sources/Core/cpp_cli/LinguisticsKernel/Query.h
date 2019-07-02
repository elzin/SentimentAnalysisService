#pragma once


#include "..\..\cpp\ASCInterface/ILinguisticProcessor.h"


#include "..\..\cpp\ASSInterface/ILinguisticProcessorEx.h"

#include "..\..\cpp\ASSInterface/ILexicaLib.h"
#include "..\..\cpp\ASSInterface/ISyntaxAnalyzer.h"
#include "..\..\cpp\ASSInterface/ISemanticAnalyze.h"
#include "..\..\cpp\ASSInterface/IRev.h"
#include "..\..\cpp\MainAnalyse\LinguisticQuery.h"

namespace SS
{
namespace LinguisticProcessor
{

class CQuery : public SS::LinguisticProcessor::CLinguisticQuery
{	
public:
	CQuery(void);
	~CQuery(void);
public:
	/// ������ ������� ������������ ��� ������ ��� ��������� ������� � ���������� ���������� �� ������������ ������� 
	/**
	������������ ��� ������ ������� � ��������� �����������, ����������� �� ���� ����������� ��������� ������� SS
	*/
	SS::Interface::Core::BlackBox::IText* GenerateQueryIText(
		/// ��������� ������
		SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams
		/// ��������� ������� �������
		, SS::Core::Types::IndexationSearch::TQueryParams* pQueryParams
		);
public:
	/// ������ ������� ������������ ��� ������ ��� ��������� ������� � ���������� ���������� �� ������������ ������� 
	/**
	������������ ��� ������ ������� � ��������� �����������, ����������� �� ���� ����������� ��������� ������� SS
	*/
	SS::Interface::Core::BlackBox::Query::IQuery* GenerateQueryIQuery(
		/// ��������� ������
		SS::Core::Types::IndexationSearch::TSearchParams* pSearchParams
		/// ��������� ������� �������
		, SS::Core::Types::IndexationSearch::TQueryParams* pQueryParams
		);
};
}
}