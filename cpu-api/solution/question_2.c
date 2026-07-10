/*
Write a program that opens a file (with the open() system call)
and then calls fork() to create a new process. Can both the child
and parent access the file descriptor returned by open()? What
happens when they are writing to the file concurrently, i.e., at the
same time?
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
        const char *msg = "from child\n";
        write(fp, msg, strlen(msg));
        exit(0);
    }
    wait_or_die();
    close(fp);
    return 0;
}
