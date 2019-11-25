#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_LEN 1024

void exit_funct(int sock)
{
    close(sock);
    exit(0);
}

int main(int argc, char **argv)
{
    int port = 8080;
    char buf[BUF_LEN];
    signal(SIGINT, exit_funct); // Ctrl+C
    
    // Create a main socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Fill server address data
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if(!inet_aton("127.0.0.1", &(serverAddr.sin_addr)))
    {
        printf("Error: IP-adress non valid\n");
        return 1;
    }
    
    // Connect to the server
    if(connect(sock, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) != 0)
    {
        printf("Error connect\n");
        return 1;
    }

    while(1)
    {
        printf(">> ");
        fgets(buf, BUF_LEN, stdin);
        send(sock, buf, BUF_LEN, 0);
        sleep(1);
    }

    return 0;
}
