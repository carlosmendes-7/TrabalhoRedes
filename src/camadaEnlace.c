/*Equipe:
 * Carlos Frederico D'Almeida e Mendes
 * Danilo de Andrade Peleteiro
 *
 *
 *
 */
#include "../include/camadaEnlace.h"
#include "../include/camadaTransporte.h"
#include "../include/camadaAplicacao.h"
#include "../include/camadaRede.h"

Enlace enlaceTestado;

void enviaQuadro(int sockfd, FILE *fp, char *sendline, int n, int maxLine, ssize_t *total, Rede rede)
{
    Enlace enlace;
    enlace.rede = rede;
    enlace.macOrigem = "";
    enlace.macDestino = "";
    
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
<<<<<<< HEAD
    enlaceTestado = enlace;
}

void verificaQuadro()
{
    printf("%d\n", enlaceTestado.rede.transporte.identificadorSegmento);
}
=======
}
>>>>>>> f4aed2585cf3d9a55362d508d148137e7d951ad7
