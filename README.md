# Projeto prático de Estrutura de Dados
Foi desenvolvido pelos integrantes do grupo uma aplicação de (_Tasks_) em C utilizando como estrutura de dados principais a Fila e uma Lista Duplamente Encadeada Circular e com Sentinela.

## Desenvolvimento da ideia
Ao seguir aquilo que foi proposto pelo docente, foi implementada uma "To do list" em C na tentativa de respeitar ao máximo os conceitos de encapsulamento que envolvem os Tipos Abstratos de Dados, ao utilizar as estruturas de dados citadas anteriormente, buscando a melhor efiência possível para as operações que são "requisitadas" pela aplicação. Desse modo, seguem os pápeis de cada Estrutura dentro do projeto:
* Fila: Receber e armazenar as atividades na ordem que são inseridas, de modo a viabilizar tambem a remoção destas. Ao analisar do ponto de vista prático, são utilizadas para que se atrelem as atividades inseridas a um determinado tópico.
* Lista: Armazena toda informação inserida anteriormente na lista, de modo a ordenar por data de entrega assim que são transferidas da fila. Além disso, será possível, graças a esta estrutura, remover tópicos por completo e consequentemente suas atividades.

### Desenvolvimento da Fila

* <strong> struct fila</strong>: encontram-se váriaveis alocadas estáticamente e um vetor de atividades que futuramente será alocado dinamicamente para possibilitar manipulações na fila;

* <strong> fila* fInicializa()</strong>: esta função tem como principal encargo preparar a fila quando requisitado pelo usuário, alocando dinamicamente a fila, definindo os apontadores de primeiro e último como zero (apontando para a primeira posição do vetor), alocando o vetor dinamicamente e a inicializando a quantidade de elementos igual a zero. Para que não haja a perda da fila alocada é retornado seu endereço para o usuário.

* <strong> void fDestroi(fila *f)</strong>: já este procedimento tem como seu papel desalocar toda a memória utilizada pela fila, ou seja, remove todos os seus elementos, um a um, até que esta esteja vazia e logo após desaloca o vetor anteriormente requistado assim como o "endereço base" utilizado na fila;

* <strong> int fVazia(fila *f)</strong>: nesta função encontramos uma ocupação de simples implementação mas de grande utilidade, isto se da graças a sua capacidade de retornar se a fila está vazia ou não se baseando na quantidade de elementos inseridos na estrutura, afinal se este contador está com seu conteúdo igual a zero estamos em uma situação de fila vazia e em qualquer outra situação (maior que zero) possuimos elementos na fila;

* <strong> int fTamanho(fila *f)</strong>: novamente, esta função possui uma incumbencia bem simples, mas muito útil, pois retorna o tamanho da fila para o usuário, ou seja, a quantidade de elementos presentes na fila neste momento;

* <strong> int fInsere(fila *f, A atvf)</strong>: aqui encontra-se a principal forma de inserir elementos na fila, deste modo, é feita, inicialmente, uma verificação para concretizar se é possível inserir mais elementos na fila ou se esta encontra-se cheia no momento, caso seja possível inserir é copiada a informação passada como parâmetro ao vetor e os índices deste são manipulados de modo a articular a funcionalidade dele para futuras operações também retornando 1 para o usuário atestando o correto funcionamento, porém caso não seja possível inserir é retornado zero indicando tal falha;

* <strong> A fRemove(fila *f)</strong>: nesta função viabiliza-se a remoção dos elementos presentes na fila, ou seja, são removidas atividades quando solicitado, assim sendo, caso a fila estiver vazia é retornado uma estrutura auxiliar para sinalizar que não foi possível retirar elementos, afinal não há nenhum elemento a se retirar, agora caso a fila esteja com elementos a ser retirados, o primeiro elemento da fila sai, através do uso de uma variável auxiliar alocada durante a execução da função que recebe a estrutura referente a atividade do índice em questão, havendo as devidas manipulações de indice e atualização da quantidade de elementos (com o retorno da estrutura retirada, verificando o correto funcionamento).

### Desenvolvimento da Lista 

* <strong> struct iterador</strong>: encontram-se váriaveis necessárias para percorrer a estrutura com um iterador;

* <strong> struct lista</strong>: encontram-se váriaveis utéis para manipulação da lista;

* <strong> struct node</strong>: aqui encontram-se informações relativas aos nós da lista, seus apontadores para frente (próximo) e para trás (anterior) e também uma variável do tipo <strong>atividade</strong> que tornará a inserção de dados relativos as atividades nos nós muito mais organizadas e limpas;

* <strong> void lInicializa(lista *l, int (*menor)(A,A))</strong>: este procedimento tem o papel de inicializar a lista requisitada pelo usuário, ou seja, alocar o sentinela, já manipular os apontadores para manter a circularidade, colocar a quantidade de elementos da lista igual a zero e atribuir o endereço da função "menor" ao ponteiro "menor";

* <strong> void lDestroi(lista *l)</strong>: neste procedimento encontramos a desalocação dos nós utilizados na lista, um a um, enquanto esta não estiver vazia, e por fim desalocamos o sentinela, retirando todo e qualquer elemento da lista da memória;

* <strong> int lInsere(lista *l, A data)</strong>: aqui há a inserção de um dado de tipo A na lista de forma ordenada. Para isso, primeiro há a alocação do novo nó, e então a atribuição desse dado para o nó e para o sentinela, para que haja uma condição de parada durante a inserção ordenada. Durante a inserção, o elemento é comparado um a um até que encontre um que seja maior ou igual e há então a manipulação dos apontadores para que seja inserido na lista, assim como um incremento na quantidade. Importante destacar que a função retorna 0 caso haja alguma falha na alocação e retorna 1 caso tenha sucesso;

* <strong> iterador lRetira(iterador i)</strong>: agora, com o procedimento em questão, é retirado um elemento em específico da lista apontado pelo iterador passado como parâmetro, funcionalidade muito útil quando aliada à função <strong>lDestroi</strong>, ao remover nó a nó do começo da lista e, concomitantemente, atualizar a quantidade de elementos. Além disso, possui retorno do tipo iterador, o qual caso seja possível retirar o nó em questão, retorna um iterador que aponta para o nó seguinte ao removido;

* <strong> int lVazia(lista *p)</strong>: encontra-se neste caso uma função de rápida implementação para averiguar se há elementos na lista ou não, pois se o elemento posterior ao sentinela for o próprio sentinela, pela propriedade de circularidade deduzimos que a lista está vazia, caso contrário ainda se possui elementos na lista;

* <strong> int lTamanho(lista *p)</strong>: de maneira análoga à função anterior, esta função é de rápida implementação e desta vez retorna o tamanho da lista para o usuário, ou seja, retorna a quantidade de elementos presentes na lista;

* <strong> int lValido(iterador i)</strong>: outra função de rápido entendimento, é responsável por verificar se o nó apontado por i não é o sentinela, de modo a evitar que haja a remoção inadequada neste componente da lista;

* <strong> iterador lPrimeiro(lista *l)</strong>: recebe uma lista como parâmetro e retorna um iterador apontando para o primeiro elemento dessa estrutura;

* <strong> iterador lProximo(iterador i)</strong>: essa função recebe como parâmetro um iterador, o qual deve apontar para algum elemento de uma estrutura, para então retornar o elemento elemento seguinte a ele;

* <strong> A lElemento(iterador i)</strong>: assim como na função anterior, é recebido um iterador como parâmetro, o qual aponta para algum nó da estrutura, em seguida tem como retorno o campo "data" referente estrutura do nó da lista;


### Atividade.h e seu importante papel
Essa biblioteca é a principal responsável por armazenar, através da <strong>struct atividade</strong>, as informações atreladas a cada atividade, ou seja, o nome da atividade, seu tópico e sua data de entrega dado por dia, mês e ano. Sob tal lógica, notabiliza-se a importância de sua presença na implementação pois além de armazenar dados valiosos para o usuário, torna o último capaz de alterar com facilidade qualquer campo que desejar para sua aplicação, tornando versátil o uso da mesma em variados contextos; 

### Ambiente de testes Unity
O Unity é uma plataforma muito versátil para a criação de testes unitários e pode ser usada para testar qualquer tipo de software, incluindo aplicações de produtividade como o (_Tasks_). Quando se quer garantir que o código implementado seja testado de maneira adequada é possível usar o Unity para criar e executar testes unitários para cada parte de sua aplicação, como a criação de uma nova tarefa, a edição de uma tarefa existente ou a exclusão de uma tarefa. Em suma, viabiliza-se a criação de testes para cada função da aplicação, garantindo que o código produzido esteja livre de erros e que a funcionalidade de cada tarefa seja testada completamente, por exemplo, foi criado um teste unitário para garantir que a função de inserção de tarefa funcione corretamente, assim sendo, foram fornecidos alguns dados de entrada para a função, como o nome da tarefa e sua descrição, e foi testado se a função insere corretamente na fila a nova tarefa com essas informações adequadas. Vale salientar que com esses testes, podemos ter certeza de que nossa aplicação funcionará conforme o esperado e que quaisquer alterações feitas no código não afetarão outras partes do sistema. Portanto, ao usar o Unity para testar uma aplicação, notabiliza-se a robustez, confiabilidade e assertividade dos códigos, auxiliando a criação de softwares de alta qualidade.
Além disso, os comentários presentes durante a construção dos testes tem como intuito gerar uma melhor compreensão sobre como cada teste é fundamentado;

## Aplicação no dia-a-dia
Este projeto foi criado com o intuito de facilitar a organização diária da pessoa que o utiliza de maneira a gerar menos confusões com relação as suas atividades e maior assertividade, produtividade e gestão de tempo ao realizá-las. Ademais, esta aplicação ainda auxilia a criar mais conforto ao usuário durante seu processo de organização, pois ao escrever suas atividades este torna-se menos ansioso e preocupado, com uma visão mais clara do que realizar primeiro e como pode gerir seus esforços de forma a obter os melhores resultados em suas tarefas.