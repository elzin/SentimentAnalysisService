#pragma once

#include "..\ASSInterface\ICoSeDi.h"
#include ".\SemanticIDSourceTree.h"


namespace SS
{
	namespace CoSeDi
	{
		namespace SQL
		{
			class CSemanticIDSourceTreeEx : 
				public SS::Interface::Core::CoSeDi::ISemanticIDSourceTree,
				public SS::Core::CommonServices::CBaseCoreClass
			{
			public:
				CSemanticIDSourceTreeEx(void);
				~CSemanticIDSourceTreeEx(void);

			public:

				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS_TRY
					{
						SS::Core::CommonServices::CBaseCoreClass::SetLoadManager( pLoadManager);

						m_oSemanticIDSourceTreeRus.SetLoadManager( pLoadManager);
						m_oSemanticIDSourceTreeEng.SetLoadManager( pLoadManager);
					}
					SS_CATCH(L"");
				}

			public:
				/// ���������� ���� ��������� �������� �������
				/** 
					\param plistOfFullIDSource - ��������� �� ������, ���������� ������� ���������
				*/
				void GetParents(std::list<SS::CoSeDi::DataTypes::SFullIDSource>* plistOfFullIDSource);

				/// ��������� ������� ���� (��������, �������)
				void Add();

				/// ������� ���� ������� (��������, �������)
				void Delete();
			private:
				SS::CoSeDi::SQL::CSemanticIDSourceTree m_oSemanticIDSourceTreeRus;
				SS::CoSeDi::SQL::CSemanticIDSourceTree m_oSemanticIDSourceTreeEng;
			};

		};

		namespace DBMS
		{
			class CSemanticIDSourceTreeEx : 
				public SS::Interface::Core::CoSeDi::ISemanticIDSourceTree,
				public SS::Core::CommonServices::CBaseCoreClass
			{
			public:
				CSemanticIDSourceTreeEx(void);
				~CSemanticIDSourceTreeEx(void);
			public:

				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS_TRY
					{
						SS::Core::CommonServices::CBaseCoreClass::SetLoadManager( pLoadManager);

						m_oSemanticIDSourceTreeRus.SetLoadManager( pLoadManager);
						m_oSemanticIDSourceTreeEng.SetLoadManager( pLoadManager);

					}
					SS_CATCH(L"")
				}

			public:
				/// ���������� ���� ��������� �������� �������
				/** 
					\param plistOfFullIDSource - ��������� �� ������, ���������� ������� ���������
				*/
				void GetParents(std::list<SS::CoSeDi::DataTypes::SFullIDSource>* plistOfFullIDSource);

				/// ��������� ������� ���� (��������, �������)
				void Add();

				/// ������� ���� ������� (��������, �������)
				void Delete();
			private:
				SS::CoSeDi::SQL::CSemanticIDSourceTree m_oSemanticIDSourceTreeRus;
				SS::CoSeDi::SQL::CSemanticIDSourceTree m_oSemanticIDSourceTreeEng;
			};

		};
	};
};