// character count;
#include<stdio.h>
#include<stdlib.h>
int main(){
    char data[100];
    char frame[101];
    int len;
    printf("Enter one word");
    scanf("%s",data);
    len=strlen(data)+1;
    frame[0]=(char)len;
    strcpy(&frame[1],data);
    printf("Framed data \n");
    printf("[count:%d] %s \n",frame[0],&frame[1]);
    return 0;
}
