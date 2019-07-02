#pragma once

#include <string>

class CMacroDefinitionGenerator
{
public:
	CMacroDefinitionGenerator(void);
	~CMacroDefinitionGenerator(void);
	///������� ���� � ��������� ��� �������� �������-������� �������� �������������
	const char* MakeTemplates();
private:
	///����� ������ ������ � �����-����������
	std::string m_sMacroDefinition;

	///������� ���� ������ �� ���������� ���-�� ��������
	std::string MakeMacroDefinition(unsigned int nValueCount);
	///������� ������-��������� ������� �� ���������� ���-�� ��������
	std::string MakeMacroDefinitionHeader(unsigned int nValueCount);
	///������� ������-��������� ������ ������� �� ���������� ���-�� ��������
	std::string MakeMacroDefinitionClassCTOR(unsigned int nValueCount);

	///������� ������ ������� ������ ������� �� ���������� ���-�� ��������
	std::string MakeMacroDefinitionClassFunctions(unsigned int nValueCount);

	///����������� ���������� �������� � ���-�������� (���� 0�00000001)
	std::string IntToMapHex(unsigned int i);
};
