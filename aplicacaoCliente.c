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
#include <arpa/inet.h>
#include "socketHandler.h"
#include "transporte.h"

#define SA struct sockaddr
#define MAX 80

void showHelp(char *nome);
void func(int sockfd); //TESTANDO MSG DE TEXTO COM SERVIDOR

int main(int argc, char *argv[])
{
    char serverAddress[INET6_ADDRSTRLEN] = ""; // INET6_ADDRSTRLEN = 46 bytes
    int rc = 0; /*variavel que recebe o retorno das chamadas de funcao*/

    if (argc < 2)
    {
        showHelp(argv[0]); // Mostra helper caso usuario nao defina nenhuma acao apos execucao do programa(-h ou -s)
    }

    int opt;
    const struct option longopts[] =
    {
        {"help"     , no_argument       , NULL , 'h'},
        {"ajuda"    , no_argument       , NULL , 'h'},
        {"send"   , required_argument , NULL , 's'},
        {"enviar"  , required_argument , NULL , 's'},
        {0          , 0                 , 0    ,  0 },
    };

    // Verifica a corretude dos comandos digitados
    while ( (opt = getopt_long(argc, argv, "hs:", longopts, NULL)) > 0 )
    {
        switch ( opt )
        {
            case 'h': /* -h ou --help */
                showHelp(argv[0]);
                break;
            case 's': /* -s ou --send */
                if(strlen(optarg) >= INET6_ADDRSTRLEN)
                {
                    fprintf(stderr, "Erro: endereco de destino muito grande\n");
                    exit(EXIT_FAILURE);
                }
                    strcpy(serverAddress, optarg); // coloca endereco escolhido pelo usuario na string 'server'
                if(argv[optind] == NULL)
                {
                    printf("Erro: argumento [ARQUIVO] nao encontrado\nEncerrando aplicacao...\n");
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                fprintf(stderr, "Erro: opcao invalida ou faltando argumento: '%c'\n", optopt);
                exit(EXIT_FAILURE);
        }
    }

    // CRIA E CONFIGURA SOCKET CLIENTE //

    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 

    // socket create and varification
    sockfd = criaSocket();

    // assign IP, PORT 
    servaddr = defineEndereco("127.0.0.1");

    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
    { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
    {
        printf("connected to the server..\n"); 
    }

    // function for chat 
    func(sockfd); 

    // close the socket 
    close(sockfd); 

    /////////////////////////////////////

    while ( argv[optind] != NULL )
    {
        struct stat s ;
        if ( stat(argv[optind], &s) == -1 )
        {
            printf("Erro em arquivo \"%s\": %s\n", argv[optind], strerror(errno));
            ++optind;
            continue;
        }
        if( enviarArquivo(argv[optind], serverAddress, s.st_blocks) )
        {
           printf("Arquivo \"%s\" transmitido com sucesso!\n", argv[optind]);
        }
        else
        {
           fprintf(stderr, "Erro: falha na transmissao do arquivo \"%s\"\n", argv[optind]);
        }
        ++optind;
    }
    return 0;
}

void showHelp(char *nome)
{
    fprintf(stderr, "##### USO DE %s #####\n\n### MOSTRAR O HELPER ###\n"
        "-h (ou --help ou --ajuda)\n\n"
        "### ENVIAR ARQUIVOS AO ENDERECO ###\n"
        "-s (ou --send ou --enviar) ENDERECO [ARQUIVO_1] [ARQUIVO_2] ... [ARQUIVO_N]\n", nome);
    exit(EXIT_FAILURE);
}

void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    for (;;)
    { 
        bzero(buff, sizeof(buff)); 
        printf("Enter the string : "); 
        n = 0; 
        
        while ((buff[n++] = getchar()) != '\n');

        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 
        
        if ((strncmp(buff, "exit", 4)) == 0)
        { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 