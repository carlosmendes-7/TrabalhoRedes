#ifndef CAMADAENLACE_H_
#define CAMADAENLACE_H_

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

#include "../include/camadaTransporte.h"
#include "../include/camadaRede.h"

void enviaQuadro(int sockfd, FILE *fp, char *sendline, int n, int maxLine, ssize_t *total, Rede rede);

#endif