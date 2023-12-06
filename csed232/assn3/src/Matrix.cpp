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

#include "Matrix.h"
#include <utility>

/*******************************************************************************
 * Default constructor.
 * 
 * Constructs a 1x1 matrix with the value 0.
 ******************************************************************************/
Matrix::Matrix()
	: m_data{1, FloatVector{1}}, m_rowCount{1}, m_colCount{1}
{ }

/*******************************************************************************
 * Size constructor.
 * 
 * Constructs a zero-initialised matrix with the given dimensions.
 * 
 * @param rowCount The number of rows in the matrix.
 * @param colCount The number of columns in the matrix.
 ******************************************************************************/
Matrix::Matrix(std::size_t rowCount, std::size_t colCount)
	: m_data{rowCount, FloatVector{colCount}}, m_rowCount{rowCount}, m_colCount{colCount}
{ }

/*******************************************************************************
 * Initialiser list constructor.
 * 
 * Constructs a matrix with the given dimensions and initialises it with the
 * given data.
 * 
 * @param rowCount The number of rows in the matrix.
 * @param colCount The number of columns in the matrix.
 * @param data The data to initialise the matrix with.
 * 
 * @warning The given data must not be of a smaller dimension than the matrix.
 * The behaviour in this case is undefined.
 ******************************************************************************/
Matrix::Matrix(std::size_t rowCount, std::size_t colCount, const float* const* data)
	: m_data{rowCount}, m_rowCount{rowCount}, m_colCount{colCount}
{
	// SAFETY: Using `data` of a smaller dimension than `rowCount` x `colCount` is UB
	for (std::size_t i = 0; i < rowCount; ++i)
		m_data[i] = FloatVector{colCount, data[i]};
}

/*******************************************************************************
 * Copy constructor.
 * 
 * Constructs a matrix with the same dimensions and data as the given matrix.
 * 
 * @param other The matrix to copy.
 ******************************************************************************/
Matrix::Matrix(const Matrix& other)
	: m_data{other.m_data}, m_rowCount{other.m_rowCount}, m_colCount{other.m_colCount}
{ }

/*******************************************************************************
 * Move constructor.
 * 
 * Constructs a matrix with the same dimensions and data as the given matrix.
 * 
 * @param other The matrix to move.
 ******************************************************************************/
Matrix::Matrix(Matrix&& other)
	: m_data{std::move(other.m_data)}, m_rowCount{other.m_rowCount}, m_colCount{other.m_colCount}
{ }

/*******************************************************************************
 * Destructor.
 * 
 * Destroys the matrix.
 ******************************************************************************/
Matrix::~Matrix()
{ }

/*******************************************************************************
 * Row count getter.
 * 
 * @return The number of rows in the matrix.
 ******************************************************************************/
std::size_t Matrix::rowCount() const
{
	return m_rowCount;
}

/*******************************************************************************
 * Column count getter.
 * 
 * @return The number of columns in the matrix.
 ******************************************************************************/
std::size_t Matrix::colCount() const
{
	return m_colCount;
}

/*******************************************************************************
 * Element getter.
 * 
 * @param i The row index of the element to get.
 * @param j The column index of the element to get.
 * 
 * @return A reference to the element at the given indices.
 * 
 * @warning The behaviour is undefined if the given indices are out of bounds.
 ******************************************************************************/
float& Matrix::element(std::size_t i, std::size_t j)
{
	// SAFETY: No bounds checking is performed by either this function
	// or `Vector::operator[]`, meaning this function will fail spectacularly
	// if the given indices are out of bounds.
	return m_data[i][j];
}

/*******************************************************************************
 * Element getter (const overload).
 * 
 * @param i The row index of the element to get.
 * @param j The column index of the element to get.
 * 
 * @return A const reference to the element at the given indices.
 * 
 * @warning The behaviour is undefined if the given indices are out of bounds.
 ******************************************************************************/
const float& Matrix::element(std::size_t i, std::size_t j) const
{
	// SAFETY: ditto
	return m_data[i][j];
}

/*******************************************************************************
 * Addition operator.
 * 
 * Performs element-wise addition on two matrices of the same dimension.
 * 
 * @param other The matrix to add.
 * 
 * @return A reference to self, which may have been modified.
 * 
 * @note This function is a no-op if the given matrix is not of the same
 * dimension as this matrix.
 ******************************************************************************/
Matrix& Matrix::operator+=(const Matrix& other)
{
	if (m_rowCount == other.m_rowCount &&
		m_colCount == other.m_colCount)
		for (std::size_t i = 0; i < m_rowCount; ++i)
			for (std::size_t j = 0; j < m_colCount; ++j)
				m_data[i][j] += other.m_data[i][j];

	return *this;
}

/*******************************************************************************
 * Subtraction operator.
 * 
 * Performs element-wise subtraction on two matrices of the same dimension.
 * 
 * @param other The matrix to subtract.
 * 
 * @return A reference to self, which may have been modified.
 * 
 * @note This function is a no-op if the given matrix is not of the same
 * dimension as this matrix.
 ******************************************************************************/
Matrix& Matrix::operator-=(const Matrix& other)
{
	if (m_rowCount == other.m_rowCount &&
		m_colCount == other.m_colCount)
		for (std::size_t i = 0; i < m_rowCount; ++i)
			for (std::size_t j = 0; j < m_colCount; ++j)
				m_data[i][j] -= other.m_data[i][j];

	return *this;
}

/*******************************************************************************
 * Multiplication operator.
 * 
 * Performs element-wise multiplication on two matrices of the same dimension.
 * 
 * @param other The matrix to multiply.
 * 
 * @return A reference to self, which may have been modified.
 * 
 * @note This function is a no-op if the given matrix is not of the same
 * dimension as this matrix.
 ******************************************************************************/
Matrix& Matrix::operator*=(const Matrix& other)
{
	if (m_rowCount == other.m_rowCount &&
		m_colCount == other.m_colCount)
		for (std::size_t i = 0; i < m_rowCount; ++i)
			for (std::size_t j = 0; j < m_colCount; ++j)
				m_data[i][j] *= other.m_data[i][j];

	return *this;
}

/*******************************************************************************
 * Multiplication operator (scalar overload).
 * 
 * Performs element-wise multiplication on a matrix with a scalar.
 * 
 * @param other The scalar to multiply.
 * 
 * @return A reference to self, which may have been modified.
 ******************************************************************************/
Matrix& Matrix::operator*=(float other)
{
	for (std::size_t i = 0; i < m_rowCount; ++i)
		for (std::size_t j = 0; j < m_colCount; ++j)
			m_data[i][j] *= other;

	return *this;
}

/*******************************************************************************
 * Subscript operator.
 * 
 * @param i The row index of the element to get.
 * 
 * @return A reference to the row at the given index.
 * 
 * @note Since the return value is a reference to a FloatVector, which subscript
 * operator has also been overloaded, this function can be used to fluidly
 * acquire a reference to a random member of the matrix.
 * 
 * @warning The behaviour is undefined if the given index is out of bounds.
 ******************************************************************************/
FloatVector& Matrix::operator[](std::size_t i)
{
	// SAFETY: ditto
	return m_data[i];
}

/*******************************************************************************
 * Subscript operator (const overload).
 * 
 * @param i The row index of the element to get.
 * 
 * @return A const reference to the row at the given index.
 * 
 * @note Since the return value is a const reference to a FloatVector, which
 * subscript operator has also been overloaded, this function can be used to
 * fluidly acquire a const reference to a random member of the matrix.
 * 
 * @warning The behaviour is undefined if the given index is out of bounds.
 ******************************************************************************/
const FloatVector& Matrix::operator[](std::size_t i) const
{
	// SAFETY: The same old UB on OOB since it delegates indexing to `Vector`
	return m_data[i];
}

/*******************************************************************************
 * Equality operator.
 * 
 * This function compares the matrix to another matrix. Two matrices are
 * considered equal if they are of the same dimension and have the same data in
 * the same order.
 * 
 * @param other The matrix to compare.
 * 
 * @return `true` if the matrices are equal, `false` otherwise.
 ******************************************************************************/
bool Matrix::operator==(const Matrix& other) const
{
	return m_data == other.m_data;
}

/*******************************************************************************
 * Inequality operator.
 * 
 * This function compares the matrix to another matrix. Two matrices are
 * considered unequal if they are of different dimensions or contain different
 * data.
 * 
 * @param other The matrix to compare.
 * 
 * @return `true` if the matrices are unequal, `false` otherwise.
 * 
 * @note This function uses the equality operator and inverts its result.
 ******************************************************************************/
bool Matrix::operator!=(const Matrix& other) const
{
	return !(*this == other);
}

/*******************************************************************************
 * Equality operator.
 * 
 * This function compares the matrix to a two-dimensional array. A matrix is
 * considered equal to a two-dimensional array if it is of the same dimension
 * and has the same data in the same order.
 * 
 * @param data The two-dimensional array to compare to.
 * 
 * @return `true` if the matrix and the array are equal, `false` otherwise.
 * 
 * @warning This function assumes `data` is of the same dimension as the matrix,
 * meaning using `data` of a different dimension is UB. Prefer
 * `operator==(const Matrix& other)` if this cannot be guaranteed.
 ******************************************************************************/
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

/*******************************************************************************
 * Inequality operator.
 * 
 * This function compares the matrix to a two-dimensional array. A matrix is
 * considered unequal to a two-dimensional array if it is of different
 * dimensions or contains different data.
 * 
 * @param data The two-dimensional array to compare to.
 * 
 * @return `true` if the matrix and the array are unequal, `false` otherwise.
 * 
 * @note This function uses the equality operator and inverts its result.
 * 
 * @warning This function assumes `data` is of the same dimension as the matrix,
 * meaning using `data` of a different dimension is UB. Prefer
 * `operator!=(const Matrix& other)` if this cannot be guaranteed.
 ******************************************************************************/
bool Matrix::operator!=(const float* const* data) const
{
	// SAFETY: ditto
	return !(*this == data);
}

/*******************************************************************************
 * Copy assignment operator.
 * 
 * This definition overrides the default copy assignment operator to perform a
 * deep copy of the given matrix and acquire a separate ownership of its data.
 * 
 * @param other The matrix to copy.
 * 
 * @return A reference to self, which may have been modified.
 ******************************************************************************/
Matrix& Matrix::operator=(const Matrix& other)
{
	m_data = other.m_data, m_colCount = other.m_colCount, m_rowCount = other.m_rowCount;

	return *this;
}

/*******************************************************************************
 * Move assignment operator.
 * 
 * This definition overrides the default move assignment operator to acquire
 * ownership of the given matrix's existing data, leaving `other` in a valid but
 * unspecified state. The current matrix is destroyed.
 * 
 * @param other The matrix to move from.
 * 
 * @return A reference to self, which may have been modified.
 ******************************************************************************/
Matrix& Matrix::operator=(Matrix&& other)
{
	m_data = std::move(other.m_data), m_colCount = other.m_colCount, m_rowCount = other.m_rowCount;

	return *this;
}

/*******************************************************************************
 * Matrix multiplication.
 * 
 * Performs matrix multiplication on two matrices of compatible dimensions. Two
 * matrices are compatible if the number of columns in the first matrix is equal
 * to the number of rows in the second matrix. The result is a new matrix with
 * the same number of rows as the first matrix and the same number of columns as
 * the second matrix. Neither the current matrix nor the given matrix is
 * modified.
 * 
 * @param other The matrix to multiply.
 * 
 * @return The result of the matrix multiplication, if successful.
 * 
 * @note This function returns an empty matrix if the given matrix is not
 * compatible for a matrix multiplication with this matrix.
 ******************************************************************************/
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

/*******************************************************************************
 * Axis-wise summation.
 * 
 * Performs summation on the matrix along the given axis. If the axis is 0, the
 * result is a row vector with the same number of columns as the matrix. If the
 * axis is 1, the result is a column vector with the same number of rows as the
 * matrix. If the axis is neither 0 nor 1, the result is a 1x1 matrix. The
 * current matrix is not modified, and a new matrix is returned.
 * 
 * @param axis The axis to sum along.
 * 
 * @return The result of the summation.
 ******************************************************************************/
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

/*******************************************************************************
 * Transposition.
 * 
 * Transposes the matrix in-place. The number of rows and columns are swapped.
 ******************************************************************************/
void Matrix::transpose()
{
	Matrix result{m_colCount, m_rowCount};
	for (std::size_t i = 0; i < m_rowCount; ++i)
		for (std::size_t j = 0; j < m_colCount; ++j)
			result.m_data[j][i] = m_data[i][j];

	*this = std::move(result);
}