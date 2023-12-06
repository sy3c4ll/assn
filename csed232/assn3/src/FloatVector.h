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

#ifndef FLOAT_VECTOR_H
#define FLOAT_VECTOR_H

#include <cstdlib>

// Uncomment this line to invalidate my three hours
// using FloatVector = Vector<float>;

class FloatVector
{
private:
	float* m_data;
	std::size_t m_capacity;
	std::size_t m_size;

	void prepare_extra(std::size_t extra);

public:
	typedef float* iterator;
	typedef const float* const_iterator;

	FloatVector();
	FloatVector(std::size_t size);
	FloatVector(std::size_t size, const float& init);
	FloatVector(std::size_t size, const float* init);
	FloatVector(const FloatVector& v);
	FloatVector(FloatVector&& v);

	~FloatVector();

	std::size_t capacity() const;
	std::size_t size() const;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	float& front();
	const float& front() const;
	float& back();
	const float& back() const;

	void allocate(std::size_t capacity);

	void resize(std::size_t size);

	void push_back(const float& value);

	void pop_back();

	void insert(iterator position, const float& value);
	void insert(iterator position, const float* first, const float* last);

	void erase(iterator position);

	void clear();

	float& operator[](std::size_t index);
	const float& operator[](std::size_t index) const;
	bool operator==(const FloatVector& v) const;
	bool operator!=(const FloatVector& v) const;
	bool operator==(const float* v) const;
	bool operator!=(const float* v) const;

	FloatVector& operator=(const FloatVector& v);
	FloatVector& operator=(FloatVector&& v);
};

#endif