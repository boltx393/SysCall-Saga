#include <stdio.h>

#define MAX_PROCESS 10

struct Process {
    int processID;
    int burstTime;
    int remainingTime;
    int completionTime; 
};

int min(int a, int b) 
{
    return (a < b) ? a : b;
}

int main() 
{
    int quantum, numProcesses;
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[MAX_PROCESS];

    for (int i = 0; i < numProcesses; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].processID = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    int completed = 0;
    int currentTime = 0;

    while (completed < numProcesses) 
    {
        for (int i = 0; i < numProcesses; i++) 
        {
            if (processes[i].remainingTime > 0) 
            {
                int executeTime = min(quantum, processes[i].remainingTime);
                currentTime += executeTime;
                processes[i].remainingTime -= executeTime;


                if (processes[i].remainingTime == 0) 
                {
                    completed++;
                    processes[i].completionTime = currentTime; 
                    // printf("%d \n", processes[i].completionTime); 
                    processes[i].remainingTime = -1; // Mark the process as completed
                }
            }
        }
    }

    float totalTurnaroundTime = 0.0;
    float totalWaitingTime = 0.0;

    printf("\nProcess\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < numProcesses; i++) 
    {
        int turnaroundTime = processes[i].completionTime;
        int waitingTime = turnaroundTime - processes[i].burstTime;

        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;

        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].burstTime, turnaroundTime, waitingTime);
    }

    float avgTurnaroundTime = totalTurnaroundTime / numProcesses;
    float avgWaitingTime = totalWaitingTime / numProcesses;

    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);

    return 0;
}
