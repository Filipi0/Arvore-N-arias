#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct no
{
    TIPOCHAVE chave;
    struct no *primFilho;
    struct no *proxIrmao;
} NO;

typedef NO *PONT;

PONT criarNovoNo(TIPOCHAVE ch)
{
    PONT novo = (PONT)malloc(sizeof(NO));
    novo->primFilho = NULL;
    novo->proxIrmao = NULL;
    novo->chave = ch;
    return novo;
}

PONT inicializa(TIPOCHAVE ch)
{
    return criarNovoNo(ch);
}

PONT buscaChave(TIPOCHAVE ch, PONT raiz)
{
    if (raiz == NULL)
        return NULL;
    if (raiz->chave == ch)
        return raiz;
    PONT p = raiz->primFilho;
    while (p)
    {
        PONT resp = buscaChave(ch, p);
        if (resp)
            return resp;
        p = p->proxIrmao;
    }
    return NULL;
}

bool insere(PONT raiz, TIPOCHAVE novaChave, TIPOCHAVE chavePai)
{
    PONT pai = buscaChave(chavePai, raiz);
    if (!pai)
        return false;

    PONT filho = criarNovoNo(novaChave);
    PONT p = pai->primFilho;
    if (!p)
    {
        pai->primFilho = filho;
    }
    else
    {
        while (p->proxIrmao)
        {
            p = p->proxIrmao;
        }
        p->proxIrmao = filho;
    }
    return true;
}

bool removeNo(PONT raiz, TIPOCHAVE ch)
{
    if (raiz == NULL)
        return false;
    PONT p = raiz->primFilho;
    PONT prev = NULL;

    while (p && p->chave != ch)
    {
        prev = p;
        p = p->proxIrmao;
    }

    if (p)
    {
        if (prev)
        {
            prev->proxIrmao = p->proxIrmao;
        }
        else
        {
            raiz->primFilho = p->proxIrmao;
        }
        free(p);
        return true;
    }
    else
    {
        p = raiz->primFilho;
        while (p)
        {
            if (removeNo(p, ch))
                return true;
            p = p->proxIrmao;
        }
    }
    return false;
}

void exibirArvore(PONT raiz)
{
    if (raiz == NULL)
        return;
    printf("%d(", raiz->chave);
    PONT p = raiz->primFilho;
    while (p)
    {
        exibirArvore(p);
        p = p->proxIrmao;
    }
    printf(")");
}

void buscarArvore(PONT raiz, TIPOCHAVE ch, PONT *pai, PONT *pt)
{
    *pai = NULL;
    *pt = NULL;
    if (raiz == NULL)
        return;

    if (raiz->primFilho != NULL)
    {
        PONT atual = raiz->primFilho;
        while (atual != NULL)
        {
            if (atual->chave == ch)
            {
                *pt = atual;
                *pai = raiz;
                return;
            }
            buscarArvore(atual, ch, pai, pt);
            if (*pt != NULL)
                return;
            atual = atual->proxIrmao;
        }
    }

    if (raiz->chave == ch)
    {
        *pt = raiz;
    }
}

int main()
{
    int opcao, chave, chavePai;
    PONT r = NULL;

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
                if (insere(r, chave, chavePai))
                {
                    printf("\n***No %d inserido como filho de %d.\n***", chave, chavePai);
                }
                else
                {
                    printf("\nNo pai %d nao encontrado.\n", chavePai);
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
                printf("\nArvore: ");
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
                if (removeNo(r, chave))
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