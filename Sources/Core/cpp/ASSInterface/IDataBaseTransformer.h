#pragma once

//#include "IInterface.h"

// --------------------------------------------------------------------------------
// GUIDs & IIDs :

/// ������������� ������ DataBaseTransformer
static const GUID CLSID_DataBaseTransformer = { 0x4ba98624, 0x2133, 0x4b90, { 0xad, 0x44, 0xc, 0xf, 0xe7, 0x1a, 0xd2, 0xb0 } };
/// ������������� ���������� DataBaseTransformer
static const GUID IID_DataBaseTransformer = { 0xf3471565, 0xf588, 0x468d, { 0xb9, 0xfb, 0x6b, 0x2f, 0xb0, 0xef, 0x42, 0xd6 } };


namespace SS   {
	namespace Interface   {
		namespace SubSidary   {	
			namespace DataBaseTransformer   {

				/// �������������� ��� ������
				enum TDataBaseId   {
					/// ���������� ����
					BASE_ENGLISH = 0,
					/// ������� ����
					BASE_RUSSIAN = 1
				};

				/// ��������� ��� �������������� ��������������� ���� ������ 
				class IDataBaseTransformer : public virtual SS::Interface::IBase   {

					public:
						/// ���������� ���� � �������������� � DBMS
						/**
							\param char      * pszDataSource            - ��� ��������� ������ (�������� "localhost")
							\param char      * pszUserLogin             - ��� ������������
							\param char      * pszUserPassword          - ������ ������������
							\param TDataBaseId eDataBaseId              - ������������� ���� ������
							\param _TCHAR    * pszSqlDataBaseNamePrefix - �������, ���������� ����� ��� (������: "Test01_" �������� � "Test01_MorphoRussian")

						���������� ���� � �������������� � DBMS
						*/
						virtual HRESULT Prepare(char * pszDataSource, char * pszUserLogin, char * pszUserPassword, TDataBaseId eDataBaseId, _TCHAR * pszSqlDataBaseNamePrefix = NULL) = 0;

						/// �������� ���� �� SQL � DBMS
						/**
							\param char      * pszDataSource            - ��� ��������� ������ (�������� "localhost")
							\param char      * pszUserLogin             - ��� ������������
							\param char      * pszUserPassword          - ������ ������������
							\param TDataBaseId eDataBaseId              - ������������� ���� ������
							\param _TCHAR    * pszSqlDataBaseNamePrefix - �������, ���������� ����� ��� (������: "Test01_" �������� � "Test01_MorphoRussian")

						�������� ���� �� SQL � DBMS
						*/
						virtual HRESULT ToDBMS(char * pszDataSource, char * pszUserLogin, char * pszUserPassword, TDataBaseId eDataBaseId, _TCHAR * pszSqlDataBaseNamePrefix = NULL) = 0;

						/// �������� ���� �� DBMS � SQL
						/**
							\param char      * pszDataSource            - ��� ��������� ������ (�������� "localhost")
							\param char      * pszUserLogin             - ��� ������������
							\param char      * pszUserPassword          - ������ ������������
							\param TDataBaseId eDataBaseId              - ������������� ���� ������
							\param _TCHAR    * pszSqlDataBaseNamePrefix - �������, ���������� ����� ��� (������: "Test01_" �������� � "Test01_MorphoRussian")

						�������� ���� �� DBMS � SQL
						*/
						virtual HRESULT ToSQL(char * pszDataSource, char * pszUserLogin, char * pszUserPassword, TDataBaseId eDataBaseId, _TCHAR * pszSqlDataBaseNamePrefix = NULL) = 0;

				};

			}
		}
	}
}