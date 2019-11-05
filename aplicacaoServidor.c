#include "socketHandler.h"
#include "transporte.h"

void receberArquivo(int sockfd, FILE *fp);
void bindarSocket(int sockfd, struct sockaddr_in *servaddr);
void listenSocket(int sockfd);
void verificaConexao(int connfd);

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
  
    // Tentativa de estabelecer conexao entre cliente-servidor (aceitar solicitacao do cliente)
    connfd = accept(sockfd, (SA*)&clientaddr, &clientAddrLength);
    verificaConexao(connfd);

    ////////// Acoes referentes ao Arquivo //////////

    char filename[BUFFSIZE] = {0}; 
    if (recv(connfd, filename, BUFFSIZE, 0) == -1) 
    {
        perror("Erro! Nao foi possivel receber o arquivo. Encerrando aplicacao...\n");
        exit(1);
    }

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) 
    {
        perror("Erro! Nao foi possivel abrir o arquivo. Encerrando aplicacao...\n");
        exit(1);
    }
    
    char addr[INET_ADDRSTRLEN];
    printf("Comecando a transferencia do arquivo: %s de %s\n", filename, inet_ntop(AF_INET, &clientaddr.sin_addr, addr, INET_ADDRSTRLEN));
    receberArquivo(connfd, fp);
    printf("Arquivo recebido com sucesso! Numero de Bytes = %ld\n", total);

    // Fechando arquivo
    fclose(fp);
  
    // Fechando socket 
    close(sockfd); 
}

void receberArquivo(int sockfd, FILE *fp)
{
    ssize_t n;
    char buff[MAX_LINE] = {0};
    while ((n = recv(sockfd, buff, MAX_LINE, 0)) > 0) 
    {
        total+=n;
        if (n == -1)
        {
            perror("Erro no recebimento do arquivo\n");
            exit(1);
        }
        
        if (fwrite(buff, sizeof(char), n, fp) != n)
        {
            perror("Erro na escrita do arquivo\n");
            exit(1);
        }
        memset(buff, 0, MAX_LINE);
    }
}

void bindarSocket(int sockfd, struct sockaddr_in *servaddr)
{
    if (bind(sockfd, (SA*)&(*servaddr), sizeof((*servaddr))) != 0)
    { 
        printf("Erro! Falha no bind.\nEncerrando a aplicacao...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Bind realizado com sucesso!\n"); 
    }
}

void listenSocket(int sockfd)
{
    if ((listen(sockfd, 5)) != 0)
    { 
        printf("Erro! Falha no listen.\nEncerrando a aplicacao...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Listen realizado com sucesso!\n"); 
    }
}

void verificaConexao(int connfd)
{
    if (connfd < 0)
    { 
        printf("Erro! Servidor recusou comunicacao.\nEncerrando a aplicacao...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Conexao entre servidor e cliente realizada com sucesso!\n");
    }
}