//SyntaxTest.h
#pragma once 

#ifdef _SS_UNITTESTS

#include "../../ASSInterface/ILexicaLib.h"
#include "../../ASSInterface/ISyntaxAnalyzer.h"
#include "../../ASSInterface/ISemanticAnalyze.h"

namespace SS
{
	namespace UnitTests
	{
		namespace Syntax
		{
			///����� ��� ������������ ������� ������
			class CSyntaxTest
			{
			private:
				///����������� ����������
				SS::Interface::Core::LexicalAnalyze::ILexica*			m_pLexic;
				///�������������� ����������
				SS::Interface::Core::ISyntaxAnalyzer*					m_pSyntax;
				///������������� ����������
				SS::Interface::Core::ISemanticAnalyze*					m_pSemantic;
				///���������� �������
				SS::Interface::Core::MainAnalyse::IAnalyseParams*		m_pQueryParams;
				///��������� ����������
				SS::Interface::Core::MainAnalyse::IAnalyseParams*		m_pIndexationParams;
				///�������� ��������
				SS::Interface::Core::ResourceManagers::ILoadManager*		m_pLoadManager;
				
				//��� �������
				enum EWorkType {eIndexation, eQuery};
				
			private:
				///���������� ��� ��� ������ Dictionary
				void RunDictionariesMagicCode(SS::Interface::Core::ResourceManagers::ILoadManager* pLoadManager);
				///��������� IText* �� ������������� ������
				SS::Interface::Core::BlackBox::IText* GetText(std::wstring str, EWorkType type);

			public:
				///�����������
				CSyntaxTest(SS::Interface::Core::ResourceManagers::ILoadManager*	pLoadManager);
				///����������
				~CSyntaxTest(){};
				///����� ����
				void TestCommon();
				///��������� �������� ������� ��� ����������
				void IndexationSpeedTest();
				///���� ��� ������� ����������
				void TestContainer();
			};
		}
	}
}

#endif