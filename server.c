#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_LEN 1024

void exit_funct(int listenSock)
{
    close(listenSock);
    exit(0);
}

int main(int argc, char **argv)
{
    int port = 8080;
    char buf[BUF_LEN];
    struct sockaddr_in serverSockAddr;

    signal(SIGINT, exit_funct); // Ctrl+C

    // Created a main server socket
    int listenSock = socket(AF_INET, SOCK_STREAM, 0);
    
    serverSockAddr.sin_family = AF_INET;
    serverSockAddr.sin_port = htons(port);
    serverSockAddr.sin_addr.s_addr = INADDR_ANY;

    // Associated an address whith the socket
    if(bind(listenSock, (struct sockaddr*) &serverSockAddr, sizeof(serverSockAddr)) != 0)
    {
        printf("Error bind\n");
        return 1;
    }

    // Listening to the server port
    if(listen(listenSock, 5) != 0)
    {
        printf("Error listen\n");
        return 1;
    }
    printf("Server listen ...\n");
    
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Receiving a connection from a client
    int clientSock = accept(listenSock, (struct sockaddr*) &clientAddr, &clientAddrLen);
    if(clientSock == -1)
    {
        printf("Error accept\n");
        return 1;
    }

    // Communication with the client in the loop
    while(1)
    {
        if(recv(clientSock, buf, sizeof(buf), 0) <= 0)
        {
            printf("Error reading of client message\n");
            clientSock = accept(listenSock, (struct sockaddr*) &clientAddr, &clientAddrLen);
            if(clientSock == -1)
            {
                printf("Error accept\n");
                return 1;
            }
            if(recv(clientSock, buf, sizeof(buf), 0) <= 0)
            {
                printf("Error reading of client message\n");
                return 1;
            }
        }

        printf("Client say >> %s", buf);

        if(send(clientSock, buf, sizeof(buf), 0) == -1)
        {
            printf("Error send message from client\n");
            return 1;
        }
        
    }

    return 0;
}
