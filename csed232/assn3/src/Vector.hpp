#ifdef VECTOR_H

#include "Vector.h"
#include <new>
#include <utility>

constexpr inline std::size_t _increase_to_fit(std::size_t s)
{
	return s < 5 ? s : s * 2;
}

template <typename T>
void Vector<T>::prepare_extra(std::size_t extra)
{
	if (m_size + extra >= m_capacity)
		allocate(_increase_to_fit(m_size + extra));
	resize(m_size + extra);
}

template <typename T>
Vector<T>::Vector()
	: m_data{nullptr}, m_capacity{0}, m_size{0}
{ }

template <typename T>
Vector<T>::Vector(std::size_t size)
	: m_data{size ? (T*) std::malloc(size * sizeof(T)) : nullptr}, m_capacity{size}, m_size{size}
{
	for (std::size_t i = 0; i < size; ++i)
		new(m_data + i) T;
}

template <typename T>
Vector<T>::Vector(std::size_t size, const T& init)
	: m_data{size ? (T*) std::malloc(size * sizeof(T)) : nullptr}, m_capacity{size}, m_size{size}
{
	for (std::size_t i = 0; i < size; ++i)
		new(m_data + i) T{init};
}

template <typename T>
Vector<T>::Vector(std::size_t size, const T* init)
	: m_data{size ? (T*) std::malloc(size * sizeof(T)) : nullptr}, m_capacity{size}, m_size{size}
{
	for (std::size_t i = 0; i < size; ++i)
		new(m_data + i) T{init[i]};
}

template <typename T>
Vector<T>::Vector(const Vector& v)
	: m_data{v.m_size ? (T*) std::malloc(v.m_size * sizeof(T)) : nullptr}, m_capacity{v.m_size}, m_size{v.m_size}
{
	for (std::size_t i = 0; i < v.m_size; ++i)
		new(m_data + i) T{v.m_data[i]};
}

template <typename T>
Vector<T>::Vector(Vector&& v)
	: m_data{v.m_data}, m_capacity{v.m_capacity}, m_size{v.m_size}
{
	v.m_data = nullptr, v.m_capacity = 0, v.m_size = 0;
}

template <typename T>
Vector<T>::~Vector()
{
	for (std::size_t i = 0; i < m_size; ++i)
		m_data[i].~T();
	std::free(m_data);
}

template <typename T>
std::size_t Vector<T>::capacity() const
{
	return m_capacity;
}

template <typename T>
std::size_t Vector<T>::size() const
{
	return m_size;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
	return m_data;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const
{
	return m_data;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end()
{
	return m_data + m_size;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const
{
	return m_data + m_size;
}

template <typename T>
T& Vector<T>::front()
{
	// SAFETY: This function performs no bounds checking,
	// therefore bounds checking must be performed manually
	// calling when `size() == 0` is UB (usually nullptr dereference -> segfault)
	return m_data[0];
}

template <typename T>
const T& Vector<T>::front() const
{
	// SAFETY: ditto
	return m_data[0];
}

template <typename T>
T& Vector<T>::back()
{
	// SAFETY: ditto
	return m_data[m_size - 1];
}

template <typename T>
const T& Vector<T>::back() const
{
	// SAFETY: ditto
	return m_data[m_size - 1];
}

template <typename T>
void Vector<T>::allocate(std::size_t capacity)
{
	if (capacity > m_capacity)
		m_data = (T*) std::realloc(m_data, capacity * sizeof(T)),
		m_capacity = capacity;
}

template <typename T>
void Vector<T>::resize(std::size_t size)
{
	allocate(size);

	for (std::size_t i = m_size; i < size; ++i)
		new(m_data + i) T;
	for (std::size_t i = size; i < m_size; ++i)
		m_data[i].~T();
	m_size = size;
}

template <typename T>
void Vector<T>::push_back(const T& value)
{
	prepare_extra(1);

	back() = value;
}

template <typename T>
void Vector<T>::pop_back()
{
	resize(m_size - 1);
}

template <typename T>
void Vector<T>::insert(iterator position, const T& value)
{
	prepare_extra(1);

	for (iterator it = end() - 1; it > position; --it)
		*it = *(it - 1);
	*position = value;
}

template <typename T>
void Vector<T>::insert(iterator position, const T* first, const T* last)
{
	if (first >= last)
		return;

	std::size_t len = last - first;
	prepare_extra(len);

	if ((first >= begin() && first < end())
		|| (last >= begin() && last < end()))
	{
		T* cpy = new T[len];
		for (std::size_t i = 0; i < len; ++i)
			cpy[i] = first[i];

		T* cur = cpy;
		for (iterator it = end() - 1; it >= position + len; --it)
			*it = *(it - len);
		for (iterator it = position; it < position + len; ++it)
			*it = std::move(*cur++);
		delete[] cpy;
	}
	else
	{
		for (iterator it = end() - 1; it >= position + len; --it)
			*it = *(it - len);
		for (iterator it = position; it < position + len; ++it)
			*it = *first++;
	}
}

template <typename T>
void Vector<T>::erase(iterator position)
{
	for (iterator it = position; it < end() - 1; ++it)
		*it = *(it + 1);
	resize(m_size - 1);
}

template <typename T>
void Vector<T>::clear()
{
	for (std::size_t i = 0; i < m_size; i++)
		m_data[i].~T();
	std::free(m_data);

	m_data = nullptr, m_capacity = 0, m_size = 0;
}

template <typename T>
T& Vector<T>::operator[](std::size_t index)
{
	// SAFETY: UB on OOB
	return m_data[index];
}

template <typename T>
const T& Vector<T>::operator[](std::size_t index) const
{
	// SAFETY: ditto
	return m_data[index];
}

template <typename T>
bool Vector<T>::operator==(const Vector& v) const
{
	if (m_size != v.m_size)
		return false;
	for (std::size_t i = 0; i < m_size; ++i)
		if (m_data[i] != v.m_data[i])
			return false;
	return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector& v) const
{
	return !(*this == v);
}

template <typename T>
bool Vector<T>::operator==(const T* v) const
{
	// SAFETY: This function assumes `v` is of the same size as the vector,
	// meaning using `v` of a different size is UB.
	// Prefer `operator==(const Vector<T>& other)` if this cannot be guaranteed
	for (std::size_t i = 0; i < m_size; ++i)
		if (m_data[i] != v[i])
			return false;
	return true;
}

template <typename T>
bool Vector<T>::operator!=(const T* v) const
{
	// SAFETY: ditto
	return !(*this == v);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v)
{
	resize(v.m_size);
	for (std::size_t i = 0; i < m_size; ++i)
		m_data[i] = v.m_data[i];

	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& v)
{
	for (std::size_t i = 0; i < m_size; ++i)
		m_data[i].~T();
	std::free(m_data);

	m_data = v.m_data, m_capacity = v.m_capacity, m_size = v.m_size;
	v.m_data = nullptr, v.m_capacity = 0, v.m_size = 0;

	return *this;
}

#endif