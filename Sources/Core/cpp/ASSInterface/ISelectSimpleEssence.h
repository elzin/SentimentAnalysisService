#pragma once 

#include <string>

#include "..\ASCinterface\iinterface.h"

// {8C7B7DFB-423E-4b4e-8095-04E0D17FC917}
static const GUID CLSID_SelectSimpleEssence = 
{ 0x8c7b7dfb, 0x423e, 0x4b4e, { 0x80, 0x95, 0x4, 0xe0, 0xd1, 0x7f, 0xc9, 0x17 } };

// {9B32665F-4051-4a3c-8815-0CBC8265B109}
static const GUID IID_SelectSimpleEssence = 
{ 0x9b32665f, 0x4051, 0x4a3c, { 0x88, 0x15, 0xc, 0xbc, 0x82, 0x65, 0xb1, 0x9 } };

namespace SS
{
	namespace Interface
	{
		namespace Core
		{
            namespace SimpleEntities
            {
                using std::wstring;

                /// ������ (������ �� ���������, �.�. � ���� �����������)
                enum ECurrencyTypes
                {
                    /// ����
                    eCurrencyEuro = 0,
                    /// �����
                    eCurrencyRouble
                };

                ///��������� ��� ��������� � ������������ ������� ���������
			    class ISelectSimpleEssence : virtual public SS::Interface::IBase
                {
                    public:
                        /// �������������
			            /// essencePath - ���� � xml-����� �������� ���������
			            /// dictionariesPath - ���� � �������� ����������� �������
			            virtual void InitFromFile(const wstring &essencePath, const wstring &dictionariesPath) = 0;
			            /// xmlText - ����� XML
			            /// dictionariesPath - ���� � �������� ����������� �������
			            virtual void InitFromXMLString(const wstring &xmlText, const wstring &dictionariesPath) = 0;

                        /// ��������� �����
                        /// text - �����, � �������� ����� ��������� ���������� ���������
                        /// applyNormalization - ���� ������������� ���������� ������������
                        /// retval wstring - ����������� �����
                        virtual wstring DetectingText(const wstring &text, bool applyNormalization) = 0;

                        /// ������������ ������
                        /// str - �������� ������ ��� ������������
                        /// typeValue - ���� ����� ������� ��� ��������
                        /// retval wstring - ��������������� ������
                        virtual wstring NormalizeString(const wstring &str, wstring &typeValue) = 0;

                        /// ��������� ����� ������/������
                        /// cur - ������
                        /// course - ����
                        virtual void SetCurrencyCourse(ECurrencyTypes cur, double course) = 0;

                        /// �������� �� ������� � �������� ������ ��������� ���� ��������
                        /// str - ������, � ������� ���������� �������� �������
                        /// type - ��� �������� ��� ������
                        /// retval bool: true - �������� ������������
                        ///              false - ���
                        virtual bool IsContainEntity(const wstring &str, const wstring &type) = 0;
                };
            }
        }
    }
}