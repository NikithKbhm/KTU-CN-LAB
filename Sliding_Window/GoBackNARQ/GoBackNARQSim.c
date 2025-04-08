
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct node{
    int packet;
    struct node* next;
};

struct node* head = NULL;

void addNode(int packet){
    struct node* temp = head;
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode -> packet = packet;

    if(head == NULL)
        head = newNode;
    else{
        while(temp -> next != NULL)
            temp = temp -> next;
        temp -> next = newNode;
    }

    newNode -> next = NULL;
}

void main(){   
    printf("Enter total number of frames: ");
    int n;
    scanf("%d", &n);

    printf("Enter timer (in sec): ");
    int timer;
    scanf("%d", &timer);

    printf("Enter window size: ");
    int size;
    scanf("%d", &size);

    int i = 0;
    for(i = 0; i < size; i++)
        addNode(i);
    
    while(head != NULL){
        printf("Sending Packet %d to receiver\n", head -> packet);
        sleep(timer);
        int lost = rand() % n;
        if(lost == head -> packet){
            printf("Acknowledgement for Packet %d has not been received\n", head -> packet);
            sleep(1);
            struct node* temp = head -> next;
            while(temp != NULL){
                printf("Sending Packet %d to receiver\n", temp -> packet);
                sleep(1);
                printf("Packet %d has been discarded by the receiver\n", temp -> packet);
                temp = temp -> next;
            }
            printf("Retransmitting Packet %d back to receiver\n", head -> packet);
        }
        else{
            printf("Acknowledgement for Packet %d has been received\n", head -> packet);
            struct node* temp = head;
            head = head -> next;
            if(i < n){
                addNode(i);
                i++;
            }
            free(temp);
        }
    }
}