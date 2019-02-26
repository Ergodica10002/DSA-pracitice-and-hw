#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <new>
#include "matrix.h"

Matrix::Matrix(const int& r, const int& c) //constructor
{
	row = r;
	col = c;
	array = new double*[row];
	for (int i = 0; i < row; i++)
		array[i] = new double[col];
}

Matrix::Matrix(const Matrix& rhs) //copy constructor
{
	row = rhs.row;
	col = rhs.col;
	array = new double*[row];
	for (int i = 0; i < row; i++){
		array[i] = new double[col];
		for (int j = 0; j < col; j++)
			array[i][j] = rhs[i][j];
	}
}

Matrix::~Matrix() //destructor
{
	delete array;
}

double* & Matrix::operator [](const int& idx) const	// Enable the use of A[i][j] instead of A.array[i][j]
{
	return array[idx];
}

Matrix Matrix::operator =(const Matrix& rhs) // assignment operator
{
	row = rhs.row;
	col = rhs.col;
	for (int i = 0; i < rhs.row; i++)
		for (int j = 0; j < rhs.col; j++)
			array[i][j] = rhs.array[i][j];
	return *this;
}

Matrix Matrix::operator -() const
{
	Matrix tmp(row, col);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			tmp[i][j] = -array[i][j];
	return tmp;
}
Matrix Matrix::operator +() const
{
}

Matrix Matrix::operator -(const Matrix& rhs) const
{
	Matrix tmp(row, col);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			tmp[i][j] = array[i][j] - rhs.array[i][j];
	return tmp;
}

Matrix Matrix::operator +(const Matrix& rhs) const
{	
	Matrix tmp(row, col);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			tmp[i][j] = array[i][j] + rhs.array[i][j];
	return tmp;
}

Matrix Matrix::operator *(const Matrix& rhs) const
{
}

Matrix Matrix::operator /(const Matrix& rhs) const
{
}

Matrix Matrix::inverse() const
{
}

void Matrix::read(const char* fn)
{
	int r, c;
	FILE *fp = fopen(fn, "r");
	if(fp == NULL){
		printf("read file [%s] error\n", fn);
		exit(0);
	}
	fscanf(fp, "%d%d", &r, &c);
	Matrix tmp(r, c);
	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			fscanf(fp, "%lf", &tmp.array[i][j]);
	fclose(fp);
	*this = tmp;
}

void Matrix::write(const char* fn)
{
	FILE *fp = fopen(fn, "w");
	if(fp == NULL){
		printf("write file [%s] error\n", fn);
		exit(0);
	}
	fprintf(fp, "%d %d\n", row, col);
	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			fprintf(fp, "%lf%c", array[i][j], " \n"[j==col-1]);
	fclose(fp);
}

void Matrix::print() const
{
	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			printf("%lf%c", array[i][j], " \n"[j==col-1]);
}
