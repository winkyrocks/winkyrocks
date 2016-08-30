#include <stdio.h>
#include <stdlib.h>

typedef struct NodeType
{
    int val;
    struct NodeType *next;
} Node;

Node* build_linked_list(int capacity)
{
    Node *next = NULL;
    for (int i = capacity - 1; i >= 0; --i)
    {
        Node *node = malloc(sizeof(Node));
        node->val = i;
        node->next = (next != NULL) ? next : NULL;

        next = node;
    }

    return next;
}

void print_linked_list(Node *head)
{
    printf("Head");
    for (Node *cur = head; cur != NULL; cur = cur->next)
        printf("(%d) -> ", cur->val);

    printf("NULL\n");
}

void free_linked_list(Node *head)
{
    Node *cur = head;
    while (cur != NULL)
    {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
}

void interleave_linked_list(Node *head)
{
    Node *slow = head;
    Node *fast = head;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node *tail = slow->next;
    slow->next = NULL;
    Node *cur =  tail->next;
    tail->next = NULL;
    while (cur != NULL)
    {
        Node *next = cur->next;
        cur->next = tail;
        tail = cur;
        cur = next;
    }

    while (tail != NULL)
    {
        Node *next = head->next;
        head->next = tail;
        tail = tail->next;
        head->next->next = next;
        head = next;
    }
}

int main()
{
    Node *head = build_linked_list(10);
    print_linked_list(head);

    interleave_linked_list(head);
    print_linked_list(head);

    free_linked_list(head);
    return 0;
}
