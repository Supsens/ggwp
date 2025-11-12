#include <stdio.h>
#include <stdlib.h> // For exit()

#define DISK_SIZE 30 // Let's use a smaller disk for easier viewing

// Simulate each disk block
struct Block {
    int file_id; // Which file this block belongs to
    int next;    // Pointer to the next block index
};

struct Block disk[DISK_SIZE];

// --- Helper Functions ---

// 1. Initialize the disk
void initialize_disk() {
    for (int i = 0; i < DISK_SIZE; i++) {
        disk[i].file_id = 0; // 0 = no file
        disk[i].next = -2;   // -2 = FREE BLOCK
    }
}

// 2. Display the current status of the disk
void display_disk_status() {
    printf("\n--- Disk Status ---\n");
    for (int i = 0; i < DISK_SIZE; i++) {
        printf("Block %2d: ", i);
        if (disk[i].next == -2) {
            printf("[ FREE ]\n");
        } else {
            printf("[File %d] -> Next: %d\n", disk[i].file_id, disk[i].next);
        }
    }
}

void create_new_file() {
    int file_id, start_block, current_block, next_block;

    printf("Enter a File ID (e.g., 1, 2, 3...): ");
    scanf("%d", &file_id);

    printf("Enter a starting block (0-%d): ", DISK_SIZE - 1);
    scanf("%d", &start_block);

    if (start_block < 0 || start_block >= DISK_SIZE || disk[start_block].next != -2) {
        printf("Error: Block %d is invalid or already in use.\n", start_block);
        return;
    }

    // Allocate the starting block
    disk[start_block].file_id = file_id;
    current_block = start_block;

    // Loop to link more blocks
    while (1) {
        printf("  Link to next block (or -1 to end file): ");
        scanf("%d", &next_block);

        if (next_block == -1) {
            disk[current_block].next = -1; // Mark as End of File
            printf("File %d created. Start: %d\n", file_id, start_block);
            break;
        }
        if (next_block < 0 || next_block >= DISK_SIZE || disk[next_block].next != -2) {
            printf("  Error: Block %d is invalid or already in use. Try again.\n", next_block);
            continue; // Ask again
        }
        disk[current_block].next = next_block;
        disk[next_block].file_id = file_id;
        current_block = next_block;
    }
}
// --- Main Menu ---
int main() {
    initialize_disk();
    int choice;
    int start;

    while (1) {
        printf("\n--- Dynamic Linked File Allocation ---\n");
        printf("1. Create New File\n");
        printf("2. Show Disk Status\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_new_file();
                break;
            case 2:
                display_disk_status();
                break;
            case 3:
                printf("Exiting.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
