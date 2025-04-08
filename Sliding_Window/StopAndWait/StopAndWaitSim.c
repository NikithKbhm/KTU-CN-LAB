#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void main(){
    int m;
    printf("Enter the max number of frames:");
    scanf("%d",&m);
    printf("Enter the  timer:");
    int timer;
    scanf("%d",&timer);
    int i = 0;
    while(i<m){
        printf("Sending packet %d to receiver \n",i);
        sleep(timer);
        int lost = rand() %m;
        if(i==lost){
            printf("Acknowledegement for packet %d has not been received\n",i);
            sleep(1);
            printf("Retransmitting packet %d back to receiver\n",i);

        }
        else{
            printf("Acknowledegement for packet %d has been received \n",i);
            i++;
        }
    }

}