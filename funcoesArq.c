//verifica se a formula esta escrita corretamente, alterei algumas coisas que estavam incorretas
int verificar(Lista *l){
    if(l == NULL) return 3;
    if(listaVazia(l) == 0) return 2;

    No *formula = l->inicio;
    int cont = 0;
    if(l->inicio->sim == ')' || l->inicio->sim == '*' || l->inicio->sim == '+' || l->inicio->sim == '-' || l->inicio->sim == '=')
        return 4;

    while(formula != NULL){
        if(formula->sim == '('){
            cont++;
            if(formula->prox->sim == ')' || formula->prox->sim == '*' || formula->prox->sim == '+' || formula->prox->sim == '-' || formula->prox->sim == '=' || formula->prox == NULL)
                return 5;
        }
        else if(formula->sim == ')'){
            cont--;
            if(formula->prox == NULL && cont != 0)
                return 30;
            else if(formula->prox == NULL && cont == 0)
                return 0;
            else if(formula->prox->sim == '(' || (formula->prox->sim >= 'A' && formula->prox->sim <= 'Z'))
                return 6;
        }
        else if(formula->sim == '+'){
            if(formula->prox->sim == ')' || formula->prox->sim == '*' || formula->prox->sim == '+' || formula->prox->sim == '-' || formula->prox->sim == '=' || formula->prox == NULL)
                return 7;
        }
        else if(formula->sim == '*'){
            if(formula->prox->sim == ')' || formula->prox->sim == '*' || formula->prox->sim == '+' || formula->prox->sim == '-' || formula->prox->sim == '=' || formula->prox == NULL)
                return 8;
        }
        else if(formula->sim == '-'){
            if(formula->prox->sim == ')' || formula->prox->sim == '*' || formula->prox->sim == '+' || formula->prox->sim == '-' || formula->prox->sim == '=' || formula->prox == NULL)
                return 9;
        }
        else if(formula->sim == '='){
            if(formula->prox->sim == ')' || formula->prox->sim == '*' || formula->prox->sim == '+' || formula->prox->sim == '-' || formula->prox->sim == '=' || formula->prox == NULL)
                return 10;
        }
        else if(formula->sim == '!'){
            if(formula->prox->sim == ')' || formula->prox->sim == '*' || formula->prox->sim == '+' || formula->prox->sim == '-' || formula->prox->sim == '=' || formula->prox == NULL)
                return 11;
        }
        else if(formula->sim >= 'A' && formula->sim <= 'Z'){
            if(formula->prox == NULL)
                return 0;
            else if(formula->prox->sim == '!' || formula->prox->sim == '(' || (formula->prox->sim >= 'A' && formula->prox->sim <= 'Z'))
                return 12;
        }
        else
            return 13;

        if(formula->prox == NULL && cont != 0)
            return 20;

        formula = formula->prox;
    }
}

//salva arquivo
int salvarArq(Lista *l, char *s){
    FILE *f = fopen(s, "ab+");
    if(f == NULL) return 2;
    No *formula = l->inicio;
    while(formula != NULL){
        if(fputc(formula->sim, f) == EOF){
            fclose(f);
            return 1;
        }
        formula = formula->prox;
    }
    if(fputc('\n', f) == EOF){
        fclose(f);
        return 1;
    }
    fclose(f);
    return 0;
}

//mostra as formulas cadastradas
void mostrarArq(){
    FILE *f = fopen("formulas.txt", "rb+");
    char s[100];
    if(f == NULL) return;
    while(fscanf(f, "%s", s) != EOF){
        printf("%s\n", s);
        s[0] = '\0';
    }
    fclose(f);
    return;
}

//mostra as formulas nao validas
int nao_formulas(){
    FILE *f = fopen("formulas.txt", "rb+");
    Lista *l = criar();
    char c;
    if(f == NULL) return 3;
    while(1){
        c = fgetc(f);
        if(c == '\n'){
            if(verificar(l) != 0){
                mostrarLista(l);
                limpar(l);
            }
            else
                limpar(l);
            continue;
        }
        else if(c == EOF){
            if(verificar(l) != 0)
                mostrarLista(l);
            break;
        }
        inserirfim(l,c);
    }
    fclose(f);
    return 0;
}

//mostra as formulas validas para escolha, o retorno é a quantidade de formulas validas existentes
int sao_formulas(){
    FILE *f = fopen("formulas.txt", "rb+");
    Lista *l = criar();
    char c;
    int i = 0;
    if(f == NULL) return -3;
    while(1){
        c = fgetc(f);
        if(c == '\n'){
            if(verificar(l) == 0){
                mostrarLista(l);
                salvarArq(l, "validas.txt");
                limpar(l);
                i++;
            }
            else
                limpar(l);
            continue;
        }
        else if(c == EOF){
            if(verificar(l) == 0){
                mostrarLista(l);
                salvarArq(l, "validas.txt");
                i++;
            }
            break;
        }
        inserirfim(l,c);
    }
    fclose(f);
    return i;
}

//insere em relaçao a ordem de escolha para formula, subformula e conectivo no arquivo de cadastro
int inserir_subformula(int formula, int sub, char conectivo){
    FILE *f = fopen("validas.txt", "ab+");
    FILE *g = fopen("formulas.txt", "ab+");
    if(f == NULL) return 3;
    char s[100], form[100], subf[100];
    int i = 0;
    while(i < formula && i < sub){
        fscanf(f, "%s", s);
        i++;
        if(i == formula){
            strcpy(form, s);
            while(1){
                fscanf(f, "%s", s);
                i++;
                if(i == sub){
                    strcpy(subf, s);
                    fprintf(g, "(%s)%c(%s)\n", form, conectivo,subf);
                    break;
                }
            }
        }
        else if(i == sub){
            strcpy(subf, s);
            while(1){
                fscanf(f, "%s", s);
                i++;
                if(i == sub){
                    strcpy(subf, s);
                    fprintf(g, "(%s)%c(%s)\n", form, conectivo,subf);
                    break;
                }
            }
        }
    }
    fclose(f);
    remove("validas.txt");
    fclose(g);
    return 0;
}
