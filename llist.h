#include <sys/socket.h>
//#include <netinet/in.h>
#include <malloc.h>

struct LNode
{
    int socket;
    char *name;
    struct LNode *next;
};

struct LNode *pushLNode(struct LNode *head, int socket, char *name);
