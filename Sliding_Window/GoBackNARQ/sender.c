#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

struct node{
    int packet;
    struct node* next;
};

struct node* head = NULL;

void addNode(int packet){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    struct node* temp = head;
    newNode -> packet = packet;
    if(head == NULL)
        head = temp = newNode;
    else{
        while(temp -> next != NULL)
            temp = temp -> next;
        temp -> next = newNode;
    }
    newNode -> next = NULL;
}

void main(){
    int senderSock, error;
    struct sockaddr_in sender;
    senderSock = socket(PF_INET, SOCK_STREAM, 0);

    struct timeval timer;
    printf("Enter timer: ");
    scanf("%ld", &timer.tv_sec);
    timer.tv_usec = 0;

    error = setsockopt(senderSock, SOL_SOCKET, SO_RCVTIMEO, &timer, sizeof(timer));     //to set the socket such that it only waits for a certain amount of time to receive ack
    if(error == -1)
        printf("Socket setup failed\n");

    sender.sin_family = AF_INET;
    sender.sin_addr.s_addr = inet_addr("127.0.0.1");
    sender.sin_port = htons(8100);

    error = connect(senderSock, (struct sockaddr*)&sender, sizeof(sender));
    if(error == -1)
        printf("Connection failed\n");
    
    printf("Enter total number of frames: ");
    int n;
    scanf("%d", &n);
    printf("Enter sliding window size (should be less than total frames): ");
    int size;
    scanf("%d", &size);
    
    int i = 0;
    for(i = 0; i < size; i++)
        addNode(i);

    while(head != NULL){
        struct node* temp = head;
        char buffer[100];
        sprintf(buffer, "%d", temp -> packet);
        error = send(senderSock, buffer, 100, 0);
        if(error == -1)
            printf("Sending failed\n");
        
        printf("Packet %d has been sent to the receiver\n", temp -> packet);
        memset(buffer, 0, 100);
        error = recv(senderSock, buffer, 100, 0);
        if(error == -1){
            struct node* temp2 = temp -> next;
            while(temp2 != NULL){
                printf("Packet %d has been sent to the receiver\n", temp2 -> packet);
                temp2 = temp2 -> next;
            }
            printf("Retransmitting Packet %d\n", temp -> packet);
            sleep(1);
        }
        else{
            printf("Acknowledgement for Packet %s has been received\n", buffer);
            if(i < n)
                addNode(i);
            head = head -> next;
            free(temp);
            i++;
        }
    }

    close(senderSock);
}