#pragma once

namespace SS
{
namespace Interface
{
namespace Core
{
namespace Common
{

	/// ���������� �������� �������� � �����������
	class IEnumerator
	{
	public:
		///���������� true, ���� ��������� ������
		virtual unsigned int Empty() = 0;

		///���������� ����� ��������� ���������
		virtual unsigned int Count() = 0;

		///������� ���������
		virtual void Clear() = 0;

		///������������� ��������� �� ������ ��������� 
		virtual unsigned int Reset() = 0;

		///������������� ��������� �� ��������� ������� ���������
		virtual unsigned int MoveNext() = 0;
	};
}
}
}
}
