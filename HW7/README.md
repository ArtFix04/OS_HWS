# Process Scheduling Simulator

1.  **First Come First Served (FCFS)**
2.  **Shortest Job First (SJF)**

You feed it some processes (with their arrival times and burst times), and it will return all the key stats like waiting time, turnaround time, and response time for both methods. It also draws a basic Gantt chart so you an see the execution order.

## What it Does

  * **Simulates Two Algorithms:**
      * **FCFS**: The simple "first in, first out" method.
      * **SJF (Non-preemptive)**: The "shortest job first" method. It waits for a process to finish, then picks the shortest available job from the waiting queue. If there's a tie, it picks the one that arrived earliest.
  * **Calculates Key Metrics:**
      * Waiting Time (WT)
      * Turnaround Time (TAT)
      * Response Time (RT)
  * **Shows a Comparison:**
      * It prints a simple **Gantt Chart** for each algorithm.
      * It calculates the **average** WT, TAT, and RT, so you can easily see which algorithm performed better for your input.
  * **Handles Idle Time:** It's smart enough to handle cases where the CPU is idle (i.e., no processes have arrived yet).

## How to Run It

You'll need a C compiler (like `gcc`) on a Linux or Unix-like system.

1.  **Compile it:**
    Open your terminal, `cd` to the folder with the code, and run:

    ```bash
    gcc scheduler.c -o scheduler
    ```

2.  **Run it:**

    ```bash
    ./scheduler
    ```

3.  **Enter your data:**
    Just follow the prompts. It will ask for the number of processes, then the arrival and burst time for each one.

## Example Run

Here's what it looks like if you use the sample data.

**Input:**

```
Enter the number of processes: 4
Enter the arrival time and burst time for process 1: 0 8
Enter the arrival time and burst time for process 2: 1 4
Enter the arrival time and burst time for process 3: 2 9
Enter the arrival time and burst time for process 4: 3 5
```

**Output:**

```

=== First Come First Served (FCFS) ===
Gantt Chart: | P1 | P2 | P3 | P4 |
PID	AT	BT	WT	TAT	RT
1	0	8	0	8	0
2	1	4	7	11	7
3	2	9	10	19	10
4	3	5	18	23	18

Average Waiting Time: 8.75
Average Turnaround Time: 15.25
Average Response Time: 8.75

=== Shortest Job First (SJF) ===
Gantt Chart: | P1 | P2 | P4 | P3 |
PID	AT	BT	WT	TAT	RT
1	0	8	0	8	0
2	1	4	7	11	7
4	3	5	9	14	9
3	2	9	15	24	15

Average Waiting Time: 7.75
Average Turnaround Time: 14.25
Average Response Time: 7.75
```
