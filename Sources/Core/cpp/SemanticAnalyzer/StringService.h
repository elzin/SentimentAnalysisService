#pragma once

namespace SS
{
	namespace Semantic
	{
		///������ ��� �����, ��������������� 0-� ��������
		class CStringService
		{
		public:
			CStringService(void);
			~CStringService(void);

			bool StrEqual(const TCHAR* sz1, const TCHAR* sz2);

			void LowerFirstChar(TCHAR* szWord);
			void UpperFirstChar(TCHAR* szWord);

			void LowerSz(TCHAR* szWord);
			void UpperSz(TCHAR* szWord);

		};
	}
}