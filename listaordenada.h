#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include "atividade.h"

typedef atividade A;

// Struct No:
struct node{
	A data;
	struct node *next, *prev;
};
typedef struct node Node;

// Struct da lista:
typedef struct{
	Node *sentinela;
	unsigned quantidade;
  int (*menor)(A,A);
}lista;

// Struct Iterador:
typedef struct{
	Node *posicao;
	lista *estrutura;
} iterador;

// Prototipo das funcoes:
void lInicializa(lista *l, int (*)(A,A));
void lDestroi(lista *l);
int lInsere(lista *l, A data);
iterador lRetira(iterador i);
int lVazia(lista *l);
int lTamanho(lista *l);
iterador lPrimeiro(lista *);
iterador lProximo(iterador);
A lElemento(iterador);
int lValido(iterador);



#endif