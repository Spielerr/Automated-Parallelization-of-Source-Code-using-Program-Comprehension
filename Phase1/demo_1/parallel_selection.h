#ifndef PARALLEL_H
#define PARALLEL_H
#include <omp.h>
#include <algorithm>
#include <vector>
#include <stdio.h>

template <typename T>
void swap(T& first, T& second) {
    T temp = first;
    first = second;
    second = temp;
}


/*
write a container for any data type, write algo for the container in parallel manner(or use stl)
wrap the data in container, use that to parallelise code

why not use stl containers itself?
*/
template <typename T, int Size>
std::vector<T> vectorise(T (&array)[Size]) {
    std::vector<T> v(std::begin(array), std::end(array));
    return v;
}

template <typename ptr_t, typename T>
std::vector<ptr_t> vectorise(ptr_t* array, T size) {
    std::vector<ptr_t> v(array, array + size);
    return v;
}

template <typename T, int Size>
void deVectorise(std::vector<T> v, T (&array)[Size]) 
{
    std::copy(std::begin(v),std::end(v),std::begin(array));

}

template <typename ptr_t>
void deVectorise(std::vector<ptr_t> v, ptr_t* array) 
{
    std::copy(std::begin(v),std::end(v), array);

}

struct Compare { int val; int index; };
#pragma omp declare reduction( maximum : struct Compare : omp_out = omp_in.val > omp_out.val ? omp_in : omp_out )
template <typename ptr_t>
void my_sort(ptr_t* arr, int p, int r)
{
    for (int i = r - 1; i > 0; --i)
    {
        struct Compare max;
        max.val = (*arr)[i];
        max.index = i;

        #pragma omp parallel for reduction( maximum : max )

        for (int j = i - 1; j >= 0; --j)
        {
            if ((*arr)[j] > max.val)
            {
                max.val = (*arr)[j];
                max.index = j;
            }
        }
        int tmp = (*arr)[i];
        (*arr)[i] = max.val;
        (*arr)[max.index] = tmp;
    }

}

#endif