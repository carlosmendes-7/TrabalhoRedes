#include "../include/camadaTransporte.h"

void enviaSegmento(int sockfd, FILE *fp, char *sendline, int n, int contSegmento, int maxLine, ssize_t *total)
{
	int identificacaoSegmento = contSegmento;
	int cheksum = identificacaoSegmento*2;
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
 	printf("ID SEGMENTO: %d\tCHEKSUM: %d\n", identificacaoSegmento, cheksum);
}