#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_funct(int listenSock)
{
    close(listenSock);
    exit(0);
}

int main(int argc, char **argv)
{
    int port = 8080;
    struct sockaddr_in serverSockAddr;

    signal(SIGINT, exit_funct);

    int listenSock = socket(AF_INET, SOCK_STREAM, 0);
    
    serverSockAddr.sin_family = AF_INET;
    serverSockAddr.sin_port = htons(port);
    serverSockAddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(listenSock, (struct sockaddr*) &serverSockAddr, sizeof(serverSockAddr)) != 0)
    {
        printf("Error bind\n");
        return 1;
    }

    if(listen(listenSock, 5) != 0)
    {
        printf("Error listen\n");
        return 1;
    }
    printf("Server listen ...\n");
    
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    int clientSock = accept(listenSock, (struct sockaddr*) &clientAddr, &clientAddrLen);
    if(clientSock == -1)
    {
        printf("Error accept\n");
        return 1;
    }

    while(1)
    {
        printf("Server runing\n");
        sleep(1);
    }

    return 0;
}
