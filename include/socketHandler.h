#ifndef SOCKETHANDLER_H_
#define SOCKETHANDLER_H_

int criaSocket();
struct sockaddr_in defineEndereco(char address[],int x);
void bindarSocket(int sockfd, struct sockaddr_in *servaddr);
void listenSocket(int sockfd);

#endif