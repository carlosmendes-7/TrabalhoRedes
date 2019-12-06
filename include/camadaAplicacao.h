/*Equipe:
 * Carlos Frederico D'Almeida e Mendes
 * Danilo de Andrade Peleteiro
 *
 *
 *
 */
#ifndef CAMADAAPLICACAO_H_
#define CAMADAAPLICACAO_H_

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
#include <libgen.h>

#include <arpa/inet.h> // Somente no Cliente 

#define MAX_LINE 4096
#define PORT 19567
#define BUFFSIZE 4096
#define SA struct sockaddr
#define MAX 80
#define TAMANHO_SEGMENTO 8

typedef struct IPs {
	char *ipCliente;
	char *ipServidor;
} IPs;

// USO CLIENTE //
void conectarClienteAoServidor(int sockfd, struct sockaddr_in *servaddr);
void verificaArquivo(int sockfd, FILE *fp, char *buff, int buff_size, char *filename);
void enviarArquivo(FILE *fp, int sockfd, ssize_t *total, IPs ips);

// USO SERVIDOR //
void verificaConexao(int connfd);
void verificaArquivoCliente(int connfd, int buff_size, char *filename);
void receberArquivo(int sockfd, FILE *fp, ssize_t *total);

#endif
