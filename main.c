#include <stdio.h>
#include <stdlib.h> /*exit()*/
#include <string.h> /*strlen()*/
#include <errno.h> /*error handling*/
#include <unistd.h> /*parse command-line options*/
#include <getopt.h> /*parse command-line options*/
#include <sys/types.h> /*stat()*/
#include <sys/stat.h> /*stat()*/
#include <netinet/in.h> /*INET6_ADDRSTRLEN*/
#include "transporte.h"

void showHelp(char *nome){
	fprintf(stderr, "##### USO DE %s #####\n\n### MOSTRAR O HELPER ###\n"
        "-h (ou --help ou --ajuda)\n\n"
        "### ENVIAR ARQUIVOS AO ENDERECO ###\n"
        "-s (ou --send ou --enviar) ENDERECO [ARQUIVO_1] [ARQUIVO_2] ... [ARQUIVO_N]\n", nome);
    exit(EXIT_FAILURE);
}

void bemVindoAoPrograma(){
    printf("##### Seja bem-vindo a Aplicacao de Transferencia de Arquivos ######\n");
    printf("### Para saber mais, digite 'about'. Caso queira iniciar a Transferencia, digite 'iniciar' ###\n");
}

void inputInicialUsuario(){
    char endereco[100000];
    printf("Digite o endereco para realizar a transferencia: ");
    while(1)
    {
        scanf("%s", endereco);
        if(endereco.size()>=INET6_ADDRSTRLEN)
        {
            printf("Erro! Tamanho do endereco maior que o comportado. Digite um novo endereco: ");
            continue
        }
        break;
    }

    printf("Digite a quantidade de arquivos que deseja transferir(máximo de 5): ");
    int qtd_arquivos;
    while(1)
    {
        scanf("%d", qtd_arquivos);
        if(qtd_arquivos<=0 || qtd_arquivos>=5)
        {
            printf("Erro! Entrada incorreta ou quantidade solicitada inviável (1 até 5 arquivos). Digite uma nova entrada: ");
            continue;
        }
        break;
    }
    char arquivos[qtd_arquivos][100000];
    for(int i=0;i<qtd_arquivos;i++)
    {
        scanf("%s",arquivos[i]);
        while(1)
        {
            if()
            scanf("%s", )
        }
    }
}

int main(int argc, char *argv[]){

    bemVindoAoPrograma(); // Função de cumprimento
    inputInicialUsuario();


	/* char server[INET6_ADDRSTRLEN] = ""; // INET6_ADDRSTRLEN = 46 bytes
	int rc = 0; variavel que recebe o retorno das chamadas de funcao

	if (argc < 2) {
        show_help(argv[0]); // Mostra helper caso usuario nao defina nenhuma acao apos execucao do programa(-h ou -s)
    }

	int opt;
	const struct option longopts[] = {
        {"help"     , no_argument       , NULL , 'h'},
        {"ajuda"    , no_argument       , NULL , 'h'},
        {"send"   , required_argument , NULL , 's'},
        {"enviar"  , required_argument , NULL , 's'},
        {0          , 0                 , 0    ,  0 },
	} ;

	while ( (opt = getopt_long(argc, argv, "hs:", longopts, NULL)) > 0 ) {
		switch ( opt ) {
        case 'h': /* -h ou --help 
            show_help(argv[0]);
            break ;
        case 's': /* -s ou --send 
            if(strlen(optarg) >= INET6_ADDRSTRLEN){
            	fprintf(stderr, "Erro: endereco de destino muito grande\n") ;
            	exit(EXIT_FAILURE);
            }
            strcpy(server, optarg); // coloca endereco escolhido pelo usuario na string 'server'

            if(argv[optind] == NULL)
            {
                printf("Erro: falta argumento [ARQUIVO]\nEncerrando aplicacao...\n");
                exit(EXIT_FAILURE);
            }

            break ;
        default:
            fprintf(stderr, "Erro: opcao invalida ou faltando argumento: '%c'\n", optopt) ;
            exit(EXIT_FAILURE); 
		}
	}


	while ( argv[optind] != NULL ) {
		struct stat s ;
        if ( stat(argv[optind], &s) == -1 ){
        	printf("Erro em arquivo \"%s\": %s\n", argv[optind], strerror(errno));
        	++optind;
        	continue;
        }
        if( enviarArquivo(argv[optind], server, s.st_blocks) >= 0 ) {
        	printf("Arquivo \"%s\" transmitido com sucesso!\n", argv[optind]);
        }else{
        	fprintf(stderr, "Erro: falha na transmissao do arquivo \"%s\"\n", argv[optind]);
        }
        ++optind;
    }*/

	return 0;
}