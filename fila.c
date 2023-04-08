#include "fila.h"

fila* fInicializa() {
  // Inicializacao:
  fila *f = (fila*)malloc(sizeof(fila));
  f->primeiro = f->ultimo = 0;
  f->atvf = (atividade*)malloc(TAMANHO_MAX*sizeof(atividade));
  f->quantidade = 0;
  return f;
}

void fDestroi(fila *f) { 
  // Libera memoria alocada para fila:
  while(!fVazia(f)) {
    fRemove(f);
  }
	free(f->atvf);
  free(f);
}

int fVazia(fila *f) {
  // Retorna V ou F para fila vazia!
  return f->quantidade == 0;
}

int fTamanho(fila *f) {
  // Retorna a quantidade de elementos!
  return f->quantidade;
}

int fInsere(fila *f, A atv) {
  // Verifica se fila esta cheia!
  if (f->quantidade == TAMANHO_MAX) {
    return 0;
  }
  // Uso do apontador para indice de vetor estatico (ultimo sempre estara livre, ate que a fila esteja cheia):
  f->atvf[f->ultimo] = atv;
  
  if (f->ultimo == TAMANHO_MAX - 1) {
    // Se ultimo indice for igual a TAMANHO_MAX - 1, manter circularidade:
    f->ultimo = 0;
  } else {
    // Mantem ultima posicao vazia:
    f->ultimo++;
  }
  f->quantidade++;
  return 1;
}

A fRemove(fila *f) {
  // Verifica se esta vazia!
  if (f->quantidade != 0) {
    atividade atvr = f->atvf[f->primeiro];
    if (f->primeiro == TAMANHO_MAX - 1) {
      // Se primeiro indice for igual a TAMANHO_MAX - 1, manter circularidade:
      f->primeiro = 0;
    } else {
      // Avanca com apontador para nao utilizar mais o conteudo do indice anterior:
      f->primeiro++;
    }
    f->quantidade--;
    return atvr;
  } else {
    atividade aux; // Apenas para evitar warnings;
    return aux;
  }
}
