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
    return 0;
}

/*int subformula(Lista *l){

}*/

int tamanho_lista(Lista *l) {
    if (l == NULL || l->inicio == NULL) {
        return -2;
    }
    int temp = 0;
    No *aux = l->inicio;
    while (aux != NULL) {
        temp++;
        aux = aux->prox;
    }
    return temp;

}

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
    printf("\n========== FORMULAS CADASTRADAS VALIDAS ==========\n");
    if (l->inicio != NULL) {
        No *aux = l->inicio;
        while (aux != NULL) {
            printf("\n[CARACTERE [%c]  CONECTIVO [%c] VALOR VDD [%d] ]\n", aux->sim.caractere, aux->sim.conectivo, aux->sim.valor_vdd_1);
            aux = aux->prox;
        }

    }
    printf("\n===================================================\n");
}

void menu_inicial() {
    printf("==========BEM VINDO==========\nCALCULADORA DE FORMULAS LOGICAS DESENVOLVIDO POR: \nEDUARDO TRINDADE\nVITOR MARTINS ROCHA.");
    printf("\nB.C.C. - T.C.D. DE ALGORITMOS E ESTRUTURAS DE DADOS 1.\n");
}

void menu_notacao() {
    printf("\n\nNOTACAO: 0 = FALSE \t1 = TRUE. \tDIGITE '!' SE DESEJAR ADICIONAR UMA NEGACAO\n");
    printf("\nAPRESENTE UM TERMO\n ");
}




/*int buscar_info(lista_dup *l, int mat) {

}*/ 

int limpar_listadup(lista_dup *l) {
    dup_no *aux;
    aux= l->first; 

    while (aux != NULL) {

        dup_no *destroy; 
        destroy = aux; 
        aux= aux->prox; 
        free (destroy);

    }

    free(l); 
    return 1;
}

void mostrar_dup(lista_dup *l) {
    printf("\n==========FORMULAS CADASTRADAS ==========\n");
    if ( l != NULL) {
        dup_no *aux = l->first;
        while (aux->prox != NULL) {
            printf("\n[TERMO : %c, CONECTIVO %c, TERMO 2: %c ]\n", aux->info.caractere, aux->info.conectivo, aux->prox->info.caractere);
            aux = aux->prox;
        }
    }
    printf("\n=========================================");
}


int interpretar_varios(Lista *l, int quantidade) {
    int i; 
    int valor_verdade = -2; 
    No *aux = l->inicio; 

    for (i=0; i < quantidade, aux != NULL; i++, aux = aux->prox) {

        No *aux2 = aux->prox;
        
        if (aux2 == NULL) {
            break;
        }

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

                    valor_verdade = 1;
                }
                else {
                    valor_verdade = 0;
                }
            }

            if (aux->sim.conectivo == '*') {

                if (aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 1) {

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
                    valor_verdade = 1;
                }
                else if (aux->sim.valor_vdd_1 == 1 && aux2->sim.valor_vdd_1 == 0) {

                    valor_verdade = 1;
                }
                else if (aux->sim.valor_vdd_1 == 0 && aux2->sim.valor_vdd_1 == 1) {

                    

                    valor_verdade = 1;
                }

             }


    
    }
    return valor_verdade;
}

int concatenar_formulas (Lista *l2, Lista *l3, char conec1, char conec2) {
    
    if (listaVazia(l2) == 0 ) {
        return 0;
    }
    No *aux = l2->inicio;
    int temp = tamanho_lista(l3);
    printf("\nTESTE TEMP = %d", temp);

    while (aux->prox != NULL) {
        if (aux->sim.caractere == conec1) {
            printf("\nTESTE: ACHOU O PRIMEIRO.\n");
            inserirfim(l3, aux->sim);
            
            if (aux->prox->sim.caractere == conec2) {
                printf("\nTESTE: ACHOU O SEGUNDO.\n");
                inserirfim(l3, aux->prox->sim);
            }
        }
        aux = aux->prox;
    }
    int aux2 = tamanho_lista(l3);
    printf("\nTESTE AUX: %d\n", aux2);

    if (temp == aux2) {
        return -3; 
    } 
    else {
        return 1; 
    }

}

int copiar_lista1(Lista *l, Lista *l2) {
    if (l == NULL || l->inicio == NULL) {
        return -2;
    } 

    No *aux = l->inicio;
    while (aux != NULL) {
        inserirfim(l2, aux->sim);
        aux = aux->prox;
    }
    return 1;

}

//retorna um valor se a lista possuir algum valor errado
int verificar_invalido(Lista *l) {
    if (l == NULL || l->inicio == NULL) {
        return -3;
    } 
    No *aux = l->inicio;
    while (aux->prox != NULL) {
        if (aux->sim.caractere == '=' || aux->sim.caractere == '+' || aux->sim.caractere == '*' || aux->sim.caractere == '!' ||aux->sim.caractere == '-' ) {
            return 1;
        }
        if ( (aux->sim.conectivo >= 90 && aux->sim.conectivo <= 65) || (aux->sim.conectivo <= 97 && aux->sim.conectivo >= 122) ) {
            return 2;
        }
        if (aux->sim.valor_vdd_1 > 1 || aux->sim.valor_vdd_1 < 0) {
            return 3; 
        }
        aux = aux->prox;
    }
    return 0;
}

void mostrar_invalido(Lista *l) {
    printf("\n========== FORMULAS CADASTRADAS INVALIDAS. ==========\n");
    if (l->inicio != NULL) {
        No *aux = l->inicio;
        while (aux != NULL) {
            printf("\n[TERMO: [%c], CONECTIVO [%c], VALOR VERDADE: [%d] ]\n", aux->sim.caractere, aux->sim.conectivo, aux->sim.valor_vdd_1);
            aux = aux->prox;
        }
    }
    printf("\n=====================================================\n");
}

int verificar_repeticao(Lista *l) {
    if (l->inicio == NULL) {
        return -2;
    }
    No *aux = l->inicio;

    while (aux != NULL) {
        No *temp = aux;

        while (temp->prox != NULL) {
            if (aux->sim.caractere == temp->prox->sim.caractere) {
                return 1;
            }
            temp = temp->prox;
        }
        aux = aux->prox;
    }

    return 0;

}
    



