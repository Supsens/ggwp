#include <stdio.h>
#include <string.h>

int main() {
    char data[100], divisor[30], temp[130];
    int dataLen, divisorLen, i, j;

    printf("Enter the data bits: ");
    scanf("%s", data);
    printf("Enter the divisor (generator): ");
    scanf("%s", divisor);

    dataLen = strlen(data);
    divisorLen = strlen(divisor);

    // Step 1: Append (divisorLen - 1) zeros to data
    strcpy(temp, data);
    for (i = 0; i < divisorLen - 1; i++)
        strcat(temp, "0");

    int totalLen = strlen(temp);

    // Step 2: Perform division (XOR)
    for (i = 0; i <= totalLen - divisorLen; i++) {
        if (temp[i] == '1') {
            for (j = 0; j < divisorLen; j++)
                temp[i + j] = (temp[i + j] == divisor[j]) ? '0' : '1';
        }
    }

    // Step 3: Extract remainder (CRC bits)
    char crc[30];
    for (i = 0; i < divisorLen - 1; i++)
        crc[i] = temp[dataLen + i];
    crc[i] = '\0';

    printf("\nCRC bits: %s", crc);
    printf("\nTransmitted Codeword: %s%s", data, crc);

    // Step 4: Receiver side
    char received[130];
    printf("\n\nEnter the received codeword: ");
    scanf("%s", received);

    // Step 5: Perform division again on received codeword
    int recvLen = strlen(received);
    for (i = 0; i <= recvLen - divisorLen; i++) {
        if (received[i] == '1') {
            for (j = 0; j < divisorLen; j++)
                received[i + j] = (received[i + j] == divisor[j]) ? '0' : '1';
        }
    }

    // Step 6: Check remainder for error
    int error = 0;
    for (i = recvLen - divisorLen + 1; i < recvLen; i++) {
        if (received[i] == '1') {
            error = 1;
            break;
        }
    }

    if (error)
        printf("\n❌ Error detected in received codeword!\n");
    else
        printf("\n✅ No error detected. Data received correctly.\n");

    return 0;
}
