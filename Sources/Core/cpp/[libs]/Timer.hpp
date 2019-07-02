/******************************************************************
���������� �������� ������ TIMER
	start - ������
   stop  - ����
   reset - ��������������������
   InSec - �������� �������� � ��������
   InTCK - � "�����"
   <<    - ����� ��-�
******************************************************************/
#ifndef TIMER_H
#define TIMER_H

#include <ostream>
#include <ctime>

namespace SS { namespace Lib {

class TTimer
{
	std::clock_t begin, end;

 public:
   TTimer(){begin = std::clock(); end = 0;}

   //��������� ���������� ������
   void Start(){ begin = std::clock(); }
   void Stop(){ end = std::clock(); }

   //���������� ������
   void Resume(){ begin = std::clock() - (end - begin); }

   //�������� ������ (����� ����� ����� ������������ Resume, ������ Start)
   void Reset(){ begin = end = 0; }

   operator std::clock_t() const{ return end - begin; }

   //������� � ��������
   double InSec() const{ return (double)(end - begin) / CLK_TCK; }

   //������� � �������� �������
   double InTCK() const{ return (double)(end - begin); }

   //����������� �������� ������� ������� ����� ���������� ������
   double MinInterv() const{ return (double) 1.0 / CLK_TCK; }
};


inline std::ostream &operator<<( std::ostream &stream, const TTimer &Ob )
{
	stream <<  Ob.InSec();
   return stream;
}

}} //namespace SS::Lib 
#endif

