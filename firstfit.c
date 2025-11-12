#include <stdio.h>

#define MAX_BLOCKS 25
#define MAX_PROCESSES 25

int main() {
    int block_size[MAX_BLOCKS], process_size[MAX_PROCESSES];
    int allocation[MAX_PROCESSES]; // Stores the block number allocated to a process
    int num_blocks, num_processes;

    // Initialize allocation array
    for (int i = 0; i < MAX_PROCESSES; i++) {
        allocation[i] = -1; // -1 means not allocated
    }

    // --- Get User Input ---
    printf("--- First Fit Allocation ---\n");
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

    // --- First Fit Allocation Logic ---
    for (int i = 0; i < num_processes; i++) { // For each process
        for (int j = 0; j < num_blocks; j++) { // Find the first block that fits
            if (block_size[j] >= process_size[i]) {
                // Allocate this block
                allocation[i] = j;
                // Reduce the size of the block
                block_size[j] -= process_size[i];
                // Break from inner loop and move to the next process
                break;
            }
        }
    }

    // --- Display Results ---
    printf("\n--- First Fit Allocation Results ---\n");
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
