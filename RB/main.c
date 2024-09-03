#include "rb.h";
#include <stdio.h>

void testCase(node** root) {
    insertNode(root, 10);
    insertNode(root, 20);
    removeNode(root, 20);
    insertNode(root, 5);
}

int main(void) {
    node* root;
    initialize(&root);
    //testCase(&root);
    int opt, num;
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
            printPreOrder(root);
            printf("\n");
            break;
        case 4:
            printInOrder(root);
            printf("\n");
            break;
        case 5:
            printPosOrder(root);
            printf("\n");
            break;
        case 99:
            break;
        }
    } while (opt != 99);
}
