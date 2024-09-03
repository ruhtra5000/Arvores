#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

node* doubleBlackNull;

// Initialize the absolute root and *doubleBlackNull
void initialize(node** root) {
    *root = NULL;

    doubleBlackNull = malloc(sizeof(node));
    doubleBlackNull->color = DOUBLE_BLACK;
    doubleBlackNull->left = NULL;
    doubleBlackNull->right = NULL;
    doubleBlackNull->dad = NULL;
    doubleBlackNull->key = 0;
}

// Inserts a new node into the tree
void insertNode(node** root, int key) {
    node* temp = (*root), * tempDad = NULL;

    // Searching the correct position to insert
    while (temp != NULL) {
        tempDad = temp;
        if (key > temp->key)
            temp = temp->right;
        else
            temp = temp->left;
    }

    // Creating the new node
    node* newNode = malloc(sizeof(node));
    newNode->key = key;
    newNode->color = RED;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->dad = tempDad;

    // First node inserted
    if (tempDad == NULL) {
        (*root) = newNode;
    }
    // Other than the first inserted
    else {
        if (tempDad->key < newNode->key)
            tempDad->right = newNode;
        else
            tempDad->left = newNode;
    }
    insertionCorrection(root, newNode);
}

// Checks if the tree needs to be corrected
void insertionCorrection(node** root, node* Node) {
    // If two red nodes in sequence: correction
    while (Node->dad != NULL && color(Node->dad) == RED) {
        // Case 1: Recolor
        if (color(uncle(Node)) == RED) {
            recolor(grandDad(Node));
            // checks if the grandad has generated another red-red sequence
            Node = grandDad(Node);
            continue;
        }
        else {
            // Case 2: Simple rotation
            // Case 2.1: Simple right rotation
            if (isLeftChild(Node) && isLeftChild(Node->dad)) {
                simpleRightRotation(root, grandDad(Node));
                // Recoloring
                Node->dad->color = BLACK;
                brother(Node)->color = RED;
                break;
            }
            // Case 2.2: Simple left rotation
            if (!isLeftChild(Node) && !isLeftChild(Node->dad)) {
                simpleLeftRotation(root, grandDad(Node));
                // Recoloring
                Node->dad->color = BLACK;
                brother(Node)->color = RED;
                break;
            }
            // Case 3: Double rotation
            // Case 3.1: Double right rotation
            if (!isLeftChild(Node) && isLeftChild(Node->dad)) {
                doubleRightRotation(root, grandDad(Node));
                // Recoloring
                Node->color = BLACK;
                Node->right->color = RED;
                break;
            }
            // Case 3.2: Double left rotation
            if (isLeftChild(Node) && !isLeftChild(Node->dad)) {
                doubleLeftRotation(root, grandDad(Node));
                // Recoloring
                Node->color = BLACK;
                Node->left->color = RED;
                break;
            }
        }
    }

    // Case 0: Paint the absolute root
    (*root)->color = BLACK;
}

// Removes a node from the tree
void removeNode(node** root, int key) {
    node* temp = *root;

    // Searchs the node
    while (temp != NULL) {
        if (key > temp->key)
            temp = temp->right;
        else if (key < temp->key)
            temp = temp->left;

        // Node founded
        else if (key == temp->key) {
            // Case 1 - Two Children
            if (temp->left != NULL && temp->right != NULL) {
                int big = biggestValue(temp->left);
                removeNode(root, big);
                temp->key = big;
                break;
            }
            // Case 2.1 - One left child
            if (temp->left != NULL && temp->right == NULL) {
                temp->left->color = BLACK;
                temp->left->dad = temp->dad;
                // If needs to remove the absolute root, update **root
                if (temp->dad == NULL) {
                    *root = temp->left;
                }
                else {
                    if (isLeftChild(temp))
                        temp->dad->left = temp->left;
                    else
                        temp->dad->right = temp->left;
                }

                free(temp);
                break;
            }
            // Case 2.2 - One right child
            if (temp->left == NULL && temp->right != NULL) {
                temp->right->color = BLACK;
                temp->right->dad = temp->dad;
                // If needs to remove the absolute root, update **root
                if (temp->dad == NULL) {
                    *root = temp->right;
                }
                else {
                    if (isLeftChild(temp))
                        temp->dad->left = temp->right;
                    else
                        temp->dad->right = temp->right;
                }

                free(temp);
                break;
            }
            // Case 3 - No children
            if (temp->left == NULL && temp->right == NULL) {
                // If needs to remove the absolute root, update **root
                if (temp->dad == NULL) {
                    *root = NULL;
                    free(temp);
                }
                else {
                    // Red and no children: just remove
                    if (color(temp) == RED) {
                        if (isLeftChild(temp))
                            temp->dad->left = NULL;
                        else
                            temp->dad->right = NULL;

                        free(temp);
                    }
                    // Black and no children: double black NULL
                    else if (color(temp) == BLACK) {
                        doubleBlackNull->dad = temp->dad;
                        if (isLeftChild(temp)) 
                            temp->dad->left = doubleBlackNull;
                        else
                            temp->dad->right = doubleBlackNull;

                        free(temp);
                        removalCorrection(root, doubleBlackNull);
                    }
                    else
                        printf("color: %d\n", temp->color);
                }
                break;
            }
        }
    }
}

// Corrects the tree until double black is removed
void removalCorrection(node** root, node* Node) {
    // Case 1 (root)
    if (Node->dad == NULL) {
        if (Node == doubleBlackNull)
            *root = NULL;
        else
            Node->color = BLACK;
        return;
    }

    // Case 2
    if (color(Node->dad) == BLACK && color(brother(Node)) == RED &&
        color(brother(Node)->left) == BLACK &&
        color(brother(Node)->right) == BLACK) {

        if (isLeftChild(Node))
            simpleLeftRotation(root, Node->dad);
        else
            simpleRightRotation(root, Node->dad);

        Node->dad->color = RED;
        grandDad(Node)->color = BLACK;

        removalCorrection(root, Node);
        return;
    }

    // Case 3
    if (color(Node->dad) == BLACK && color(brother(Node)) == BLACK &&
        color(brother(Node)->left) == BLACK &&
        color(brother(Node)->right) == BLACK) {

        Node->dad->color = DOUBLE_BLACK;
        brother(Node)->color = RED;
        removeDoubleBlack(root, Node);
        removalCorrection(root, Node->dad);
        return;
    }

    // Case 4
    if (color(Node->dad) == RED && color(brother(Node)) == BLACK &&
        color(brother(Node)->left) == BLACK &&
        color(brother(Node)->right) == BLACK) {

        Node->dad->color = BLACK;
        brother(Node)->color = RED;
        removeDoubleBlack(root, Node);
        return;
    }

    // Case 5.1 - Double black left child
    if (isLeftChild(Node) && color(brother(Node)) == BLACK &&
        color(brother(Node)->left) == RED &&
        color(brother(Node)->right) == BLACK) {

        simpleRightRotation(root, brother(Node));
        brother(Node)->color = BLACK;
        brother(Node)->right->color = RED;

        removalCorrection(root, Node);
        return;
    }

    // Case 5.2 - Double black right child
    if (!isLeftChild(Node) && color(brother(Node)) == BLACK &&
        color(brother(Node)->left) == BLACK &&
        color(brother(Node)->right) == RED) {

        simpleLeftRotation(root, brother(Node));
        brother(Node)->color = BLACK;
        brother(Node)->left->color = RED;

        removalCorrection(root, Node);
        return;
    }

    // Case 6.1 - Double black left child
    if (isLeftChild(Node) && color(brother(Node)) == BLACK &&
        color(brother(Node)->right) == RED) {

        simpleLeftRotation(root, Node->dad);
        grandDad(Node)->color = Node->dad->color;
        Node->dad->color = BLACK;
        uncle(Node)->color = BLACK;
        removeDoubleBlack(root, Node);
        return;
    }

    // Case 6.2 - Double black right child
    if (!isLeftChild(Node) && color(brother(Node)) == BLACK &&
        color(brother(Node)->left) == RED) {

        simpleRightRotation(root, Node->dad);
        grandDad(Node)->color = Node->dad->color;
        Node->dad->color = BLACK;
        uncle(Node)->color = BLACK;
        removeDoubleBlack(root, Node);
        return;
    }
}

// Remove the double black node itself
void removeDoubleBlack(node** root, node* Node) {
    // Double black is null
    if (Node == doubleBlackNull) {
        if (isLeftChild(Node))
            Node->dad->left = NULL;
        else
            Node->dad->right = NULL;
    }
    // Double black isnt null
    else
        Node->color = BLACK;
}

// Returns the color of a node
enum color color(node* Node) {
    if (Node != NULL)
        return Node->color;
    return BLACK; // NULL's color: BLACK
}

// Checks if a node is a left child. Otherwise, is a right child.
int isLeftChild(node* Node) {
    if (Node->dad->left == Node)
        return 1;
    return 0;
}

// Returns the relatives of a node
node* brother(node* Node) {
    if (isLeftChild(Node))
        return Node->dad->right;
    else
        return Node->dad->left;
}

node* grandDad(node* Node) { return Node->dad->dad; }

node* uncle(node* Node) { return brother(Node->dad); }

// Return the biggest value of a tree
int biggestValue(node* root) {
    if (root != NULL) {
        node* tmp = root;
        while (tmp->right != NULL)
            tmp = tmp->right;
        return tmp->key;
    }
}

// Correction functions
void recolor(node* Node) {
    Node->color = RED;
    Node->right->color = BLACK;
    Node->left->color = BLACK;
}

/*
    p         v
   /         / \
  v     ->  u   p
 / \           /
u   t2        t2
*/

void simpleRightRotation(node** root, node* pivot) {
    node* greatGrandad = pivot->dad;
    node* dad = pivot->left;
    node* child = dad->left, * t2 = dad->right;

    int pivotRelativePosition;
    if (greatGrandad != NULL)
        pivotRelativePosition = isLeftChild(pivot);

    pivot->left = t2;
    // if subtree isnt NULL, update its dad pointer
    if (t2 != NULL)
        t2->dad = pivot;

    dad->right = pivot;
    dad->dad = greatGrandad;
    pivot->dad = dad;

    // pivot isnt the absolute root,
    // so update greatgrandad pointer to it
    if (greatGrandad != NULL) {
        if (pivotRelativePosition)
            greatGrandad->left = dad;
        else
            greatGrandad->right = dad;
    }
    // pivot is the absolute root, so update **root
    else
        *root = dad;
}

/*
    p          v
     \        / \
      v  ->  p   u
     / \      \
    t2   u    t2
*/

void simpleLeftRotation(node** root, node* pivot) {
    node* greatgrandad = pivot->dad;
    node* dad = pivot->right;
    node* child = dad->right, * t2 = dad->left;

    int pivotRelativePosition;
    if (greatgrandad != NULL)
        pivotRelativePosition = isLeftChild(pivot);

    pivot->right = t2;
    if (t2 != NULL)
        t2->dad = pivot;

    dad->dad = greatgrandad;
    dad->left = pivot;
    pivot->dad = dad;

    // pivot isnt the absolute root,
    // so update greatgrandad pointer to it
    if (greatgrandad != NULL) {
        if (pivotRelativePosition)
            greatgrandad->left = dad;
        else
            greatgrandad->right = dad;
    }
    // pivot is the absolute root, so update **root
    else
        *root = dad;
}

void doubleRightRotation(node** root, node* pivot) {
    simpleLeftRotation(root, pivot->left);
    simpleRightRotation(root, pivot);
}

void doubleLeftRotation(node** root, node* pivot) {
    simpleRightRotation(root, pivot->right);
    simpleLeftRotation(root, pivot);
}

// Prints
void printPreOrder(node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        if (root->color == RED)
            printf("(R) ");
        else if (root->color == BLACK)
            printf("(B) ");
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
