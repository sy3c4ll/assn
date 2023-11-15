#include "FloatVector.h"

FloatVector::FloatVector()
  : m_data(nullptr), m_capacity(0), m_size(0)
{
}

FloatVector::FloatVector(int size)
  : m_data{std::calloc(size, sizeof(float))}, m_capacity{size}, m_size{size}
{
}

FloatVector::FloatVector(int size, const float& init)
  : m_data{std::malloc(size * sizeof(float))}, m_capacity{size}, m_size{size}
{
	for (int i = 0; i < size; i++)
	  m_data[i] = init;
}

FloatVector::FloatVector(int size, const float* init)
  : m_data{std::memcpy(std::malloc(size * sizeof(float)), init, size)}, m_capacity{size}, m_size{size}
{
}

FloatVector::FloatVector(const FloatVector& v)
  : m_data{std::memcpy(std::malloc(v.m_capacity * sizeof(float)), v.m_data, v.m_size)}, m_capacity{v.m_capacity}, m_size{v.m_size}
{
}

FloatVector::FloatVector(FloatVector&& v)
  : m_data{v.m_data}, m_capacity{v.m_capacity}, m_size{v.m_size}
{
	v.m_data = nullptr, v.m_capacity = 0, v.m_size = 0;
}

FloatVector::~FloatVector()
{
	free(m_data);
}

int FloatVector::capacity() const
{
	return m_capacity;
}

int FloatVector::size() const
{
	return m_size;
}

FloatVector::iterator FloatVector::begin()
{
	return m_data;
}

FloatVector::const_iterator FloatVector::begin() const
{
	return m_data;
}

FloatVector::iterator FloatVector::end()
{
	return m_data + m_size;
}

FloatVector::const_iterator FloatVector::end() const
{
	return m_data + m_size;
}

/// SAFETY: This function performs no bounds checking,
/// therefore bounds checking must be performed manually
/// calling when size() == 0 is UB (usually nullptr dereference -> segfault)
float& FloatVector::front()
{
	return m_data[0];
}

/// SAFETY: ditto
const float& FloatVector::front() const
{
	return m_data[0];
}

/// SAFETY: ditto
float& FloatVector::back()
{
	return m_data[m_size - 1];
}

/// SAFETY: ditto
const float& FloatVector::back() const
{
	return m_data[m_size - 1];
}

void FloatVector::allocate(int capacity)
{
}

void FloatVector::resize(int size)
{
}

void FloatVector::push_back(const float& value)
{
}

void FloatVector::pop_back()
{
}

void FloatVector::insert(iterator position, const float& value)
{
}

void FloatVector::insert(iterator position, const float* first, const float* last)
{
}

void FloatVector::erase(iterator position)
{
}

void FloatVector::clear()
{
}

float& FloatVector::operator[](int index)
{
	static float dummy = 0.0f;
	return dummy;
}

const float& FloatVector::operator[](int index) const
{
	static const float dummy = 0.0f;
	return dummy;
}

FloatVector& FloatVector::operator=(const FloatVector& v)
{
	return *this; // TODO
}
