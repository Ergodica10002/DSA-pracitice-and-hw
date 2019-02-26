#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <new>
class Matrix{
	public:
		double **array;
		int row;
		int col;

		Matrix(const int&, const int&); 	//constuctor
		Matrix(const Matrix&); 				//copy constructor
		~Matrix();							//destructor

		double* & operator [](const int&) const;
		Matrix operator =(const Matrix&);
		//unary operators
		Matrix operator -() const;
		Matrix operator +() const;
		//binary operators
		Matrix operator -(const Matrix&) const;
		Matrix operator +(const Matrix&) const;
		Matrix operator *(const Matrix&) const;
		Matrix operator /(const Matrix&) const;
		
		void read(const char*);
		void write(const char*);
		void print() const;
		Matrix inverse() const;
};


Matrix::Matrix(const int& r, const int& c) //constructor
{
	array = new double*[r];
	row = r;
	col = c;
	for (int i = 0; i < r; i++){
		array[i] = new double[c];
		for (int j = 0; j < c; j++)
			array[i][j] = i * c + j;	
	}
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
}

Matrix Matrix::operator -() const
{
}

Matrix Matrix::operator +() const
{
}

Matrix Matrix::operator -(const Matrix& rhs) const
{
}

Matrix Matrix::operator +(const Matrix& rhs) const
{
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

