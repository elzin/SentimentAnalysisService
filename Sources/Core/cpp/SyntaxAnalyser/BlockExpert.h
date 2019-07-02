//BlockExpert.h
#pragma once
#include "./BaseExpertConstruction.h"

namespace SS
{
namespace Syntax
{
namespace ExpertModel
{
	///������� ��� ������ � �������
	class CBlockExpert : public CBaseExpertConstruction
	{
	private:
		///��������� �� ��������� �����������
		CBoard* m_pBoard;
		///���� � ������-���������
		PBLOCK m_pBlockDetect;
		///���� ������ �� ������
		PBLOCK m_pBlockRight;
		///���� ����� �� ������
		PBLOCK m_pBlockLeft;
		///������ ����������� ������
		std::list<PBLOCK> m_UnionBlocks; 

	private:
		///�������� ������ �����������
		inline void ExecuteAnalysis();
		///�������� ������ ������-��������
		inline bool ExecuteDetect(IObjectAnalyser* pObjectAnalyser);
		///�������� ������ ��������� ���������
		inline bool ExecuteOther(IObjectAnalyser* pObjectAnalyser);
		///���������� �����
		void UniteBlocks();

	public:
		///�����������
		CBlockExpert( SS::SyntaxConstructions::Types::CConstructionEx & oConstruction,
					  SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager,
					  SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams,
					  int IdGroup, ESyntaxBase eBase )
					  :
					  CBaseExpertConstruction(oConstruction, pLoadManager, pAnalyseParams, IdGroup, eBase),
					  m_pBoard(NULL), m_pBlockDetect(NULL), m_pBlockRight(NULL), m_pBlockLeft(NULL) {};
		///����������
		~CBlockExpert(){};
		///������ �� ����� 
		bool PassBoard(CBoard & oBoard, PBLOCK pBlock);
	};

}
}
}