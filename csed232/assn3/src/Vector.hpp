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

#ifdef VECTOR_H

#include "Vector.h"
#include <new>
#include <utility>

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
 * Prepares extra valid space by allocating memory and instantiating objects.
 * 
 * This function is used to prepare extra valid space for the vector. If the
 * vector does not have enough capacity to store `extra` more elements, this
 * function allocates more memory to the vector, the amount of which is
 * determined by `_increase_to_fit`.
 * 
 * Since the memory layout of a contiguous chunk allocated by `std::malloc` or
 * `std::realloc` is undefined, this function also instantiates objects in the
 * newly allocated memory. This is done by calling the placement new operator
 * on the newly allocated memory. This is apparently UB and even outright errors
 * on some compilers, however this seems to he only way to instantiate objects
 * in memory allocated by `std::malloc` or `std::realloc`.
 * 
 * @param extra The amount of _extra_ space to prepare.
 ******************************************************************************/
template <typename T>
void Vector<T>::prepare_extra(std::size_t extra)
{
	if (m_size + extra >= m_capacity)
		allocate(_increase_to_fit(m_size + extra));
	resize(m_size + extra);
}

/*******************************************************************************
 * Constructs a vector with no elements.
 * 
 * Constructs an empty vector with no memory allocated.
 ******************************************************************************/
template <typename T>
Vector<T>::Vector()
	: m_data{nullptr}, m_capacity{0}, m_size{0}
{ }

/*******************************************************************************
 * Size constructor.
 * 
 * Constructs a vector with `size` default-inserted elements.
 * 
 * @param size The size of the vector.
 * 
 * @note This constructor behaves identically to `Vector()` if `size == 0`.
 * @note This constructor requires `T` to be default-constructible. A compile
 * error will occur otherwise.
 ******************************************************************************/
template <typename T>
Vector<T>::Vector(std::size_t size)
	: m_data{size ? (T*) std::malloc(size * sizeof(T)) : nullptr}, m_capacity{size}, m_size{size}
{
	for (std::size_t i = 0; i < size; ++i)
		new(m_data + i) T;
}

/*******************************************************************************
 * Uniform constructor.
 * 
 * Constructs a vector with `size` copies of `init`.
 * 
 * @param size The size of the vector.
 * @param init The value to initialize the elements with.
 * 
 * @note This constructor behaves identically to `Vector()` if `size == 0`.
 * @note This constructor requires `T` to be copy-constructible. A compile
 * error will occur otherwise.
 ******************************************************************************/
template <typename T>
Vector<T>::Vector(std::size_t size, const T& init)
	: m_data{size ? (T*) std::malloc(size * sizeof(T)) : nullptr}, m_capacity{size}, m_size{size}
{
	for (std::size_t i = 0; i < size; ++i)
		new(m_data + i) T{init};
}

/*******************************************************************************
 * Array constructor.
 * 
 * Constructs a vector with `size` elements, each initialised to the value at
 * the corresponding index in array `init`.
 * 
 * @param size The size of the vector.
 * @param init The array to initialise each element to.
 * 
 * @note This constructor behaves identically to `Vector()` if `size == 0`.
 * @note This constructor requires `T` to be copy-constructible. A compile
 * error will occur otherwise.
 ******************************************************************************/
template <typename T>
Vector<T>::Vector(std::size_t size, const T* init)
	: m_data{size ? (T*) std::malloc(size * sizeof(T)) : nullptr}, m_capacity{size}, m_size{size}
{
	for (std::size_t i = 0; i < size; ++i)
		new(m_data + i) T{init[i]};
}

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
 * @note This constructor requires `T` to be copy-constructible. A compile
 * error will occur otherwise.
 ******************************************************************************/
template <typename T>
Vector<T>::Vector(const Vector& v)
	: m_data{v.m_size ? (T*) std::malloc(v.m_size * sizeof(T)) : nullptr}, m_capacity{v.m_size}, m_size{v.m_size}
{
	for (std::size_t i = 0; i < v.m_size; ++i)
		new(m_data + i) T{v.m_data[i]};
}

/*******************************************************************************
 * Move constructor.
 * 
 * Constructs a vector with the same elements as `v`, leaving `v` in a valid but
 * unspecified state.
 * 
 * @param v The vector to move.
 ******************************************************************************/
template <typename T>
Vector<T>::Vector(Vector&& v)
	: m_data{v.m_data}, m_capacity{v.m_capacity}, m_size{v.m_size}
{
	v.m_data = nullptr, v.m_capacity = 0, v.m_size = 0;
}

/*******************************************************************************
 * Destructor.
 * 
 * Destroys the vector, deallocating all memory and calling the destructor of
 * each element.
 ******************************************************************************/
template <typename T>
Vector<T>::~Vector()
{
	for (std::size_t i = 0; i < m_size; ++i)
		m_data[i].~T();
	std::free(m_data);
}

/*******************************************************************************
 * Capacity getter.
 * 
 * @return The capacity of the vector.
 ******************************************************************************/
template <typename T>
std::size_t Vector<T>::capacity() const
{
	return m_capacity;
}

/*******************************************************************************
 * Size getter.
 * 
 * @return The size of the vector.
 ******************************************************************************/
template <typename T>
std::size_t Vector<T>::size() const
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
template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
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
template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const
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
template <typename T>
typename Vector<T>::iterator Vector<T>::end()
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
template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const
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
template <typename T>
T& Vector<T>::front()
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
template <typename T>
const T& Vector<T>::front() const
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
template <typename T>
T& Vector<T>::back()
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
template <typename T>
const T& Vector<T>::back() const
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
template <typename T>
void Vector<T>::allocate(std::size_t capacity)
{
	if (capacity > m_capacity)
		m_data = (T*) std::realloc(m_data, capacity * sizeof(T)),
		m_capacity = capacity;
}

/*******************************************************************************
 * Resizes the vector.
 * 
 * This function exhibits three distinct behaviours depending on `size`:
 * - If `size < m_size`, the vector is truncated and the excess objects are
 * destroyed.
 * - If `size == m_size`, the vector is left unchanged.
 * - If `size > m_size`, the vector is extended to `size` elements, with the
 * new elements being default-constructed. Allocation is performed if necessary.
 * 
 * @param size The size to resize to.
 * 
 * @note This function requires `T` to be default-constructible. A compile
 * error will occur otherwise.
 ******************************************************************************/
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
 * @note This function requires `T` to be copy-constructible. A compile
 * error will occur otherwise.
 ******************************************************************************/
template <typename T>
void Vector<T>::push_back(const T& value)
{
	prepare_extra(1);

	back() = value;
}

/*******************************************************************************
 * Pops an element from the back of the vector.
 * 
 * This function removes an element from the back of the vector. The element is
 * properly destroyed, but _not_ returned.
 * 
 * @warning For an empty container, the behaviour is undefined.
 ******************************************************************************/
template <typename T>
void Vector<T>::pop_back()
{
	resize(m_size - 1);
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
 * @note This function requires `T` to be copy-constructible. A compile
 * error will occur otherwise.
 * 
 * @warning The behaviour for a `position` not in `[begin(), end()]` is
 * undefined.
 ******************************************************************************/
template <typename T>
void Vector<T>::insert(iterator position, const T& value)
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
 * @note This function requires `T` to be copy-constructible. A compile
 * error will occur otherwise.
 * 
 * @warning The behaviour for a `position` not in `[begin(), end()]` is
 * undefined.
 ******************************************************************************/
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

/*******************************************************************************
 * Erases an element at set position.
 * 
 * This function removes the element at `position` by pulling all succeeding
 * elements to the left. The element is properly destroyed. This operation
 * decreases the size of the vector by 1, if successful.
 * 
 * @param position The position to erase the element at.
 * 
 * @warning The behaviour for a `position` not in `[begin(), end()]` is
 * undefined.
 ******************************************************************************/
template <typename T>
void Vector<T>::erase(iterator position)
{
	for (iterator it = position; it < end() - 1; ++it)
		*it = *(it + 1);
	resize(m_size - 1);
}

/*******************************************************************************
 * Clears the vector.
 * 
 * This function clears the vector, destroying all objects and freeing all
 * memory allocated by it.
 * 
 * @note Calling this function on an empty vector is perfectly safe, since a
 * `free` on a `nullptr` is a well-defined no-op.
 ******************************************************************************/
template <typename T>
void Vector<T>::clear()
{
	for (std::size_t i = 0; i < m_size; i++)
		m_data[i].~T();
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
template <typename T>
T& Vector<T>::operator[](std::size_t index)
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
template <typename T>
const T& Vector<T>::operator[](std::size_t index) const
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
 * 
 * @note This function requires `T` to be equality-comparable. A compile
 * error will occur otherwise.
 ******************************************************************************/
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
 * @note This function requires `T` to be equality-comparable. A compile
 * error will occur otherwise.
 ******************************************************************************/
template <typename T>
bool Vector<T>::operator!=(const Vector& v) const
{
	return !(*this == v);
}

/*******************************************************************************
 * Equality operator.
 * 
 * This function compares the vector to an array of Ts. The vector and the array
 * are equal if they have the same size and contain the same elements in the
 * same order.
 * 
 * @param v The array to compare to.
 * 
 * @return `true` if the vector and the array are equal, `false` otherwise.
 * 
 * @note This function requires `T` to be equality-comparable. A compile
 * error will occur otherwise.
 * 
 * @warning This function assumes `v` is of the same size as the vector, meaning
 * using `v` of a different size is UB. Prefer `operator==(const Vector& other)`
 * if this cannot be guaranteed.
 ******************************************************************************/
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

/*******************************************************************************
 * Inequality operator.
 * 
 * This function compares the vector to an array of Ts. The vector and the array
 * are unequal if they have different sizes or contain different elements.
 * 
 * @param v The array to compare to.
 * 
 * @return `true` if the vector and the array are unequal, `false` otherwise.
 * 
 * @note This function uses the equality operator and inverts its result.
 * @note This function requires `T` to be equality-comparable. A compile
 * error will occur otherwise.
 * 
 * @warning This function assumes `v` is of the same size as the vector, meaning
 * using `v` of a different size is UB. Prefer `operator!=(const Vector& other)`
 * if this cannot be guaranteed.
 ******************************************************************************/
template <typename T>
bool Vector<T>::operator!=(const T* v) const
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
 * @note This function requires `T` to be copy-constructible. A compile
 * error will occur otherwise.
 ******************************************************************************/
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v)
{
	resize(v.m_size);
	for (std::size_t i = 0; i < m_size; ++i)
		m_data[i] = v.m_data[i];

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