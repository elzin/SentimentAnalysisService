#pragma once

#include "../../ASSInterface/TDictionaryManager.h"
#include "../../ASCInterface/IDBMS.h"
#include "../../ASCInterface/defines.h"
#include "../../ASSInterface/ICommon.h"
#include "../../ASSInterface/TDBMS_Names.h"

namespace SS   {
	namespace Dictionary   {
		namespace Core   {

			class IMorphoTypesSearch   {

				public:

					/// ������������� ���� � ������ ������ � ��������� �� ��������� ���� IDataBase (��� ������ Load())
					virtual BOOL Init(
						/// ���� � ������ ������
						IN  CONST _TCHAR * pszPathToDataFiles,
						/// ��������� �� ��������� ���� IDataBase (��� ������ Load())
						IN  SS::Interface::Core::DBMS::IDataBase * pIDataBase = NULL) = 0;

					/// ���������/������������� �������
					virtual BOOL Load(VOID) = 0;

					/// ����������� ������
					virtual BOOL Clear(VOID) = 0;

					/// ��������� ����� ���������� ��� ������������ ������
					/** 
						\param oIDType - ����� ���� ����������������
						\param oIDForm - ����� ���������
						\param oIDEnding - ������ ���������
						\param oMorphoInfo - �������������� �������� ��������������� ����������
						\param oSpecialMorpho - �������������� �������������� ��������������� ����������
						\return BOOL - ��������� ��������
					*/
					BOOL AddInfo(
						IN  SS::Dictionary::Types::TIDType        oIDType,
						IN  SS::Dictionary::Types::TIDForm        oIDForm, 	
						IN  SS::Dictionary::Types::TIDEnding      oIDEnding, 
						IN  SS::Dictionary::Types::TMorphoInfo    oMorphoInfo, 
						IN  SS::Dictionary::Types::TSpecialMorpho oSpecialMorpho);


					/// ������������ ����� ���������� �� ��������� �� ������� ������������ �������������
					/** 
						\param oIDType - ����� ���� ����������������
						\param oIDEnding - ������ ���������
						\param p_l_MorphoType - ��������� �� ������ ��������, ���������� ������ ���������� �� ���������
						\return BOOL - ��������� ��������
					*/
					virtual BOOL GetByForm(
						IN  SS::Dictionary::Types::TIDType oIDType, 
						IN  SS::Dictionary::Types::TIDEnding oIDEnding, 
						OUT std::list<SS::Dictionary::Types::SMorphoType> *p_l_MorphoType) = 0;

					/// ������������ ����� ���������� �� ������� ������������ ������������� �� ������� ����������
					/** 
						\param oIDType	- ��� ����������������
						\param oIDForm	- ������ ���������
						\param pIDEnding - ������ ���������
						\return BOOL - ��������� ��������
					*/
					virtual BOOL GetIDEndingByIDTypeAndIDForm(
						IN  SS::Dictionary::Types::TIDType oIDType, 
						IN  SS::Dictionary::Types::TIDForm oIDForm, 
						OUT SS::Dictionary::Types::TIDEnding * pIDEnding) = 0;

					/// ������������ ����� ��������������� ���������� �� ������� ��������� � ���� ���������������� 
					/** 
						\param oIDType - ��� ����������������
						\param oIDForm - ����� ���������
						\param pMorphoType - ��������� �� ������ ��������, ���������� ������ ���������� �� ���������
						\return BOOL - ��������� ��������
					*/
					virtual BOOL GetMorphoTypeByIDTypeAndIDForm(
						IN   SS::Dictionary::Types::TIDType oIDType, 
						IN   SS::Dictionary::Types::TIDForm oIDForm, 
						OUT SS::Dictionary::Types::SMorphoType * pMorphoType) = 0;

					/// ������������ ����� ���������� � ���� ���������� � ���� ����������������
					/** 
						\param oIDType - ��� ����������������
						\param p_l_MorphoType - ��������� �� ������ ��������, ���������� ������ ���������� �� ���������
						\return BOOL - ��������� ��������
					*/
					virtual BOOL GetMorphoTypesListByIDType(
						IN   SS::Dictionary::Types::TIDType oIDType, 
						OUT std::list<SS::Dictionary::Types::SMorphoType> * p_l_MorphoType) = 0;

					/// ������������ ����� ��������������� ���������� �� ���� ����������������
					/** 
						\param oIDType - ��� ����������������
						\param oIDForm - ����� ���������
						\param oIDType - ��� ����������������
						\param pMorphoInfo - �������������� �������� ��������������� ����������
						\param pSpecialMorpho - �������������� �������������� ��������������� ����������
						\return BOOL - ��������� ��������
					*/
					virtual BOOL GetMorphoInfoByIDType(
						IN   SS::Dictionary::Types::TIDType oIDType, 
						IN   SS::Dictionary::Types::TIDForm oIDForm, 
						OUT SS::Dictionary::Types::TMorphoInfo * pMorphoInfo, 
						OUT SS::Dictionary::Types::TSpecialMorpho * pSpecialMorpho) = 0;


               /// ������� �� IDType �������������� MorphoInfo
               /// ��������� ������� 12.04.05
               virtual BOOL GetMorphoInfoByIDType( 
                  IN   SS::Dictionary::Types::TIDType oIDType,
                  OUT SS::Dictionary::Types::TMorphoInfo * pMorphoInfo
               ) = 0;



				}; // class IMorphoTypesSearch

			} // namespace Core   {
		} // namespace Dictionary   {
} // namespace SS   {
