#pragma once

namespace SS
{
	namespace Semantic
	{


	enum CommonFeature
	{
		efcNon							=0,
		efcRepresentBecome				=0x01,//1 �������� ��������� represent or become
		efcSemanticVerb					=0x02,//3 ���������� ���������
		efcSemanticCommon				=0x04,//4 �� ���������� (�����) ���������
		efcSemanticName					=0x08,//5 ��������� �����
		efcSemanticMeasure				=0x10,//7 ��������� ����
		efcNoun							=0x20,//2 �������� ���������������
		efcAdverbAdjective				=0x40,//8 �������� ������� �/��� ��������������
		efcVerb							=0x80,//10 �������� ������
		efcPretext						=0x0100,//6 �������
		efcVerbWithPrep					=0x0200, //11 ����������� ���������� ������� � ���������
		efcDetectedNoun					=0x0400,//9 ���������� - ��� ��� ����� ���������������
		efcSemanticCitation				=0x0800,// ��������� ������
	};
///��������
	enum ERusFeature
	{
		efRNon							=0,
		efRCaseNominative				=0x01,//1 �������� ������������ �����
		efRCaseInstrumental				=0x02,//11 ������������ �����
		efRCaseAccusative				=0x04,//12 ����������� �����
		efRCaseGenetive					=0x08,//14 ����������� �����
		efRCaseLocative					=0x0100, //25 ����������
		efRCaseDative					=0x0200,  //26 ��������� �����
		efRCaseAll						=0x0400, //20 ����� �������� ��� ������, �� �� ���������� ����� (��� ��������)
		efRAnimate						=0x0800,//18 �������� �������������
		efRPassive						=0x1000,//19 �������� ������ (������ ����� � ������������� ������ ��� ������� ������������� ���������)
		efRVerbDeepr					=0x2000,  //28 ������������
	};
	enum EEngFeature
	{
		efENon							=0,
		efEDetPronounAdjective			=0x01,//3 ������������ ��� ����������� pronounAdjective
		efEClearProper					=0x02,//4 ��� ������� �� ������� ��� �����������
		efENotOnlyNoun					=0x04,//6 �������� �� ������ ���������������
		efECaseGenetive					=0x08,//14 ����������� �����
		efEDNounPrep					=0x10, //21 ��������������� (����)
		efEDNounNominative				=0x20, //22 ��������������� ��� �������� (����)
		efEDNounPrepOF					=0x40, //23 ��������������� � ��������� of (����)
		efEVerbParticiplePresent		=0x80,  //27 ��������� ���������� �������
		efEVerbInfinitive				=0x1000  //29 ������������
	};

	///����������� ��� �����(�����)
	enum TSpecialUnitType{
		ustUndefined,
		ustEndSentence,	//����� - ����� �����������
		ustInitials,	//��������
		ustFamily,		//�������
		ustMeasureUnit, //������� ���������
		ustShortering,  //���������� ���� �.�.
		ustPunkt,		//����� � ������ ������
		ustWordCombination,		//���������� ���� 0 
		ustWordCombinationLex,		//���������� ���� New lexical unit 
		ustURL,			//url	
		ustDate,			//���� 
		ustTime,			//�����
		ustAbbreviation,//������������
		ustAcronim,		//�������
		ustNumeral,		//������������
		ustComplexProperName,	//��������� ��� �����������
		ustAux,
		ustCitation,				//������
		ustPlaceSpecification,	//��������� ����� ���� - �����,������
		ustProperGroup,			//������ ���� � ������� ����� �� ����������� ����� �� ������ ����� �������
		ustNewWordContainer		//���� �������� ����� ��� �������
	};
	///// �������������� ��� 
	//enum TSyntaxUnitType{
	//	usntUndefined,
	//	usntQuestionGroup,	/// �������������� ������
	//	usntEntity1,		/// ������ ��������
	//	usntEntity2,		/// ������ ��������
	//	usntVerb,			/// ������
	//	usntPrepositionGroup,	/// 
	//	usntMeasure,		/// �������������� ����
	//	usntComplexWord,		
	//	usntDateSyntax,			/// �������������� �������
	//	usntTimeSyntax,			///�����  � ���������
	//	usntComplexProperNameSyntax,	///��������� ��� ����������� � ���������
	//	usntSubjectComplement,			/// ���������
	//	usntObjectSubject				/// �������/������ 
	//};


	}
}