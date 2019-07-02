#pragma once



namespace SS
{
	namespace Core
	{
		namespace Features
		{
			/*	�����������/������������� �������������� ����������	*/
			class CSyntaxAnalyzer
			{
			public:
				/// �����������
				CSyntaxAnalyzer(void);
				/// ����������
				virtual ~CSyntaxAnalyzer(void){};
			public: //from SS::Core::SMISL::IAMConverterSyntax	
			/// �������� ����� ��������� �������������� ������������ � �����
			/** 
				\param oPartOfSpeechTypes - ����� ���� �����, ��� �������� ���������� ��������� �����������
				\param *pSyntaxFeature	- ������ ��������� �������������� �������������
				\param piSyntaxInfo	- �����, ������� �������� �������������� ��������� �������������� ��������������
				\return void
			*/
				HRESULT Code(
					/*in*/Types::PartOfSpeechTypes oPartOfSpeechTypes,
					/*in*/SS::Core::Features::CSyntaxFeatureApriori *pSyntaxFeature, 
					/*out*/unsigned int* iSyntaxInfo);
			/// ��������� ������������� ����� � ����� ��������� �������������� ������������� 
			/** 
				\param oPartOfSpeechTypes - ����� ���� �����, �������������� �������������� �������� ���������� ��������
				\param iSyntaxInfo - �������������� �������������� ��������������
				\param *pSyntaxFeature - ����� �������������� ��������� 
				\return void
			*/
				HRESULT EnCode(
				/*in*/ Types::PartOfSpeechTypes oPartOfSpeechTypes,
				/*in*/unsigned int iSyntaxInfo,	
				/*out*/SS::Core::Features::CSyntaxFeatureApriori *pSyntaxFeature);
			};
		};
	};	
};