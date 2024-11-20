#include <stdio.h>
#include <limits.h>


// Process structure
struct process {
    int PID;
    int arriveTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
};

// First Come First Serve (FCFS) Scheduling
void FCFS(struct process processes[], int n) {
    int currentTime = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    int i, j;

    // Sort processes by arrival time using bubble sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].arriveTime > processes[j + 1].arriveTime) {
                struct process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    printf("\nFirst Come First Serve Scheduling\n");
    printf("\nGantt Chart:\n");

    for (i = 0; i < n; i++) {
        // If there's a gap between processes
        if (currentTime < processes[i].arriveTime) {
            printf("| idle |");
            currentTime = processes[i].arriveTime;
        }

        printf("| P%d ", processes[i].PID);

        // Calculate waiting time
        processes[i].waitingTime = currentTime - processes[i].arriveTime;

        // Update current time
        currentTime += processes[i].burstTime;

        // Calculate turnaround time
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;

        // Update totals
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("|\n\nProcess Details:\n");
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].PID,
               processes[i].arriveTime,
               processes[i].burstTime,
               processes[i].waitingTime,
               processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

// Round Robin (RR) Scheduling
void RR(struct process processes[], int n) {
    int timeQuantum;
    int currentTime = 0;
    int completed = 0;
    int i;

    // Create temporary array to store remaining burst times
    int remainingTime[100];

    for (i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }

    printf("\nRound Robin Scheduling\n");
    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    printf("\nGantt Chart:\n");

    while (completed != n) {
        int flag = 0;

        for (i = 0; i < n; i++) {
            if (remainingTime[i] > 0 && processes[i].arriveTime <= currentTime) {
                flag = 1;

                printf("| P%d ", processes[i].PID);

                if (remainingTime[i] > timeQuantum) {
                    currentTime += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                } else {
                    currentTime += remainingTime[i];
                    processes[i].waitingTime = currentTime - processes[i].arriveTime - processes[i].burstTime;
                    processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
                    remainingTime[i] = 0;
                    completed++;
                }
            }
        }

        if (flag == 0) {
            printf("| idle |");
            currentTime++;
        }
    }

    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("|\n\nProcess Details:\n");
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].PID,
               processes[i].arriveTime,
               processes[i].burstTime,
               processes[i].waitingTime,
               processes[i].turnaroundTime);
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

// Shortest Job First (SJF) Scheduling Function
void SJF(struct process processes[], int n) {
    int currentTime = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    int i, completed = 0;
    int isCompleted[100] = {0};  
    printf("\nShortest Job First (Non-Preemptive) Scheduling\n");
    printf("\nGantt Chart:\n");

    while (completed < n) {
        int idx = -1;
        int minBurstTime = 99999;

        
        for (i = 0; i < n; i++) {
            if (processes[i].arriveTime <= currentTime && !isCompleted[i]) {
                if (processes[i].burstTime < minBurstTime) {
                    minBurstTime = processes[i].burstTime;
                    idx = i;
                }
                else if (processes[i].burstTime == minBurstTime) {
                    
                    if (processes[i].arriveTime < processes[idx].arriveTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            
            printf("| P%d (%d) ", processes[idx].PID, currentTime);

            
            processes[idx].waitingTime = currentTime - processes[idx].arriveTime;
            currentTime += processes[idx].burstTime;
            processes[idx].turnaroundTime = processes[idx].waitingTime + processes[idx].burstTime;

            
            totalWaitingTime += processes[idx].waitingTime;
            totalTurnaroundTime += processes[idx].turnaroundTime;

            
            isCompleted[idx] = 1;
            completed++;
        } else {
            
            printf("| idle (%d) ", currentTime);
            currentTime++;
        }
    }
    printf("|\n");

    
    printf("\nProcess Details:\n");
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].PID,
               processes[i].arriveTime,
               processes[i].burstTime,
               processes[i].waitingTime,
               processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}


// Shortest Remaining Time First (SRTF) Scheduling Function
void SRTF(struct process processes[], int n) {
    int currentTime = 0;
    int completed = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    int i;
    int remainingTime[100];  

    
    for (i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
    }

    printf("\nShortest Remaining Time First (Preemptive) Scheduling\n");
    printf("\nGantt Chart:\n");

    int prev = -1;  
    while (completed < n) {
        int idx = -1;
        int minRemainingTime = 99999;

       
        for (i = 0; i < n; i++) {
            if (processes[i].arriveTime <= currentTime && remainingTime[i] > 0) {
                if (remainingTime[i] < minRemainingTime) {
                    minRemainingTime = remainingTime[i];
                    idx = i;
                }
                else if (remainingTime[i] == minRemainingTime) {
                    
                    if (processes[i].arriveTime < processes[idx].arriveTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            
            if (prev != idx) {
                if (prev != -1) {
                    printf("(%d) ", currentTime);
                }
                printf("| P%d ", processes[idx].PID);
                prev = idx;
            }

            
            remainingTime[idx]--;
            currentTime++;

           
            if (remainingTime[idx] == 0) {
                completed++;
                processes[idx].turnaroundTime = currentTime - processes[idx].arriveTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

                
                totalWaitingTime += processes[idx].waitingTime;
                totalTurnaroundTime += processes[idx].turnaroundTime;
            }
        } else {
            
            if (prev != -1) {
                printf("(%d) ", currentTime);
            }
            printf("| idle ");
            prev = -1;
            currentTime++;
        }
    }
    printf("(%d) |\n", currentTime);

    
    printf("\nProcess Details:\n");
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].PID,
               processes[i].arriveTime,
               processes[i].burstTime,
               processes[i].waitingTime,
               processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}


void pq(struct process processes[], int n) {
    int currentTime = 0;
    int completed = 0;
    int i, j;
    int isComplete[100] = {0};
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    int priority[100];

    printf("\nPriority Queue Scheduling\n");
    printf("\nEnter priority for each process (Lower number = Higher priority):\n");
    for(i = 0; i < n; i++) {
        printf("Priority for Process %d: ", processes[i].PID);
        scanf("%d", &priority[i]);
    }

    printf("\nGantt Chart:\n");

    while(completed != n) {
        int highestPriority = INT_MAX;
        int selectedProcess = -1;

        for(i = 0; i < n; i++) {
            if(processes[i].arriveTime <= currentTime && !isComplete[i]) {
                if(priority[i] < highestPriority) {
                    highestPriority = priority[i];
                    selectedProcess = i;
                } else if(priority[i] == highestPriority && processes[i].arriveTime < processes[selectedProcess].arriveTime) {
                    selectedProcess = i;
                }
            }
        }

        if(selectedProcess == -1) {
            printf("| idle |");
            currentTime++;
            continue;
        }

        printf("| P%d ", processes[selectedProcess].PID);
        processes[selectedProcess].waitingTime = currentTime - processes[selectedProcess].arriveTime;
        currentTime += processes[selectedProcess].burstTime;
        processes[selectedProcess].turnaroundTime = processes[selectedProcess].waitingTime + processes[selectedProcess].burstTime;
        totalWaitingTime += processes[selectedProcess].waitingTime;
        totalTurnaroundTime += processes[selectedProcess].turnaroundTime;
        isComplete[selectedProcess] = 1;
        completed++;
    }

    printf("|\n\nProcess Details:\n");
    printf("PID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
            processes[i].PID,
            processes[i].arriveTime,
            processes[i].burstTime,
            priority[i],
            processes[i].waitingTime,
            processes[i].turnaroundTime
        );
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

// Highest Response Ratio Next (HRRN) scheduling function
void HRRN(struct process processes[], int n) {
    int completed = 0, time = 0;
    float avgTurnAroundTime, avgWaitingTime;
    int countTT = 0, countWT = 0;

    
    for (int i = 0; i < n; i++) {
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].completionTime = 0;
    }

    printf("\nHRRN Scheduling\n");
    printf("\nGantt Chart:\n");

    while (completed < n) {
        float maxRatio = -1.0;
        int highestRatioIndex = -1;

        
        for (int i = 0; i < n; i++) {
            if (processes[i].arriveTime <= time && processes[i].turnaroundTime == 0) {
                int waitingTime = time - processes[i].arriveTime;
                float responseRatio = (float)(waitingTime + processes[i].burstTime) / processes[i].burstTime;

                if (responseRatio > maxRatio) {
                    maxRatio = responseRatio;
                    highestRatioIndex = i;
                }
            }
        }

        if (highestRatioIndex != -1) {
            int i = highestRatioIndex;

            
            printf("| P%d ", processes[i].PID);

            processes[i].completionTime = time + processes[i].burstTime;
            processes[i].waitingTime = time - processes[i].arriveTime;
            time += processes[i].burstTime;
            processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
            completed++;

            
            countTT += processes[i].turnaroundTime;
            countWT += processes[i].waitingTime;
        } else {
            
            printf("| idle ");
            time++;
        }
    }

    printf("|\n\nProcess Details:\n");
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tFinish Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].PID, processes[i].arriveTime, processes[i].burstTime,
               processes[i].waitingTime, processes[i].turnaroundTime, processes[i].completionTime);
    }

    avgTurnAroundTime = (float)countTT / n;
    avgWaitingTime = (float)countWT / n;
    printf("\nAverage Turnaround Time: %.2f", avgTurnAroundTime);
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
}



// Multilevel Feedback Queue (MLFQ) scheduling function
void MLFQ(struct process processes[], int n) {
    int time = 0, completed = 0;
    int quantum[] = {4, 8, 12};  
    int numLevels = sizeof(quantum) / sizeof(quantum[0]);
    int remainingTime[n], queueLevel[n];
    int countTT = 0, countWT = 0;
    float avgTurnAroundTime, avgWaitingTime;

    
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
        queueLevel[i] = 0;  
    }
    printf("\nMultilevel Feedback Queue scheduling\n");
    printf("\nGantt Chart:\n");

    while (completed < n) {
        int executed = 0;

        
        for (int level = 0; level < numLevels; level++) {
            for (int i = 0; i < n; i++) {
                if (processes[i].arriveTime <= time && remainingTime[i] > 0 && queueLevel[i] == level) {
                    printf("| P%d(L%d) ", processes[i].PID, level + 1);  

                    if (remainingTime[i] > quantum[level]) {
                        time += quantum[level];
                        remainingTime[i] -= quantum[level];
                        queueLevel[i]++;  
                    } else {
                        time += remainingTime[i];
                        processes[i].completionTime = time;
                        processes[i].waitingTime = time - processes[i].arriveTime - processes[i].burstTime;
                        processes[i].turnaroundTime = time - processes[i].arriveTime;
                        remainingTime[i] = 0;
                        completed++;
                        countTT += processes[i].turnaroundTime;
                        countWT += processes[i].waitingTime;
                    }
                    executed = 1;
                }
            }
        }

        if (!executed) {
            printf("| idle ");
            time++;  
        }
    }

    printf("|\n");

    avgTurnAroundTime = (float)countTT / n;
    avgWaitingTime = (float)countWT / n;

    printf("\n--- Multilevel Queue with Feedback ---\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: Arrival Time = %d, Burst Time = %d, Waiting Time = %d, Turnaround Time = %d, Completion Time = %d\n",
               processes[i].PID, processes[i].arriveTime, processes[i].burstTime,
               processes[i].waitingTime, processes[i].turnaroundTime, processes[i].completionTime);
    }

    printf("Average Turnaround Time = %.2f\n", avgTurnAroundTime);
    printf("Average Waiting Time = %.2f\n", avgWaitingTime);
}


int main() {
    int temp, i, n;
    int algorithm[7] = {0};

    printf("Select function that you want to simulate:\n");
    printf("[1]  First come first serve\n");
    printf("[2]  Round robin\n");
    printf("[3]  Shortest job first\n");
    printf("[4]  Shortest remaining time first\n");
    printf("[5]  Priority queue\n");
    printf("[6]  Highest response ratio next\n");
    printf("[7]  Multilevel queue with feedback\n");
    printf("[-1] Done\n\n");

    do {
        scanf("%d", &temp);
        if (temp == -1) break;
        if (temp >= 1 && temp <= 7) algorithm[temp - 1]++;
    } while (1);

    printf("How many processes: ");
    scanf("%d", &n);

    struct process processes[n];

    printf("Input process detail: ID, Arrival Time, Burst Time\n");
    for (i = 0; i < n; i++) {
        scanf("%d %d %d", &processes[i].PID, &processes[i].arriveTime, &processes[i].burstTime);
    }

    for (i = 0; i < 7; i++) {
        if (algorithm[i] != 0) {
            switch (i) {
                case 0:
                    FCFS(processes, n);
                    break;
                case 1:
                    RR(processes, n);
                    break;
                case 2:
                    SJF(processes, n);
                    break;
                case 3:
                    SRTF(processes, n);
                    break;
                case 4:
                    pq(processes, n);
                    break;
                case 5:
                    HRRN(processes, n);
                    break;
                case 6:
                    MLFQ(processes, n);
                    break;
                
            }
        }
    }

    return 0;
}

