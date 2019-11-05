#include <stdio.h>
#include <stdlib.h> /*exit()*/
#include <string.h> /*strlen()*/
#include <unistd.h> /*parse command-line options*/
#include <sys/socket.h> /*socket*/
#include <netinet/in.h> /*INET6_ADDRSTRLEN*/
#include <arpa/inet.h>

#define SA struct sockaddr
#define MAX 80
#define PORT 8080

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

struct sockaddr_in defineEndereco(char address[])
{
	struct sockaddr_in servidorTemp;
	bzero(&servidorTemp, sizeof(servidorTemp));
	servidorTemp.sin_family = AF_INET;
	servidorTemp.sin_port = htons(PORT);
	if(address=="127.0.0.1")
	{
		servidorTemp.sin_addr.s_addr = inet_addr(address); 	
	}
	else
	{
		servidorTemp.sin_addr.s_addr = htonl(INADDR_ANY);
	}

	return servidorTemp;
}