#include <stdio.h>

int main() {
    // --- 1. SETUP ---
    int n, qt; // n = number of processes, qt = quantum time

    // Arrays for process details
    int pid[20]; // Process ID
    int at[20];  // Arrival Time
    int bt[20];  // Burst Time
    int rt[20];  // Remaining Time (copy of bt)
    int wt[20];  // Waiting Time
    int tat[20]; // Turnaround Time

    int curr_time = 0; // Current time (CPU clock)
    int done = 0;      // Counter for completed processes

    float total_wt = 0;
    float total_tat = 0;

    // --- 2. INPUT ---
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details (Arrival Time and Burst Time):\n");
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1; // Set Process ID (e.g., 1, 2, 3...)

        printf("P%d Arrival Time: ", pid[i]);
        scanf("%d", &at[i]);

        printf("P%d Burst Time:   ", pid[i]);
        scanf("%d", &bt[i]);

        rt[i] = bt[i]; // Initialize remaining time
    }

    printf("\nEnter the Time Quantum: ");
    scanf("%d", &qt);

    // --- 3. SCHEDULING LOGIC ---
    while (done != n) {
        int cpu_was_idle = 1; // Flag to check if CPU was idle

        // Iterate through all processes
        for (int i = 0; i < n; i++) {

            // Check if process has arrived and still needs to run
            if (at[i] <= curr_time && rt[i] > 0) {

                cpu_was_idle = 0; // CPU is not idle, it found work

                // --- Case 1: Process runs for a full quantum ---
                if (rt[i] > qt) {
                    curr_time += qt; // Advance time by one quantum
                    rt[i] -= qt;     // Reduce remaining time
                }
                // --- Case 2: Process finishes in this turn ---
                else {
                    curr_time += rt[i]; // Advance time by the remaining time
                    rt[i] = 0;          // Process is finished
                    done++;             // Increment completed process count

                    // Calculate metrics for the completed process
                    tat[i] = curr_time - at[i]; // Turnaround Time
                    wt[i] = tat[i] - bt[i];     // Waiting Time

                    // Add to totals for average calculation
                    total_wt += wt[i];
                    total_tat += tat[i];
                }
            }
        }

        // If no process was ready to run in that loop,
        // it means the CPU was idle. We must advance the time.
        if (cpu_was_idle == 1) {
            curr_time++;
        }
    }

    // --- 4. OUTPUT TABLE ---
    printf("\n--- Round Robin Scheduling Results ---\n");
    printf("========================================================\n");
    printf("| PID | Arrival | Burst | Waiting | Turnaround |\n");
    printf("|-----|---------|-------|---------|------------|\n");

    for (int i = 0; i < n; i++) {
        printf("| %-3d | %-7d | %-5d | %-7d | %-10d |\n",
               pid[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("========================================================\n");

    // Print Averages
    printf("\nAverage Waiting Time:     %.2f\n", total_wt / n);
    printf("Average Turnaround Time:  %.2f\n", total_tat / n);

    return 0;
}
