#ifndef FLOAT_MATRIX_H
#define FLOAT_MATRIX_H

#include "FloatVector.h"
#include "Vector.h"

class Matrix
{
private:
    Vector<FloatVector> m_data;
    std::size_t m_rowCount;
    std::size_t m_colCount;

public:
    Matrix();
    Matrix(std::size_t rowCount, std::size_t colCount);
    Matrix(std::size_t rowCount, std::size_t colCount, const float* const* data);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();

    std::size_t rowCount() const;
    std::size_t colCount() const;

    const float& element(std::size_t i, std::size_t j) const;
    float& element(std::size_t i, std::size_t j);

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(float other);
    const FloatVector& operator[](std::size_t i) const;
    FloatVector& operator[](std::size_t i);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    bool operator==(const float* const* data) const;
    bool operator!=(const float* const* data) const;

    Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other); 

    Matrix matmul(const Matrix& other) const;
    Matrix sum(int axis = -1) const;
    void transpose();
};

#endif