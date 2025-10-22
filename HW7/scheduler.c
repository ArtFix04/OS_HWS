#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int start_time;
    
    int is_completed;
};

void print_results(struct Process procs[], int n) {
    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               procs[i].pid, procs[i].arrival_time, procs[i].burst_time,
               procs[i].waiting_time, procs[i].turnaround_time, procs[i].response_time);
    }
}

void print_averages(struct Process procs[], int n) {
    float total_wt = 0, total_tat = 0, total_rt = 0;
    for (int i = 0; i < n; i++) {
        total_wt += procs[i].waiting_time;
        total_tat += procs[i].turnaround_time;
        total_rt += procs[i].response_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
    printf("\n");
}

int compare_fcfs(const void* a, const void* b) {
    struct Process* p1 = (struct Process*)a;
    struct Process* p2 = (struct Process*)b;
    return p1->arrival_time - p2->arrival_time;
}

void run_fcfs(struct Process procs[], int n) {
    printf("=== First Come First Served (FCFS) ===\n");
    
    qsort(procs, n, sizeof(struct Process), compare_fcfs);

    int current_time = 0;
    printf("Gantt Chart: |");
    
    for (int i = 0; i < n; i++) {
        if (current_time < procs[i].arrival_time) {
            current_time = procs[i].arrival_time;
        }
        
        procs[i].start_time = current_time;
        procs[i].completion_time = current_time + procs[i].burst_time;
        procs[i].turnaround_time = procs[i].completion_time - procs[i].arrival_time;
        procs[i].waiting_time = procs[i].turnaround_time - procs[i].burst_time;
        procs[i].response_time = procs[i].start_time - procs[i].arrival_time;
        
        current_time = procs[i].completion_time;
        
        printf(" P%d |", procs[i].pid);
    }
    printf("\n");
    
    print_results(procs, n);
    print_averages(procs, n);
}

void run_sjf(struct Process procs[], int n) {
    printf("=== Shortest Job First (SJF) ===\n");
    
    struct Process ordered_results[n];
    int completed_count = 0;
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        procs[i].is_completed = 0;
    }

    printf("Gantt Chart: |");

    while (completed_count < n) {
        int best_job_idx = -1;
        int shortest_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (procs[i].arrival_time <= current_time && !procs[i].is_completed) {
                if (procs[i].burst_time < shortest_burst) {
                    shortest_burst = procs[i].burst_time;
                    best_job_idx = i;
                } else if (procs[i].burst_time == shortest_burst) {
                    if (procs[i].arrival_time < procs[best_job_idx].arrival_time) {
                        best_job_idx = i;
                    }
                }
            }
        }

        if (best_job_idx == -1) {
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!procs[i].is_completed && procs[i].arrival_time < next_arrival) {
                    next_arrival = procs[i].arrival_time;
                }
            }
            current_time = next_arrival;
        } else {
            struct Process* job = &procs[best_job_idx];

            job->start_time = current_time;
            job->completion_time = current_time + job->burst_time;
            job->turnaround_time = job->completion_time - job->arrival_time;
            job->waiting_time = job->turnaround_time - job->burst_time;
            job->response_time = job->start_time - job->arrival_time;
            job->is_completed = 1;

            current_time = job->completion_time;
            
            printf(" P%d |", job->pid);
            
            ordered_results[completed_count] = *job;
            completed_count++;
        }
    }
    printf("\n");
    
    print_results(ordered_results, n);
    print_averages(ordered_results, n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("No processes to schedule.\n");
        return 1;
    }

    struct Process* all_procs = malloc(n * sizeof(struct Process));
    if (all_procs == NULL) {
         printf("Error allocating memory.\n");
         return 1;
    }

    for (int i = 0; i < n; i++) {
        all_procs[i].pid = i + 1;
        printf("Enter the arrival time and burst time for process %d: ", all_procs[i].pid);
        scanf("%d %d", &all_procs[i].arrival_time, &all_procs[i].burst_time);
    }
    
    printf("\n");

    struct Process* procs_for_fcfs = malloc(n * sizeof(struct Process));
    struct Process* procs_for_sjf = malloc(n * sizeof(struct Process));
    
    for(int i = 0; i < n; i++) {
        procs_for_fcfs[i] = all_procs[i];
        procs_for_sjf[i] = all_procs[i];
    }

    run_fcfs(procs_for_fcfs, n);
    run_sjf(procs_for_sjf, n);

    free(all_procs);
    free(procs_for_fcfs);
    free(procs_for_sjf);

    return 0;
}
