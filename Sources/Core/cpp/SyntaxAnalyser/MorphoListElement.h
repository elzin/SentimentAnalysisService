#pragma once

#include "../ASSInterface/IBlackBoxFeature.h"
#include "../ASSInterface/IBlackBox.h"
#include "../ASSInterface/IAMConverter.h"
#include "../ASSInterface/TDictionaryManager.h"

namespace SS
{
	namespace Syntax
	{
		namespace BoardElements
		{
			///������� ���������������� ������ �������� �����
			class CMorphoListElement
			{
			private:
				///��������������� ����
				SS::Core::Features::CMorphoFeature m_oMorphoFeature;
				///���� �� BlackBox
				SS::Interface::Core::BlackBox::IFeature* m_pFeature;
				///������ �� BlackBox
				SS::Interface::Core::BlackBox::IIndex* m_pIndex;
				///����� ���������
				SS::Interface::Core::AMConverter::IAMConverterMorpho* m_pAMConverterMorpho;
			
			private:
				///�������������� CMorphoFeature � IFeature 
				void UpdateIFeature();
			
			public:
				///�����������
				CMorphoListElement() : m_pFeature(NULL), m_pIndex(NULL), m_pAMConverterMorpho(NULL) {};
				///����������
				~CMorphoListElement(){};

				///������������� �������� �����������
				void Init( SS::Interface::Core::AMConverter::IAMConverterMorpho* converter,
						   SS::Interface::Core::BlackBox::IFeature* feature, 
						   SS::Interface::Core::BlackBox::IIndex* index, 
						   int unit_num = 0, bool isPerson = false);

				///���������� MorphoFeature
				SS::Core::Features::CMorphoFeature & GetMorphoFeature()
				{
					return m_oMorphoFeature;
				}
				///���������� ����� ����
				SS::Core::Features::Types::PartOfSpeechTypes GetPOST() const;
				///���������� ����� �������
				SS::Core::Features::Types::VerbForm GetVerbForm() const;
				///���������� ������������ �������
				SS::Core::Features::Types::TransitionalType GetTransType() const;
				///������������� MorphoFeature
				void SetMorphoFeature(SS::Core::Features::CMorphoFeature* feature)
				{
					m_oMorphoFeature.AssignMorphoFeature(feature);
					UpdateIFeature();
				}
				///�������� MorphoFeature
				void AddMorphoFeature(SS::Core::Features::CMorphoFeature* pMorphoFeature)
				{
					m_oMorphoFeature.AssignValidMorphoFeature(pMorphoFeature);
					UpdateIFeature();
				}
				///���������� ������ ������
				unsigned int GetIDSource() const 
				{
					SS::Dictionary::Types::TDictionaryIndex oIndexVal;
					m_pIndex->GetDictionaryIndex()->GetFirst(&oIndexVal);
					
					return oIndexVal.GetDictionaryIndexWithoutFlags();
				}
				///�������� ����
				void ReleaseFeature()
				{
					m_pFeature->ReleaseFeature();
				}
				///��������� ��������� �� IIndex
				SS::Interface::Core::BlackBox::IIndex* GetIndex();
				///operator==
				//bool operator==(const CMorphoListElement & rMorphoElement);
			};
		}
	}
}





