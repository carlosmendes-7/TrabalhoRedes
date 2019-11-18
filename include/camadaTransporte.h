#ifndef CAMADATRANSPORTE_H_
#define CAMADATRANSPORTE_H_

#include <stdio.h>
#include <stdlib.h> /*exit()*/
#include <string.h> /*strlen()*/
#include <errno.h> /*error handling*/
#include <sys/types.h> /*stat()*/
#include <sys/stat.h> /*stat()*/
#include <sys/socket.h> /*socket*/
#include <netinet/in.h> /*INET6_ADDRSTRLEN*/
#include <libgen.h>

#include <arpa/inet.h> // Somente no Cliente 

#define PORT 19567
#define MAX 80
#define SA struct sockaddr

void enviaSegmento(int sockfd, FILE *fp, char *sendline, int n, int contSegmento, int maxLine, ssize_t *total);

#endif