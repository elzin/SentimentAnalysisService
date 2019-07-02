//ExpertSemantic.cpp
#include "StdAfx.h"
#include ".\expertsemantic.h"
#include "../ASCInterface/TDictionaryIndex.h"

namespace SS
{
namespace Syntax
{
namespace ExpertSemantic
{

	///������� ��� ��������� ����������� ��� ����� �� ��������� TMetro
	void CExpertSemantic::DetectMetro(SS::Syntax::BoardElements::CBoard & oBoard)
	{
		SS_TRY
		{
			//������������ ����
			using namespace SS::Core::Features;
			//����������� �������� ��� �.�
			Types::TMetro oMetroM;
			//����������� �������� ��� �.�
			Types::TMetro oMetroF;
			//���������� ��� �.�
			oMetroM.Assign(Values::TMetroType.smtMetroTupik);
			oMetroM.AssignOR(&Values::TMetroType.smtMetroProspekt);
			oMetroM.AssignOR(&Values::TMetroType.smtMetroProezd);
			oMetroM.AssignOR(&Values::TMetroType.smtMetroPereulok);
			oMetroM.AssignOR(&Values::TMetroType.smtMetroBulvar);
			oMetroM.AssignOR(&Values::TMetroType.Undefined);
			//���������� ��� �.�
			oMetroF.Assign(Values::TMetroType.smtMetroAlleya);
			oMetroF.AssignOR(&Values::TMetroType.smtMetroLiniya);
			oMetroF.AssignOR(&Values::TMetroType.smtMetroNaberezhnaya);
			oMetroF.AssignOR(&Values::TMetroType.smtMetroPloshad);
			oMetroF.AssignOR(&Values::TMetroType.smtMetroStreet);
			oMetroF.AssignOR(&Values::TMetroType.Undefined);
			//�������������� ��������
			unsigned int uiValue = 0;

			//������� ���������
			SS::Syntax::BoardElements::BoardElementsIterator it(oBoard.ElementsBegin());
			for (; it != oBoard.ElementsEnd(); ++it)
			{
				//��������� ��� �����-����
				CMorphoFeature & rMorphoFeature = (*it)->GetVerElem()->m_pMorpho->GetMorphoFeature();
				//��������� ��� ��������-����
				CSemanticFeature & rSemanticFeature = (*it)->GetSemanticFeature();
				//���������� ��������
				if (rSemanticFeature.m_SPCADMetro.IsUndefined())
				{ continue;	}
				//�������� ����
				if (rMorphoFeature.m_GenderType.Equal(Values::GenderType.gtMasculine))
				{
					uiValue = rSemanticFeature.m_SPCADMetro.GetValue() & oMetroM.GetValue();
					if (uiValue) 
					{ 
						rSemanticFeature.m_SPCADMetro.SetValue(uiValue);
						(*it)->RemoveUselessSemantic();
					}
				}
				else if (rMorphoFeature.m_GenderType.Equal(Values::GenderType.gtFemale))
				{
					uiValue = rSemanticFeature.m_SPCADMetro.GetValue() & oMetroF.GetValue();
					if (uiValue) 
					{ 
						rSemanticFeature.m_SPCADMetro.SetValue(uiValue);
						(*it)->RemoveUselessSemantic();
					}
				}
			}
		}
		SS_CATCH(L"")
	}
	
	///�������� �������� Undefine �� �������� ������������� ����
	void CExpertSemantic::DeleteUndefine(SS::Core::Features::CSemanticFeature* pSemFeature)
	{
		SS_TRY
		{
			//���������� ���
			const unsigned int Count = pSemFeature->GetFeatureCount();
			//�������� ����
			unsigned int iValue = 0;
			//������� ���
			for (unsigned int i = 0; i < Count; ++i)
			{
				//���� ���� �� undefined
				if ( !pSemFeature->GetFeature(i)->IsUndefined() )
				{ 
					//�������� ��������
					iValue = pSemFeature->GetFeature(i)->GetValue();
					//���� ���� ������ �� ����� �������� ��������
					if (iValue == 0) 
					{
						//������ undefined
						iValue = 1;
					}
					else
					{
						//������� undefined. �������� ������� ���
						iValue = iValue >> 1;
						iValue = iValue << 1;
					}
					//���������� ��������
					pSemFeature->GetFeature(i)->SetValue(iValue);
				}
			}
		}
		SS_CATCH(L"")
	}
	
	///������ �� �����
	bool CExpertSemantic::PassBoard(SS::Syntax::BoardElements::CBoard & oBoard)
	{
		SS_TRY
		{
			//�������� �����
			if (oBoard.GetLang() != SS::Core::Types::ealRussian)
			{ return false; }
			
			//��������
			SS::Syntax::BoardElements::CBoardElement* pBoardElementPr = NULL;
			
			//������� ���������
			SS::Syntax::BoardElements::BoardElementsIterator it(oBoard.ElementsBegin());
			for (; it != oBoard.ElementsEnd(); ++it)
			{
				pBoardElementPr = oBoard.GetParent(*it);
				if (pBoardElementPr == NULL)
				{ continue; }
				//����� � ������ ������ ������
				pBoardElementPr->GetSemanticFeature().AssignAND(&((*it)->GetSemanticFeature()));
				DeleteUndefine(&pBoardElementPr->GetSemanticFeature());
				pBoardElementPr->RemoveUselessSemantic();
			}
			//������� ������ � ���������� Metro
			DetectMetro(oBoard);
		}
		SS_CATCH(L"")
		return true;
	}

}
}
}