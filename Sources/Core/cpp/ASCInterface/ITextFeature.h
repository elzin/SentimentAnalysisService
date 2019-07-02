//ITextFeature.h
#pragma once

#include "IInterface.h"
// {82E5D81C-04A6-4e82-83F5-9380FAB6E732}
static const GUID CLSID_TextFeature = 
{ 0x82e5d81c, 0x4a6, 0x4e82, { 0x83, 0xf5, 0x93, 0x80, 0xfa, 0xb6, 0xe7, 0x32 } };
// {5D601B65-40C4-4875-91A7-36ED4F2E0DF1}
static const GUID IID_TextFeature = 
{ 0x5d601b65, 0x40c4, 0x4875, { 0x91, 0xa7, 0x36, 0xed, 0x4f, 0x2e, 0xd, 0xf1 } };

namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			namespace CommonContainers
			{
				class ITitle
				{
				public:
					virtual ~ITitle() {}
					///���������� ����� ������� ����� ���������
					virtual int GetFirstWord() = 0;
					///���������� ����� ���������� ����� ���������
					virtual int GetLastWord() = 0;
					///��� ���������
					virtual int GetType() = 0;
					///��������� �� ��������� ���������
					virtual ITitle* GetNextTitle() = 0;
				};

				///������������ ������������� ������ (���� � ������ � ����.)
				/**
				������������� ����� ������� ����������
				� ����� ���� � �������������� ��
				������ ���� (��� ����������� �������� � ��������� ����)
				*/
				class ITextFeature : public IBase
				{
				public:
					virtual ~ITextFeature(){};


					virtual void GetTextFeatureBuff(char** ppBuff, unsigned int* pSize) = 0;
					virtual void SetTextFeatureBuff(char* pBuff, unsigned int Size) = 0;


					///�������� ���� � ������
					virtual const wchar_t* GetTextPath() = 0;
					///�������� ���� � ������
					virtual void SetTextPath(const wchar_t* szPath) = 0;

					///�������� ��� ������
					virtual const wchar_t* GetTextName() = 0;
					///�������� ��� ������
					virtual void SetTextName(const wchar_t* szName) = 0;

					///�������� ����� �������
					virtual const char* GetAccessRights() = 0;
					///�������� ����� �������
					virtual void SetAccessRights(const char* szAccessRights) = 0;

					/////�������� ��� ����
					//virtual const char* GetBaseName() = 0;
					/////�������� ��� ����
					//virtual void SetBaseName(const char* szName) = 0;

					///������������ ����������� ������ ������� ����������� ������
					virtual void SetFirstSentenceAbsNumber(unsigned int uiValue) = 0;
					///��������� ����������� ������ ������� ����������� ������
					virtual unsigned int GetFirstSentenceAbsNumber() = 0;

					///������������ ������ ������
					virtual void SetTextNumber(unsigned int uiValue) = 0;
					///��������� ������ ������
					virtual unsigned int GetTextNumber(void) = 0;

					///������������ ������� ������
					virtual void SetTextSize(unsigned int uiValue) = 0;
					///��������� ������� ������
					virtual unsigned int GetTextSize(void) = 0;

					///������ ����� ���������� ��������� ����� � �������
					virtual const FILETIME GetTextFileTime() const = 0;
					///������������� ����� ���������� ��������� ����� � �������
					virtual void SetTextFileTime(const FILETIME* pFileTime) = 0;

					///������������� ������ ����� ������
					virtual void SetTextFileSize(const unsigned int ulFileSize) = 0;
					///���������� ������ ����� ������
					virtual const unsigned int GetTextFileSize() const  = 0;

					///������������� ID �������
					virtual void SetPluginID(const unsigned int uiPluginID) = 0;
					/// ���������� ID �������
					virtual const unsigned int GetPluginID() const  = 0;

					///������� �������� ��������������
					virtual void Clear() = 0;

					virtual ITitle* GetFirstTitle() = 0;
					virtual void AddTitle(int nBegin, int nEnd, int iType) = 0;
				};
			


			}
		}
	}
}