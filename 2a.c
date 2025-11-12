#include<stdio.h>
#include<stdlib.h>

#define FLAG 'F'
#define ESC 'E'

void stuff_data(char *data,char *stuffed_frame){
    int data_index=0;
    int frame_index=0;

    stuffed_frame[frame_index++]=FLAG;

    while(data[data_index]!='\0'){
        char curr_char=data[data_index];

        if(curr_char==FLAG|| curr_char==ESC){
            stuffed_frame[frame_index++]=ESC;
        }
          stuffed_frame[frame_index++]=curr_char;
          data_index++;

    }
      stuffed_frame[frame_index++]=FLAG;
        stuffed_frame[frame_index]='\0';
}

void unstuff_data(char *stuffed_frame, char *unstuffed_data) {
    int frame_index = 1;      // Start at 1 to skip the Start Flag
    int data_index = 0;       // Our position in the recovered data

    // Loop until we hit the End Flag (the last character)
    while (stuffed_frame[frame_index + 1] != '\0') {
        char current_char = stuffed_frame[frame_index];
        // If we find an ESCAPE character...
        if (current_char == ESC) {
            // ...skip it and just copy the *next* character
            frame_index++;
            unstuffed_data[data_index++] = stuffed_frame[frame_index];
        } else {
            // Otherwise, it's normal data, just copy it
            unstuffed_data[data_index++] = current_char;
        }

        frame_index++;
    }
    unstuffed_data[data_index] = '\0';
}

int main() {

    char original_data[100];
    printf("please enter data: ");
    scanf("%s",original_data);

    char stuffed[200];
    char unstuffed[200];

    printf("Original data:    %s\n", original_data);
    stuff_data(original_data, stuffed);
    printf("Stuffed frame:    %s\n", stuffed);
    unstuff_data(stuffed, unstuffed);
    printf("Unstuffed data:   %s\n", unstuffed);

    return 0;
}





