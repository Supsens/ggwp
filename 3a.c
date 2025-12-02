#include <stdio.h>
#include <string.h>

char FLAG[] = "01111110";

// ------------ SENDER SIDE: BIT STUFFING ------------
void bit_stuff(char *data, char *stuffed_frame) {
    int i = 0;               // index for data
    int j = 0;               // index for stuffed_frame
    int one_count = 0;

    // 1. Add starting FLAG (8 bits)
    for (int k = 0; k < 8; k++) {
        stuffed_frame[j++] = FLAG[k];
    }

    // 2. Copy data with stuffing
    while (data[i] != '\0') {
        char bit = data[i];

        // copy current bit
        stuffed_frame[j++] = bit;

        if (bit == '1') {
            one_count++;
            // after 5 ones, stuff a '0'
            if (one_count == 5) {
                stuffed_frame[j++] = '0';
                one_count = 0;
            }
        } else { // bit == '0'
            one_count = 0;
        }

        i++;
    }

    // 3. Add ending FLAG
    for (int k = 0; k < 8; k++) {
        stuffed_frame[j++] = FLAG[k];
    }

    stuffed_frame[j] = '\0';   // null terminate
}

// ------------ RECEIVER SIDE: BIT UNSTUFFING ------------
void bit_unstuff(char *stuffed_frame, char *unstuffed_data) {
    int i = 8;                          // skip starting FLAG
    int j = 0;                          // index for unstuffed_data
    int one_count = 0;
    int len = strlen(stuffed_frame);
    int end_flag_start = len - 8;       // last 8 bits are FLAG

    while (i < end_flag_start) {
        char bit = stuffed_frame[i];

        if (bit == '1') {
            one_count++;
            unstuffed_data[j++] = '1';
        } else { // bit == '0'
            if (one_count == 5) {
                // stuffed '0' → skip it
                one_count = 0;
                // do NOT copy this '0'
            } else {
                one_count = 0;
                unstuffed_data[j++] = '0';
            }
        }

        i++;
    }

    unstuffed_data[j] = '\0';
}

// -------------------- MAIN --------------------
int main() {
    char
