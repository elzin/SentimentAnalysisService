#pragma once

#include "IBlackBoxUnit.h"
#include "TMainAnalyseTypes.h"

#include "..\ASCInterface\ITextFeature.h"
#include "IXML.h"

#include <list>
using namespace std;


namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			namespace BlackBox
			{
				using SS::Interface::Core::CommonContainers::ITextFeature;

				/// ������������ ������ ��������� �����������
				enum eProcessed
				{
					/// �� ����������
					None,
					/// ���������� �������������� ������
					Syntax,
					/// �������� ��������
					Entities
				};

				///�����������
				class ISentence
				{
				public:
					///���������� ����� � �����
					virtual void AddUnit(IUnit* pUnit) = 0;

					///��������� ��������� �� ��������� �����������
					virtual ISentence* GetNextSentence() = 0;
					///��������� ��������� �� ����������� �����������
					virtual ISentence* GetPrevSentence() = 0;

					///��������� ��������� �� ������ ����
					virtual IUnit* GetFirstUnit() = 0;
					///��������� ��������� �� ��������� ����
					virtual IUnit* GetLastUnit() = 0;

					///������� �����������, ������� ��������� ���������� � �������� ���� ������
					virtual void ClearSentence() = 0;
					///�������� �����������, ������ ��������� �� ���������(������) �����������
					virtual ISentence* ReleaseSentence() = 0;

					/// ������������� ���� �����������
					virtual void SetLanguage(SS::Core::Types::EAnalyseLanguage eLanguage) = 0;
					/// ���������� ���� �����������
					virtual SS::Core::Types::EAnalyseLanguage GetLanguage() = 0;

					/// ������������� ������������� �����������
					virtual void SetRelevance(unsigned int uiRelevance) = 0;
					/// ���������� ������������� �����������
					virtual unsigned int GetRelevance() = 0;				

					virtual int isEnabled() = 0;

					virtual void SetEnabled(int test) = 0;

					virtual void GetLinearUnits(list<IUnit*>& allUnits) = 0;

					virtual void GetLinearUnitsFull(list<IUnit*>& allUnits) = 0;

					virtual void GetLinearUnitsNonEmpty(list<IUnit*>& allUnits) = 0;

					virtual int IsDigest() = 0;

					virtual void SetDigest(int val) = 0;

					virtual int IsPreDigest() = 0;

					virtual void SetPreDigest(int val) = 0;

					virtual int GetToneNeg() = 0;

					virtual void SetToneNeg(int val) = 0;

					virtual int GetTonePos() = 0;

					virtual void SetTonePos(int val) = 0;

					virtual ISentence* GetPrevSentenceLinear() = 0;

					virtual void SetPrevSentenceLinear(ISentence* val) = 0;

					virtual wstring GetMarkers() = 0;

					virtual void SetMarkers(wstring val) = 0;

					/// ���������� ���������� ���� ��������� �����������
					virtual eProcessed GetProcessed() = 0;
					/// ������ ���������� ���� ��������� �����������
					virtual void SetProcessed(eProcessed val) = 0;
				};

				///��������
				class IParagraph
				{
				public:
					///���������� ����������� � �����
					virtual void AddSentence(ISentence* pSentence) = 0;

					///��������� ��������� �� ��������� ��������
					virtual IParagraph* GetNextParagraph() = 0;
					///��������� ��������� �� ����������� ��������
					virtual IParagraph* GetPrevParagraph() = 0;

					///��������� ��������� �� ������ �����������
					virtual ISentence* GetFirstSentence() = 0;
					///��������� ��������� �� ��������� �����������
					virtual ISentence* GetLastSentence() = 0;

					///������� ���������, ������� ��������� ���������� � �������� ���� ���������
					virtual void ClearParagraph() = 0;
					///�������� ���������, ������ ��������� �� ���������(������) ��������
					virtual IParagraph* ReleaseParagraph() = 0;

					///���������� "�����" ���� ������� ������ ��������� �����
					virtual void SetIndexTypeName(const wchar_t* wszName) = 0;
					///��������� "�����" ���� ������� ������ ��������� �����
					virtual const wchar_t* GetIndexTypeName() = 0;
					/// ������������� ������������� ���������
					virtual void SetRelevance(int iRelevance) = 0;
					/// ���������� ������������� ���������
					virtual int GetRelevance() = 0;

					/// ���������� ��� ����� ���� 
					virtual SS::Core::Types::IndexationSearch::ETextCutType GetType() = 0;
					/// ������������� ��� ����� �����
					virtual void SetType(SS::Core::Types::IndexationSearch::ETextCutType eTextCutType) = 0;
					/// ���������� ������� ���������
					virtual unsigned int GetLevel() = 0;
					/// ������������� ������� ���������
					virtual void SetLevel(unsigned int uiLevel) = 0;
					/// ���������� ����� ������ ����� ���� �����
					virtual unsigned int GetNumber() = 0;
					/// ������������� ����� ������ ����� ���� �����
					virtual void SetNumber(unsigned int uiNumber) = 0;
				};

				///�����
				class IText : public SS::Interface::Common::IXMLStorage
				{
				public:
					///��������� ��������� �� �������������� ������
					virtual ITextFeature* GetTextFeature() = 0;

					///���������� ��������� � �����
					virtual void AddParagraph(IParagraph* pParagraph) = 0;

					///��������� ��������� �� ������ ��������
					virtual IParagraph* GetFirstParagraph() = 0;
					///��������� ��������� �� ��������� ��������
					virtual IParagraph* GetLastParagraph() = 0;

					///������� ������, ������� ��������� ���������� � �������� ���� ����������
					virtual void ClearText() = 0;
					///�������� ������
					virtual void ReleaseText() = 0;

					///�������� ������������� � �������������� ������� ������� ������ �� ����� ������ �������
					virtual void Normalize() = 0;
				};

			}
		}
	}
}
