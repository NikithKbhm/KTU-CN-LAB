#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>

void main(){
    int clientsock , serversock, error;
    struct sockaddr_in server,client;

    serversock = socket(AF_INET,SOCK_STREAM,0);

    if(serversock == -1)
        printf("Error in socket creation");
    
    server.sin_family = AF_INET;
    server.sin_port = htons(8100);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    error = bind(serversock,(struct sockaddr*)&server,sizeof(server));
    if(error == -1)
        printf("Error in binding");
    
    error = listen(serversock,1);
    if(error == -1)
    printf("Error in listening");

    socklen_t clientlen = sizeof(client);
    clientsock = accept(serversock,(struct sockaddr*)&client,&clientlen);
    if(error == -1)
    printf("Error in accepting");
    char request[10];
    error = recv(clientsock,request,10,0);
    int k = atoi(request);
    for(int i = 2 ; i<=k ; i++){
        int flag = 0;
        for(int j = 2 ; j<=i/2 ;j++){
            if(i%j == 0){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            char buffer[100];
            sprintf(buffer,"%d",i);
            error = send(clientsock,buffer,100,0);
            if(error == -1)
                printf("Error in sending prime data");
            sleep(1);
        }
    }
    close(serversock);
    close(clientsock);
    
}