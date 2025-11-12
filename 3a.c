
#include <stdio.h>
#include <string.h>

char FLAG[] = "01111110";
void bit_stuff(char *data, char *stuffed_frame) {
    int data_index = 0;
    int stuffed_index = 0;
    int one_count = 0; // Counter for consecutive '1's

    // 1. Add the Start Flag to the frame
    strcpy(stuffed_frame, FLAG);
    stuffed_index = 8; // We've written 8 characters

    // 2. Loop through the raw data bits
    while (data[data_index] != '\0') {
        char current_bit = data[data_index];

        // Always copy the current bit
        stuffed_frame[stuffed_index++] = current_bit;

        if (current_bit == '1') {
            one_count++;
        } else {
            one_count = 0; // Reset count on a '0'
        }

        // --- The Stuffing Rule ---
        // If we hit 5 ones, stuff a '0' and reset the count
        if (one_count == 5) {
            stuffed_frame[stuffed_index++] = '0';
            one_count = 0;
        }

        data_index++;
    }

    // 3. Add the End Flag to the frame
    strcat(stuffed_frame, FLAG); // strcat adds the string to the end
}

/*
 * --- Receiver Side: bit_unstuff ---
 * Takes a stuffed frame and removes the stuffed '0's.
 */
void bit_unstuff(char *stuffed_frame, char *unstuffed_data) {
    int stuffed_index = 8; // Skip the 8-bit Start Flag
    int data_index = 0;
    int one_count = 0;

    // Loop until we are 8 bits from the end (which is the End Flag)
    while (stuffed_frame[stuffed_index + 8] != '\0') {
        char current_bit = stuffed_frame[stuffed_index];

        if (current_bit == '1') {
            one_count++;
            // Copy the '1' to our final data
            unstuffed_data[data_index++] = current_bit;
        } else { // current_bit is a '0'

            // --- The Unstuffing Rule ---
            if (one_count == 5) {
                // This is a stuffed '0', so we DON'T copy it.
                // We just skip it and reset the count.
                one_count = 0;
            } else {
                // This is a normal '0', so we copy it.
                one_count = 0;
                unstuffed_data[data_index++] = current_bit;
            }
        }
        stuffed_index++;
    }

    // Add the null terminator to make it a valid string
    unstuffed_data[data_index] = '\0';
}

/*
 * --- Main Function ---
 * Let's test it!
 */
int main() {
    // We'll use %99s to prevent buffer overflow
    char original_data[100];

    char stuffed[200];
    char unstuffed[200];

    printf("Enter data (only '0's and '1's): ");
    scanf("%99s", original_data);

    printf("\nOriginal data:  %s\n", original_data);

    // --- Sender's Action ---
    bit_stuff(original_data, stuffed);
    printf("Stuffed frame:  %s\n", stuffed);

    // --- Receiver's Action ---
    bit_unstuff(stuffed, unstuffed);
    printf("Unstuffed data: %s\n", unstuffed);

    return 0;
}
