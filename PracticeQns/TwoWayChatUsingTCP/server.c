#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

void main(){
    int clientsock,serversock,error;
    struct sockaddr_in server , client;
    socklen_t len = sizeof(client);

    serversock = socket(AF_INET,SOCK_STREAM,0);
    if(serversock == -1)
        printf("Error in creation of socket");

    server.sin_family = AF_INET;
    server.sin_port = htons(8100);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    error = bind(serversock,(struct sockaddr*)&server,sizeof(server));
    if(error == -1)
        printf("Binding failed!");
    error = listen(serversock,1);
    if(error == -1)
        printf("Error in listening");
    clientsock = accept(serversock,(struct sockaddr*)&client,&len);
    while(1){
        char buffer[1024];
        error = recv(clientsock,buffer,1024,0);
        if(error == -1)
            printf("Error in receiving");
        printf("\nClient:%s\n",buffer);
        memset(buffer,0,1024);
        printf("\nServer:");
        fgets(buffer,1024,stdin);
        error = send(clientsock,buffer,1024,0);
    }
    close(serversock);
    close(clientsock);
}