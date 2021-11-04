
void bubbleSort()
{
    int count;
    printf("Enter the count: \n");
    scanf("%d",&count);
    int numbers[count];
    printf("Enter the numbers: ");

    for(int i=0; i<count; i++)
    {
        scanf("%d",&numbers[i]);
    }

    for(int i=0; i<count-1; i++)
    {
        for(int j=0; j<count-1; j++)
        {
            if(numbers[j]>numbers[j+1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }
        }
    }

    for(int i=0; i<count; i++)
    {
        printf("%d\n",numbers[i]);
    }
}
