#include "Matr_prob.h"
#include <iostream>
//#include <string>
//using namespace std;



Matrix::~Matrix() {
	for (int i = 0; i < rows; i++)
	{
		delete[] Matr[i];
	}
	delete[] Matr;
}

int Matrix::get_rows() {
	return this->rows;
}

int Matrix::get_cols() {
	return this->cols;
}

Matrix operator +(Matrix& op1, Matrix& op2) {
	Matrix temp(op1.rows, op1.cols);
	for (int i = 0; i < op1.rows; i++)
		for (int j = 0; j < op1.cols; j++)
			temp.Matr[i][j] = op1.Matr[i][j] + op2.Matr[i][j];
	return temp;
}


Matrix operator *(Matrix& op1, Matrix& op2) {
	Matrix temp(op1.rows, op2.cols);
	for (int i = 0; i < op1.rows; i++)
		for (int j = 0; j < op2.cols; j++)
			for (int k = 0; k < op1.cols; k++)
				temp.Matr[i][j] += op1.Matr[i][k] * op2.Matr[k][j];
	return temp;
}

void Matrix::operator =(Matrix op2) {
	std::cout << " v ravno " << std::endl;
	rows = op2.rows;
	cols = op2.cols;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			Matr[i][j] = op2.Matr[i][j];
	}
}

/*
Matrix::Matrix(int n)
{
	Matr = new double* [n];
	for (int i = 0; i < n; i++) {
		Matr[i] = new double[n];
		for (int j = 0; j < n; j++)
			Matr[i][j] = 0;
	}

	for (int i = 0; i < n; i++) {
		Matr[i][i] = 1;
	}

	rows = cols = n;
}
*/
Matrix::Matrix(int iRows, int iCols)
{
	Matr = new double* [iRows];
	for (int i = 0; i < iRows; i++) {
		Matr[i] = new double[iCols];
		for (int j = 0; j < iCols; j++)
			Matr[i][j] = 0;
	}

	rows = iRows;
	cols = iCols;
}

Matrix::Matrix(const Matrix& obj) {    // ����������� �����
	rows = obj.rows;
	cols = obj.cols;
	Matr = new double* [rows];
	for (int i = 0; i < rows; i++) {
		Matr[i] = new double[cols];
		for (int j = 0; j < cols; j++)
			Matr[i][j] = obj.Matr[i][j];
	}
}
/*
string Matrix::v_stroku() {
	string s1 = "";
	for (int i = 0; i < rows; i++) {
		s1 += "\n";
		for (int j = 0; j < cols; j++)
			s1 += to_string(Matr[i][j]) + " ";
	}
	return s1;
}

void Matrix::Transpose() {
	double** temp;
	int temp1;

	temp = new double* [cols];
	for (int i = 0; i < cols; i++)
		temp[i] = new double[rows];

	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++)
			temp[i][j] = Matr[j][i];      // temp ����������������� �������

	for (int i = 0; i < rows; i++)
	{
		delete[] Matr[i];
	}
	delete[] Matr;

	Matr = new double* [cols];
	for (int i = 0; i < cols; i++)
		Matr[i] = new double[rows];

	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++)
			Matr[i][j] = temp[i][j];
	temp1 = cols;
	cols = rows;
	rows = temp1;
}

Matrix operator *(Matrix &op1, int op2) {
	Matrix temp(op1.rows, op1.cols);
	for (int i = 0; i < op1.rows; i++)
		for (int j = 0; j < op1.cols; j++)
			temp.Matr[i][j] = op1.Matr[i][j] * op2;
	return temp;
}

Matrix operator *(int op2, Matrix &op1) {
	Matrix temp(op1.rows, op1.cols);
	for (int i = 0; i < op1.rows; i++)
		for (int j = 0; j < op1.cols; j++)
			temp.Matr[i][j] = op1.Matr[i][j] * op2;
	return temp;
}

Matrix Matrix::operator -() const {
	Matrix temp(rows, cols);
	temp = (Matrix &)*this * -1;
	return temp;
}
Matrix operator -(Matrix& op1, Matrix &op2) {
	if (op1.rows != op2.rows || op1.cols != op2.cols) {
		cout << endl << "������� ������ ���� ����� " << endl;
		return NULL;
	}
	Matrix temp(op1.rows, op1.cols);
	temp = (Matrix &)op1 + (Matrix &)-op2;
	return temp;
}

Matrix operator /(Matrix& op1, int op2) {
	Matrix temp(op1.rows, op1.cols);
	for (int i = 0; i < op1.rows; i++)
		for (int j = 0; j < op1.cols; j++)
			temp.Matr[i][j] = op1.Matr[i][j] / op2;
	return temp;
}
*/
