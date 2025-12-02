#include <stdio.h>
#include <stdlib.h>

#define FLAG 'F'
#define ESC  'E'

// --- Stuffing ---
void stuff_data(char *data, char *stuffed_frame) {
    int i = 0; // data index
    int j = 0; // frame index

    // Add starting FLAG
    stuffed_frame[j++] = FLAG;

    // Go through each character of data
    while (data[i] != '\0') {
        char c = data[i];

        // If it's FLAG or ESC, put ESC first
        if (c == FLAG || c == ESC) {
            stuffed_frame[j++] = ESC;
        }

        // Copy the character
        stuffed_frame[j++] = c;
        i++;
    }

    // Ending FLAG
    stuffed_frame[j++] = FLAG;
    stuffed_frame[j] = '\0'; // null-terminate
}

// --- Unstuffing ---
void unstuff_data(char *stuffed_frame, char *unstuffed_data) {
    int i = 1; // start from 1 to skip starting FLAG
    int j = 0; // data index

    // Read until we hit the ending FLAG or end of string
    while (stuffed_frame[i] != '\0' && stuffed_frame[i] != FLAG) {
        char c = stuffed_frame[i];

        if (c == ESC) {
            // Skip ESC and take the next character as is
            i++;
            c = stuffed_frame[i];
        }

        unstuffed_data[j++] = c;
        i++;
    }

    unstuffed_data[j] = '\0';
}

int main() {
    char original_data[100];
    char stuffed[200];
    char unstuffed[200];

    printf("Please enter data: ");
    scanf("%s", original_data);

    printf("Original data:   %s\n", original_data);

    stuff_data(original_data, stuffed);
    printf("Stuffed frame:   %s\n", stuffed);

    unstuff_data(stuffed, unstuffed);
    printf("Unstuffed data:  %s\n", unstuffed);

    return 0;
}
