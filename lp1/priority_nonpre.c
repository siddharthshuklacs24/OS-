#include<stdio.h>

struct process{
    int pid;
    int at;
    int bt;
    int pr;
    int ct;
    int tat;
    int wt;
    int rt;
    int done;
};

float average(struct process p[],int n,int choice) {
    int sum=0;

    for(int i=0;i<n;i++) {
        if(choice==1)
            sum+=p[i].tat;
        else if(choice==2)
            sum+=p[i].wt;
    }

    return (float)sum/n;
}

void calcCT(struct process p[],int n) {

    int completed=0;
    int time=0;

    while(completed<n) {

        int idx=-1;
        int bestPriority=999;
        //running a loop to select the process arrived with highest priority
        for(int i=0;i<n;i++) {

            if(p[i].at<=time && p[i].done==0) {

                if(p[i].pr < bestPriority) {
                    bestPriority=p[i].pr;
                    idx=i;
                }

            }
        }

        // CPU idle
        if(idx==-1) {
            time++;
        }
        //logic for calculating ct for selected highest priority arrived process
        else {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].done = 1;
            completed++;
        }
    }
}

void calcTAT(struct process p[],int n) {
    for(int i=0;i<n;i++) {
        p[i].tat = p[i].ct - p[i].at;
    }
}

void calcWT(struct process p[],int n) {
    for(int i=0;i<n;i++) {
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].wt;
    }
}

int main() {

    struct process p[5]={
        {1,0,7,3,0,0,0,0,0},
        {2,2,4,1,0,0,0,0,0},
        {3,3,6,4,0,0,0,0,0},
        {4,5,5,2,0,0,0,0,0},
        {5,6,2,1,0,0,0,0,0}
    };

    int n=5;

    calcCT(p,n);
    calcTAT(p,n);
    calcWT(p,n);

    printf("PROCESS\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n\n");

    for(int i=0;i<n;i++) {

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].pr,
               p[i].ct,
               p[i].tat,
               p[i].wt,
               p[i].rt);
    }

    printf("\nAverage Turnaround Time = %.2f", average(p,n,1));
    printf("\nAverage Waiting Time = %.2f\n", average(p,n,2));

}
