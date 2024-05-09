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
    if (tree == NULL || tree->root == NULL)
    {
        // Si el árbol está vacío, el nuevo nodo se convierte en la raíz
        tree->root = createTreeNode(key, value);
        tree->current = tree->root;
    }
    else
    {
        TreeNode * aux = tree->root;
        TreeNode * parent = NULL;
        while (aux != NULL)
        {
            parent = aux;
            if (is_equal(tree, key, aux->pair->key))
            {
                // Si la llave ya existe en el árbol, no hacemos nada
                return;
            }
            else
            {
                if (tree->lower_than(key, aux->pair->key) == 1)
                {
                    // Si la llave es menor que la del nodo actual, nos movemos a la izquierda
                    aux = aux->left;
                }
                else
                {
                    // Si la llave es mayor que la del nodo actual, nos movemos a la derecha
                    aux = aux->right;
                }
            }
        }

        // Creamos el nuevo nodo y lo insertamos como hijo del nodo adecuado
        TreeNode * new_node = createTreeNode(key, value);
        if (tree->lower_than(key, parent->pair->key) == 1)
        {
            parent->left = new_node;
        }
        else
        {
            parent->right = new_node;
        }
    }
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

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


Pair * upperBound(TreeMap * tree, void* key) {
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

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
