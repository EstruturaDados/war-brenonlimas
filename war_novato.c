 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>


 struct territorio{
    char nome[30];
    char cor[10];
    int tropas;
 };

int main() {

    struct territorio tabuleiro[5];
    int qtdtropas = 0;

    do {

        printf("--- Cadastrando território %d ---\n\n", qtdtropas + 1);

        printf("Nome do território: ");
        fgets(tabuleiro[qtdtropas].nome, 30, stdin);

        printf("Cor do exército: ");
        fgets(tabuleiro[qtdtropas].cor, 10, stdin);

        printf("Número de tropas: ");
        scanf("%d",&tabuleiro[qtdtropas].tropas);
       
        printf("\n");
        
        qtdtropas++;
        
        getchar();

    } while (qtdtropas < 5);

    printf("---Lista de territórios---\n\n");

    for (int i = 0; i < qtdtropas; i++) {
    printf("TERRITÓRIO %d\n", i + 1);
    printf("- Nome: %s", tabuleiro[i].nome);
    printf("- Cor: %s", tabuleiro[i].cor);
    printf("- Tropas: %d\n", tabuleiro[i].tropas);
    printf("-----------------------\n");

    }
    

    
    return 0;
}