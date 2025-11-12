#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // for sleep() function

int main() {
    int total_frames, i = 1;
    srand(time(0)); // Seed random number generator

    printf("Enter total number of frames to send: ");
    scanf("%d", &total_frames);

    printf("\n--- Stop and Wait ARQ Simulation ---\n");

    while (i <= total_frames) {
        printf("\nSending Frame %d...", i);
        fflush(stdout);
        sleep(1); // simulate sending delay

        int success = rand() % 2; // 0 = lost, 1 = received

        if (success) {
            printf("\nFrame %d received successfully.", i);
            sleep(1); // simulate receiver processing time

            printf("\nSending ACK for Frame %d...", i);
            fflush(stdout);
            sleep(1); // simulate ACK transmission time

            int ack_received = rand() % 2; // simulate ACK loss

            if (ack_received) {
                printf("\nACK %d received by sender.", i);
                sleep(1);
                i++; // next frame
            } else {
                printf("\nACK %d lost! Sender waits for timeout...", i);
                fflush(stdout);
                sleep(2); // simulate waiting timeout
                printf("\nTimeout! Retransmitting Frame %d...", i);
            }
        } else {
            printf("\nFrame %d lost during transmission!", i);
            fflush(stdout);
            sleep(2); // wait before retransmission
            printf("\nRetransmitting Frame %d...", i);
        }
    }

    printf("\n\nAll %d frames sent successfully!\n", total_frames);
    return 0;
}
