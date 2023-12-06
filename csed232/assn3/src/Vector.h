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

#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>

template <typename T>
class Vector
{
private:
	T* m_data;
	std::size_t m_capacity;
	std::size_t m_size;

	void prepare_extra(std::size_t extra);

public:
	typedef T* iterator;
	typedef const T* const_iterator;

	Vector();
	Vector(std::size_t size);
	Vector(std::size_t size, const T& init);
	Vector(std::size_t size, const T* init);
	Vector(const Vector& v);
	Vector(Vector&& v);

	~Vector();

	std::size_t capacity() const;
	std::size_t size() const;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	T& front();
	const T& front() const;
	T& back();
	const T& back() const;

	void allocate(std::size_t capacity);

	void resize(std::size_t size);

	void push_back(const T& value);

	void pop_back();

	void insert(iterator position, const T& value);
	void insert(iterator position, const T* first, const T* last);

	void erase(iterator position);

	void clear();

	T& operator[](std::size_t index);
	const T& operator[](std::size_t index) const;
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;
	bool operator==(const T* v) const;
	bool operator!=(const T* v) const;

	Vector& operator=(const Vector& v);
	Vector& operator=(Vector&& v);
};

#include "Vector.hpp"

#endif