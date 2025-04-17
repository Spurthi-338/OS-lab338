#include<stdio.h> 
#include<stdlib.h>

#define MAX 10

typedef struct
{
    int pid;
    int ET;
    int period;
    int deadline;
} Process;

void rateMonotonic(Process P[], int n)
{
    printf("\nRate-Monotonic Scheduling:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (P[i].period > P[j].period)
            {
                Process temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("Process %d executes with period %d\n", P[i].pid, P[i].period);
    }
}

void earliestDeadlineFirst(Process P[], int n)
{
    printf("\nEarliest Deadline First Scheduling:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (P[i].deadline > P[j].deadline)
            {
                Process temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("Process %d executes with deadline %d\n", P[i].pid, P[i].deadline);
    }
}

void proportionalScheduling(Process P[], int n)
{
    printf("\nProportional Scheduling:\n");
    int total_execution = 0;
    for (int i = 0; i < n; i++) total_execution += P[i].ET;
    for (int i = 0; i < n; i++)
    {
        float share = ((float)P[i].ET / total_execution) * 100;
        printf("Process %d gets %.2f%% of CPU time\n", P[i].pid, share);
    }
}

int main()
{
    int n, choice;
    Process P[MAX];
    printf("Enter the number of P: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter Process ID, Execution Time, Period, and Deadline: ");
        scanf("%d %d %d %d", &P[i].pid, &P[i].ET, &P[i].period, &P[i].deadline);
    }
    printf("\nChoose a scheduling algorithm:\n");
    printf("1. Rate-Monotonic Scheduling\n");
    printf("2. Earliest Deadline First Scheduling\n");
    printf("3. Proportional Scheduling\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        rateMonotonic(P, n);
        break;
    case 2:
        earliestDeadlineFirst(P, n);
        break;
    case 3:
        proportionalScheduling(P, n);
        break;
    default:
        printf("Invalid choice!\n");
    }
    return 0;
}