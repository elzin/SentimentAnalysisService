//SemanticService.cpp
#include "StdAfx.h"
#include ".\semanticservice.h"

namespace SS
{
namespace Syntax
{
namespace BoardElements
{

	///������������ ����
	using namespace SS::Core::Features;
	
	///�����������
	CSemanticService::CSemanticService()
		: m_pAMConverterSemantic(NULL),
		  m_pBlackBoxTextStorage(NULL),
		  m_pUnit(NULL),
		  m_IsModified(false)
	{
	}

	///��������=
	void CSemanticService::operator=(const CSemanticService & v)
	{
		m_oSemanticContainer = v.m_oSemanticContainer;
		m_oSemanticFeature.AssignSemanticFeature(&v.m_oSemanticFeature);
		m_pUnit = v.m_pUnit;
		m_pAMConverterSemantic = v.m_pAMConverterSemantic;
		m_pBlackBoxTextStorage = v.m_pBlackBoxTextStorage;
		m_IsModified = v.m_IsModified;
	}

	///����������� �����������
	CSemanticService::CSemanticService(const CSemanticService & v) : m_oSemanticContainer(v.m_oSemanticContainer)
	{
		m_oSemanticFeature.AssignSemanticFeature(&v.m_oSemanticFeature);
		m_pUnit = v.m_pUnit;
		m_pAMConverterSemantic = v.m_pAMConverterSemantic;
		m_pBlackBoxTextStorage = v.m_pBlackBoxTextStorage;
		m_IsModified = v.m_IsModified;
	}

	///�������� ����������
	bool CSemanticService::BadPtr()
	{
		if ( (!m_pAMConverterSemantic) || (!m_pBlackBoxTextStorage) || (!m_pUnit) )
		{ return true; }
		return false;
	}
	
	///�������� �������� Undefine �� �������� ������������� ����
	void CSemanticService::UndefineSemantic()
	{
		//���������� ���
		const unsigned int Count = m_oSemanticFeature.GetFeatureCount();
		//�������� ����
		unsigned int iValue = 0;
		//������� ���
		for (unsigned int i = 0; i < Count; ++i)
		{
			//�������� ��������
			iValue = m_oSemanticFeature.GetFeature(i)->GetValue();
			//���� ���� ������ �� ����� �������� ��������
			if (iValue == 0) 
			{ iValue = 1; /*������ undefined*/ }
			//���������� ��������
			m_oSemanticFeature.GetFeature(i)->SetValue(iValue);	
		}
	}

	///�������� ����
	void CSemanticService::ZeroSemantic()
	{
		//���������� ���
		const unsigned int Count = m_oSemanticFeature.GetFeatureCount();
		//�������� ����
		const unsigned int iValue = 0;
		//������� ���
		for (unsigned int i = 0; i < Count; ++i)
		{ m_oSemanticFeature.GetFeature(i)->SetValue(iValue); }
	}
	
	///������������� ����� ���������
	void CSemanticService::GenerateSemantic()
	{
		//�������� ����
		ZeroSemantic();
		//�������
		for (SSemanticData* pSemanticData = m_oSemanticContainer.GetFirst(); pSemanticData; pSemanticData = m_oSemanticContainer.GetNext())
		{ 
			//���� ������� �� �������� �� ����������
			if (pSemanticData->oMark == mDelete)
			{ continue; }
			m_oSemanticFeature.AssignOR(&pSemanticData->oSemanticFeature); 
		}
		//����������� undefine ��� 0
		UndefineSemantic();
	}
	
	///��������� ������� ����������� � ������� �����
	void CSemanticService::ApplyConstructionObject( SS::SyntaxConstructions::Types::CConstructionObject* pObject,
												    const CSemanticService* pSemanticServiceBase )
	{
		SS_TRY
		{
			//�������� ������
			if (BadPtr())
			{ SS_THROW(L"������������ ������ ��� ���������� ��������."); }
			
			//�������� ������
			if (pObject->m_SemanticFeatureAposteriori.m_OperationMod.Equal(Values::OperationMod.opmRemove))
			{
				Remove(pObject);
			}
			else if (pObject->m_SemanticFeatureAposteriori.m_OperationMod.Equal(Values::OperationMod.opmSelect)) 
			{
				Select(pObject);
			}
			else if (pObject->m_SemanticFeatureAposteriori.m_OperationMod.Equal(Values::OperationMod.opmAdd)) 
			{
				Add(pObject);
			}
			else if (pObject->m_SemanticFeatureAposteriori.m_OperationMod.Equal(Values::OperationMod.opmAppoint)) 
			{
				Appoint(pObject);
			}

			//���� ���� ������, �� ��������� ���������
			if (pSemanticServiceBase)
			{
				Inherit(pSemanticServiceBase);
			}
		}
		SS_CATCH(L"")
	}

	///���������� ����
	void CSemanticService::SetUnit(SS::Interface::Core::BlackBox::IUnit* pUnit)
	{ 
		if (pUnit == NULL) 
		{ SS_THROW(L"������������� NULL-��"); }
		m_pUnit = pUnit; 
	}
	
	///���������� ������������� ���������
	void CSemanticService::SetSemanticConverter(SS::Interface::Core::AMConverter::IAMConverterSemantic* pAMConverterSemantic)
	{ 
		if (pAMConverterSemantic == NULL) 
		{ SS_THROW(L"������������� NULL-��"); }
		m_pAMConverterSemantic = pAMConverterSemantic; 
	}

	///���������� BlackBox �������
	void CSemanticService::SetTextStorage(SS::Interface::Core::BlackBox::IBlackBoxTextStorage* pBlackBoxTextStorage)
	{
		if (pBlackBoxTextStorage == NULL) 
		{ SS_THROW(L"������������� NULL-��"); }
		m_pBlackBoxTextStorage = pBlackBoxTextStorage;
	}

	///�������� ���������
	void CSemanticService::AddSemantic( SS::Interface::Core::BlackBox::IIndex* pIndex,
										SS::Core::Features::CSemanticFeature* pSemanticFeature,
										EMark oMark )
	{
		SSemanticData* pSemanticData = m_oSemanticContainer.Add();
		if (!pSemanticData) 
		{ SAVE_LOG(SS_WARNING AND __WFUNCTION__ AND L"���������� ������� ���������� ������������� �������������."); return; }
		pSemanticData->pIndex = pIndex;
		pSemanticData->oSemanticFeature.AssignSemanticFeature(pSemanticFeature);
		pSemanticData->oMark = oMark;
		m_IsModified = true;
	}

	///�������� ������ � ������
	void CSemanticService::Clear()
	{
		m_oSemanticContainer.Clear();
		m_oSemanticFeature.Undefine();
		m_pUnit = NULL;
		m_IsModified = false;
	}

	///�������� ������������� ����
	SS::Core::Features::CSemanticFeature & CSemanticService::GetSemanticFeature()
	{ 
		if (m_IsModified) 
		{
			m_IsModified = false;
			GenerateSemantic();
		}
		return m_oSemanticFeature; 
	}

	///�������
	void CSemanticService::Remove(SS::SyntaxConstructions::Types::CConstructionObject* pObject)
	{
		const unsigned int MIN_SIZE = 1;
		for ( SSemanticData* pSemanticData = m_oSemanticContainer.GetFirst(); (pSemanticData && (m_oSemanticContainer.Size() > MIN_SIZE)); 
			  pSemanticData = m_oSemanticContainer.GetNext() )
		{ 
			if ( pSemanticData->oSemanticFeature.IsIntersectsWith(pObject->m_SemanticFeatureAposteriori) )
			{
				//�������� �� ��������
				pSemanticData->oMark = mDelete;
				m_IsModified = true;
			}
		}
	}

	///���������� ��������� ��� ��������� �� ��������
	unsigned int CSemanticService::Size()
	{
		unsigned int uiSize = 0;
		for (SSemanticData* pSemanticData = m_oSemanticContainer.GetFirst(); pSemanticData; pSemanticData = m_oSemanticContainer.GetNext())
		{ 
			if (pSemanticData->oMark == mDelete) continue;
			++uiSize;
		}
		return uiSize;
	}
	
	///�������
	void CSemanticService::Select(SS::SyntaxConstructions::Types::CConstructionObject* pObject)
	{
		unsigned int uiSize = Size();
		std::list<SSemanticData*> oDelDataList;
		//�������
		for (SSemanticData* pSemanticData = m_oSemanticContainer.GetFirst(); pSemanticData; pSemanticData = m_oSemanticContainer.GetNext())
		{
			if (pSemanticData->oMark == mDelete) continue;
			if ( !pSemanticData->oSemanticFeature.IsIntersectsWith(pObject->m_SemanticFeatureAposteriori) )
			{ oDelDataList.push_back(pSemanticData); }
		}
		//��������
		if (oDelDataList.size() == uiSize)
		{ return; }
		else
		{
			std::list<SSemanticData*>::iterator it(oDelDataList.begin());
			for (it; it != oDelDataList.end(); ++it)
			{
				//�������� �� ��������
				(*it)->oMark = mDelete;
				m_IsModified = true;
			}
		}
	}
	
	///���������
	void CSemanticService::Appoint(SS::SyntaxConstructions::Types::CConstructionObject* pObject)
	{
		//�������� �� �������� ��� ���������
		for (SSemanticData* pSemanticData = m_oSemanticContainer.GetFirst(); pSemanticData; pSemanticData = m_oSemanticContainer.GetNext())
		{ pSemanticData->oMark = mDelete; }
		//��������� � ���������
		AddSemantic(NULL, &pObject->m_SemanticFeatureAposteriori, mAdd);
	}
	
	///��������
	void CSemanticService::Add(SS::SyntaxConstructions::Types::CConstructionObject* pObject)
	{
		//��������� � ���������
		AddSemantic(NULL, &pObject->m_SemanticFeatureAposteriori, mAdd);
	}

	///������������ ��������� �� ��������� ��������
	void CSemanticService::Inherit(const CSemanticService* pSemanticServiceBase)
	{
		//������� ��������� �������� �����
		SSemanticData* pBaseSemanticData = pSemanticServiceBase->m_oSemanticContainer.GetFirst();
		for (pBaseSemanticData; pBaseSemanticData; pBaseSemanticData = pSemanticServiceBase->m_oSemanticContainer.GetNext())
		{ 
			//��������� � ���������
			AddSemantic(NULL, &pBaseSemanticData->oSemanticFeature, mAdd);
		}
	}

	///��������� ��������� ��������� � BlackBox
	void CSemanticService::UpdateBlackBox()
	{
		//������� ���� ���������
		for (SSemanticData* pSemanticData = m_oSemanticContainer.GetFirst(); pSemanticData; pSemanticData = m_oSemanticContainer.GetNext())
		{ 
			if (pSemanticData->oMark == mAdd)
			{
				//������� ����� ������
				SS::Interface::Core::BlackBox::IIndex* pIndex = m_pBlackBoxTextStorage->CreateIndex();
				m_pUnit->AddIndex(pIndex);
				//������ �������
				SS::Dictionary::Types::TDictionaryIndex oIndexVal;
				m_pAMConverterSemantic->Code(&pSemanticData->oSemanticFeature, &oIndexVal);
				oIndexVal.SetDictionaryNumber(SS::Dictionary::DATA_TYPE::NAMES::ednSemantic);
				pIndex->GetDictionaryIndex()->AppendIndex(oIndexVal);
				//����� �������
				pSemanticData->oMark = mUndefined;
				pSemanticData->pIndex = pIndex;
			}
			else if (pSemanticData->oMark == mDelete)
			{
				SS::Interface::Core::BlackBox::IIndex* pIndex = NULL;
				pIndex = pSemanticData->pIndex;
				if (pIndex)
				{ pIndex->ReleaseIndex(); }
				m_oSemanticContainer.DeleteCurrent();
			}
		}
	}

}
}
}