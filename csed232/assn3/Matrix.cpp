#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix(int rowCount, int colCount)
{
}

Matrix::Matrix(int rowCount, int colCount, float** data)
{
}

Matrix::Matrix(const Matrix& other)
{
}

Matrix::~Matrix()
{
}

float& Matrix::element(int i, int j)
{
	static float dummy = 0.0f;
	return dummy;
}

const float& Matrix::element(int i, int j) const
{
	static const float dummy = 0.0f;
	return dummy;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	return *this; // TODO
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	return *this; // TODO
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	return *this; // TODO
}

Matrix& Matrix::operator*=(float other)
{
	return *this; // TODO
}

Matrix& Matrix::operator=(const Matrix& other)
{
	return *this; // TODO
}

Matrix Matrix::matmul(const Matrix& other)
{
	return *this; // TODO
}

Matrix Matrix::sum(int axis)
{
	return *this; // TODO
}

void Matrix::transpose()
{
}
