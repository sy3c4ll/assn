#include "FloatVector.h"
#include <cstring>

constexpr inline std::size_t _increase_to_fit(std::size_t s)
{
	return s < 5 ? s : s * 2;
}

void FloatVector::prepare_extra(std::size_t extra)
{
	if ((m_size += extra) >= m_capacity)
		allocate(_increase_to_fit(m_size));
}

FloatVector::FloatVector()
	: m_data{nullptr}, m_capacity{0}, m_size{0}
{ }

FloatVector::FloatVector(std::size_t size)
	: m_data{(float*) std::calloc(size, sizeof(float))}, m_capacity{size}, m_size{size}
{ }

FloatVector::FloatVector(std::size_t size, const float& init)
	: m_data{(float*) std::malloc(size * sizeof(float))}, m_capacity{size}, m_size{size}
{
	for (std::size_t i = 0; i < size; ++i)
		m_data[i] = init;
}

FloatVector::FloatVector(std::size_t size, const float* init)
	: m_data{(float*) std::memcpy(std::malloc(size * sizeof(float)), init, size * sizeof(float))}, m_capacity{size}, m_size{size}
{ }

FloatVector::FloatVector(const FloatVector& v)
	: m_data{(float*) std::memcpy(std::malloc(v.m_size * sizeof(float)), v.m_data, v.m_size * sizeof(float))}, m_capacity{v.m_size}, m_size{v.m_size}
{ }

FloatVector::FloatVector(FloatVector&& v)
	: m_data{v.m_data}, m_capacity{v.m_capacity}, m_size{v.m_size}
{
	v.m_data = nullptr, v.m_capacity = 0, v.m_size = 0;
}

FloatVector::~FloatVector()
{
	std::free(m_data);
}

std::size_t FloatVector::capacity() const
{
	return m_capacity;
}

std::size_t FloatVector::size() const
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

float& FloatVector::front()
{
	// SAFETY: This function performs no bounds checking,
	// therefore bounds checking must be performed manually
	// calling when `size() == 0` is UB (usually nullptr dereference -> segfault)
	return m_data[0];
}

const float& FloatVector::front() const
{
	// SAFETY: ditto
	return m_data[0];
}

float& FloatVector::back()
{
	// SAFETY: ditto
	return m_data[m_size - 1];
}

const float& FloatVector::back() const
{
	// SAFETY: ditto
	return m_data[m_size - 1];
}

void FloatVector::allocate(std::size_t capacity)
{
	if (capacity > m_capacity)
		m_data = (float*) std::realloc(m_data, capacity * sizeof(float)),
		m_capacity = capacity;
}

void FloatVector::resize(std::size_t size)
{
	allocate(size);

	if (size > m_size)
		std::memset(m_data + m_size, 0, (size - m_size) * sizeof(float));
	m_size = size;
}

void FloatVector::push_back(const float& value)
{
	prepare_extra(1);

	back() = value;
}

void FloatVector::pop_back()
{
	--m_size;
}

void FloatVector::insert(iterator position, const float& value)
{
	prepare_extra(1);

	for (iterator it = end() - 1; it > position; --it)
		*it = *(it - 1);
	*position = value;
}

void FloatVector::insert(iterator position, const float* first, const float* last)
{
	if (first >= last)
		return;

	std::size_t len = last - first;
	prepare_extra(len);

	float* cpy = nullptr;
	if ((first >= begin() && first < end())
		|| (last >= begin() && last < end()))
	{
		cpy = (float*) std::memcpy(std::malloc(len * sizeof(float)), first, len * sizeof(float));
		first = cpy, last = cpy + len;
	}

	for (iterator it = end() - 1; it >= position + len; --it)
		*it = *(it - len);
	std::memcpy(position, first, len * sizeof(float));

	// `free`ing a `nullptr` is a well-defined no-op
	std::free(cpy);
}

void FloatVector::erase(iterator position)
{
	for (iterator it = position; it < end() - 1; ++it)
		*it = *(it + 1);
	--m_size;
}

void FloatVector::clear()
{
	std::free(m_data);
	m_data = nullptr, m_capacity = 0, m_size = 0;
}

float& FloatVector::operator[](std::size_t index)
{
	// SAFETY: UB on OOB
	return m_data[index];
}

const float& FloatVector::operator[](std::size_t index) const
{
	// SAFETY: ditto
	return m_data[index];
}

bool FloatVector::operator==(const FloatVector& v) const
{
	return m_size == v.m_size && memcmp(m_data, v.m_data, m_size * sizeof(float)) == 0;
}

bool FloatVector::operator!=(const FloatVector& v) const
{
	return !(*this == v);
}

bool FloatVector::operator==(const float* v) const
{
	// SAFETY: This function assumes `v` is of the same size as the vector,
	// meaning using `v` of a different size is UB.
	// Prefer `operator==(const FloatVector& other)` if this cannot be guaranteed
	return memcmp(m_data, v, m_size * sizeof(float)) == 0;
}

bool FloatVector::operator!=(const float* v) const
{
	// SAFETY: ditto
	return !(*this == v);
}

FloatVector& FloatVector::operator=(const FloatVector& v)
{
	m_data = (float*) std::realloc(m_data, v.m_size * sizeof(float));
	std::memcpy(m_data, v.m_data, v.m_size * sizeof(float));
	m_capacity = v.m_size, m_size = v.m_size;

	return *this;
}

FloatVector& FloatVector::operator=(FloatVector&& v)
{
	std::free(m_data);

	m_data = v.m_data, m_capacity = v.m_capacity, m_size = v.m_size;
	v.m_data = nullptr, v.m_capacity = 0, v.m_size = 0;

	return *this;
}