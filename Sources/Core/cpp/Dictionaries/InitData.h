#pragma once


namespace SS{ 
namespace Dictionary{
namespace InitData{

/**
   ������ ����������� ��� ������������� �������� � ������ �������� � �������
*/
   //HMODULE - ���� DLL
   extern HMODULE g_hModuleCurrentDLL;

   //�����
   namespace Languages
   {
      enum eLanguages
      {
         English,
         Russian,
         
         COUNT,
         Undefined = COUNT
      };
   }

   //��������� �� ����� �������
   namespace LangDepDict
   {
      enum eLangDepDict
      {
         Smart,
         Abbreviations,

         COUNT
      };
   };

   //�������������� ���������������� �������� �������� � �������������
   namespace ObjectID
   {
      enum eObjectID
      {
         //�������� �� �����
         EngSmart,
         EngAbbreviations,
         RusSmart,
         RusAbbreviations,

         //����������� �� �����
		 OrderingRussian,
         ArabicNumbers,
         RomanNumbers,
         NumericOrdering,
         Symbols,

         DICTS_COUNT,
         FIRST_CHARACTERISTIC = DICTS_COUNT,

         //������ �������������� �����
         ContainHypen = FIRST_CHARACTERISTIC,           //�� �������� �����
         ContainQuotationS,                             //�� �������� �������� � s
         ContainQuotationNT,                            //�� �������� �������� � NT

         FULL_CHARACTERISTIC_COUNT
      };

   }

   //����������� ��������������� ���������������� ��������, �������������� �������� �� ����� ��������� �������
   extern const WORD DictionaryToResId[ObjectID::DICTS_COUNT];

   //��� ������ �������� �� ����� ��������� ������� 
   extern const wchar_t DictionaryResClass[];
   
   //��� ������ �������� � ������� ��� TConstData
   extern const wchar_t ConstDataResClass[];

   //������������ ���� � ��������� �� ����� ������� � ������������� �������
   inline ObjectID::eObjectID Convert( Languages::eLanguages Language, LangDepDict::eLangDepDict LangDepDict )
   {
      APL_ASSERT( Language >= 0 && LangDepDict >= 0 && Language < Languages::COUNT && LangDepDict < LangDepDict::COUNT );

      return static_cast<ObjectID::eObjectID>(Language * Languages::COUNT + LangDepDict);
   }

   //������ ����������� �� ����� �������
   //�������� ����������� �� ����� �������� [ FirstUndepDict(), ObjectID::DICTS_COUNT )
   //�������� ��������� [ 0, FirstUndepDict() )

   inline size_t FirstUndepDict()
   {
      return LangDepDict::COUNT * Languages::COUNT;
   }

   
  
} //namespace InitData
} //namespace Dictionary
} //namespace SS


