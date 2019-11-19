/*TODO
deixar server aberto
multiplos clientes
interface gráfica
*/

#include "../include/socketHandler.h"
#include "../include/camadaAplicacao.h"
#include "../include/camadaTransporte.h"

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

    printf("%s\n", serverAddress);
    // Tentativa de estabelecer conexao com o servidor para envio de arquivo [CAMADA DE APLICACAO]
    conectarClienteAoServidor(sockfd, &servaddr);

    ////////// Acoes referentes ao Arquivo //////////
    char inputFilePath[256];
    printf("Digite o path e nome do arquivo que deseja enviar: ");
    scanf("%s", inputFilePath);
    char *filename = basename(inputFilePath); // nome do arquivo dado pelo usuário
    FILE *fp = fopen(inputFilePath, "rb"); // tentativa de abrir o arquivo  
    char buff[BUFFSIZE] = {0};

    verificaArquivo(sockfd, fp, buff, BUFFSIZE, filename); // Verifica se Arquivo Existe e envia Path para o socket
    
    IPs ips;
    ips.ipCliente = "127.0.0.1";
    ips.ipServidor = serverAddress;
    enviarArquivo(fp, sockfd, &total, ips);

    // Fechando arquivo
    fclose(fp);

    // Fechando socket
    close(sockfd); 

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