#include "log.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char *criar(int i){
    char *s = (char *)malloc(i * sizeof(char));
    return s;
}

int validade(char *s){
    int i = 0, j = 0;
    int k = 0;
    while(s[j] != '\0'){
        if(s[j] == '('){
            int cont1 = 1, cont2 = 0;
            for(j = i + 1; s[j] != '\0'; j++){
                if(s[j] == '('){
                    cont1++;
                }
                else if(s[j] == ')'){
                    cont2++;
                }
                else if(j == strlen(s) - 1){
                    if(cont1 != cont2)
                        return 7;
                }
            }
        }
        else if(s[k] == ')')
            return 8;
        j++;
    }
    while(s[i] != '\0'){
		if(i == strlen(s) - 1){
			if((s[i] >= 65 && s[i] >= 90) || s[i] == ')')
				return 0;
		}
        else if(s[i] == '~'){
			j = i;
            if(verNegacao(s, &j) != 0)
                return 1;
        }
        else if(s[i] == '-'){
            for(j = i + 1; 1; j++){
                if(s[j] >= 65 && s[j] <= 90){
                    break;
                }
                else if(s[j] == '=' || s[j] == '^' || s[j] == '-' || s[j] == '+' || s[i] == ')'){
                    return 2;
                }
                else if(s[j] == '~'){
                    if(verNegacao(s, &j) != 0)
                        return 1;
                    else
                        break;
                }
                else if(j == strlen(s) - 1){
                    return 3;
                }
            }
        }
        else if(s[i] == '='){
            for(j = i + 1; 1; j++){
                if(s[j] >= 65 && s[j] <= 90){
                    break;
                }
                else if(s[j] == '=' || s[j] == '^' || s[j] == '-' || s[j] == '+' || s[j] == ')'){
                    return 2;
                }
                else if(s[j] == '~'){
                    if(verNegacao(s, &j) != 0)
                        return 1;
                    else
                        break;
                }
                else if(j == strlen(s) - 1){
                    return 3;
                }
            }
        }
        else if(s[i] == '^'){
            for(j = i + 1; 1; j++){
                if(s[j] >= 65 && s[j] <= 90){
                    break;
                }
                else if(s[j] == '=' || s[j] == '^' || s[j] == '-' || s[j] == '+' || s[j] == ')'){
                    return 2;
                }
                else if(s[j] == '~'){
                    if(verNegacao(s, &j) != 0)
                        return 1;
                    else
                        break;
                }
                else if(j == strlen(s) - 1){
                    return 3;
                }
            }
        }
        else if(s[i] == '+'){
            for(j = i + 1; 1; j++){
                if(s[j] >= 65 && s[j] <= 90){
                    break;
                }
                else if(s[j] == '=' || s[j] == '^' || s[j] == '-' || s[j] == '+' || s[j] == ')'){
                    return 2;
                }
                else if(s[j] == '~'){
                    if(verNegacao(s, &j) != 0)
                        return 1;
                    else
                        break;
                }
                else if(j == strlen(s) - 1){
                    return 3;
                }
            }
        }
        else if(s[i] == '('){
            for(j = i + 1; 1; j++){
                if(s[j] >= 65 && s[j] <= 90){
                    break;
                }
                else if(s[j] == '=' || s[j] == '^' || s[j] == '-' || s[j] == '+' || s[j] == ')'){
                    return 2;
                }
                else if(s[j] == '~'){
                    if(verNegacao(s, &j) != 0)
                        return 1;
                    else
                        break;
                }
                else if(j == strlen(s) - 1){
                    return 3;
                }
            }
        }
        else if(s[i] == ')'){
            for(j = i + 1; 1; j++){
                if(s[j] >= 65 && s[j] <= 90){
                    return 4;
                }
                else if(s[j] == '=' || s[j] == '^' || s[j] == '-' || s[j] == '+' || s[j] == ')'){
                    break;
                }
                else if(s[j] == '~'){
                    return 1;
                }
                else if(s[j] == '('){
                    return 6;
                }
                else if(j == strlen(s) - 1){
                    break;
                }
            }
        }
        else if(s[0] >= 65 && s[0] <= 90){
            for(j = 1; 1; j++){
                if(s[j] >= 65 && s[j] <= 90){
                    return 4;
                }
                else if(s[j] == '=' || s[j] == '^' || s[j] == '-' || s[j] == '+' || s[i] == ')'){
					break;
                }
                else if(s[i] == '~'){
                    return 1;
                }
                else if(j == strlen(s) - 1){
                    return 3;
                }
            }
        }
        else if(s[i] >= 65 && s[i] <= 90){
            return 4;
        }
        else{
            return 5;
        }
        i = j;
        i++;
    }
    return 0;
}

int verNegacao(char *s, int *k){
    int j;
    for(j = *k + 1; 1; j++){
        if(s[j] >= 65 && s[j] <= 90){
            break;
        }
        else if(s[j] == '=' || s[j] == '^' || s[j] == '-' || s[j] == '+' || s[j] == ')'){
            return 1;
        }
        else if(j == strlen(s) - 1)
            return 2;
    }
    *k = j;
    return 0;
}

int separar(char *s){
    int i = 0, j;
    while(s[i] != 0){
        if(s[i] == '('){
            for(j = i + 1; 1; j++){

            }
        }
        i++;
    }
}




--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct no{
    char sim;
    struct no *prox;
}No;

typedef struct formula_logica{
    No *inicio;
}Lista;


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

int inserirfim(Lista *l, char c){
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

int inseririnicio(Lista *l, char c){
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
    if(l->inicio->sim == ')' || l->inicio->sim == '*' || l->inicio->sim == '+' || l->inicio->sim == '-' || l->inicio->sim == '=')
        return 4;

    while(n != NULL){
        if(n->sim == '('){
            cont++;
            if(n->prox->sim == ')' || n->prox->sim == '*' || n->prox->sim == '+' || n->prox->sim == '-' || n->prox->sim == '=' || n->prox == NULL)
                return 5;
        }
        else if(n->sim == ')'){
            cont--;
            if(n->prox == NULL)
                return 0;
            else if(n->prox->sim == '(' || (n->prox->sim >= 'A' && n->prox->sim <= 'Z'))
                return 6;
        }
        else if(n->sim == '+'){
            if(n->prox->sim == ')' || n->prox->sim == '*' || n->prox->sim == '+' || n->prox->sim == '-' || n->prox->sim == '=' || n->prox == NULL)
                return 7;
        }
        else if(n->sim == '*'){
            if(n->prox->sim == ')' || n->prox->sim == '*' || n->prox->sim == '+' || n->prox->sim == '-' || n->prox->sim == '=' || n->prox == NULL)
                return 8;
        }
        else if(n->sim == '-'){
            if(n->prox->sim == ')' || n->prox->sim == '*' || n->prox->sim == '+' || n->prox->sim == '-' || n->prox->sim == '=' || n->prox == NULL)
                return 9;
        }
        else if(n->sim == '='){
            if(n->prox->sim == ')' || n->prox->sim == '*' || n->prox->sim == '+' || n->prox->sim == '-' || n->prox->sim == '=' || n->prox == NULL)
                return 10;
        }
        else if(n->sim == '!'){
            if(n->prox->sim == ')' || n->prox->sim == '*' || n->prox->sim == '+' || n->prox->sim == '-' || n->prox->sim == '=' || n->prox == NULL)
                return 11;
        }
        else if(n->sim >= 'A' && n->sim <= 'Z'){
            if(n->prox == NULL)
                return 0;
            else if(n->prox->sim == '!' || n->prox->sim == '(' || (n->prox->sim >= 'A' && n->prox->sim <= 'Z'))
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

int subformula(Lista *l){

}









