#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>

void main(){
    int clientsock ,error;
    struct sockaddr_in client,server;
    clientsock = socket(AF_INET,SOCK_DGRAM,0);
    if(clientsock == -1)
        printf("Error in socket creation!");
    
    client.sin_family = AF_INET;
    client.sin_port = htons(8100);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    char request[10];
    printf("Enter request:");
    scanf("%s",request);

    socklen_t serverlen = sizeof(server);
    socklen_t clientlen = sizeof(client);

    error = sendto(clientsock,request,10,0,(struct sockaddr*)&client,clientlen);
    if(error == -1)
        printf("Error in sending!");

    char buffer[100];
    error = recvfrom(clientsock,buffer,100,0,(struct sockaddr*)&server,&serverlen);
    if(error == -1)
        printf("Error in receiving");
    printf("System time is : %s",buffer);
    close(clientsock);
}