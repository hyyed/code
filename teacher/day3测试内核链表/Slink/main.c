#include <stdio.h>
#include "slink.h"
int main(void)
{
    struct SLink* head = createNode(0);

    for(int i=0; i<5; i++)
    {
        int data = random()%100;
        struct SLink* node = createNode(data);
        insertNode(head, node);
    }

    displayNode(head);

    int d = 0;
    scanf("%d", &d);
    struct SLink* dnode = indexOf(head, d);
    if(dnode != NULL)
    {
        deleteNode(dnode);
    }
    displayNode(head);

    destroyNode(head);
}