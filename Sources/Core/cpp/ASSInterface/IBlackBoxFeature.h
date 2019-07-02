#pragma once


namespace SS
{
	namespace Interface
	{
		namespace Core
		{
			namespace BlackBox
			{
/// ������������ ��������������� � ���� ����������� �������������
/**
	������������ ��������������� � ���� ����������� �������������
	����������� ��� ��������� ����������
*/
				class IFeature
				{
				public:
					///������ ������ ���������� m_ulIndex
					virtual unsigned int GetMorphoIndex() = 0;
					///��������� ���������� ������ ���������� m_ulIndex
					virtual void SetMorphoIndex(unsigned int uiValue) = 0;
					///������  ����� ��������������� ���������� m_ulMorphoInfo
					virtual unsigned int GetMorphoInfo() = 0;
					///��������� ���������� ����� ��������������� ���������� m_ulMorphoInfo
					virtual void SetMorphoInfo(unsigned int uiValue) = 0;
					///������  ����� ��������������� ���������� m_ulPartOfSpeech
					virtual unsigned int GetPartOfSpeech() = 0;
					///��������� ���������� ����� ��������������� ���������� m_ulPartOfSpeech
					virtual void SetPartOfSpeech(unsigned int uiValue) = 0;

					///�������� ��������������
					virtual IFeature* ReleaseFeature() = 0;
					///������� �������� ��������������
					virtual void ClearFeature() = 0;
				};
			}
		}
	}
}
