#pragma once

#include "./TStatisticsCollector.h"
#include "./IBlackBox.h"
#include "..\ASCInterface\IInterface.h"


// --------------------------------------------------------------------------------
// {00DDC188-820E-40b3-ADA8-23EB2D11AF14}
static const GUID CLSID_TextStatisticsProcessor = { 0xddc188, 0x820e, 0x40b3, { 0xad, 0xa8, 0x23, 0xeb, 0x2d, 0x11, 0xaf, 0x14 } };

// {F7A8B570-678B-4ef9-BDC9-0C4A32CBA5BB}
static const GUID IID_TextStatisticsProcessor = { 0xf7a8b570, 0x678b, 0x4ef9, { 0xbd, 0xc9, 0xc, 0x4a, 0x32, 0xcb, 0xa5, 0xbb } };
// ------------------------------------------------------------------------------------------------------------------------------

// {32c07056-611c-4b0e-b2e1-5358f8bf3385} 
static const GUID CLSID_FrequenceDictionaryStatistics = 
{ 0x32c07056, 0x611c, 0x4b0e, { 0xb2, 0xe1, 0x53, 0x58, 0xf8, 0xbf, 0x33, 0x85 } };

// {fb4d247e-4038-4296-8069-746a991ad806} 
static const GUID IID_FrequenceDictionaryStatistics = 
{ 0xfb4d247e, 0x4038, 0x4296, { 0x80, 0x69, 0x74, 0x6a, 0x99, 0x1a, 0xd8, 0x06 } };
///////////////////////////////////////////////////////////////////////////////

// {F380EEFD-2B72-4b12-8DCD-67D80956E850}
static const GUID CLSID_ContentAnalysisProcessor = 
{ 0xf380eefd, 0x2b72, 0x4b12, { 0x8d, 0xcd, 0x67, 0xd8, 0x9, 0x56, 0xe8, 0x50 } };

// {BDA14EDC-DCD7-4895-8569-BC601ED183DB}
static const GUID IID_ContentAnalysisProcessor = 
{ 0xbda14edc, 0xdcd7, 0x4895, { 0x85, 0x69, 0xbc, 0x60, 0x1e, 0xd1, 0x83, 0xdb } };


namespace SS
{
namespace Interface
{
namespace Statistics
{
	/// ��������� �������-�������
	class IContentAnalysisProcessor : public virtual SS::Interface::IBase   
	{
		public:

			/// ��������� ���������� � ������ ����� ����������
			virtual void Init(
			/// ��������� � ������������� �������
			SS::Core::Types::IndexationSearch::TNativeTextForIndexation* pNativeText) = 0;
			/// ��������� ���� ������ �� ������� ������������� ����
			virtual void AnalyseText() = 0;
			/// ����������� ���
			virtual double GetIndexYule(SS::Dictionary::Types::TDictionaryIndex  iPositiveSemClassA, SS::Dictionary::Types::TDictionaryIndex iPositiveSemClassB) = 0;
			/// ����������� �����
			virtual double GetIndexIanis(SS::Dictionary::Types::TDictionaryIndex iPositiveSemClass,  SS::Dictionary::Types::TDictionaryIndex iNegativeSemClass) = 0;
			/// ������� ���������� �������
			virtual double GetIndexPirson(SS::Dictionary::Types::TDictionaryIndex iPositiveSemClassA, SS::Dictionary::Types::TDictionaryIndex iPositiveSemClassB) = 0;
			/// ���������� ����� �������������� ����������
			virtual bool GetClassSubTreeWithMarkers(SS::Dictionary::Types::TDictionaryIndex iSemClass, SS::Statistics::Types::ISemClassSubTreeWithMarkers * pIStruct) = 0;
			/// ��������� ��������� �� ��������������� ����� � �������� �������� (����� ������ <GetClassSubTreeWithMarkers()>)
			virtual const std::wstring * GetTextWithMarkers(void) = 0;

	};

	class IFrequenceDictionaryStatistics : public virtual SS::Interface::IBase   
	{
	public:
		/// ������ ����� ������������� ��� ��������� ������ �������
		virtual void StartStatisticsCollection() = 0;
		/// ��������� ����� ������������� ��� ��������� ������ �������
		virtual void StopStatisticsCollection() = 0;
		/// ���������� ������� ��������� ������� 
		/// ��������� � ������������� �������
		virtual void Init(SS::Core::Types::IndexationSearch::TNativeTextForIndexation* pNativeText) = 0;
		/// ���������� ������� ��������� ������� 
		/// p_l_Paths - ������ ����� ��� ���������, ����� ����� ����� ���� ��� 
		/// ���� � ���������, ��� � ���� � ������
		virtual void Init(std::list<std::wstring>* p_l_Paths) = 0;
		/// ��������� ������� ��������� �������
		virtual void Analyse() = 0;
		/// ���������� ����� �������������� ����������
		virtual void SetStatistics(/*in*/SS::Statistics::Types::IWordFrequencyParameters* pWordFrequencyParameters) = 0;
		/// ���������� ����� �������������� ����������
		virtual void GetStatistics(/*out*/SS::Statistics::Types::IWordFrequencyParameters* pWordFrequencyParameters) = 0;
	};

	/// �������� ����� �������, ��������� �� ��������������� ���������� ��� ������� ������
	class ITextStatisticsProcessor : public virtual SS::Interface::IBase   
	{
	public:
		/// ���������� ������� ��������� ���������� ������
		virtual void Init(
			/// ��������� � ������������� �������
			SS::Core::Types::IndexationSearch::TNativeTextForIndexation* pNativeText) = 0;
		/// ��������� ������ ������
		virtual void AnalyseText() = 0;
		/// ���������� ����� �������������� ����������
		virtual void GetTextStatistics(/*in out*/SS::Statistics::Types::IStatisticsParameters* pStatisticsParameters) = 0;
		/// ����� ���������� ��������                    
		virtual void GetSymbolsSequenceStatistics(
			/*in*/SS::Statistics::Types::TNativeSymbols* pNativeSymbols, 
			/*out*/SS::Statistics::Types::TResultType* pResultType) = 0;
	};
}
}
}