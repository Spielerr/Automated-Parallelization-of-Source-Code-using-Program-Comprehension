
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>


int test(int a)
{
    return a + 4;
}

int abc = 2;


int add(int a, int b)
{
    return a + b + 4;
}



int main(int argc, const char** argv)
{
    int res1;
    int a1 = 3;
    int b1 = 4;
    res1 = add(a1,b1);
    
    
    
    // bind
    // send it to thread
    
    
    // x - > thread to add fn
    // x.wait();
    
    int res2 = res1 + 5;
    
    res1 = res2 + 2;
    
    // for(x : void )
    // {
    //     x.wait();
    // }
    
    
}

		
		
	


