void output(int *data, int *arrayLength) 
{
    for (int *pArray = data; pArray - data < *arrayLength; pArray++) {
            printf("%d", *pArray);
            if (data - pArray + *arrayLength > 1) {
                printf("%c", ' ');
            }
        }
}
