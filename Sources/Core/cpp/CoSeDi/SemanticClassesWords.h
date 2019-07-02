#pragma once

#include "..\ASSInterface\ICoSeDi.h"
#include  ".\Connect.h"

namespace SS   {
	namespace CoSeDi   {

		// --------------------------------------------------
		/// ��������� ������ ����������� ����� � ������� ������������� �������

		class CSemanticClassesWords : 
			public SS::Core::CommonServices::CBaseCoreClass,
			public SS::Interface::Core::CoSeDi::ISemanticClassesWords   {

			public:

				CSemanticClassesWords();
				~CSemanticClassesWords();

				VOID SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager * pLoadManager);

			public:

				/// ������������� ����� �������������� ������ ��� ������
				/** 
					\param iCurrentClass - ����� ��������������
				*/
				VOID SetClass(IN TYPE_DictIndex iCurrentClass)   {
					m_iCurSemClass = iCurrentClass;
				}

				/// ���������� ����� �������������� �������������� ������
				/** 
					\param VOID
				*/
				TYPE_DictIndex GetClass(VOID)   {
					return(m_iCurSemClass);
				}

				/// ���������� ������ �������� ������������� ������� �� ������� �����
				/** 
					\param iIDSource - ������ �����
					\param pClassesList - ��������� �� ������ �������� ������������� �������
				*/
				BOOL GetClasses(IN TYPE_DictIndex iIDSource, OUT std::list<TYPE_DictIndex> * pClassesList);

				/// ���������� ������ ����, ������� ��������� � �������� �������������� ������
				/** 
					\param pIDSourcesList -������ �������� ����, ����������� � �������������� �������������� ������
					TRUE - �������� ���������
				*/
				BOOL GetWords(OUT std::list<TYPE_DictIndex> * pIDSourcesList);

				/// ��������� ����� � �������� �������������� ������
				/** 
					\param iIDSource - ������ �����
					\return TRUE - �������� ���������
				*/
				BOOL AddWord(IN TYPE_DictIndex iIDSource);

				/// ������� �����, ����������� � �������� �������������� ������
				/** 
					\param iIDSource - ������ �����
					\return TRUE - �������� ���������
				*/
				BOOL DeleteWord (IN TYPE_DictIndex iIDSource);

			public:
		
				BOOL   zm_fDbmsConnect(VOID);
				BOOL   zm_fDbmsDisConnect(VOID);
				INT    zm_iConnectionCnt;
				HANDLE zm_hMutex;

			private:

				TYPE_DictIndex m_iCurSemClass;

				SS::Interface::Core::ResourceManagers::ILingvoBaseManager * m_pLingvoBaseManager;
				SS::Interface::Core::DBMS::IDataBase                      * m_pDtaBaseR;
				SS::Interface::Core::DBMS::IDataBase                      * m_pDtaBaseE;
				SS::Interface::Core::DBMS::IDataTable                     * m_pTblWordR;
				SS::Interface::Core::DBMS::IDataTable                     * m_pTblWordE;

				SS::Interface::Core::DBMS::IDataTable                     * m_pCurrTbl;
				BOOL SetCurrTbl(UINT iDictNum);

				INT32        m_iWordId;
				INT32        m_iClassId;

				VOID       * m_aWordAddArr[2];
				VOID       * m_aWordFindArr[2];

				enum   {
					fenFindInTreeByIdWord  = 0,
					fenFindInTreeByIdClass = 1,
				};
		};

		class SCW_AutoConnect   {
			public:
				SCW_AutoConnect(CSemanticClassesWords * pSemanticClassesWords)   {
					m_pSemanticClassesWords = pSemanticClassesWords;
					m_pSemanticClassesWords->zm_fDbmsConnect();
				}
				~SCW_AutoConnect()   {
					m_pSemanticClassesWords->zm_fDbmsDisConnect();
				}
			private:
				CSemanticClassesWords * m_pSemanticClassesWords;
		};

		#define DBMS_CONNECT_SCW SCW_AutoConnect oAutoConnect(this)

	};
};

#define _F __FUNCTION__

///	������ ��������� �� ������ � ������ �������
/**
	\param pFuncName  - ��� ������� � ������� ��������� ������
	\param nFailCode  - ��� ������
	\param pFormatStr - ������ ��������������
	\param ...        - ���������� ������ ����������
	\return HRESULT   - ��� ������ nFailCode ��� ��� �� GetLastError()

	������ ��������� �� ������ � ������ �������
	*/
HRESULT LogFail(CHAR * pFuncName, HRESULT nFailCode, _TCHAR * pFormatStr, ...);

///	������ �������� ��������� � ������ �������
/**
	\param pFormatStr - ������ ��������������
	\param ... - ���������� ������ ����������
	\return VOID

	������ �������� ��������� � ������ �������
	*/
VOID LogMess(_TCHAR * pFormatStr, ...);
