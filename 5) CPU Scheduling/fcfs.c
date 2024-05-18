#include <stdio.h>

void findWaitingTimeFCFS(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0; // waiting time for first process is 0
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

void findTurnAroundTimeFCFS(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAvgTimeFCFS(int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTimeFCFS(processes, n, bt, wt);
    findTurnAroundTimeFCFS(processes, n, bt, wt, tat);
    printf("Processes  Burst time  Waiting time  Turn around time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d ", (i + 1));
        printf("          %d ", bt[i]);
        printf("          %d", wt[i]);
        printf("                 %d\n", tat[i]);
    }
    printf("Average waiting time = %f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %f\n", (float)total_tat / (float)n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processes[n], burst_time[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    findAvgTimeFCFS(processes, n, burst_time);
    return 0;
}
