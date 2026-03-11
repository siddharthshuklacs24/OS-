
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
};

float average(struct process p[],int n,int choice) {
    int sum=0;

    for(int i=0;i<n;i++) {
        if(choice==1)
            sum+=p[i].tat;
        else
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

        for(int i=0;i<n;i++) {

            if(p[i].at<=time && p[i].rt>0) {

                if(p[i].pr < bestPriority) {
                    bestPriority=p[i].pr;
                    idx=i;
                }
            }
        }

        if(idx==-1) {
            time++;
        }

        else {

            p[idx].rt--;   // run for 1 unit
            time++;

            if(p[idx].rt==0) {
                p[idx].ct=time;
                completed++;
            }
        }
    }
}

void calcTAT(struct process p[],int n) {
    for(int i=0;i<n;i++) {
        p[i].tat=p[i].ct-p[i].at;
    }
}

void calcWT(struct process p[],int n) {
    for(int i=0;i<n;i++) {
        p[i].wt=p[i].tat-p[i].bt;
    }
}

int main() {

    struct process p[5]={
        {1,0,7,3,0,0,0,7},
        {2,2,4,1,0,0,0,4},
        {3,3,6,4,0,0,0,6},
        {4,5,5,2,0,0,0,5},
        {5,6,2,1,0,0,0,2}
    };

    int n=5;

    calcCT(p,n);
    calcTAT(p,n);
    calcWT(p,n);

    printf("PROCESS\tAT\tBT\tPR\tCT\tTAT\tWT\n\n");

    for(int i=0;i<n;i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].pr,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", average(p,n,1));
    printf("\nAverage Waiting Time = %.2f\n", average(p,n,2));

}