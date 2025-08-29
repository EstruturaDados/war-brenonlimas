 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>

 struct territorio{
    char nome[30];
    char cor[10];
    int tropas;
 };

 struct territorio* TAM_tabuleiro(int qtd){
    struct territorio *t;
    t = (struct territorio *) calloc(qtd, sizeof(struct territorio));
    return t;
 };

 void ataque (struct territorio *atacante, struct territorio *defensor ){
    int ataque = 0;
    int defesa = 0;
 
    ataque = rand() % 6 + 1;
    defesa = rand() % 6 + 1;
    
    printf("O atacante %s rolou um dado e tirou: %d \n", atacante->nome, ataque );
    printf("O defensor %s rolou um dado e tirou: %d \n", defensor->nome, defesa );
    atacante->nome[strcspn(atacante->nome, "\n")] = '\0';
    defensor->nome[strcspn(defensor->nome, "\n")] = '\0';

    if (ataque > defesa){
        if (defensor->tropas == 1)
        {
            strcpy(defensor->cor, atacante->cor); 
            printf("Territorio conquistado pelo atacante\n");
            printf("\n");

        } else {
            defensor->tropas--;
            printf("VITORIA DO ATACANTE! O defensor perde 1 tropa.\n");
            printf("\n");

        }
        
    } else {
        atacante->tropas--;
        printf("VITORIA DO DEFENSOR! O defensor perde 1 tropa. \n");
        printf("\n");
    }
    

 };

int main() {

    srand(time(0));

    struct territorio *tabuleiro;
    int qtdterritorios = 0, reserva_territorios = 0, escolha_ataque = 0, escolha_defesa = 0;

    printf("Defina a quantidade de territórios: \n");
    scanf("%d", &reserva_territorios);
    getchar();

    tabuleiro = TAM_tabuleiro(reserva_territorios);

    do {

        printf("--- Cadastrando território %d ---\n\n", qtdterritorios + 1);

        printf("Nome do território: ");
        fgets(tabuleiro[qtdterritorios].nome, 30, stdin);
        
        printf("Cor do exército: ");
        fgets(tabuleiro[qtdterritorios].cor, 10, stdin);

        printf("Número de tropas: ");
        scanf(" %d",&tabuleiro[qtdterritorios].tropas);
        getchar();
        printf("\n");
        
        tabuleiro[qtdterritorios].nome[strcspn(tabuleiro[qtdterritorios].nome, "\n")] = '\0';
        tabuleiro[qtdterritorios].cor[strcspn(tabuleiro[qtdterritorios].cor, "\n")] = '\0';

        qtdterritorios++;
        
        

    } while (qtdterritorios < reserva_territorios);

    do
    {
     
    printf("--- Mapa do Mundo - Estado Atual ---\n\n");

    for (int i = 0; i < qtdterritorios; i++) {
    
    printf("%d. %s (Exercito: %s, Tropas: %d)\n", i+1, tabuleiro[i].nome, tabuleiro[i].cor, tabuleiro[i].tropas);
    printf("\n");
    
    }
    
    printf("---FASE DE ATAQUE---\n\n");
    printf("Escolha o território atacante (de 1 a %d ou 0 para sair...)\n", qtdterritorios);
    scanf(" %d", &escolha_ataque);

    printf("Escolha o territorio defensor (de 1 a %d ou 0 para sair...)\n", qtdterritorios);
    scanf(" %d",&escolha_defesa);
    printf("\n");

    ataque(&tabuleiro[escolha_ataque - 1], &tabuleiro[escolha_defesa -1]);

    
    printf("Pression enter para iniciar uma nova rodada. \n");
    getchar();
    getchar();
    

    } while (escolha_ataque != 0 || escolha_defesa != 0);

    free(tabuleiro);
    
    return 0;
}