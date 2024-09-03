#include "avl.h"
#include <stdio.h>

void test(node** root) {
    insertNode(root, 10);
    insertNode(root, 3);
    insertNode(root, 15);
    insertNode(root, 1);
    insertNode(root, 5);
    insertNode(root, 12);
    insertNode(root, 22);
    insertNode(root, 4);
    insertNode(root, 7);
    insertNode(root, 11);
    insertNode(root, 21);
    insertNode(root, 25);
}

int main(void) {
    node* root = NULL;
    int opt, num;

    // test(&root);

    do {
        scanf("%d", &opt);
        switch (opt) {
        case 1:
            scanf("%d", &num);
            insertNode(&root, num);
            break;
        case 2:
            scanf("%d", &num);
            removeNode(&root, num);
            break;
        case 3:
            printf("Print pre order:\n");
            printPreOrder(&root);
            printf("\n");
            break;
        case 4:
            printf("\nPrint in order:\n");
            printInOrder(&root);
            printf("\n");
            break;
        case 5:
            printf("\nPrint pos order:\n");
            printPosOrder(&root);
            printf("\n");
            break;
        case 99:
            // Exit
            break;
        }
    } while (opt != 99);
}