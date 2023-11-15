#ifndef FLOAT_VECTOR_H
#define FLOAT_VECTOR_H

#include <cstdlib>

class FloatVector {
private:
    float* m_data;
    std::size_t m_capacity;
    std::size_t m_size;

public:
    typedef float* iterator;
    typedef const float* const_iterator;

    FloatVector();
    FloatVector(int size);
    FloatVector(int size, const float& init);
    FloatVector(int size, const float* init);
    FloatVector(const FloatVector& v);
    FloatVector(FloatVector&& v);

    ~FloatVector();

    int capacity() const;
    int size() const;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    float& front();
    const float& front() const;
    float& back();
    const float& back() const;

    void allocate(int capacity);

    void resize(int size);

    void push_back(const float& value);

    void pop_back();

    void insert(iterator position, const float& value);
    void insert(iterator position, const float* first, const float* last);

    void erase(iterator position);

    void clear();

    float& operator[](int index);
    const float& operator[](int index) const;
    FloatVector& operator=(const FloatVector& v);
};

#endif

