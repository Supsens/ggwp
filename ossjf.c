
#include <stdio.h>
#include <limits.h> // For INT_MAX

int main() {
    // --- 1. SETUP ---
    int n; // number of processes

    // Arrays for process details
    int pid[20]; // Process ID
    int at[20];  // Arrival Time
    int bt[20];  // Burst Time
    int wt[20];  // Waiting Time
    int tat[20]; // Turnaround Time
    int ct[20];  // Completion Time
    int is_completed[20]; // Flag (0=no, 1=yes)

    int curr_time = 0; // Current time (CPU clock)
    int completed = 0; // Counter for completed processes

    float total_wt = 0;
    float total_tat = 0;

    // --- 2. INPUT ---
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details (Arrival Time and Burst Time):\n");
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1; // Set Process ID

        printf("P%d Arrival Time: ", pid[i]);
        scanf("%d", &at[i]);

        printf("P%d Burst Time:   ", pid[i]);
        scanf("%d", &bt[i]);

        is_completed[i] = 0; // Initialize as not completed
    }

    // --- 3. SCHEDULING LOGIC (NON-PREEMPTIVE) ---
    while (completed != n) {

        int shortest_job_index = -1; // -1 means no job found
        int min_burst = INT_MAX;     // Start with a very large burst time

        // --- Find the shortest job that has arrived and is not complete ---
        for (int i = 0; i < n; i++) {

            // Check if process has arrived and is not finished
            if (at[i] <= curr_time && is_completed[i] == 0) {

                // If this job is shorter than the current minimum
                if (bt[i] < min_burst) {
                    min_burst = bt[i];
                    shortest_job_index = i;
                }
            }
        }

        // --- Process the chosen job ---
        if (shortest_job_index == -1) {
            // No job is ready (CPU is idle), advance time
            curr_time++;
        } else {
            // A job was found, let it run to completion
            int i = shortest_job_index;

            // Advance time by the job's burst time
            curr_time += bt[i];

            // Calculate metrics
            ct[i] = curr_time;
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];

            // Add to totals
            total_wt += wt[i];
            total_tat += tat[i];

            // Mark as complete
            is_completed[i] = 1;
            completed++;
        }
    }

    // --- 4. OUTPUT TABLE ---
    printf("\n--- SJF (Non-Preemptive) Scheduling Results ---\n");
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
