#include "../include/camadaAplicacao.h"


// USO CLIENTE //

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

void verificaArquivo(int sockfd, FILE *fp, char *buff, int buff_size, char *filename)
{
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
    while ((n = fread(sendline, sizeof(char), TAMANHO_SEGMENTO, fp)) > 0) 
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

void verificaArquivoCliente(int connfd, int buff_size, char *filename)
{
    if(recv(connfd, filename, buff_size, 0) == -1) 
    {
        perror("Erro! Nao foi possivel receber o path do arquivo. Encerrando aplicacao...\n");
        exit(1);
    }
    
}

void receberArquivo(int sockfd, FILE *fp, ssize_t *total)
{
    ssize_t n;
    char buff[MAX_LINE] = {0};
    while ((n = recv(sockfd, buff, TAMANHO_SEGMENTO, 0)) > 0) 
    {
        *total+=n;
        printf("%s\n", buff);
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