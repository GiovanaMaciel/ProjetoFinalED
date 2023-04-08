#include "listaordenada.h"

void lInicializa(lista *l, int (*menor)(A,A)) {
  // Aloca sentinela:
  l->sentinela = (Node*)malloc(sizeof(Node));;
  // Manipula ponteiros:
  l->sentinela->next = l->sentinela->prev = l->sentinela;
	l->quantidade = 0;
  // Inicializa com retorno de menor:
	l->menor = menor;
}

int lValido(iterador i) {
  // Retorna se a posicao nao e sentinela, logo valida para manipulacao:  
  return i.posicao != i.estrutura->sentinela;
}

int lTamanho(lista *l) {
  // Retorna quantidade de elementos na lista:
  return l->quantidade;
}

iterador lPrimeiro(lista *l) {
    iterador i;
		// Aponta para o primeiro elemento da lista;
    i.posicao = l->sentinela->next;
		// Aponta para a estrutura em questao;
    i.estrutura = l;
    return i;
}

iterador lProximo(iterador i) {
  iterador p;
  // Posicao "assume o local proximo elemento";
  p.posicao = i.posicao->next;
  // Atualiza estrutura em questao;
  p.estrutura = i.estrutura;
  return p;
}

A lElemento(iterador i) {
    // Retorna elemento em posicao determinada pelo iterador;
    return i.posicao->data;
}

void lDestroi(lista *l) {
    // Retira todos elementos validos da lista:
    while(lValido(lRetira(lPrimeiro(l))));
    // Desaloca sentinela
    free(l->sentinela);
    // Atualiza quantidade e acerta apontador do sentinela;
    l->quantidade = 0;
    l->sentinela = NULL;
}

int lVazia(lista *l){
  // Caso o proximo do sentinela seja ele proprio, pela circularidade, lista esta vazia!
	return l->sentinela->next == l->sentinela;
}

int lInsere(lista *l, A data) {
    // Alocacao de novo no
    Node *n = (Node*)malloc(sizeof(Node));
    // Verificacao de alocacao
    if(!n) {
      return 0;
    }
    // Atualiza conteudo do no;
    n->data = data;
    // "Insere" conteudo no sentinela para auxiliar na insercao ordenada!
    l->sentinela->data = data; 
    Node *p = l->sentinela->next;
    // Encontra posicao ideal do no;
    while(l->menor(p->data,n->data)) {
      p = p->next;
    }
    // Manipulacoes de apotandor para manter estrutura adequada:
    n->next = p;
    n->prev = p->prev;
    p->prev->next = n;
    p->prev = n;

    l->quantidade++;
    // Sinaliza insercao bem sucedida:
    return 1;
}

iterador lRetira(iterador i) {
    // Caso o no em questao seja valido para retirada, retire!
    if(lValido(i)) {
        Node *p = i.posicao;
        // Atualizacao do iterador:
        i.posicao = i.posicao->next;
        // Manipulacao de apontador
        p->next->prev = p->prev;
        p->prev->next = p->next;
        // Desaloca o no apontado, anteriormente, pelo iterador:
        free(p);
        // Atualiza quantidade de elementos na estrutura:
        i.estrutura->quantidade--;       
    }
    return i;
}

