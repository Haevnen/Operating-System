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
