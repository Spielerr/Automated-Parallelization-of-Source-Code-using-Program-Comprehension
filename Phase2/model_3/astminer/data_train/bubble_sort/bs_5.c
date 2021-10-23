
// void swapper(int *x, int *y)
// {
//     int temp = *x;
//     *x = *y;
//     *y = temp;
// }
int bubbleSort(int arr[], int size)
{
    int i, j;
    for (i = 0; i < size-1; i++)
        for (j = 0; j < size-i-1; j++)
            if (arr[j] > arr[j+1])
                swapper(&arr[j], &arr[j+1]);
}
// void printer(int arr[], int size)
// {
//     for(int i = 0; i< size; i++)
//         printf("%d ", arr[i]);
//     printf("\n");
// }
