#pragma once

#include "ExpertGroup.h"
#include "ParsingType.h"
#include "../ASSInterface/Construction.h"
#include "../ASCInterface/IInterface.h"
#include "../ASSInterface/ICommon.h"
#include "ExpertSemantic.h"

#include <vector>

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			///��������� ��������� � ��������� ����� ���������.
			class CGroupManager : public SS::Interface::Core::Common::ILoad
			{
			public:
				///��� - ��������� ���������� �� ������ ���������
				typedef std::vector<CExpertGroup*>				TCollection;
				///��� - �������� ���������
				typedef std::vector<CExpertGroup*>::iterator	TCollectionItr;

			private:
				///��������� �� ������
				bool m_bGroupsLoaded;
				///�������� ��������
				SS::Interface::Core::ResourceManagers::ILoadManager* m_pLoadManager;
				///��������� ������� ��� ������� �������. ����������� ��������, ���� ���, � ����� ����� �������
				CBaseExpert* m_pExpertResumeQuery;
				///������� ���������
				TCollection* m_pCurrentCollection;
				///������ ������� ������
				TCollectionItr m_itCurrentGroup;
				///��������� ��� ������������� ����������
				TCollection m_NullCollection;
				
				///������ ����� ��������� ��� ������� ����������� �����
				TCollection m_vAllGroupsEng;
				///������ ����� ��������� ��� ������� �������� �����
				TCollection m_vAllGroupsRus;
				///������ ������� ������� (���������� ����)
				TCollection m_vQueryGroupsEng;
				///������ ��� ������� ������� (���������� ����)
				TCollection m_vIndexationGroupsEng;
				///������ ������� ������� (������� ����)
				TCollection m_vQueryGroupsRus;
				///������ ��� ������� ������� (������� ����)
				TCollection m_vIndexationGroupsRus;

				///������ ���������� �������� ��� ���������� (���������� ����)
				TCollection m_vIndexationAmbGroupsEng;
				///������ ���������� �������� ���������� (������� ����)
				TCollection m_vIndexationAmbGroupsRus;
				
				std::map<ParsingType, TCollection*> m_mapCollections;

				///��� ������ (����������, ������ �������, ���������� ���������)
				ParsingType	m_ParsingType;
				///����������� ������
				SS::Core::CommonServices::CManagerLifeTimeForCriticalSection m_oManagerLifeTimeForCriticalSection;
				///��������� �������
				SS::Interface::Core::MainAnalyse::IAnalyseParams* m_pAnalyseParams;
				///��� �������������� ���
				ESyntaxBase m_eBase;
				///��������� ������� ��� ������ � ����������
				SS::Syntax::ExpertSemantic::CExpertSemantic m_oExpertSemantic;

			private:
				///�������� ����� ��� ����������� �����
				void LoadGroupsForLanguage( 
								SS::Interface::Core::SyntaxConstructions::ISyntaxConstructionsManager* pSyntaxConstructionsManager,
								TCollection & rAllGroups,
								TCollection & rAmbiguityGroups,
								TCollection & rQueryGroups,
								TCollection & rIndexationGroups );
				///���� ������ ���� ������������� �������
				bool DynamicAnalyse(bool bFragm, BoardElements::CBoard* pBoard);
				///������ ILoad
				/// ��������� � �������� ��� ��������� ������
				bool ToBinary(){ return false; }
				///��������� �����������
				bool Clear();

			public:
				///�����������
				CGroupManager();
				///����������
				~CGroupManager();
				///���������� LoadManager
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
				///��������� ��������� �� ������ ������
				CExpertGroup* GetFirstGroup();
				///��������� ��������� �� ��������� ������ (������ NULL ���� ����� ������ ���)
				CExpertGroup* GetNextGroup();
				///��������� �������������� ������ ����������� � ������������ ��������� �������
				void ParseSentenceDynamic(BoardElements::CBoard* pBoard, ParsingType pType);
				///��������� ���� �������
				void SetParsingType(ParsingType pType)
				{
					m_ParsingType = pType;
				}
				///������ ��� �������
				///���������� �������� �� ������ ������ (������ ����� ������ ��� �������)
				TCollectionItr GetBeginGroup();
				///���������� �������� �� ������ �� ��������� (������ ����� ������ ��� �������)
				TCollectionItr GetEndGroup();
				///������ ILoad
				///��������� �����������
				bool Load();
				///�������������� �����������
				bool ReLoad();
				///���������� AnalyseParams
				void SetAnalyseParams(SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams);
				///���������� ��� �������������� ���
				void SetBase(ESyntaxBase eBase) { m_eBase = eBase; };
			};

		}
	}
}