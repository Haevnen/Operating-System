**1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.**
- A: 200, B:200, C:200
  - SJF:
    - Response time: (0 + 200 + 400) / 3 = 200
    - Turnaround time: (200 + 400 + 600) / 3 = 400
  - FIFO:
    - Response time: (0 + 200 + 400) / 3 = 200
    - Turnaround time: (200 + 400 + 600) / 3 = 400

```shell
python3 scheduler.py -p SJF -l 200,200,200 -c                                                                                          ✔  at 00:23:47  
ARG policy SJF
ARG jlist 200,200,200

Here is the job list, with the run time of each job: 
  Job 0 ( length = 200.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 200.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
  [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
  [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
```

```shell
python3 scheduler.py -p FIFO -l 200,200,200 -c                                                                                         ✔  at 00:23:59  
ARG policy FIFO
ARG jlist 200,200,200

Here is the job list, with the run time of each job: 
  Job 0 ( length = 200.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 200.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
  [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
  [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
```

**2. Now do the same but with jobs of different lengths: 100, 200, and 300.**
- A: 100, B:200, C:300
  - SJF:
    - Response time: (0 + 100 + 300) / 3 = 133.3
    - Turnaround time: (100 + 300 + 600) / 3 = 333.3
  - FIFO:
    - Response time: (0 + 100 + 300) / 3 = 133
    - Turnaround time: (100 + 300 + 600) / 3 = 333.3
```shell
python3 scheduler.py -p SJF -l 100,200,300 -c                                                                                          ✔  at 00:28:35  
ARG policy SJF
ARG jlist 100,200,300

Here is the job list, with the run time of each job: 
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
  [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
```

```shell
python3 scheduler.py -p FIFO -l 100,200,300 -c                                                                                         ✔  at 00:24:57  
ARG policy FIFO
ARG jlist 100,200,300

Here is the job list, with the run time of each job: 
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
  [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
```

**3. Now do the same, but also with the RR scheduler and a time-slice of 1**
- A: 200, B:200, C:200
  - Round Robin + time-slice = 1:
    - Response time: (0 + 1 + 2) / 3 = 1
    - Turnaround time: (598 + 599 + 600) / 3 = 599

- A: 100, B:200, C:300
  - Round Robin + time-slice = 1:
    - Response time: (0 + 1 + 2) / 3 = 1
    - Turnaround time: (298 + 499 + 600) / 3 = 465.67

**4. For what types of workloads does SJF deliver the same turnaround times as FIFO?**
- SJF delivers the same turnaround times as FIFO when all jobs arrive in
  non-descending order of their CPU burst times. 
  - E.g., 200, 200, 200 or 100, 200, 200, 300

**5. For what types of workloads and quantum lengths (interrupt timer) does SJF deliver the same response times as RR?**
- SJF delivers the same response times as RR when RR's quantum length is large
  enough that no process is preempted and all jobs arrive in non-descending
  order of their CPU burst times.
  - E.g., A:2, B:4, C:6 and quantum length is 10
    - So, the running be like
    ```shell
    0      2      6      12
    |--P1--|--P2--|--P3--|
    ```

**6. What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?**
- In SJF, when the CPU burst lengths of all jobs increase proportionally, the
  response time of later job also increase because they must wait longer for
  earlier jobs to finish.
- The first job's response time remains 0
- Consequently, the average response time increase.

**7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?**
- A larger quantum means fewer context switches. Call A is the quantum length 
    - The first job's response time remains 0
    - The second job must wait for one quantum: A
    - The third job must wait for two quantum: 2 * A
    - ...
    - The last process must wait for N-1 quantum: (N-1) * A
    - So the response time = (0 + A + 2*A + ... + (N-1)*A) / N
- Therefore, as the quantum increases, the response time will increase also
  (every process must wait longer for its first execution)