// rate monotonic scheduling 
#include<stdio.h>
#include<math.h>

struct tasks {
    int pid;
    int Ci;
    int Ti;
    int remaining;
    int next_arrival;
};

int main() {    
    
    int n;
    printf("enter number of tasks: ");
    scanf("%d",&n);

    struct tasks t[n];

    // input
    for(int i=0;i<n;i++) {
        printf("Task %d\n", i+1);

        printf("enter Ci: ");
        scanf("%d", &t[i].Ci);

        printf("enter Ti: ");
        scanf("%d", &t[i].Ti);

        t[i].pid = i+1;

        // init for step 5
        t[i].remaining = 0;
        t[i].next_arrival = 0;
    }

    // Step 1: CPU utilization
    float u=0;
    for(int i=0;i<n;i++) {
        u += (float)t[i].Ci / t[i].Ti; 
    }
    printf("CPU utilization: %f\n", u);

    // Step 2: RMS bound
    float bound = n * (pow(2, (float)1/n) - 1);
    printf("Bound: %f\n", bound);

    // Step 3
    if(u <= bound) {
        printf("Schedulable using RMS\n");
    } else {
        printf("Not guaranteed schedulable\n");
    }

    // Step 4: sort by Ti
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            if(t[i].Ti > t[j].Ti) {
                struct tasks temp = t[i];
                t[i] = t[j];
                t[j] = temp;
            }
        }
    }

    // Step 5: Scheduling simulation
    int LIMIT = 30;  // simulate till time 30

    printf("\n--- Scheduling ---\n");

    for(int time = 0; time < LIMIT; time++) {

        // check arrivals
        for(int i=0;i<n;i++) {
            if(time == t[i].next_arrival) {
                t[i].remaining = t[i].Ci;
                t[i].next_arrival += t[i].Ti;
            }
        }

        // pick highest priority task (smallest Ti)
        int idx = -1;
        for(int i=0;i<n;i++) {
            if(t[i].remaining > 0) {
                idx = i;
                break;
            }
        }

        // execute
        if(idx != -1) {
            printf("Time %d: Task %d\n", time, t[idx].pid);
            t[idx].remaining--;
        } else {
            printf("Time %d: Idle\n", time);
        }
    }

    return 0;
}
