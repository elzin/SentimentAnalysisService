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
				namespace Syntax
				{
					/// ����� ��� ������� � �������������� ����������
					class CAccessSyntax
					{
					protected:
						/*! \var unsigned int	iSyntaxInfo
						*  \brief     �������������� �������������� ����������
						*/
						unsigned int	iSyntaxInfo;
						/*! \var unsigned int	m_uiIDSource
						*  \brief     ������ ������ �����
						*/
						unsigned int	m_uiIDSource;
						/*! \var unsigned short	m_ushDictionaryNumber
						*  \brief     ����� �������
						*/
						unsigned short	m_ushDictionaryNumber;
					public:
						/// ���������� ������ ������
						unsigned int GetIDSource()
						{					
							return m_uiIDSource;
						}
						/// ������������� ������ ������
						void SetIDSource(unsigned int uiIDSource)
						{
							m_uiIDSource = uiIDSource;
						}
						/// ���������� ������ �������
						unsigned short GetDictionaryNumber()
						{					
							return m_ushDictionaryNumber;
						}
						/// ������������� ������ �������
						void SetDictionaryNumber(unsigned short ushDictionaryNumber)
						{
							m_ushDictionaryNumber = ushDictionaryNumber;
						}
						/// ���������� �������������� �������������� ����������
						int GetSyntaxInfo()
						{
							return iSyntaxInfo;
						}
						/// ������������� �������������� �������������� ����������
						void SetSyntaxInfo(SS::CoSeDi::DataTypes::TSyntaxInfo SyntaxInfo)
						{
							iSyntaxInfo	= (unsigned int)SyntaxInfo;
						}
					};
					/// ����� ��� ��������� ���� ���������� �� ������� Syntax
					class CAccessSyntaxSALL : public CAccessSyntax
					{
					public:
						BEGIN_COLUMN_MAP(CAccessSyntaxSALL)
							COLUMN_ENTRY(1, m_ushDictionaryNumber)										
							COLUMN_ENTRY(2, m_uiIDSource)										
							COLUMN_ENTRY(3, iSyntaxInfo)										
						END_COLUMN_MAP()
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessSyntaxSALL,
							_T("SELECT * FROM Syntax"));	
					};
					/// ����� ��� ��������� ���������� �� ������� ������ � ������� �� ������� Syntax
					class CAccessSyntaxSbyIDSource : public CAccessSyntax
					{
					public:
						BEGIN_COLUMN_MAP(CAccessSyntaxSbyIDSource)
							COLUMN_ENTRY(1, iSyntaxInfo)										
						END_COLUMN_MAP()
					public:
						BEGIN_PARAM_MAP(CAccessSyntaxSbyIDSource)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(1, m_ushDictionaryNumber)	
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(2, m_uiIDSource)						
						END_PARAM_MAP()		
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessSyntaxSbyIDSource,
							_T("SELECT SyntaxInfo FROM Syntax WHERE DictionaryNumber = ? and IDSource = ?"));	
					};
					/// ����� ��� ���������� ���������� � ������� Syntax
					class CAccessSyntaxI : public CAccessSyntax
					{					
					public:
						BEGIN_PARAM_MAP(CAccessSyntaxI)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(1, m_ushDictionaryNumber)						
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(2, m_uiIDSource)	
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(3, iSyntaxInfo)						
						END_PARAM_MAP()		
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessSyntaxI,
							_T("INSERT INTO Syntax (DictionaryNumber, IDSource, SyntaxInfo) VALUES (?,?,?)"));	
					};
					/// ����� ����������� ������ � ������� Syntax
					class CAccessSyntaxU : public CAccessSyntax
					{
					public:
						BEGIN_PARAM_MAP(CAccessSyntaxU)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(1, iSyntaxInfo)						
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(2, m_ushDictionaryNumber)	
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(3, m_uiIDSource)						
						END_PARAM_MAP()		
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessSyntaxU,
							_T("UPDATE Syntax SET  SyntaxInfo = ? WHERE DictionaryNumber = ? and IDSource = ?"));	
					};
					/// ������� ������ �� ������� Syntax �� ������� ������� � ������ �����
					class CAccessSyntaxD : public CAccessSyntax
					{
					public:
						BEGIN_PARAM_MAP(CAccessSyntaxD)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(1, m_ushDictionaryNumber)	
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(2, m_uiIDSource)						
						END_PARAM_MAP()		
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessSyntaxD,
							_T("DELETE Syntax WHERE DictionaryNumber = ? and IDSource = ?"));	
					};
					/// ������� ������ �� ������� Syntax �� ������� �������, ������ ����� � �������������� ���������� � �����
					class CAccessSyntaxDSelected : public CAccessSyntax
					{
					public:
						BEGIN_PARAM_MAP(CAccessSyntaxDSelected)
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(1, m_ushDictionaryNumber)	
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(2, m_uiIDSource)						
							SET_PARAM_TYPE(DBPARAMIO_INPUT)						
							COLUMN_ENTRY(3, iSyntaxInfo)	
						END_PARAM_MAP()		
					public:	/*	��������� ��� �������	*/
						/*	��������������� ������	*/
						DEFINE_COMMAND(CAccessSyntaxDSelected,
							_T("DELETE Syntax WHERE DictionaryNumber = ? and IDSource = ? and SyntaxInfo = ?"));	
					};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					/*	�������������� ���������� � �����	*/

					typedef CAccessor<CAccessSyntaxDSelected> CAccessorSyntaxDSelected;
					typedef CCommand<CAccessorSyntaxDSelected> CCommandSyntaxDSelected;
					typedef CPreparedCommand<CAccessorSyntaxDSelected> CPreparedSyntaxDSelected;
					
					typedef CAccessor<CAccessSyntaxD> CAccessorSyntaxD;
					typedef CCommand<CAccessorSyntaxD> CCommandSyntaxD;
					typedef CPreparedCommand<CAccessorSyntaxD> CPreparedSyntaxD;
					
					typedef CAccessor<CAccessSyntaxU> CAccessorSyntaxU;
					typedef CCommand<CAccessorSyntaxU> CCommandSyntaxU;
					typedef CPreparedCommand<CAccessorSyntaxU> CPreparedSyntaxU;
					
					typedef CAccessor<CAccessSyntaxI> CAccessorSyntaxI;
					typedef CCommand<CAccessorSyntaxI> CCommandSyntaxI;
					typedef CPreparedCommand<CAccessorSyntaxI> CPreparedSyntaxI;
					
					typedef CAccessor<CAccessSyntaxSbyIDSource> CAccessorSyntaxSbyIDSource;
					typedef CCommand<CAccessorSyntaxSbyIDSource> CCommandSyntaxSbyIDSource;
					typedef CPreparedCommand<CAccessorSyntaxSbyIDSource> CPreparedSyntaxSbyIDSource;

					typedef CAccessor<CAccessSyntaxSALL> CAccessorSyntaxSALL;
					typedef CCommand<CAccessorSyntaxSALL> CCommandSyntaxSALL;
					typedef CPreparedCommand<CAccessorSyntaxSALL> CPreparedSyntaxSALL;
				
					/*typedef CAccessor<CAccess> CAccessor;
					typedef CCommand<CAccessor> CCommand;
					typedef CPreparedCommand<CAccessor> CPrepared;*/
				};
				
			};
		};
	};
};

#pragma warning( default : 4995 )