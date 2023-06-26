#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burstTime[n];
    int priority[n];
    int processNumber[n]; // Array to store the original process numbers

    for (int i = 0; i < n; i++)
    {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burstTime[i]);

        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &priority[i]);

        processNumber[i] = i + 1; // Assign the process number to the corresponding index
    }

    // Sort burst time, priority, and process numbers simultaneously using the Selection Sort algorithm
    for (int i = 0; i < n - 1; i++)
    {
        int highestPriorityIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (priority[j] < priority[highestPriorityIndex])
            {
                highestPriorityIndex = j;
            }
        }
        // Swap burst times
        int tempBurst = burstTime[highestPriorityIndex];
        burstTime[highestPriorityIndex] = burstTime[i];
        burstTime[i] = tempBurst;
        // Swap priorities
        int tempPriority = priority[highestPriorityIndex];
        priority[highestPriorityIndex] = priority[i];
        priority[i] = tempPriority;
        // Swap process numbers
        int tempProcess = processNumber[highestPriorityIndex];
        processNumber[highestPriorityIndex] = processNumber[i];
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
        turnaroundTime[i] = completionTime[i] - burstTime[i];
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
    printf("%-10s%-10s%-10s%-10s%-10s\n", "Process", "BT", "Priority", "TAT", "WT");

    for (int i = 0; i < n; i++)
    {
        printf("%-10d%-10d%-10d%-10d%-10d\n", processNumber[i], burstTime[i], priority[i], turnaroundTime[i], waitingTime[i]);
    }

    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);

    return 0;
}
