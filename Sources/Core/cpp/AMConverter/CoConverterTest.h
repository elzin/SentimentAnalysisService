#pragma once

#ifdef _SS_UNITTESTS


#include "./CoConverter.h"


namespace SS
{
	namespace UnitTests
	{
		namespace AMConverter
		{
			
			/// �������� �� ������������ ���������������� ����������
			class CCoConverterTest 
			{

			public:
				/// ��������� ������������ ����������� ������ ������������� ������������� � ������������������ �����
				void TestMorpho(void);
				bool TestSemanticSetXML(void);
			};

			
		};

	};
};

#endif