#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burstTime[n];
    int processNumber[n]; // Array to store the original process numbers

    for (int i = 0; i < n; i++)
    {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
        processNumber[i] = i + 1; // Assign the process number to the corresponding index
    }

    // Sort burst time and process numbers simultaneously using the Selection Sort algorithm
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (burstTime[j] < burstTime[minIndex])
            {
                minIndex = j;
            }
        }
        // Swap burst times
        int tempBurst = burstTime[minIndex];
        burstTime[minIndex] = burstTime[i];
        burstTime[i] = tempBurst;
        // Swap process numbers
        int tempProcess = processNumber[minIndex];
        processNumber[minIndex] = processNumber[i];
        processNumber[i] = tempProcess;
    }

    int completionTime[n], turnaroundTime[n], waitingTime[n];

    // Calculate completion time, turnaround time, and waiting time
    completionTime[0] = burstTime[0];
    turnaroundTime[0] = completionTime[0];
    waitingTime[0] = 0;

    for (int i = 1; i < n; i++)
    {
        completionTime[i] = completionTime[i - 1] + burstTime[i];
        turnaroundTime[i] = completionTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
    }

    // Calculate average turnaround time and average waiting time
    float avgTurnaroundTime = 0;
    float avgWaitingTime = 0;

    for (int i = 0; i < n; i++)
    {
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }

    avgTurnaroundTime /= n;
    avgWaitingTime /= n;

    // Print the table
    printf("%-10s%-10s%-10s%-10s\n", "Process", "BT", "TAT", "WT");

    for (int i = 0; i < n; i++)
    {
        printf("%-10d%-10d%-10d%-10d\n", processNumber[i], burstTime[i], turnaroundTime[i], waitingTime[i]);
    }

    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);

    return 0;
}
