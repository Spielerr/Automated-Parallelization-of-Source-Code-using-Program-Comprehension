#include <stdio.h>
#include <stdlib.h>

// Expansion of e^x

//e^x = 1 + x + (x^2)/2! + (x^3)/3! + (x^4)/4! + .....

//Write a program to individually calculate the terms and calculate till the n = 4th term

int sum(int a, int b)
{
    return a + b;
}

int multiply(int a, int b)
{
    return a * b;
}

float divide(int a, int b)
{
    return (float)(a)/b;

}

//calculates a to the power of x
int pow(int a, int x)
{
    int ans = 1;
    for(int i = 1; i<=x; ++i)
    {
        ans = ans*(a);
    }

    return ans;
}

int factorial(int n)
{
    int fact = 1;
    for(int i = 2; i<=n; ++i)
    {
        fact = fact*i;
    }

    return fact;
}

int main()
{
    // int a = sum(1,2);
    // int b = multiply(2,3);
    // float c = divide(5,2);

    // int d = pow(4,3);
    // int e = factorial(5);

    // printf("%d %d %f %d %d",a,b,c,d,e);

    // int *x = (int*)malloc(sizeof(int));
    // *x = 34;

    // int *n1 = (int*)malloc(sizeof(int));
    // *n1 = 2;

    // int *n2 = (int*)malloc(sizeof(int));
    // *n2 = 3;

    // int *n3 = (int*)malloc(sizeof(int));
    // *n3 = 4;

    int x = 34;
    int n1 = 2;
    int n2 = 3;
    int n3 = 4;
	

    float ans = 0;

    float term1 = 1.0f;
    float term2 = x;

    ans = term1 + term2;
	
    int part1_3 = pow(x,n1);
    int part2_3 = factorial(n1);
    float term3 = part1_3/part2_3;

    // int part1_4 = pow(x,n2);
    // int part2_4 = factorial(n2);
    // float term4 = part1_4/part2_4;

    // ans = ans + term3;
    // ans = ans + term4;

    // int part1_5 = pow(x,n3);
    // int part2_5 = factorial(n3);
    // float term5 = part1_5 / part2_5;

    // ans = ans + term5;

    // printf("The expansion of the series e to the power of x for x = 34, approximated to the 4th term is %f", ans);
	
}