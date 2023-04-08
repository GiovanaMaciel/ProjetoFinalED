#include "atividade.h"
#include "fila.h"
#include "listaordenada.h"
#include <stdio.h>
#include <string.h>

#define MAX 1000

// Prototipo das funcoes:
void lTransfere(lista *l, fila *p);
int verificaData(A atv);
int lRemoveTopico(lista *p, S *Topico);
int menor(A p1, A p2);
void printarTarefas(lista *l);

int main() {

  // Declaracao de variaveis:
  lista l;
  fila *f;
  A atv;
  S instrucao[MAX], boolean;
  // Uso de arte ASCII para ilustracao;
  char arte[] =

      "*****************************************\n"
      "████████╗ █████╗ ███████╗██╗  ██╗███████╗\n"
      "╚══██╔══╝██╔══██╗██╔════╝██║ ██╔╝██╔════╝\n"
      "   ██║   ███████║███████╗█████╔╝ ███████╗\n"
      "   ██║   ██╔══██║╚════██║██╔═██╗ ╚════██║\n"
      "   ██║   ██║  ██║███████║██║  ██╗███████║\n"
      "   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n"
      "*****************************************\n";

  /* --------------------------------- COMANDOS --------------------------------- */

  printf("\n%s", arte);

  printf("\nPara inserir uma instrucao siga os seguintes padroes:\n\n");
  printf("-- Inserir na fila de atividade: Insere *ATV_nome* *dd/mm/yyyy*\n");
  printf("  • Note que os asteriscos devem ser ignorados e o campo *ATV_nome* nao deve conter espacos!\n");
  printf("-- Remover o primeiro elemento do topico: Remove\n");
  printf("-- Para encerrar atividades do topico: SairT\n");

  /* ---------------------------------------------------------------------------*/

  lInicializa(&l, menor);

  while (1) {
    f = fInicializa(); 
		
    printf("\nDeseja inserir um novo topico? S/N:\n");
    scanf(" %c", &boolean); 
		
    if (boolean == 'S') {
			
      printf("Qual o topico em questao? \n");
      scanf("%s", atv.topico);
      printf("Utilize agora os comandos para atividades relacionadas ao topico!\n");
			
      do {
        scanf("%s", instrucao);
				// Realiza scanf da instrucao e logo apos busca comando adequado: 
        if (strcmp(instrucao, "Insere") == 0) {
          scanf("%s", atv.atividade);
          scanf("%d/%d/%d", &atv.dia, &atv.mes, &atv.ano);
          // Faz verificacao para para analisar data quanto sua validade:
        	if(verificaData(atv)) {
          	printf("Data invalida!\n");
          } else {
            // Insere atividade na fila!
            if (fInsere(f, atv)) {
              printf("%s inserido com sucesso!\n", atv.atividade);
            } else {
              printf("nao foi possivel inserir %s!\n", atv.atividade);
            }
          }
        } else if (strcmp(instrucao, "Remove") == 0) {
          // Remove atividade da fila!
          if(fTamanho(f) < 0) {
            printf("Fila vazia, impossivel retirar!\n");
          } else {
            A i = fRemove(f);
            printf("Atividade %s removida com sucesso!\n", i.atividade);
          }
        } else if (strcmp(instrucao, "SairT") == 0) { 
          // Transferimos os dados da fila para lista!
          lTransfere(&l, f); 
          // Destruimos fila para sermos capazes de reutiliza-la;
          fDestroi(f);       
        }
      } while (strcmp(instrucao, "SairT") != 0); 
      
    } else if (boolean == 'N') {
      printf("Deseja remover algum topico? S/N:\n"); 
      scanf(" %c", &boolean);
      // Verificacao para remocao do topico ou termino de execucao de programa;
      if (boolean == 'S') {
        printf("Qual seria o topico em questao? \n");
        scanf("%s", atv.topico);
        // Analisa se foi possivel encontrar topico e suas atividades para remove-las;
        if(lRemoveTopico(&l, atv.topico) >= 1) {
					printf("O topico %s e suas atividades foram removidas com sucesso!", atv.topico);
				}
				else {
					printf("Nao foi possivel encontrar o topico em questao!");
				}
      } else {
        // Print para finalizar execucao:
        printarTarefas(&l);
        printf("\nObrigado por usar nossa aplicacao!\n");
        break;
      }
    }
  }
  // Desaloca adequadamente a lista; 
  lDestroi(&l);
	fDestroi(f);
  return (0);
}


  /* --------------------------------- FUNCOES --------------------------------- */

int lRemoveTopico(lista *l, S *Topico) {
  int i = lTamanho(l);
  int cont = 0;
	iterador it = lPrimeiro(l);
  for(int j = 0; j < i; j++, it = lProximo(it)) {
    // Achamos atividade de mesmo topico a ser removido? Retire!
    if (strcmp(lElemento(it).topico, Topico) == 0) {
			lRetira(it);
      // Atualizacao de contador para retorno adequado;
      cont++;
    }
  }
  // Retorna contador para verificacao na main!
  return cont;
}

void lTransfere(lista *p, fila *f) {
  // Vai retirando todos os elementos da fila e os transfere para lista (insere)!
  while(!fVazia(f)) {
    atividade i = fRemove(f);
    lInsere(p, i);
  }
}

int verificaData(atividade atv) {
  // Retorna 1 em caso de data invalida e retorna 0 em caso de data padrao;
	return ((atv.dia>31) || (atv.mes > 12) || (atv.ano > 9999) || (atv.dia>29 && atv.mes==2) || (atv.dia>30 && atv.mes==4) || (atv.dia>30 && atv.mes==6) || (atv.dia>30 && atv.mes==9) || (atv.dia>30 && atv.mes==11) || (atv.dia<1) || (atv.mes<1) || (atv.ano<1) || (atv.ano%4!=0 && atv.mes==2 && atv.dia>28));
}

int menor(A p1, A p2) {
	// Verifica qual estrutura eh "menor" a partir dos campos ano, mes e dia;
	if(p1.ano==p2.ano){ // Se ano for igual, analisa mes;
		if(p1.mes==p2.mes){ // Se mes for igual, analisa dia;
			if(p1.dia<p2.dia){ // Analisa baseado no dia da atividade;
				return 1;
			}
			return 0;
		}
		else if(p1.mes<p2.mes) { // Analisa baseado no mes da atividade;
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(p1.ano<p2.ano) { // Analisa baseado no ano da atividade;
		return 1;
	}
	else {
		return 0;
	}
}

void printarTarefas(lista *l){
	int tam = lTamanho(l);
	printf("\nTASKS:\n");
	if(!tam) {//Se nao tiver nenhuma tarefa a ser feita;
		printf("Nada a fazer!\n");
	}
	int i = 1;
	//Iterador comeca no primeiro elemento da lista e a cada iteracao passa para o proximo;
	for(iterador it = lPrimeiro(l); lValido(it); i++, it = lProximo(it)) {
    printf("%d. %s: ", i, lElemento(it).topico);//Printa o topico do elemento;
    printf("%s ", lElemento(it).atividade);//Printa o nome da atividade do elemento;
		printf("%02d/%02d/%04d", lElemento(it).dia, lElemento(it).mes, lElemento(it).ano);//Printa a data da atividade no modelo dd/mm/yyyy;
		printf("\n");
  }			
}