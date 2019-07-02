#pragma once

#include <atldbcli.h>

#include "..\ASSInterface\TLibBrokerTypes.h"
#include <sqloledb.h>

#pragma warning( disable : 4995 )

namespace SS
{
	namespace CoSeDi
	{
		namespace SQL
		{
			namespace SQL_ACCESS
			{
				namespace Semantic
				{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*	������������� �������� ����	*/
					
					/// ����� ��� ������� � ������� ���������� ������������� �������� ����
					class CAccessSemanticIDSourceTree
					{
					protected:
						/*! \var int m_lIDSourceParent
						*  \brief     ������ ������ ��������
						*/
						int m_lIDSourceParent;
						/*! \var int m_lIDSourceChild
						*  \brief     ������ ������ �������
						*/
						int m_lIDSourceChild;
						/*! \var short m_shDictionaryNumberParent
						*  \brief     ������ ������� ��������
						*/
						short m_shDictionaryNumberParent;
						/*! \var short m_shDictionaryNumberChild
						*  \brief     ������ ������� �������
						*/
						short m_shDictionaryNumberChild;
					public:
						/// ������������� ������ ������ ��������
						void SetIDSourceParent(int lIDSourceParent)
						{
							m_lIDSourceParent = lIDSourceParent;
						}
						/// ������������� ������ ������ �������
						void SetIDSourceChild(int lIDSourceChild)
						{
							m_lIDSourceChild = lIDSourceChild;
						}
						/// ������������� ������ ������� ��������
						void SetDictionaryNumberParent(short shDictionaryNumberParent)
						{
							m_shDictionaryNumberParent = shDictionaryNumberParent;
						}
						/// ������������� ������ ������� �������
						void SetDictionaryNumberChild(short shDictionaryNumberChild)
						{
							m_shDictionaryNumberChild = shDictionaryNumberChild;
						}
						/// ���������� ������ ������ ��������
						int GetIDSourceParent()
						{
							return m_lIDSourceParent;
						}
						/// ���������� ������ ������ �������
						int GetIDSourceChild()
						{
							return m_lIDSourceChild;
						}
						/// ���������� ������ ������� ��������						
						short GetDictionaryNumberParent()
						{
							return m_shDictionaryNumberParent;
						}
						/// ���������� ������ ������� �������
						short GetDictionaryNumberChild()
						{
							return m_shDictionaryNumberChild;
						}
					};

					/// ����� ��� ���������� ������� � ������� ������������� �������� ����
					class CISemanticIDSourceTree : public CAccessSemanticIDSourceTree
					{
					public:
						BEGIN_PARAM_MAP(CISemanticIDSourceTree)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(1, m_shDictionaryNumberParent)							
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(2, m_lIDSourceParent)							
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(3, m_shDictionaryNumberChild)							
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(4, m_lIDSourceChild)							
						END_PARAM_MAP()		
					public:
						/*	��������������� ������	*/
						DEFINE_COMMAND(CISemanticIDSourceTree,
_T("INSERT SemanticIDSourceTree (DictionaryNumberParent, IDSourceParent, DictionaryNumberChild, IDSourceChild) VALUES(?,?,?,?)"));	
					
					};

					/// ����� ��� �������� ������� �� ������� ������������� �������� ����
					class CDSemanticIDSourceTree : public CAccessSemanticIDSourceTree
					{
					public:
						BEGIN_PARAM_MAP(CDSemanticIDSourceTree)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(1, m_shDictionaryNumberParent)							
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(2, m_lIDSourceParent)							
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(3, m_shDictionaryNumberChild)							
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(4, m_lIDSourceChild)							
						END_PARAM_MAP()		
					public:
						/*	��������������� ������	*/
						DEFINE_COMMAND(CDSemanticIDSourceTree,
_T("DELETE SemanticIDSourceTree WHERE DictionaryNumberParent = ? AND IDSourceParent = ? AND DictionaryNumberChild = ? AND IDSourceChild = ?"));	
					
					};

					/// ����� ��� ��������� ������� �� ������� ������������� �������� ���� �� ������� �������
					class CSSemanticIDSourceTree : public CAccessSemanticIDSourceTree
					{
				
					public:
						BEGIN_COLUMN_MAP(CSSemanticIDSourceTree)
							COLUMN_ENTRY(1, m_shDictionaryNumberParent)		
							COLUMN_ENTRY(2, m_lIDSourceParent)	
							COLUMN_ENTRY(3, m_shDictionaryNumberChild)	
							COLUMN_ENTRY(4, m_lIDSourceChild)								
						END_COLUMN_MAP()
					public:
						BEGIN_PARAM_MAP(CSSemanticIDSourceTree)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(1, m_shDictionaryNumberChild)							
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(2, m_lIDSourceChild)							
						END_PARAM_MAP()		
					public:
						/*	��������������� ������	*/
						DEFINE_COMMAND(CSSemanticIDSourceTree,
_T("SELECT DictionaryNumberParent, IDSourceParent, DictionaryNumberChild, IDSourceChild FROM SemanticIDSourceTree WHERE DictionaryNumberChild = ? AND IDSourceChild = ?"));	
					
					};

					/// ����� ��� ��������� ������� �� ������� ������������� �������� ����
					class CSAllSemanticIDSourceTree : public CAccessSemanticIDSourceTree
					{
				
					public:
						BEGIN_COLUMN_MAP(CSAllSemanticIDSourceTree)
							COLUMN_ENTRY(1, m_shDictionaryNumberParent)		
							COLUMN_ENTRY(2, m_lIDSourceParent)	
							COLUMN_ENTRY(3, m_shDictionaryNumberChild)	
							COLUMN_ENTRY(4, m_lIDSourceChild)								
						END_COLUMN_MAP()
					public:
						/*	��������������� ������	*/
						DEFINE_COMMAND(CSAllSemanticIDSourceTree,
		_T("SELECT DictionaryNumberParent, IDSourceParent, DictionaryNumberChild, IDSourceChild FROM SemanticIDSourceTree"));	
					
					};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
					/*	������������� ���������� � ������ �����	*/
				
				/// ����� ����������� ���� ������� Semantics � ������������ ��� ������� �� �����
				class CAccessorTSemantics 
				{
				protected:	
					/*! \var unsigned short	m_ushDictionaryNumber
					*  \brief     ����� �������
					*/
					unsigned short	m_ushDictionaryNumber;
					/*! \var unsigned short	m_ushDictionaryNumber
					*  \brief     ������ ������ �����
					*/
					unsigned int	m_uiIDSource;
					/*! \var unsigned short	m_ushDictionaryNumber
					*  \brief     ������ �������������� ������ �����
					*/
					int	m_iClass;									
				public:	
					/// ���������� ������ ������ �����
					unsigned int	GetIDSource()
					{
						return m_uiIDSource;
					}
					/// ������������� ������ ������ �����
					void	SetIDSource(unsigned int uiIDSource)
					{
						m_uiIDSource = uiIDSource;
					}	
					/// ���������� ������ ������� �����
					unsigned short	GetDictionaryNumber()
					{
						return m_ushDictionaryNumber;
					}
					/// ������������� ������ ������� �����
					void	SetDictionaryNumber(unsigned short ushDictionaryNumber)
					{
						m_ushDictionaryNumber = ushDictionaryNumber;
					}
					/// ���������� ������ �������������� ������ �����
					int	GetClass()
					{
						return m_iClass;
					}
					/// ������������� ������ �������������� ������ �����
					void	SetClass(unsigned int iClass)
					{
						m_iClass = iClass;
					}					
				};

				/// ����� ��� �������� ������ �� ������� Semantics �� ������� �����
				class CAccessDTSemantics : public CAccessorTSemantics
				{
				public:
					BEGIN_PARAM_MAP(CAccessDTSemantics)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)
						COLUMN_ENTRY(1, m_iClass)										
						SET_PARAM_TYPE(DBPARAMIO_INPUT)
						COLUMN_ENTRY(2, m_ushDictionaryNumber)										
						SET_PARAM_TYPE(DBPARAMIO_INPUT)
						COLUMN_ENTRY(3, m_uiIDSource)																						
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessDTSemantics, 
						_T("DELETE FROM Semantics WHERE SemanticClass = ? AND DictionaryNumber = ? AND IDSource = ?"));	
				};
				
				/// ����� ��� ���������� ������ � ������� Semantics 
				class CAccessITSemanticsAddWord : public CAccessorTSemantics
				{
				public:
					BEGIN_PARAM_MAP(CAccessITSemanticsAddWord)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(1, m_iClass)																
						SET_PARAM_TYPE(DBPARAMIO_INPUT)
						COLUMN_ENTRY(2, m_ushDictionaryNumber)																
						SET_PARAM_TYPE(DBPARAMIO_INPUT)
						COLUMN_ENTRY(3, m_uiIDSource)																						
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessITSemanticsAddWord,
						_T("INSERT Semantics (SemanticClass, DictionaryNumber, IDSource) VALUES (?,?,?)"));	
				};

				/// ����� ��� ��������� ������ �� ������� Semantics �� ������� �������������� ������
				class CAccessSTSemanticsGetByClass : public CAccessorTSemantics
				{
				public:
					BEGIN_COLUMN_MAP(CAccessSTSemanticsGetByClass)
						COLUMN_ENTRY(1, m_iClass)										
						COLUMN_ENTRY(2, m_ushDictionaryNumber)										
						COLUMN_ENTRY(3, m_uiIDSource)																
					END_COLUMN_MAP()
				public:
					BEGIN_PARAM_MAP(CAccessSTSemanticsGetByClass)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(1, m_iClass)																
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessSTSemanticsGetByClass, 
						_T("SELECT SemanticClass, DictionaryNumber, IDSource FROM Semantics WHERE SemanticClass = ?"));	
				};

				/// ����� ��� ��������� ������ �� ������� Semantics �� ������� �����				
				class CAccessSTSemanticsGetByIDSource : public CAccessorTSemantics
				{
				public:
					BEGIN_COLUMN_MAP(CAccessSTSemanticsGetByIDSource)
						COLUMN_ENTRY(1, m_iClass)										
						COLUMN_ENTRY(2, m_ushDictionaryNumber)										
						COLUMN_ENTRY(3, m_uiIDSource)																
					END_COLUMN_MAP()
				public:
					BEGIN_PARAM_MAP(CAccessSTSemanticsGetByIDSource)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(1, m_ushDictionaryNumber)																
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(2, m_uiIDSource)																						
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessSTSemanticsGetByIDSource,
						_T("SELECT SemanticClass, DictionaryNumber, IDSource FROM Semantics WHERE DictionaryNumber = ? AND IDSource = ?"));	
				};

				/// ����� ��� ��������� ������� �� ������� Semantics 				
				class CAccessSFullTSemantics : public CAccessorTSemantics
				{
				public:
					BEGIN_COLUMN_MAP(CAccessSFullTSemantics)
						COLUMN_ENTRY(1, m_iClass)										
						COLUMN_ENTRY(2, m_ushDictionaryNumber)										
						COLUMN_ENTRY(3, m_uiIDSource)																										
					END_COLUMN_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessSFullTSemantics,
						_T("SELECT SemanticClass, DictionaryNumber, IDSource  FROM Semantics"));	
				};

				/// ����� ��� ��������� ������� �� ������� SemanticsExtra 				
				class CAccessSFullTSemanticsExtra : public CAccessorTSemantics
				{
				public:
					BEGIN_COLUMN_MAP(CAccessSFullTSemanticsExtra)
						COLUMN_ENTRY(1, m_iClass)										
						COLUMN_ENTRY(2, m_ushDictionaryNumber)										
						COLUMN_ENTRY(3, m_uiIDSource)																										
					END_COLUMN_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessSFullTSemanticsExtra,
						_T("SELECT SemanticClass, DictionaryNumber, IDSource  FROM SemanticsExtra"));	
				};

	/*************************************************/

				/// ����� ��� �������� ������ �� ������� Semantics �� ������� �����
				class CAccessDTSemanticsSynonims : public CAccessorTSemantics
				{
				public:
					BEGIN_PARAM_MAP(CAccessDTSemanticsSynonims)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)
						COLUMN_ENTRY(1, m_iClass)										
						SET_PARAM_TYPE(DBPARAMIO_INPUT)
						COLUMN_ENTRY(2, m_ushDictionaryNumber)										
						SET_PARAM_TYPE(DBPARAMIO_INPUT)
						COLUMN_ENTRY(3, m_uiIDSource)																						
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessDTSemanticsSynonims, 
						_T("DELETE FROM SemanticsSynonims WHERE SemanticClass = ? AND DictionaryNumber = ? AND IDSource = ?"));	
				};
				
				/// ����� ��� ���������� ������ � ������� Semantics 
				class CAccessITSemanticsSynonimsAddWord : public CAccessorTSemantics
				{
				public:
					BEGIN_PARAM_MAP(CAccessITSemanticsSynonimsAddWord)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(1, m_iClass)																
						SET_PARAM_TYPE(DBPARAMIO_INPUT)
						COLUMN_ENTRY(2, m_ushDictionaryNumber)																
						SET_PARAM_TYPE(DBPARAMIO_INPUT)
						COLUMN_ENTRY(3, m_uiIDSource)																						
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessITSemanticsSynonimsAddWord,
						_T("INSERT SemanticsSynonims (SemanticClass, DictionaryNumber, IDSource) VALUES (?,?,?)"));	
				};

				/// ����� ��� ��������� ������ �� ������� Semantics �� ������� �������������� ������
				class CAccessSTSemanticsSynonimsGetByClass : public CAccessorTSemantics
				{
				public:
					BEGIN_COLUMN_MAP(CAccessSTSemanticsSynonimsGetByClass)
						COLUMN_ENTRY(1, m_iClass)										
						COLUMN_ENTRY(2, m_ushDictionaryNumber)										
						COLUMN_ENTRY(3, m_uiIDSource)																
					END_COLUMN_MAP()
				public:
					BEGIN_PARAM_MAP(CAccessSTSemanticsSynonimsGetByClass)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(1, m_iClass)																
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessSTSemanticsSynonimsGetByClass, 
						_T("SELECT SemanticClass, DictionaryNumber, IDSource FROM SemanticsSynonims WHERE SemanticClass = ?"));	
				};

				/// ����� ��� ��������� ������ �� ������� Semantics �� ������� �����				
				class CAccessSTSemanticsSynonimsGetByIDSource : public CAccessorTSemantics
				{
				public:
					BEGIN_COLUMN_MAP(CAccessSTSemanticsSynonimsGetByIDSource)
						COLUMN_ENTRY(1, m_iClass)										
						COLUMN_ENTRY(2, m_ushDictionaryNumber)										
						COLUMN_ENTRY(3, m_uiIDSource)																
					END_COLUMN_MAP()
				public:
					BEGIN_PARAM_MAP(CAccessSTSemanticsSynonimsGetByIDSource)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(1, m_ushDictionaryNumber)																
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(2, m_uiIDSource)																						
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessSTSemanticsSynonimsGetByIDSource,
						_T("SELECT SemanticClass, DictionaryNumber, IDSource FROM SemanticsSynonims WHERE DictionaryNumber = ? AND IDSource = ?"));	
				};

				/// ����� ��� ��������� ������� �� ������� Semantics 				
				class CAccessSFullTSemanticsSynonims : public CAccessorTSemantics
				{
				public:
					BEGIN_COLUMN_MAP(CAccessSFullTSemanticsSynonims)
						COLUMN_ENTRY(1, m_iClass)										
						COLUMN_ENTRY(2, m_ushDictionaryNumber)										
						COLUMN_ENTRY(3, m_uiIDSource)																										
					END_COLUMN_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessSFullTSemanticsSynonims,
						_T("SELECT SemanticClass, DictionaryNumber, IDSource  FROM SemanticsSynonims"));	
				};

/////////////////////////////////////////////////////////////////////////////////////////
/* ������ � ������� ������������� ������� */

				/// ����� ����������� ���� �������	SemanticClassesTree � ������������ ��� ��������� ������ �� ���			
				class CAccessorTSemanticsTree 
				{
				protected:	

					/*! \var unsigned int	m_ushIDClass
					*  \brief     ������ �������������� ������
					*/
					unsigned int	m_ushIDClass;

					/*! \var unsigned int	m_ushIDParent
					*  \brief   ������ ������, ����������� ��������� ��� ��������
					*/
					unsigned int	m_ushIDParent;

					/*! \var char				m_chName
					*  \brief     ��� �������������� ������
					*/
					wchar_t				m_chName[128];				

					/*! \var char				m_chShortName
					*  \brief     �������� ��� �������������� ������
					*/
					wchar_t				m_chShortName[128];				

					/*! \var unsigned int				m_uiColor
					*  \brief     ����  �������������� ������
					*/
					unsigned int 		m_uiColor;				

				public:	
					/// ���������� ������ ������
					unsigned int	GetIDClass()
					{
						return m_ushIDClass;
					}
					/// ������������� ������ ������
					void	SetIDClass(unsigned int ushIDClass)
					{
						m_ushIDClass = ushIDClass;
					}	
					/// ���������� ������ ������, ����������� ��������� ��� �������
					unsigned int	GetIDParent()
					{
						return m_ushIDParent;
					}
					/// ������������� ������ ������, ����������� ��������� ��� �������
					void	SetIDParent(unsigned int ushIDParent)
					{
						m_ushIDParent = ushIDParent;
					}	
					/// ���������� ��� �������������� ������
					wchar_t*	GetName()
					{
						return m_chName;
					}
					/// ������������� ��� �������������� ������
					void	SetName(const wchar_t * chName)
					{
						wcscpy(m_chName, chName);	
						return;
					}
					/// ���������� �������� ��� �������������� ������
					wchar_t*	GetShortName()
					{
						return m_chShortName;
					}
					/// ���������� ���� �������������� ������
					unsigned int	GetColor()
					{
						return m_uiColor;
					}
				};


				/// ����� ��� ������ �� ����� �������������� ������
				class CAccessTSemanticsTreeByName : public CAccessorTSemanticsTree
				{
				public:
					BEGIN_COLUMN_MAP(CAccessTSemanticsTreeByName)
						COLUMN_ENTRY(1, m_ushIDClass)										
						COLUMN_ENTRY(2, m_ushIDParent)										
						COLUMN_ENTRY(3, m_chName)										
					END_COLUMN_MAP()
				public:
					BEGIN_PARAM_MAP(CAccessTSemanticsTreeByName)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(1, m_chName)																						
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessTSemanticsTreeByName,
						_T("SELECT * FROM SemanticClassesTree WHERE Name = ?"));	
				};


				/// ����� ��� ������ �� ������� �������������� ������
				class CAccessTSemanticsTreeByClass : public CAccessorTSemanticsTree
				{
				public:
					BEGIN_COLUMN_MAP(CAccessTSemanticsTreeByClass)
						COLUMN_ENTRY(1, m_ushIDClass)										
						COLUMN_ENTRY(2, m_ushIDParent)										
						COLUMN_ENTRY(3, m_chName)										
					END_COLUMN_MAP()
				public:
					BEGIN_PARAM_MAP(CAccessTSemanticsTreeByClass)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(1, m_ushIDClass)																						
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessTSemanticsTreeByClass,
						_T("SELECT * FROM SemanticClassesTree WHERE IDClass = ?"));	
				};

				/// ����� ��� ������ �������������� ������	�� ������� ��������  
				class CAccessTSemanticsTreeByParent : public CAccessorTSemanticsTree
				{
				public:
					BEGIN_COLUMN_MAP(CAccessTSemanticsTreeByParent)
						COLUMN_ENTRY(1, m_ushIDClass)										
						COLUMN_ENTRY(2, m_ushIDParent)										
						COLUMN_ENTRY(3, m_chName)										
					END_COLUMN_MAP()
				public:
					BEGIN_PARAM_MAP(CAccessTSemanticsTreeByParent)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(1, m_ushIDParent)																						
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessTSemanticsTreeByClass,
						_T("SELECT * FROM SemanticClassesTree WHERE IDParent = ?"));	
				};

				/// ����� ��� �������� ������ �� ������� SemanticClassesTree �� ������� ������������� ������
				class CAccessDTSemanticsTree : public CAccessorTSemanticsTree
				{
				public:
					BEGIN_PARAM_MAP(CAccessDTSemanticsTree)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(1, m_ushIDClass)																						
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessDTSemanticsTree,
						_T("DELETE FROM SemanticClassesTree WHERE IDClass = ?"));	
				};

				/// ����� ��� ���������� ���������� � ������� SemanticClassesTree
				class CAccessITSemanticsTreeCreateClass : public CAccessorTSemanticsTree
				{
				public:
					BEGIN_PARAM_MAP(CAccessITSemanticsTreeCreateClass)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(1, m_ushIDClass)	
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(2, m_ushIDParent)	
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(3, m_chName)	
					END_PARAM_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessITSemanticsTreeCreateClass,
						_T("INSERT INTO SemanticClassesTree VALUES( ?, ?, ?)"));	
				};

				/// ����� ��� ��������� �� SemanticClassesTree ������������� ������� �������������� ������
				class CAccessSTSemanticsTreeGetMaxID : public CAccessorTSemanticsTree
				{
				public:
					BEGIN_COLUMN_MAP(CAccessSTSemanticsTreeGetMaxID)
						COLUMN_ENTRY(1, m_ushIDClass)																									
					END_COLUMN_MAP()				
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessSTSemanticsTreeGetMaxID,
						_T("SELECT MAX(IDClass) FROM SemanticClassesTree HAVING count(*) > 0"));	
				};

				/// ����� ��� ���������� ���������� � ������� SemanticClassesTree
				class CAccessUTSemanticsTreeName : public CAccessorTSemanticsTree
				{
				public:
					BEGIN_PARAM_MAP(CAccessUTSemanticsTreeName)
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(1, m_chName)	
						SET_PARAM_TYPE(DBPARAMIO_INPUT)						
						COLUMN_ENTRY(2, m_ushIDClass)						
					END_PARAM_MAP()		
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessUTSemanticsTreeName,
						_T("UPDATE SemanticClassesTree SET Name = ? WHERE IDClass = ?"));	
				};

				/// ����� ��� ��������� ������ ���������� �� ������� SemanticClassesTree
				class CAccessSFullTSemanticsTree : public CAccessorTSemanticsTree
				{
				public:
					BEGIN_COLUMN_MAP(CAccessSFullTSemanticsTree)
						COLUMN_ENTRY(1, m_ushIDClass)										
						COLUMN_ENTRY(2, m_ushIDParent)										
						COLUMN_ENTRY(3, m_chName)
						COLUMN_ENTRY(4, m_chShortName)
						COLUMN_ENTRY(5, m_uiColor)
					END_COLUMN_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessSFullTSemanticsTree,
						_T("SELECT * FROM SemanticClassesTree"));	
				};

/////////////////////////////////////////////////////////////////////////////////////////
/* ������ �� ������� ������������� ������� */

				/// ����� ����������� ���� �������	SemanticClassesWords � ������������ ��� ��������� ������ �� ���			
				class CAccessorTSemanticsWords 
				{
				protected:	

					unsigned int	m_iIDSource;
					/*! \var unsigned int m_iIDClass
					*  \brief     ������ ������
					*/

					/*! \var unsigned int	m_ushIDClass
					*  \brief     ������ �������������� ������
					*/
					unsigned int	m_iIDClass;
					
				public:	

					/// ���������� ������ ������, ����������� ��������� ��� �������
					unsigned int	GetIDSource()
					{
						return m_iIDSource;
					}
					/// ������������� ������ ������, ����������� ��������� ��� �������
					void	SetIDSource(unsigned int iIDSource)
					{
						m_iIDSource = iIDSource;
					}	

					/// ���������� ������ ������
					unsigned int	GetIDClass()
					{
						return m_iIDClass;
					}
					/// ������������� ������ ������
					void	SetIDClass(unsigned int iIDClass)
					{
						m_iIDClass = iIDClass;
					}	
				};



				/// ����� ��� ��������� ������ ���������� �� ������� SemanticClassesWords
				class CAccessSFullTSemanticsWords : public CAccessorTSemanticsWords
				{
				public:
					BEGIN_COLUMN_MAP(CAccessSFullTSemanticsWords)
						COLUMN_ENTRY(1, m_iIDSource)										
						COLUMN_ENTRY(2, m_iIDClass)										
					END_COLUMN_MAP()
				public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
					DEFINE_COMMAND(CAccessSFullTSemanticsWords,
						_T("SELECT * FROM SemanticClassesWords"));	
				};

/////////////////////////////////////////////////////////////////////////////////////////
/*		������� ��� ������� � ������		*/
////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////				
					
					/*	������������ ���� � �����������	*/
					
					/// �������� �� ������� 
					typedef CAccessor<CAccessDTSemanticsSynonims> CAccessorDTSemanticsSynonims;
					typedef CCommand<CAccessorDTSemanticsSynonims> CCommandDTSemanticsSynonims;
					typedef CPreparedCommand<CAccessorDTSemanticsSynonims> CPreparedDTSemanticsSynonims;
					
					/// ������� � �������
					typedef CAccessor<CAccessITSemanticsSynonimsAddWord> CAccessorITSemanticsSynonimsAddWord;
					typedef CCommand<CAccessorITSemanticsSynonimsAddWord> CCommandITSemanticsSynonimsAddWord;
					typedef CPreparedCommand<CAccessorITSemanticsSynonimsAddWord> CPreparedITSemanticsSynonimsAddWord;

					/// ����� ���������� �� ������
					typedef CAccessor<CAccessSTSemanticsSynonimsGetByClass> CAccessorSTSemanticsSynonimsGetByClass;
					typedef CCommand<CAccessorSTSemanticsSynonimsGetByClass> CCommandSTSemanticsSynonimsGetByClass;
					typedef CPreparedCommand<CAccessorSTSemanticsSynonimsGetByClass> CPreparedSTSemanticsSynonimsGetByClass;

					/// ����� ���������� �� ������
					typedef CAccessor<CAccessSTSemanticsSynonimsGetByIDSource> CAccessorSTSemanticsSynonimsGetByIDSource;
					typedef CCommand<CAccessorSTSemanticsSynonimsGetByIDSource> CCommandSTSemanticsSynonimsGetByIDSource;
					typedef CPreparedCommand<CAccessorSTSemanticsSynonimsGetByIDSource> CPreparedSTSemanticsSynonimsGetByIDSource;

					/// ����� ���� ����������
					typedef CAccessor<CAccessSFullTSemanticsSynonims> CAccessorSFullTSemanticsSynonims;
					typedef CCommand<CAccessorSFullTSemanticsSynonims> CCommandSFullTSemanticsSynonims;
					typedef CPreparedCommand<CAccessorSFullTSemanticsSynonims> CPreparedSFullTSemanticsSynonims;

///////////////////////////////////////////////////////////////////////////////////////				
					
					/*	������������ ���� � �����������	*/
					
					/// �������� �� ������� 
					typedef CAccessor<CAccessDTSemantics> CAccessorDTSemantics;
					typedef CCommand<CAccessorDTSemantics> CCommandDTSemantics;
					typedef CPreparedCommand<CAccessorDTSemantics> CPreparedDTSemantics;
					
					/// ������� � �������
					typedef CAccessor<CAccessITSemanticsAddWord> CAccessorITSemanticsAddWord;
					typedef CCommand<CAccessorITSemanticsAddWord> CCommandITSemanticsAddWord;
					typedef CPreparedCommand<CAccessorITSemanticsAddWord> CPreparedITSemanticsAddWord;

					/// ����� ���������� �� ������
					typedef CAccessor<CAccessSTSemanticsGetByClass> CAccessorSTSemanticsGetByClass;
					typedef CCommand<CAccessorSTSemanticsGetByClass> CCommandSTSemanticsGetByClass;
					typedef CPreparedCommand<CAccessorSTSemanticsGetByClass> CPreparedSTSemanticsGetByClass;

					/// ����� ���������� �� ������
					typedef CAccessor<CAccessSTSemanticsGetByIDSource> CAccessorSTSemanticsGetByIDSource;
					typedef CCommand<CAccessorSTSemanticsGetByIDSource> CCommandSTSemanticsGetByIDSource;
					typedef CPreparedCommand<CAccessorSTSemanticsGetByIDSource> CPreparedSTSemanticsGetByIDSource;

					/// ����� ���� ����������
					typedef CAccessor<CAccessSFullTSemantics> CAccessorSFullTSemantics;
					typedef CCommand<CAccessorSFullTSemantics> CCommandSFullTSemantics;
					typedef CPreparedCommand<CAccessorSFullTSemantics> CPreparedSFullTSemantics;

					/// ����� ���� ����������
					typedef CAccessor<CAccessSFullTSemanticsExtra> CAccessorSFullTSemanticsExtra;
					typedef CCommand<CAccessorSFullTSemanticsExtra> CCommandSFullTSemanticsExtra;
					typedef CPreparedCommand<CAccessorSFullTSemanticsExtra> CPreparedSFullTSemanticsExtra;

///////////////////////////////////////////////////////////////////////////////////////
				/*	������������� �������� ����	*/

				
					typedef CAccessor<CSAllSemanticIDSourceTree> CAccessorSAllSemanticIDSourceTree;
					typedef CCommand<CAccessorSAllSemanticIDSourceTree> CCommandSAllSemanticIDSourceTree;
					typedef CPreparedCommand<CAccessorSAllSemanticIDSourceTree> CPreparedSAllSemanticIDSourceTree;

					typedef CAccessor<CSSemanticIDSourceTree> CAccessorCSSemanticIDSourceTree;
					typedef CCommand<CAccessorCSSemanticIDSourceTree> CCommandCSSemanticIDSourceTree;
					typedef CPreparedCommand<CAccessorCSSemanticIDSourceTree> CPreparedCSSemanticIDSourceTree;

					typedef CAccessor<CDSemanticIDSourceTree> CAccessorCDSemanticIDSourceTree;
					typedef CCommand<CAccessorCDSemanticIDSourceTree> CCommandCDSemanticIDSourceTree;
					typedef CPreparedCommand<CAccessorCDSemanticIDSourceTree> CPreparedCDSemanticIDSourceTree;

					typedef CAccessor<CISemanticIDSourceTree> CAccessorCISemanticIDSourceTree;
					typedef CCommand<CAccessorCISemanticIDSourceTree> CCommandCISemanticIDSourceTree;
					typedef CPreparedCommand<CAccessorCISemanticIDSourceTree> CPreparedCISemanticIDSourceTree;

///////////////////////////////////////////////////////////////////////////////////////

					/*	������	������������� ������� */

					typedef CAccessor<CAccessUTSemanticsTreeName> CAccessorUTSemanticsTreeName;
					typedef CCommand<CAccessorUTSemanticsTreeName> CCommandUTSemanticsTreeName;
					typedef CPreparedCommand<CAccessorUTSemanticsTreeName> CPreparedUTSemanticsTreeName;

					typedef CAccessor<CAccessSTSemanticsTreeGetMaxID> CAccessorSTSemanticsTreeGetMaxID;
					typedef CCommand<CAccessorSTSemanticsTreeGetMaxID> CCommandSTSemanticsTreeGetMaxID;
					typedef CPreparedCommand<CAccessorSTSemanticsTreeGetMaxID> CPreparedSTSemanticsTreeGetMaxID;

					typedef CAccessor<CAccessTSemanticsTreeByName> CAccessorTSemanticsTreeByName;
					typedef CCommand<CAccessorTSemanticsTreeByName> CCommandTSemanticsTreeByName;
					typedef CPreparedCommand<CAccessorTSemanticsTreeByName> CPreparedTSemanticsTreeByName;

					typedef CAccessor<CAccessTSemanticsTreeByClass> CAccessorTSemanticsTreeByClass;
					typedef CCommand<CAccessorTSemanticsTreeByClass> CCommandTSemanticsTreeByClass;
					typedef CPreparedCommand<CAccessorTSemanticsTreeByClass> CPreparedTSemanticsTreeByClass;

					typedef CAccessor<CAccessTSemanticsTreeByParent> CAccessorTSemanticsTreeByParent;
					typedef CCommand<CAccessorTSemanticsTreeByParent> CCommandTSemanticsTreeByParent;
					typedef CPreparedCommand<CAccessorTSemanticsTreeByParent> CPreparedTSemanticsTreeByParent;

					typedef CAccessor<CAccessDTSemanticsTree> CAccessorDTSemanticsTree;
					typedef CCommand<CAccessorDTSemanticsTree> CCommandDTSemanticsTree;
					typedef CPreparedCommand<CAccessorDTSemanticsTree> CPreparedDTSemanticsTree;

					typedef CAccessor<CAccessITSemanticsTreeCreateClass> CAccessorITSemanticsTreeCreateClass;
					typedef CCommand<CAccessorITSemanticsTreeCreateClass> CCommandITSemanticsTreeCreateClass;
					typedef CPreparedCommand<CAccessorITSemanticsTreeCreateClass> CPreparedITSemanticsTreeCreateClass;		

					typedef CAccessor<CAccessSFullTSemanticsTree> CAccessorSFullTSemanticsTree;
					typedef CCommand<CAccessorSFullTSemanticsTree> CCommandSFullTSemanticsTree;
					typedef CPreparedCommand<CAccessorSFullTSemanticsTree> CPreparedSFullTSemanticsTree;

					typedef CAccessor<CAccessSFullTSemanticsWords> CAccessorSFullTSemanticsWords;
					typedef CCommand<CAccessorSFullTSemanticsWords> CCommandSFullTSemanticsWords;
					typedef CPreparedCommand<CAccessorSFullTSemanticsWords> CPreparedSFullTSemanticsWords;

				};
			};
		};
	};
};

#pragma warning( default : 4995 )