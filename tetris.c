#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
} 
typedef struct peca{
    int valordeordenacao;
    char tipo[10];
    char cor[50];
    char borda[50];
    float peso, tamanho;
    struct peca *prox;
    struct peca *ant;
}Peca;

int opcaoMenu = 4;
int tam;

Peca *inicio = NULL;
Peca *fim = NULL;

void add(){
    char bordaTemp[2];
    float tamanho,peso;
    char escolhaTipo;
    Peca * nova = (Peca*)malloc(sizeof(Peca));
    //menu de escolha da peça
    puts("Qual é o tipo da peça? \n");
    puts("[1] - Peça T");
    puts("[2] - Peça S1");
    puts("[3] - Peça S2");
    puts("[4] - Peça I");
    puts("[5] - Peça L1");
    puts("[6] - Peça L2");
    puts("[7] - Peça Q");
    printf("Resposta: ");
    scanf(" %c", &escolhaTipo);
    
    while(escolhaTipo < '1' || escolhaTipo > '7'){
        printf("\033[0;31m");
        puts("Opção inválida, digite um número de 1 a 7");
        printf("\033[0m");
        scanf(" %c", &escolhaTipo);
        limparBuffer();
    }
    escolhaTipo = escolhaTipo - '0';
    limparBuffer();

    switch(escolhaTipo){
        case 1:
            strcpy(nova->tipo, "T");
            nova->valordeordenacao = 1;
            break;
        case 2:
            strcpy(nova->tipo, "S1");
            nova->valordeordenacao = 2;
            break;
        case 3:
            strcpy(nova->tipo, "S2");
            nova->valordeordenacao = 3;
            break;
        case 4:
            strcpy(nova->tipo, "I");
            nova->valordeordenacao = 4;
            break;
        case 5: 
            strcpy(nova->tipo, "L1");
            nova->valordeordenacao = 5;
            break;
        case 6:
            strcpy(nova->tipo, "L2");
            nova->valordeordenacao = 6;
            break;
        case 7:
            strcpy(nova->tipo, "Q");
            nova->valordeordenacao = 7;
            break;
        default:
            break;
    }
    //COR

    char corpeca[50];
    printf("Digite a cor da peça: ");
    scanf("%[^\n]", corpeca); // Usa fgets para ler a string com espaços
    corpeca[0] = toupper(corpeca[0]); // Converte o primeiro caractere para maiúsculo
    strcpy(nova->cor, corpeca);
    // nova->cor[strcspn(nova->cor, "\n")] = '\0'; 

    //TAMANHO
    limparBuffer();
    while (1) {
        printf("Qual é o tamanho da peça? [Em px] ");
        if (scanf("%f", &tamanho) == 1 && tamanho > 0) {
            nova->tamanho = tamanho;
            limparBuffer();
            break;
        } else {
            printf("\033[0;31m");
            printf("Valor inválido, digite novamente.\n");
            printf("\033[0m");
            limparBuffer();
        }
    }
        
    //BORDA
    printf("A peça possui borda? [s/n] ");
    scanf(" %c", bordaTemp);
    limparBuffer();
    tolower(bordaTemp[0]);
    while(bordaTemp[0] != 's' && bordaTemp[0] != 'n'){
        printf("\033[0;31m");
        printf("Valor inválido, digite novamente [s/n]: ");
        printf("\033[0m");
        scanf(" %c", bordaTemp);
        limparBuffer();
    }   
    if(strcmp(bordaTemp, "s") == 0){
        strcpy(nova->borda, "Com Borda");
    }
    else if(strcmp(bordaTemp, "n") == 0){
        strcpy(nova->borda, "Sem Borda");
    }
    // adicionados sempre no final
    if(inicio == NULL){
        inicio = nova;
        fim = nova;
    }
    else{
        fim->prox = nova;
        nova->ant = fim;
        fim = nova;
        
    }
    tam++;
}

int menu(){
    printf("\033[0;36m");
    printf("Menu: \n");
    printf("[1] - Adicionar peça \n");
    printf("[2] - Listar peças \n");
    printf("[3] - Reorganizar peças \n");
    printf("[0] - Sair\n");
    printf("\033[0m");
    printf("Opção: ");
    
    scanf("%d", &opcaoMenu);
    return opcaoMenu;
}

void imprimir(){
    Peca *aux = inicio;
        if(aux == NULL){
            printf("\033[0;31m");
            puts("Nenhuma peça cadastrada");
            printf("\033[0m");
            return;
        }
        else{
        printf("\033[0;32m");
        printf("Você tem essas peças cadastradas: \n");
        printf("\033[0m");
        
        for (int i = 0; i < tam; i++) {
            printf("%d | Tipo -  %-16s | Cor - %-16s | Borda - %-16s |\n",i+1 ,aux->tipo, aux->cor, aux->borda);
            aux = aux->prox;
        }
        
        printf("+------------------+------------------+------------------+------------------+---\n");
        
        }
    }

void reorganizar() {
    Peca *aux = inicio;

    // Percorre a lista
    while (aux != NULL) {
        Peca *menor = aux; // Assume que o nó atual é o menor pois é o único encontrado até agora
        Peca *prox = aux->prox;

        // Encontra o nó com o menor valor de ordenação no restante
        while (prox != NULL) {
            if (prox->valordeordenacao < menor->valordeordenacao) {
                menor = prox;
            }
            prox = prox->prox;
        }

        // Troca todos os campos entre o nó atual e o menor encontrado
        if (menor != aux) {
            // Troca valordeordenacao
            int temp_valor = aux->valordeordenacao;
            aux->valordeordenacao = menor->valordeordenacao;
            menor->valordeordenacao = temp_valor;

            // Troca tipo
            char temp_tipo[10];
            strcpy(temp_tipo, aux->tipo);
            strcpy(aux->tipo, menor->tipo);
            strcpy(menor->tipo, temp_tipo);

            // Troca cor
            char temp_cor[50];
            strcpy(temp_cor, aux->cor);
            strcpy(aux->cor, menor->cor);
            strcpy(menor->cor, temp_cor);

            // Troca borda
            char temp_borda[50];
            strcpy(temp_borda, aux->borda);
            strcpy(aux->borda, menor->borda);
            strcpy (menor->borda, temp_borda);

            // Troca peso
            float temp_peso = aux->peso;
            aux->peso = menor->peso;
            menor->peso = temp_peso;

            // Troca tamanho
            float temp_tamanho = aux->tamanho;
            aux->tamanho = menor->tamanho;
            menor->tamanho = temp_tamanho;
        }

        // Avança para o próximo nó
        aux = aux->prox;
    }
}

int main(){
    while(opcaoMenu != 0){
        menu();
        if(opcaoMenu == 1){
            add();
        }
        else if(opcaoMenu == 2){
            imprimir();
        }
        else if(opcaoMenu == 3){
            reorganizar();
        }
    }
    Peca *aux = inicio;
    while (aux != NULL) {
        Peca *temp = aux;
        aux = aux->prox;
        free(temp);
    }

    return 0;
}
