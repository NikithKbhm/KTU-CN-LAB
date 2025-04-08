#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

void main(){
    int clientsock , error;
    struct sockaddr_in client;
    clientsock = socket(AF_INET,SOCK_STREAM,0);
    
    client.sin_family = AF_INET;
    client.sin_port = htons(8100);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    error = connect(clientsock,(struct sockaddr*)&client,sizeof(client));
    if(error == -1)
        printf("error in connection");
    
    char request[10];
    printf("Enter the number of primes needed(range):");
    int n;
    scanf("%d",&n);
    sprintf(request,"%d",n);
    error = send(clientsock,request,10,0);
    if(error == -1)
        printf("Error in sending");
    
    char buffer[100];
    while(1){
    error = recv(clientsock,buffer,100,0);
    if(error == -1)
        printf("Error in receiving data from server");
    if(strcmp(buffer,"")==0)
        break;
    printf("%s\n",buffer);
    memset(buffer,0,100);
    }
    close(clientsock);
}