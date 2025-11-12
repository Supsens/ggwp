
#include <stdio.h>
#include <limits.h> // For INT_MAX

#define MAX_BLOCKS 25
#define MAX_PROCESSES 25

int main() {
    int block_size[MAX_BLOCKS], process_size[MAX_PROCESSES];
    int allocation[MAX_PROCESSES];
    int num_blocks, num_processes;

    // Initialize allocation array
    for (int i = 0; i < MAX_PROCESSES; i++) {
        allocation[i] = -1; // -1 means not allocated
    }

    // --- Get User Input ---
    printf("--- Best Fit Allocation ---\n");
    printf("Enter number of memory blocks: ");
    scanf("%d", &num_blocks);
    printf("Enter size of each block:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("Block %d: ", i);
        scanf("%d", &block_size[i]);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter size of each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        scanf("%d", &process_size[i]);
    }
    for (int i = 0; i < num_processes; i++) {
        int best_fit_index = -1;
        int min_diff = INT_MAX; 
        for (int j = 0; j < num_blocks; j++) {
            if (block_size[j] >= process_size[i]) {
                int diff = block_size[j] - process_size[i];
                if (diff < min_diff) {
                    min_diff = diff;
                    best_fit_index = j;
                }
            }
        }
        if (best_fit_index != -1) {
            allocation[i] = best_fit_index;
            block_size[best_fit_index] -= process_size[i];
        }
    }

    // --- Display Results ---
    printf("\n--- Best Fit Allocation Results ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t\t%d\t\t", i, process_size[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i]);
        } else {
            printf("Not Allocated\n");
        }
    }

    return 0;
}
