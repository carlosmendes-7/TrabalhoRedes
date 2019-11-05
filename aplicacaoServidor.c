#include "socketHandler.h"
#include "transporte.h"

void func(int sockfd);
void writefile(int sockfd, FILE *fp);

ssize_t total=0;

int main(int argc, char *argv[])
{
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, clientaddr; 
  
    // socket create and verification 
    sockfd = criaSocket();

    // assign IP, PORT 
    servaddr = defineEndereco("127.0.0.1");

    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
    { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Socket successfully binded..\n"); 
    }
  
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0)
    { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Server listening..\n"); 
    }

    len = sizeof(clientaddr); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&clientaddr, &len); 
    if (connfd < 0)
    { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
    {
        printf("server acccept the client...\n");
    }

    // ARQUIVO //
    char filename[BUFFSIZE] = {0}; 
    if (recv(connfd, filename, BUFFSIZE, 0) == -1) 
    {
        perror("Can't receive filename");
        exit(1);
    }

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) 
    {
        perror("Can't open file");
        exit(1);
    }
    
    char addr[INET_ADDRSTRLEN];
    printf("Start receive file: %s from %s\n", filename, inet_ntop(AF_INET, &clientaddr.sin_addr, addr, INET_ADDRSTRLEN));
    writefile(connfd, fp);
    printf("Receive Success, NumBytes = %ld\n", total);
    fclose(fp);

    // Function for chatting between client and server 
    //func(connfd); 
  
    // After chatting close the socket 
    close(sockfd); 
}

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    // infinite loop for chat 
    for (;;)
    { 
        bzero(buff, MAX); 
  
        // read the message from client and copy it in buffer 
        read(sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : ", buff); 
        bzero(buff, MAX); 
        n = 0; 
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n'); 
  
        // and send that buffer to client 
        write(sockfd, buff, sizeof(buff)); 
  
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0)
        { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
} 

void writefile(int sockfd, FILE *fp)
{
    ssize_t n;
    char buff[MAX_LINE] = {0};
    while ((n = recv(sockfd, buff, MAX_LINE, 0)) > 0) 
    {
        total+=n;
        if (n == -1)
        {
            perror("Receive File Error");
            exit(1);
        }
        
        if (fwrite(buff, sizeof(char), n, fp) != n)
        {
            perror("Write File Error");
            exit(1);
        }
        memset(buff, 0, MAX_LINE);
    }
}