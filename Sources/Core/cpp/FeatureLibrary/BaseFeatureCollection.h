#pragma once

#include "BaseFeature.h"
#include <list>
#include <vector>
namespace SS
{
	namespace Core
	{
		namespace Features
		{
			namespace Base
			{

				///��� ������ (��� �������� ������������ ���������� ��������)
				enum TFeatureCollectionType
				{
					///�����������(�������)
					fctUnknown,
					///CMorphoFeature
					fctMorphoFeature,
					///CMorphoFeatureApriori
					fctMorphoFeatureApriori,
					///CMorphoFeatureAposteriori
					fctMorphoFeatureAposteriori,
					///CSemanticFeature
					fctSemanticFeature,
					///CSyntaxFeatureApriori
					fctSyntaxFeatureApriori,
					///CSyntaxFeatureAposteriori
					fctSyntaxFeatureAposteriori,
					///CObjectFeature
					fctConstructionFeature,
					///CSentenceFeature
					fctSentenceFeature,
				///CSemanticFeatureApriori
				fctSemanticFeatureApriori,
				///CSemanticFeatureAposteriori
				fctSemanticFeatureAposteriori,

				};

				/// ������� ����� ��� ���� ������� �������������. �������� ����� ���������(��������������) ���������� ������� �������� ��� �������
				class CBaseFeatureCollection
				{
				public:
					CBaseFeatureCollection(void);
					virtual ~CBaseFeatureCollection(void);

					///��������� ���������� �������� �������� ���-��
					virtual void GetXMLValue(std::string& sXML) const;
					///������������ �������� ���-�� �� ���������� ��������
					virtual void SetXMLValue(const std::string& sXML);

					///��������� ���������� �������� �������� ���-�
					virtual void ToString(std::string& s) const;
					///��������� ���������� �������� �������� ���-�
					std::string CBaseFeatureCollection::ToString() const;

					/// ��������� �������� ����� ����������
					virtual	void Undefine();
					///������ ��� ���� ��� ���-�� Undefined
					virtual bool IsUndefined() const;

					/// ���������� ������ �����, ��� ����������� ������ �� ���� � ���������� �������������� ����������
					virtual	void GetValue(std::vector<unsigned char>& vecOfByte);
					///�������� �����
					void GetValueTest(std::vector<unsigned char> & vecOfByte);
					///���������� ������ ����� ������� � ���������� �������, ����������� ������������ ���������� � ������, ������� ������� ������� �� ����� ���, ���������� �������
					virtual	void SetValue(std::vector<unsigned char>& vecOfByte, unsigned int& uiCurPosition);

					/// "�������� = " - ����������� �������� ������� ������ ������-�� ����
					virtual void Assign(const CBaseFeatureCollection* pValue);

					/// "�������� == " - ���������� �� ��������� ������� ������ ������-�� ����
					virtual bool Equal(const CBaseFeatureCollection* pValue)  const;
					/// "�������� &= " - ����������� �������� ������� ������ ������-�� ����
					virtual void AssignAND(const CBaseFeatureCollection* pValue);
					/// "�������� |= " - ����������� �������� ������� ������ ������-�� ����
					virtual void AssignOR(const CBaseFeatureCollection* pValue);

					/// �������������� ��������� �������� (�������� �� ������ ��������� ���������� ���������)
					virtual bool IsIncludes(const CBaseFeatureCollection* pValue) const;

					/// �������������� ����������� �������� (������������ �� ������ ��������� � ���������� ����������)
					virtual bool IsIntersectsWith(const CBaseFeatureCollection* pValue) const;

					/// ����������� ��������
					virtual bool IsIntersectsOrEmpty(const CBaseFeatureCollection* pValue) const;

					///������ ��������� ��� ��������������
					virtual const char* GetFeatureName() const = 0;
					///������ ��������� �������� ��������������
					virtual const char* GetFeatureDescription() const = 0;

					///������ ���-�� �������������, �������� � ���������
					unsigned int GetFeatureCount() const;
					///������ �������������� �� ��������� �� ����������� ������
					const CBaseFeature* GetFeature(unsigned int nFeature) const;
				CBaseFeature* GetFeature(unsigned int nFeature);

				//�������� �������� ������. �������� ������ (� ��������� ������ ����������)
				std::string GetPrintableDataDescription() const;


				protected:
					///������ ���������� �� ��� ��������������, �������� � �����
					CBaseFeature** m_ppFeatures;
					CBaseFeature*** m_pppFeatures;
					///���������� ������������� � ������
					unsigned int m_FeatureCount;
					///
					int m_unusedFreeSpace;
					///��� ������ (��� �������� ������������ ���������� ��������)
					TFeatureCollectionType m_FeatureCollectionType;

					///��������� ��������� �� �������������� � ������ �������������
					/**
						���������� � ������������� �������-����������� ��� ���� ������������� - ������ ���� �������
						��� ������������� ��� ������ ������� ���������� ��� ��������� �������� ������ ������������� ������� �����������
					*/
					void AddFeatureToCollection(CBaseFeature* pFeature);

					///������ ��������� ������ ���, ������� ��������� �������� ������ ��������������
					void GetFeatureXMLRegion(const std::string& sXML, std::string& s) const;

					///������ ������ - ��������� ��������������
					void AppendFeatureHeader(std::string& s) const;
					///������ ������ - ����������� ��������������
					void AppendFeatureEnd(std::string& s) const;
					///������ ������ - ���� ��������������
					void AppendFeatureValues(std::string& s) const;
				};
			
			}
		}
	}
}