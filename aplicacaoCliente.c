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

void show_help(char *nome){
	fprintf(stderr, "Uso: %s -d ENDERECO [ARQUIVOS]...\n", nome);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	char server[INET6_ADDRSTRLEN] = "";
	int rc = 0; /*variavel que recebe o retorno das chamadas de funcao*/

	if (argc < 3) {
        show_help(argv[0]);
    }

	int opt;
	const struct option longopts[] = {
        {"help"     , no_argument       , NULL , 'h'},
        {"ajuda"    , no_argument       , NULL , 'h'},
        {"adress"   , required_argument , NULL , 'd'},
        {"endereco" , required_argument , NULL , 'd'},
        {"destino"  , required_argument , NULL , 'd'},
        {0          , 0                 , 0    ,  0 },
	} ;

	while ( (opt = getopt_long(argc, argv, "hd:", longopts, NULL)) > 0 ) {
		switch ( opt ) {
        case 'h': /* -h ou --help */
            show_help(argv[0]);
            break ;
        case 'd': /* -d ou --destino */
            if(strlen(optarg) >= INET6_ADDRSTRLEN){
            	fprintf(stderr, "Erro: endereco de destino muito grande\n") ;
            	exit(EXIT_FAILURE);
            }
            strcpy(server, optarg);
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
    }

	return 0;
}