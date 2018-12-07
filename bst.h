#ifndef BST_H
#define BST_H

typedef struct Data
{
    int value;
}Data;

typedef struct Node
{
    struct Node *left;
    struct Node *right;
    Data data;
    struct Node *parent;
}Node;

typedef struct Tree
{
    struct Node *root;
    Data * (*insert)(struct Tree *, Data);
    void (*sort)(struct Tree *, Data *);
    Data * (*search)(struct Tree *, Data);
    struct Tree * (*clone)(struct Tree*);
    int (*compare)(struct Tree *,struct Tree *);
    void (*removeData)(struct Tree *, Data);
    void (*delete)(struct Tree *);
}Tree;

Tree * newTree();

Node * newNode(Data,Node *);

#endif