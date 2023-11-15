#ifndef FLOAT_MATRIX_H
#define FLOAT_MATRIX_H

#include "FloatVector.h"  // FloatVector 클래스를 사용할 경우

class Matrix
{
private:

public:
    Matrix();
    Matrix(int rowCount, int colCount);
    Matrix(int rowCount, int colCount, float** data);
    Matrix(const Matrix& other);
    ~Matrix();

    const float& element(int i, int j) const;
    float& element(int i, int j);

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(float other);
    Matrix& operator=(const Matrix& other);
	 

    Matrix matmul(const Matrix& other);
    Matrix sum(int axis = -1);
    void transpose();
};

#endif
