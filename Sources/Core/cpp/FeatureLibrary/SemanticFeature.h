#pragma once
#pragma warning( disable : 4290 )
#include <stdexcept> 
#include ".\basefeaturecollection.h"
#include "define.h"
namespace SS
{
namespace Core
{
namespace Features
{
/// ������������� ��������������
class CSemanticFeature :
	public SS::Core::Features::Base::CBaseFeatureCollection
{
public:
	CSemanticFeature(void);
	~CSemanticFeature(void);
	CSemanticFeature& operator = (const CSemanticFeature& value)
	{
		Assign(&value);
		return *this;
	}

	CSemanticFeature(const CSemanticFeature& value){
		Init();
		*this = value;
	};

	///������ ��������� ��� ��������������
	const char* GetFeatureName() const {return "SemanticFeature";};
	///������ ��������� �������� ��������������
	const char* GetFeatureDescription() const {return "������������� ��������������";};
	//
	void AssignSemanticFeature( CSemanticFeature const* pValue)throw( std::invalid_argument );
//���� �������������

///////////////////////////////////////////////////////////////////////////////
// ��������!!! ��� ��������� ������������� ������������� ���������� �������� 
// ���������� ������� GetNextLevelFeatureNumber
///////////////////////////////////////////////////////////////////////////////

	//1-� ������� ������������� ��������
	Types::TSemanticType			m_SemanticType;

	//2-� ������� ������������� ��������
	Types::TSTimeIntervalType		m_STimeIntervalType;
	Types::TSPlaceType				m_SPlaceType;
	Types::TSMeasureType			m_SMeasureType;
	Types::TSPersonType				m_SPersonType;
	Types::TSOrganizationType		m_SOrganizationType;			
	Types::TSVerbType				m_SVerbType;
	Types::TSServiceTypes			m_SServiceTypes;
	Types::TSInfo					m_SInfoTypes;
	Types::TSMaterial				m_SMaterial;
	Types::TSTransport				m_STransport;
	Types::TSBuilding				m_SBuilding;

	//3-� ������� ������������� ��������
	// ���������� ������������� ����
	Types::TSVBeType				m_SVBeType;
	Types::TSVAcquirePossessType	m_SVAcquirePossessType;
	Types::TSVEndType				m_SVEndType;

	Types::TSMFood					m_SMFood;
	Types::TSMForFreeTime			m_SMForFreeTime;
	
	//4-� ������� ������������� ��������				
	Types::TSVAcquireType			m_SVAcquireType;
	
	//5-� ������� ������������� ��������	
	Types::TCity					m_SPCity;
	Types::TArea					m_SPCArea;
	Types::TDistrict				m_SPCADistrict;
	Types::TMetro					m_SPCADMetro;

	//6-� ������� ������������� ��������
	Types::TGeneric					m_SGeneric;

	//�������, ����������� ��� ������� ������
	bool CSemanticFeature::IsInclude(const CSemanticFeature& value) const;
	bool CSemanticFeature::IsIncludeEx(const CSemanticFeature& value) const;
	///����������� ��������
	bool IsIntersectsOrEmpty(const CSemanticFeature & pValue) const;
	///����������� �������� � ������ ������� TCity TArea TDistrict TMetro
	bool IsIntersectsOrEmptyDeep(const CSemanticFeature & pValue) const;
	///����������� ������� �����
	bool IsIntersectsWith(const CSemanticFeature & oValue) const;

/// ������� ��������� ����������� �������� ������� ������������� �������������
/// ������������� �������������� ��������� �� ��������� �������, ������ ��������� �������� 
/// ������������� ������ ������ ������� ��������� �� ��������� ������������� ���������� ������.
/// ������� �������� �� ����� ������� �������������� CurFeatureNumber (CBaseFeatureCollection::GetFeature)
/// � �� � �������� CurFeatureValue (CMapFeature::GetSingleValue) ���������� ����� �������������� ����������
/// ������ ��� 0 ���� ������� ������� �������� ���������.
static unsigned int GetNextLevelFeatureNumber( unsigned int CurFeatureNumber, unsigned int CurFeatureValue );
	///������� �����
	using CBaseFeatureCollection::IsIntersectsOrEmpty;
	using CBaseFeatureCollection::IsIntersectsWith;

private:
	void Init();
};
}
}
}