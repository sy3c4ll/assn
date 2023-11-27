#include "Matrix.h"
#include <utility>

Matrix::Matrix()
	: m_data{1, FloatVector{1}}, m_rowCount{1}, m_colCount{1}
{
}

Matrix::Matrix(std::size_t rowCount, std::size_t colCount)
	: m_data{rowCount, FloatVector{colCount}}, m_rowCount{rowCount}, m_colCount{colCount}
{
}

Matrix::Matrix(std::size_t rowCount, std::size_t colCount, const float* const* data)
	: m_data{rowCount}, m_rowCount{rowCount}, m_colCount{colCount}
{
	// SAFETY: Using `data` of a smaller dimension than `rowCount` x `colCount` is UB
	for (std::size_t i = 0; i < rowCount; ++i)
		m_data[i] = FloatVector{colCount, data[i]};
}

Matrix::Matrix(const Matrix& other)
	: m_data{other.m_data}, m_rowCount{other.m_rowCount}, m_colCount{other.m_colCount}
{
}

Matrix::Matrix(Matrix&& other)
	: m_data{std::move(other.m_data)}, m_rowCount{other.m_rowCount}, m_colCount{other.m_colCount}
{
}

Matrix::~Matrix()
{
}

std::size_t Matrix::rowCount() const
{
	return m_rowCount;
}

std::size_t Matrix::colCount() const
{
	return m_colCount;
}

float& Matrix::element(std::size_t i, std::size_t j)
{
	// SAFETY: No bounds checking is performed by either this function
	// or `Vector::operator[]`, meaning this function will fail spectacularly
	// if the given indices are out of bounds.
	return m_data[i][j];
}

const float& Matrix::element(std::size_t i, std::size_t j) const
{
	// SAFETY: ditto
	return m_data[i][j];
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	if (m_rowCount == other.m_rowCount &&
		m_colCount == other.m_colCount)
		for (std::size_t i = 0; i < m_rowCount; ++i)
			for (std::size_t j = 0; j < m_colCount; ++j)
				m_data[i][j] += other.m_data[i][j];
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	if (m_rowCount == other.m_rowCount &&
		m_colCount == other.m_colCount)
		for (std::size_t i = 0; i < m_rowCount; ++i)
			for (std::size_t j = 0; j < m_colCount; ++j)
				m_data[i][j] -= other.m_data[i][j];
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	if (m_rowCount == other.m_rowCount &&
		m_colCount == other.m_colCount)
		for (std::size_t i = 0; i < m_rowCount; ++i)
			for (std::size_t j = 0; j < m_colCount; ++j)
				m_data[i][j] *= other.m_data[i][j];
	return *this;
}

Matrix& Matrix::operator*=(float other)
{
	for (std::size_t i = 0; i < m_rowCount; ++i)
		for (std::size_t j = 0; j < m_colCount; ++j)
			m_data[i][j] *= other;
	return *this;
}

const FloatVector& Matrix::operator[](std::size_t i) const
{
	// SAFETY: The same old UB on OOB since it delegates indexing to `Vector`
	return m_data[i];
}

FloatVector& Matrix::operator[](std::size_t i)
{
	// SAFETY: ditto
	return m_data[i];
}

bool Matrix::operator==(const Matrix& other) const
{
	return m_data == other.m_data;
}

bool Matrix::operator!=(const Matrix& other) const
{
	return !(*this == other);
}

bool Matrix::operator==(const float* const* data) const
{
	// SAFETY: This function assumes `data` is of the same dimension as the matrix,
	// meaning using `data` of a different dimension is UB.
	// Prefer `operator==(const Matrix& other)` if this cannot be guaranteed
	for (std::size_t i = 0; i < m_rowCount; ++i)
		if (m_data[i] != data[i])
			return false;
	return true;
}

bool Matrix::operator!=(const float* const* data) const
{
	// SAFETY: ditto
	return !(*this == data);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	m_data = other.m_data, m_colCount = other.m_colCount, m_rowCount = other.m_rowCount;
	return *this;
}

Matrix& Matrix::operator=(Matrix&& other)
{
	m_data = std::move(other.m_data), m_colCount = other.m_colCount, m_rowCount = other.m_rowCount;
	return *this;
}

Matrix Matrix::matmul(const Matrix& other) const
{
	if (m_colCount == other.m_rowCount)
	{
		Matrix result{m_rowCount, other.m_colCount};
		for (std::size_t i = 0; i < m_rowCount; ++i)
			for (std::size_t j = 0; j < other.m_colCount; ++j)
				for (std::size_t k = 0; k < m_colCount; ++k)
					result.m_data[i][j] += m_data[i][k] * other.m_data[k][j];
		return result;
	}
	else
	{
		return Matrix{};
	}
}

Matrix Matrix::sum(int axis) const
{
	if (axis == 0)
	{
		Matrix result{1, m_colCount};
		for (std::size_t i = 0; i < m_colCount; ++i)
			for (std::size_t j = 0; j < m_rowCount; ++j)
				result.m_data[0][i] += m_data[j][i];
		return result;
	}
	else if (axis == 1)
	{
		Matrix result{m_rowCount, 1};
		for (std::size_t i = 0; i < m_rowCount; ++i)
			for (std::size_t j = 0; j < m_colCount; ++j)
				result.m_data[i][0] += m_data[i][j];
		return result;
	}
	else
	{
		Matrix result{1, 1};
		for (std::size_t i = 0; i < m_rowCount; ++i)
			for (std::size_t j = 0; j < m_colCount; ++j)
				result.m_data[0][0] += m_data[i][j];
		return result;
	}
}

void Matrix::transpose()
{
	Matrix result{m_colCount, m_rowCount};
	for (std::size_t i = 0; i < m_rowCount; ++i)
		for (std::size_t j = 0; j < m_colCount; ++j)
			result.m_data[j][i] = m_data[i][j];
	*this = std::move(result);
}