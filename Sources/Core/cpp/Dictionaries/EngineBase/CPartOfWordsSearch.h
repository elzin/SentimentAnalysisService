#pragma once

//	Windows Header Files

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <wchar.h>
#include <ctype.h>
#include <time.h>
#include <string>

//	SQL Std
#include <atldbcli.h>
#include <sqloledb.h>

//	STL
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>

#include <iomanip>
#include <iostream>

#include "IPartOfWordsSearch.h"

using namespace SS::Dictionary::Types;
using namespace SS::Dictionary::Core;
using namespace SS::Interface::Core;

namespace SS{ 
namespace Dictionary{
namespace Core{

		class CPartOfWordsSearch : public IPartOfWordsSearch, public OBJECT_LEVEL_LOCKABLE_SYNC_DEP<CPartOfWordsSearch, SCriticalSectionImplStategy, CURRENT_THREAD_DEBUG_INFO>   {

			public:

				/// �����������
				CPartOfWordsSearch(VOID);

				/// ����������� ���������� Init()
				CPartOfWordsSearch(
					/// ���� � ������ ������
					CONST _TCHAR * pszPathToDataFiles,
					/// ��������� �� ��������� ������� IDataTable (��� ������ Create())
					DBMS::IDataTable * pIDataTable);

				/// ������������� ���� � ������ ������ � ��������� �� ��������� ������� IDataTable (��� ������ Create())
				BOOL Init(
					/// ���� � ������ ������
					CONST _TCHAR * pszPathToDataFiles,
					/// ��������� �� ��������� ������� IDataTable (��� ������ Create())
					DBMS::IDataTable * pIDataTable);

				/// ����������
				~CPartOfWordsSearch(VOID);

				/// C������ �����, ���������� ������ � ������ ������
				BOOL Create(VOID);

				/// ���������/������������� �������
				BOOL Load(VOID);

            //���� � ��������� �������� ��� ������ � ������� �� ���������� Create, ����� Load;
            BOOL LoadIfFilesExists();

            /// ��������� ������� ������ ���� �� ��� �� ��� ��������
            BOOL LoadIfNeed();

            //��������� �� ������
            BOOL Empty(){ return !m_pTreeData && !m_pIdData; }

				/// ����������� ������
				BOOL Clear(VOID);

				/// ����� � ������� ���� ��������� ������� � �����, ��� ���� ��������� ��������� ����� �����, � �������� � ������� ������ ��������� ��������� �������� � �����.
				BOOL GetHypothesis(
					/// ������� ����� ��� ������
					IN CONST WCHAR * pwsPartOfWord,
					/// ������� � �����, � ������� ���������� ������ �����;  �.�. ���� ���������� ����� ����� �abc� ������ ����� 2, �ab� � 1 � �.�.
					IN INT iBeginPosition,
					/// ������ �������� ������, ����� ������� ���������� ������� reserve
					OUT std::vector< SS::Dictionary::Types::SHypothesisInfo > * p_v_HypothesisInfo,
					/// ����������� ���������� ����������, ��� ������� ����� ������������ � <p_v_SHypothesisInfo>
					IN INT iMinMatchSymbols);

				/// ���� ��� ��������� ���� ������ ���� � �� ��������
				BOOL GetByForm(
					/// ������� ����� ��� ������
					IN CONST WCHAR * pwsPartOfWord,
					/// ������� � �����, � ������� ���������� ������ �����
					IN INT iBeginPosition,
					/// ������ �������� ������, ����� ������� ���������� ������� reserve
					OUT std::vector< SPartOfWord > * p_v_PartOfWord,
					/// �������� ������: �� ������ ����� ��� ���
					IN BOOL isCompleteWord = FALSE);

				/// ���� ����� ����� �� �������
				BOOL GetFormById(
					/// ������ ��� ������
					IN UINT iID, 
					/// ��������� ����� �����
					OUT std::wstring * pwsPartOfWord);

			private:

				BYTE                    * m_pTreeData;
				UINT                      m_iTreeDataSize;
				BYTE                    * m_pTPtr;
				BYTE                    * m_pTLastPtr;

				BYTE                    * m_pIdData;
				UINT                      m_iIdDataSize;
				UINT32                  * m_pIdArr;
				UINT                      m_iIdNum;

				SPartOfWord               m_oPartOfWord;

				SHypothesisInfo                              m_oHypothesisInfo;
				std::vector< SHypothesisInfo >             * m_p_v_HypothesisInfo;
				INT                                          m_iHypLetterIdx;
				INT                                          m_iHypMatchSymbols;

				typedef BYTE *                               HypTreeBranch; 
				typedef std::set < HypTreeBranch >			 HypTreeBranchSet;
				typedef HypTreeBranchSet::const_iterator     HypTreeBranchItr;
				typedef std::pair< HypTreeBranchItr, bool >  HypTreeBranchPair;

				HypTreeBranchSet                             m_oHypTreeBranchSet; 
//				HypTreeBranchItr                             m_oHypTreeBranchItr;
				HypTreeBranchPair                            m_oHypTreeBranchPair;


				std::vector<std::wstring> m_oLfVecor;
				std::vector<UINT32>       m_oIdVecor;

				VOID                      m_fRectifyTreePtrs_RecurFunc(BYTE * pMem);
				VOID                      m_fCollectIdsForHypothesis_RecurFunc(BYTE * pMem, INT iLevel);
				VOID                      m_fCollectIdsForHypothesis_RecurFunc_ForLast(BYTE * pMem);
				BOOL                      m_fRectifyIdArrPtrs_IterFunc(UINT32 * pIdArr);
				VOID                      m_fMakeTreeBranchRecurFunc(UINT iCurNumOfLeters, std::vector<UINT> & roVectOfAllowedIdxs);
				INT                       m_fFindLetterIdx(wchar_t wcLetter, wchar_t * pLettersArr, UINT16 iLettersNum);
				BOOL                      m_fReadData(VOID);

				STLSTR                    m_sPathToDataFiles;
				DBMS::IDataTable        * m_pIDataTable;

		}; // class CPartOfWordsSearch : 

		/// �������� ����� ��� __FUNCTION__
		#define _F __FUNCTION__

		namespace PartOfWordsSearchDbg
		{
			/// ������ ��������� �� ������ � ������ �������
			HRESULT LogFail(char * pFuncName, char * pFormatStr, ...);

			/// ������ �������� ��������� � ������ �������
			VOID    LogMess(char * pFormatStr, ...);
		}


		/// ���������������� ������ ������ ��� �������� ������ ������
		#define TREE_MAX_SIZE   (10*1024*1024-128)

		/// �����. �����
		#define MEM_UINT32(pMem)                   *((UINT32 *)(pMem))
		/// �����. �����
		#define MEM_UINT16(pMem)                   *((UINT16 *)(pMem))
		/// �����. �����
		#define SET_MEM_UINT32_AND_INC(pMem,iVal)  *((UINT32 *)(pMem))=iVal, pMem+=sizeof(UINT32)
		/// �����. �����
		#define SET_MEM_UINT16_AND_INC(pMem,iVal)  *((UINT16 *)(pMem))=iVal, pMem+=sizeof(UINT16)


} //namespace SS
} //namespace Dictionary
} //namespace Core




