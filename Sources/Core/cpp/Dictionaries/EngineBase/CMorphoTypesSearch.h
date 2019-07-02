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

#include "IMorphoTypesSearch.h"

using namespace SS::Dictionary::Types;
using namespace SS::Dictionary::Core;
using namespace SS::Interface::Core;

namespace SS{ 
namespace Dictionary{
namespace Core{


		class CMorphoTypesSearch : public IMorphoTypesSearch, public OBJECT_LEVEL_LOCKABLE_SYNC_DEP<CMorphoTypesSearch, SCriticalSectionImplStategy, CURRENT_THREAD_DEBUG_INFO>   {

			public:

				/// �����������
				CMorphoTypesSearch(VOID);

				/// ����������
				~CMorphoTypesSearch(VOID);

				/// ������������� ���� � ������ ������ � ��������� �� ��������� ���� IDataBase (��� ������ Load())
				BOOL Init(
					/// ���� � ������ ������
					IN  CONST _TCHAR * pszPathToDataFiles,
					/// ��������� �� ��������� ���� IDataTable (��� ������ Load())
					IN  SS::Interface::Core::DBMS::IDataBase * pIDataBase);

				/// ���������/������������� �������
				BOOL Load(VOID);

            /// ��������� ������� ������ ���� �� ��� �� ��� ��������
            BOOL LoadIfNeed();
            
            //��������� �� ������
            BOOL Empty(){ return m_oIDTypeMap.empty() ; }

				/// ����������� ������
				BOOL Clear(VOID);

			public:

				/// ��������� ����� ���������� ��� ������������ ������
				/** 
					\param oIDType - ����� ���� ����������������
					\param oIDForm - ����� ���������
					\param oIDEnding - ������ ���������
					\param oMorphoInfo - �������������� �������� ��������������� ����������
					\param oSpecialMorpho - �������������� �������������� ��������������� ����������
					\return bool - ��������� ��������
				*/
				BOOL AddInfo(
					IN  SS::Dictionary::Types::TIDType        oIDType,
					IN  SS::Dictionary::Types::TMorphoInfo    oMorphoInfo, 
					IN  SS::Dictionary::Types::TIDForm        oIDForm, 	
					IN  SS::Dictionary::Types::TIDEnding      oIDEnding, 
					IN  SS::Dictionary::Types::TSpecialMorpho oSpecialMorpho);

				/// ������������ ����� ���������� �� ��������� �� ������� ������������ �������������
				/** 
					\param oIDType - ����� ���� ����������������
					\param oIDEnding - ������ ���������
					\param p_l_MorphoType - ��������� �� ������ ��������, ���������� ������ ���������� �� ���������
					\return bool - ��������� ��������
				*/
				BOOL GetByForm(
					IN  SS::Dictionary::Types::TIDType oIDType, 
					IN  SS::Dictionary::Types::TIDEnding oIDEnding, 
					OUT std::list<SS::Dictionary::Types::SMorphoType> * p_l_MorphoType);

				/// ������������ ����� ���������� �� ������� ������������ ������������� �� ������� ����������
				/** 
					\param oIDType	- ��� ����������������
					\param oIDForm	- ������ ���������
					\param pIDEnding - ������ ���������
					\return bool - ��������� ��������
				*/
				BOOL GetIDEndingByIDTypeAndIDForm(
					IN  SS::Dictionary::Types::TIDType oIDType, 
					IN  SS::Dictionary::Types::TIDForm oIDForm, 
					OUT SS::Dictionary::Types::TIDEnding * pIDEnding);

				/// ������������ ����� ��������������� ���������� �� ������� ��������� � ���� ���������������� 
				/** 
					\param oIDType - ��� ����������������
					\param oIDForm - ����� ���������
					\param pMorphoType - ��������� �� ������ ��������, ���������� ������ ���������� �� ���������
					\return bool - ��������� ��������
				*/
				BOOL GetMorphoTypeByIDTypeAndIDForm(
					IN  SS::Dictionary::Types::TIDType oIDType, 
					IN  SS::Dictionary::Types::TIDForm oIDForm, 
					OUT SS::Dictionary::Types::SMorphoType * pMorphoType);

				/// ������������ ����� ���������� � ���� ���������� � ���� ����������������
				/** 
					\param oIDType - ��� ����������������
					\param p_l_MorphoType - ��������� �� ������ ��������, ���������� ������ ���������� �� ���������
					\return bool - ��������� ��������
				*/
				BOOL GetMorphoTypesListByIDType(
					IN  SS::Dictionary::Types::TIDType oIDType, 
					OUT std::list<SS::Dictionary::Types::SMorphoType> * p_l_MorphoType);

				/// ������������ ����� ��������������� ���������� �� ���� ����������������
				/** 
					\param oIDType - ��� ����������������
					\param oIDForm - ����� ���������
					\param oIDType - ��� ����������������
					\param pMorphoInfo - �������������� �������� ��������������� ����������
					\param pSpecialMorpho - �������������� �������������� ��������������� ����������
					\return bool - ��������� ��������
				*/
				BOOL GetMorphoInfoByIDType(
					IN  SS::Dictionary::Types::TIDType oIDType, 
					IN  SS::Dictionary::Types::TIDForm oIDForm, 
					OUT SS::Dictionary::Types::TMorphoInfo * pMorphoInfo, 
					OUT SS::Dictionary::Types::TSpecialMorpho * pSpecialMorpho);


            /// ������� �� IDType �������������� MorphoInfo
            /// ��������� ������� 12.04.05
            virtual BOOL GetMorphoInfoByIDType( 
               IN   SS::Dictionary::Types::TIDType oIDType,
               OUT SS::Dictionary::Types::TMorphoInfo *pMorphoInfo
               );

			private:

				typedef struct   {
				//	TIDForm              m_oIDForm;
					TIDEnding            m_oIDEnding;
					TSpecialMorpho       m_oSpecialMorpho;
				} TMorFormInfo;

				typedef std::vector< TMorFormInfo >                   TMorFormInfoVect;
				typedef TMorFormInfoVect::const_iterator              TMorFormInfoItr;

				typedef std::vector< TIDForm >                        TIDFormVect;
				typedef TIDFormVect::const_iterator                   TIDFormItr;

				typedef std::unordered_map < TIDEnding, TIDFormVect >   TEndingsAndFormsMap;
				typedef std::pair        < TIDEnding, TIDFormVect >   TEndingsAndFormsPair;
				typedef TEndingsAndFormsMap::const_iterator           TEndingsAndFormsItr;
				typedef std::pair< TEndingsAndFormsItr, bool >        TEndingsAndFormsRet;

				typedef struct   {
					TMorphoInfo          m_oMorphoInfo;
					TMorFormInfoVect     m_oMorFormInfoVect;
					TEndingsAndFormsMap  m_oEndingsAndFormsMap;
				} TIDTypeInfo;

				typedef std::unordered_map < TIDType, TIDTypeInfo >     TIDTypeMap;
				typedef std::pair        < TIDType, TIDTypeInfo >     TIDTypePair;
 				typedef TIDTypeMap::const_iterator                    TIDTypeItr;
				typedef std::pair< TIDTypeItr, bool >                 TIDTypeRet;

				TIDTypeMap                     m_oIDTypeMap; 
				TIDTypeItr                     m_oIDTypeItr;
				TIDTypeRet                     m_oIDTypeRet;

				TEndingsAndFormsItr            m_oEndingsAndFormsItr; 
				TEndingsAndFormsRet            m_oEndingsAndFormsRet;

				TIDTypeInfo                    m_oIDTypeInfoEmpty;
				TIDFormVect                    m_oIDFormVectEmpty;
				TMorFormInfo                   m_oMorFormInfoEmpty;

				STLSTR                         m_sPathToDataFiles;
				DBMS::IDataBase              * m_pIDataBase;

		}; // class CMorphoTypesSearch : 

		/// �������� ����� ��� __FUNCTION__
		#define _F __FUNCTION__

		namespace CMorphoTypesSearchDbg
		{
			/// ������ ��������� �� ������ � ������ �������
			HRESULT LogFail(char * pFuncName, char * pFormatStr, ...);

			/// ������ �������� ��������� � ������ �������
			VOID    LogMess(char * pFormatStr, ...);
		}

} //namespace SS
} //namespace Dictionary
} //namespace Core





