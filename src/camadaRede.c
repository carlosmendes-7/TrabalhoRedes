/*Equipe:
 * Carlos Frederico D'Almeida e Mendes
 * Danilo de Andrade Peleteiro
 *
 *
 *
 */
#include "../include/camadaRede.h"
#include "../include/camadaTransporte.h"
#include "../include/camadaAplicacao.h"
#include "../include/camadaEnlace.h"

void enviaDatagrama(int sockfd, FILE *fp, char *sendline, int n, int maxLine, ssize_t *total, Transporte transporte, IPs ips)
{
	
    Rede rede;
    rede.transporte = transporte;
    rede.ips = ips;

    enviaQuadro(sockfd, fp, sendline, n, maxLine, total, rede);
    
    printf("%d\t%d\n", transporte.identificadorSegmento, transporte.checksumSegmento);
}
