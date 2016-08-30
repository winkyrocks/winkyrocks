#include <stdio.h>
#include <stdlib.h>

typedef struct NodeType
{
    int value;
    int left_size;
    struct NodeType *left;
    struct NodeType *right;
} Node, *PNode;

void insert_node(Node** root, int x)
{
    if (*root == NULL)
    {
        Node *p = (Node*) malloc(sizeof(Node));
        p->value = x;
        p->left_size = 0;
        p->left = NULL;
        p->right = NULL;

        *root = p;
    }
    else if (x < (*root)->value)
    {
        insert_node(&(*root)->left, x);
        ++(*root)->left_size;
    }
    else
    {
        insert_node(&(*root)->right, x);
    }
}

int getRank(int x, Node *root)
{
    if (root == NULL) return -1;

    if (x == root->value)
    {
        return root->left_size;
    }
    else if (x < root->value)
    {
        return getRank(x, root->left);
    }
    else
    {
        return root->left_size + 1 + getRank(x, root->right);
    }
}

Node *build_binary_tree(int *array, int count)
{
    if (count == 0) return NULL;

    Node *root = NULL;

    for (int i = 0; i < count; ++i)
    {
        insert_node(&root, array[i]);
    }

    return root;
}

void traverse_binary_tree(Node *root)
{
    if (root == NULL) return;

    printf("(%d, %d(%d), %d) ",root->left == NULL ? -1 : root->left->value,  root->value, root->left_size, root->right == NULL ? -1 : root->right->value);
    traverse_binary_tree(root->left);
    traverse_binary_tree(root->right);
}

void link_binary_tree(Node *root, Node** pre)
{
    if (root == NULL) return;

    link_binary_tree(root->left, pre);
    printf("%d(%d) ", root->value, *pre == NULL ? -1 : (*pre)->value);
    *pre = root;
    link_binary_tree(root->right, pre);
}

void dispose_binary_tree(Node *root)
{
    if (root == NULL) return;

    dispose_binary_tree(root->left);
    dispose_binary_tree(root->right);
    printf("DEL %d ", root->value);
    free(root);
}

int main()
{
    int intArray[10] = { 15, 10, 12, 20, 25, 30, 4, 5, 7, 13 };

    Node *root = build_binary_tree(intArray, 10);

    traverse_binary_tree(root);
    printf("\n");

    Node *pre = NULL;
    link_binary_tree(root, &pre);
    printf("\n");

    for (int i = 0; i < sizeof(intArray)/sizeof(int); ++i)
    {
        printf("GetRank(%d)=%d\n", intArray[i], getRank(intArray[i], root));
    }

    dispose_binary_tree(root);
    return 0;
}
