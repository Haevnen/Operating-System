/*
 Measure the costs of a system call
*/

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    // gettimeofday() has microsecond resolution, while modern system calls
    // often take only several hundred nanoseconds.
    // That is why we should repeat the system call many times.
    const int N = 1000000;
    struct timeval start, end;

    gettimeofday(&start, NULL);
    for (int i = 0; i < N; i++ ) {
        read(0, NULL, 0);
    }
    gettimeofday(&end, NULL);

    double elapsed = 
        (end.tv_sec - start.tv_sec) + 
        (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Total time %.6f seconds\n", elapsed);
    printf("Average time per system call %.3f ns \n", 
        elapsed * 1000000000 / N);


    /*
        Calling gettimeofday() also has overhead. So, a common technique
        is to measure and subtract the cost of an empty loop.
    */

    gettimeofday(&start, NULL);
    for (int i = 0; i < N; i++ ) {
        // empty loop
    }
    gettimeofday(&end, NULL);
    double empty_loop_elapsed = 
        (end.tv_sec - start.tv_sec) + 
        (end.tv_usec - start.tv_usec) / 1000000.0;

    gettimeofday(&start, NULL);
    for (int i = 0; i < N; i++ ) {
        read(0, NULL, 0);
    }
    gettimeofday(&end, NULL);
    elapsed = 
        (end.tv_sec - start.tv_sec) + 
        (end.tv_usec - start.tv_usec) / 1000000.0;
    
    printf("Total time %.6f seconds\n", elapsed - empty_loop_elapsed);
    printf("Average time per system call %.3f ns \n", 
        (elapsed - empty_loop_elapsed) * 1000000000 / N);

    return 0;
}