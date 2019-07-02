#pragma once


#include "..\ASSInterface\ICoSeDi.h"
#include ".\connect.h"
#include ".\dboSemantic.h"

namespace SS
{
	namespace CoSeDi
	{
		namespace SQL
		{

			/// ����� ����������� ������ � ��������� ����
			class CSemanticIDSourceTree :
				public SS::CoSeDi::SQL::CConnect,
				public SS::Interface::Core::CoSeDi::ISemanticIDSourceTree
			{
			public:
				/// �����������
				/** 
					\param szBaseName - ��� ����
				*/
				CSemanticIDSourceTree(const wchar_t* szBaseName);
				/// ����������
				virtual ~CSemanticIDSourceTree(void);
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
			public: // function
				/// ������������� ��������� �� ������� �������� ����������
				/** 
					\param pLoadManager - ��������� �� ������� �������� ����������
					\return void
				*/	
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS_TRY;
	
					SS::Core::CommonServices::CBaseCoreClass::SetLoadManager(pLoadManager);
					InitConnection();

					SS_CATCH(L"");
				}
			public:
				/// ���������� �������� ��� �������� ������� ������
				/** 
					\param oFullIDSource - 
					\param oPrepared - �������� ��� ������ ���������� �� ������� ������
					\param plistOfFullIDSource
				*/
				void GetParent(	
					SS::CoSeDi::DataTypes::SFullIDSource& oFullIDSource,
					SS::CoSeDi::SQL::SQL_ACCESS::Semantic::CPreparedCSSemanticIDSourceTree& oPrepared,
					std::list<SS::CoSeDi::DataTypes::SFullIDSource>* plistOfFullIDSource);

			};
		};
			
		namespace DBMS
		{
			/// ����� ����������� ������ � ��������� ����
			class CSemanticIDSourceTree :
				public SS::CoSeDi::DBMS::CConnect,
				public SS::Interface::Core::CoSeDi::ISemanticIDSourceTree
			{
			public:
				/// �����������
				/** 
					\param szBaseName - ��� ����
				*/
				CSemanticIDSourceTree(const wchar_t* szBaseName);
				/// ����������
				virtual ~CSemanticIDSourceTree(void);
			public: // function
				/// ������������� ��������� �� ������� �������� ����������
				/** 
					\param pLoadManager - ��������� �� ������� �������� ����������
					\return void
				*/	
				void SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager)
				{
					SS::Core::CommonServices::CBaseCoreClass::SetLoadManager(pLoadManager);
					InitConnection();
				}
			private:
				bool InitConnection();
				
				void GetParents(std::list<SS::CoSeDi::DataTypes::SFullIDSource>* plistOfFullIDSource, SS::CoSeDi::DataTypes::SFullIDSource& oCurChild);
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

			protected:
				/*! \var SS::CoSeDi::DataTypes::SSemanticIDSourceTree m_SemanticIDSourceTree
				*  \brief     ��������� ��� ������� � ������� �������������� ������  �����
				*/
				SS::CoSeDi::DataTypes::SSemanticIDSourceTree m_SemanticIDSourceTree;

				/*! \var void       * TableRecord[4];
				*  \brief     ������ ���������� �� ������, ���������� ������ � DBMS �������
				*/
				void       * TableRecord[4];

				/*! \enum EFindMode
				*  \brief     ��������� ����, �� �������� ����� �������������� �����
				*/
				enum EFindMode
				{
					efmByIDParent,
					efmByIDChild
				};
			};
		};
	};
};