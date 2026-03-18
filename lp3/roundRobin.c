#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int rbt;        // Remaining Burst Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int rt;         // Response Time
    bool first_time;// Flag to check if process is getting CPU for the first time
};

int main() {
    int n, tq;
    float total_tat = 0, total_wt = 0;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    
    // 1. Take Inputs
    for (int i = 0; i < n; i++) {
        printf("Enter PID, Arrival Time, and Burst Time for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].bt);
        p[i].rbt = p[i].bt; 
        p[i].first_time = true; 
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // 2. Sort processes by Arrival Time (Bubble Sort for simplicity)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j+1].at) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    // 3. Initialize Ready Queue
    int queue[1000]; 
    int front = 0, rear = 0;
    
    int current_time = 0;
    int completed = 0;
    int i = 0; // Tracks the next process to arrive

    // Fast-forward time to the first process's arrival if CPU is idle at t=0
    if (p[0].at > current_time) {
        current_time = p[0].at;
    }

    // Enqueue all processes that have arrived at the starting time
    while (i < n && p[i].at <= current_time) {
        queue[rear++] = i;
        i++;
    }

    // 4. Execute Round Robin Simulation
    while (completed < n) {
        // If queue is empty but processes are pending, fast-forward time to next arrival
        if (front == rear) {
            current_time = p[i].at;
            while (i < n && p[i].at <= current_time) {
                queue[rear++] = i;
                i++;
            }
        }

        // Dequeue process
        int idx = queue[front++];

        // Calculate Response Time if getting CPU for the first time
        if (p[idx].first_time) {
            p[idx].rt = current_time - p[idx].at;
            p[idx].first_time = false;
        }

        // Execute process for Time Quantum or Remaining Burst Time, whichever is smaller
        int exec_time = (p[idx].rbt < tq) ? p[idx].rbt : tq;
        current_time += exec_time;
        p[idx].rbt -= exec_time;

        // Enqueue newly arrived processes DURING this execution window
        while (i < n && p[i].at <= current_time) {
            queue[rear++] = i;
            i++;
        }

        // If the current process is not finished, put it back at the end of the queue
        if (p[idx].rbt > 0) {
            queue[rear++] = idx;
        } else {
            // Process is finished: Calculate Completion, Turnaround, and Waiting Times
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            
            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
            completed++;
        }
    }

    // 5. Sort back by PID to print results neatly in their original order
    for (int j = 0; j < n - 1; j++) {
        for (int k = 0; k < n - j - 1; k++) {
            if (p[k].pid > p[k+1].pid) {
                struct Process temp = p[k];
                p[k] = p[k+1];
                p[k+1] = temp;
            }
        }
    }

    // 6. Print the Table
    printf("\n-------------------------------------------------------------------------");
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    printf("-------------------------------------------------------------------------\n");
    for (int j = 0; j < n; j++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[j].pid, p[j].at, p[j].bt, p[j].ct, p[j].tat, p[j].wt, p[j].rt);
    }
    printf("-------------------------------------------------------------------------\n");
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
