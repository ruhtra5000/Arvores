#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Insert a new node on the BST
void insertNode(node** root, int key) {
    if (*root == NULL) {
        node* newNode = malloc(sizeof(node));
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        *root = newNode;
    }
    else {
        if (key > (*root)->key)
            insertNode(&(*root)->right, key);
        else // if (key < (*root)->key)
            insertNode(&(*root)->left, key);
    }
}

// Remove a node off the tree
void removeNode(node** root, int key) {
    if (*root == NULL)
        return;
    // Right node found
    else if ((*root)->key == key) {
        // Node without child
        if ((*root)->left == NULL && (*root)->right == NULL) {
            *root = NULL;
            free(*root);
        }

        // Node with one child
        else if ((*root)->left != NULL && (*root)->right == NULL) {
            node* tmp = *root;
            *root = (*root)->left;
            free(tmp);
        }

        else if ((*root)->left == NULL && (*root)->right != NULL) {
            node* tmp = *root;
            *root = (*root)->right;
            free(tmp);
        }

        // Node with two children
        else {
            int big = biggestValue((*root)->left);
            (*root)->key = big;
            removeNode(&(*root)->left, big);
        }
    }
    else {
        if (key > (*root)->key)
            removeNode(&(*root)->right, key);
        else // if (key < (*root)->key)
            removeNode(&(*root)->left, key);
    }
}

// Returns the biggest value on a tree
int biggestValue(node* root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root->key;
}

// Print with pre order selection
void printPreOrder(node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

void printInOrder(node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->key);
        printInOrder(root->right);
    }
}

void printPosOrder(node* root) {
    if (root != NULL) {
        printPosOrder(root->left);
        printPosOrder(root->right);
        printf("%d ", root->key);
    }
}

// Count the number of elements at the tree
int count(node* root) {
    if (root == NULL)
        return 0;
    else
        return 1 + count(root->left) + count(root->right);
}

// Calculates the tree height
int height(node* root) {
    if (root == NULL)
        return 0;
    else
        return 1 + MAX(height(root->left), height(root->right));
}

// Sum all the elements of the tree
int sum(node* root) {
    if (root == NULL)
        return 0;
    else {
        return root->key + sum(root->left) + sum(root->right);
    }
}

// Searching a number on the tree
int search(node* root, int key) {
    if (root == NULL) {
        return 0;
    }
    else if (root->key == key) {
        return 1;
    }
    else if (key > root->key)
        return search(root->right, key);
    else
        return search(root->left, key);
}
