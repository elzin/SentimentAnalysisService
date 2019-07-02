#pragma once
#include "GraphematicCharacteristicProcessor.h"

namespace NER
{
	using System::Collections::Generic::List;

	ref class Word
	{
		private:
			/// ���������� ��������������� �������������
			static NER::GraphematicCharacteristicProcessor^ _processor = gcnew NER::GraphematicCharacteristicProcessor();

			/// ��������������� ��������������
			List<System::String^>^ _graphematicCharacteristics;
		
		public:
			/// �����������
			/// value - �����
			Word(System::String^ value)
			{
				_graphematicCharacteristics = gcnew List<System::String^>();
				_graphematicCharacteristics->Add(value);
				for each (System::String^ characteristic in _processor->Run(value))
					_graphematicCharacteristics->Add(characteristic);
			}

			/// ��������� ��������� ��������������� �������������
			List<System::String^>^ GetGraphematicCharacteristics() { return _graphematicCharacteristics; }
	};

	ref class Sentence
	{
		private:
			/// ������ ����
			List<Word^>^ _words;

		public:
			/// �����������
			Sentence()
			{
				_words = gcnew List<Word^>();
			}

			/// ���������� �����
			void AddWord(Word^ word)
			{
				_words->Add(word);
			}

			/// ��������� ������ ����
			List<Word^>^ GetWords() { return _words; }
	};
}