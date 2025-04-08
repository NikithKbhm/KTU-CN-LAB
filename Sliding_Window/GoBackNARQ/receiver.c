#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>

int main(){
    int receiversock, sendersock, error;
    struct sockaddr_in sender,receiver;
    receiversock = socket(AF_INET,SOCK_STREAM,0);

    receiver.sin_family = AF_INET;
    receiver.sin_addr.s_addr = inet_addr("127.0.0.1");
    receiver.sin_port = htons(8100);

    error = bind(receiversock,(struct sockaddr*)&receiver,sizeof(receiver));
    if(error == -1){
        printf("Binding failed\n");
    }
    error = listen(receiversock,1);
    if(error == -1){
        printf("Listening failed\n");
    }
    socklen_t len = sizeof(sender);
    sendersock = accept(receiversock,(struct sockaddr*)&sender,&len);
    while(1){
        char buffer[100];
        error = recv(sendersock,buffer,100,0);
        printf("received packet %s from sender\n",buffer);
        sleep(5);
        error = send(sendersock,buffer,100,0);
        if(error == -1){
            printf("Sending failed\n");
        }
        printf("Sent acknowledgement for packet %s to the sender\n",buffer);

    }
    close(receiversock);
    close(sendersock);
    return 0;
}

