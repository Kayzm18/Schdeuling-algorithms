#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
};

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    int i;

    for (i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].completionTime = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int currentTime = 0, completed = 0;
    int visited[n];
    for (i = 0; i < n; i++) visited[i] = 0;

    int queue[n * 10], front = 0, rear = 0;

    // Add processes that arrive at time 0
    for (i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= currentTime && !visited[i]) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (front < rear) {
        int index = queue[front++];
        int execTime = (processes[index].remainingTime < quantum) ?
                       processes[index].remainingTime : quantum;
        currentTime += execTime;
        processes[index].remainingTime -= execTime;

        // Add new arrivals
        for (i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (processes[index].remainingTime > 0) {
            queue[rear++] = index; // Requeue
        } else {
            processes[index].completionTime = currentTime;
            completed++;
        }

        if (front == rear && completed < n) {
            for (i = 0; i < n; i++) {
                if (!visited[i]) {
                    currentTime = processes[i].arrivalTime;
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }

    // Output
    float totalTurnaround = 0, totalWaiting = 0;

    printf("\nP\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        int turnaround = processes[i].completionTime - processes[i].arrivalTime;
        int waiting = turnaround - processes[i].burstTime;
        totalTurnaround += turnaround;
        totalWaiting += waiting;

        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               turnaround,
               waiting);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTurnaround / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWaiting / n);

    return 0;
}