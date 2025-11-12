
#include <stdio.h>
#include <limits.h> // For INT_MAX

#define MAX_FRAMES 10
#define MAX_PAGES 50

int main() {
    int frames[MAX_FRAMES], counter[MAX_FRAMES];
    int page_string[MAX_PAGES];
    int num_frames, num_pages;
    int page_faults = 0;
    int time = 0; // "Time" increments with each page reference

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    printf("Enter number of pages in reference string: ");
    scanf("%d", &num_pages);

    printf("Enter the page reference string (e.g., 7 0 1 2 0...):\n");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &page_string[i]);
    }

    // Initialize frames to -1 (empty) and counters to 0
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }

    printf("\nPage\tFrames\n");
    // Loop through the reference string
    for (int i = 0; i < num_pages; i++) {
        int current_page = page_string[i];
        int found = 0;
        time++; // Increment time for each page reference

        // 1. Check for a HIT
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == current_page) {
                found = 1;
                counter[j] = time; // Update last used time
                break;
            }
        }

        // 2. If it's a FAULT
        if (found == 0) {
            page_faults++;
            int empty_frame = -1;

            // 2a. Check for an empty frame
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    empty_frame = j;
                    break;
                }
            }

            if (empty_frame != -1) {
                // Found an empty frame
                frames[empty_frame] = current_page;
                counter[empty_frame] = time;
            } else {
                // 2b. No empty frames, must replace (find LRU)
                int lru_index = 0;
                int min_time = counter[0];

                for (int j = 1; j < num_frames; j++) {
                    if (counter[j] < min_time) {
                        min_time = counter[j];
                        lru_index = j;
                    }
                }
                // Replace the LRU page
                frames[lru_index] = current_page;
                counter[lru_index] = time;
            }
        }

        // Print current state of frames
        printf("%d\t", current_page);
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults (LRU): %d\n", page_faults);
    return 0;
}
