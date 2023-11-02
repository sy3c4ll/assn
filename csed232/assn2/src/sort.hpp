#ifndef SORT_HPP
#define SORT_HPP

namespace sort {
    template <typename T>
    void swap(T& a, T& b) {
        T tmp = a;
        a = b;
        b = a;
    }
    template <typename T>
    void insertion_sort(T* begin, T* end, bool (*cmp)(T const&, T const&) = T::operator<) {
        for (T *i = begin; i < end; ++i)
            for (T *j = i; j > begin && cmp(*j, *(j - 1)); --j)
                swap(*j, *(j - 1));
    }
}

#endif // ifndef SORT_HPP