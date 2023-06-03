#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Simbolo{
    char caractere; //caractere que sera apresentado pelo usuario
    char conectivo; //conectivo que sera apresentado pelo usuario
    int valor_vdd_1; //valor vdd que o usuario ira atribuir ao caractere. Notacao: 0 = false, 1 = true.
}simbolo;

typedef struct no{
    simbolo sim;
    struct no *prox;
}No;

typedef struct formula_logica{
    No *inicio;
}Lista; //serve apenas para a realização da interpretação de formulas logicas

typedef struct Formulas_validas {

    char termo1, termo2, conectivo; //estes serao as variaveis que irao guardar os termos validos.

}form_val; 

typedef struct Pilha_no{

    form_val info;  
    struct Pilha_no *prox;

}pilha_no; 

typedef struct Pilha{

    pilha_no *topo;

}pilha; //Sera usado para guardar formulas validas


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

/* int interpretar(Lista *l, simbolo termo); 
*/  

void mostrar(Lista *l);



pilha *criar_pilha ();

int pilha_vazia(pilha *p);

int pop(pilha *p, form_val *valor); //remover e consulta 

void limpar_pilha(pilha *p); 

int push(pilha *p, form_val valor); //inserir

int tamanho_pilha (pilha *p);


int interpretar_varios(Lista *l, pilha *p, int quantidade); //retorna um valor verdade que pode ser 0 ou 1, e se o valor for 1, guarda a formula em uma pilha.



