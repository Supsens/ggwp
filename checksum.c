#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // for strtol()

int main() {
    char data[100];
    int k;

    printf("Enter the binary data string: ");
    scanf("%s", data);
    printf("Enter number of segments: ");
    scanf("%d", &k);

    int n = strlen(data);
    int m = n / k;                  // bits per segment
    int mask = (1 << m) - 1;        // used for carry wrap-around
    int sum = 0;

    printf("\n--- SENDER ---\n");

    // Step 1: Divide data into segments and add (using integer conversion)
    for (int i = 0; i < k; i++) {
        char segmentStr[32];
        strncpy(segmentStr, &data[i * m], m);
        segmentStr[m] = '\0'; // null terminate substring

        int segment = (int)strtol(segmentStr, NULL, 2); // binary → integer
        printf("Segment %d: %s (%d)\n", i + 1, segmentStr, segment);

        sum += segment;
        if (sum > mask) // wrap-around carry
            sum = (sum & mask) + 1;
    }

    int checksum = (~sum) & mask; // 1's complement of sum

    printf("Sum (decimal): %d\n", sum);
    printf("Checksum (binary): ");
    for (int i = m - 1; i >= 0; i--)
        printf("%d", (checksum >> i) & 1);
    printf(" (%d)\n", checksum);

    // Step 2: Receiver side (add sum + checksum)
    printf("\n--- RECEIVER ---\n");
    int receiverSum = sum + checksum;
    if (receiverSum > mask)
        receiverSum = (receiverSum & mask) + 1;
    receiverSum = (~receiverSum) & mask;

    printf("Receiver's Final Sum (Complemented): ");
    for (int i = m - 1; i >= 0; i--)
        printf("%d", (receiverSum >> i) & 1);
    printf("\n");

    if (receiverSum == 0)
        printf("Conclusion:  Accept Data\n");
    else
        printf("Conclusion: Reject Data\n");

    return 0;
}




#include <stdio.h>

int main() {
    int data[10], n, i, sum = 0, checksum;

    printf("Enter number of data words: ");
    scanf("%d", &n);

    printf("Enter the data words:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &data[i]);

    // Calculate sum
    for (i = 0; i < n; i++)
        sum += data[i];

    // Wrap around carry (for simplicity, assume 8-bit words)
    while (sum >> 8)
        sum = (sum & 255)  + (sum >> 8);

    checksum = ~sum & 255;

    printf("Checksum: %d\n", checksum);
    printf("Transmitted code (data + checksum): ");
    for (i = 0; i < n; i++)
        printf("%d ", data[i]);
    printf("%d\n", checksum);

    return 0;
}


