#pragma once

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			///��� �������
			enum ParsingType
			{
				///��������������
				ptUndefined = -1,
				///���������� �������� (����������)
				ptMorphoResolveEnglish, 
				///������ ������� (����������)
				ptQueryAnalyzeEnglish,
				///������ ������ (����������)
				ptFullParsingEnglish,
				///���������� �������� (�������)
				ptMorphoResolveRussian, 
				///������ ������� (�������)
				ptQueryAnalyzeRussian,
				///������ ������ (�������)
				ptFullParsingRussian
			};
		}
	}
}