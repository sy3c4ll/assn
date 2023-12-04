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