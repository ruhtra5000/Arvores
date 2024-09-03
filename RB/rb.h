#pragma once
#ifndef RB_H;
#define RB_H ;

enum color { RED, BLACK, DOUBLE_BLACK };

typedef struct node node;

struct node {
	int key;
	enum color color;
	node* left, * right, * dad;
};

void initialize(node** root);

void insertNode(node** root, int key);

void insertionCorrection(node** root, node* Node);

void removeNode(node** root, int key);

void removalCorrection(node** root, node* Node);

void removeDoubleBlack(node** root, node* Node);

enum color color(node* Node);

int isLeftChild(node* Node);

node* brother(node* Node);

node* grandDad(node* Node);

node* uncle(node* Node);

int biggestValue(node* root);

void recolor(node* Node);

void simpleRightRotation(node** root, node* pivot);

void simpleLeftRotation(node** root, node* pivot);

void doubleRightRotation(node** root, node* pivot);

void doubleLeftRotation(node** root, node* pivot);

void printPreOrder(node* root);

void printInOrder(node* root);

void printPosOrder(node* root);

#endif
