#include <stdio.h>
#include <stdlib.h>
double mean(int *a1, int n1) {
    double mean = 0;
    for (int i = 0; i < n1; ++i) {
        mean += a1[i];
    }
    mean /= n1;
    a1[0] = 4;
    return mean;
}

int max(int *a4, int n4) {
    int max = a4[0];
    for (int i = 1; i < n4; ++i) {
        if (a4[i] > max) {
            max = a4[i];
        }
    }

    return max;
}

int min(int *a4, int n4) {
    int min = a4[0];
    for (int i = 1; i < n4; ++i) {
        if (a4[i] < min) {
            min = a4[i];
        }
    }

    return min;
}

#include <omp.h>

int main(int argc, char *argv[]) {
    int array_size = atoi(argv[1]);
    int *array = (int *)malloc(array_size * sizeof(int));

    srand(8);
    for (int i = 0; i < array_size; ++i) {
        array[i] = rand();
    }
    double m1;
    int m2, m3, m4, k;

#pragma omp parallel sections
    {
#pragma omp section
        m1 = mean(array, array_size);

#pragma omp section
        m3 = max(array, array_size);

#pragma omp section
        m4 = min(array, array_size);
    }
}
