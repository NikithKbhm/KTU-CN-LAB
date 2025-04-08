#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>

void main(){
    int clientsock ,error ;
    struct sockaddr_in client;
    clientsock = socket(AF_INET,SOCK_STREAM,0);
    if(clientsock == -1)
        printf("Error in socket creation!");
    client.sin_family = AF_INET;
    client.sin_port = htons(8100);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    error = connect(clientsock,(struct sockaddr*)&client,sizeof(client));
    if(error == -1)
        printf("Error in connecting");
    while(1){
        printf("\nClient\n");
        printf("Enter the data to be sent: ");
        char buffer[1024];
        fgets(buffer ,1024, stdin);
        error = send(clientsock,buffer,1024,0);
        if(error == -1)
            printf("Error in sending !");
        memset(buffer,0,1024);
        error= recv(clientsock,buffer,1024,0);
        printf("%s",buffer);

    }
    close(clientsock);
     
}