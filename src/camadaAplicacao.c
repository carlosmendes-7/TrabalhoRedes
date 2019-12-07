/*Equipe:
 * Antonio Carlos Couto Oliveira
 * Caique de Souza Silva
 * Carlos Frederico D'Almeida e Mendes
 * Danilo de Andrade Peleteiro
 * Rafael Barretto Serejo Farias
 * Vinicius Aragao Nascimento
 */

#include "../include/camadaAplicacao.h"
#include "../include/camadaTransporte.h"
#include "../include/camadaRede.h"

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

void enviarArquivo(FILE *fp, int sockfd, ssize_t *total, IPs ips)
{
    int contSegmento=1;
    int n; 
    char sendline[MAX_LINE] = {0}; 
    while ((n = fread(sendline, sizeof(char), TAMANHO_SEGMENTO, fp)) > 0) 
    {

        enviaSegmento(sockfd, fp, sendline, n, contSegmento, MAX_LINE, total, ips); // ENVIA SEGMENTO PARA CAMADA DE TRANSPORTE
        contSegmento++;
    }
    printf("Envio realizado com sucesso! Numero de Bytes = %ld\nEncerrando aplicacao...\n", *total);
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
        printf("Pacote recebido: %s\n", buff);
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
    printf("Arquivo recebido com sucesso! Numero de Bytes = %ld\nEncerrando a aplicacao...\n", *total);
}

// SOCKET HANDLER //

int criaSocket()
{
    printf("[SOCKET]\nIniciando Criacao do Socket...\n");
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        printf("Criacao do socket falhou...\nEncerrando aplicacao...\n"); 
        exit(0); 
    }
    printf("Socket criado com sucesso!\n");  
    return sockfd;
}

struct sockaddr_in defineEndereco(char *address, int x)
{
    struct sockaddr_in servidorTemp;
    bzero(&servidorTemp, sizeof(servidorTemp));
    servidorTemp.sin_family = AF_INET;
    servidorTemp.sin_port = htons(PORT);
    if(x==1)
    {
        servidorTemp.sin_addr.s_addr = inet_addr("127.0.0.1"); // era address
    }
    else
    {
        servidorTemp.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    return servidorTemp;
}

void bindarSocket(int sockfd, struct sockaddr_in *servaddr)
{
    printf("[BIND]\nIniciando Binding...\n");
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
    printf("[LISTEN]\nIniciando Listen...\n");
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