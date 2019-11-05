#include <stdio.h>
#include <stdlib.h> /*exit()*/
#include <string.h> /*strlen()*/
#include <errno.h> /*error handling*/
#include <unistd.h> /*parse command-line options*/
#include <getopt.h> /*parse command-line options*/
#include <sys/types.h> /*stat()*/
#include <sys/stat.h> /*stat()*/
#include <sys/socket.h> /*socket*/
#include <netinet/in.h> /*INET6_ADDRSTRLEN*/
#include "socketHandler.h"
#include "transporte.h"

#define SA struct sockaddr
#define MAX 80

void func(int sockfd);

int main(int argc, char *argv[])
{
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and verification 
    sockfd = criaSocket();

    // assign IP, PORT 
    servaddr = defineEndereco(INADDR_ANY);

    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
    { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Socket successfully binded..\n"); 
    }
  
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0)
    { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Server listening..\n"); 
    }

    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0)
    { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
    {
        printf("server acccept the client...\n");
    }

    // Function for chatting between client and server 
    func(connfd); 
  
    // After chatting close the socket 
    close(sockfd); 
}

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    // infinite loop for chat 
    for (;;)
    { 
        bzero(buff, MAX); 
  
        // read the message from client and copy it in buffer 
        read(sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : ", buff); 
        bzero(buff, MAX); 
        n = 0; 
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n'); 
  
        // and send that buffer to client 
        write(sockfd, buff, sizeof(buff)); 
  
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0)
        { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
} 