#include <stdio.h>

int input(int *data, int *arrayLength) 
{
    char c;
    for (int *pArray = data; pArray - data < *arrayLength; pArray++) {
        if ((scanf("%d%c", pArray, &c) == 2) &&  ((c == ' ' &&
           pArray - data < *arrayLength - 1) || c == '\n')) {
        } else {
            return 0;
        }
    }
return 1;
}

void output(int *data, int *arrayLength) 
{
    for (int *pArray = data; pArray - data < *arrayLength; pArray++) {
            printf("%d", *pArray);
            if (data - pArray + *arrayLength > 1) {
                printf("%c", ' ');
            }
        }
}

void bubbleSort(int *data, int *arrayLength) 
{
    for (int i = 0; i < *arrayLength - 1; i++) {
        for (int j = 0; j < *arrayLength - i - 1; j++) {
            if (data[j] > data[j+1]) {
                int tmp = data[j];
                data[j] = data[j+1];
                data[j+1] = tmp;
            }
        }
    }
}

int main() {
    int arrayLength = 10, data[1000000];
    if (input(data, &arrayLength) == 1) {
        bubbleSort(data, &arrayLength);
        output(data, &arrayLength);
    } else {
        printf("n/a");
    }
    return 0;
}
