#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void exit_funct(int sock)
{
    close(sock);
    exit(0);
}

int main(int argc, char **argv)
{
    int port = 8080;
    signal(SIGINT, exit_funct);
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if(!inet_aton("127.0.0.1", &(serverAddr.sin_addr)))
    {
        printf("Error: IP-adress non valid\n");
        return 1;
    }
    
    if(connect(sock, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) != 0)
    {
        printf("Error connect\n");
        return 1;
    }

    return 0;
}
