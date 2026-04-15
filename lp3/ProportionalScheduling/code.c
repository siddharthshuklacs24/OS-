#include <stdio.h>

#define TIME_QUANTUM 10   // you can change this

struct process {
    int pid;
    int Ci;          // total execution time
    int remaining;
    int weight;
    int completed;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    int total_weight = 0;

    // input
    for(int i = 0; i < n; i++) {
        printf("Process %d\n", i+1);

        printf("Enter Ci: ");
        scanf("%d", &p[i].Ci);

        printf("Enter weight: ");
        scanf("%d", &p[i].weight);

        p[i].pid = i + 1;
        p[i].remaining = p[i].Ci;
        p[i].completed = 0;

        total_weight += p[i].weight;
    }

    int time = 0;
    int completed_count = 0;

    printf("\n--- Proportional Share Scheduling ---\n");

    // Step 4
    while(completed_count < n) {

        // Step 5: loop through all processes
        for(int i = 0; i < n; i++) {

            if(p[i].completed)
                continue;

            // Step 6: ready check (all ready here)
            
            // Step 8: calculate time slice
            int time_slice = (p[i].weight * TIME_QUANTUM) / total_weight;

            if(time_slice == 0) time_slice = 1; // avoid 0 slice

            // Step 9: run process
            printf("Time %d: P%d runs for %d units\n", time, p[i].pid, time_slice);

            // Step 10
            p[i].remaining -= time_slice;
            time += time_slice;

            // Step 11–12
            if(p[i].remaining <= 0) {
                printf("P%d completed at time %d\n", p[i].pid, time);

                p[i].completed = 1;
                completed_count++;

                // Step 13
                total_weight -= p[i].weight;
            }
        }
    }

    return 0;
}
