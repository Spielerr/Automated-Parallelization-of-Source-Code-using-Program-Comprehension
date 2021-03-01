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

template <typename T>
int partition(std::vector<T>& my_vector, int l, int r) 
{

    int pivot = my_vector[r];
    int i = (l - 1); 
 
    // #pragma omp for
    for (int j = l; j <= r - 1; j++) 
    { 
         
        if (my_vector[j] < pivot) 
        { 
            i++;  
            T temp = my_vector[i];
            my_vector[i] = my_vector[j];
            my_vector[j] = temp; 
        } 
    }  
    T temp = my_vector[i+1];
    my_vector[i+1] = my_vector[r];
    my_vector[r] = temp;
    return (i + 1);

}

template <typename ptr_t>
void my_sort(ptr_t& arr, int p, int r)
{
    int div;

    if (p < r) 
    {
        div = partition(arr, p, r);
       

       
        my_sort(arr, p, div - 1);
            
        
        my_sort(arr, div + 1, r);
        
    }
}

#endif