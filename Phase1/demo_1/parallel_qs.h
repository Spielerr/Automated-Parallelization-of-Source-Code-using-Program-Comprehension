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

    // int p = (*my_vector)[l];
    // int i = l;
    // int j = r + 1;
    // // printf("\nHERE\n");

    //     do
    //     {
    //         // #pragma omp parallel sections/
    //         {

    //             // #pragma omp section
    //             {
    //                 do
    //                 {
    //                     ++i;
    //                 } while ((*my_vector)[i] < p);
    //             }

    //                 // printf("\nHERE %d\n", i);
    //             // #pragma omp section
    //             {
    //                 do
    //                 {
    //                     --j;
    //                 } while ((*my_vector)[j] > p);
    //             }
            
    //         }

    //         // #pragma omp barrier
    //                 // printf("\nHERE %d\n", j);
    //         swap((*my_vector)[i], (*my_vector)[j]);

    //     } while (i < j);
    //         // printf("\nHERE END\n");
    // swap((*my_vector)[i], (*my_vector)[j]);  
    // swap((*my_vector)[l], (*my_vector)[j]);

    // return j;

}

struct Compare { int val; int index; };
#pragma omp declare reduction( maximum : struct Compare : omp_out = omp_in.val > omp_out.val ? omp_in : omp_out )
template <typename ptr_t>
void my_sort(ptr_t& arr, int p, int r)
{
    int div;

    if (p < r) 
    {
        div = partition(arr, p, r);
        #pragma omp parallel sections
        {

        #pragma omp section
        my_sort(arr, p, div - 1);
            
        #pragma omp section
        my_sort(arr, div + 1, r);
        }
    }

}

#endif