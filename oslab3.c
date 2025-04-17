#include <stdio.h>
#define MAX 10
typedef struct {
    int pid;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int arrival_time;  
} Process;
Process processes[MAX];
int n; 

void roundRobin(int quantum) {
    int remaining_burst[MAX], time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        remaining_burst[i] = processes[i].burst_time;
    }

    printf("\nRound Robin Scheduling:\n");
    printf("PID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_burst[i] > 0 && processes[i].arrival_time <= time) {
                if (remaining_burst[i] > quantum) {
                    time += quantum;
                    remaining_burst[i] -= quantum;
                } else {
                    time += remaining_burst[i];
                    processes[i].turnaround_time = time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    remaining_burst[i] = 0;
                    completed++;
                }
            }
        }
    }


    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].arrival_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

void nonPreemptivePriorityScheduling() {
    Process temp;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
 
            if (processes[i].arrival_time > processes[j].arrival_time ||
                (processes[i].arrival_time == processes[j].arrival_time && processes[i].priority > processes[j].priority)) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    int time = 0;
    int completed = 0;
    printf("\nPriority Scheduling (Non-Preemptive):\n");
    printf("PID\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurnaround Time\n");

    while (completed < n) {
        int min_priority = 1000; 
        int process_index = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].turnaround_time == 0) {
                if (processes[i].priority < min_priority) {
                    min_priority = processes[i].priority;
                    process_index = i;
                }
            }
        }

        if (process_index == -1) {
            time++;
            continue;
        }

        time += processes[process_index].burst_time;
        processes[process_index].turnaround_time = time - processes[process_index].arrival_time;
        processes[process_index].waiting_time = processes[process_index].turnaround_time - processes[process_index].burst_time;

        completed++;
    }

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].arrival_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

void preemptivePriorityScheduling() {
    int time = 0, completed = 0, min_priority, process_index;
    int remaining_burst[MAX];
    for (int i = 0; i < n; i++) {
        remaining_burst[i] = processes[i].burst_time;  
    }
    int completed_process[MAX] = {0}; 
    
    printf("\nPreemptive Priority Scheduling:\n");
    printf("PID\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurnaround Time\n");

    while (completed < n) {
        min_priority = 1000; 
        process_index = -1;

        for (int i = 0; i < n; i++) {
            if (!completed_process[i] && remaining_burst[i] > 0 && processes[i].arrival_time <= time && processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                process_index = i;
            }
        }

        remaining_burst[process_index]--;
        time++;

        if (remaining_burst[process_index] == 0) {
            completed_process[process_index] = 1;
            completed++;

            processes[process_index].turnaround_time = time - processes[process_index].arrival_time;
            processes[process_index].waiting_time = processes[process_index].turnaround_time - processes[process_index].burst_time;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].arrival_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    int choice, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nEnter burst time, arrival time, and priority for process %d:\n", i + 1);
        printf("Burst time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Priority (lower number means higher priority): ");
        scanf("%d", &processes[i].priority);
    }
    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. Round Robin Scheduling\n");
    printf("2. Priority Scheduling (Non-Preemptive)\n");
    printf("3. Priority Scheduling (Preemptive)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Enter time quantum for Round Robin: ");
        scanf("%d", &quantum);
        roundRobin(quantum);
    } else if (choice == 2) {
        nonPreemptivePriorityScheduling();
    } else if (choice == 3) {
        preemptivePriorityScheduling();
    } else {
        printf("Invalid choice!\n");
    }
    return 0;
}