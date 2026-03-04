#include <stdio.h>

int main() {
    int n, bt[20], wt[20], tat[20], at[20], ct[20], rt[20];
    int i, time = 0, count = 0, min, index;
    float twt = 0.0, ttat = 0.0, awt, att;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];  // Remaining time
    }

    while (count < n) {
        min = 9999;
        index = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                if (rt[i] < min) {
                    min = rt[i];
                    index = i;
                }
            }
        }

        if (index != -1) {
            rt[index]--;   // Execute for 1 unit
            time++;

            if (rt[index] == 0) {
                ct[index] = time;
                tat[index] = ct[index] - at[index];
                wt[index] = tat[index] - bt[index];
                count++;
            }
        } else {
            time++;  // CPU idle
        }
    }

    for (i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
    }

    awt = twt / n;
    att = ttat / n;

    printf("\nPROCESS\tAT\tBT\tCT\tWT\tTAT");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", awt);
    printf("\nAverage Turnaround Time = %.2f\n", att);

    return 0;
}
