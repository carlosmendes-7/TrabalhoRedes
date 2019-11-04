#include <stdio.h>
#include <stdlib.h> /*exit()*/
#include <string.h> /*strlen()*/
#include <errno.h> /*error handling*/
#include <unistd.h> /*parse command-line options*/
#include <getopt.h> /*parse command-line options*/
#include <sys/types.h> /*stat()*/
#include <sys/stat.h> /*stat()*/
#include <netinet/in.h> /*INET6_ADDRSTRLEN*/
#include "transporte.h"

int criaSocket();
sockaddr_in defineEndereco();

int main(int argc, char *argv[])
{
	int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and verification 
    sockfd = criaSocket();

    // assign IP, PORT 
    servaddr = defineEndereco();

    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 
}

int criaSocket()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("socket creation failed...\n"); 
        exit(0); 
	}
	printf("Socket successfully created..\n");	
	return sockfd;
}

sockaddr_in defineEndereco()
{
	sockaddr_in servidorTemp;
	bzero(&servidorTemp, sizeof(servidorTemp));
	servidorTemp.sin_family = AF_INET;
	servidorTemp.sin_addr.s_addr = htonl(INADDR_ANY);
	servidorTemp.sin_port = htons(PORT);
	return servidorTemp;
}