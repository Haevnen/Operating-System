/*
    Measure the cost of a context switch.
*/
#include <assert.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    /*
        * A context switch occurs when the OS stops one process
        and schedules another.
        
        * Since only the kernel decides when a context switch
        happens, it cannot be measured directly.
        
        * A common technique is to create two processes that
        communicate using two pipes:
        
           P1 ---> pipe1 ---> P2
           P2 ---> pipe2 ---> P1
        
        * Each blocking read forces the scheduler to switch
        between the two processes.
 */

    int fd1[2], fd2[2];
    assert(pipe(fd1) == 0);
    assert(pipe(fd2) == 0);

    const int N = 1000000;
    struct timeval start, end;

    // The main logic
    int rc = fork();
    assert(rc >= 0);

    if (rc == 0) {
        // P2
        // Unused pipe
        close (fd1[1]);
        close (fd2[0]);

        for (int i = 0; i < N; i++) {
            char c;
            read(fd1[0], &c, 1);
            write(fd2[1], &c, 1);
        }
    } else {
        // P1
        close (fd1[0]);
        close (fd2[1]);

        gettimeofday(&start, NULL);
        char c = 'x';
        for (int i = 0; i < N; i++) {
            write(fd1[1], &c, 1);
            read(fd2[0], &c, 1);
        }
        wait(NULL);
        gettimeofday(&end, NULL);
    }
    // End of the main logic

    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);

    double elapsed = 
        (end.tv_sec - start.tv_sec) + 
        (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Total time %.6f seconds\n", elapsed);
    printf("Average time per context switch %.3f ns \n", 
        elapsed * 1000000000 / (2 * N));
    
    return 0;
}