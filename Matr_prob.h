#pragma once
class Matrix
{
	//double** Matr;
	int rows, cols;

public:
	double** Matr;
	// ������ ������� iRows * iCols
	Matrix(int iRows, int iCols);
	// ����������� ����� 
	Matrix(const Matrix& obj);
	int get_rows(); // ���������� �����
	int get_cols();  // ���������� �����
	// ������������ ��� ������
//	std::string v_stroku();
	// ������������� ������� 
//	void Transpose();
	// ������ ���������� ��������� ������� n x n
//	Matrix(int n);
	// ����������
	~Matrix();
	// ����� ���� ������
	friend Matrix operator +(Matrix& op1, Matrix& op2);
	// ������� ���� ������ 
//	friend Matrix operator -(Matrix& op1, Matrix& op2);
	//��������� ���� ������ 
	friend Matrix operator *(Matrix& op1,  Matrix& op2);
	// ��������� ������� �� �����
//	friend Matrix operator *(Matrix &op1, int op2);
//	friend Matrix operator *(int op2, Matrix &op1);
	// ������� ������� �� �����
//	friend Matrix operator /(Matrix& op1,  int op2);

	// ������� �����
//	Matrix operator -() const;
	// �������� =
	void operator =(Matrix op2);
};

