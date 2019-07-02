#pragma once

#include "..\ASSInterface\ICoSeDi.h"
#include  ".\Connect.h"

namespace SS   {
	namespace CoSeDi   {

		// --------------------------------------------------
		/// ����� ������ � ������� ������������� �������

		class CSemanticClassesTree : 

			public SS::Core::CommonServices::CBaseCoreClass,
			public SS::Interface::Core::CoSeDi::ISemanticClassesTree   {

			public:

				CSemanticClassesTree();
				~CSemanticClassesTree();

				VOID SetLoadManager(SS::Interface::Core::ResourceManagers::ILoadManager * pLoadManager);

			public:

				/// ������� ������������� �����
				/** 
					\param  IN iParentClassId - ����� ������������� �������������� ������ ( -1 == �������� ���, ����� - ������� � �������� )
					\param  IN psClassName - ��� �������������� ������
					\return TYPE_DictIndex - ����� �������������� ������ ( 0 == o�����)
				*/
				TYPE_DictIndex CreateClass(IN TYPE_DictIndex iParentClassId, IN std::wstring * psClassName, IN UINT32 iColor = DEFAULT_CLASS_COLOR, IN std::wstring * psShortName = NULL); 

				/// ������� ������������� �����
				/**
					\param  IN   iClassId    - ����� �������������� ������
					\return BOOL ( FALSE == o����� )
				*/
				BOOL DeleteClass(IN TYPE_DictIndex iClassId);

				/// ������������� ������������� �����
				/**
					\param  IN   iClassId       - ����� �������������� ������
					\param  IN   psNewClassName - ����� ��� �������������� ������
					\return BOOL ( FALSE == o����� )
				*/
				BOOL RenameClass(IN TYPE_DictIndex iClassId, IN std::wstring * psNewClassName, IN UINT32 iNewColor = DEFAULT_CLASS_COLOR, IN std::wstring * psNewShortName = NULL);


				///// �������� ����� �������������� ������ �� ��� ����� 
				///** 
				//	\param  IN psClassName - ��� �������������� ������
				//	\return ����� �������������� ������  ( -1 == ������ )
				//*/
				//TYPE_DictIndex GetClassIdByName(IN std::wstring * psClassName, IN TYPE_DictNumber eDictNumber);

				/// �������� ����� �������������� ������ �� ��� ��������� ����� 
				/** 
					\param  IN psClassShortName - �������� ��� �������������� ������
					\return ����� �������������� ������  ( -1 == ������ )
				*/
				TYPE_DictIndex GetClassIdByShortName(IN std::wstring * psClassShortName, IN TYPE_DictNumber eDictNumber);

				/// �������� ��� �������������� ������ �� ��� ������ 
				/**
					\param  IN   iClassId    - ����� �������������� ������
					\param  OUT  psClassName - ��� �������������� ������
					\return BOOL ( FALSE == o����� )
				*/
				BOOL GetClassNameById(IN TYPE_DictIndex iClassId, OUT std::wstring * psClassName, OUT UINT32 * piColor = NULL, OUT std::wstring * psShortName = NULL);


				/// �������� ������ ID �������� ������������� �������
				/** 
					\param  IN  iParentClassId - ����� ������������� �������������� ������
					\param  OUT pChildrenList  - ������ ����� �������� ������������� �������
					\return BOOL ( FALSE == o����� )
				*/
				BOOL GetChildren(IN TYPE_DictIndex iParentClassId, OUT std::list<TYPE_DictIndex> * pChildrenList);

				/// �������� ����� �������������� ������ ��������
				/** 
					\param  IN iClassId    - ����� �������������� ������
					\return TYPE_DictIndex - ����� �������������� ������ �������� ( -1 == ������ )
				*/
				TYPE_DictIndex GetClassParentId(IN TYPE_DictIndex iClassId);

				// --------------------------------

				/// 
				BOOL GetShortName(IN TYPE_DictIndex iParentClassId, OUT std::wstring * psClassShortName);

				///
				BOOL SetShortName(IN TYPE_DictIndex       iClassId);

				/// 
				BOOL ZMethod(VOID * pDataPtr1 = NULL, VOID * pDataPtr2 = NULL);


			public:

				BOOL   zm_fDbmsConnect(VOID);
				BOOL   zm_fDbmsDisConnect(VOID);
				INT    zm_iConnectionCnt;
				HANDLE zm_hMutex;

			private:

				SS::Interface::Core::ResourceManagers::ILingvoBaseManager * m_pLingvoBaseManager;
				SS::Interface::Core::DBMS::IDataBase                      * m_pDtaBaseR;
				SS::Interface::Core::DBMS::IDataBase                      * m_pDtaBaseE;
				SS::Interface::Core::DBMS::IDataTable                     * m_pTblTreeR;
				SS::Interface::Core::DBMS::IDataTable                     * m_pTblTreeE;

				SS::Interface::Core::DBMS::IDataTable                     * m_pCurrTbl;
				BOOL SetCurrTbl(UINT iDictNum);

				INT32        m_iClassId;
				INT32        m_iParentId;
				std::wstring m_sClassName;
				std::wstring m_sClassShortName;
				UINT32       m_iClassColor;

				VOID       * m_aTreeAddArr[5];
				VOID       * m_aTreeFindArr[5];

				enum   {
					fenFindInTreeByIdParent  = 0,
					fenFindInTreeByIdClass   = 1,
					fenFindInTreeByName      = 2,
					fenFindInTreeByShortName = 3
				};
		};

		class SCT_AutoConnect   {
			public:
				SCT_AutoConnect(CSemanticClassesTree * pSemanticClassesTree)   {
					m_pSemanticClassesTree = pSemanticClassesTree;
					m_pSemanticClassesTree->zm_fDbmsConnect();
				}
				~SCT_AutoConnect()   {
					m_pSemanticClassesTree->zm_fDbmsDisConnect();
				}
			private:
				CSemanticClassesTree * m_pSemanticClassesTree;
		};

		#define DBMS_CONNECT_SCT SCT_AutoConnect oAutoConnect(this)


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

