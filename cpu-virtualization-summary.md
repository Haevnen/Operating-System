# The Problem
- A computer typically has a limited number of physical CPUs, but users want to
  run lot of applications (e.g., web browser, text editor, background services)
  simultaneously.


# Solution
- The OS virtualize the CPU so that each program appears to have its own
  dedicated CPU, allowing multiple programs to run concurrently.

## The Abstraction: The process
- To solve this, OS creates an abstraction called a process. A process is simply
  a running program.
    - State: 
        - OS tracks the state of each process (that will be used in
          context-switching), which includes its memory (address space), CPU
          registers (program counter, general purpose registers ) and open
          files.
    - API:
        - OS provides a set of system calls (API) to manage processes.
        - `fork()` to create a new process
        - `exec()` to run a different program within a process
        - `wait()` to pause until a child process finishes
        - `kill()` to send signals to a process (e.g, SIGINT, SIGTSTP)
        - Example: 
            - `wc p3.c > newfile.txt` : call `fork()` to create a new child
              process, and before calling `exect()`, the shell closes standard
              output and opens the file newfile.txt. By doing so, any output from
              the wc are sent to the file instead of the screen. And finally,
              waits for the command to complete by calling `wait()`

| Feature                | fork    ()                                                                                                      | exec()                                                                                                                |
| ---------------------- | ----------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------- |
| Primary Purpose        | Creates a new process (child) from an existing process (parent) medium.                                     | Runs a completely new program within an existing process medium.                                                      |
| New Process Created?   | Yes. It duplicates the caller to create a child process devtecheduacademy.                                  | No. It replaces the current process with a new one medium+1.                                                          |
| Process ID (PID)       | The child gets a new, unique PID. The parent's PID remains unchanged medium.                                | The PID remains exactly the same, as the process itself doesn't change medium+1.                                      |
| Memory / Address Space | Duplicates the parent's entire memory (code, data, heap, stack) into the child medium.                      | Replaces the current memory space (code, data, heap, stack) with the new program's memory devtecheduacademy.          |
| Return Values          | Returns twice: in the parent it returns the child's PID; in the child it returns 0 medium.                  | Returns nothing on success (because the original program is gone). Returns -1 on failure devtecheduacademy.           |
| Execution Flow         | Both the parent and child processes continue executing the same code from the line after the fork() medium. | The current program stops executing entirely, and the new program begins from its main() function devtecheduacademy.  |
| Common Use Case        | Used by a shell to clone itself before running a user command medium.                                       | Used immediately after a fork() so the child clone can transform into the requested command (like ls or grep) medium. |

## The Mechanism: Limited Direct Execution (LDE)
- OS needs a mechanism to share the CPU efficiently without losing control of
  the system
    - **Direct Execution**: For high performance, OS run program directly on the
      CPU. However, it may raise several problems, for example it could run forever or
      perform malicious actions (like accessing another program's memory)

    - **Limited Control**: 
        - To prevent that problem, hardware provides at least two modes: 
          **User Mode** - where apps run with restricted privileges and **Kernel
          Mode** - where OS runs with full hardware access.
        - When a user app needs to do something privileged, it must execute a
          **system call**, which triggers an `interrupt (trap)` to safely jump
          into Kernel mode. When finished, the OS calls a `return-from-trap` instruction.
        - At the boot time, the kernel initializes the `trap table` - tell the
          hardware what code to run when certain events occurs (`trap handler`)
    
    - **Timer Interrupts**: OS configures a hardware timer to prevent program
      hold the CPU forever (e.g., in an infinite loop). Every few milliseconds,
      the timer generates an interrupt, pausing the running user process and
      return control to the OS.
    
    - **Context Switching**: Save current process's state and load the state of
      a different process

## The Policy: Scheduling
- Once the OS has the mechanism to switch between processes, it needs a policy
  to decide which process to run next. 

| Algorithm                                | What it is                                                                                                                                 | Pros                                                                                                    | Cons                                                                                                                        |
| ---------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------ | ------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------- |
| FIFO / SJF                               | Basic, non-preemptive schedulers that run jobs to completion (`assumption: knows the length of each job`)                                                                             | Simple and straightforward.                                                                             | Suffers from the "convoy effect," where a long job blocks all short jobs behind it (FIFO) and jobs can arrive at any time instead of all all at once                                        |
| STCF (Shortest Time-to-Completion First) | A preemptive version of SJF that interrupts the current job if a new, shorter job arrives. (`assumption: knows the length of each job`)                                                 | Great for optimizing turnaround time.                                                                   | Bad for response time.                                                                                                      |
| Round Robin (RR)                         | The OS runs a job for a tiny time slice (quantum), then switches to the next. (`assumption: knows the length of each job`)                                                             | Provides excellent response time, making it ideal for interactive systems.                              | Terrible for turnaround time.                                                                                               |
| Multi-Level Feedback Queue (MLFQ)        | Uses multiple queues with different priority levels, it observers the execution of a job and prioritizes it accordingly. <ul><li>Rule 1: If Priority(A) > Priority(B), A runs, B doesn't</li><li>Rule 2: If Priority(A) = Priority(B), A & B run in RR of the given queue</li><li>Rule 3: When a job enters the system, it's placed at the highest priority</li><li>Rule 4: Once a job uses up its time allotment at a given level, its priority is reduced</li><li>Rule 5: After some time period S, move all jobs in the system to the topmost queue</li></ul>| The most realistic modern scheduler; it can deliver excellent overall performance for both interactive jobs or long-running CPU-intensive workloads | <ul><li>Long-running computations may spend most of time in low-priority queues</li><li>Complex to tune (number of queues, quantum time, priority boost interval)</li><li>Not perfectly fair (CPU time depends on process behavior rather than a guaranteed allocation</li></ul>  |
| Proportional Share (Lottery)             | Ensure that each job obtain a certain percentage of CPU time (E.g., lottery scheduling, stride scheduling and completely fair scheduler - CFS)                                              | Guarantees fairness among competing processes.                                                          | The scheduler can not infer process important, someone/smth must assign shares