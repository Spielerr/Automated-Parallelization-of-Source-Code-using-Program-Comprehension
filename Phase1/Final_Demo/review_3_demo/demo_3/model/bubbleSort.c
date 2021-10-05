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
