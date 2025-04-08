
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void main(){
    int clientSock, error;
    struct sockaddr_in client;
    clientSock = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(8080);

    error = connect(clientSock, (struct sockaddr*)&client, sizeof(client));
    if(error == -1)
        printf("Connection failed\n");

    printf("Enter filename: ");
    char filename[30];
    scanf("%s", filename);
    error = send(clientSock, filename, 30, 0);
    if(error == -1)
        printf("Couldn't send the filename\n");
    
    char processID[10];
    error = recv(clientSock, processID, 10, 0);
    if(error == -1)
        printf("Couldn't receive the process ID\n");
    
    printf("Process ID of the server: %s\n", processID);
    
    char buffer[100];
    while(1){
        error = recv(clientSock, buffer, 100, 0);
        if(error == -1)
            printf("Couldn't receive file contents\n");
        printf("%s", buffer);
        memset(buffer, 0, 100);
    }
    
    close(clientSock);
}