#include "log.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
NOTACAO
'=' == se
'-' == entao
'*' == e
'!' == negacao
'+' == ou 
*/

Lista *criar(){
    Lista *l = (Lista *)malloc(sizeof(Lista));
    l->inicio = NULL;
    return l;
}

FILE *abrir(){
    FILE *f = fopen("sub.txt", "ab+");
    return f;
}

void fechar(FILE *f){
    fclose(f);
}

int inserirfim(Lista *l, simbolo c){
    if(l == NULL) return 3;
    if(listaVazia(l) == 0)
        return inseririnicio(l, c);

    No *n1 = l->inicio, *n = (No *)malloc(sizeof(No));
    while(n1->prox != NULL)
        n1 = n1->prox;
    n->sim = c;
    n->prox = n1->prox;
    n1->prox = n;
    return 0;
}

int inseririnicio(Lista *l, simbolo c){
    if(l == NULL) return 3;
    No *n = (No *)malloc(sizeof(No));
    n->sim = c;
    n->prox = l->inicio;
    l->inicio = n;
    return 0;
}

int removerinicio(Lista *l){
    if(l == NULL) return 3;
    if(listaVazia(l) == 0) return 1;
    No *n = l->inicio;
    l->inicio = n->prox;
    free(n);
    return 0;
}

int removerfim(Lista *l){
    if(l == NULL) return 3;
    if(listaVazia(l) == 0) return 1;
    No *n = l->inicio;
    while(n->prox != NULL)
        n = n->prox;
    if(l->inicio->prox == NULL)
        l->inicio = NULL;
    else
        n = NULL;
    return 0;
}

int listaVazia(Lista *l){
    if(l == NULL) return 3;
    if(l->inicio == NULL)
        return 0;

    return 1;
}

void limpar(Lista *l) {
    while (listaVazia(l) != 0)
        removerinicio(l);
}

int verificar(Lista *l){
    if(l == NULL) return 3;
    if(listaVazia(l) == 0) return 2;

    No *n = l->inicio;
    int cont = 0;
    if(l->inicio->sim.caractere == ')' || l->inicio->sim.caractere == '*' || l->inicio->sim.caractere == '+' || l->inicio->sim.caractere == '-' || l->inicio->sim.caractere == '=')
        return 4;

    while(n != NULL){
        if(n->sim.caractere == '(') {
            cont++;
            if(n->prox->sim.caractere == ')' || n->prox->sim.caractere == '*' || n->prox->sim.caractere == '+' || n->prox->sim.caractere == '-' || n->prox->sim.caractere == '=' || n->prox == NULL)
                return 5;
        }
        else if(n->sim.caractere == ')'){
            cont--;
            if(n->prox == NULL)
                return 0;
            else if(n->prox->sim.caractere == '(' || (n->prox->sim.caractere >= 'A' && n->prox->sim.caractere <= 'Z'))
                return 6;
        }
        else if(n->sim.caractere == '+'){
            if(n->prox->sim.caractere == ')' || n->prox->sim.caractere == '*' || n->prox->sim.caractere == '+' || n->prox->sim.caractere == '-' || n->prox->sim.caractere == '=' || n->prox == NULL)
                return 7;
        }
        else if(n->sim.caractere == '*'){
            if(n->prox->sim.caractere == ')' || n->prox->sim.caractere == '*' || n->prox->sim.caractere == '+' || n->prox->sim.caractere == '-' || n->prox->sim.caractere == '=' || n->prox == NULL)
                return 8;
        }
        else if(n->sim.caractere == '-'){
            if(n->prox->sim.caractere == ')' || n->prox->sim.caractere == '*' || n->prox->sim.caractere == '+' || n->prox->sim.caractere == '-' || n->prox->sim.caractere == '=' || n->prox == NULL)
                return 9;
        }
        else if(n->sim.caractere == '='){
            if(n->prox->sim.caractere == ')' || n->prox->sim.caractere == '*' || n->prox->sim.caractere == '+' || n->prox->sim.caractere == '-' || n->prox->sim.caractere == '=' || n->prox == NULL)
                return 10;
        }
        else if(n->sim.caractere == '!'){
            if(n->prox->sim.caractere == ')' || n->prox->sim.caractere == '*' || n->prox->sim.caractere == '+' || n->prox->sim.caractere == '-' || n->prox->sim.caractere == '=' || n->prox == NULL)
                return 11;
        }
        else if(n->sim.caractere >= 'A' && n->sim.caractere <= 'Z'){
            if(n->prox == NULL)
                return 0;
            else if(n->prox->sim.caractere == '!' || n->prox->sim.caractere == '(' || (n->prox->sim.caractere >= 'A' && n->prox->sim.caractere <= 'Z'))
                return 12;
        }
        else
            return 13;

        if(n->prox == NULL && cont != 0)
            return 20;
        if(cont < 0)
            return 30;

        n = n->prox;
    }
}

/*int subformula(Lista *l){

}*/

/*int interpretar(Lista *l, simbolo termo ) { //interpreta apenas 2 termos

    No *aux = l->inicio;
    /*if ( ( verificar(l) == 0 ) || ( verificar(l) <= 12 ) || ( verificar(l) == 13 ) || (verificar(l) >= 30)  ) {
        printf("\nTESTE VERIFICAR."); 
        return -4;
    }
    for (No *aux= l->inicio; aux != NULL; aux = aux->prox ) {

        No *aux2 = aux->prox;
        printf("\nTESTE AUX: %c, %d", aux->sim.caractere, aux->sim.valor_vdd_1);
        printf("\nTESTE AUX2: %c, %d", aux2->sim.caractere, aux2->sim.valor_vdd_1);



            if (aux->sim.conectivo == '=' ) {
                
                if ( aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 0 ) {
                    return 0;
                }
                else {
                    return 1; 
                }

            }

            if (aux->sim.conectivo == '-') {

                if ( (aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 1) || (aux->sim.valor_vdd_1 == 0 && aux2->sim.valor_vdd_1 == 0) ) {
                    return 1;
                }
                else {
                    return 0;
                }
            }

            if (aux->sim.conectivo == '*') {

                if (aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 1) {
                    return 1;
                }
                else if (aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 0) {
                    return 0;
                }
                else if (aux->sim.valor_vdd_1 == 0 && aux2->sim. valor_vdd_1 == 1) {
                    return 0;
                }
                else if (aux->sim.valor_vdd_1 == 0 && aux2->sim.valor_vdd_1 == 0) {
                    return 0;
                }
             }

             if (aux->sim.conectivo == '!' && aux->sim.valor_vdd_1 == 1) {
                aux->sim.valor_vdd_1 = 0;
             }
             if (aux->sim.conectivo == '1' && aux->sim.valor_vdd_1 == 0) {
                aux->sim.valor_vdd_1 = 1;
             }
             if (aux2->sim.conectivo == '!' && aux2->sim.valor_vdd_1 == 1) {
                aux2->sim.valor_vdd_1 = 0;
             }
             if (aux2->sim.conectivo == '1' && aux2->sim.valor_vdd_1 == 0) {
                aux2->sim.valor_vdd_1 = 1;
             }  

             
             if (aux->sim.conectivo == '+') {

                if (aux->sim.valor_vdd_1 == 0 && aux2->sim.valor_vdd_1 == 0) {
                    return 0;
                }
                else if (aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 1) {
                    return 1; 
                }
                else if (aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 0) {
                    return 1;
                }
                else if (aux->sim.valor_vdd_1 == 0 && aux2->sim.valor_vdd_1 == 1) {
                    return 1;
                }

             }


    } 

}*/ 



void mostrar(Lista *l) {
    if (l != NULL) {
        No *aux = l->inicio; 
        while (aux != NULL) {
            printf("[CARACTERE [%c]  CONECTIVO [%c] VALOR VDD [%d] \n]", aux->sim.caractere, aux->sim.conectivo, aux->sim.valor_vdd_1);
            aux = aux->prox;
        }
    }
}

void menu_inicial() {
    printf("==========BEM VINDO==========\nCALCULADORA DE FORMULAS LOGICAS DESENVOLVIDO POR: \nEDUARDO TRINDADE\nVITOR MARTINS ROCHA.");
    printf("\nB.C.C. - T.C.D. DE ALGORITMOS E ESTRUTURAS DE DADOS 1.\n");
}

void menu_notacao() {
    printf("\n\nNOTACAO: 0 = FALSE \t1 = TRUE.\n");
    printf("\nAPRESENTE UM TERMO\n ");
}

pilha *criar_pilha () {

    pilha *p = (pilha *) malloc(sizeof(pilha)); 
    if (p == NULL) {
        return NULL; 
    }
    p->topo = NULL;
    return p;

}

int pilha_vazia(pilha *p) {
    if (p == NULL) {
        return -1;
    }
    if (p->topo == NULL) {
        return -3;
    }
    else {
        return -2; 
    }
}

int pop (pilha *p, form_val *valor) {

    if ( p == NULL) {
        return -1;
    }
    if ( pilha_vazia(p) == -3 ) {
        return -3;
    }

    if (valor != NULL) {
    
        pilha_no *aux; 
        aux = p->topo;

        *valor= aux->info; 
        p->topo = aux->prox;

        free(aux); 
        return 1;
    }
    if (valor == NULL) {
        
        pilha_no *aux = p->topo; 
        p->topo = aux->prox;
        free(aux); 

        return 1;
    }

}

void limpar_pilha(pilha *p) {

    if (p == NULL) {
        return ; 
    }
    while (pilha_vazia(p) != -3) {
        pop(p, NULL ); 
    }

    free(p);
    p = NULL;

}

int push(pilha *p, form_val valor) {
    if (p == NULL) {
        return -1;
    }

    pilha_no *aux = (pilha_no *) malloc(sizeof(pilha_no));
    aux->info = valor; 

    aux->prox = p->topo; 
    p->topo = aux; 

    return 1; 
}

int consultar_pilha (pilha *p, form_val *valor) {
    
    if (p == NULL) {
        return -1;
    }
    if (pilha_vazia(p) == -3) {
        return -3;
    }
    pilha_no *aux; 
    
    *valor = aux->info;

    return 1; 
}

int tamanho_pilha (pilha *p) {
    if ( p == NULL ) {
        return -1;
    }
    
    int contador = 0; 
    pilha_no *temp = p->topo; 

    while (temp != NULL) {
        contador++;
        temp = temp->prox; 
    }
    return contador;
}

void mostrar_pilha (pilha *p) {
    if ( p != NULL ) {
        printf("\n======PILHA======\n{ \n");
        pilha_no *aux = p->topo;
        while ( aux != NULL ) {
            printf("[ TERMO 1: %c, CONECTIVO %c, TERMO 2: %c ]\n", aux->info.termo1, aux->info.conectivo,aux->info.termo2);
            aux = aux->prox;
        } 
        printf(" }"); 
    }
}


int interpretar_varios(Lista *l, pilha *p, int quantidade) {
    int i; 
    int valor_verdade = -2; 
    No *aux = l->inicio; 

    for (i=0; i < quantidade, aux->prox != NULL; i++, aux = aux->prox) {

        No *aux2 = aux->prox;
        printf("\nTESTE AUX: %c, %d", aux->sim.caractere, aux->sim.valor_vdd_1);
        printf("\nTESTE AUX2: %c, %d", aux2->sim.caractere, aux2->sim.valor_vdd_1);

        form_val informacao; 
        informacao.termo1 = aux->sim.conectivo;
        informacao.termo2 = aux2->sim.caractere;
        informacao.conectivo = aux->sim.conectivo;

        

            if (aux->sim.conectivo == '=' ) {
                
                if ( aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 0 ) {
                    valor_verdade = 0;
                }
                else {
                    valor_verdade = 1;
                }

            }

            if (aux->sim.conectivo == '-') {

                if ( (aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 1) || (aux->sim.valor_vdd_1 == 0 && aux2->sim.valor_vdd_1 == 0) ) {

                    push(p, informacao);

                    valor_verdade = 1;
                }
                else {
                    valor_verdade = 0;
                }
            }

            if (aux->sim.conectivo == '*') {

                if (aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 1) {

                    push(p, informacao);

                    valor_verdade = 1;
                }
                else if (aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 0) {
                    valor_verdade = 0;
                }
                else if (aux->sim.valor_vdd_1 == 0 && aux2->sim. valor_vdd_1 == 1) {
                    valor_verdade = 0;
                }
                else if (aux->sim.valor_vdd_1 == 0 && aux2->sim.valor_vdd_1 == 0) {
                    valor_verdade = 0;
                }
             }

             if (aux->sim.conectivo == '!' && aux->sim.valor_vdd_1 == 1) {
                aux->sim.valor_vdd_1 = 0;
             }
             if (aux->sim.conectivo == '1' && aux->sim.valor_vdd_1 == 0) {


                aux->sim.valor_vdd_1 = 1;
             }
             if (aux2->sim.conectivo == '!' && aux2->sim.valor_vdd_1 == 1) {
                aux2->sim.valor_vdd_1 = 0;
             }
             if (aux2->sim.conectivo == '1' && aux2->sim.valor_vdd_1 == 0) {


                aux2->sim.valor_vdd_1 = 1;
             }  

             
             if (aux->sim.conectivo == '+') {

                if (aux->sim.valor_vdd_1 == 0 && aux2->sim.valor_vdd_1 == 0) {
                    valor_verdade = 0;
                }
                else if (aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 1) {

                    push(p, informacao);

                    valor_verdade = 1;
                }
                else if (aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 0) {

                    push(p, informacao);

                    valor_verdade = 1;
                }
                else if (aux->sim.valor_vdd_1 == 0 && aux2->sim.valor_vdd_1 == 1) {

                    push(p, informacao);

                    valor_verdade = 1;
                }

             }


    
    }
    return valor_verdade;
}
