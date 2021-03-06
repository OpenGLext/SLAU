// MethodKramera.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Fraction.h"
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;

Fraction frac;


struct indexMatrix
{
	int a;
	int b;

};

struct AllMinor
{
  float  oneMinor[4];
  float  twoMinor[4];
  float  threeMinor[4];
  float  forMinor[4];
};

float det[4];
float vec[4];
float vecX[2];
float tmpVec[2];

float det3x3[8],detOne3x3[8],detTwo3x3[8],detThree3x3[8];
float newmatrix[14];
float advDiag[2];
float subMainDiag[2];
float transMatrix[8];
float dcopy[8];
int selMAtrix;
float opredel;
int i;
float deltax, delta, deltay,deltaz;
float x, y, z;
float tr;
float MatMinor3x3[8];
float MatMinor2x2[3];
float korni3x3[3];
float AdvMatrix[4];
typedef int aa[3][3];
aa *a;
float *dinamDet;
float *dinamVec;

//превратим матрицу в расширенную матрицу добавив столбец вектор
void TranslateMatrixToAdvMatrix(float *d, float *vec)
{
	for (int i = 0; i < 9; i++)
		AdvMatrix[i] = d[i];

	AdvMatrix[3] = vec[0];
	AdvMatrix[7] = vec[1]; 
	AdvMatrix[11] = vec[2];

}

// Ранг матрицы 3x3
int RangMatrix(aa *a,int n,int m)
{
	////ранг матрицы
	//const double EPS = 1E-9;
	//// матрица nxm ?

	//int rank = max(n, m);
	////char matrix ?
	//vector<char> line_used(n);
	//for (int i = 0; i < m; ++i)
	//{
	//	int j;
	//	for (j = 0; j < n; ++j)
	//		if (!line_used[j] && abs(a[j][i]) > EPS)
	//			break;
	//	if (j == n)
	//		--rank;
	//	else
	//	{
	//		line_used[j] = true;
	//		for (int p = i + 1; p < m; ++p)
	//			a[j][p] /= a[j][i];
	//		for (int k = 0; k < n; ++k)
	//			if (k != j && abs(a[k][i]) > EPS)
	//				for (int p = i + 1; p < m; ++p)
	//					a[k][p] -= a[j][p] * a[k][i];
	//	}
	//}

	return 1;
}
//умножим матрицу на вектор ---> на выходе вектор tmpVec
void MultyMatrixOnVector(float *d, float *v)
{
	  tmpVec[0] = (( d[0] * v[0] ) + ( d[3] * v[1]) + (d[6] * v[2]) );
	  tmpVec[1] = (( d[1] * v[0] ) + ( d[4] * v[1]) + (d[7] * v[2]) );
	  tmpVec[2] = (( d[2] * v[0] ) + ( d[5] * v[1]) + (d[8] * v[2]) );

}
float Determinant2x2(float *det)
{
	//det[3] = 0;
	return ((det[0]*det[3]) - (det[1]*det[2]));

}
float Determinant2x2Index(float *det, int indx,indexMatrix indOne,indexMatrix indTwo)
{
	return det[indx] = (det[indOne.a] * det[indOne.b]) - ( det[indTwo.a] * det[indTwo.b]);
}
float Determinant3x3(float *det)
{
	return (det3x3[0] * det3x3[4] * det3x3[8]) +
		   (det3x3[6] * det3x3[1] * det3x3[5]) +
		   (det3x3[3] * det3x3[7] * det3x3[2]) -
		   (det3x3[6] * det3x3[4] * det3x3[2]) -
		   (det3x3[0] * det3x3[7] * det3x3[5]) -
		   (det3x3[3] * det3x3[1] * det3x3[8]);
}

// получим 4и матрицы миноры из матрицы 4x4
AllMinor GetAllMinor(float *dinamDet)
{
	AllMinor all;

	all.oneMinor[0] = dinamDet[5]; all.oneMinor[1] = dinamDet[6];  all.oneMinor[2] = dinamDet[7];
	all.oneMinor[3] = dinamDet[9];  all.oneMinor[4] = dinamDet[10];  all.oneMinor[5] = dinamDet[11];
	all.oneMinor[6] = dinamDet[13];  all.oneMinor[7] = dinamDet[14];  all.oneMinor[8] = dinamDet[15];

	return all;
}
float DeterminantNxM(float *dinamDet,int sz)
{
	float s = 0.0f; float onestrMatrix[3];
	float oneMatrix[3], twoMatrix[3];
	AllMinor all;

	all = GetAllMinor(dinamDet);
	
	onestrMatrix[0] = dinamDet[0]; onestrMatrix[1] = dinamDet[1]; 
	onestrMatrix[2] = dinamDet[2]; onestrMatrix[3] = dinamDet[3];

	 for (int j=0;j<3;j++)
	for (int i = 0; i < 4; i++)
		s = s + (all.oneMinor[i] * Determinant3x3(oneMatrix) * powf(-1, i + j));
	 // ошибка стека s - содержит кривые данныые
	 return s;
}
float DetOne(float *detOne3x3)
{
	return 0.0f; //(detOne3x3);
}
float GetDeltaX(float *det)
{
	return (vec[0]*det[3]) - (vec[1]*det[2]);
}
float  GetDeltaY(float *det)
{
	return (vec[1]*det[0]) - (vec[0] * det[1]) ;
}
void TransportMatrix(float *det, float *transMatrix)
{
    transMatrix[0] = det[0];
	transMatrix[1] = det[3];
	transMatrix[2] = det[6];
	transMatrix[3] = det[1];
	transMatrix[4] = det[4];
	transMatrix[5] = det[7];
	transMatrix[6] = det[2];
	transMatrix[7] = det[5];
	transMatrix[8] = det[8];
}
void PrintMatrix(float *det)
{
	std::cout << endl;
  std::cout << "|   "<< det[0]<<" "<<" "<<" "<<det[3]<<" "<<" "<<" "<<det[6]<<"|"<<endl;
  std::cout << "|  "<< det[1]<< " "<<" "<<" "<<det[4]<< " "<<" "<<" "<<det[7]<<"|"<<endl;
  std::cout << "|   "<< det[2]<< " " << " " << det[5] << " " << " " <<" "<< det[8] << "|" << endl;
  std::cout << endl;
}
void PrintVector(float *v)
{
	std::cout << endl;
	std::cout << "|   " <<  v[0]   << "|" << endl;
	std::cout << "|  "  <<  v[1]   << "|" << endl;
	std::cout << "|   " <<  v[3]   << "|" << endl;
	std::cout << endl;
}
float TriangleMethodDelta(float *d)
{

	 return ( 
		    d[2]*d[3]*d[8] +
		    d[5]*d[1]*d[6] -
		    d[0]*d[5]*d[7] -
		    d[8]*d[3]*d[1] );
 
}
float MainDiagonal(float *d)
{
	return d[0] * d[4] * d[8];
}
void MainSubDiagonals(float *d)
{
	subMainDiag[0] =  d[0] * d[4] * d[8];
	subMainDiag[1] =  d[1] * d[5] * d[6];
	subMainDiag[2] =  d[2] * d[3] * d[7];
}
float AdvDiagonal(float *d)
{
	 return -(d[2]*d[4]*d[6]);

}
void AdvDiagonalSaveDiagonals(float *d)
{
	advDiag[0] = (d[2] * d[4] * d[6]);
	advDiag[1] = (d[0] * d[5] * d[7]);
	advDiag[2] = (d[1] * d[3] * d[8]);

	
}
float SubFunctionDeterminant(float *d)
{
	return (d[1] * d[5] * d[11]) +
		(d[2] * d[10] * d[14]) -
		(d[9] * d[5] * d[7]) -
		(d[12] * d[10] * d[8]);
}
float Determinant(float *d)
{
	float dd = 0; float dd_ = 0; float dd3 = 0;
	

	for (int i = 0; i < 9; i++)
	{
		newmatrix[i] = d[i];
	}

	//add two strings

	newmatrix[9] = d[0]; newmatrix[10] = d[3]; newmatrix[11] = d[6];
	newmatrix[12] = d[1]; newmatrix[13] = d[4]; newmatrix[14] = d[7];

	dd = MainDiagonal(d);
	dd_ = -AdvDiagonal(d);
	//dd_ = CheckSign(dd_);
	dd3 = -SubFunctionDeterminant(newmatrix);
	//dd3 = CheckSign(dd3);
	dd = (dd + (-dd_) - dd3);
		  

	
	return dd;
}
float TriangleMulty(float a, float b, float c)
{
	return a * b*c;
}
float CalcSubAddDiagonal(float *d)
{
	i =  TriangleMulty(d[0], d[5], d[7]);
	tr = TriangleMulty(d[1], d[3], d[8]);

	return (-i) + (-tr);
	// неверный знак после TriangleMulty
}
float  CheckSign(float a)
{
	if ((a == 0) || (a == -0)) return 0;
	if (a < 0) return abs(a);
	if (a > 0) return -a;
}
float MethodLineDelta(float *d)
{
	float m,n,tr;
	
	MainSubDiagonals(d);

	m = subMainDiag[0] + subMainDiag[1] + subMainDiag[2];

	AdvDiagonalSaveDiagonals(d);

	m = m + CheckSign(advDiag[0]) + CheckSign(advDiag[1]) + CheckSign(advDiag[2]);
	

	return m;
}
void AddVectorToMatrix(float *d)
{
	
	float m, n;
	

	for  (int i = 0;  i < 9;  i++)
	{
		dcopy[i] = d[i];
	}

	//add first row
	
    d[0] = vec[0];
	d[1] = vec[1];
	d[2] = vec[2];

	PrintMatrix(d);


	deltax = MethodLineDelta(d);

    d[0] = dcopy[0]; d[1] = dcopy[1]; d[2] = dcopy[2];
	d[3] = vec[0]; d[4] = vec[1]; d[5] = vec[2];

	PrintMatrix(d);


	deltay = MethodLineDelta(d);

	//add 3 row
	d[3] = dcopy[3]; d[4] = dcopy[4]; d[5] = dcopy[5];
	d[6] = vec[0]; d[7] = vec[1]; d[8] = vec[2];

	PrintMatrix(d);


	deltaz = MethodLineDelta(d);

	// добавить проверку кратность деления иначе образовать дроби
	korni3x3[0] = deltax / delta;
	korni3x3[1] = deltay / delta;
	korni3x3[2] = deltaz / delta;

}
void SearchMatrixMinor(float *det3x3)
{
	float det=0;


	det = Determinant3x3(det3x3);
	if ( det != 0) { std::cout << "Determinant not zero" << endl;
	std::cout << det << endl;}

	MatMinor3x3[0] = (det3x3[4] * det3x3[8]) - (det3x3[5] * det3x3[7]);
	MatMinor3x3[3] = (det3x3[1] * det3x3[8]) - (det3x3[2] * det3x3[7]);
	MatMinor3x3[6] = (det3x3[1] * det3x3[5]) - (det3x3[2] * det3x3[4]);
	MatMinor3x3[1] = (det3x3[3] * det3x3[8]) - (det3x3[5] * det3x3[6]);
	MatMinor3x3[4] = (det3x3[0] * det3x3[8]) - (det3x3[2] * det3x3[6]);
	MatMinor3x3[7] = (det3x3[0] * det3x3[5]) - (det3x3[2] * det3x3[3]);
	MatMinor3x3[2] = (det3x3[3] * det3x3[7]) - (det3x3[4] * det3x3[6]);
	MatMinor3x3[5] = (det3x3[0] * det3x3[7]) - (det3x3[1] * det3x3[6]);
	MatMinor3x3[8] = (det3x3[0] * det3x3[4]) - (det3x3[1] * det3x3[3]);
	//Display MinorMatrix
	std::cout << "Матрица миноров " << endl;
	PrintMatrix(MatMinor3x3);

	//сменим знаки
	MatMinor3x3[3] = CheckSign(MatMinor3x3[3]); 
	MatMinor3x3[1] = CheckSign(MatMinor3x3[1]);
	MatMinor3x3[5] = CheckSign(MatMinor3x3[5]);
	MatMinor3x3[7] = CheckSign(MatMinor3x3[7]);
	std::cout << "Матрица алгебр.дополнений" << endl;
	PrintMatrix(MatMinor3x3);

	//транспонируем матрицу
	TransportMatrix(MatMinor3x3, transMatrix);
	std::cout << "Транспонированная матрица алгеб.дополнений" << endl;
	PrintMatrix(transMatrix);

	//получим корни
	MultyMatrixOnVector(transMatrix, vec);
	std::cout << "Корни A = 1/det A * mat * vec " << endl;
	std::cout << "Вектор " << endl;
	PrintVector(tmpVec);

	std::cout << " x = " << "(1/" << abs(det) << ")*" << tmpVec[0] << endl;
	std::cout << " y =  " << "(1/" << abs(det) << ")*" << tmpVec[1] << endl;
	std::cout << " z = " <<"(1/"<< abs(det)<<")*"<<tmpVec[2]<<endl;

	std::cout << " x = " << ((1/det)*tmpVec[0])<< " y =  "<<(1/det)*tmpVec[1] <<" z = "<<
		                   (1/det)*tmpVec[2]<< endl;


}
void MethodInvertMatrix2x2(float *d)
{
	//if (Determinant2x2(d) == 0) { std::cout << "Обратной матрицы НЕТ" << endl; }
//	else
		//SearchMatrixMinor();
	//SearchAdvMatrix();
	//TransportMatrix();
}
// извлечем знаки из матрицы ---> операции для проверки подстановки корней 
// храним в строке ?
string GetSignElementsMatrix(float *det)
{
	string s = " ";

	for ( i = 0;  i < 9;  i++)
	{
		if (det[i] < 0) s = s + "-";
		else s = s + "+";
	}

	return  s;
}


// проверка полученных корней вектор O
bool CheckAnswer(float *det)
{
	if ( ( det3x3[0] * korni3x3[0] ) == vec[0] &&
		 ( det3x3[1] * korni3x3[1]) ==  vec[1] &&
		 ( det3x3[2] * korni3x3[2]) ==  vec[2] ) 
      { 
	  
	  return true;
     
       }

	else return false;
}
// проверка уравнения 3х3 матрицы - подставим корни.умножим на коэфициенты и произведем действия
bool CheckLinearSystemMatrix3x3()
{

	return false;

	return true;
}

//Проверка СОВМЕСТНОСТИ РЕШЕНИЯ СЛАУ
bool CheckSovmestSLAU(float *d,float *v,int rangMatrixd,int rangMatrixAdv)
{
	int rA=0, rAAdv=0;
	
	// Ранг матрицы основной вычислим
	//rA = RangMatrix(d);

	// Из основной матрицы получим расширенную матрицу
	TranslateMatrixToAdvMatrix(d, v);

	std::cout << "Расширенная матрица " << endl;
	PrintMatrix(AdvMatrix);
	    
	  // Вычислим ранг расш матрицы
	   //  rAAdv = RangMatrix(AdvMatrix);
	
		 if (rangMatrixd == rangMatrixAdv) return true;
	else return false;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	/* debug data 2x2  */
	det[0] = 0; det[1] = 0; det[2] = 0; det[3] = 0;
	//vec[0] = 2; vec[1] = 9; vec[2] = 17; vec[3] = 0;
	vec[0] = 2; vec[1] = 9; vec[2] = 17; vec[3] = 0;


	/* debug data 3x3 */
	/*det3x3[0] = 2;
	det3x3[1] = 2; 
	det3x3[2] = 6;

	det3x3[3] = -3;
	det3x3[4] = 1;
	det3x3[5] = -5;

	det3x3[6] = 1;
	det3x3[7] = -4;
	det3x3[8] = 2;*/

	//other matrix
	det3x3[0] = 2;
	det3x3[1] = 2;
	det3x3[2] = 6;
	det3x3[3] = -3;
	det3x3[4] = 1;
	det3x3[5] = -5;
	det3x3[6] = 1;
	det3x3[7] = -4;
	det3x3[8] = 2;
	std::cout << "Решение СЛАУ" << endl << "Метод Крамера матрица 2х2х [1];" << endl <<
		"матрица 3х3 [2];" << endl << "метод обратной матрицы - матрица 3х3 [3] " << endl <<
		"Проверка совместного решения СЛАУ [4]" << endl<<
		         "Задать свой размер матрицы и вектора [5]"<<endl;
	
	//std::cout << "Выбор Матрицы 2х2 - [1] 3x3 - [2] " << endl;
	std::cin >> selMAtrix;
	//selMAtrix = 2;
	//PrintMatrix(transMatrix);

	if (selMAtrix == 1) 
	{
		selMAtrix = 0;
		std::cout << "Ввод матрицы.Ввод сверху вниз по столбцам.Пустые значения ,ввести 0 " << endl;

		for (i=0; i < 4; i++)
		{
			std::cout << "Matrix[" <<i<<"] = ";
			std::cin >> det[i];
		}
		
		std::cout << "Ввод вектора " << endl;
		for  (i = 0; i < 4; i++)
		{
			std::cout << "Vect[" << i << "] = ";
			std::cin >> vec[i];
		}

		//det[0] = 7; det[1] = -5; det[2] = 1; det[3] = 3;
		//vec[0] = 23; vec[1] = 1; vec[2] = 0; vec[3] = 0;

		  

		opredel = Determinant2x2(det);
		std::cout << "Определитель матрицы = "<<opredel << endl;
		if (opredel != 0)
		{ 
			deltax = GetDeltaX(det);
			x = deltax / opredel;
			std::cout << "Есть единственное решение - можно решить методом Крамера" << endl;
			std::cout << "DeltaX = " << deltax<<endl;
			std::cout << "X = " << x<<endl;


			deltay = GetDeltaY(det);
			y = deltay / opredel;
			std::cout << "DeltaY = " << deltay<<endl;
			std::cout << "Y = " << y<<endl;

			  std::cin >> i;
		}
		else if (opredel < 0) { std::cout << "Нет единственного решения - можно решить методом Гаусса" << endl; }
		
	}

	if (selMAtrix == 2)
	{
		std::cout << "Ввод матрицы.Ввод сверху вниз по столбцам.Пустые значения = 0 " << endl;

		for (i = 0; i < 9; i++)
		{
			std::cout << "Matrix[" << i << "] = ";
			std::cin >> det3x3[i];
		}
		std::cout << "Ввод вектора " << endl;
		for (i = 0; i < 3; i++)
		{
			std::cout << "Vect[" << i << "] = ";
			std::cin >> vec[i];
		}

		PrintMatrix(det3x3);
		//TransportMatrix(det3x3, transMatrix);
		delta = Determinant(det3x3);
		//delta = Determinant(det3x3);
		std::cout << "det|A| = " << delta << endl;
		std::cout << "det|A| != 0  значит, система имеет единственное решение " << endl;
		AddVectorToMatrix(det3x3);
		std::cout << "deltaX = " << deltax << endl;
		std::cout << "deltaY = " << deltay << endl;
		std::cout << "deltaZ = " << deltaz << endl;
		std::cout << "" << endl;

		if ((int)deltax % (int)delta != 0)
		{
			//std::cout << "x = deltaX / delta "<<deltax<<" / "<<delta<< endl; 

			frac.AddDrob(deltax, delta);
			if (frac.CheckSokrDrob(frac.drobA))
			{
				frac.SokrDrob(frac.drobA);
				std::cout << "x = deltaX / delta ";
				frac.ShowDrob(frac.drobA);
			}
		}
		else std::cout << "x = (deltaX / delta) " << deltax / delta << endl;

		if ((int)deltay % (int)delta != 0)
		{
			frac.AddDrob(deltay, delta);
			if (frac.CheckSokrDrob(frac.drobA))
			{
				frac.SokrDrob(frac.drobA);
				std::cout << "y = deltaY / delta ";
				frac.ShowDrob(frac.drobA);
			}
		}
		else std::cout << "y = (deltaY / delta) " << deltay / delta << endl;

		if ((int)deltaz % (int)delta != 0)
		{
			frac.AddDrob(deltaz, delta);
			if (frac.CheckSokrDrob(frac.drobA))
			{
				frac.SokrDrob(frac.drobA);
				std::cout << endl << "z = deltaZ / delta ";
				frac.ShowDrob(frac.drobA);
			}
		}
		else std::cout << "z = (deltaz / delta) " << deltaz / delta << endl;

		std::cin >> selMAtrix;
	}

	   // Матричный метод.вычисление обратной матрицы
	if (selMAtrix == 3)
	{
		std::cout << "Ввод матрицы.Ввод сверху вниз по столбцам.Пустые значения = 0 " << endl;

		for (i = 0; i < 9; i++)
		{
			std::cout << "Matrix[" << i << "] = ";
			std::cin >> det3x3[i];
		}
		std::cout << "Ввод вектора " << endl;
		for (i = 0; i < 3; i++)
		{
			std::cout << "Vect[" << i << "] = ";
			std::cin >> vec[i];
		}
		SearchMatrixMinor(det3x3);
		std::cin >> selMAtrix;
	}

	if (selMAtrix == 4)
	{
		selMAtrix = 0;
		int rangMatrixd = 0, rangMatrixAdv = 0;

		std::cout << "Ввод матрицы.Ввод сверху вниз по столбцам.Пустые значения ,ввести 0 " << endl;
		rangMatrixd = 2;  rangMatrixAdv = 3;

		for (i = 0; i < 9; i++)
		{
			std::cout << "Matrix[" << i << "] = ";
			std::cin >> det[i];
		}

		std::cout << "Ввод вектора " << endl;
		for (i = 0; i < 4; i++)
		{
			std::cout << "Vect[" << i << "] = ";
			std::cin >> vec[i];
		}

		if (CheckSovmestSLAU(det, vec,rangMatrixd,rangMatrixAdv)) { std::cout << "СЛАУ имеет совместное решение! Решение имеет один ответ." << endl; }
		else { std::cout << "СЛАУ не имеет совместного решения! Нет корней." << endl; }
		std::cin >> vec[i];
	}
      

	if (selMAtrix == 5)
		{
			int szMatrix, szVec;
			/*std::cout << "Ввести размер матрицы" << endl;
			std::cin >> szMatrix;
			dinamDet = new float[szMatrix];

			std::cout << "Ввести размер вектора" << endl;
			std::cin >> szVec;
			dinamVec = new float[szVec];

			for (i = 0; i < szMatrix; i++)
			{
				std::cout << "Matrix[" << i << "] = ";
				std::cin >> dinamDet[i];
			}
			std::cout << "Ввод вектора " << endl;
			for (i = 0; i < szVec; i++)
			{
				std::cout << "Vect[" << i << "] = ";
				std::cin >> dinamVec[i];
			}*/

			/* ------------- Debug Data -------------- */
			   dinamDet = new float[9]; dinamVec = new float[3]; szMatrix = 9;

			   dinamDet[0] = 2; dinamDet[1] = -3; dinamDet[2] = 1;
			   dinamDet[3] = 2; dinamDet[4] = 1; dinamDet[5] = -4;
			   dinamDet[6] = 6; dinamDet[7] = -5; dinamDet[8] = 2;
			   dinamVec[0] = 2; dinamVec[1] = 9; dinamVec[2] = 17;

			/* ------------- Debug Data -------------- */

			std::cout<<"определитель"<<DeterminantNxM(dinamDet, szMatrix)<<endl;
			
			std::cin >> i;
	    }

		return 0;
	}
	


