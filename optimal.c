
#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

// Helper function to predict the future
int find_optimal_page(int frames[], int num_frames, int page_string[], int num_pages, int current_index) {
    int replace_index = -1;
    int furthest_distance = -1;

    for (int i = 0; i < num_frames; i++) {
        int current_frame_page = frames[i];
        int j;
        // Look for this page in the future
        for (j = current_index + 1; j < num_pages; j++) {
            if (page_string[j] == current_frame_page) {
                // Found it. Check if it's the furthest
                if (j > furthest_distance) {
                    furthest_distance = j;
                    replace_index = i;
                }
                break; // Stop searching for this page
            }
        }

        // If the page is NOT found in the future, it's the perfect one to replace
        if (j == num_pages) {
            return i; // Replace this page
        }
    }

    // If all pages are found, return the one that was found furthest away
    // If replace_index is still -1 (e.g., single frame), just replace the first frame
    return (replace_index == -1) ? 0 : replace_index;
}


int main() {
    int frames[MAX_FRAMES];
    int page_string[MAX_PAGES];
    int num_frames, num_pages;
    int page_faults = 0;

    printf("Enter number of frames: ");// the storage
    scanf("%d", &num_frames);

    printf("Enter number of pages in reference string: "); // the loockup string
    scanf("%d", &num_pages);

    printf("Enter the page reference string (e.g., 7 0 1 2 0...):\n"); //data
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &page_string[i]);
    }

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\n");
    // Loop through the reference string
    for (int i = 0; i < num_pages; i++) {
        int current_page = page_string[i];
        int found = 0;

        // 1. Check for a HIT
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == current_page) {
                found = 1;
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
            } else {
                // 2b. No empty frames, must replace (find OPTIMAL)
                int replace_index = find_optimal_page(frames, num_frames, page_string, num_pages, i);
                frames[replace_index] = current_page;
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

    printf("\nTotal Page Faults (Optimal): %d\n", page_faults);
    return 0;
}
