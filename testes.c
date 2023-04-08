#include "Unity/unity.h"
#include "fila.h"
#include "atividade.h"
#include "listaordenada.h"
#include <string.h>

void setUp(){};
void tearDown(){};

//Funcao auxiliar para testar a lista. Verifica pela data qual eh mais antiga
//Essa funcao eh necessaria para fazer os testes das funcoes da lista, uma vez que, para a inicializacao
//eh preciso da funcao menor.
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



//Verifica qual data eh mais antiga.
//Exemplo: menor(a1, a2) compara se a data a1 eh mais antiga que a2 (a1<a2).
//Caso a1<a2 a funcao menor retorna 1, e caso contrario, retorna.
//Caso a1=a2 a funcao retorna 0.
//Pelos testes do Unity, TEST_ASSERT_EQUAL_INT, verificamos que funcao menor funciona corretamente.
void teste_menor(){

    atividade a1, a2;

    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 1964;
    a2.dia = 19;
    a2.mes = 9;
    a2.ano = 2023;

    TEST_ASSERT_EQUAL_INT(1, menor(a1, a2));
    TEST_ASSERT_EQUAL_INT(0, menor(a2, a1));

    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 2023;
    a2.dia = 20;
    a2.mes = 12;
    a2.ano = 2023;

    TEST_ASSERT_EQUAL_INT(0, menor(a1, a2));
    TEST_ASSERT_EQUAL_INT(0, menor(a2, a1));
}


//Neste teste eh verificado o funcionamento de fInicializa, entao, com base na fila.c, simulamos o enderecamento
//dado nesse arquivo e analisamos se os ponteiros tem enderecos corretos, alem de verificar se o tamanho da fila
//inicializa com 0 (f->quantidade = 0)
void teste1() {

    fila *f;
    f = fInicializa();
    TEST_ASSERT_EQUAL_PTR(f->primeiro, f->ultimo);        //Testa se f->primeiro tem mesmo endereco de f->ultimo 
    TEST_ASSERT_EQUAL_PTR(0, f->ultimo);                  //E testa se ambos f->primeiro e 
    TEST_ASSERT_EQUAL_PTR(0, f->primeiro);                //f->ultimo apontam para 0
    TEST_ASSERT_EQUAL_INT(0, f->quantidade);              //Testa se f->quantidade inicialzia com 0
    TEST_ASSERT_NOT_NULL(f->atvf);                        //Testa se f->atvf foi alocado corretamente na memoria
}


// Teste da funcao fDestroi, que deve destruir corretamente uma fila com um elemento
void teste2() {

    fila *f = fInicializa();
    atividade a1;

    // Definicao dos campos da atividade:
    a1.topico[MAX_TAREFA] = "Calculo";
    a1.atividade[MAX_TAREFA] = "Estudar_para_P3";
    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 2020;

    fInsere(f, a1);
    TEST_ASSERT_EQUAL(f->quantidade, 1);
    fDestroi(f);
    TEST_ASSERT_EQUAL(f->quantidade, 0); // Verifica se a fila foi completamente destruida
}



//Teste da funcao fVazia
//Neste teste eh verificado o funcionamento correto da funcao fVazia, ou seja, se a fila esta vazia ou nao.
//Inicialmente atribuimos uma atividade na fila e testamos se ela esta vazia ou nao com fVazia. Pela verificacao
//com a funcao do Unity, TEST_ASSERT_EQUAL, comparamos o retorno de fVazia com o numero 0, pois, como
//foi inserido um elemento na fila, ela nao esta vazia e, portanto, fVazia retorna 0, e assim o teste passa.
//Depois disso removemos este elemento da fila, e verificamos novamente com TEST_ASSERT_EQUAL se o valor
//retornado por fVazia eh 1, ja que agora a fila esta vazia. Caso fVazia retorne 1 entao o teste esta correto.
void teste3(){                                          

    fila *f;
    f = fInicializa();                                      //Inicializa a fila

    atividade a1;                                         

    // Definicao dos campos da atividade 1:
    a1.topico[MAX_TAREFA] = "Calculo";
    a1.atividade[MAX_TAREFA] = "Estudar_para_P3";
    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 2020;

    fInsere(f, a1);                                         //Insere a atividade a1 na fila
    TEST_ASSERT_EQUAL(0, fVazia(f));                        //Verifica se a fila NAO esta vazia (se nao esta vazia fVazia retorna 0)
    fRemove(f); 
    TEST_ASSERT_EQUAL(1, fVazia(f));                        //Verifica se a fila esta vazia apos a remocao (fVazia retorna 1)

}


//Teste da funcao fTamanho
void teste4(){

    fila *f = fInicializa();
    atividade a1, a2;

    //Testa se a fila comeca vazia
    TEST_ASSERT_EQUAL(f->quantidade, 0);

    // Definicao dos campos da atividade 1:
    a1.topico[MAX_TAREFA] = "Calculo";
    a1.atividade[MAX_TAREFA] = "Estudar_para_P3";
    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 2020;
    fInsere(f, a1);
    TEST_ASSERT_EQUAL(f->quantidade, 1); // Testa se a quantidade de elementos na fila eh atualizada corretamente apos insercao
    
    // Definicao dos campos da atividade 2:
    a2.topico[MAX_TAREFA] = "Fisica";
    a2.atividade[MAX_TAREFA] = "Entregar_Projeto";
    a2.dia = 12;
    a2.mes = 10;
    a2.ano = 2023;
    fInsere(f, a2);
    TEST_ASSERT_EQUAL(f->quantidade, 2);// Testa se a quantidade de elementos na fila eh atualizada corretamente para 2
};



//Teste da funcao fInsere
//Neste teste verificamos o funcionamento da funcao fInsere.
//Depois de inicializar a fila inserimos duas atividades, e a cada insercao verificamos se os dados passados para
//a fila sao coerentes, ou seja, por meio das funcoes do Unity, TEST_ASSERT_EQUAL_STRING e TEST_ASSERT_EQUAL_INT
//testamos se as strings(a.topico e a.atividade) e as datas(a.dia, a.mes, a.ano) passadas sao iguais.
//Caso os dados sejam transmitidos corretamente o teste passa!
void teste5() {                                                   

    fila *f;
    f = fInicializa();                                             //Inicializa a fila

    atividade a1, a2;

    // Definicao dos campos da atividade 1:
    a1.topico[MAX_TAREFA] = "Fisica";
    a1.atividade[MAX_TAREFA] = "Estudar_Conservacao_de_Energia";
    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 2020;

    fInsere(f, a1);                                                //Insere a atividade a1 na fila

    TEST_ASSERT_EQUAL_STRING(a1.topico, f->atvf[0].topico);        //Verifica se a fila recebeu a1.topico corretamente
    TEST_ASSERT_EQUAL_STRING(a1.atividade, f->atvf[0].atividade);  //Verifica se a fila recebeu a1.atividade corretamente
    TEST_ASSERT_EQUAL_INT(a1.dia, f->atvf[0].dia);                 //Verifica se a fila recebeu a1.dia corretamente
    TEST_ASSERT_EQUAL_INT(a1.mes, f->atvf[0].mes);                 //Verifica se a fila recebeu a1.mes corretamente
    TEST_ASSERT_EQUAL_INT(a1.ano, f->atvf[0].ano);                 //Verifica se a fila recebeu a1.ano corretamente

    // Definicao dos campos da atividade 2:
    a2.topico[MAX_TAREFA] = "Calculo";
    a2.atividade[MAX_TAREFA] = "Estudar_para_P3";
    a2.dia = 10;
    a2.mes = 7;
    a2.ano = 2021;

    fInsere(f, a2);                                                //Insere a atividade a2 na fila f

    TEST_ASSERT_EQUAL_STRING(a2.topico, f->atvf[1].topico);        //Verifica se a fila recebeu a2.topico corretamente
    TEST_ASSERT_EQUAL_STRING(a2.atividade, f->atvf[1].atividade);  //Verifica se a fila recebeu a2.atividade corretamente
    TEST_ASSERT_EQUAL_INT(a2.dia, f->atvf[1].dia);                 //Verifica se a fila recebeu a2.dia corretamente
    TEST_ASSERT_EQUAL_INT(a2.mes, f->atvf[1].mes);                 //Verifica se a fila recebeu a2.mes corretamente
    TEST_ASSERT_EQUAL_INT(a2.ano, f->atvf[1].ano);                 //Verifica se a fila recebeu a2.ano corretamente
}



//Teste da funcao fRemove
void teste6() {
    
    fila *f;
    f = fInicializa();                                    

    atividade a1, a2;       

    TEST_ASSERT_EQUAL(0, f->quantidade); // Verifica se a fila esta vazia                          

    // Definicao dos campos da atividade 1:
    a1.topico[MAX_TAREFA] = "Calculo";
    a1.atividade[MAX_TAREFA] = "Estudar_para_P3";
    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 2020;

    fInsere(f, a1);        
    TEST_ASSERT_EQUAL(1, f->quantidade); // Verifica se a fila tem um elemento
    fRemove(f);
    TEST_ASSERT_EQUAL(0, f->quantidade); // Verifica se a fila esta vazia

    // Definicao dos campos da atividade 2:
    a2.topico[MAX_TAREFA] = "Matematica_Discreta";
    a2.atividade[MAX_TAREFA] = "Entregar_Trabalho";
    a2.dia = 12;
    a2.mes = 10;
    a2.ano = 2023;                           

    fInsere(f, a2);        
    TEST_ASSERT_EQUAL(1, f->quantidade); // Verifica se a fila tem um elemento
    fRemove(f);
    TEST_ASSERT_EQUAL(0, f->quantidade); //Verifica novamente se a fila esta vazia
                
}


//Teste da funcao lInicializa
void teste7() {

    lista l;
    lInicializa(&l, menor);

    // Testa se o ponteiro do sentinela eh igual ao proximo e anterior a ele mesmo
    TEST_ASSERT_EQUAL_PTR(l.sentinela, l.sentinela->next); 
    TEST_ASSERT_EQUAL_PTR(l.sentinela, l.sentinela->prev);
    // Testa se a quantidade de elementos eh igual a zero
    TEST_ASSERT_EQUAL(0, l.quantidade);

}


//Teste da funcao lValido
//Aqui verificamos o funcionamento da funcao lValido.
//Apos inicializar uma sentinela e um iterador i, passamos a posicao i do iterador sendo l.sentinela->next
//E l.estrutura recebe o endereco da lista l.
//Fazendo TEST_ASSERT_TRUE analisamos se a posicao do iterador NAO eh a sentinela. Caso a posicao nao seja a 
//sentinela, entao a posicao nao eh valida para manipulacao e a funcao lValido retorna 1, assim, o teste passa.
//O segundo teste consiste em passar o endereco da sentinela para o iterador (i.posicao = l.sentinela),
//desse modo, o teste lValido deve retornar Falso, ja que a posicao eh a sentinela e nao pode ser usada para
//manipulacao. Com TEST_ASSERT_FALSE verificamos que lValido retorna Falso, e o teste passa.
void teste8() {                                                       

    lista l;
    l.sentinela = malloc(sizeof(l.sentinela));                         //Aloca espaco para uma sentinela da lista
    l.sentinela->next = NULL;                                          //Inicializa a sentinela
   
    iterador i;
    i.posicao = l.sentinela->next;                                     
    i.estrutura = &l;
    
    TEST_ASSERT_TRUE(lValido(i));

    // Testa se a posicao eh sentinela, logo nao eh valida para manipulacao
    i.posicao = l.sentinela;
    TEST_ASSERT_FALSE(lValido(i));
}


//Teste da funcao lTamanho
void teste9() {

    lista l;
    lInicializa(&l, menor);

    atividade a1, a2;

    // Insere uma atividade na lista e verifica se o tamanho eh igual a 1
    a1.topico[MAX_TAREFA] = "Calculo";
    a1.atividade[MAX_TAREFA] = "Estudar_para_P3";
    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 2020;
    lInsere (&l, a1);
    TEST_ASSERT_EQUAL_INT(1, l.quantidade);

    // Insere outra atividade na lista e verifica se o tamanho eh igual a 2
    a2.topico[MAX_TAREFA] = "Estruturas_de_Dados";
    a2.atividade[MAX_TAREFA] = "Entregar_Projeto";
    a2.dia = 12;
    a2.mes = 9;
    a2.ano = 2023;
    lInsere (&l, a2);
    TEST_ASSERT_EQUAL_INT(2, l.quantidade);
}


//Teste da funcao lPrimeiro
void teste10() {

    lista l;
    lInicializa(&l, menor);

    atividade a1, a2;

    //Insere a primeira atividade na lista:
    a1.topico[MAX_TAREFA] = "Calculo";
    a1.atividade[MAX_TAREFA] = "Estudar_para_P3";
    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 2020;
    lInsere (&l, a1);

    //Insere a segunda atividade na lista:
    a2.topico[MAX_TAREFA] = "Estruturas_de_Dados";
    a2.atividade[MAX_TAREFA] = "Entregar_Projeto";
    a2.dia = 12;
    a2.mes = 9;
    a2.ano = 2023;
    lInsere (&l, a2);

    //Obtem o primeiro no da lista:
    iterador i = lPrimeiro(&l);

    //Testa se o primeiro no retornado eh o primeiro no da lista:
    TEST_ASSERT_EQUAL_PTR(l.sentinela->next, i.posicao);
    TEST_ASSERT_EQUAL_PTR(&l, i.estrutura);
}



//Teste da funcao lProximo
void teste11() {
 
    lista l;
    lInicializa(&l, menor);

    atividade a1, a2;
    
    //Insere a primeira atividade na lista:
    a1.topico[MAX_TAREFA] = "Calculo";
    a1.atividade[MAX_TAREFA] = "Estudar_para_P3";
    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 2020;
    lInsere (&l, a1);
    
    //Insere a segunda atividade na lista:
    a2.topico[MAX_TAREFA] = "Estruturas_de_Dados";
    a2.atividade[MAX_TAREFA] = "Entregar_Projeto";
    a2.dia = 12;
    a2.mes = 9;
    a2.ano = 2023;
    lInsere (&l, a2);

    iterador i = lPrimeiro(&l); // Inicializa o iterador na primeira posicao da lista
    iterador p = lProximo(i); // Avança o iterador para a proxima posicao

    TEST_ASSERT_EQUAL_PTR(l.sentinela->next->next, p.posicao); // Testa se a posicao atual do iterador eh a posicao correta
    TEST_ASSERT_EQUAL_PTR(i.estrutura, p.estrutura); // Testa se o iterador esta apontando para a mesma lista
}


//Teste da funcao lElemento
void teste12() {

    lista l;
    lInicializa(&l, menor);

    atividade a1, a2;

    //Insere a primeira atividade na lista:
    a1.topico[MAX_TAREFA] = "Calculo";
    a1.atividade[MAX_TAREFA] = "Estudar_para_P3";
    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 2020;
    lInsere (&l, a1);
    
    //Insere a segunda atividade na lista:
    a2.topico[MAX_TAREFA] = "Estruturas_de_Dados";
    a2.atividade[MAX_TAREFA] = "Entregar_Projeto";
    a2.dia = 12;
    a2.mes = 9;
    a2.ano = 2023;
    lInsere (&l, a2);

    // Obtem o primeiro elemento da lista:
    iterador i = lPrimeiro(&l);

    // Verifica se a atividade do primeiro elemento eh a atividade a1:
    TEST_ASSERT_EQUAL_STRING(a1.atividade, lElemento(i).atividade);

    // Avança para o proximo elemento da lista:
    i = lProximo(i);

    // Verifica se a atividade do segundo elemento eh a atividade a2:
    TEST_ASSERT_EQUAL_STRING(a2.atividade, lElemento(i).atividade);

}


//Teste da funcao lDestroi
//Neste teste analisamos o funcionamento da funcao lDestroi
//Depois de inicializarmos a lista e inserirmos duas atividades nela, utilizamos a funcao lDestroi 
//para destruir a lista. Nos testes, verificamos se a quantidade de elementos na lista eh 0 apos
//sua detruicao, para isso usamos a funcao do Unity TEST_ASSERT_EQUAL_INT(0, l.quantidade).
//Ja para verificar se a sentinela aponta para NULL apos a destruicao testamos com a funcao
//TEST_ASSERT_EQUAL_PTR(NULL, l.sentinela)
//Caso os valores e enderecos estejam corretos o teste passa!
void teste13(){

    lista l;
    lInicializa(&l, menor);                                         //Inicializa a lista

    atividade a1, a2;

    a1.topico[MAX_TAREFA] = "Calculo!";
    a1.atividade[MAX_TAREFA] = "Estudar_para_P3";
    a1.dia = 30;
    a1.mes = 5;
    a1.ano = 1431;
    lInsere (&l, a1);                                               //Insere atividade a1 na lista
    
    a2.topico[MAX_TAREFA] = "Matematica_Discreta";
    a2.atividade[MAX_TAREFA] = "Entregar_Trabalho";
    a2.dia = 7;
    a2.mes = 9;
    a2.ano = 1822;
    lInsere (&l, a2);                                               //Insere atividade a2 na lista

    lDestroi(&l);                                                   //Destroi a lista

    TEST_ASSERT_EQUAL_INT(0, l.quantidade);                         //Testa se a quantidade de elementos na lista eh 0
    TEST_ASSERT_EQUAL_PTR(NULL, l.sentinela);                       //Testa se a sentinela aponta para NULL
}


//Teste da funcao lVazia
void teste14() {
    
    lista l;

    lInicializa(&l, menor);
    
    TEST_ASSERT_EQUAL_INT(1, lVazia(&l)); // Testa se a lista esta vazia com a funcao lVazia
    TEST_ASSERT_EQUAL_INT(0, l.quantidade); // Testa se a quantidade de elementos na lista eh zero

    atividade a1;

    //Insere a atividade na lista:
    a1.topico[MAX_TAREFA] = "Fisica";
    a1.atividade[MAX_TAREFA] = "Estudar_Conservacao_de_Energia";
    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 2020;
    lInsere(&l, a1);
    
    TEST_ASSERT_EQUAL_INT(0, lVazia(&l)); // Testa se a lista nao esta mais vazia
    TEST_ASSERT_EQUAL_INT(1, l.quantidade); // Testa se a quantidade de elementos na lista eh igual a 1
}



//Teste da funcao lInsere
//Neste teste analisamos o funcionamento da funcao lInsere
//OBS: como a insercao eh baseada pela data devido a funcao menor, entao a1<a3<a2 pelo exemplo utilizado
//No teste verificamos se as strings e as datas foram passadas corretamente para seus devidos enderecos
//por meio das funcoes do unity TEST_ASSERT_EQUAL_STRING e TEST_ASSERT_EQUAL_INT.
//Alem disso testamos tambem se a quantidade esta sendo incrementada.
//Caso todos os testes passem a funcao esta funcionando perfeitamente!
void teste15(){

    lista l;
    lInicializa(&l, menor);                                              //Inicializa a lista

    atividade a1, a2, a3;

    a1.topico[MAX_TAREFA] = "Fisica";
    a1.atividade[MAX_TAREFA] = "Estudar_Cinematica";
    a1.dia = 15;
    a1.mes = 11;
    a1.ano = 1889;
    lInsere (&l, a1);                                                    //Insere atividade a1 na lista
    TEST_ASSERT_EQUAL_INT(1, l.quantidade);                              //Verifica se quantidade de elementos na lista esta correta
    
    a2.topico[MAX_TAREFA] = "Matematica_Discreta";
    a2.atividade[MAX_TAREFA] = "Entregar_Trabalho";
    a2.dia = 1;
    a2.mes = 1;
    a2.ano = 2023;
    lInsere (&l, a2);                                                    //Insere atividade a2 na lista
    TEST_ASSERT_EQUAL_INT(2, l.quantidade);                              //Verifica se quantidade de elementos na lista esta correta

    a3.topico[MAX_TAREFA] = "Calculo";
    a3.atividade[MAX_TAREFA] = "Estudar_para_P2";
    a3.dia = 1;
    a3.mes = 1;
    a3.ano = 2018;
    lInsere (&l, a3);                                                    //Insere atividade a3 na lista
    TEST_ASSERT_EQUAL_INT(3, l.quantidade);                              //Verifica se quantidade de elementos na lista esta correta

    TEST_ASSERT_EQUAL_STRING(a1.topico, l.sentinela->next->data.topico);
    TEST_ASSERT_EQUAL_STRING(a1.atividade, l.sentinela->next->data.atividade);
    TEST_ASSERT_EQUAL_INT(a1.dia, l.sentinela->next->data.dia);
    TEST_ASSERT_EQUAL_INT(a1.mes, l.sentinela->next->data.mes);
    TEST_ASSERT_EQUAL_INT(a1.ano, l.sentinela->next->data.ano);

    TEST_ASSERT_EQUAL_STRING(a2.topico, l.sentinela->next->next->next->data.topico);
    TEST_ASSERT_EQUAL_STRING(a2.atividade, l.sentinela->next->next->next->data.atividade);
    TEST_ASSERT_EQUAL_INT(a2.dia, l.sentinela->next->next->next->data.dia);
    TEST_ASSERT_EQUAL_INT(a2.mes, l.sentinela->next->next->next->data.mes);
    TEST_ASSERT_EQUAL_INT(a2.ano, l.sentinela->next->next->next->data.ano);

    TEST_ASSERT_EQUAL_STRING(a3.topico, l.sentinela->next->next->data.topico);
    TEST_ASSERT_EQUAL_STRING(a3.atividade, l.sentinela->next->next->data.atividade);
    TEST_ASSERT_EQUAL_INT(a3.dia, l.sentinela->next->next->data.dia);
    TEST_ASSERT_EQUAL_INT(a3.mes, l.sentinela->next->next->data.mes);
    TEST_ASSERT_EQUAL_INT(a3.ano, l.sentinela->next->next->data.ano);

    
}


//Teste da funcao lRetira
void teste16() {

    lista l;
    lInicializa(&l, menor);

    atividade a1, a2;

    //Insere a atividade 1 na lista:
    strcpy(a1.topico, "Fisica");
    strcpy(a1.atividade, "Estudar_Conservacao_de_Energia");
    a1.dia = 20;
    a1.mes = 12;
    a1.ano = 2020;
    lInsere(&l, a1);

    //Insere a atividade 2 na lista:
    strcpy(a2.topico, "Matematica");
    strcpy(a2.atividade, "Resolver_exercicios_de_Analise_Combinatoria");    
    a2.dia = 15;
    a2.mes = 3;
    a2.ano = 2023;
    lInsere(&l, a2);

    //Retira a primeira atividade:
    iterador i = lPrimeiro(&l);
    i = lRetira(i);

    //Verifica se a lista nao esta vazia e se a atividade restante eh a esperada:
    TEST_ASSERT_EQUAL_INT(lVazia(&l), 0);
    TEST_ASSERT_EQUAL_STRING("Matematica", lElemento(i).topico);
    TEST_ASSERT_EQUAL_STRING("Resolver_exercicios_de_Analise_Combinatoria", lElemento(i).atividade);
    TEST_ASSERT_EQUAL_INT(1, l.quantidade);
}


int main(){

    UNITY_BEGIN();         

    RUN_TEST(teste_menor);                                                       
    RUN_TEST(teste1);                                                         
    RUN_TEST(teste2);                                                           
    RUN_TEST(teste3);                                                           
    RUN_TEST(teste4);                                                           
    RUN_TEST(teste5);                                                          
    RUN_TEST(teste6);                                                           
    RUN_TEST(teste7);                                                         
    RUN_TEST(teste8);                                                          
    RUN_TEST(teste9);                                                       
    RUN_TEST(teste10);                                                          
    RUN_TEST(teste11);      
    RUN_TEST(teste12);   
    RUN_TEST(teste13);
    RUN_TEST(teste14);         
    RUN_TEST(teste15); 
    RUN_TEST(teste16);                                                                                        

    return UNITY_END();
}