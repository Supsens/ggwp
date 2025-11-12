#include <stdio.h>
#include <string.h>

// --- Helper function to perform binary XOR ---
// This is the core of the "division"
void perform_xor(char *temp_data, char *generator, int gen_len) {
    for (int i = 0; i < gen_len; i++) {
        // If bits are the same, result is '0'. If different, result is '1'.
        temp_data[i] = (temp_data[i] == generator[i]) ? '0' : '1';
    }
}

// --- Helper function to check if a remainder is zero ---
int is_remainder_zero(char *remainder, int gen_len) {
    for (int i = 0; i < gen_len - 1; i++) {
        if (remainder[i] == '1') {
            return 0; // Not zero
        }
    }
    return 1; // Is zero
}

// --- Main CRC calculation function ---
void calculate_crc(char *data, char *generator, char *remainder) {
    int data_len = strlen(data);
    int gen_len = strlen(generator);

    // The remainder will be k-1 bits, where k is length of generator
    int rem_len = gen_len - 1;

    // Create a temporary copy of the data to work on
    char temp_data[200];
    strcpy(temp_data, data);

    // --- This is the binary long division (using XOR) ---
    // We "divide" until we've processed all bits that can be divided
    for (int i = 0; i <= (data_len - gen_len); i++) {
        // If the leading bit is '0', we don't need to XOR
        if (temp_data[i] == '1') {
            // Perform XOR starting from the current bit (temp_data[i])
            perform_xor(&temp_data[i], generator, gen_len);
        }
    }

    // The last 'rem_len' bits of temp_data are our remainder
    strcpy(remainder, &temp_data[data_len - rem_len]);
}


int main() {
    char data[100];
    char generator[50];
    char appended_data[150];
    char crc_remainder[50];
    char transmitted_codeword[150];
    char received_remainder[50];

    printf("Enter data (e.g., 101100): ");
    scanf("%99s", data);
    printf("Enter generator (e.g., 1101): ");
    scanf("%99s", generator);

    int data_len = strlen(data);
    int gen_len = strlen(generator);
    int rem_len = gen_len - 1;

    printf("\n--- SENDER SIDE ---\n");
    strcpy(appended_data, data);
    for (int i = 0; i < rem_len; i++) {
        strcat(appended_data, "0"); // Add one '0' at a time
    }
    printf("Data with %d zeros: %s\n", rem_len, appended_data);

    // --- 3. SENDER: Calculate CRC ---
    calculate_crc(appended_data, generator, crc_remainder);
    printf("Calculated CRC:       %s\n", crc_remainder);

    // --- 4. SENDER: Create final codeword (Data + CRC) ---
    strcpy(transmitted_codeword, data);       // Start with original data
    strcat(transmitted_codeword, crc_remainder); // Add the CRC
    printf("Transmitted Codeword: %s\n", transmitted_codeword);


    printf("\n--- RECEIVER SIDE (NO ERROR) ---\n");

    // --- 5. RECEIVER: Check the clean codeword ---
    // The receiver divides the *entire* codeword by the generator
    calculate_crc(transmitted_codeword, generator, received_remainder);
    printf("Receiver's remainder: %s\n", received_remainder);

    // Check if the remainder is all zeros
    if (is_remainder_zero(received_remainder, gen_len)) {
        printf("RESULT: No error detected. Data is OK.\n");
    } else {
        printf("RESULT: Error detected! Data is corrupt.\n");
    }


    printf("\n--- ERROR SIMULATION ---\n");

    // --- 6. SIMULATE ERROR: Flip one bit ---
    // Let's flip the 2nd bit (at index 1)
    if (transmitted_codeword[1] == '0') {
        transmitted_codeword[1] = '1';
    } else {
        transmitted_codeword[1] = '0';
    }
    printf("Corrupted Codeword:   %s\n", transmitted_codeword);

    // --- 7. RECEIVER: Check the corrupted codeword ---
    calculate_crc(transmitted_codeword, generator, received_remainder);
    printf("Receiver's remainder: %s\n", received_remainder);

    if (is_remainder_zero(received_remainder, gen_len)) {
        printf("RESULT: No error detected. (This is bad!)\n");
    } else {
        printf("RESULT: Error detected! Data is corrupt.\n");
    }

    return 0;
}
