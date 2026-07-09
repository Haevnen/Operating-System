**1.Run ./fork.py -s 10 and see which actions are taken. Can you predict what the process tree looks like at each step? Use the -c flag to check your answers. Try some different random seeds (-s) or add more actions (-a) to get the hang of it.**
- Just one level of parent-child relationship

```shell
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: c EXITS
                               a
                               └── b
Action: a forks d
                               a
                               ├── b
                               └── d
Action: a forks e
                               a
                               ├── b
                               ├── d
                               └── e
```

**2.One control the simulator gives you is the fork_percentage, controlled by the -f flag. The higher it is, the more likely the next action is a fork; the lower it is, the more likely the action is an exit.Run the simulator with a large number of actions (e.g., -a 100) and vary the fork_percentage from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percentage changes? Check your answer with -c.**

- The higher the `fork_percentage`, the more likely the next action is to be a fork.
- With a `fork_percentage` of 10%, the process tree is relatively shallow.
- In contrast, with a `fork_percentage` of 90%, the process tree contains many more forks, resulting in a deeper and more highly nested process hierarchy.

**3.Tell which actions were taken with this process tree**

```shell
                           Process Tree:
                               a

Action?
                               a
                               └── b
Action?
                               a
Action?
                               a
                               └── c
Action?
                               a
                               └── c
                                   └── d
Action?
                               a
                               └── c
                                   └── d
                                       └── e
```

- a fork b -> b exit -> a fork c-> c fork d -> d fork e

**4. Tell what happens to its children in the process tree when a child exits. E.g., ./fork.py -A a+b,b+c,c+d,c+e,c-**
- Its children become orphaned processes. And orphaned processes are re-parented to the root process
- When -R flag (`local_reparent`) is enabled, orphaned processes are re-parented to local parent (b in this scenario)

```shell
# without -R
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               ├── b
                               ├── d
                               └── e
```

```shell
# with -R
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               └── b
                                   ├── d
                                   └── e
```