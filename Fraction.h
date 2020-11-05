#pragma once
#include <iostream>

using namespace std;

class Fraction
{
public:
	Fraction();
	~Fraction();

	typedef struct drob
	{
		int Natur;
		int chisl;
		int znamenatel;
	};


	drob drobA, drobB;
	drob *drA, *drB;

	void ShowDrob(drob a);
	void AddDrob(float a,float b);
	bool CheckDrobObZnamenatel(drob drobA, drob drobB);
	void InputDrob();
	void SummaDrobsPositive();
	void GetDrobA();
	void  GetDrobB();
	bool CheckNormalFraction(drob a);
	void MultyFract();
	void DivsFract();
	void ConvertNoneNormalFractionInSmFractal();
	
	/* -- ��������� � ������� -- */
	bool CheckSokrDrob(drob a);
	void CreateObZnamenatel(drob drobA, drob drobB);
	void Raznost();
	
	void SokrDrob(drob a);
	
	/* -- ��������� � ������� -- */

private:

	drob tmpA,tmpB,tmp;
	drob summa;
	drob raznost;
	drob multy;
	drob divs;
	drob w, t, q;

	// ���������� ����� ��������
	int NOD(int a, int b);
	int NOK(int a, int b);
	int NOKDrobs(drob drobA, drob drobB);
	bool CheckNormalDrob(drob dr);
	//�� ������� �� �����? ��������� = 0 ��� ������ ������ ����������� = 0
	bool CheckDrobONZero(drob dr);

	
	
	
	
	

	
};

