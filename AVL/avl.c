#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

// Inserts a new node on the tree
int insertNode(node** root, int key) {
    // Returns an int that represents the tree growth

    // Searching the correct position to do the insertion
    if (*root == NULL) {
        node* new = malloc(sizeof(node));
        new->key = key;
        new->balanceFactor = 0;
        new->left = NULL;
        new->right = NULL;

        *root = new;

        return 1; // grew
    }
    else {
        if (key > (*root)->key) {
            // Right subtree grew
            if (insertNode(&(*root)->right, key)) {
                (*root)->balanceFactor++;
                switch ((*root)->balanceFactor) {
                case 0:
                    return 0; // Didnt grew
                case 1:
                    return 1; // Grew
                case 2:
                    // Apply rotation
                    rotate(root);
                    return 0; // rotation prevents the growth
                }
            }
            return 0;
        }
        else {
            // Left subtree grew
            if (insertNode(&(*root)->left, key)) {
                (*root)->balanceFactor--;
                switch ((*root)->balanceFactor) {
                case 0:
                    return 0; // Didnt grew
                case -1:
                    return 1; // Grew
                case -2:
                    // Apply rotation
                    rotate(root);
                    return 0; // rotation prevents the growth
                }
            }
            return 0;
        }
    }
}

// Removes a node from the tree
int removeNode(node** root, int key) {
    // Returns an int that represents the tree's shrink

    // Element dont exist
    if (*root == NULL) {
        return 0; // Didnt decreased
    }
    // Element founded
    else if ((*root)->key == key) {
        // Case 1: no children
        if ((*root)->left == NULL && (*root)->right == NULL) {
            free(*root);
            *root = NULL;
            return 1;
        }
        // Case 2: one child (left)
        else if ((*root)->left != NULL && (*root)->right == NULL) {
            node* tmp = *root;
            *root = (*root)->left;
            free(tmp);
            tmp = NULL;
            return 1;
        }
        //(right)
        else if ((*root)->left == NULL && (*root)->right != NULL) {
            node* tmp = *root;
            *root = (*root)->right;
            free(tmp);
            tmp = NULL;
            return 1;
        }
        // Case 3: two children
        else {
            int big = searchBiggerElement(&(*root)->left);
            (*root)->key = big;
            // Rever
            if (removeNode(&(*root)->left, big)) {
                (*root)->balanceFactor++;
                switch ((*root)->balanceFactor) {
                case 0:
                    return 1; // Decreased
                case 1:
                    return 0; // Didnt decreased
                case 2:
                    // Apply rotation
                    rotate(root);
                    if ((*root)->balanceFactor == -1) {
                        return 0;
                    }
                    return 1;
                }
            }
            return 0;
        }
    }
    else {
        if (key > (*root)->key) {
            // Right subtree decreased
            if (removeNode(&(*root)->right, key)) {
                (*root)->balanceFactor--;
                switch ((*root)->balanceFactor) {
                case 0:
                    return 1; // Decreased
                case -1:
                    return 0; // Didnt decreased
                case -2:
                    // Apply rotation
                    rotate(root);
                    if ((*root)->balanceFactor == 1) {
                        return 0;
                    }
                    return 1;
                }
            }
            return 0;
        }
        else {
            // Left subtree decreased
            if (removeNode(&(*root)->left, key)) {
                (*root)->balanceFactor++;
                switch ((*root)->balanceFactor) {
                case 0:
                    return 1; // Decreased
                case 1:
                    return 0; // Didnt decreased
                case 2:
                    // Apply rotation
                    rotate(root);
                    if ((*root)->balanceFactor == -1) {
                        return 0;
                    }
                    return 1;
                }
            }
            return 0;
        }
    }
}

// Decide the correct rotation to be made
void rotate(node** pivot) {
    node* p, * u, * v;
    p = *pivot;

    // Left rotations
    if ((*pivot)->balanceFactor == 2) {
        // Simple left rotation
        u = p->right;
        if (u->balanceFactor >= 0) {
            switch (u->balanceFactor) {
            case 0:
                p->balanceFactor = 1;
                u->balanceFactor = -1;
                break;
            case 1:
                p->balanceFactor = 0;
                u->balanceFactor = 0;
                break;
            }
            simpleLeftRotation(pivot);
        }
        // Double left rotation
        else { //(u->balanceFactor == -1)
            v = u->left;
            switch (v->balanceFactor) {
            case -1:
                p->balanceFactor = 0;
                u->balanceFactor = 1;
                v->balanceFactor = 0;
                break;
            case 0:
                p->balanceFactor = 0;
                u->balanceFactor = 0;
                v->balanceFactor = 0;
                break;
            case 1:
                p->balanceFactor = -1;
                u->balanceFactor = 0;
                v->balanceFactor = 0;
                break;
            }
            doubleLeftRotation(pivot);
        }
    }
    // Right rotations
    else if ((*pivot)->balanceFactor == -2) {
        // Simple right rotation
        u = p->left;
        if (u->balanceFactor <= 0) {
            switch (u->balanceFactor) {
            case 0:
                p->balanceFactor = -1;
                u->balanceFactor = 1;
                break;
            case -1:
                p->balanceFactor = 0;
                u->balanceFactor = 0;
                break;
            }
            simpleRightRotation(pivot);
        }
        // Double right rotation
        else { //(u->balanceFactor == 1)
            v = u->right;
            switch (v->balanceFactor) {
            case -1:
                p->balanceFactor = 1;
                u->balanceFactor = 0;
                v->balanceFactor = 0;
                break;
            case 0:
                p->balanceFactor = 0;
                u->balanceFactor = 0;
                v->balanceFactor = 0;
                break;
            case 1:
                p->balanceFactor = 0;
                u->balanceFactor = -1;
                v->balanceFactor = 0;
                break;
            }
            doubleRightRotation(pivot);
        }
    }
}

// Rotations
void simpleLeftRotation(node** pivot) {
    node* p, * u, * t2; //*t1, *t3;

    p = *pivot;
    u = p->right;
    // t1 = p->left;
    t2 = u->left;
    // t3 = u->right;

    u->left = p;
    p->right = t2;
    *pivot = u;
}

void simpleRightRotation(node** pivot) {
    node* p, * u, * t2; //*t1, *t3;

    p = *pivot;
    u = p->left;
    // t1 = u->left;
    t2 = u->right;
    // t3 = p->right;

    u->right = p;
    p->left = t2;
    *pivot = u;
}

void doubleLeftRotation(node** pivot) {
    /*node *p, *u;
    p = *pivot;
    u = p->right;*/
    simpleRightRotation(&(*pivot)->right);
    simpleLeftRotation(pivot);
}

void doubleRightRotation(node** pivot) {
    /*node *p, *u;
    p = *pivot;
    u = p->left;*/
    simpleLeftRotation(&(*pivot)->left);
    simpleRightRotation(pivot);
}

// Prints
void printPreOrder(node** root) {
    if (*root != NULL) {
        printf("%d (%d) ", (*root)->key, (*root)->balanceFactor);
        printPreOrder(&(*root)->left);
        printPreOrder(&(*root)->right);
    }
}

void printInOrder(node** root) {
    if (*root != NULL) {
        printInOrder(&(*root)->left);
        printf("%d ", (*root)->key);
        printInOrder(&(*root)->right);
    }
}

void printPosOrder(node** root) {
    if (*root != NULL) {
        printPosOrder(&(*root)->left);
        printPosOrder(&(*root)->right);
        printf("%d ", (*root)->key);
    }
}

// Searches the bigger element in a tree
int searchBiggerElement(node** root) {
    if ((*root)->right == NULL) {
        return (*root)->key;
    }
    else {
        searchBiggerElement(&(*root)->right);
    }
}