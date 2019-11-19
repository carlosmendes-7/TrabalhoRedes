#ifndef CAMADAREDE_H_
#define CAMADAREDE_H_

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
#include "../include/camadaAplicacao.h"

typedef struct Rede {
	Transporte transporte;
	IPs ips;
} Rede;

void enviaDatagrama(int sockfd, FILE *fp, char *sendline, int n, int maxLine, ssize_t *total, Transporte transporte, IPs ips);

#endif