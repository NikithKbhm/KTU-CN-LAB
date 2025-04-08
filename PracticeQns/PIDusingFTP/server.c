
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void main(){
    int clientSock, serverSock, error;
    struct sockaddr_in server, client;
    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    error = bind(serverSock, (struct sockaddr*)&server, sizeof(server));
    if(error == -1)
        printf("Binding failed\n");
    
    error = listen(serverSock, 5);
    if(error == -1)
        printf("Listening failed\n");
    
    socklen_t len = sizeof(client);
    clientSock = accept(serverSock, (struct sockaddr*)&client, &len);

    char filename[30];
    error = recv(clientSock, filename, 30, 0);
    if(error == -1)
        printf("Filename not receieved\n");
    
    FILE* file = fopen(filename, "r");
    char processID[10];
    sprintf(processID, "%d", getpid());
    error = send(clientSock, processID, 10, 0);
    if(error == -1)
        printf("Couldn't send ProcessID\n");
    
    char buffer[100];
    while(fgets(buffer, 100, file) != NULL){
        error = send(clientSock, buffer, strlen(buffer), 0);
        if(error == -1)
            printf("Couldn't send file contents\n");
        memset(buffer, 0, 100);
    }

    close(clientSock);
    close(serverSock);
}