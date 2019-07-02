#pragma once

#include "..\assinterface\iblackbox.h"


namespace SS
{
	namespace Semantic
	{
		namespace AnalysisExperts
		{
			namespace Question
			{

				///����� ����
				enum EPOS {
					eposNon,/// �������������
					eposAux,/// ��������������� ������
					eposVerbMain,/// �������� �����
					eposPrep,/// �������
					eposToBe,/// ����� ������� be
					eposTo,/// ������� to
					eposIn,/// ������� in
					eposFrom,/// ������� from
					eposLong,/// long
					eposQuestion,/// �������������� �����
					eposDet/// �������������
				};


				struct SMorphoDescription {
					/// ��������������� ��������������
					SS::Core::Features::CMorphoFeature  _oMorphoFeature;
					/// ����� ����
					EPOS _ePOS;
					
					SMorphoDescription(){  _ePOS=eposNon; };
					SMorphoDescription(const SMorphoDescription & oDesc){ this->_ePOS=oDesc._ePOS; this->_oMorphoFeature.Assign(&oDesc._oMorphoFeature); };
				};

				/// ���������� ��������� ��������������� ������������� ����� � ������ � ����
				class CQuestionFrameWork
				{
				private:

					typedef std::map<SS::Interface::Core::BlackBox::IUnit*,SS::Core::Features::CMorphoFeature> TUMF;

					typedef std::map<SS::Interface::Core::BlackBox::IUnit*,SS::Core::Features::CSemanticFeature> TUSF;

					typedef std::map<SS::Interface::Core::BlackBox::IUnit*,SMorphoDescription> TUMD;

				public:
					CQuestionFrameWork(void);
					~CQuestionFrameWork(void);

					SS::Core::Features::CMorphoFeature * GetUnitMorphoFeature(SS::Interface::Core::BlackBox::IUnit* pUnit);
					void AddUnitMorphoFeature(SS::Interface::Core::BlackBox::IUnit* pUnit,SS::Core::Features::CMorphoFeature & oMorphoFeature );

					SS::Core::Features::CSemanticFeature * GetUnitSemanticFeature(SS::Interface::Core::BlackBox::IUnit* pUnit);
					void AddUnitSemanticFeature(SS::Interface::Core::BlackBox::IUnit* pUnit,SS::Core::Features::CSemanticFeature & oSemanticFeature );

					SMorphoDescription * GetUnitDescription(SS::Interface::Core::BlackBox::IUnit* pUnit);
					void AddUnitDescription(SS::Interface::Core::BlackBox::IUnit* pUnit,SMorphoDescription & oDescription );

					void Clear();

				private:
					TUMF m_UnitMorphoFeature;
					TUSF m_UnitSemanticFeature;
					TUMD m_UnitDescription;
				};

			}
		}
	}
}