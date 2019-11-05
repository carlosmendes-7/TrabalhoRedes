#include "socketHandler.h"
#include "transporte.h"

void writefile(int sockfd, FILE *fp);

ssize_t total=0;

int main(int argc, char *argv[])
{
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, clientaddr; 
  
    // Verifica e cria socket
    sockfd = criaSocket();

    // Define Endereco e porta
    servaddr = defineEndereco("", 0);

    // Bindando socket
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
    { 
        printf("Erro! Falha no bind.\nEncerrando a aplicacao...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Bind realizado com sucesso!\n"); 
    }
  
    // Realizando listen
    if ((listen(sockfd, 5)) != 0)
    { 
        printf("Erro! Falha no listen.\nEncerrando a aplicacao...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Listen realizado com sucesso!\n"); 
    }

    len = sizeof(clientaddr); 
  
    // Tentativa de estabelecer conexao entre cliente-servidor (aceitar solicitacao do cliente)
    connfd = accept(sockfd, (SA*)&clientaddr, &len); 
    if (connfd < 0)
    { 
        printf("Erro! Servidor recusou comunicacao.\nEncerrando a aplicacao...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Conexao entre servidor e cliente realizada com sucesso!\n");
    }

    // ARQUIVO //
    char filename[BUFFSIZE] = {0}; 
    if (recv(connfd, filename, BUFFSIZE, 0) == -1) 
    {
        perror("Can't receive filename");
        exit(1);
    }

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) 
    {
        perror("Can't open file");
        exit(1);
    }
    
    char addr[INET_ADDRSTRLEN];
    printf("Comecando a transferencia do arquivo: %s de %s\n", filename, inet_ntop(AF_INET, &clientaddr.sin_addr, addr, INET_ADDRSTRLEN));
    writefile(connfd, fp);
    printf("Arquivo recebido com sucesso! Numero de Bytes = %ld\n", total);

    // Fechando arquivo
    fclose(fp);
  
    // Fechando socket 
    close(sockfd); 
}

void writefile(int sockfd, FILE *fp)
{
    ssize_t n;
    char buff[MAX_LINE] = {0};
    while ((n = recv(sockfd, buff, MAX_LINE, 0)) > 0) 
    {
        total+=n;
        if (n == -1)
        {
            perror("Receive File Error");
            exit(1);
        }
        
        if (fwrite(buff, sizeof(char), n, fp) != n)
        {
            perror("Write File Error");
            exit(1);
        }
        memset(buff, 0, MAX_LINE);
    }
}