#ifndef ARVOREN_H
#define ARVOREN_H

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct no
{
    TIPOCHAVE chave;
    struct no *primFilho;
    struct no *proxIrmao;
    int numFilhos;
} NO;

typedef NO *PONT;

PONT criarNovoNo(TIPOCHAVE ch);
PONT inicializa(TIPOCHAVE ch);
PONT buscaChave(TIPOCHAVE ch, PONT raiz);
bool insere(PONT raiz, TIPOCHAVE novaChave, TIPOCHAVE chavePai, int maxFilhos);
bool removeNo(PONT *raiz, TIPOCHAVE ch);
void exibirArvore(PONT raiz);
void buscarArvore(PONT raiz, TIPOCHAVE ch, PONT *pai, PONT *pt);

#endif
