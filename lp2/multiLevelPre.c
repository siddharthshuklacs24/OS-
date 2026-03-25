#include <stdio.h>

struct Process {
    int pid;
    int at;   // Arrival Time
    int bt;   // Burst Time
    int rt;   // Remaining Time
    int ct;   // Completion Time
    int wt;   // Waiting Time
    int tat;  // Turnaround Time
    int type; // 0 = System, 1 = User
    int done; // 0 = not done, 1 = completed
};

int main() {
    int n, i, time = 0, completed = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i+1);
        p[i].pid = i + 1;

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Enter Type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        p[i].rt = p[i].bt; // initialize remaining time
        p[i].done = 0;
    }

    // Preemptive Scheduling
    while(completed < n) {
        int idx = -1;
        int best_at = 1e9;

        // Step 1: System processes (higher priority)
        for(i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].done == 0 && p[i].type == 0 && p[i].rt > 0) {
                if(p[i].at < best_at) {
                    best_at = p[i].at;
                    idx = i;
                }
            }
        }

        // Step 2: User processes if no system process found
        if(idx == -1) {
            best_at = 1e9;
            for(i = 0; i < n; i++) {
                if(p[i].at <= time && p[i].done == 0 && p[i].type == 1 && p[i].rt > 0) {
                    if(p[i].at < best_at) {
                        best_at = p[i].at;
                        idx = i;
                    }
                }
            }
        }

        // Step 3: If no process available
        if(idx == -1) {
            time++;
            continue;
        }

        // Execute for 1 time unit (PREEMPTIVE)
        p[idx].rt--;
        time++;

        // If process completes
        if(p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = 1;
            completed++;
        }
    }

    // Output
    float avg_wt = 0, avg_tat = 0;

    printf("\nPID\tAT\tBT\tType\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%s\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt,
            (p[i].type == 0) ? "SYS" : "USR",
            p[i].ct, p[i].tat, p[i].wt);

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("\nAverage WT = %.2f", avg_wt / n);
    printf("\nAverage TAT = %.2f\n", avg_tat / n);

    return 0;
}