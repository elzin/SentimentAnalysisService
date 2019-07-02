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
				namespace Combinatory
				{
					/// �������� ��� ������� � ������������� ����� ���
					class CAccessorTCombinatory 
					{
					protected:	
						/*! \var unsigned int	m_uiID
						*  \brief     ������ ����������
						*/
						unsigned int	m_uiID;
						/*! \var short			m_shIDType
						*  \brief     ����� ���� ����������������
						*/
						short			m_shIDType;
						/*! \var short			m_shIDForm
						*  \brief     ������ ����������
						*/
						short			m_shIDForm;
						/*! \var unsigned short	m_ushDictionaryNumber
						*  \brief     ����� �������
						*/
						unsigned short	m_ushDictionaryNumber;
						/*! \var unsigned int	m_uiIDSource
						*  \brief     ������ ������
						*/
						unsigned int	m_uiIDSource;
						/*! \var unsigned short	m_ushLevel
						*  \brief     ����� ����� � ����������
						*/
						unsigned short	m_ushLevel;
						/*! \var short			m_shCombiType
						*  \brief     ��� ����������
						*/
						short			m_shCombiType;
					public:	
						/// ���������� ������ ����������
						unsigned int	GetID()
						{
							return m_uiID;
						}
						/// ������������� ������ ����������
						void	SetID(unsigned int uiID)
						{
							m_uiID = uiID;
						}
						/// ���������� ������ ������
						unsigned int	GetIDSource()
						{
							return m_uiIDSource;
						}
						/// ������������� ������ ������
						void	SetIDSource(unsigned int uiIDSource)
						{
							m_uiIDSource = uiIDSource;
						}	
						/// ���������� ����� ���� ����������������
						short	GetIDType()
						{
							return m_shIDType;
						}
						/// ���������� ����� ����������
						short	GetIDForm()
						{
							return m_shIDForm;
						}
						/// ���������� ��� ����������
						SS::CoSeDi::DataTypes::ECombiType	GetCombiType()
						{
							return (SS::CoSeDi::DataTypes::ECombiType)m_shCombiType;
						}
						/// ������������� ����� ���� ����������������
						void	SetIDType(short shIDType)
						{
							m_shIDType = shIDType;
						}
						/// ������������� ����� ����������
						void	SetIDForm(short shIDForm)
						{
							m_shIDForm = shIDForm;
						}
						/// ������������� ��� ����������
						void	SetCombiType(SS::CoSeDi::DataTypes::ECombiType eCombiType)
						{
							m_shCombiType =(short)eCombiType;
						}
						/// ���������� ����� �������
						unsigned short	GetDictionaryNumber()
						{
							return m_ushDictionaryNumber;
						}
						/// ������������� ����� �������
						void	SetDictionaryNumber(unsigned short ushDictionaryNumber)
						{
							m_ushDictionaryNumber = ushDictionaryNumber;
						}	
						/// ���������� ����� ����� � ����������
						unsigned short	GetLevel()
						{
							return m_ushLevel;
						}
						/// ������������� ����� ����� � ����������
						void	SetLevel(unsigned short ushLevel)
						{
							m_ushLevel = ushLevel;
						}
						
					};					
					
					/// ����� ��� ������� ����� � ����
					class CAccessITCombinatory : public CAccessorTCombinatory
					{
					public:	/*	��������� ��� �������	*/
						BEGIN_PARAM_MAP(CAccessITCombinatory)
							SET_PARAM_TYPE(DBPARAMIO_INPUT) // 1 //���� ID
							COLUMN_ENTRY(1, m_uiID) 
							SET_PARAM_TYPE(DBPARAMIO_INPUT) // 2 //���� IDType
							COLUMN_ENTRY(2, m_shIDType)
							SET_PARAM_TYPE(DBPARAMIO_INPUT) // 3 //���� IDForm
							COLUMN_ENTRY(3, m_shIDForm)
							SET_PARAM_TYPE(DBPARAMIO_INPUT) // 4 //���� DictionaryNumber
							COLUMN_ENTRY(4, m_ushDictionaryNumber)
							SET_PARAM_TYPE(DBPARAMIO_INPUT) // 5 //���� IDSource
							COLUMN_ENTRY(5, m_uiIDSource)
							SET_PARAM_TYPE(DBPARAMIO_INPUT) // 6 //���� Level
							COLUMN_ENTRY(6, m_ushLevel)
							SET_PARAM_TYPE(DBPARAMIO_INPUT) // 7 //���� CombiType
							COLUMN_ENTRY(7, m_shCombiType)
						END_PARAM_MAP()
					public:	/*	��������� ��� �������	*/
					/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessITCombinatory, 
					_T("INSERT Combinatory (ID, IDType, IDForm, DictionaryNumber, IDSource, Level, CombiType) VALUES (?,?,?,?,?,?,?)"));	
					};

					/// ����� ��� ��������� ������������� ID 
					class CAccessSMaxTCombinatory : public CAccessorTCombinatory
					{
					public:
						BEGIN_COLUMN_MAP(CAccessSMaxTCombinatory)
							COLUMN_ENTRY(1, m_uiID)										
						END_COLUMN_MAP()
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessSMaxTCombinatory, _T("SELECT MAX(ID) FROM Combinatory HAVING count(*) > 0"));	
					};

					/// ����� ��� �������� ������ �� �������
					class CAccessDTCombinatory : public CAccessorTCombinatory
					{
					public:
						BEGIN_PARAM_MAP(CAccessDTCombinatory)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)
							COLUMN_ENTRY(1, m_uiID)										
						END_PARAM_MAP()
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessDTCombinatory, _T("DELETE FROM Combinatory WHERE ID = ?"));	
					};

					/// ����� ��� ��������� ������ ���������� � ����������
					class CAccessSTCombinatoryInfo : public CAccessorTCombinatory
					{
					public:
						BEGIN_COLUMN_MAP(CAccessSTCombinatoryInfo)
							COLUMN_ENTRY(1, m_uiID)										
							COLUMN_ENTRY(2, m_shIDType)										
							COLUMN_ENTRY(3, m_shIDForm)										
							COLUMN_ENTRY(4, m_ushDictionaryNumber)										
							COLUMN_ENTRY(5, m_uiIDSource)										
							COLUMN_ENTRY(6, m_ushLevel)										
							COLUMN_ENTRY(7, m_shCombiType)										
						END_COLUMN_MAP()
					public:
						BEGIN_PARAM_MAP(CAccessSTCombinatoryInfo)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)
							COLUMN_ENTRY(1, m_uiID)																
						END_PARAM_MAP()
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessSTCombinatoryInfo,
							_T("SELECT * FROM Combinatory WHERE ID = ? ORDER BY Level"));	
					};

					/// ����� ��� ��������� ���� ���������� ��� ��������� �������� �����
					class CAccessSAllCombination : public CAccessorTCombinatory
					{
					public:
						BEGIN_COLUMN_MAP(CAccessSAllCombination)
							COLUMN_ENTRY(1, m_uiID)
						END_COLUMN_MAP()
					public:
						BEGIN_PARAM_MAP(CAccessSAllCombination)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)
							COLUMN_ENTRY(1, m_uiIDSource)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)
							COLUMN_ENTRY(2, m_ushDictionaryNumber)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)
							COLUMN_ENTRY(3, m_shIDForm)
						END_PARAM_MAP()
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessSTCombinatoryInfo, 
							_T("SELECT ID FROM Combinatory WHERE IDSource = ? and DictionaryNumber = ? and (IDForm = ? or IDForm = -1)"));	
					};

					/// ����� ��� ��������� ���� ����������
					class CAccessSFullCombination : public CAccessorTCombinatory
					{
					public:
						BEGIN_COLUMN_MAP(CAccessSFullCombination)
							COLUMN_ENTRY(1, m_uiID)
							COLUMN_ENTRY(2, m_shIDType)
							COLUMN_ENTRY(3, m_shIDForm)
							COLUMN_ENTRY(4, m_ushDictionaryNumber)
							COLUMN_ENTRY(5, m_uiIDSource)
							COLUMN_ENTRY(6, m_ushLevel)
							COLUMN_ENTRY(7, m_shCombiType)						
						END_COLUMN_MAP()
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessSFullCombination, 
							_T("SELECT * FROM Combinatory"));	
					};

					/// ����� ��� ��������� ���� ����������
					class CAccessSFullCombinationExtra : public CAccessorTCombinatory
					{
					public:
						BEGIN_COLUMN_MAP(CAccessSFullCombinationExtra)
							COLUMN_ENTRY(1, m_uiID)
							COLUMN_ENTRY(2, m_shIDType)
							COLUMN_ENTRY(3, m_shIDForm)
							COLUMN_ENTRY(4, m_ushDictionaryNumber)
							COLUMN_ENTRY(5, m_uiIDSource)
							COLUMN_ENTRY(6, m_ushLevel)
							COLUMN_ENTRY(7, m_shCombiType)						
						END_COLUMN_MAP()
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessSFullCombinationExtra, 
							_T("SELECT * FROM CombinatoryExtra"));	
					};

					/// ����� ��� ��������� ������� �� ������� CombiSynonyms
					class CAccessSFullTCombiSynonyms
					{
					public:
						
						UINT32 m_uiSynonymClass;
						UINT16 m_ushDictionaryNumber;
						UINT32 m_uiIDSource;

						BEGIN_COLUMN_MAP(CAccessSFullTCombiSynonyms)
							COLUMN_ENTRY(1, m_uiSynonymClass)										
							COLUMN_ENTRY(2, m_ushDictionaryNumber)										
							COLUMN_ENTRY(3, m_uiIDSource)																										
						END_COLUMN_MAP()
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessSFullTCombiSynonyms,
							_T("SELECT x.SemanticClass, x.DictionaryNumber, x.IDSource  FROM CombiSynonyms x ORDER BY x.SemanticClass,x.IDSource"));	
					};

///////////////////////////////////////////////////////////////////////////////////////
					/*	�������������� ������	*/
					typedef CAccessor<CAccessSMaxTCombinatory> CAccessorSMaxTCombinatory;
					typedef CCommand<CAccessorSMaxTCombinatory> CCommandSMaxTCombinatory;
					typedef CPreparedCommand<CAccessorSMaxTCombinatory> CPreparedSMaxTCombinatory;

					typedef CAccessor<CAccessITCombinatory> CAccessorITCombinatory;
					typedef CCommand<CAccessorITCombinatory> CCommandITCombinatory;
					typedef CPreparedCommand<CAccessorITCombinatory> CPreparedITCombinatory;

					typedef CAccessor<CAccessDTCombinatory> CAccessorDTCombinatory;
					typedef CCommand<CAccessorDTCombinatory> CCommandDTCombinatory;
					typedef CPreparedCommand<CAccessorDTCombinatory> CPreparedDTCombinatory;

					typedef CAccessor<CAccessSTCombinatoryInfo> CAccessorSTCombinatoryInfo;
					typedef CCommand<CAccessorSTCombinatoryInfo> CCommandSTCombinatoryInfo;
					typedef CPreparedCommand<CAccessorSTCombinatoryInfo> CPreparedSTCombinatoryInfo;

					typedef CAccessor<CAccessSAllCombination> CAccessorSAllCombination;
					typedef CCommand<CAccessorSAllCombination> CCommandSAllCombination;
					typedef CPreparedCommand<CAccessorSAllCombination> CPreparedSAllCombination;

					/// ����� ���� ����������
					typedef CAccessor<CAccessSFullCombination> CAccessorSFullCombination;
					typedef CCommand<CAccessorSFullCombination> CCommandSFullCombination;
					typedef CPreparedCommand<CAccessorSFullCombination> CPreparedSFullCombination;

					/// ����� ���� ����������
					typedef CAccessor<CAccessSFullCombinationExtra> CAccessorSFullCombinationExtra;
					typedef CCommand<CAccessorSFullCombinationExtra> CCommandSFullCombinationExtra;
					typedef CPreparedCommand<CAccessorSFullCombinationExtra> CPreparedSFullCombinationExtra;

					/// ����� ���� ����������
					typedef CAccessor<CAccessSFullTCombiSynonyms> CAccessorSFullTCombiSynonyms;
					typedef CCommand<CAccessorSFullTCombiSynonyms> CCommandSFullTCombiSynonyms;
					typedef CPreparedCommand<CAccessorSFullTCombiSynonyms> CPreparedSFullTCombiSynonyms;

					
					/*typedef CAccessor<CAccess> CAccessor;
					typedef CCommand<CAccessor> CCommand;
					typedef CPreparedCommand<CAccessor> CPrepared;*/					
				};				
			};
		};
	};
};

#pragma warning( default : 4995 )