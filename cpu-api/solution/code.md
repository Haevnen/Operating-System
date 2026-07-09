**1. What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x**
- Set x = 100 in main process and access this variable in child process -> x still equals 100
- Try to update the value of x in child process (x = 200), and access this variable in main process -> x still equals 100
- The reason is the child has its own copy of x, so every change to this copy is
  not reflected in the main process.

