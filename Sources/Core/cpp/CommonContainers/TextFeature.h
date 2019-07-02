//TextFeature.h

#pragma once

#include "..\ASCInterface\ICommonContainers.h"
#include "..\ASCInterface\ITextFeature.h"
#include "..\ASSInterface\IBlackBox.h"
#include <list>

namespace SS
{
	namespace Core
	{
		namespace CommonContainers
		{

			using SS::Interface::Core::CommonContainers::ITextFeature;
			using SS::Interface::Core::BlackBox::IBlackBoxTextStorage;
			using SS::Interface::Core::CommonContainers::ITitle;
			using SS::Interface::Core::ResourceManagers::ILoadManager;
				
			///������������ ������������� ������ (���� � ������ � ����.)
			/**
			������������� ����� ������� ����������
			� ����� ���� � �������������� ��
			������ ���� (��� ����������� �������� � ��������� ����)
			*/
			class CTextFeature : public ITextFeature
			{
			private:
				ITextFeature*			m_pItemTextFeature;
				IBlackBoxTextStorage*	m_pBlackBoxTextStorage;
			public:
			  //������������
				CTextFeature();
				virtual ~CTextFeature();

			  //������������� ����� IBase
				///������������� ��������� �� ���� ��������
				virtual void SetLoadManager(ILoadManager* pLoadManager);

			  //������ IBase
				virtual ULONG Release();
				virtual HRESULT QueryInterface(REFIID pIID, void** pBase);	//���������� � ���������� � �������� REFIID. 
																			//pBase ����� NULL, ���� ������ ��������� �� ��������������
			  //������ ITextFeature
				virtual ITitle* GetFirstTitle();
				virtual void AddTitle(int nBegin, int nEnd, int iType);
				
				virtual void GetTextFeatureBuff(char** ppBuff, unsigned int* pSize);
				virtual void SetTextFeatureBuff(char* pBuff, unsigned int Size);
				///�������� ���� � ������
				virtual const wchar_t* GetTextPath();										
				///�������� ���� � ������
				virtual void SetTextPath(const wchar_t* szPath);							
				///�������� ��� ������
				virtual const wchar_t* GetTextName();										
				///�������� ��� ������
				virtual void SetTextName(const wchar_t* szName);							
				///�������� ����� �������
				virtual const char* GetAccessRights();									
				///�������� ����� �������
				virtual void SetAccessRights(const char* szAccessRights);				
				///�������� ��� ����
				//virtual const char* GetBaseName();										
				///�������� ��� ����
				//virtual void SetBaseName(const char* szName);							
				///������� �������� ��������������
				virtual void Clear();													
				///������������ ����������� ������ ������� ����������� ������
				virtual void SetFirstSentenceAbsNumber(unsigned int uiValue);			
				///��������� ����������� ������ ������� ����������� ������
				virtual unsigned int GetFirstSentenceAbsNumber();						
				///������������ ������ ������
				virtual void SetTextNumber(unsigned int uiValue);
				///��������� ������ ������
				virtual unsigned int GetTextNumber();
				///������������ ������� ������
				virtual void SetTextSize(unsigned int uiValue);
				///��������� ������� ������
				virtual unsigned int GetTextSize();
				///������ ����� ���������� ��������� ����� � �������
				virtual const FILETIME GetTextFileTime() const;
				///������������� ����� ���������� ��������� ����� � �������
				virtual void SetTextFileTime(const FILETIME* pFileTime);
				///������������� ������ ����� ������
				virtual void SetTextFileSize(const unsigned int ulFileSize);
				///���������� ������ ����� ������
				virtual const unsigned int GetTextFileSize() const;
				///������������� ID �������
				virtual void SetPluginID(const unsigned int uiPluginID);
				///���������� ID �������
				virtual const unsigned int GetPluginID() const;
			};


		}
	}
}