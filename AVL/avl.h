#ifndef AVL_H
#define AVL_H

typedef struct node node;

struct node {
	int key;
	int balanceFactor;
	node* left;
	node* right;
};

int insertNode(node** root, int key);

int removeNode(node** root, int key);

void rotate(node** pivot);

void simpleLeftRotation(node** pivot);

void simpleRightRotation(node** pivot);

void doubleLeftRotation(node** pivot);

void doubleRightRotation(node** pivot);

void printPreOrder(node** root);

void printInOrder(node** root);

void printPosOrder(node** root);

int searchBiggerElement(node** root);

#endif