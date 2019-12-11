#include "llist.h"

struct LNode *pushLNode(struct LNode *head, int socket, char *name)
{
    struct LNode *new_node = (struct LNode*) malloc(sizeof(struct LNode));
    new_node->socket = socket;
    new_node->name = name;
    new_node->next = NULL;

    if(head == NULL)
    {
        head = new_node;
        return head;
    }
    else
        while(head->next != NULL)
            head = head->next;
        head->next = new_node;
        return head;
}
