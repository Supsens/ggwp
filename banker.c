#include <stdio.h>
int is_safe(int P, int R, int processes[], int available[], int max[][R], int allocation[][R]) {

    // These are now Variable Length Arrays (VLAs)
    // Their size is determined by the P and R passed to the function.
    int need[P][R];
    int finish[P];
    int work[R];
    int safe_sequence[P];
    int count = 0;

    // Initialize finish array to all 0 (false)
    for(int i = 0; i < P; i++) {
        finish[i] = 0;
    }

    // 1. Calculate the Need matrix
    // Need = Max - Allocation
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // 2. Initialize Work = Available
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    // 3. Find a process to finish
    while (count < P) {
        int found = 0; // Flag to check if a safe process was found
        for (int i = 0; i < P; i++) {
            if (finish[i] == 0) { // If process is not finished
                // Check if Need <= Work
                int j;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j])
                        break; // This process needs more than available
                }

                if (j == R) { // If all needs are met (j looped all resources)
                    // Mark process as finished and add its resources to Work
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    safe_sequence[count++] = i;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            // If no process can be allocated, system is in an unsafe state
            printf("\nSystem is in an UNSAFE state.\n");
            return 0; // Not safe
        }
    }

    // If all processes are finished, the system is safe
    printf("\nSystem is in a SAFE state.\n");
    printf("Safe Sequence: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safe_sequence[i]);
    }
    printf("\n");
    return 1; // Safe
}

int main() {
    int P, R;
    printf("Enter the number of processes: ");
    scanf("%d", &P);
    printf("Enter the number of resource types: ");
    scanf("%d", &R);

    // Declare all arrays now that we have P and R
    int processes[P];
    int available[R];
    int max[P][R];
    int allocation[P][R];

    // Initialize processes array
    for (int i = 0; i < P; i++) {
        processes[i] = i;
    }

    printf("\nEnter the Available resources (one number for each resource type):\n");
    for (int i = 0; i < R; i++) {
        printf("R%d: ", i);
        scanf("%d", &available[i]);
    }

    printf("\nEnter the Maximum resource needs matrix (row by row):\n");
    for (int i = 0; i < P; i++) {
        printf("For process P%d: ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter the Current Allocation matrix (row by row):\n");
    for (int i = 0; i < P; i++) {
        printf("For process P%d: ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Check if the system is safe by passing P and R
    is_safe(P, R, processes, available, max, allocation);

    return 0;
}
