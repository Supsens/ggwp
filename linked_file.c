#include <stdio.h>
#include <stdlib.h> // For exit()

#define DISK_SIZE 30   // Let's use a smaller disk for easier viewing
#define FREE     -2    // Free block
#define END_FILE -1    // End of file

// Simulate each disk block
struct Block {
    int file_id; // Which file this block belongs to (0 = no file)
    int next;    // Next block index, -2 = free, -1 = end of file
};

struct Block disk[DISK_SIZE];

// --- Helper Functions ---

// 1. Initialize the disk
void initialize_disk() {
    for (int i = 0; i < DISK_SIZE; i++) {
        disk[i].file_id = 0; // 0 = no file
        disk[i].next = FREE; // -2 = FREE BLOCK
    }
}

// 2. Display the current status of the disk
void display_disk_status() {
    printf("\n--- Disk Status ---\n");
    for (int i = 0; i < DISK_SIZE; i++) {
        printf("Block %2d: ", i);
        if (disk[i].next == FREE) {
            printf("[ FREE ]\n");
        } else {
            printf("[File %d] -> Next: %d\n", disk[i].file_id, disk[i].next);
        }
    }
}

// Find how many free blocks we have
int count_free_blocks() {
    int cnt = 0;
    for (int i = 0; i < DISK_SIZE; i++) {
        if (disk[i].next == FREE) cnt++;
    }
    return cnt;
}

// 3. Create a new file with automatic allocation
void create_new_file() {
    int file_id, start_block, blocks_needed;

    printf("Enter a File ID (e.g., 1, 2, 3...): ");
    scanf("%d", &file_id);

    printf("Enter starting block (0-%d): ", DISK_SIZE - 1);
    scanf("%d", &start_block);

    if (start_block < 0 || start_block >= DISK_SIZE || disk[start_block].next != FREE) {
        printf("Error: Block %d is invalid or already in use.\n", start_block);
        return;
    }

    printf("Enter file size (number of blocks needed): ");
    scanf("%d", &blocks_needed);

    if (blocks_needed <= 0) {
        printf("Error: File size must be > 0.\n");
        return;
    }

    int free_blocks = count_free_blocks();
    if (blocks_needed > free_blocks) {
        printf("Error: Not enough free blocks. Free: %d, Needed: %d\n",
               free_blocks, blocks_needed);
        return;
    }

    // Allocate starting block
    int prev_block = start_block;
    disk[start_block].file_id = file_id;
    disk[start_block].next = END_FILE; // will be updated if more blocks
    blocks_needed--;

    // Automatically find and allocate remaining blocks
    for (int b = 0; b < DISK_SIZE && blocks_needed > 0; b++) {
        if (disk[b].next == FREE && b != start_block) {
            disk[prev_block].next = b;    // link previous to this
            disk[b].file_id = file_id;    // mark file id
            disk[b].next = END_FILE;      // temporarily end of file
            prev_block = b;
            blocks_needed--;
        }
    }

    printf("File %d created. Start block: %d\n", file_id, start_block);
}

// --- Main Menu ---
int main() {
    initialize_disk();
    int choice;

    while (1) {
        printf("\n--- Dynamic Linked File Allocation (Auto) ---\n");
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



#include <stdio.h>
#define MAX 50

struct Block {
    int used;       // 0 = free, 1 = allocated
    int next;       // next block number, -1 = end
};

int main() {
    struct Block disk[MAX];
    int start, len, i, j, count, file[MAX];
    char ch;

    for (i = 0; i < MAX; i++) {
        disk[i].used = 0;
        disk[i].next = -1;
    }

    printf("--- Linked File Allocation Simulation ---\n");

    do {
        printf("\nEnter starting block: ");
        scanf("%d", &start);
        printf("Enter file length: ");
        scanf("%d", &len);

        if (start < 0 || start >= MAX) {
            printf("Invalid starting block!\n");
            continue;
        }
        if (disk[start].used) {
            printf("Block %d already allocated!\n", start);
            continue;
        }

        file[0] = start;
        count = 1;
        for (i = 0; i < MAX && count < len; i++)
            if (i != start && disk[i].used == 0)
                file[count++] = i;

        if (count == len) {
            for (i = 0; i < len - 1; i++) {
                disk[file[i]].used = 1;
                disk[file[i]].next = file[i + 1];
            }
            disk[file[len - 1]].used = 1;
            disk[file[len - 1]].next = -1;

            printf("File allocated successfully.\nStart Block: %d\nBlocks: ", start);
            j = start;
            while (j != -1) {
                printf("%d -> ", j);
                j = disk[j].next;
            }
            printf("END\n");
        } else {
            printf("Allocation failed! Not enough free blocks.\n");
        }

        printf("\nDisk Status (1=Used, 0=Free):\n");
        for (i = 0; i < MAX; i++) {
            printf("%d ", disk[i].used);
            if ((i + 1) % 10 == 0) printf("\n");
        }

        printf("\nAllocate another file? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');

    return 0;
}
