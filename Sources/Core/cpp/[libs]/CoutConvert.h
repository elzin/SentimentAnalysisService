#ifndef CoutConvert_H
#define CoutConvert_H

#include <string>
#include <memory>

//�������� ���� ���������� ������ �� ���� �������������, �� ����� �������� ��� � stdafx.h, �.�.
//� ���� ������ �� �������� ��������� ������ cout �� ��� �������, � ��������� ������ ostream, 
//����� �������� ���������� (�������������), � ����� � �������������� ���������
   
/**
	����� ������������� ���������� << ��� ����������� ������ ������� ����� �� �������. �������������� ��� ������� ��� � 
	UNICODE ������. ����� ������� ������ �������������� � ����������� OEM ������ � ������������ �� �������.
	������ ����������� ���������� ���� ���������� ����������� ��������� �������: ������� ������� ����� ������� ��������� ���
	���������� ���������� ��� ���������, � ��� ��������� << ������� � ���������� ���������� ��� ��������� �������.
	������: ��� ������� ��������� ���������� ��� ������ � �������:
	
	int main(int argc, _TCHAR* argv[])
	{   
		wchar_t *WStr = L"��� ���� WStr";
		char *Str= "��� ���� Str";
		const wchar_t *ConstWStr = L"��� ���� ConstWStr";
		const char *ConstStr= "��� ���� ConstStr";
		wchar_t rgWStr[] = L"��� ���� rgWStr";
		char rgStr[]= "��� ���� rgStr";
		const wchar_t rgConstWStr[] = L"��� ���� rgConstWStr";
		const char rgConstStr[]= "��� ���� rgConstStr";

		std::string	 CString("��� ���� std::string");
		std::wstring WString(L"��� ���� std::wstring");

		cout << WStr << endl;
		cout << Str << endl;
		cout << ConstWStr << endl;
		cout << ConstStr << endl;
		cout << rgWStr << endl;
		cout << rgStr << endl;
		cout << rgConstWStr << endl;
		cout << rgConstStr << endl;
		cout << "��� ���� ������� ������ ������������ ������" << endl;
		cout << L"��� ���� ������� ������ ������������ ������" << endl;
		cout << CString << endl;
		cout << WString<< endl;;

		return 0;
	}


   ������� ��������������� � OEM ������ ���� ��� &stream == &cout
*/
namespace std
{
std::ostream &operator<< ( std::ostream &stream, const char * const obj );
std::ostream &operator<< ( std::ostream &stream, const std::string &obj );
std::ostream &operator<< ( std::ostream &stream, const wchar_t * const obj );
std::ostream &operator<< ( std::ostream &stream, const std::wstring &obj );

//� ��� � �� ����� ������ ���������� ����� 'operator <<' is ambiguous ��� ������ �������� std::list<T>::size()
//std::ostream &operator<<( std::ostream &stream, allocator<int>::size_type obj );
} //namespace std

#endif