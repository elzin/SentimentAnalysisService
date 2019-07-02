#pragma once

#include "BlockVersionElement.h"
#include "BoardCommonTypes.h"
#include "Container.h"
#include "../ASSInterface/Constants.h"

namespace SS
{
	namespace Syntax
	{
		namespace BoardElements
		{
			///�������� ������� �����.
			class CBlockVersion
			{
			private:
				///��������� ��� ��������� ��������
				CContainer<VERELEMENT, 50/*SS::Constants::MAX_WORDS_IN_SENTENCE*/> m_VersionElements;
				///�������������� ��������
				SBlockVersionCharacteristics m_Characteristic;
				
			private:	
				///���������� �������������
				void FillCharacteristic();
				///���������� �������� ���������, ���������� � ���������� �������.
				int GetHeadCount();
				///���������� ������������� � ���������� ������� ���������
				int GetUnfilledCount();

			public:
				///���������� ������ ������� ��������
				PVERELEMENT GetFirst() const;
				///���������� ��������� �������� ��������
				PVERELEMENT GetNext() const;
				///���������� �������� ��������
				PVERELEMENT AddElement();
				///�������� ��������� ������� �� ����� �������� ���������
				bool operator<(CBlockVersion & version);
				///�������� ������������.
				CBlockVersion & operator=(const CBlockVersion & Version);
				///�������� ���� ��������� ��������
				void ClearAll();
				///���������� ������������� ��������
				const SBlockVersionCharacteristics* GetVersionCharacteristics();
				///�������� ���������� ��������
				bool IsValid();
			};

		}
	}
}