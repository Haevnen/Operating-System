/*
Write a program that calls fork(). Before calling fork(), have the
main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process?
What happens to the variable when both the child and parent change
the value of x?
*/

#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>

void wait_or_die() {
    int rc = wait(NULL);
    assert(rc > 0);
}

int fork_or_die() {
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

int main(int argc, char *argv[]) {
    int fp = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    assert(fp >= 0);
    const char *msg = "from parent\n";
    write(fp, msg, strlen(msg));
    // process a
    if (fork_or_die() == 0) {
        sleep(2);
        // process b
        if (fork_or_die() == 0) {
            sleep(1);
            const char *msg = "from child\n";
            write(fp, msg, strlen(msg));
            // process c
            exit(0);
        }
    }
    wait_or_die();
    close(fp);
    return 0;
}
