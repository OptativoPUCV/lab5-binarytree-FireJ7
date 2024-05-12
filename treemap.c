#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
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
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
    
}



void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    if(searchTreeMap(tree, key) == NULL)
      {
        TreeNode *new = createTreeNode(key, value);
        if(tree->root == NULL)
        {
          tree->root = new;
          tree->current = new;
        }
        else
        {
          TreeNode *aux = tree->root;
          while(aux != NULL)
          {
            if(tree->lower_than(key, aux->pair->key))
            {
              if(aux->left == NULL)
              {
                aux->left = new;
                new->parent = aux;
                tree->current = new;
                return;
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
                tree->current = new;
                return;
              }
              else
              {
                aux = aux->right;
              }
            }
          }
        } 
      }
}

TreeNode * minimum(TreeNode * x)
{
    TreeNode* aux = x;
    while(aux->left != NULL)
    {
        aux = aux->left;
    }
    return aux;
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
    TreeNode * aux = tree->root;
    while(aux != NULL)
    {
        if(is_equal(tree, key, aux->pair->key) == 1)
        {
            tree->current = aux;
            return aux->pair;
        }
        if(tree->lower_than(key, aux->pair->key) == 1)
        {
            aux = aux->left; 
        }
        else
        {
            aux = aux->right;
        }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) 
{
    TreeNode* aux = tree->root;
    TreeNode * limiteSuperiorEncontrado = NULL;

    while(aux != NULL) {
        if(is_equal(tree, key, aux->pair->key)) {
            tree->current = aux;
            return aux->pair;
        }
        if(tree->lower_than(key, aux->pair->key)) {
            limiteSuperiorEncontrado = aux;
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    // Si aux es NULL, significa que la llave no se encontró en el árbol.
    // Devolvemos el par asociado al nodo que sería el límite superior si la llave
    // se insertara en el árbol.
    if(limiteSuperiorEncontrado != NULL) {
        tree->current = limiteSuperiorEncontrado;
        return limiteSuperiorEncontrado->pair;
    }

    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) 
{
    TreeNode * aux = tree->root;
    while(aux != NULL)
    {
        if(aux->left != NULL)
        {
            aux = aux->left;
        }
        else
        {
            tree->current = aux;
            return aux->pair;
        }
    }
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) 
{
    TreeNode * aux = tree->current;
    if(aux->right != NULL)
    {
        aux = aux->right;
        while(aux->left != NULL)
        {
            aux = aux->left;
        }
        tree->current = aux;
        return aux->pair;
    }
    else
    {
        while(aux->parent != NULL)
        {
            if(aux->parent->left == aux)
            {
                tree->current = aux->parent;
                return aux->parent->pair;
            }
            aux = aux->parent;    
        }
    }
    return NULL;
}
