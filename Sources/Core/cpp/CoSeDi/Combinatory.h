#pragma once

#include "..\ASSInterface\ICoSeDi.h"
#include "..\ASSInterface\TCoSeDiDataTypes.h"
#include "..\ASSInterface\ILingvoBaseManager.h"
#include "..\ASSInterface\TDictionaryNames.h"
#include "..\ASCInterface\IDBMS.h"

//#include "..\ASSInterface\TBaseNames.h"

//#include ".\dboCombinatory.h"
//#include ".\CombinatoryAnalysis.h"
//#include ".\cl_CLoadManagerAgent.h"

using namespace SS::Interface::Core::ResourceManagers;
using namespace SS::Interface::Core::CoSeDi;
using namespace SS::Interface::Core::DBMS;
using namespace SS::CoSeDi::DataTypes;

namespace SS   {
	namespace CoSeDi   {
		namespace DBMS   {

			/// ������ ��������� �� ������ � ������ �������
			HRESULT CombiErr(WCHAR * pFormatStr, ...);

			// --------------------------------------------------------------------------------------
			/// ����� CSimpleConnect
			class CSimpleConnect   {

				public:

					/// �����������
					CSimpleConnect(void) : m_pDataBase(NULL), m_pDataTable(NULL), m_poLingvoBaseManager(NULL)
					{
						memset(m_wsBaseName, 0, sizeof(wchar_t) * 100);
					}

					/// ����������
					~CSimpleConnect(void) { CloseConnection(); }

					/// �������� ���������� � ������			
					void CloseConnection(void);

					/// ������������� ���������� � ������				
					bool InitConnection(ILoadManager * pLoadManager, const wchar_t * pwsBaseName, const wchar_t * pwsTableName);

					/// ���������� ��������� �� IDataTable
					IDataTable * GetDataTable(void);

				private:

					/// ��������� �� IDataBase
					IDataBase * m_pDataBase;

					/// ��������� �� IDataTable
					IDataTable * m_pDataTable;

					/// ��������� �� ILingvoBaseManager
					ILingvoBaseManager * m_poLingvoBaseManager;

					wchar_t m_wsBaseName[100];

			};


			// --------------------------------------------------------------------------------------
			/// ����� CCombinatory
			class CCombinatory :	public SS::Interface::Core::CoSeDi::ICombinatory   {

				public:

					/// �����������
					CCombinatory() {}

					/// ����������
					~CCombinatory(void)   {
						zm_ConnectEng.CloseConnection();
						zm_ConnectRus.CloseConnection();
					}

					BOOL InitConnection(WCHAR * pwszDataTablesName, BOOL bExtraTables);
				
				public: 

					/// ���������� ������ ���������� ��� ������������ ������ ������� IDSource-��
					/** 
						\param  itrStartItr_In_ListOfSetsOfSourcesAndForms - ��������� �������� ������
						\param  iNumOfWordsToProcess                       - ����� ������� IDSource-�� ��� ���������
						\param  p_listCombinationInfo                      - �������� ������ ���������� � �����������
						\return bool                                       - ��������� ���������� ��������
					*/
					bool GetCombinationsInfo(
						/*in */ TListOfSetsOfSourcesAndFormsItr itrStartItr_In_ListOfSetsOfSourcesAndForms,
						/*in */ UINT iNumOfWordsToProcess,
						/*out*/ std::list<SCombinationNewInfo> * p_listCombinationInfo);

					/// ���������� ������ ���������� ��� ������������ ������ ������� IDSource-�� (Mode 2 : ������� ���� �� �����)
					/** 
						\param  itrStartItr_In_ListOfSetsOfSourcesAndForms - ��������� �������� ������
						\param  iNumOfWordsToProcess                       - ����� ������� IDSource-�� ��� ���������
						\param  p_listCombinationInfo                      - �������� ������ ���������� � �����������
						\return bool                                       - ��������� ���������� ��������
					*/
					bool GetCombinationsInfo_2(
						/*in */ TListOfSetsOfSourcesAndFormsItr itrStartItr_In_ListOfSetsOfSourcesAndForms,
						/*in */ UINT iNumOfWordsToProcess,
						/*out*/ std::list<SCombinationNewInfo> * p_listCombinationInfo);


					/// ���������� ������ ���������� ��� ������������ ������ ������� IDSource-��
					/** 
						\param  itrBegin_ListOfSetsOfSourcesAndForms - ��������� �������� ������
						\param  itrEnd_ListOfSetsOfSourcesAndForms   - �������� �������� ������
						\param  p_listCombinationInfo          - �������� ������ �������� ���������� � �����������
						\return bool                           - ��������� ���������� ��������
					*/
					bool GetCombinationsInfo(
						/*in */ TListOfSetsOfSourcesAndFormsItr itrBegin_ListOfSetsOfSourcesAndForms,
						/*in */ TListOfSetsOfSourcesAndFormsItr itrEnd_ListOfSetsOfSourcesAndForms,
						/*out*/ std::list<SCombinationNewInfo> * p_listCombinationInfo);

					/// ���������� ������ ���������� ��� ������������ ������ ������� IDSource-�� (Mode 2 : ������� ���� �� �����)
					/** 
						\param  itrBegin_ListOfSetsOfSourcesAndForms - ��������� �������� ������
						\param  itrEnd_ListOfSetsOfSourcesAndForms   - �������� �������� ������
						\param  p_listCombinationInfo          - �������� ������ �������� ���������� � �����������
						\return bool                           - ��������� ���������� ��������
					*/
					bool GetCombinationsInfo_2(
						/*in */ TListOfSetsOfSourcesAndFormsItr itrBegin_ListOfSetsOfSourcesAndForms,
						/*in */ TListOfSetsOfSourcesAndFormsItr itrEnd_ListOfSetsOfSourcesAndForms,
						/*out*/ std::list<SCombinationNewInfo> * p_listCombinationInfo);
					
					/// ���������� ������ ����������, ���������� �������� IDSource
					/** 
						\param iIDSource              - �������� IDSource
						\param  p_listCombinationsIDs - �������� ������ �������� ����������
						\return bool                  - ��������� ���������� ��������
					*/
					bool GetCombinationsByIDSource(/*in*/int iIDSource, /*out*/ std::list<int> * p_listCombinationsIDs);	
					
					/// ���������� ���������� � ����������
					/** 
						\param iIDCombination    - ����� ����������
						\param p_CombinationInfo - ��������� �� ���������, �������� ���������� � ����������
						\return bool             - ��������� ���������� ��������
					*/
					bool GetCombinationInfo(/*in*/int iIDCombination, /*out*/ SCombinationNewInfo * p_CombinationInfo);	

					/// ������� ����������
					/** 
						\param p_CombinationInfo - ��������� �� ���������, ���������� ���������� � ����������
						\return bool             - ��������� ���������� ��������
					*/
					bool CreateCombination(/*in out*/ SCombinationNewInfoForAdd * p_CombinationInfo);			

					/// ������� ����������
					/** 
						\param iIDCombination - ����� ����������
						\return bool          - ��������� ���������� ��������
					*/
					bool DeleteCombination(/*in*/int iIDCombination);

				public:

					/// ������ ��������� � ILoadManager
					void SetLoadManager(ILoadManager * pLoadManager);

				private:

					/// ���� ������ � DBMS �������� 
					enum EFindMode   {
						efmByID,
						efmByHashKey,
						efmByHashKey_2,
						efmByIDSource
					};

					ILoadManager                     * zm_pLoadManager;
					BOOL                               m_bExtraTables;

					BOOL                               zm_fRecursiveFunc(  UINT iLevel);
					BOOL                               zm_fRecursiveFunc_2(UINT iLevel);
					BOOL                               zm_fCheckCombination(  VOID);
					BOOL                               zm_fCheckCombination_2(VOID);

					SCombinationNewInfo                zm_oCombinationInfo;
					VOID                             * zm_apTableRecord[16];
					
					TListOfPtrsToSetsOfSourcesAndForms       zm_SubListForCheck;
					TListOfPtrsToSetsOfSourcesAndFormsItr    zm_SubListForCheckItr;

					UINT                               zm_SubListForCheckSise;  
					UINT32                             zm_SubListIDSourceArr[MAX_NUM_OF_COMBINATION_MEMBERS];
					UINT32                             zm_SubListIDFormArr[  MAX_NUM_OF_COMBINATION_MEMBERS];

					CSimpleConnect                     zm_ConnectEng;
					CSimpleConnect                     zm_ConnectRus;

					TSetOfHashKeys                     zm_setExistingHashKeys;
					TSetOfHashKeys                     zm_setExistingHashKeys_2;
					TSetOfSourcesAndForms              zm_setExistingFirstSourcesAndForms;

					UINT32                             zm_fGetHashKey_2(UINT32 aiDataArr[]);

					std::list<SCombinationNewInfo>   * zm_plistCombinationInfo;
					UINT                               zm_iPosInClauseCnt;

			}; 

		} // namespace DBMS   {
	} // namespace CoSeDi   {
} // namespace SS
