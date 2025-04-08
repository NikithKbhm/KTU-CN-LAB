#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct node{
    int packet;
    struct node*next;
};

struct node* head = NULL;
struct node* headRetransmit = NULL;

void addNode(int packet, int isRetransmitting){
    struct node * temp;
    if(isRetransmitting == 1)
        temp = headRetransmit;
    else    
        temp = head;
    struct node * newnode = (struct node*)malloc(sizeof(struct node));
    newnode -> packet = packet;
    
    if(temp == NULL){
        if(isRetransmitting == 1)
           headRetransmit = newnode;
        else
            head = newnode;
    }
        
    else{
        while(temp->next!=NULL)
            temp = temp ->next;
        temp->next = newnode;
    }
    newnode->next = NULL;
}

void main(){
    int m , size ,i=0;
    printf("Enter the max no of frames:");
    scanf("%d",&m);
    printf("Enter the window size:");
    scanf("%d",&size);
    printf("Enter timer");
    int timer;
    scanf("%d",&timer);
    for(int i = 0 ; i<size ; i++)
        addNode(i,0);
    struct node*temp = head;
    while(temp!=NULL){
        printf("Sending packet %d to receiver\n",temp->packet);
        sleep(timer);
        int lost = rand()%m;
        if(lost == temp->packet){
            addNode(temp->packet,1);
            printf("Acknowledgement of %d packet has not been received!\n",temp->packet);
            sleep(1);
            head=head->next;

        }
        else{
            printf("Acknowledegement for %d packet has been received\n",temp->packet);
            if(headRetransmit == NULL){
                if(i<m){
                        addNode(i,0);
                        i++;
                }
            }
            struct node*temp2 = head;
            head = head ->next;
            free(temp2);
        }
        if(head == NULL){
            if(i<m){
                addNode(i,0);
                i++;
            }
            while(headRetransmit != NULL){
                printf("Retransmitting packet %d again",headRetransmit->packet);
                sleep(timer);
                int lost = rand() % m;
                if(lost == headRetransmit->packet){
                    addNode(headRetransmit->packet,1);
                    printf("Acknowledegement has not been received");
                    sleep(1);
                    
                }
                else{
                    printf("Acknowledgment for %d packet has been received",headRetransmit->packet);
                   struct node * temp2 = headRetransmit;
                   headRetransmit = headRetransmit->next;
                   free(temp2);
                }
            }
        }
        temp = head;
    }
}