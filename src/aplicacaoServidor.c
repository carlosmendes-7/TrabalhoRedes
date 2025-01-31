/*Equipe:
 * Antonio Carlos Couto Oliveira
 * Caique de Souza Silva
 * Carlos Frederico D'Almeida e Mendes
 * Danilo de Andrade Peleteiro
 * Rafael Barretto Serejo Farias
 * Vinicius Aragao Nascimento
 */

#include "../include/camadaAplicacao.h"


ssize_t total=0;

int main(int argc, char *argv[])
{

    ////////// Acoes para o Socket //////////

    int sockfd, connfd, clientAddrLength; 
    struct sockaddr_in servaddr, clientaddr; 
  
    // Verifica e cria socket
    sockfd = criaSocket();

    // Define Endereco e porta
    servaddr = defineEndereco("", 0);

    // Bindando socket
    bindarSocket(sockfd, &servaddr);
  
    // Realizando listen
    listenSocket(sockfd);

    clientAddrLength = sizeof(clientaddr); 
  
    // Tentativa de estabelecer conexao entre cliente-servidor (aceitar solicitacao do cliente) [CAMADA DE APLICACAO]
    connfd = accept(sockfd, (SA*)&clientaddr, &clientAddrLength);
    verificaConexao(connfd);

    //printf("IP CLIENTE: %s\nIP SERVIDOR: %s\n", inet_ntoa(clientaddr.sin_addr), inet_ntoa(servaddr.sin_addr));
    ////////// Acoes referentes ao Arquivo //////////

    char filename[BUFFSIZE] = {0}; 
    verificaArquivoCliente(connfd,BUFFSIZE,filename);
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) 
    {
        perror("Erro! Nao foi possivel abrir o arquivo. Encerrando aplicacao...\n");
        exit(1);
    }
    
    char addr[INET_ADDRSTRLEN];
    printf("Comecando a transferencia do arquivo: %s de %s\n", filename, inet_ntop(AF_INET, &clientaddr.sin_addr, addr, INET_ADDRSTRLEN));
    receberArquivo(connfd, fp, &total);

    // Fechando arquivo
    fclose(fp);
  
    // Fechando socket 
    close(sockfd);

}

