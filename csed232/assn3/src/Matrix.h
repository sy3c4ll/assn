// *****************************************************************************
//
// 무은재학부 20230262 김연웅
// yeonung04 (POSTECH ID)
// 2023-2 객체지향 프로그래밍 Assignment #3
//
// 나는 이 프로그래밍 과제를 다른 소스를 인용없이 참고하거나,
// 다른 사람의 부적절한 도움을 받지 않고 완수하였습니다.
// I completed this programming task without using any uncited sources
// or receiving improper help from others.
//
// *****************************************************************************

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
	FloatVector& operator[](std::size_t i);
	const FloatVector& operator[](std::size_t i) const;
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