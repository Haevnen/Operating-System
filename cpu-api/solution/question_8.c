/*
Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the
pipe() system call
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

void wait_or_die(int pid) {
    int rc = waitpid(pid, NULL, 0);
    assert(rc > 0);
}

int fork_or_die() {
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

// we simulate a pipe where the first child writes to the pipe and the second
// child reads from the pipe. The parent process waits for both children to finish.
int main(int argc, char *argv[]) {
    // process a
    int fd[2];
    // create a pipe
    assert(pipe(fd) == 0);

    int rc = fork_or_die();
    if (rc == 0) {
        // writer
        printf("writer created\n");
        close(fd[0]); // close the read end of the pipe
        assert(dup2(fd[1], STDOUT_FILENO) != -1);// redirect stdout to pipe
        close(fd[1]); // close the write end of the pipe, since we don't need it anymore
        printf("hello from child 1\n");
        exit(0);
    }
    
    int rc2 = fork_or_die();
    if (rc2 == 0) {
        // reader
        printf("reader created\n");
        close(fd[1]); // the reader doesn't write to the pipe, so close the write end
        assert(dup2(fd[0], STDIN_FILENO) != -1); // redirect stdin to pipe
        close(fd[0]); // close the read end of the pipe, since we don't need it anymore
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            printf("child 2 read: %s", buffer);
        }
        exit(0);
    }
    // we must close the parent's copies of the pipe before waiting, otherwise the reader will never see EOF
    close(fd[0]);
    close(fd[1]);
    
    wait_or_die(rc);
    wait_or_die(rc2);
    return 0;
}
