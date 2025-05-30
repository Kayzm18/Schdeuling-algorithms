#include <iostream>
#include <limits> // Required for numeric_limits

using namespace std;

const int MAX = 30; // Use const int for constants in C++

int main() {
    // Variables
    int numOfProcess;
    int waitingT[MAX];
    int burstT[MAX];
    int turnaroundT[MAX];
    float averageWT = 0;
    float turnaround = 0;

    // Asking for user input (number of processes)
    cout << "Enter the number of processes: ";
    cin >> numOfProcess;

    // Input validation to prevent buffer overflows
    if (numOfProcess > MAX) {
        cout << "Error: Number of processes exceeds the maximum limit (" << MAX << ")." << endl;
    }

    // Asking for user input (burst time of the processes)
    cout << "Enter the burst time of the processes:\n";
    for (int i = 0; i < numOfProcess; ++i) {
        cout << "Process " << i + 1 << ": ";
        cin >> burstT[i];
    }

    cout << "Process\t Burst Time\t Waiting Time\t Turnaround Time\n";
    for (int i = 0; i < numOfProcess; ++i) {
        waitingT[i] = 0;
        turnaroundT[i] = 0;
        for (int j = 0; j < i; ++j) {
            waitingT[i] += burstT[j];
        }
        turnaroundT[i] = waitingT[i] + burstT[i];
        averageWT += waitingT[i];
        turnaround += turnaroundT[i];

        cout << i + 1 << "\t\t" << burstT[i] << "\t\t" << waitingT[i] << "\t\t" << turnaroundT[i] << "\n";
    }

    averageWT /= numOfProcess;
    turnaround /= numOfProcess;
    cout << "Average waiting time = " << averageWT << "\n";
    cout << "Average turnaround time = " << turnaround << "\n";

    return 0;
}