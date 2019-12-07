/*Equipe:
 * Antonio Carlos Couto Oliveira
 * Caique de Souza Silva
 * Carlos Frederico D'Almeida e Mendes
 * Danilo de Andrade Peleteiro
 * Rafael Barretto Serejo Farias
 * Vinicius Aragao Nascimento
 */

#include "../include/camadaEnlace.h"
#include "../include/camadaTransporte.h"
#include "../include/camadaAplicacao.h"
#include "../include/camadaRede.h"

void enviaQuadro(int sockfd, FILE *fp, char *sendline, int n, int maxLine, ssize_t *total, Rede rede)
{
    Enlace enlace;
    enlace.rede = rede;
    enlace.macOrigem = "8E:2A:9F";
    enlace.macDestino = "8E:2A:9F";
    
    if(*total==8)
    {
        printf("[CAMADA DE ENLACE]\n");
        printf("MAC ORIGEM: %s\nMAC DESTINO: %s\n", enlace.macOrigem, enlace.macDestino);
    }

	*total+=n;
	if (n != maxLine && ferror(fp))
    {
        perror("Read File Error");
        exit(1);
    }
    
    if (send(sockfd, sendline, n, 0) == -1)
    {
        perror("Can't send file");
        exit(1);
    }
    memset(sendline, 0, maxLine);
}