#pragma once

#include ".\basefeaturecollection.h"
#include "define.h"
namespace SS
{
	namespace Core
	{
		namespace Features
		{
			/// ������ ���������� � ������������������ ���� � �����������
			class CObjectFeature:
				public SS::Core::Features::Base::CBaseFeatureCollection
			{
			public:
				CObjectFeature(void);
				~CObjectFeature(void);
				CObjectFeature& operator = (const CObjectFeature& value)
				{
					Assign(&value);
					return *this;
				}
				CObjectFeature(const CObjectFeature& value){
					Init();
					*this = value;
				};

 				///������ ��������� ��� ��������������
				const char* GetFeatureName() const {return "ConstructionFeature";};
				///������ ��������� �������� ��������������
				const char* GetFeatureDescription() const {return "������ ���������� � ������������������ ���� � �����������";};

				/// ������� �������� �����������
				Types::ObjectsOrder				m_ObjectsOrder;			// ������ ��� ���
				/// ��������� �� ��������� � ������
				Types::PositionToDetectedObject	m_PositionToDetectedObject;	// ����� ��� ������
				/// �������������� �����
				Types::ObjectObligation			m_ObjectObligation;		// ������������ ��� ��������������
				/// ����� �������� ������ ����
				Types::SameTypeObjectsNumber	m_SameTypeObjectsNumber;
				/// ������� ��������
				Types::ScopeOfTheRule			m_ScopeOfTheRule;		// �� ����� ����������� ��� �� ����� �����
				/// ��������� ������� � �����
				Types::PositionInBlock			m_PositionInBlock;		// ��������� � �����
				/// ����� ������������
				Types::AgreementType			m_AgreementType;		// �� ����, �����, ������ ��� �����, ����				
				/// ������� ������ ��������� ���������
				Types::ChildrenAnalysisDepth	m_ChildrenAnalysisDepth;
				/// ����� ������������ �������������� �������������
				Types::SyntaxParamsInheritanceMode m_SyntaxParamsInheritanceMode;
				/// ����� �����������
				Types::SentenceNumber m_SentenceNumber;
				/// ���������� ����� ����� � �����������
				Types::BlockPosition m_BlockPosition;
				/// ���������� ������ ��� ��������� �� ������-�����
				Types::BlockSearchScope m_BlockSearchScope;
				/// ������� ����� ����
				Types::CreateUnit m_CreateUnit;
				/// ��� ����������� �����
				Types::MoveType m_MoveType;

			private:
				void Init();
			};
		}
	}
}