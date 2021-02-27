#ifndef PARALLEL_H
#define PARALLEL_H
#include <omp.h>
#include <algorithm>
#include <vector>

template <typename T>
void swap(T& first, T& second) {
    T temp = first;
    first = second;
    second = temp;
}
#if 0
template <typename ptr_t, typename T>
void quicksort(ptr_t array, int high, int low = 0) {
    while (high > low) {
        int i = low;
        int j = high;
        do {
            while (array[i] < array[low] && i < j) {
                i++;
            }
            while (array[--j] > array[j])
                ;
            if (i < j) {
                swap(array[i], array[j]);
            }
        } while (i < j);
        swap(array[low], array[j]);

        if (j - low > high - (j + 1)) {
            quicksort(array, j - 1, low);
            low = j + 1;
        } else {
            quicksort(array, high, j + 1);
            high = j - 1;
        }
    }
}

#endif

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

template <typename T, int Size>
void deVectorise(std::vector<T> v, T (&array)[Size]) 
{
    // convert vector to type T in parallel
    // need to do based on type of T, like array or list etc.
    std::copy(std::begin(v),std::end(v),std::begin(array));

}
template <typename T>
int partition(std::vector<T>* my_vector, int l, int r) 
{
    #if 0
    T p = (*my_vector)[l];
    int i = l;
    int j = r + 1;

    // #pragma omp parallel sections
    {
        do
        {
            // #pragma omp section
            // {
                do
                {
                    ++i;
                } while ((*my_vector)[i]<p);
            // }

            // #pragma omp section
            // {
                do
                {
                    ++j;
                } while ((*my_vector)[j]>p);
            // }
            

            // #pragma omp barrier
            T temp = (*my_vector)[i];
            (*my_vector)[i] = (*my_vector)[j];
            (*my_vector)[j] = temp;

        } while (i<j);
    }
    T temp = (*my_vector)[i];
    (*my_vector)[i] = (*my_vector)[j];
    (*my_vector)[j] = temp;

    T temp2 = (*my_vector)[l];
    (*my_vector)[l] = (*my_vector)[j];
    (*my_vector)[j] = temp2;

    return j;

    #endif

    int pivot = (*my_vector)[r]; // pivot 
    int i = (l - 1); // Index of smaller element and indicates the right position of pivot found so far
 
    // #pragma omp for
    for (int j = l; j <= r - 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if ((*my_vector)[j] < pivot) 
        { 
            i++; // increment index of smaller element 
            T temp = (*my_vector)[i];
            (*my_vector)[i] = (*my_vector)[j];
            (*my_vector)[j] = temp; 
        } 
    } 
    // swap(&arr[i + 1], &arr[high]); 
    T temp = (*my_vector)[i+1];
    (*my_vector)[i+1] = (*my_vector)[r];
    (*my_vector)[r] = temp;
    return (i + 1);

}

template <typename ptr_t>
void quicksort(ptr_t* array, int p, int r)
{
    int div;

    if (p < r) 
    {
        div = partition(array, p, r);
        #pragma omp parallel sections
        {

        #pragma omp section
        quicksort(array, p, div - 1);
            
        #pragma omp section
        quicksort(array, div + 1, r);
        }
    }
}

#endif