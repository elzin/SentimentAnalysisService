#pragma once

#include "IBlackBoxFeature.h"
#include "IBlackBoxDictionaryIndex.h"


namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			namespace BlackBox
			{
/// ������������ ���������� ���������� �����
/** ������������ ���������� ���������� �����, ��������� �� �������,
	���������������� ��� ����������/������
*/
				class IIndex
				{
				public:
					///������������ �������� ����� ����������
					virtual void SetIndexationFlag(bool bl) = 0;
					///��������� �������� ����� ����������
					virtual bool GetIndexationFlag() = 0;

					///��������� ���������� ������� 
					virtual IDictionaryIndex* GetDictionaryIndex() = 0;

					///���������� �������������
					virtual void AddFeature(IFeature* pFeature) = 0;
					///��������� ������ ��������������
					virtual IFeature* GetFirstFeature() = 0;
					///��������� ��������� ��������������
					virtual IFeature* GetNextFeature() = 0;

					///������� ������ �� ������, ��� ���� �� ������ ������, ������ ������ �� ������ ������
					virtual IIndex* Pop() = 0;
					///�������� �������
					virtual IIndex* ReleaseIndex() = 0;
					///������� ����� �������, ������� ������� ������ �������������
					virtual void ClearIndex() = 0;
				};
			}
		}
	}
}
