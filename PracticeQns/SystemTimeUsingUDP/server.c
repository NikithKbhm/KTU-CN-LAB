#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<time.h>

void main(){
    int serversock,error;
    struct sockaddr_in server,client;
    serversock = socket(AF_INET,SOCK_DGRAM,0);
    if(serversock == -1)
        printf("Error in creating socket");
    
    server.sin_family = AF_INET;
    server.sin_port = htons(8100);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    error = bind(serversock,(struct sockaddr*)&server,sizeof(server));
    if(error == -1)
        printf("Error in Binding");
    char request[10];
    char buffer[100];
    socklen_t clientlen = sizeof(client);
    socklen_t serverlen = sizeof(server);
    error = recvfrom(serversock,request,1024,0,(struct sockaddr*)&client,&clientlen);
    if(error == -1)
        printf("Error in receiving");

    if(strcmp(request, "time")==0){
        struct tm* now;
        time_t current_time = time(NULL);
        now = localtime(&current_time);
        char buffer[100];
        strftime(buffer,100,"%D %H:%M:%S\n",now);
        error = sendto(serversock,buffer,100,0,(struct sockaddr*)&client,clientlen);
        if(error == -1)
            printf("Error in sending!"); 
    }
    else{
        printf("Invalid request!\n");
    }
    close(serversock);
}