#include "../include/socketHandler.h"
#include "../include/camadaTransporte.h"

int criaSocket()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("Criacao do socket falhou...\nEncerrando aplicacao...\n"); 
		exit(0); 
	}
	printf("Socket criado com sucesso!\n");  
	return sockfd;
}

struct sockaddr_in defineEndereco(char address[], int x)
{
	struct sockaddr_in servidorTemp;
	bzero(&servidorTemp, sizeof(servidorTemp));
	servidorTemp.sin_family = AF_INET;
	servidorTemp.sin_port = htons(PORT);
	if(x==1)
	{
		servidorTemp.sin_addr.s_addr = inet_addr(address); 	
	}
	else
	{
		servidorTemp.sin_addr.s_addr = htonl(INADDR_ANY);
	}

	return servidorTemp;
}