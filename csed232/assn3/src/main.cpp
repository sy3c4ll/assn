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

#include <iostream>
#include <cstdio>
#include "FloatVector.h"
#include "Vector.h"
#include "Matrix.h"

using namespace std;

// 필요시 테스트 함수 활용
// 지워도 무방
void print_float_vec(const FloatVector& vec)
{
	cout << "----------------------------------------" << endl;
	cout << "Print (Data size, Allocation size)" << endl;
	cout << "(" << vec.size() << ", " << vec.capacity() << ")\n\n";
	cout << "Print Data" << endl;
	for (auto it =vec.begin(); it != vec.end(); ++it) cout << *it << "\t";
	cout << endl;
}

void print_matrix(const Matrix& mat)
{
	cout << "----------------------------------------" << endl;
	cout << "Print (rowCount, colCount)" << endl;
	cout << "(" << mat.rowCount() << ", " << mat.colCount() << ")\n\n";
	cout << "Print Data" << endl;
	for (size_t i = 0; i < mat.rowCount(); ++i) { for (size_t j = 0; j < mat.colCount(); ++j) cout << mat[i][j] << "\t"; cout << endl; }
}

void test_float_vec()
{
	cout << "========================================" << endl;
	cout << "1. init vector" << endl;
	float tmp[] = { 3.2, 2.5, 2.11 };
	FloatVector vec1;
	FloatVector vec2(sizeof(tmp) / sizeof(*tmp), tmp);
	FloatVector vec3(vec2);
	print_float_vec(vec1);
	print_float_vec(vec2);
	print_float_vec(vec3);
	cout << endl;
	cout << "========================================" << endl;
	cout << "2. push_back" << endl;
	float push = 3.763;
	vec1.push_back(push);
	vec2.push_back(push);
	print_float_vec(vec1);
	print_float_vec(vec2);
	cout << endl;
	cout << "========================================" << endl;
	cout << "3. insert" << endl;
	float insrt = -5.8775;
	vec1.insert(vec1.begin(), insrt);
	float insrt_arr[] = { 3.2105, 2.51, -3.70, 3.14 };
	vec1.insert(vec1.begin(), insrt_arr, insrt_arr + sizeof(insrt_arr) /
		sizeof(*insrt_arr));
	print_float_vec(vec1);
	cout << endl;
	cout << "========================================" << endl;
	cout << "4. pop_back" << endl;
	vec1.pop_back();
	print_float_vec(vec1);
	cout << endl;
	cout << "========================================" << endl;
	cout << "5. erase" << endl;
	vec1.erase(vec1.begin() + 3);
	print_float_vec(vec1);
	cout << endl;
	cout << "========================================" << endl;
	cout << "6. resize" << endl;
	vec1.resize(3);
	print_float_vec(vec1);
	cout << endl;
	cout << "========================================" << endl;
	cout << "7. operator []" << endl;
	for (int i = 0; i < 3; i++)
		cout << vec1[i] << "\t";
	cout << endl;
	cout << "========================================" << endl;
	cout << "8. operator =" << endl;
	FloatVector vec5;
	vec5 = vec1;
	print_float_vec(vec1);
	print_float_vec(vec5);
	cout << endl;
	cout << "========================================" << endl;
	cout << "9. clear" << endl;
	vec1.clear();
	print_float_vec(vec1);
	cout << endl;
	cout << "========================================" << endl;
	cout << "10. allocate and insert" << endl;
	float pi[30] = { 0, };
	for (int i = 0; i < 30; i++)
		pi[i] = 3.14;
	vec1.allocate(int(30 * 1.5));
	vec1.insert(vec1.begin(), pi, pi + 30);
	print_float_vec(vec1);
	cout << endl;
}

void test_float_vec_template()
{
	Vector<float> vec;
	vec.push_back(3.0f);
}

void test_matrix()
{
	// 행렬 생성
	Matrix matrix1(2, 2);
	Matrix matrix2(2, 2);

	// 데이터 설정
	matrix1.element(0, 0) = 1.0;
	matrix1.element(0, 1) = 2.0;
	matrix1.element(1, 0) = 3.0;
	matrix1.element(1, 1) = 4.0;

	matrix2.element(0, 0) = 0.5;
	matrix2.element(0, 1) = 0.5;
	matrix2.element(1, 0) = 0.5;
	matrix2.element(1, 1) = 0.5;

	print_matrix(matrix1);
	print_matrix(matrix2);

	// 행렬 덧셈
	Matrix resultAdd = matrix1;
	resultAdd += matrix2;

	print_matrix(resultAdd);

	// 행렬 뺄셈
	Matrix resultSubtract = matrix1;
	resultSubtract -= matrix2;

	print_matrix(resultSubtract);

	// 행렬 곱셈 (요소별)
	Matrix resultMultiply = matrix1;
	resultMultiply *= matrix2;

	print_matrix(resultMultiply);

	// 행렬 스칼라 곱셈
	Matrix resultScalarMultiply = matrix1;
	resultScalarMultiply *= 2.0;

	print_matrix(resultScalarMultiply);

	// 행렬 곱셈
	Matrix matrix3(2, 3);
	Matrix resultMatMul = matrix1.matmul(matrix3);

	print_matrix(resultMatMul);

	// 합계 연산
	Matrix resultSumRow = matrix1.sum(0);
	Matrix resultSumCol = matrix1.sum(1);
	Matrix resultSumAll = matrix1.sum();

	print_matrix(resultSumRow);
	print_matrix(resultSumCol);
	print_matrix(resultSumAll);

	// 전치 행렬
	matrix1.transpose();

	print_matrix(matrix1);
}

int main()
{
	test_float_vec();
	test_float_vec_template();
	test_matrix();
	return 0;
}