/*Equipe:
 * Antonio Carlos Couto Oliveira
 * Caique de Souza Silva
 * Carlos Frederico D'Almeida e Mendes
 * Danilo de Andrade Peleteiro
 * Rafael Barretto Serejo Farias
 * Vinicius Aragao Nascimento
 */

#include "../include/camadaTransporte.h"
#include "../include/camadaRede.h"
#include "../include/camadaAplicacao.h"

void enviaSegmento(int sockfd, FILE *fp, char *sendline, int n, int contSegmento, int maxLine, ssize_t *total, IPs ips)
{
	Transporte transporte;
	transporte.identificadorSegmento = contSegmento;
	transporte.checksumSegmento = transporte.identificadorSegmento*2;

	printf("[CAMADA DE TRANSPORTE]\n");
 	printf("ID SEGMENTO: %d\nCHECKSUM: %d\n", transporte.identificadorSegmento, transporte.checksumSegmento);
	enviaDatagrama(sockfd, fp, sendline, n, maxLine, total, transporte, ips);	
}
