#include "stdafx.h"
#include "../FeatureLibrary/define.h"
#include "BlockVersion.h"

namespace SS
{
namespace Syntax
{
namespace BoardElements
{
	using namespace SS::Core::Features;

	//����������� ������
	
	//���������� �������� ���������, ���������� � ���������� �������.
	int CBlockVersion::GetHeadCount()
	{
		int retval = 0;
		for (PVERELEMENT pElem = m_VersionElements.GetFirst(); pElem; pElem = m_VersionElements.GetNext())
		{ if (pElem->m_isHead) retval++; }
		return retval;
	}

	//���������� ������������� � ���������� ������� ���������
	int CBlockVersion::GetUnfilledCount()
	{
		int retval = 0;
		for (PVERELEMENT pElem = m_VersionElements.GetFirst(); pElem; pElem = m_VersionElements.GetNext())
		{ if ( pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.IsUndefined() ) retval++;	}
		return retval;
	}

	//���������� �������������
	void CBlockVersion::FillCharacteristic()
	{
		m_Characteristic.m_headCount = GetHeadCount();
		m_Characteristic.m_unfilledCount = GetUnfilledCount();
		m_Characteristic.m_ObjectCount = m_Characteristic.m_SComplCount = m_Characteristic.m_mainCount = m_Characteristic.m_SFinCount = 0;
		m_Characteristic.m_isMainRoot = m_Characteristic.m_isVerbRoot = m_Characteristic.m_isSFin = m_Characteristic.m_isChain = 
		m_Characteristic.m_isInfBetween = m_Characteristic.m_isAdjunct = m_Characteristic.m_isVerbMet = m_Characteristic.m_isAdjAfterVerb = 
		m_Characteristic.m_isAdjBeforeVerb = m_Characteristic.m_isVerbAdjSCompl = false;

		PVERELEMENT pFirstElem = m_VersionElements.GetFirst();
		for (PVERELEMENT pElem = pFirstElem; pElem; pElem = m_VersionElements.GetNext())
		{
			if ( pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal(Values::SyntaxCategories.scMain) )
			{
				m_Characteristic.m_isMainRoot = true;
				m_Characteristic.m_mainCount++;
			}

			if ( pElem->m_isHead && (pElem->m_morphoFeatureApriori.m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postVerb)) )
			{ m_Characteristic.m_isVerbRoot = true; }

			if ( pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal(Values::SyntaxCategories.scSubjectFin) )
			{
				m_Characteristic.m_isSFin = true;
				m_Characteristic.m_SFinCount++;
			}

			if ( pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal(Values::SyntaxCategories.scChain) )
			{ m_Characteristic.m_isChain = true; }

			if ( pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.GetValue() & Values::SyntaxCategories.scSubjectComplement.GetValue() )
			{ m_Characteristic.m_SComplCount++; }

			if ( (pElem->m_isHead) && (pElem->m_morphoFeatureApriori.m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postOfficial)) &&
				(pElem->m_morphoFeatureApriori.m_OfficialType.Equal(Values::OfficialType.otInfMarker)) )
			{
				if ( (m_Characteristic.m_isSFin || m_Characteristic.m_isMainRoot) && 
					!(m_Characteristic.m_isSFin && m_Characteristic.m_isMainRoot) )
				{ m_Characteristic.m_isInfBetween = true; }
			}

			if ( pElem->m_morphoFeatureApriori.m_PartOfSpeechTypes.Equal(Values::PartOfSpeechTypes.postVerb) )
			{ m_Characteristic.m_isVerbMet = true; }

			if ( pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.GetValue() & Values::SyntaxCategories.scAjunct.GetValue() )
			{
				if (m_Characteristic.m_isVerbMet)
				{ 
					m_Characteristic.m_isAdjAfterVerb = true; 
				}
				else if (pElem != pFirstElem)
				{
					m_Characteristic.m_isAdjBeforeVerb = true;
				}
			}

			if ( pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal(Values::SyntaxCategories.scSubjectComplement) && m_Characteristic.m_isAdjAfterVerb )
			{ m_Characteristic.m_isVerbAdjSCompl = true; }

			if ( pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal( Values::SyntaxCategories.scAjunct ) ||
				 pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal( Values::SyntaxCategories.scAjunctCause ) ||
				 pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal( Values::SyntaxCategories.scAjunctGoal ) ||
				 pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal( Values::SyntaxCategories.scAjunctManner ) ||
				 pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal( Values::SyntaxCategories.scAjunctMeasure ) ||
				 pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal( Values::SyntaxCategories.scAjunctPlaceEnd ) ||
				 pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal( Values::SyntaxCategories.scAjunctPlaceFixedPoint ) ||
				 pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal( Values::SyntaxCategories.scAjunctPlaceSource ) ||
				 pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal( Values::SyntaxCategories.scAjunctTimeDuration ) ||
				 pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal( Values::SyntaxCategories.scAjunctTimeEnd ) ||
				 pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal( Values::SyntaxCategories.scAjunctTimeSource ) )
			{ m_Characteristic.m_isAdjunct = true; }

			if ( pElem->m_syntaxFeatureAposteriori.m_SyntaxCategories.Equal(Values::SyntaxCategories.scObject) )
			{ m_Characteristic.m_ObjectCount++; }
		}
		if ( !m_Characteristic.m_isMainRoot || !m_Characteristic.m_isSFin )
		{ m_Characteristic.m_isInfBetween = false; }
	}


	//������������� ������

    //���������� ������ ������� ��������
	PVERELEMENT CBlockVersion::GetFirst() const
	{
		return m_VersionElements.GetFirst();
	}
	
	//���������� ��������� �������� ��������
	PVERELEMENT CBlockVersion::GetNext() const
	{
		return m_VersionElements.GetNext();
	}

	//���������� �������� ��������
	PVERELEMENT CBlockVersion::AddElement()
	{
		PVERELEMENT pElem = m_VersionElements.Add();
		if (pElem) return pElem;
		SAVE_LOG(L"������� ������� ���������� ��������� ��������.");
        return NULL;		
	}

	//�������� ��������� ������� �� ����� �������� ���������
	bool CBlockVersion::operator<(CBlockVersion & oVer)
	{
		int verHeadCount = oVer.GetHeadCount();
		int ownHeadCount = this->GetHeadCount();
		if (verHeadCount != ownHeadCount)
		{ return (ownHeadCount < verHeadCount); }

		int verUnfilledCount = oVer.GetUnfilledCount();
		int ownUnfilledCount = this->GetUnfilledCount();
		if (ownUnfilledCount != verUnfilledCount)
		{ return (ownUnfilledCount < verUnfilledCount); }

		FillCharacteristic();		//���������� ����������� ������������� m_Characteristic
		oVer.FillCharacteristic();	//���������� ������������� m_Characteristic ��������� ��������
		
		//��������� ��� ������������� ������ (��������)
		SBlockVersionCharacteristics & VerCharacteristic = oVer.m_Characteristic;
		if (m_Characteristic.m_isMainRoot ^ VerCharacteristic.m_isMainRoot) 
		{
			if (m_Characteristic.m_isMainRoot)
			{ return true; }
			else
			{ return false; }
		}
		
		if (m_Characteristic.m_isSFin ^ VerCharacteristic.m_isSFin) 
		{
			if (m_Characteristic.m_isSFin)
			{ return true; }
			else
			{ return false; }
		}

		if ( ( (m_Characteristic.m_mainCount == 1) && (m_Characteristic.m_SFinCount == 1) ) &&
			 ( (VerCharacteristic.m_mainCount != 1) || (VerCharacteristic.m_SFinCount != 1) ) )
		{ return true; }
		
		if ( ( (VerCharacteristic.m_mainCount == 1) && (VerCharacteristic.m_SFinCount == 1) ) &&
			 ( (m_Characteristic.m_mainCount != 1) || (m_Characteristic.m_SFinCount != 1) ) )
		{ return false; }

		if ( (m_Characteristic.m_SComplCount < 2) && (VerCharacteristic.m_SComplCount >= 2) )
		{ return true; }
		
		if ( (VerCharacteristic.m_SComplCount < 2) && (m_Characteristic.m_SComplCount >= 2) ) 
		{ return false; }

		if (m_Characteristic.m_isInfBetween ^ VerCharacteristic.m_isInfBetween) 
		{
			if (m_Characteristic.m_isInfBetween)
			{ return false; }
			else
			{ return true; }
		}
		//m_Characteristic ����� (m_isMainRoot) � (m_isChain) � � VerCharacteristic ��� ���� ���� ��� �����
		if ( (m_Characteristic.m_isMainRoot && m_Characteristic.m_isChain) && 
			!(VerCharacteristic.m_isMainRoot && VerCharacteristic.m_isChain) )
		{ return true; }

		if ( (VerCharacteristic.m_isMainRoot && VerCharacteristic.m_isChain) && 
			!(m_Characteristic.m_isMainRoot && m_Characteristic.m_isChain) )
		{ return false; }

		if (m_Characteristic.m_isVerbRoot ^ VerCharacteristic.m_isVerbRoot) 
		{
			if (m_Characteristic.m_isVerbRoot)
			{ return true; }
			else
			{ return false; }
		}
		
		if (m_Characteristic.m_isAdjAfterVerb && VerCharacteristic.m_isAdjBeforeVerb)
		{ return true; }

		if (m_Characteristic.m_isAdjBeforeVerb && VerCharacteristic.m_isAdjAfterVerb)
		{ return false; }
		
		return false;
	}

	//�������� ������������
	CBlockVersion & CBlockVersion::operator=(const CBlockVersion & Version)
	{
		m_VersionElements.Clear();
		for (PVERELEMENT pElem = Version.GetFirst(); pElem; pElem = Version.GetNext())
		{ m_VersionElements.Add()->Assign(pElem); }
		return (*this);
	}

	//���������� ������������� ��������
	const SBlockVersionCharacteristics* CBlockVersion::GetVersionCharacteristics()
	{
		FillCharacteristic();
		return &(m_Characteristic);
	}

	//�������� ���� ��������� ��������
	void CBlockVersion::ClearAll()
	{
		m_VersionElements.Clear();
	}

	//�������� ���������� ��������
	bool CBlockVersion::IsValid()
	{
		return !(m_VersionElements.Empty());
	}

}
}
}