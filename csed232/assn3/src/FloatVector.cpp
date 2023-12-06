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

#include "FloatVector.h"
#include <cstring>

/*******************************************************************************
 * The desired allocation amount for a given size.
 * 
 * This function is used to determine the amount of memory to allocate for a
 * given size. The amount of memory allocated is always at least `size` bytes,
 * but may be more depending on the implementation. In other words, this
 * function determines the growing behaviour of the vector.
 * 
 * @param s The size to allocate for.
 * 
 * @return The desired allocation amount.
 * 
 * @note This function is `constexpr` and may be used in constant expressions.
 * @note This function is `inline` and is probably inlined by the compiler.
 ******************************************************************************/
constexpr inline std::size_t _increase_to_fit(std::size_t s)
{
	return s < 5 ? s : s * 2;
}

/*******************************************************************************
 * Prepares extra valid space by allocating more memory if necessary.
 * 
 * This function is used to prepare extra valid space for the vector. If the
 * vector does not have enough capacity to store `extra` more elements, this
 * function allocates more memory to the vector. The amount of memory allocated
 * is determined by `_increase_to_fit`.
 * 
 * Since all bit patterns of a float are valid, this function only allocates and
 * increases m_size if needed currently. This will change when FloatVector is
 * generalised, since some classes may fail to exist as an object entirely with
 * such an assumption.
 * 
 * @param extra The amount of _extra_ space to prepare.
 ******************************************************************************/
void FloatVector::prepare_extra(std::size_t extra)
{
	if ((m_size += extra) >= m_capacity)
		allocate(_increase_to_fit(m_size));
}

/*******************************************************************************
 * Default constructor.
 * 
 * Constructs an empty vector with no memory allocated.
 ******************************************************************************/
FloatVector::FloatVector()
	: m_data{nullptr}, m_capacity{0}, m_size{0}
{ }

/*******************************************************************************
 * Size constructor.
 * 
 * Constructs a vector with `size` elements, each initialised to `0`.
 * 
 * @param size The size of the vector.
 * 
 * @note This function behaves identically to `FloatVector()` if `size == 0`.
 ******************************************************************************/
FloatVector::FloatVector(std::size_t size)
	: m_data{size ? (float*) std::calloc(size, sizeof(float)) : nullptr}, m_capacity{size}, m_size{size}
{ }

/*******************************************************************************
 * Uniform initialisation constructor.
 * 
 * Constructs a vector with `size` elements, each initialised to `init`.
 * 
 * @param size The size of the vector.
 * @param init The value to initialise each element to.
 * 
 * @note This function behaves identically to `FloatVector()` if `size == 0`.
 ******************************************************************************/
FloatVector::FloatVector(std::size_t size, const float& init)
	: m_data{size ? (float*) std::malloc(size * sizeof(float)) : nullptr}, m_capacity{size}, m_size{size}
{
	for (std::size_t i = 0; i < size; ++i)
		m_data[i] = init;
}

/*******************************************************************************
 * Array initialisation constructor.
 * 
 * Constructs a vector with `size` elements, each initialised to the value at
 * the corresponding index in array `init`.
 * 
 * @param size The size of the vector.
 * @param init The array to initialise each element to.
 * 
 * @note This function behaves identically to `FloatVector()` if `size == 0`.
 ******************************************************************************/
FloatVector::FloatVector(std::size_t size, const float* init)
	: m_data{size ? (float*) std::memcpy(std::malloc(size * sizeof(float)), init, size * sizeof(float)) : nullptr}, m_capacity{size}, m_size{size}
{ }

/*******************************************************************************
 * Copy constructor.
 * 
 * Constructs a vector with the same elements as `v`.
 * 
 * @param v The vector to copy.
 * 
 * @note Size is replicated but capacity is not guaranteed to be: this is
 * implementation-defined. Capacity is however guaranteed to be equal to or
 * greater than size.
 ******************************************************************************/
FloatVector::FloatVector(const FloatVector& v)
	: m_data{v.m_size ? (float*) std::memcpy(std::malloc(v.m_size * sizeof(float)), v.m_data, v.m_size * sizeof(float)) : nullptr}, m_capacity{v.m_size}, m_size{v.m_size}
{ }

/*******************************************************************************
 * Move constructor.
 * 
 * Constructs a vector with the same elements as `v`, leaving `v` in a valid but
 * unspecified state.
 * 
 * @param v The vector to move.
 ******************************************************************************/
FloatVector::FloatVector(FloatVector&& v)
	: m_data{v.m_data}, m_capacity{v.m_capacity}, m_size{v.m_size}
{
	v.m_data = nullptr, v.m_capacity = 0, v.m_size = 0;
}

/*******************************************************************************
 * Destructor.
 * 
 * Destroys the vector, freeing all memory allocated by it.
 ******************************************************************************/
FloatVector::~FloatVector()
{
	std::free(m_data);
}

/*******************************************************************************
 * Capacity getter.
 * 
 * @return The capacity of the vector.
 ******************************************************************************/
std::size_t FloatVector::capacity() const
{
	return m_capacity;
}

/*******************************************************************************
 * Size getter.
 * 
 * @return The size of the vector.
 ******************************************************************************/
std::size_t FloatVector::size() const
{
	return m_size;
}

/*******************************************************************************
 * Iterator to the first element getter.
 * 
 * @return An iterator to the first element of the vector.
 * 
 * @warning The return value must not be dereferenced if the vector is empty.
 ******************************************************************************/
FloatVector::iterator FloatVector::begin()
{
	return m_data;
}

/*******************************************************************************
 * Iterator to the first element getter (const overload).
 * 
 * @return A const iterator to the first element of the vector.
 * 
 * @warning The return value must not be dereferenced if the vector is empty.
 ******************************************************************************/
FloatVector::const_iterator FloatVector::begin() const
{
	return m_data;
}

/*******************************************************************************
 * Iterator to the element after the last element getter.
 * 
 * @return An iterator to the element after the last element of the vector.
 * 
 * @warning The return value must not be dereferenced if the vector is empty.
 ******************************************************************************/
FloatVector::iterator FloatVector::end()
{
	return m_data + m_size;
}

/*******************************************************************************
 * Iterator to the element after the last element getter (const overload).
 * 
 * @return A const iterator to the element after the last element of the vector.
 * 
 * @warning The return value must not be dereferenced if the vector is empty.
 ******************************************************************************/
FloatVector::const_iterator FloatVector::end() const
{
	return m_data + m_size;
}

/*******************************************************************************
 * First element getter.
 * 
 * @return A reference to the first element of the vector.
 * 
 * @warning For an empty container, the behaviour is undefined.
 ******************************************************************************/
float& FloatVector::front()
{
	// SAFETY: This function performs no bounds checking,
	// therefore bounds checking must be performed manually
	// calling when `size() == 0` is UB (usually nullptr dereference -> segfault)
	return m_data[0];
}

/*******************************************************************************
 * First element getter (const overload).
 * 
 * @return A const reference to the first element of the vector.
 * 
 * @warning For an empty container, the behaviour is undefined.
 ******************************************************************************/
const float& FloatVector::front() const
{
	// SAFETY: ditto
	return m_data[0];
}

/*******************************************************************************
 * Last element getter.
 * 
 * @return A reference to the last element of the vector.
 * 
 * @warning For an empty container, the behaviour is undefined.
 ******************************************************************************/
float& FloatVector::back()
{
	// SAFETY: ditto
	return m_data[m_size - 1];
}

/*******************************************************************************
 * Last element getter (const overload).
 * 
 * @return A const reference to the last element of the vector.
 * 
 * @warning For an empty container, the behaviour is undefined.
 ******************************************************************************/
const float& FloatVector::back() const
{
	// SAFETY: ditto
	return m_data[m_size - 1];
}

/*******************************************************************************
 * Allocates memory for the vector.
 * 
 * This function allocates memory for the vector. If the vector already has
 * enough capacity to store `capacity` elements, this function does nothing.
 * Otherwise, this function calls `std::realloc` and lets it do its magic.
 * 
 * @param capacity The capacity to allocate for.
 * 
 * @note This function uses `std::realloc`, the root of all C-C++-interop
 * memory-related UBs and general evil in this codebase. I blame Stroustrup.
 ******************************************************************************/
void FloatVector::allocate(std::size_t capacity)
{
	if (capacity > m_capacity)
		m_data = (float*) std::realloc(m_data, capacity * sizeof(float)),
		m_capacity = capacity;
}

/*******************************************************************************
 * Resizes the vector.
 * 
 * This function exhibits three distinct behaviours depending on `size`:
 * - If `size < m_size`, the vector is truncated to the first `size` elements.
 * - If `size == m_size`, the vector is left unchanged.
 * - If `size > m_size`, the vector is extended to `size` elements, with the
 * new elements being initialised to `1`. Allocation is performed if necessary.
 * 
 * @param size The size to resize to.
 ******************************************************************************/
void FloatVector::resize(std::size_t size)
{
	allocate(size);

	if (size > m_size)
		std::memset(m_data + m_size, 0, (size - m_size) * sizeof(float));
	m_size = size;
}

/*******************************************************************************
 * Pushes an element to the back of the vector.
 * 
 * This function pushes an element to the back of the vector. If the vector does
 * not have enough capacity to store the new element, this function allocates
 * more memory to the vector. The amount of memory allocated is determined by
 * `_increase_to_fit`.
 * 
 * @param value The value to push.
 * 
 * @note This function may allocate extra memory as determined by
 * `_increase_to_fit`.
 ******************************************************************************/
void FloatVector::push_back(const float& value)
{
	prepare_extra(1);

	back() = value;
}

/*******************************************************************************
 * Pops an element from the back of the vector.
 * 
 * This function removes an element from the back of the vector. The element is
 * _not_ returned.
 * 
 * @warning For an empty container, the behaviour is undefined.
 ******************************************************************************/
void FloatVector::pop_back()
{
	--m_size;
}

/*******************************************************************************
 * Inserts an element with given value at set position.
 * 
 * This function pushes all elements at and beyond `position` one index to the
 * right, then allocates a new element at `position` with `value`. This
 * operation increases the size of the vector by 1, if successful.
 * 
 * @param position The position to insert the element into.
 * @param value The value of the new element.
 * 
 * @note This function may allocate extra memory as determined by
 * `_increase_to_fit`.
 * 
 * @warning The behaviour for a `position` not in `[begin(), end()]` is
 * undefined.
 ******************************************************************************/
void FloatVector::insert(iterator position, const float& value)
{
	prepare_extra(1);

	for (iterator it = end() - 1; it > position; --it)
		*it = *(it - 1);
	*position = value;
}

/*******************************************************************************
 * Inserts an array of floats at set position.
 * 
 * This function makes space for all elements in `[first, last)` at `position`
 * and beyond by pushing the succeeding elements to the right, then copies all
 * elements in `[first, last)` to the newly available space in the vector. This
 * operation increases the size of the vector by the length of the give array,
 * if successful.
 * 
 * @param position The position to insert the array into.
 * @param first A pointer to the beginning of the array.
 * @param last A pointer one past the end of the array.
 * 
 * @note This function is designed to deal with cases where [first, last)
 * overlaps with [begin(), end()] automatically by copying elements prior to
 * moving. However, this incurs additional time and memory overhead.
 * @note This function may allocate extra memory as determined by
 * `_increase_to_fit`.
 * 
 * @warning The behaviour for a `position` not in `[begin(), end()]` is
 * undefined.
 ******************************************************************************/
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

/*******************************************************************************
 * Erases an element at set position.
 * 
 * This function removes the element at `position` by pulling all succeeding
 * elements to the left. This operation decreases the size of the vector by 1,
 * if successful.
 * 
 * @param position The position to erase the element at.
 * 
 * @warning The behaviour for a `position` not in `[begin(), end()]` is
 * undefined.
 ******************************************************************************/
void FloatVector::erase(iterator position)
{
	for (iterator it = position; it < end() - 1; ++it)
		*it = *(it + 1);
	--m_size;
}

/*******************************************************************************
 * Clears the vector.
 * 
 * This function clears the vector, freeing all memory allocated by it.
 * 
 * @note Calling this function on an empty vector is perfectly safe, since a
 * `free` on a `nullptr` is a well-defined no-op.
 ******************************************************************************/
void FloatVector::clear()
{
	std::free(m_data);
	m_data = nullptr, m_capacity = 0, m_size = 0;
}

/*******************************************************************************
 * Subscript operator.
 * 
 * @param index The index of the element to get.
 * 
 * @return A reference to the element at `index`.
 * 
 * @warning The behaviour for an `index` not in `[0, size())` is undefined.
 ******************************************************************************/
float& FloatVector::operator[](std::size_t index)
{
	// SAFETY: UB on OOB
	return m_data[index];
}

/*******************************************************************************
 * Subscript operator (const overload).
 * 
 * @param index The index of the element to get.
 * 
 * @return A const reference to the element at `index`.
 * 
 * @warning The behaviour for an `index` not in `[0, size())` is undefined.
 ******************************************************************************/
const float& FloatVector::operator[](std::size_t index) const
{
	// SAFETY: ditto
	return m_data[index];
}

/*******************************************************************************
 * Equality operator.
 * 
 * This function compares the vector to another vector. Two vectors are equal if
 * they have the same size and contain the same elements in the same order.
 * 
 * @param v The vector to compare to.
 * 
 * @return `true` if the vectors are equal, `false` otherwise.
 ******************************************************************************/
bool FloatVector::operator==(const FloatVector& v) const
{
	return m_size == v.m_size && memcmp(m_data, v.m_data, m_size * sizeof(float)) == 0;
}

/*******************************************************************************
 * Inequality operator.
 * 
 * This function compares the vector to another vector. Two vectors are unequal
 * if they have different sizes or contain different elements.
 * 
 * @param v The vector to compare to.
 * 
 * @return `true` if the vectors are unequal, `false` otherwise.
 * 
 * @note This function uses the equality operator and inverts its result.
 ******************************************************************************/
bool FloatVector::operator!=(const FloatVector& v) const
{
	return !(*this == v);
}

/*******************************************************************************
 * Equality operator.
 * 
 * This function compares the vector to an array of floats. The vector and the
 * array are equal if they have the same size and contain the same elements in
 * the same order.
 * 
 * @param v The array to compare to.
 * 
 * @return `true` if the vector and the array are equal, `false` otherwise.
 * 
 * @warning This function assumes `v` is of the same size as the vector, meaning
 * using `v` of a different size is UB. Prefer `operator==(const FloatVector&
 * other)` if this cannot be guaranteed.
 ******************************************************************************/
bool FloatVector::operator==(const float* v) const
{
	// SAFETY: This function assumes `v` is of the same size as the vector,
	// meaning using `v` of a different size is UB.
	// Prefer `operator==(const FloatVector& other)` if this cannot be guaranteed
	return memcmp(m_data, v, m_size * sizeof(float)) == 0;
}

/*******************************************************************************
 * Inequality operator.
 * 
 * This function compares the vector to an array of floats. The vector and the
 * array are unequal if they have different sizes or contain different elements.
 * 
 * @param v The array to compare to.
 * 
 * @return `true` if the vector and the array are unequal, `false` otherwise.
 * 
 * @note This function uses the equality operator and inverts its result.
 * 
 * @warning This function assumes `v` is of the same size as the vector, meaning
 * using `v` of a different size is UB. Prefer `operator!=(const FloatVector&
 * other)` if this cannot be guaranteed.
 ******************************************************************************/
bool FloatVector::operator!=(const float* v) const
{
	// SAFETY: ditto
	return !(*this == v);
}

/*******************************************************************************
 * Copy assignment operator.
 * 
 * This definition overrides the default copy assignment operator to perform a
 * deep copy on its elements and gain a new, separate ownership of the array.
 * 
 * @param v The vector to copy from.
 * 
 * @return A reference to self.
 * 
 * @note Size is replicated but capacity is not guaranteed to be: this is
 * implementation-defined. Capacity is however guaranteed to be equal to or
 * greater than size.
 ******************************************************************************/
FloatVector& FloatVector::operator=(const FloatVector& v)
{
	m_data = (float*) std::realloc(m_data, v.m_size * sizeof(float));
	std::memcpy(m_data, v.m_data, v.m_size * sizeof(float));
	m_capacity = v.m_size, m_size = v.m_size;

	return *this;
}

/*******************************************************************************
 * Move assignment operator.
 * 
 * This definition overrides the default move assignment operator to gain
 * ownership of the existing array, leaving `v` in a valid but unspecified
 * state. The current vector is destroyed.
 * 
 * @param v The vector to move from.
 * 
 * @return A reference to self.
 ******************************************************************************/
FloatVector& FloatVector::operator=(FloatVector&& v)
{
	std::free(m_data);

	m_data = v.m_data, m_capacity = v.m_capacity, m_size = v.m_size;
	v.m_data = nullptr, v.m_capacity = 0, v.m_size = 0;

	return *this;
}