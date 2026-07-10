/*
Write a program that creates a child process, and then in the child
closes standard output (STDOUT_FILENO). What happens if the child
calls printf() to print some output after closing the descriptor?
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

void wait_or_die(pid_t pid) {
    int rc = waitpid(pid, NULL, 0);
    assert(rc > 0);
}

int fork_or_die() {
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

int main(int argc, char *argv[]) {
    // process a
    int rc = fork_or_die();
    if (rc == 0) {
        sleep(2);
        close(STDOUT_FILENO);
        printf("from child\n");
        // process b
        exit(0);
    } else {
        wait_or_die(rc);
        printf("from parent\n");
    }
    return 0;
}
