#include <stdio.h>
#include <stdlib.h> // For exit()

#define DISK_SIZE 30
int disk[DISK_SIZE];
void initialize_disk() {
    for (int i = 0; i < DISK_SIZE; i++) {
        disk[i] = 0; // 0 = Free
    }
}
void display_disk_status() {
    printf("\n--- Disk Status ---\n[ ");
    for (int i = 0; i < DISK_SIZE; i++) {
        printf("%d ", disk[i]);
    }
    printf("]\n");
}

void allocate_file() {
    int file_id, length;
    int start_block = -1; // -1 means no block found yet

    printf("Enter a File ID (e.g., 1, 2, 3...): ");
    scanf("%d", &file_id);
    printf("Enter file length (number of blocks): ");
    scanf("%d", &length);

    if (length > DISK_SIZE) {
        printf("Error: File is larger than the entire disk.\n");
        return;
    }

    // Find the first contiguous block of 'length' (First Fit)
    for (int i = 0; i <= DISK_SIZE - length; i++) {
        int is_free = 1; // Assume this spot is free

        // Check 'length' blocks starting from 'i'
        for (int j = 0; j < length; j++) {
            if (disk[i + j] != 0) { // If a block is not free
                is_free = 0; // This spot is no good
                i = i + j;   // Optimization: Skip ahead
                break;
            }
        }

        if (is_free == 1) {
            // Found a free spot!
            start_block = i;
            break;
        }
    }

    // If we found a spot, allocate it
    if (start_block != -1) {
        for (int k = 0; k < length; k++) {
            disk[start_block + k] = file_id;
        }
        printf("Success: File %d allocated from block %d to %d.\n",
               file_id, start_block, start_block + length - 1);
    } else {
        printf("Error: Not enough contiguous free space found for file %d.\n", file_id);
    }
}

// --- Main Menu ---
int main() {
    initialize_disk();
    int choice;

    while (1) {
        printf("\n--- Dynamic Sequential File Allocation ---\n");
        printf("1. Allocate New File\n");
        printf("2. Deallocate File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                allocate_file();
                break;
            case 2:
                display_disk_status();
                break;
            case 4:
                printf("Exiting.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
