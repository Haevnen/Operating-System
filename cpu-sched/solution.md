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