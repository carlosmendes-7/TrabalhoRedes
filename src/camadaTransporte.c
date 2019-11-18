#include "../include/camadaTransporte.h"
#include "../include/camadaRede.h"
#include "../include/camadaAplicacao.h"

void enviaSegmento(int sockfd, FILE *fp, char *sendline, int n, int contSegmento, int maxLine, ssize_t *total, IPs ips)
{
	Transporte transporte;
	transporte.identificadorSegmento = contSegmento;
	transporte.checksumSegmento = transporte.identificadorSegmento*2;

	enviaDatagrama(sockfd, fp, sendline, n, maxLine, total, transporte, ips);

	//printf("IP CLIENTE: %s\tIP SERVIDOR: %s\n", ips.ipCliente, ips.ipServidor);
 	//printf("ID SEGMENTO: %d\tCHEKSUM: %d\n", identificacaoSegmento, cheksum);
 	//printf("IP CLIENTE: %s\tIP SERVIDOR: %s\n", ipCliente, ipServidor);
}