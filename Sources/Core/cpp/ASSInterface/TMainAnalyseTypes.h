#pragma once

namespace SS
{
namespace Core
{
namespace Types
{
	
	///����� �������
	enum EAnalyseMods
	{
		///����������
		eamIndexation = 0,
		///������ �������
		eamQuery = 1,
		///����� �� �������� ������
		eamStrictQuery,
		///����� �� �������� ������
		eamOnlyKeyWords,
		///������ ������� c ���������� ��������� ������
		eamQueryAndSearchString,
		/// ������ ������� � ������������ ����������
		eamRejectUnimportant,
		/// ����� ������ �� ������
		eamSearch
	};

	enum ERelevanceParams
	{
		erpUndefine,
		erpCalculateIndexesWeight 
	};

	enum ECurrentSystemMode
	{
		ecsmLocal,
		ecsmGlobal
	};

	enum ESyntaxAnalysisMode
	{
		esamFull,
		esamFullWithoutSyntaxTree,
		esamMorphologyAmbiguityResolve
	};
	


}
}
}
