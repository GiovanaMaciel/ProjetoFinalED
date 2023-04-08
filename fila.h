#ifndef FILA_H
#define FILA_H

#include <stdlib.h>
#include "atividade.h"

#define TAMANHO_MAX 1000

// "Redefinição" de tipos:
typedef int T;
typedef atividade A;

// Struct da fila:
typedef struct {
  T primeiro, ultimo;
  A *atvf;
  unsigned quantidade;
} fila;

// Prototipo das funcoes:
fila* fInicializa();
void fDestroi(fila *f);
A fRemove(fila *f);
int fInsere(fila *f, A atvf);
int fVazia(fila *f);
int fTamanho (fila *f);

#endif
