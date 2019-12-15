#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "llist.h"

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
    char name[80];
    struct sockaddr_in serverSockAddr;
    struct LNode *client = NULL;

    signal(SIGINT, exit_funct); // Ctrl+C

    // Created a main server socket
    int listenSock = socket(AF_INET, SOCK_STREAM, 0);
    
    // Created a linked list head. Save the sokets information in it.
    // Store the main server socket information in the linked list head.
    struct LNode* head = pushLNode(NULL, listenSock, "SERVER");

    serverSockAddr.sin_family = AF_INET;
    serverSockAddr.sin_port = htons(port);
    serverSockAddr.sin_addr.s_addr = INADDR_ANY;

    // Associated an address whith the socket
    if(bind(listenSock, (struct sockaddr*) &serverSockAddr, sizeof(serverSockAddr)) != 0)
    {
        printf("Error bind\n");
        return 2;
    }

    // Listening to the server port
    if(listen(listenSock, 5) != 0)
    {
        printf("Error listen\n");
        return 3;
    }
    printf("Server listen ...\n");

    // Communication with the client in the loop
    while(1)
    {
        fd_set readfds;
        int max_d = listenSock;

        FD_ZERO(&readfds);
        FD_SET(listenSock, &readfds);
        
        client = head;
        while(client->next)
        {
            client = client->next;
            FD_SET(client->socket, &readfds);
            if(client->socket > max_d)
                max_d = client->socket;
        }
        
        if(select(max_d+1, &readfds, NULL, NULL, NULL) < 1)
        {
            printf("Error select\n");
            return 4;
        }
        
        // Received a new connection request
        if(FD_ISSET(listenSock, &readfds))
        {
            int clientSock = accept(listenSock, NULL, NULL);
            if(clientSock == -1)
            {
                printf("Error accept\n");
                return 5;
            }
            // Save new client descriptor
            sprintf(name, "%d", clientSock);
            pushLNode(head, clientSock, name);
        }
        
        client = head;
        while(client->next)
        {
            client = client->next;
            if(FD_ISSET(client->socket, &readfds))
            {
                int client_recv = recv(client->socket, buf, sizeof(buf), 0);
                if(client_recv == -1)
                {
                    printf("Error reading of client %s message\n", client->name);
                    return 6;
                }
                else if(client_recv == 0) // Client exit
                {
                    printf("Client %s left the chat\n", client->name);
                    close(client->socket); // Close this client socket
                    delLNode(head, client->name); // Delete client
                }
                else
                    printf("Client %s say >> %s", client->name, buf);

                struct LNode *recipient = head;
                while(recipient->next)
                {
                    recipient = recipient->next;
                    if(send(recipient->socket, buf, sizeof(buf), 0) == -1)
                    {
                        printf("Error send message from client %s\n", recipient->name);
                        return 7;
                    }
                }
            }
        }
    }
    return 0;
}
