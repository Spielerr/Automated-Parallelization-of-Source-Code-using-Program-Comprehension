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
