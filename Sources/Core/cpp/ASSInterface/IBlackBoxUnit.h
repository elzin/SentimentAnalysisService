#pragma once

#include "IBlackBoxIndex.h"
#include "IBlackBoxSyntaxUnit.h"
#include "CObligatory.h"
#include "TCitation.h"
#include "..\ASCInterface\TCoommonTypes.h"
#include <string>
#include <list>

namespace SS
{
	namespace Core
	{
		namespace BlackBox
		{
			namespace Types
			{
				struct SUnitInfo
				{
					SUnitInfo()
					{
						Clear();
					}

					void Clear()
					{
						_bIsSyntax = false;
						_shCommonFeature = 0;
						_uiFeature = 0;
						_PlaceType.SetValue(0);
						_TimeType.SetValue(0);
					}

					UINT _uiFeature;
					SS::Core::Features::Types::TSPlaceType _PlaceType;
					SS::Core::Features::Types::TSTimeIntervalType _TimeType;
					short _shCommonFeature;
					bool _bIsSyntax;
				};
			}
		}
	}
}


namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			namespace BlackBox
			{

				///���� ����������� (�����-�����)
				/**
					���� ������������ ����� ����� 
					��������������� ��������,
					������� ���� ��������� �������� � 
					���������� ������� ��������.
					���� ����� ����� � �������� ����� ������ �����.
					��������, ���� "UN" ����� ����� ����� ������ ������ 
					"United" � "Nations"
					*/
				class IUnit : public CObligation
				{
				public:
					/// ���������� ��������� �����
					virtual void AddUnitChild(IUnit *pUnit) = 0;
					/// ������� ������ �������� ������
					virtual std::list<IUnit*> GetChildList() = 0;

					/// ������������� ������� � �������������
					virtual void SetTransPosition(unsigned char uchTransPosition) = 0;
					/// ���������� ������� � �������������
					virtual unsigned char GetTransPosition() = 0;
					
					/// ������������� ���������� ����� ����� � ������
					virtual void SetPosition(unsigned int uiPosition) = 0;
					/// ���������� ���������� ����� ����� � ������
					virtual unsigned int GetPosition() = 0;				

					/// ��������� ����������� ������ � ������ ������� ������� �����
					virtual unsigned int GetFirstCharPosition() = 0;
					/// ������������ ����������� ������ � ������ ������� ������� �����
					virtual void SetFirstCharPosition(unsigned int uiPosition) = 0;

					/// ������ ��� ��������� �������
					virtual SS::Core::Types::IndexationSearch::EHighlightType GetHighlightType() = 0;
					/// ��������� ��� ��������� �������
					virtual void SetHighlightType(SS::Core::Types::IndexationSearch::EHighlightType hlt) = 0;

					/// ������ ��� ��������� �������
					virtual bool GetIsInAnswerSentence() = 0;
					/// ��������� ��� ��������� �������
					virtual void SetIsInAnswerSentence(bool bIn) = 0;

					///��������� ���������� �������� �����
					virtual const wchar_t* GetWord() = 0;
					///������������ ���������� �������� �����
					virtual void SetWord(const wchar_t* wcWord) = 0;

					///������������� �������� ����� ����������
					virtual void SetSyntaxFlag(bool bl) = 0;
					///��������� �������� ����� ����������
					virtual bool GetSyntaxFlag() = 0;

					///��������� ��������� �� ������������ �������������� �������������
					virtual ISyntaxFeature* GetSyntaxFeature() = 0;
					///�������� � ��������� ��������� �� ������������ �������������� �������������
					virtual ISyntaxFeature* CreateSyntaxFeature() = 0;

					///���������� �������
					virtual void AddIndex(IIndex* pIndex) = 0;
					///��������� ������� �������
					virtual IIndex* GetFirstIndex() = 0;
					///��������� ���������� �������
					virtual IIndex* GetNextIndex() = 0;

					///���������� ����� �� ������� ����
					virtual void AddUnitVertical(IUnit* pUnit) = 0;
					///���������� ����� ������ �� �����
					virtual void AddUnitHorizontal(IUnit* pUnit) = 0;

					///���������� �����, ������� ���������� ��������� ��� ����� �����, � ��� ��������� ���������� �������� ����� ����� 
					virtual void InsertUnitVertical(IUnit* pUnit) = 0;

					///����������� ������������������ ������
					/**������ ���� ���������� ����������� ������������������
					������ �� pLeft �� pRight
					�.�. ���������� ��������� ���� ������
					�������������� ����� ������ ����� ������ �������� � ���� ������*/
					virtual void JoinUpInterval(IUnit* pLeft, IUnit* pRight) = 0;

					///������� ���� �� ������, ��� ���� �� ������ ������, ������ ������ �� ���� ������
					virtual IUnit* Pop() = 0;

					///�������� ����� � ��� ���������
					/**�������� ����� � ��� ���������
					������ ��������� �� ������ ����*/
					virtual IUnit* ReleaseUnitHorizontal() = 0;
					///�������� ����� � ��� ���������
					/**�������� ����� � ��� ���������
					������ ��������� �� ��������*/
					virtual IUnit* ReleaseUnitVertical() = 0;

					///������� ���������� ����������, ������� �������� ���������
					virtual void ClearUnit() = 0;

					///��������� �������� ����� �����
					virtual IUnit* GetParentUnit() = 0;

					///��������� ������ ������(�������)�������� ����� �����
					virtual IUnit* GetLeftChildUnit() = 0;
					///��������� ������ �������(����������)�������� ����� �����
					virtual IUnit* GetRightChildUnit() = 0;

					///��������� ����� ����� �� �����
					virtual IUnit* GetLeftUnit() = 0;
					///��������� ����� ������ �� �����
					virtual IUnit* GetRightUnit() = 0;

					///��������� ���������� �����
					virtual unsigned int GetChildCount(void) = 0;
					///��������� ������� �����
					virtual bool HasChilds(void) = 0;
					/// ��������� ������� ������� ���� �������� � �������� �����
					virtual bool HasIndexType(SS::Interface::Core::BlackBox::EIndexType oIndexType, bool bIsAnalyseChild = false) = 0;

					/// �������� ��������� SUnitInfo
					virtual SS::Core::BlackBox::Types::SUnitInfo* GetInfo() = 0;
					/// �������� ��������� SUnitInfo
					virtual void ClearInfo() = 0;

					virtual int GetIsTargetObjectUnit() = 0;

					virtual int GetIsTargetObjectUnitFromParent() = 0;

					virtual void SetIsTargetObjectUnit(int bIsTargetObjectUnit) = 0;

					virtual unsigned int GetFirstCharPositionNew() = 0;
                    virtual int GetLastCharPositionNew(const wchar_t *pText) = 0;

					virtual void SetCitation(TCitation *cit) = 0;

					virtual TCitation* GetCitation() = 0;					

					virtual std::wstring GetWordFull() = 0;

					virtual IUnit* GetReferenceUnit() = 0;

					virtual void SetReferenceUnit(IUnit* unit) = 0;

					virtual bool IsVisual() = 0;

					virtual void SetIsTargetObjectUnitFromChilds(int bIsTargetObjectUnit) = 0;

					virtual int GetIsTargetObjectUnitFromChilds() = 0;

					virtual void SetTone(int nTone) = 0;

					virtual void SetToneStrong(int nTone) = 0;

					virtual int GetTone() = 0;
					
					virtual void SetRealTone(int nTone) = 0;

					virtual int GetRealTone() = 0;

					virtual void SetRealInversion(bool bInv) = 0;

	                virtual bool GetRealInversion() = 0;

					virtual void SetInversion(int nInversion) = 0;

					virtual int GetInversion() = 0;

					virtual void SetInverted(bool bInv) = 0;

					virtual bool GetInverted() = 0;

					virtual void SetTermNumber(int nTermNumber) = 0;

					virtual int GetTermNumber() = 0;

					virtual void SetStopWordUnit(int val) = 0;

					virtual int GetStopWordUnit() = 0;

					virtual void SetUnitToneDict(wchar_t* val) = 0;

					virtual wchar_t* GetUnitToneDict() = 0;

					virtual bool IsRusInitial() = 0;

					virtual bool IsInitial() = 0;

					virtual void SetFreeForTone(bool val) = 0;

					virtual bool GetFreeForTone() = 0;

					virtual void SetUnknownWord(bool val) = 0;

					virtual bool GetUnknownWord() = 0;

					virtual void SetPatternName(std::wstring val) = 0;

					virtual std::wstring GetPatternName() = 0;

					virtual void SetHashKey(__int64 val) = 0;

					virtual __int64 GetHashKey() = 0;

					virtual bool IsEvristicAbbr() = 0;
					
					virtual void SetEvristicLN(bool val) = 0;

					virtual bool GetEvristicLN() = 0;

					virtual void SetToneTermCount(int nTermNumber) = 0;

					virtual int GetToneTermCount() = 0;

					virtual void SetNumber(int val) = 0;

					virtual int GetNumber() = 0;	

					virtual void SetIsNominalOnly(bool val) = 0;

					virtual bool GetIsNominalOnly() = 0;

					//virtual void AddSemanticIndex(IIndex* pMorphoIndex, IIndex* pSemanticIndex) = 0;
				};
			}
		}
	}
}
