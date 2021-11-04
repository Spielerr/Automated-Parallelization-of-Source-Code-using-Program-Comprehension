#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    struct timeval stop, start;
	gettimeofday(&start, NULL);

    // Pass executable name to run it
    system(argv[1]);

    gettimeofday(&stop, NULL);
	printf("Time Taken %lu\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);

}
