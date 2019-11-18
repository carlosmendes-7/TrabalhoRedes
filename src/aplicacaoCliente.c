/*TODO
deixar server aberto
dissociar camada de aplicacao da app
procurar lib para segmentacao
multiplos clientes
interface gráfica
*/

#include "../include/socketHandler.h"
#include "../include/camadaTransporte.h"
#include "../include/camadaAplicacao.h"

void showHelp(char *nome);

ssize_t total=0;

int main(int argc, char *argv[])
{

    // INET6_ADDRSTRLEN = 46 bytes
    char serverAddress[INET6_ADDRSTRLEN] = "";

    // Mostra helper caso usuario nao defina nenhuma acao apos execucao do programa(-h ou -s)
    if (argc < 2)
    {
        showHelp(argv[0]); 
    }

    // Cria vetor de struct para opcoes que usuario escolhera
    const struct option longopts[] =
    {
        {"help"     , no_argument       , NULL , 'h'},
        {"ajuda"    , no_argument       , NULL , 'h'},
        {"send"   , required_argument , NULL , 's'},
        {"enviar"  , required_argument , NULL , 's'},
        {0          , 0                 , 0    ,  0 },
    };

    // Verifica a corretude dos comandos digitados
    int opt;
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
                strcpy(serverAddress, optarg); // coloca endereco escolhido pelo usuario na string 'serverAddress'
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

    ////////// Acoes para o Socket //////////

    int sockfd, connfd; 
    struct sockaddr_in servaddr, clientaddr; 

    // Verifica e cria socket
    sockfd = criaSocket();

    // Define Endereco e porta
    servaddr = defineEndereco(serverAddress, 1);

    // Tentativa de estabelecer conexao com o servidor para envio de arquivo [CAMADA DE APLICACAO]
    conectarClienteAoServidor(sockfd, &servaddr);

    ////////// Acoes referentes ao Arquivo //////////

    char *filename = basename(argv[3]); // nome do arquivo dado pelo usuário
    FILE *fp = fopen(argv[3], "rb"); // tentativa de abrir o arquivo  
    char buff[BUFFSIZE] = {0};

    verificaArquivo(sockfd, fp, buff, BUFFSIZE, filename); // Verifica se Arquivo Existe e envia Path para o socket

    enviarArquivo(fp, sockfd, &total);

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
        if( /*enviarArquivo(argv[optind], serverAddress, s.st_blocks)*/ 1 )
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
        "-s (ou --send ou --enviar) ENDERECO NOMEDOARQUIVO\n", nome);
    exit(EXIT_FAILURE);
}