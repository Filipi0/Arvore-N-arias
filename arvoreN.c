#include <stdio.h>
#include <stdlib.h>
#include "arvoreN.h"

typedef NO *PONT;

PONT criarNovoNo(TIPOCHAVE ch)
{
    PONT novo = (PONT)malloc(sizeof(NO));
    novo->primFilho = NULL;
    novo->proxIrmao = NULL;
    novo->chave = ch;
    novo->numFilhos = 0;
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

bool insere(PONT raiz, TIPOCHAVE novaChave, TIPOCHAVE chavePai, int maxFilhos)
{
    PONT pai = buscaChave(chavePai, raiz);
    if (!pai)
        return false;

    if (pai->numFilhos >= maxFilhos)
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
    pai->numFilhos++;
    return true;
}

#include <stdlib.h>

bool removeNo(PONT *raiz, TIPOCHAVE ch)
{
    if (*raiz == NULL)
        return false;

    PONT p = *raiz;

    // Caso a chave seja a da raiz
    if (p->chave == ch)
    {
        if (p->primFilho)
        {
            PONT ultimoIrmao = p->primFilho;
            while (ultimoIrmao->proxIrmao)
                ultimoIrmao = ultimoIrmao->proxIrmao;

            ultimoIrmao->proxIrmao = p->proxIrmao;

            *raiz = p->primFilho;
        }
        else
        {
            *raiz = p->proxIrmao;
        }

        free(p);
        return true;
    }

    PONT prev = NULL;
    p = (*raiz)->primFilho;

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
            (*raiz)->primFilho = p->proxIrmao;
        }
        free(p);
        (*raiz)->numFilhos--;
        return true;
    }
    else
    {
        p = (*raiz)->primFilho;
        while (p)
        {
            if (removeNo(&p, ch))
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