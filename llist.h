#include <malloc.h>

struct LNode
{
    int socket;
    char *name;
    struct LNode *next;
};

struct LNode *pushLNode(struct LNode *head, int socket, char *name);
int delLNode(struct LNode *head, char *name);
void clearAllLNodes(struct LNode *head);
