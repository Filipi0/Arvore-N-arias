#include <stdio.h>
#include "arvoreN.h"

int main()
{
    int opcao, chave, chavePai, maxFilhos;
    PONT r = NULL;

    printf("Digite o numero maximo de filhos por no: ");
    scanf("%d", &maxFilhos);

    while (true)
    {
        printf("\nEscolha uma opcao:\n");
        printf("1. Inicializar arvore\n");
        printf("2. Inserir no\n");
        printf("3. Exibir arvore\n");
        printf("4. Remover no\n");
        printf("5. Buscar no\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (r != NULL)
            {
                printf("\nArvore ja inicializada!\n");
            }
            else
            {
                printf("\nDigite a chave da raiz: ");
                scanf("%d", &chave);
                r = inicializa(chave);
                printf("\nArvore inicializada com raiz %d.\n", chave);
            }
            break;

        case 2:
            if (r == NULL)
            {
                printf("Inicialize a arvore primeiro!\n");
            }
            else
            {
                printf("Digite a chave do novo no: ");
                scanf("%d", &chave);
                printf("Digite a chave do no pai: ");
                scanf("%d", &chavePai);
                if (insere(r, chave, chavePai, maxFilhos))
                {
                    printf("\n***No %d inserido como filho de %d.\n***", chave, chavePai);
                }
                else
                {
                    printf("\nNo pai %d nao encontrado ou limite de filhos atingido.\n", chavePai);
                }
            }
            break;

        case 3:
            if (r == NULL)
            {
                printf("\nInicialize a arvore primeiro!\n");
            }
            else
            {
                printf("\nArvore: \n");
                exibirArvore(r);
                printf("\n");
            }
            break;

        case 4:
            if (r == NULL)
            {
                printf("\nInicialize a arvore primeiro!\n");
            }
            else
            {
                printf("\nDigite a chave do no a ser removido: ");
                scanf("%d", &chave);
                if (removeNo(&r, chave))  // Chamada ajustada
                {
                    printf("\nNo %d removido.\n", chave);
                }
                else
                {
                    printf("\nNo %d nao encontrado.\n", chave);
                }
            }
            break;

        case 5:
            if (r == NULL)
            {
                printf("\nInicialize a arvore primeiro!\n");
            }
            else
            {
                printf("\nDigite a chave do no a ser buscado: ");
                scanf("%d", &chave);
                PONT pai, pt;
                buscarArvore(r, chave, &pai, &pt);
                if (pt)
                {
                    printf("\nNo %d encontrado.\n", chave);
                    if (pai)
                    {
                        printf("Pai: %d\n", pai->chave);
                    }
                    else
                    {
                        printf("No %d eh a raiz.\n", chave);
                    }
                }
                else
                {
                    printf("\nNo %d nao encontrado.\n", chave);
                }
            }
            break;

        case 0:
            printf("\nSaindo...\n");
            return 0;

        default:
            printf("\nOpcao invalida!\n");
        }
    }

    return 0;
}
