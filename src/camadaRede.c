/*Equipe:
 * Antonio Carlos Couto Oliveira
 * Caique de Souza Silva
 * Carlos Frederico D'Almeida e Mendes
 * Danilo de Andrade Peleteiro
 * Rafael Barretto Serejo Farias
 * Vinicius Aragao Nascimento
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

    printf("[CAMADA DE REDE]\n");
    printf("IP ORIGEM: %s\nIP DESTINO: %s\n", ips.ipCliente, ips.ipServidor);
    enviaQuadro(sockfd, fp, sendline, n, maxLine, total, rede);    
}
