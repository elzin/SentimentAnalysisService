#pragma once

#include "BaseExpert.h"
#include "BoardElement.h"
#include "../ASSInterface/IAMConverter.h"
#include <list>
#include <string>

namespace SS
{
	namespace Syntax
	{
		namespace ExpertModel
		{
			using namespace SS::Core::Features;
			
			///������� ��������� ���������� ����� �����������, ����������� � ������ ������.
			class CGenericExpertUniformBinderEng : public CBaseExpert
			{
			protected:
				///����� � ����� ����������, ����������� ���������� ����� �����������
				std::list<std::wstring> m_conjunctions;
				///��� ����������� �������� ���� � ������������ ��������������
				CSyntaxFeatureAposteriori m_oSyntaxFeatureAposteriori;
			
			public:
				///�����������
				CGenericExpertUniformBinderEng();
				///������ �� �����
				virtual bool PassBoard(BoardElements::CBoard & rBoard, BoardElements::PBLOCK pBlock);
				///��������� �������� ��������
				virtual std::wstring GetName() const
				{
					return L"Uniform members binder";
				}
			};
			
			///������� ��������� ���������� ����� �����������, ����������� � ������ ������.
			class CGenericExpertUniformBinderFinalEng : public CGenericExpertUniformBinderEng
			{
			private:
				///���������� true ���� ������ ���������� ��������� ������ �� Noun �������� (�������, �������) �����
				bool AnalisNounOnly(BoardElements::PBLOCK pBlockPrev, BoardElements::BoardElementsIterator itElemSecond) const;
			
			public:
				///������ �� �����
				virtual bool PassBoard(BoardElements::CBoard & rBoard, BoardElements::PBLOCK pBlock);
			};
		}
	}
}