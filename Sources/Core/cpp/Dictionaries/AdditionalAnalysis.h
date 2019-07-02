#pragma once

namespace SS{ 
namespace Dictionary{

//����� ���� ��� �������
namespace HyphenAnalisisPrivate
{
   //��� �����
   enum EWordClassification
   {
      WCUndefined,
      WCToLiboNibud,
      WCKoeKoy,
      WCPo,
      WCVVo,
      WCDeKaKoKosS
   };
   
   typedef std::list<SS::Dictionary::Types::TWordInfo> TWIList;

   //������������� ������ ����
   typedef AssocVector<std::wstring, EWordClassification> TWordClassificationStorage;

   //������ ���������������
   typedef Detail::TFeatureList TFeatureList;
   typedef std::vector<TFeatureList> TFeatureListForWord;

   //��������� ��� ���� ������ ������� ��������� ����
   struct IRusRuleCheck
   {
      virtual ~IRusRuleCheck() {}
      
      ///////////////////////////////////////////////////////////////////////////////
      // ������������� ����� ���������� �����
      // LeftWord, RightWord - ����� ������� ����� � ������ �� ������
      // LeftMorpho, RightMorpho - ��������������� ������ � ������� �����
      // MorphoFeature - �������������� ��������������� ���������� �����
      // WCS - ������������� ������ ����
      virtual bool Check( 
         const std::wstring &LeftWord, const std::wstring &RightWord, 
         const TFeatureList &LeftMorpho, const TFeatureList &RightMorpho, 
         const TWordClassificationStorage &WCS,  
         CMorphoFeature &MorphoFeature
      ) const = 0;
   };

   //���������� �� ��������� �����
   struct TWordPartInfo
   {
      std::wstring WordLower;   //������ �������
      std::wstring WordOrigin;  //������������ �������
      TWIList MorphoInfo;       //��������������� ���������� �����
   };

   typedef std::vector<TWordPartInfo> TWordPartInfoList;

   //��������� ��� ���� ������ ������� ��������� ����
   struct IEngRuleCheck
   {
      virtual ~IEngRuleCheck() {}

      ///////////////////////////////////////////////////////////////////////////////
      // ������������� ����� ���������� �����
      // TFeatureListForWord - ������ ��������������� � ������ ����� �����, �.�. �������� ����� ���������� ��������
      // MorphoFeature - �������� ���������������
      virtual bool Check( 
         const TFeatureListForWord &FeatureListForWord,  
         TFeatureList &FeatureList
         ) const = 0;
   };


   //������� ������ FeatureList �� WIList 
   void FillFeatureList( const TWIList &WIList, HyphenAnalisisPrivate::TFeatureList &FeatureList, IAMConverterMorpho *pAMConverter );

   inline EWordClassification GetType(const TWordClassificationStorage &WCS, const std::wstring &Str )
   {
      TWordClassificationStorage::const_iterator I = WCS.find( Str );

      return I != WCS.end() ? I->second : WCUndefined;
   }

} //namespace HyphenAnalisisPrivate

///////////////////////////////////////////////////////////////////////////////
// ����� �������� �������������� ������ ��������� ���� �� �������
///////////////////////////////////////////////////////////////////////////////
class TCompoundWordAnalysis: public NonCopyable
{ 
public:
   typedef HyphenAnalisisPrivate::TWordPartInfoList TWordPartInfoList;
   typedef HyphenAnalisisPrivate::TFeatureList TFeatureList;
   

private:
   typedef std::list<SS::Dictionary::Types::TWordInfo> TWIList;
   typedef std::vector<HyphenAnalisisPrivate::IRusRuleCheck *> TRussianRules;
   typedef std::vector<std::pair<HyphenAnalisisPrivate::IEngRuleCheck *, const char *> > TEnglishRules; //������ ���������� ������ � ���������


private:
   HyphenAnalisisPrivate::TWordClassificationStorage m_WordClassification;
   TRussianRules m_RussianRules;
   TEnglishRules m_EnglishRules;

public:
   TCompoundWordAnalysis();
   ~TCompoundWordAnalysis();

   ///////////////////////////////////////////////////////////////////////////////
   // ������������� ����� �� ������� ����� ���������� �����
   // LeftWord, RightWord - ����� ������� ����� � ������ �� ������
   // LeftMorpho, RightMorpho - ��������������� ������ � ������� �����
   // MorphoFeature - �������������� ��������������� ���������� �����
   // 
   // ����� - ������� �� ���������� ��������������� ��������������� �����
   // ������� ��. � ������������
   ///////////////////////////////////////////////////////////////////////////////
   bool HyphenAnalisisRussian(
      const std::wstring &LeftWord, const std::wstring &RightWord, 
      const TWIList &LeftMorpho, const TWIList &RightMorpho, 
      IAMConverterMorpho *pAMConverter,
      CMorphoFeature &MorphoFeature
   ) const;

   ///////////////////////////////////////////////////////////////////////////////
   // ������������� ����� �� ���������� ����� ���������� �����
   // wcWord - ����� ���������� ������
   // PartInfoList - ��������������� � ������ ����� �����
   // FeatureList  - �������������� ��������������� ���������� �����
   // 
   // ����� - ������� �� ���������� ��������������� ��������������� �����
   // ������� ��. � ������������
   ///////////////////////////////////////////////////////////////////////////////
   bool HyphenAnalisisEnglish(
      const wchar_t* wcWord,
      const TWordPartInfoList &PartInfoList, 
      IAMConverterMorpho *pAMConverter,
      TFeatureList &FeatureList
   ) const;


};

} //namespace Dictionary
} //namespace SS
