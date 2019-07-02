#include <atldbcli.h>

#include "..\ASSInterface\TLibBrokerTypes.h"
#include <sqloledb.h>

#pragma warning( disable : 4995 )

namespace SS
{
	namespace SyntaxConstructions
	{
		namespace SQL
		{
			namespace SQL_ACCESS
			{
				namespace ConstructionGroups
				{
					///	����� ��� ������� � ������� ����� �����������
					class CConstructionGroups
					{
					protected:						
						///������ �����������
						long m_lIDConstruction;
						///������ ������
						short m_shIDGroup;
					
					public:
						///���������� ����� �����������
						long GetIDConstruction()
						{
							return m_lIDConstruction;
						}
						///������������� ����� �����������
						void SetIDConstruction(long lIDConstruction)
						{
							m_lIDConstruction = lIDConstruction;
						}
						///���������� ����� ������ �����������
						short GetIDGroup()
						{
							return m_shIDGroup;
						}
						///������������� ����� ������ �����������
						void SetIDGroup(short shIDGroup)
						{
							m_shIDGroup = shIDGroup;
						}
					};

					/// ����� ��� �������� ����������� �� �������
					class CConstructionGroupsD : public CConstructionGroups
					{
					public:
						BEGIN_PARAM_MAP(CConstructionGroupsD)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(1, m_shIDGroup)							
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(2, m_lIDConstruction)							
						END_PARAM_MAP()		
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CConstructionGroupsD,
							_T("DELETE SyntaxConstructionGroups WHERE IDGroup = ? AND IDConstruction = ?"));	
					};

					/// ����� ��� ��������� ���� ����� ����������� �� �������
					class CConstructionGroupsSAll : public CConstructionGroups
					{
					public:
						BEGIN_COLUMN_MAP(CConstructionGroupsSAll)
							COLUMN_ENTRY(1, m_shIDGroup)		
							COLUMN_ENTRY(2, m_lIDConstruction)		
						END_COLUMN_MAP()
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CConstructionGroupsSAll,
							_T("SELECT IDGroup, SyntaxConstructionGroups.IDConstruction FROM SyntaxConstructionGroups, ConstructionsInUse where ConstructionsInUse.IDConstruction = SyntaxConstructionGroups.IDConstruction and Rem > 0 ORDER BY IDGroup, position"));	
					};

					/// ����� ��� ���������� ������ � ����������� � �������
					class CConstructionGroupsI : public CConstructionGroups
					{
					public:
						BEGIN_PARAM_MAP(CConstructionGroupsI)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(1, m_shIDGroup)							
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(2, m_lIDConstruction)							
						END_PARAM_MAP()		
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CConstructionGroupsI,
							_T("INSERT INTO SyntaxConstructionGroups (IDGroup, IDConstruction) VALUES (?,?)"));	
					};

					///����� ��� ������� � ������� SyntaxConstructionGroupsType
					class CConstructionGroupsType
					{
					protected:
						///������������� ������
						int m_iIdGroup;
						///����� �������
						int m_iAnalyseMode;
						///�������� �� ������� ���������� ���������
						int m_iResolveAmbiguity;

					public:
						///��������� ��������������
						int GetIdGroup()
						{
							return m_iIdGroup;
						}
						///�������� ��� �������
						int GetAnalyseMode()
						{
							return m_iAnalyseMode;
						}
						///��������� ���������� � �������������� � ���������� ��������
						int GetResolveAmbiguity()
						{
							return m_iResolveAmbiguity;
						}
					};
					
					///������ 
					class CConstructionGroupsTypeSAll : public CConstructionGroupsType
					{
					public:
						BEGIN_COLUMN_MAP(CConstructionGroupsTypeSAll)
							COLUMN_ENTRY(1, m_iIdGroup)							
							COLUMN_ENTRY(2, m_iAnalyseMode)							
							COLUMN_ENTRY(3, m_iResolveAmbiguity)	
						END_COLUMN_MAP()		
					
					public:
						///������
						DEFINE_COMMAND(CConstructionGroupsTypeSAll,
							_T("SELECT SyntaxConstructionGroupsType.IDGroup, AnalyseMode, AmbiguityResolve FROM SyntaxConstructionGroupsType, AmbiguityGroups WHERE SyntaxConstructionGroupsType.IDGroup = AmbiguityGroups.IDGroup ORDER BY AnalyseMode, Position") );	
					};



/////////////////////////////////////////////////////////////////////////////////////////
/*		������� ��� ������� � ������		*/
////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
					
					typedef CAccessor<CConstructionGroupsD> CAccessorConstructionGroupsD;
					typedef CPreparedCommand<CAccessorConstructionGroupsD> CPreparedConstructionGroupsD;

					typedef CAccessor<CConstructionGroupsSAll> CAccessorConstructionGroupsSAll;
					typedef CPreparedCommand<CAccessorConstructionGroupsSAll> CPreparedConstructionGroupsSAll;

					typedef CAccessor<CConstructionGroupsI> CAccessorConstructionGroupsI;
					typedef CPreparedCommand<CAccessorConstructionGroupsI> CPreparedConstructionGroupsI;

					typedef CAccessor<CConstructionGroupsTypeSAll> CAccessorConstructionGroupsTypeSAll;
					typedef CPreparedCommand<CAccessorConstructionGroupsTypeSAll> CPreparedConstructionGroupsTypeSAll;

				};
			};
		};
	};
};

#pragma warning( default : 4995 )
