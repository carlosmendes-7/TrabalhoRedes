#include "socketHandler.h"
#include "transporte.h"

void showHelp(char *nome);
void conectarClienteAoServidor(int sockfd, struct sockaddr_in *servaddr);
void sendfile(FILE *fp, int sockfd);

ssize_t total=0;

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
    struct sockaddr_in servaddr, clientaddr; 

    // Verifica e cria socket
    sockfd = criaSocket();

    // Define Endereco e porta
    servaddr = defineEndereco(serverAddress, 1);

    // Tentativa de estabelecer conexao com o servidor para envio de arquivo
    //conectarClienteAoServidor(sockfd, &servaddr);
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
    { 
        printf("Conexão com o servidor falhou...\nEncerrando aplicacao...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Conectado ao servidor!\n"); 
    }

    // ARQUIVO //
    char *filename = basename(argv[3]); // abrindo argumento referente ao arquivo. precisa generalizar 
    if (filename == NULL)
    {
        perror("Can't get filename");
        exit(1);
    }

    char buff[BUFFSIZE] = {0};
    strncpy(buff, filename, strlen(filename));
    if (send(sockfd, buff, BUFFSIZE, 0) == -1)
    {
        perror("Can't send filename");
        exit(1);
    }
    
    FILE *fp = fopen(argv[3], "rb");
    if (fp == NULL) 
    {
        perror("Can't open file");
        exit(1);
    }

    sendfile(fp, sockfd);
    printf("Envio realizado com sucesso! Numero de Bytes = %ld\n", total);

    // Fechando arquivo
    fclose(fp);

    // Fechando socket
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

void conectarClienteAoServidor(int sockfd, struct sockaddr_in *servaddr)
{
    if (connect(sockfd, (SA*)servaddr, sizeof(servaddr)) != 0)
    { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
    {
        printf("connected to the server..\n"); 
    }
}

void sendfile(FILE *fp, int sockfd) 
{
    int n; 
    char sendline[MAX_LINE] = {0}; 
    while ((n = fread(sendline, sizeof(char), MAX_LINE, fp)) > 0) 
    {
        total+=n;
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
}