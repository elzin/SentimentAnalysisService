#pragma once

#include "..\ASSInterface\ISyntaxConstructions.h"
#include ".\dboSyntax.h"
#include ".\connect.h"

namespace SS
{
	namespace SyntaxConstructions
	{
		namespace SQL
		{
			class CDetectWordsGroups : public SS::Interface::Core::SyntaxConstructions::IDetectWordsGroups,
									   public SS::CConnectSQL				
			{
			public:
				///�����������
				CDetectWordsGroups(wchar_t* szBaseName);
				///����������
				~CDetectWordsGroups(){};
				///������� ������ ���� ��� ��������������
				bool CreateDetectWordsGroup( SS::SyntaxConstructions::Types::TDetectWordsGroup& oDetectGroup);
				///������� ������� ������ ���� ��� ��������������
				void DeleteDetectWordsGroup();
				///���������� ��� �������� ������ ���� ��� ��������������
				void GetWords(SS::SyntaxConstructions::Types::TDetectWordsGroup & oDetectGroup);
				///������� ������� ����� ��������� �� ������ ���� ��� �������������� � ������������� �����
				void SetWords(SS::SyntaxConstructions::Types::TDetectWordsGroup & oDetectGroup);
				///���������� ������ �� ����� � ������ ��� ��������������
				bool IsDetectWord(std::string & sDetectWord);
				///��������� � �������� ��� ��������� ������ 
				bool ToBinary();
			};
		}
		
		namespace DBMS
		{
			class CDetectWordsGroups : public SS::Interface::Core::SyntaxConstructions::IDetectWordsGroups,
									   public SS::CConnectDBMS
			{
			private:
				///��������� ����, �� �������� ����� �������������� �����
				enum EFindMode
				{
					efmByDetectWord,
					efmByDetectWordGroupName
				};
				///������ ���������� �� ������, ���������� ������ � DBMS �������
				void* TableRecord[2];
				///��������� ��� ������� � ������� DetectWordGroupName
				SS::SyntaxConstructions::Types::SDetectWordGroupName m_oDetectWordGroupName;
				///���������� ���������� ������������� ������
				bool m_TableInited;
			
			private:
				///������������� ���������� � ��������				
				void InitConnection();
			
			public:
				///�����������
				CDetectWordsGroups(wchar_t* szBaseName);
				///����������
				virtual ~CDetectWordsGroups(){};
				///C������ ������ ���� ��� ��������������
				bool CreateDetectWordsGroup(SS::SyntaxConstructions::Types::TDetectWordsGroup & oDetectGroup);
				///������� ������� ������ ���� ��� ��������������
				void DeleteDetectWordsGroup();
				///���������� ��� �������� ������ ���� ��� ��������������
				void GetWords(SS::SyntaxConstructions::Types::TDetectWordsGroup & oDetectGroup);
				///������� ������� ����� ��������� �� ������ ���� ��� �������������� � ������������� �����
				void SetWords(SS::SyntaxConstructions::Types::TDetectWordsGroup & oDetectGroup);
				///���������� ������ �� ����� � ������ ��� ��������������
				bool IsDetectWord(std::string & sDetectWord);
				///���������� ��������� ���������� ������������� ������
				void SetRepeatTableInit() { m_TableInited = false; };
			};
		}
	}
}