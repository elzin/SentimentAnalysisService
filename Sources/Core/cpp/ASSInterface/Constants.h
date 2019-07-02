#pragma once

namespace SS
{
namespace Constants
{

	//������������ ����� ���� � ����� (������������ ���������� ������ � LexemeBoard-e)
	const int MAX_WORDS_IN_BLOCK = 50000;
	//���� ���-�� �������� � �����
	const int MAX_CHARS_IN_WORD = 50;
	//������������ ����� ���� � �����������
	const int MAX_WORDS_IN_SENTENCE = 255;
	//���� ����� ����������� � ���������
	const long MAX_SENTS_IN_PARAGRAPH = 256;

	//���� �������� �������������, ��� �������� ������������� ���������� �� ����
	const long MAX_NUMERIC_VALUE = 0x1000000;
	//���� �������� �������������, ������������� � �����
	const int MAX_FLOAT_NUMERIC_VALUE = 0x200000;
	//���� ���������� ����� � ������ �������������
	const int MAX_ZERO_COUNT = 8;

	//������������ �����, �������������� ��� ���
	const int MAX_YEAR_NUMBER = 2500;

	const int MIN_YEAR_NUMBER = 1800;

	//�����, �� ������� ���������� �������������
	const int RELEVANCE_MULTIPLIER = 1000000;
	//�����, �� ������� ���������� ������� ����������
	const int FUZZY_LEVEL_MULTIPLIER = 100000000;

	////����� DictionaryIndex-�, ������� ���� ���������� � �������������
	//const unsigned int SIGNIFICANT_INDEX_PART = 0x7FFFFFFF;

	namespace Dictionary
	{
		//����������� ����� ����� ���������� �������� ��� ����� ��������������
		const int MIN_MORPHO_RECOGNIZABLE_WORD_LEN_RUS = 4; //��� �������� �����
		const int MIN_MORPHO_RECOGNIZABLE_WORD_LEN_ENG = 3; //��� ����������� �����

		//����������� ���������� ��������� � ����� ���� � ���� ���� ��� ������� 
		//����� ������� ��� �� ������ ����� ����� ���������� ���������� �������
		const int MIN_COINCIDENCE_FOR_MORPHO_RECOGNIZABLE = 2;
	}
}
}
