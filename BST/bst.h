#pragma once
#ifndef BST_H
#define BST_H

typedef struct node node;

struct node {
	int key;
	node* left;
	node* right;
};

void insertNode(node** root, int key);

void removeNode(node** root, int key);

void printPreOrder(node* root);
void printInOrder(node* root);
void printPosOrder(node* root);

int count(node* root);

int height(node* root);

int sum(node* root);

int search(node* root, int key);

#endif