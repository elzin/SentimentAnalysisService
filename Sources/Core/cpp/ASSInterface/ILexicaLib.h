#pragma once

#include "..\assinterface\iblackbox.h"
#include "..\ascinterface\ilinguisticprocessor.h"

#include "IMainAnalyse.h"
#include "ICommon.h"


// {747F8F64-781E-474b-BB51-A516B1EEAFFE}
static const GUID CLSID_LexicaPrimary = 
{ 0x747f8f64, 0x781e, 0x474b, { 0xbb, 0x51, 0xa5, 0x16, 0xb1, 0xee, 0xaf, 0xfe } };

// {CAEFF0C4-D83B-4124-9254-8F0F4051EF5D}
static const GUID CLSID_Lexica = 
{ 0xcaeff0c4, 0xd83b, 0x4124, { 0x92, 0x54, 0x8f, 0xf, 0x40, 0x51, 0xef, 0x5d } };

// {FCEC0C30-CA10-4b05-9DB3-6056E769EB8C}
static const GUID IID_LexicaPrimary = 
{ 0xfcec0c30, 0xca10, 0x4b05, { 0x9d, 0xb3, 0x60, 0x56, 0xe7, 0x69, 0xeb, 0x8c } };

// {6DA5178C-46A3-485e-BF38-C5F0FA8E5F71}
static const GUID IID_Lexica = 
{ 0x6da5178c, 0x46a3, 0x485e, { 0xbf, 0x38, 0xc5, 0xf0, 0xfa, 0x8e, 0x5f, 0x71 } };


namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			namespace LexicalAnalyze
			{					
				///��������� ���������� ����������� ������������
				class ILexica :
					virtual public SS::Interface::Core::ILexicaPrimary,
					virtual public SS::Interface::Core::Common::CAnalyseParams
				{
				public:
					virtual ~ILexica() {}
				public:
					/// ������ ������, ������������� � ������������ ��������� ������ � ������ ���������� � ��������
					virtual void AnalyzeDocStructure(SS::Interface::Core::BlackBox::IText* pText) = 0;
					/// ������ ������, ������������� � ������������ ��������� ������ � ������ ���������� � ��������
					virtual void AnalyzeNext(SS::Interface::Core::BlackBox::IText* pText, vector<vector<wstring>> *pParagraphs, bool isSimple = false, int mode = 1) = 0;
					
					virtual void AnalyzeNextSentence(SS::Interface::Core::BlackBox::IText* pText, bool isSimple = false, int mode = 1) = 0;
					/// ��������� ��������
					virtual void FillSynonyms(SS::Interface::Core::BlackBox::IText* pText) = 0;
					/// ��������� �������������� ���� ��� �����
					virtual void SetSemanticType(SS::Interface::Core::BlackBox::IUnit* pUnit, SS::Core::Features::Types::TSemanticType semanticType) = 0;
					/// ��������, ��� ���� ����� �������� ������������� ���
					virtual bool IsSemanticType(SS::Interface::Core::BlackBox::IUnit* pUnit, SS::Core::Features::Types::TSemanticType semanticType) = 0;
					///// ��������� ���������� �������
					//virtual void SetAfterSyntaxAnalyzeParams(SS::Interface::Core::MainAnalyse::IAfterSyntaxAnalyseParams* pAnalyseParams) = 0;
					///// ���������� ������� ����� ��������������� �������
					//virtual bool AnalyzeAfterSyntax(SS::Interface::Core::BlackBox::IText* pText)=0;
				};
			};
			

//			///��������� ������ ������������ �������
//			class ILexicAnalyze : public virtual SS::Interface::IBase//,
////						public SS::SMInterface::IWorkWithManagerConnections
//			{
//			public:
//			////////////////////////////////////////////////////////////////////
//			/*������� ��� ������ � ������� ����� �������*/
//				///������������� �������� ������� ������
//				virtual void Init(
//					///��������� �������
//					SS::Interface::Core::MainAnalyse::IAnalyseParams* pAnalyseParams, 
//					///����� ��� �������
//					SS::Core::Types::IndexationSearch::TNativeText* pNativeText) = 0;
//
//				///������ ��������� ����� ������ � ��������� ���������� � pText
//				virtual bool AnalyseNext(
//					///��� ���� ���������� ���������
//					SS::Interface::Core::BlackBox::IText* pText) = 0;
//
//				/// ���������� ������ �� ������������� �������
//				/** 
//					\param pQuery - ��������� ���������� ����������� ������ (��������� � ���������� pQuery)
//					\return bool - ������ - ���� �� ���� ������
//				 
//				�� ������ ���� ������� ������ ���� ������ ����� Init � ���������� - ������ ������� , ����� 
//				AnalyseNext(...)
//				*/
//				virtual bool QueryToSearchString(SS::Interface::Core::BlackBox::IText* pQuery,
//					std::string * pSearchString)=0;
//
//				virtual bool SyntaxQuestionPostProcess(SS::Interface::Core::BlackBox::IText* pQuery)=0;
//
//				ILexicAnalyze(void){};
//				virtual ~ILexicAnalyze(){};
//
//			};

			/////������ � ������� ����� � ������
			//struct SWordPosition{
			//	///����� �����
			//	unsigned int nWordNumber;
			//	///������
			//	unsigned int iBegin;
			//	///�����
			//	unsigned int iEnd;
			//};

			/////������ �������� SWordPosition
			//typedef list<SWordPosition> TWordPositionList;

			////////////////////////////////////////////////////////////////////////////
			/////����� ����� ����������� � �������
			//class IWordPosition : public virtual SS::Interface::IBase
			//{
			//public:
			//	//////////////////////////////////////////////////////////////////////////
			//	///������������� ������� ����� ���������� ������ �������
			//	virtual void Init(const char* szbuf) = 0;
			//	///��������� ������ ������� �� ������ �����
			//	virtual unsigned int GetPosition(unsigned int nWordNumber) = 0;

			//	///��������� � ��������� ������� �������� ������ � ����� ����� �� ���������� ������� ����
			//	virtual void GetPositions(wchar_t* pwchText, unsigned int iLength, TWordPositionList* p_list_WordPositions) = 0;

			//	IWordPosition(void){};
			//	virtual ~IWordPosition(){};

			//};

			/////������� ��� ������ �� ������� ��� ������� ���������� � ��������
			//class IWordEncoding : public virtual SS::Interface::IBase
			//{
			//public:

			//	///������������� �������
			//	/**��� ���� ����� �� ����������� ��������� ������ ���� �� ����� �������
			//	*/
			//	virtual void Init(const char* buff) = 0;
			//	///��������� ������� �����
			//	virtual bool GetWord(char* szWord) = 0;
			//	///����� ��������� �����
			//	/**
			//	\param pszWord ������� �����
			//	\param EntryPoints ������ ��������� ���������
			//	*/
			//	virtual void Find ( char *pszWord, std::list<int> *EntryPoints ) = 0;

			//	///����� ��������� ���� ����
			//	/**
			//	\param AllWords �����
			//	\param AllEntryPoints ������ ������� ��������� ���������
			//	*/
			//	virtual void FindAll( std::vector<string> AllWords, std::vector< std::list<int> > *AllEntryPoints) = 0;

			//	IWordEncoding(void){};
			//	virtual ~IWordEncoding(){};

			//};
		}
	}
}
