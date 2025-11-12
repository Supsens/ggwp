
#include <stdio.h>
#include <string.h>

int main() {
    char str1[100];
    char str2[100];
    int distance = 0;

    printf("Enter the first binary string: ");
    scanf("%99s", str1);
    printf("Enter the second binary string: ");
    scanf("%99s", str2);

    // 2. Check if the lengths are the same
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2) {
        printf("Error: Strings must be of equal length.\n");
        return 1; // Exit with an error
    }

    // 3. Compare each character and count differences
    for (int i = 0; i < len1; i++) {
        // If the characters at the same position are different...
        if (str1[i] != str2[i]) {
            distance++; // ...increment the distance
        }
    }

    // 4. Print the result
    printf("\nString 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    printf("Hamming Distance: %d\n", distance);

    return 0;
}
