#ifndef ATIVIDADE_H
#define ATIVIDADE_H

#define MAX_TAREFA 1000

// "redefinicao" de variaveis;
typedef int T;
typedef char S;

// struct das atividades:
typedef struct {
  S atividade[MAX_TAREFA], topico[MAX_TAREFA];
  T dia, mes, ano;
} atividade;

#endif