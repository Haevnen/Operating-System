/*
 Measure the costs of a system call
*/

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int N = 1000000;
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

    return 0;
}