#include "Fraction.h"


void Fraction::Raznost()
{
	
	raznost.znamenatel = drobA.znamenatel;
	raznost.chisl = drobA.chisl - drobB.chisl;
	
	ShowDrob(drobA);
	std::cout << " - ";
	ShowDrob(drobB);
	std::cout << " = ";
	drobA = raznost;
	ShowDrob(raznost);

}
Fraction::Fraction()
{
}
Fraction::~Fraction()
{
}
void Fraction::InputDrob()
{
	std::cin >> drobA.chisl >> drobA.znamenatel >> drobB.chisl >> drobB.znamenatel;
	if (!CheckDrobONZero(drobA) && !CheckDrobONZero(drobB))
	{
		std::cout << "Дробь нулевая,вычисления не имеют смысла" << endl;
		exit;
		if (!CheckDrobONZero(drobA) || !CheckDrobONZero(drobB))
		{
			std::cout << "Дробь нулевая,вычисления не имеют смысла" << endl;
			exit;
		}

		
	}
	// превращение числа N в дробь N/1

	if (drobA.chisl != 0  && drobA.znamenatel == NULL )
	{
		drobA.znamenatel = 1;
	}
}
void Fraction::ShowDrob(drob a)
{
	if (a.znamenatel == 1) { std::cout << a.chisl << endl; }
	else
	std::cout << a.chisl << "/"  << a.znamenatel;
	//std::cout << " " << endl;
}
void Fraction::AddDrob(float a,float b)
{
	drobA.chisl = a;
	drobA.znamenatel = b;
}
int  Fraction::NOD(int a, int b)
{
		int c;

		while (b)
		{

			c = a % b;

			a = b;

			b = c;

		}

		return a;
	
}
bool Fraction::CheckNormalDrob(drob dr)
{
	if (dr.chisl < dr.znamenatel) return true;
	if (dr.chisl > dr.znamenatel) return false;
	if (dr.chisl == dr.znamenatel) return false;

}
bool Fraction::CheckDrobONZero(drob dr)
{
	if (dr.chisl == 0) return false;
	if (dr.znamenatel == 0) return false;
}
int  Fraction::NOK(int a, int b)
{
   return std::abs((a*b) / NOD(a, b));
}
int  Fraction::NOKDrobs(drob drobA, drob drobB)
{
	int a = 0, b = 0;
	a = drobA.znamenatel;
	b = drobB.znamenatel;
	return NOK(a, b);
}
bool Fraction::CheckDrobObZnamenatel(drob drobA, drob drobB)
{
	if (drobA.znamenatel == drobB.znamenatel) return true;
	else return false;
}
void Fraction::SummaDrobsPositive()
{
	summa.chisl = drobA.chisl + drobB.chisl;
	summa.znamenatel = drobA.znamenatel;

	//

	/* display equation */

	ShowDrob(drobA);
	std::cout << "  +  ";
	ShowDrob(drobB);
	std::cout << "  =  ";
	

   drobA = summa;

}
void Fraction::SokrDrob(drob a)
{
	
	tmpA.chisl = a.chisl / (NOD(a.chisl, a.znamenatel))  ;
	tmpA.znamenatel =  a.znamenatel / (NOD(a.chisl, a.znamenatel));
	
	drobA = tmpA;
}
bool Fraction::CheckSokrDrob(drob a)
{
	if (NOD(a.chisl, a.znamenatel) == 1) return false;
	else return true;
}
void Fraction::GetDrobA()
{

}
void Fraction::GetDrobB()
{

}
bool Fraction::CheckNormalFraction(drob a)
{
	if (a.chisl > a.znamenatel) return false;
	if (a.chisl < a.znamenatel) return true;

}

void Fraction::MultyFract()
{
	

	multy.chisl = drobA.chisl * drobB.chisl;
	multy.znamenatel = drobA.znamenatel * drobB.znamenatel;

    ShowDrob(drobA);
	std::cout << " * ";
	ShowDrob(drobB);
	std::cout << " = ";
	drobA = multy;
	ShowDrob(multy);
	
}

void Fraction::DivsFract()
{

	divs.chisl = drobA.chisl * drobB.znamenatel;
	divs.znamenatel = drobA.znamenatel * drobB.chisl;

	ShowDrob(drobA);
	std::cout << " : ";
	ShowDrob(drobB);
	std::cout << " = ";
	drobA = divs;
	ShowDrob(divs);
}

void Fraction::ConvertNoneNormalFractionInSmFractal()
{

	   tmpA.chisl = drobA.chisl % drobA.znamenatel;
	   if (tmpA.chisl != 0) 
	   {
		   tmpA.znamenatel = drobA.znamenatel;
		   tmpA.Natur = drobA.chisl / drobA.znamenatel; 
		   drobA = tmpA;
	   }

	  
		
}

// создадим общий знаменатель результат в drobA->drobATemp drobB->drobBTemp
void Fraction::CreateObZnamenatel(drob drobA, drob drobB)
{
	/***----- DrobA ------***/


	std::cout << "Общий знаменатель " << NOKDrobs(drobA, drobB) << endl;
	std::cout << "Найден доп множитель " << (NOKDrobs(drobA, drobB) / drobA.znamenatel) << "\n";

	drobA.chisl = (NOKDrobs(drobA, drobB) / drobA.znamenatel) * drobA.chisl;
	drobA.znamenatel = NOKDrobs(drobA, drobB);

	/***----- DrobB ------***/
	std::cout << "Найден доп множитель " << (NOKDrobs(drobA, drobB) / drobB.znamenatel) << endl;
	drobB.chisl = (NOKDrobs(drobA, drobB) / drobB.znamenatel) * drobB.chisl;
	drobB.znamenatel = NOKDrobs(drobA, drobB);


	tmpA = drobA; tmpB = drobB;

	//ShowDrob(drobA);

	ShowDrob(drobB);
}
