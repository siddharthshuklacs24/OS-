#include <stdio.h>

struct process {
    int pid;
    int Ci;
    int Ti;
    int Di;  // deadline = Ti - 1

    int remaining;
    int next_arrival;
    int absolute_deadline;
};

// GCD
int gcd(int a, int b) {
    while(b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// LCM
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

// LCM of all Ti
int find_lcm(struct process p[], int n) {
    int result = p[0].Ti;
    for(int i = 1; i < n; i++) {
        result = lcm(result, p[i].Ti);
    }
    return result;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    // input
    for(int i = 0; i < n; i++) {
        printf("Process %d\n", i+1);

        printf("Enter Ci: ");
        scanf("%d", &p[i].Ci);

        printf("Enter Ti: ");
        scanf("%d", &p[i].Ti);

        p[i].pid = i + 1;

        // given condition
        p[i].Di = p[i].Ti - 1;

        // init
        p[i].remaining = 0;
        p[i].next_arrival = 0;
        p[i].absolute_deadline = p[i].Di;
    }

    // utilization (EDF uses Di)
    float U = 0;
    for(int i = 0; i < n; i++) {
        U += (float)p[i].Ci / p[i].Di;
    }

    printf("Utilization: %f\n", U);

    if(U <= 1)
        printf("Feasible\n");
    else
        printf("Not guaranteed feasible\n");

    int LIMIT = find_lcm(p, n);

    printf("\n--- EDF Scheduling (till %d) ---\n", LIMIT);

    // scheduling loop
    for(int time = 0; time < LIMIT; time++) {

        // arrivals
        for(int i = 0; i < n; i++) {
            if(time == p[i].next_arrival) {
                p[i].remaining = p[i].Ci;
                p[i].absolute_deadline = time + p[i].Di;
                p[i].next_arrival += p[i].Ti;
            }
        }

        // select earliest deadline
        int idx = -1;
        int min_deadline = 999999;

        for(int i = 0; i < n; i++) {
            if(p[i].remaining > 0) {
                if(p[i].absolute_deadline < min_deadline) {
                    min_deadline = p[i].absolute_deadline;
                    idx = i;
                }
            }
        }

        // execute
        if(idx != -1) {
            printf("Time %d: P%d\n", time, p[idx].pid);
            p[idx].remaining--;
        } else {
            printf("Time %d: Idle\n", time);
        }
    }

    return 0;
}
