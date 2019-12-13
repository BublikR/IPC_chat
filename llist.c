#include "llist.h"

// Ceate a linked list head or new node.
// Set the first parameter "NULL", if you create the head.
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

// Delete one node by name
int delLNode(struct LNode *head, char *name)
{
    struct LNode *previous = NULL;

    while(head->next != NULL)
    {
        previous = head;
        head = head->next;

        if(head->name == name)
        {
            previous->next = head->next;
            free(head);
            return 0;
        }
    }
    return -1;
}

// Clear all list
void clearAllLNodes(struct LNode *head)
{
    struct LNode *node = NULL;
    while(head->next != NULL)
    {
        node = head;
        head = head->next;
        free(node);
    }
    free(head);
}
