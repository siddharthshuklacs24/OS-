#include <stdio.h>

int main() {

    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m];
    int avail[m];

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Request Matrix
    printf("\nEnter Request Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    int finish[n];
    int work[m];

    // Initialize work = available
    for(int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    // Initialize finish[]
    for(int i = 0; i < n; i++) {

        int empty = 1;

        for(int j = 0; j < m; j++) {
            if(alloc[i][j] != 0) {
                empty = 0;
                break;
            }
        }

        if(empty)
            finish[i] = 1;
        else
            finish[i] = 0;
    }

    while(1) {

        int found = 0;

        for(int i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(int j = 0; j < m; j++) {

                    if(request[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {

                    for(int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    int deadlock = 0;

    for(int i = 0; i < n; i++) {

        if(finish[i] == 0) {
            deadlock = 1;
            break;
        }
    }

    if(deadlock) {

        printf("\nDeadlock detected among processes:\n");

        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {
                printf("P%d ", i);
            }
        }

        printf("\n");
    }
    else {
        printf("\nNo deadlock detected\n");
    }

    return 0;
}
