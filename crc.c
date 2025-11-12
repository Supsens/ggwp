#include <stdio.h>
#include <string.h>

int main() {
    char data[100], divisor[30];
    int dataLen, divisorLen, i, j;

    printf("Enter the data bits: ");
    scanf("%s", data);
    printf("Enter the divisor (generator): ");
    scanf("%s", divisor);

    dataLen = strlen(data);
    divisorLen = strlen(divisor);

    // Append (divisorLen - 1) zeros to the data
    int totalLen = dataLen + divisorLen - 1;
    char temp[150], remainder[30];

    strcpy(temp, data);
    for (i = 0; i < divisorLen - 1; i++)
        strcat(temp, "0");

    // Division process (XOR method)
    for (i = 0; i <= totalLen - divisorLen; i++) {
        if (temp[i] == '1') {
            for (j = 0; j < divisorLen; j++)
                temp[i + j] = (temp[i + j] == divisor[j]) ? '0' : '1';
        }
    }

    // The remainder is the last (divisorLen - 1) bits
    for (i = 0; i < divisorLen - 1; i++)
        remainder[i] = temp[dataLen + i];
    remainder[i] = '\0';

    printf("\nCRC bits: %s", remainder);

    // Final transmitted codeword = original data + CRC
    printf("\nTransmitted Codeword: %s%s\n", data, remainder);

    return 0;
}

