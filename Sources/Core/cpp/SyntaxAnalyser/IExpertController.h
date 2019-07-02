#pragma once

#include <string>
#include <map>
#include <iostream>
#include <atlbase.h>
#include <atldbcli.h>
using namespace std;

#include "Board.h"
#include "ParsingType.h"
#include "../ASCInterface/IInterface.h"
#include "../ASSInterface/IBlackBoxItems.h"
#include "../ASSInterface/ICommon.h"

// {3470A3FA-B115-41b6-BF83-418AC65E6DD2}
static const GUID CLSID_ExpertController = 
{ 0x3470a3fa, 0xb115, 0x41b6, { 0xbf, 0x83, 0x41, 0x8a, 0xc6, 0x5e, 0x6d, 0xd2 } };

// {D6D2501D-80D3-465b-AA3D-FB2AED893BFF}
static const GUID CLSID_ExpertController_RusNQ = 
{ 0xd6d2501d, 0x80d3, 0x465b, { 0xaa, 0x3d, 0xfb, 0x2a, 0xed, 0x89, 0x3b, 0xff } };

// {81E49010-922F-42ff-B3A7-5E6DD61F674D}
static const GUID IID_ExpertController = 
{ 0x81e49010, 0x922f, 0x42ff, { 0xb3, 0xa7, 0x5e, 0x6d, 0xd6, 0x1f, 0x67, 0x4d } };


namespace SS
{
	namespace Interface
	{
		namespace Syntax
		{
			///��������� ���������� ���������.
			class IExpertController : public SS::Interface::IBase
			{
			public:
				///���������� ����������� ��� ������ � ��������� ���������
				virtual SS::Interface::Core::Common::ILoad* GetLoader() = 0;
				///������������� ������������� �����������
				virtual void SetSentence(SS::Interface::Core::BlackBox::ISentence* pSentence) = 0;
				///������������� ������������� ����������� ��� �������� �����
				virtual void SetSentenceTest( SS::Interface::Core::BlackBox::ISentence* pSentence,  
											  SS::Syntax::ExpertModel::ParsingType type ) = 0;
				///��������� ����������
				virtual void SetParams(bool bOneHyp, int iNumHyp) = 0;
				///��������� �������������� ������ ����������� � ������������ ��������� �������
				virtual void ParseSentenceDynamic(SS::Syntax::ExpertModel::ParsingType pType) = 0;
				///��������� ���������� ��������
				virtual void PerformStep() = 0;
				///��������� �� ����� ������� ������ ���������
				virtual void PerformGroup() = 0;
				///������������ ��������� ��������
				virtual void PerformVersion() = 0;
				///���������� ������, ����������� �������� ��������
				virtual std::wstring GetCurrentExpertString() = 0;
				///���������� "�����"
				virtual SS::Syntax::BoardElements::CBoard& GetBoard() = 0;
				///��������� �� ��������� �� ��������
				virtual bool IsVersioned() = 0;
			};
		}
	}
}