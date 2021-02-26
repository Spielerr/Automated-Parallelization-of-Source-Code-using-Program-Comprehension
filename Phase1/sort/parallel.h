#include <omp.h>

#include <vector>
#if 0
template <typename T>
void swap(T& first, T& second) {
    T temp = first;
    first = second;
    second = temp;
}

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
template <typename T>
std::vector<T> vectorise(T array) {
    std::vector<T> v(std::begin(array), std::end(array));
    return v;
}

template <typename T>
void deVectorise(std::vector<T> v, T array) {
    // convert vector to type T in parallel
    // need to do based on type of T, like array or list etc.
}
template <typename ptr_t, typename T>
int partition(ptr_t array, int p, int r) {}

template <typename ptr_t>
void quicksort(ptr_t array, int p, int r) {
    int div;
    if (p < r) {
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