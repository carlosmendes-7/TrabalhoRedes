#include "../include/camadaAplicacao.h"



void conectarClienteAoServidor(int sockfd, struct sockaddr_in *servaddr)
{
    if (connect(sockfd, (SA*)&(*servaddr), sizeof((*servaddr))) != 0)
    { 
        printf("Conexão com o servidor falhou...\nEncerrando aplicacao...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Conectado ao servidor!\n");
    }
}

void verificaArquivo(int sockfd, FILE *fp, char *buff, int buff_size, char *filename){
	if(fp==NULL)
	{
		perror("Erro! Arquivo não encontrado.\n");
		exit(1);
	}
	strncpy(buff, filename, strlen(filename));
    if (send(sockfd, buff, BUFFSIZE, 0) == -1)
    {
        perror("Erro! Nao foi possivel enviar o path do arquivo. Encerrando aplicacao...\n");
        exit(1);
    } 
}

void enviarArquivo(FILE *fp, int sockfd, ssize_t *total)
{
    int n; 
    char sendline[MAX_LINE] = {0}; 
    while ((n = fread(sendline, sizeof(char), MAX_LINE, fp)) > 0) 
    {
        *total+=n;
        if (n != MAX_LINE && ferror(fp))
        {
            perror("Read File Error");
            exit(1);
        }
        
        if (send(sockfd, sendline, n, 0) == -1)
        {
            perror("Can't send file");
            exit(1);
        }
        memset(sendline, 0, MAX_LINE);
    }
    printf("Envio realizado com sucesso! Numero de Bytes = %ld\n", *total);
}

// USO SERVIDOR //

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
