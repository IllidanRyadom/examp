
#define _USE_MATH_DEFINES // for C++
//#include <cmath>
#include <iostream>
//#include <cstring>
#include <list>
#include <time.h>
#include <chrono>
#include "Matr_prob.h"

clock_t start, end1;

int main() {

	setlocale(LC_ALL, "Rus");

	
	//=========================================================== КОЛЕБАТЕЛЬНОЕ ЗВЕНО ================================================
	{
		auto begin = std::chrono::steady_clock::now();
		start = clock();
		double T = 0.1, d = 0.001, K = 10, Eps = 0.2, N = 3000;
		double u = -Eps / T;
		double v = sqrt(1 - Eps * Eps) / T;

		Matrix Af(2, 2);

		Af.Matr[0][0] = (cos(v * d) * v - u * sin(v * d)) * exp(u * d) / v;
		Af.Matr[0][1] = sin(v * d) * exp(u * d) / v;
		Af.Matr[1][0] = -sin(v * d) * (u * u + v * v) * exp(u * d) / v;
		Af.Matr[1][1] = (u * sin(v * d) + v * cos(v * d)) * exp(u * d) / v;

		Matrix Bf(2, 1);

		Bf.Matr[0][0] = -exp(u * d) * K * cos(v * d) + K + exp(u * d) * K * u * sin(v * d) / v;
		Bf.Matr[1][0] = exp(u * d) * sin(v * d) * K * u * u / v + exp(u * d) * K * sin(v * d) * v;

		Matrix Cf(1, 2);

		Cf.Matr[0][0] = 1.0;
		Cf.Matr[0][1] = 0.0;


		Matrix X(2, 1);

		X.Matr[0][0] = 0.0;
		X.Matr[1][0] = 0.0;


		std::list<Matrix> Y_list;

		for (int i = 0; i < N; i++)
		{
			Y_list.push_back(Cf * X);
			X = (Matrix&)(Af * X) + Bf;
		}
		end1 = clock();
		std::cout << "vremya v ms :  " << (end1- start)<< '\n';

		auto end = std::chrono::steady_clock::now();

		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

		std::cout << "The time: " << elapsed_ms.count() << " ms\n";
	}
	
	
	//=========================================================== Аппериодическое ЗВЕНО ================================================
	{
		start = clock();
		double d1 = 0.0001, T1 = 0.008, K1 = 1, N1 = 10000;

		Matrix Af(1, 1);

		Af.Matr[0][0] = exp(-d1 / T1);

		Matrix Bf(1, 1);

		Bf.Matr[0][0] = -K1 * (exp(-d1 / T1) - 1);


		Matrix X(1, 1);

		X.Matr[0][0] = 0;

		std::list<Matrix> Y_list;

		for (int i = 0; i < N1; i++)
		{
			Y_list.push_back(X);
			X = (Matrix&)(Af * X) + Bf;
		}
		end1 = clock();
		std::cout << "vremya v ms :  " << (end1 - start) << '\n';
	}
	
	
	//=========================================================== ИНТЕГРИРУЮЩЕЕ ЗВЕНО ================================================
	{
		start = clock();
		double Kint = 2, dint = 0.0001, Nint = 100000;

		Matrix Af(1, 1);

		Af.Matr[0][0] = 1;

		Matrix Bf(1, 1);

		Bf.Matr[0][0] = Kint * dint;


		Matrix X(1, 1);

		X.Matr[0][0] = 0;

		std::list<Matrix> Y_list;

		for (int i = 0; i < Nint; i++)
		{
			Y_list.push_back(X);
			X = (Matrix&)(Af * X) + Bf;
		}
		end1 = clock();
		std::cout << "vremya v ms :  " << (end1 - start) << '\n';
	}
	
	
	//=========================================================== Низкочастотный Фильтр ЗВЕНО ================================================
	{
		start = clock();
		double dlf = 0.0001, Tlf = 2, Klf = 10, Nlf = 150000;
		Matrix Af(2, 2);

		Af.Matr[0][0] = exp(-dlf / Tlf) * (Tlf + dlf) / Tlf;
		Af.Matr[0][1] = exp(-dlf / Tlf) * dlf;
		Af.Matr[1][0] = exp(-dlf / Tlf) * (-dlf / (Tlf * Tlf));
		Af.Matr[1][1] = -exp(-dlf / Tlf) * (-Tlf + dlf) / Tlf;

		Matrix Bf(2, 1);

		Bf.Matr[0][0] = -exp(-dlf / Tlf) * Klf * (-Tlf * exp(dlf / Tlf) + Tlf + dlf) / Tlf;
		Bf.Matr[1][0] = exp(-dlf / Tlf) * Klf * dlf / (Tlf * Tlf);

		Matrix Cf(1, 2);

		Cf.Matr[0][0] = 1;
		Cf.Matr[0][1] = 0;

		Matrix X(2, 1);

		X.Matr[0][0] = 0;
		X.Matr[1][0] = 0;


		std::list<Matrix> Y_list;

		for (int i = 0; i < Nlf; i++)

		{
			Y_list.push_back(Cf * X);
			X = (Matrix&)(Af * X) + Bf;
		}
		end1 = clock();
		std::cout << "vremya v ms :  " << (end1 - start) << '\n';
	}
	
	//=========================================================== Полосовой фильтр ЗВЕНО ================================================
	{
		start = clock();
		double u, v, Eps_bpf = 0.5, T2bpf = 0.01, dbpf = 0.0001, Nbpf = 100000, T1bpf = 0.1, Kbpf = 0.1;

		u = -Eps_bpf / T2bpf;
		v = sqrt(1 - Eps_bpf * Eps_bpf) / T2bpf;

		Matrix Af(2, 2);

		Af.Matr[0][0] = -(-cos(v * dbpf) * v + u * sin(v * dbpf)) * exp(u * dbpf) / v;

		Af.Matr[0][1] = sin(v * dbpf) * exp(u * dbpf) / v;

		Af.Matr[1][0] = -sin(v * dbpf) * (u * u + v * v) * exp(u * dbpf) / v;

		Af.Matr[1][1] = (u * sin(v * dbpf) + v * cos(v * dbpf)) * exp(u * dbpf) / v;

		Matrix Bf(2, 1);

		Bf.Matr[0][0] = (v - exp(u * dbpf) * cos(v * dbpf) * v + exp(u * dbpf) * sin(v * dbpf) * u) * Kbpf / (v * u * u + v * v * v);

		Bf.Matr[1][0] = exp(u * dbpf) * sin(v * dbpf) * Kbpf / v;

		Matrix Cf(1, 2);

		Cf.Matr[0][0] = u * u + v * v;
		Cf.Matr[0][1] = T1bpf * u * u + T1bpf * v * v;


		Matrix X(2, 1);

		X.Matr[0][0] = 0;
		X.Matr[1][0] = 0;


		std::list<Matrix> Y_list;


		for (int i = 0; i < Nbpf; i++)
		{
			Y_list.push_back(Cf * X);
			X = (Matrix&)(Af * X) + Bf;
		}
		end1 = clock();
		std::cout << "vremya v ms :  " << (end1 - start) << '\n';

	}

	//=========================================================== Каскадная Реализация  ================================================
	{
		start = clock();
		double d1 = 0.0001, T1 = 2, K1 = 10, N1 = 150000;
		Matrix Af(1, 1);

		Af.Matr[0][0] = exp(-d1 / T1);

		Matrix Bf(1, 1);

		Bf.Matr[0][0] = -K1 * (exp(-d1 / T1) - 1);


		Matrix X1(1, 1);

		X1.Matr[0][0] = 0;

		Matrix Cf(1, 1);

		Cf.Matr[0][0] = 1 / K1;

		Matrix X2(1, 1);

		X2.Matr[0][0] = 0;

		std::list<Matrix> Y_list;

		for (int i = 0; i < N1; i++)
		{
			Y_list.push_back(Cf * X2);
			X1 = Af * (Matrix&)(X1 + Bf);
			X2 = (Matrix&)(Af * X2) +  (Matrix&)(Bf * X1);

		}
		end1 = clock();
		std::cout << "vremya v ms :  " << (end1 - start) << '\n';
	}
	
system("pause");
};


