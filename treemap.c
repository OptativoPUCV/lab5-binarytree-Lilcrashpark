#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode 
{
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap 
{
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2)
{
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value)
{
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->lower_than = lower_than;
    new->root = NULL;
    new->current = NULL;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    if (tree == NULL || key == NULL || value == NULL)
    {
        return;
    }
    TreeNode * new = createTreeNode(key,value);
    if (tree->root == NULL)
    {
        tree->root = new;
    }
    else
    {
        TreeNode * aux = tree->root;
        while (aux != NULL)
        {
            if (tree->lower_than(key,aux->pair->key) == 1)
            {
                if (aux->left == NULL)
                {
                    aux->left = new;
                    new->parent = aux;
                    break;
                }
                else
                {
                    aux = aux->left;
                }
            }
            else
            {
                if(aux->right == NULL)
                {
                    aux->right = new;
                    new->parent = aux;
                    break;
                }
                else
                {
                    aux = aux->right;
                }
            }
        }
    }
}

TreeNode * minimum(TreeNode * x)
{
    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;
    
    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    if (tree == NULL || tree->root == NULL)
    {
        return NULL;
    }
    TreeNode * aux = tree->root;
    while (aux != NULL)
    {
        if (is_equal(tree,key,aux->pair->key) == 1)
        {
            tree->current = aux;
            return aux->pair;
        }
        else
        {
            if (tree->lower_than(key,aux->pair->key) == 1)
            {
                aux = aux->left;
            }
            else
            {
                aux = aux->right;
            }
        }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) 
{
    
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) 
{
    if (tree == NULL || tree->root == NULL)
    {
        return NULL;
    }
    TreeNode * aux = tree->root;
    while (aux->left != NULL)
    {
        aux = aux->left;
    }
    tree->current = aux;
    return aux->pair;
}

Pair * nextTreeMap(TreeMap * tree) 
{
    if (tree == NULL || tree->current == NULL)
    {
        return NULL;
    }
    TreeNode * aux = tree->current;
    if (aux->right != NULL)
    {
        aux = aux->right;
        while (aux->left != NULL)
        {
            aux = aux->left;
        }
        tree->current = aux;
        return aux->pair;
    }
    else
    {
        TreeNode * parent = aux->parent;
        while (parent != NULL && aux == parent->right)
        {
            aux = parent;
            parent = parent->parent;
        }
        tree->current = parent;
        if (parent != NULL)
        {
            return parent->pair;
        }
    }
    return NULL;
}
