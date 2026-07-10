**1. What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x**
- Set x = 100 in main process and access this variable in child process -> x still equals 100
- Try to update the value of x in child process (x = 200), and access this variable in main process -> x still equals 100
- The reason is the child has its own copy of x, so every change to this copy is
  not reflected in the main process.

[codeQ1](question_1.c)

**2. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?**
- Yes, after `fork()`, both child and parent can access the same file descriptor
  returned by `open()`
- Both fp refer to the same underlying open file description
- If both parent and child write concurrently to the same file description
  - the writes are a race -> order is not guaranteed -> output is unpredictable
[codeQ2](question_2.c)

**3. can you do this without calling wait() in the parent?**
- No, parent and child process runs concurrently, and we can not ensure the running order due to OS scheduler
[codeQ3](question_3.c)

**4. Why do you think there are so many variants of the same basic call?**
- The `exec()` family of functions all perform the same task, they replace the
  current process with a new program - with the same PID. After successful `exec()`, the original
  program no longer exists and execution begins at `main()` of new program.
- They differ only in how arguments are passed (list vs array), whether the
  executable is searched on PATH...
[codeQ4](question_4.c)

**5. What does wait() return? What happens if you use wait() in the child?**
- The PID of the child is returned to the calling process (when it stops or be
  terminate). Otherwise, a value of -1 is returned
- If you call `wait()` in child process. The result is depend on whether the
  child process has any children. If it has no child process -> `wait()` return
  -1 immediately. Otherwise, it is blocked until the child's children exits.

**6. When would waitpid() be useful**
- wait for a specific child only
- useful when your parent has multiple children and you care which one finishes first