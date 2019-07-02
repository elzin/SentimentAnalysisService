#pragma once

#include "../ASCInterface/IInterface.h"
#include "./IBlackBoxItems.h"
#include "./Construction.h"

// {b1629ff1-9f26-42bb-b330-8afb33cb8c6d} 
static const GUID CLSID_ConstructionManager = 
{ 0xb1629ff1, 0x9f26, 0x42bb, { 0xb3, 0x30, 0x8a, 0xfb, 0x33, 0xcb, 0x8c, 0x6d } };

// {d83e285f-2106-41e6-8d72-98cb4d51640b} 
static const GUID IID_ConstructionManager = 
{ 0xd83e285f, 0x2106, 0x41e6, { 0x8d, 0x72, 0x98, 0xcb, 0x4d, 0x51, 0x64, 0x0b } };

namespace SS
{
	namespace Interface
	{
		namespace Test
		{
			///��������� ���������� ���������.
			class IConstructionManager :
				virtual public SS::Interface::IBase,
				virtual public SS::Interface::Core::Common::CAnalyseParams
			{
			public:
				typedef std::vector<SS::Interface::Core::BlackBox::IUnit *> TUnitsVector;
            typedef std::vector<TUnitsVector> TUnitsCombination;
	            
				//����� � ������ ������� ������������� ������������ ������� �����������.
				//��� ���� ������ ������� �������� ������� ������������ ����� ��������� ����������
				//������ ���������� ��� ������� �����������.
				//���� ��� ������������ ��� �����������, �� ������ ������� ��������� ��������������, 
				//�� � �� �������� ������� ������������� �������� �����������.
				typedef std::vector<TUnitsCombination> TDetectedUnits;

			public:
				// ������������ ����������� �� ����.
				// �����: true - �������� ������ ������
				virtual BOOL InitCounstructions() = 0;
				// ������� Construction ������� ������������.(��������� ����������� �������� ����������)
				// �����: true - �������� ������ ������
				virtual BOOL InitCounstructions( const SS::SyntaxConstructions::Types::CConstructionEx& Construction ) = 0;
				
///////////////////////////////////////////////////////////////////////
				/// ������������� ������������� �����������
				virtual void SetText(SS::Interface::Core::BlackBox::IText* pText) = 0;
///////////////////////////////////////////////////////////////////////				
				/// ������ ������� ��������� �����������; �� �� ��������� �� , ������ true, ���� ������� ����������� �� ���������
				virtual BOOL GetNextCounstruction() = 0;
				/// ���������� ���������� � ������� �����������
				virtual BOOL GetCurrentCounstructionInfo(SS::SyntaxConstructions::Types::CConstructionEx& oConstructionEx) = 0;
				/// ��������� ��������� �����������
				virtual BOOL ApplyCounstruction() = 0;

				/// ������ ������� ��������� ������; ������ true, ���� ������� ������ ����������� �� ���������
				virtual BOOL GetNextGroup() = 0;
				/// ���������� ���������� � ������� ������
				virtual BOOL GetCurrentGroupInfo(std::wstring & wName) = 0;
				/// ��������� �� ����� ������� ������ ���������
				/// ���� ����� ��������� ������� ������ ���������, � ����� ��� (GetNextCounstruction(), ApplyCounstruction()),
				/// �� ��������� ������� ������ �� �����
				virtual BOOL ApplyGroup() = 0;
///////////////////////////////////////////////////////////////////////
				/// ����� �������� ��������������� �������� ������� ����������� � pText � �������� ��������� 
				/// �� ��� � DetectedUnits
				virtual void GetDetectedUnits(TDetectedUnits& v_DetectedUnits) = 0;

            //��������� ������ ������ pText � ��������� ���� �� ���� FileName
            virtual void SaveTreeToFile(SS::Interface::Core::BlackBox::IText* pText, const std::wstring & FileName) = 0;
			};
		}
	}
}