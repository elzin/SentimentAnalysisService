#pragma once

namespace SS
{
	namespace Core
	{
		namespace Features
		{
			class CSyntaxAposterioriAnalyzer
			{
			public:
				/// �����������
				CSyntaxAposterioriAnalyzer(void);
				/// ����������
				~CSyntaxAposterioriAnalyzer(void);
			public:
				/// �������� ����� ������������� �������������� ������������ � �����
				/** 
					\param *pSyntaxFeatureAposteriori - ����� ������������� �������������� �������������
					\param piSyntaxInfo - �����, ������� �������� �������������� ������������� �������������� ��������������
				*/
				void Code(/*in*/SS::Core::Features::CSyntaxFeatureAposteriori *pSyntaxFeatureAposteriori, 
					/*out*/unsigned int* piSyntaxInfo) ;
				/// ��������� ������������� ����� � ����� ��������� �������������� ������������� 
				/** 
					\param iSyntaxInfo - �����, ������� �������� �������������� ������������� �������������� ��������������
					\param *pSyntaxFeatureAposteriori - ����� ������������� �������������� �������������
				*/
				void EnCode(
					/*in*/unsigned int iSyntaxInfo,	
					/*out*/SS::Core::Features::CSyntaxFeatureAposteriori *pSyntaxFeatureAposteriori);
			};
		};
	};
};