#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Simbolo{
    char caractere; //caractere que sera apresentado pelo usuario
    char conectivo; //conectivo que sera apresentado pelo usuario
    int valor_vdd_1; //valor vdd que o usuario ira atribuir ao caractere. Notacao: 0 = false, 1 = true.
    int is_neg;
}simbolo;

typedef struct no{
    simbolo sim;
    struct no *prox;
}No;

typedef struct formula_logica{
    No *inicio;
}Lista; //serve apenas para a realização da interpretação de formulas logicas


typedef struct Dup_no{
    simbolo info;
    struct Dup_no *prox; 
    struct Dup_no *ant; 
}dup_no; 

typedef struct Lista_Dup{
    dup_no *first;
}lista_dup;


Lista *criar(); 

FILE *abrir();

void fechar (FILE *f); 

int inseririnicio(Lista *l, simbolo c);

int inserirfim(Lista *l, simbolo c); 

int removerinicio(Lista *l);

int removerfim(Lista *l);

int listaVazia(Lista *l);

void limpar(Lista *l);

int verificar(Lista *l);

int subformula(Lista *l); 

int tamanho_lista(Lista *l);

/* int interpretar(Lista *l, simbolo termo); 
*/  

void mostrar(Lista *l);





int interpretar_varios(Lista *l, int quantidade); //retorna um valor verdade que pode ser 0 ou 1, e se o valor for 1, guarda a formula em uma pilha.

int concatenar_formulas (Lista *l2, Lista *l3, char conec1, char conec2); 

int copiar_lista1(Lista *l, Lista *l2); //simplesmente copia o conteudo de uma lista para outra

int verificar_invalido(Lista *l); //percorre a lista l1 e verifica se algo esta errado de acordo com as regras da logica proposicional

int verificar_repeticao(Lista *l); 

