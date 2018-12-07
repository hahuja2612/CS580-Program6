#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "bst.h"


Node * newNode(Data data,Node *parent)
{
    Node *node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->data = data;
    return node;
}



Data * searchNode(Node *n,Data d)
{
    if (n->data.value == d.value)
    {
        return &(n->data);
    }
    else if (n->data.value < d.value)
    {
        if(n->right == NULL)
        {
             NULL;
        }
        else
        {
             searchNode(n->right,d);
        }
    }
    else if (n->data.value > d.value)
    {
        if(n->left == NULL)
        {
            NULL;
        }
        else
        {
             searchNode(n->left,d);
        }
    }
}

Data * insertNode(Node *n,Data d)
{
    if (n->data.value < d.value)
    {
        if(n->right == NULL)
        {
            n->right = malloc(sizeof(Node));
            n->right->left = n->right->right = NULL;
            n->right->parent = n;
            n->right->data = d;
        }
        else
        {
            insertNode(n->right,d);
        }
    }
    else if (n->data.value > d.value)
    {
        if(n->left == NULL)
        {
            n->left = malloc(sizeof(Node));
            n->left->left = n->left->right = NULL;
            n->left->parent = n;
            n->left->data = d;
        }
        else
        {
            insertNode(n->left,d);
        }
    }
    else if (n->data.value == d.value)
    {
      return NULL;
    }

}

Data * search(Tree* bst,Data value)
{
    if (bst->root == NULL)
    {
        return NULL;
    }

    else
        {
          searchNode(bst->root,value);
        }

}

Data * insertTree(Tree* bst,Data value)
{
    if (bst->root == NULL)
    {
        bst->root = malloc(sizeof(Tree));
        bst->root->data=value;
        bst->root->left = NULL;
        bst->root->right = NULL;
        bst->root->parent = NULL;
    }
    else
        {
         insertNode(bst->root,value);
        }

}

int d1[30];
int c1 = 0;
int d2[30];
int c2 = 0;
int d3[30];
int c3 = 0;

Data * cloneTree(Node* n)
{
   if (n != NULL)
    {
       d1[c1] = n->data.value;
       c1 = c1 + 1 ;
    
    cloneTree(n->left);
    cloneTree(n->right);}
}
Tree * clone(Tree* bst)
{
    cloneTree(bst->root);
    int i;
    Tree *bst2 = newTree();
    for (i = 0; i < c1; i++){

		insertTree(bst2, (Data){d1[i]});
	}
	return bst2;
}
Data * Tree1(Node* n)
{
   if (n != NULL)
    {
       d2[c2] = n->data.value;
       c2 = c2 + 1 ;
    }
    if (n != NULL)
    {
    Tree1(n->left);
    Tree1(n->right);}
}
Data * Tree2(Node* n)
{
   if (n != NULL)
    {
       d3[c3] = n->data.value;
       c3 = c3 + 1 ;
    }
    if (n != NULL)
    {
    Tree2(n->left);
    Tree2(n->right);}
}
int compare(Tree *t, Tree * copy)
{
    if (t == NULL || copy == NULL)
    {
        return 0;
    }
     c3 = 0;

     c2 = 0;
    Tree1(t->root);
    Tree2(copy->root);
    int i;
    for (i = 0; i < c2; i++)
    {
        if (d3[i] != d2[i])
        {
            return 0;
        }
	}
	return 1;
}
int x=0;
void traverse (Tree* bst,Node * n,Data *array)
{
    if (n != NULL)
    {
        traverse(bst,n->left,array);
        array[x] = n->data;
        x = x + 1;
        traverse(bst,n->right,array);
    }
}
void sort(Tree* bst,Data *d)
{
    traverse(bst,bst->root,d);
}
void removeLeaf(Node* leaf,Tree* bst)
{
    if (leaf == bst->root && leaf->data.value == bst->root->data.value)
            {
                free(bst->root);
                bst->root = NULL;
                return;
            }
    if (leaf->data.value < leaf->parent->data.value)
    {
        leaf->parent->left = NULL;
    }
    else
    {
        leaf->parent->right = NULL;
    }
    free(leaf);
}
Node * readNode(Node *n,Data d)
{

    if (n->data.value == d.value)
    {
        return n;
    }
    else if (n->data.value < d.value)
    {
        if(n->right == NULL)
        {
            return NULL;
        }
        else
        {
            return readNode(n->right,d);
        }
    }
    else if (n->data.value > d.value)
    {
        if(n->left == NULL)
        {
           return NULL;
        }
        else
        {
            return readNode(n->left,d);
        }
    }
}
void shortCircuit(Node* n)
{

    if (n==n->parent->left)
    {
        if (n->left != NULL)
        {
            n->parent->left = n->left;
            n->left->parent=n->parent;
        }
        else
        {
            n->parent->left = n->right;
            n->right->parent=n->parent;
        }
    }
    else
    {
        if(n->left != NULL)
        {
            n->parent->right = n->left;
            n->left->parent=n->parent;
        }
        else
        {
            n->parent->right=n->right;
            n->right->parent=n->parent;
        }
    }
    free(n);
}
Node* SearchRightMin(Node* n)
{
    n = n->right;
    while (n->left != NULL)
        n = n->left;
    return n;
}
void promotion(Node* n,Tree* bst)
{
    Node* prom = SearchRightMin(n);
    n->data = prom->data;

    if (prom->left == NULL && prom->right == NULL)
    {
        removeLeaf(prom,bst);
    }
    else
    {
        shortCircuit(prom);
    }
}
void removeData(Tree* bst,Data d)
{
    Node* del = readNode(bst->root,d);

    if (del != NULL)
    {
        if(del->left == NULL && del->right == NULL)
        {
            removeLeaf(del,bst);

        }
        else if( del->left == NULL || del->right == NULL)
        {
           if (del->data.value == bst->root->data.value)
            {
                if (del->left != NULL)
                {

                    bst->root = del->left;
                    free(del);
                }
                else
                {

                    bst->root = del->right;
                     free(del);
                }
            }
            else
            {
              shortCircuit(del);
            }
        }
        else
        {
            promotion(del,bst);
        }
    }
}
void deletePost(Tree *bst, Node*n)
{
    if(n != NULL)
    {

        deletePost(bst, n->left);
        deletePost(bst,n->right);
        if(n->parent != NULL)
        {
            removeLeaf(n,bst);
        }
        else
        {
            free(bst->root);
        }

    }
}
void deleteTree (Tree * bst)
{
    deletePost(bst,bst->root);
    free(bst);
}
Tree * newTree()
{
    Tree *tree = malloc(sizeof(Tree));
    tree->root = NULL;
    tree->insert = insertTree;
    tree->sort = sort;
    tree->search = search;
    tree->clone = clone;
    tree->compare = compare;
    tree->removeData = removeData;
    tree->delete = deleteTree;
    return tree;
}