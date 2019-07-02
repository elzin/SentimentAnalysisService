//UnitsExpert.h
#pragma once
#include "./BaseExpertConstruction.h"

namespace SS
{
namespace Syntax
{
namespace ExpertModel
{
	///������� ��� ����������� �� ����
	class CUnitsExpert : public CBaseExpertConstruction
	{
	private:
		///�������� ������ �����������
		inline void ExecuteAnalysis(PBLOCK pBlock);

	public:
		///�����������
		CUnitsExpert( SS::SyntaxConstructions::Types::CConstructionEx & oConstruction,
					  SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager,
					  SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams,
					  int iIdGroup, ESyntaxBase eBase )
					  :
					  CBaseExpertConstruction(oConstruction, pLoadManager, pAnalyseParams, iIdGroup, eBase) {};
		///����������
		~CUnitsExpert() {};
		///������ �� �����
		bool PassBoard(CBoard & oBoard, PBLOCK pBlock);
	};

}
}
}