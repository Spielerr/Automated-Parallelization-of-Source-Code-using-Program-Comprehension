
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>



int add(int a, int b)
{
    return a + b;
}



int main(int argc, const char** argv)
{
    int res1 = add(1,3);
    
    if(1<2)
    {
        int res2 = add(5,6);
    }
    else if(2==3)
    {
        int res3 = add(3,3);
    }
    else
    {
        int res4 = add(2,4);
    }
    
    for(int i = 0; i<5; ++i)
    {
        int res = add(i,i+1);
    }
    

    

}

		
		
	



