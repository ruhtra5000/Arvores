#include "bst.h"
#include <stdio.h>

int main(void) {
    node* root = NULL;
    int opc, chave;

    while (1) {
        scanf("%d", &opc);
        switch (opc) {
        // Inserir
        case 1:
            scanf("%d", &chave);
            insertNode(&root, chave);
            break;
        // Remover elemento
        case 2:
            scanf("%d", &chave);
            removeNode(&root, chave);
            break;
        // Print Pre Order
        case 3:
            printPreOrder(root);
            printf("\n");
            break;
        // Print In Order
        case 4:
            printInOrder(root);
            printf("\n");
            break;
        // Print Pos Order
        case 5:
            printPosOrder(root);
            printf("\n");
            break;
        // Altura da arvore
        case 6:
            printf("%d\n", height(root));
            break;
        // Soma dos elementos
        case 7:
            printf("%d\n", sum(root));
            break;
        // Buscar um elemento
        case 8:
            scanf("%d", &chave);
            printf("%d\n", search(root, chave));
            break;
        // Qtde de elementos
        case 9:
            printf("%d\n", count(root));
            break;
        // Encerrar programa
        case 99:
            exit(0);
            break;
        }
    }

    return 0;
}