#include "../include/camadaRede.h"
#include "../include/camadaTransporte.h"
#include "../include/camadaAplicacao.h"

void enviaDatagrama(int sockfd, FILE *fp, char *sendline, int n, int maxLine, ssize_t *total, Transporte transporte, IPs ips)
{
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

    printf("%d\t%d\n", transporte.identificadorSegmento, transporte.checksumSegmento);
}