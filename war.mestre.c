// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>

 
// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct territorio{
    char nome[30];
    char cor[10];
    int tropas;
    int IDmissao;
    int IDexercito;
    int conquistados;
    int streak;
 };
// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:
struct territorio* alocarMapa(void);
int inicializarTerritorios(struct territorio *territorios);
void liberarMemoria(struct territorio *territorios);
void exibirMenuPrincipal(void);
void exibirMapa(const struct territorio *territorios, int totalTerritorios);
void exibirMissao(struct territorio *territorios);
void faseDeAtaque(struct territorio *territorios, int totalTerritorios, int escolha_ataque, int escolha_defesa);
void simularAtaque(struct territorio *atacante, struct territorio *defensor );
int sortearMissao(struct territorio *territorios);
int verificarVitoria(struct territorio *territorios, int totalTerritorios, struct territorio *territoriojogador);
void limparBufferEntrada(void);

const char* missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar todas as tropas da cor Vermelha",
        "Conquistar 2 territorios seguidos",
        "Ocupar 2 continentes",
        "Conquistar Asia e Europa"
        };

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
     // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.
    srand(time(0));
    int escolhaAtaque = 0;
    int escolhaDefesa = 0;
    int statusMission = 0;
    int indiceJogador = 0;
    int totalTerritorios = 5;
    int opcao = 0;

    struct territorio *territorios;
    territorios = alocarMapa();
    indiceJogador = inicializarTerritorios(territorios);
    sortearMissao(&territorios[indiceJogador]);
    exibirMissao(&territorios[indiceJogador]);
    
   
    do{
        exibirMapa(territorios, totalTerritorios);
        exibirMenuPrincipal();
        printf("\nEscolha uma opção: ");
        scanf(" %d", &opcao);

        switch(opcao)
        {
        case 1:
            faseDeAtaque(territorios, totalTerritorios, escolhaAtaque, escolhaDefesa);
            
            break;
        case 2:
            exibirMissao(&territorios[indiceJogador]);
            statusMission = verificarVitoria(territorios, totalTerritorios, &territorios[indiceJogador]);
        break;
        default:
            printf("\nOpção inválida! Tente novamente\n");;
            printf("Pressione Enter para continuar...");
            getchar();
        break;

        }
        
    } while (opcao != 0 && statusMission != 1);
    


    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.
    
    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
    liberarMemoria(territorios);
    return 0;
    
}




// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.
 struct territorio* alocarMapa(){

    return (struct territorio *) calloc(5, sizeof(struct territorio));

 };

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
int inicializarTerritorios(struct territorio *territorios){

    const char *Continentes[5] = {"Asia", "America", "Europa", "Africa", "Oceania"};    
    const char *Cores[5] = {"Vermelho", "Azul", "Verde", "Amarelo", "Branco"};
    
    for (int i = 0; i < 5; i++)
    {
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        strcpy(territorios[i].nome, Continentes[i]);
        strcpy(territorios[i].cor, Cores[i]);
         territorios[i].tropas = 5;
    }

    for (int i = 0; i < 5; i++) {
    
    printf("%d. %s                  (Exercito: %s, Tropas: %d)\n", i+1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    
    
    }
    

    int escolha;
    
    printf("\nEscolha seu exercito: ");
    fflush(stdout);
    scanf("%d", &escolha);
    limparBufferEntrada();
    
    int indice = escolha -1;

    territorios[indice].IDexercito = indice;

    return indice;

    };

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.
void liberarMemoria(struct territorio *territorios){
    free(territorios);
    printf("Memoria liberada com suceso. \n");

}
// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.
void exibirMenuPrincipal(){
    printf("\n---MENU DE AÇÕES---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
    printf("\n");


}
// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
void exibirMapa(const struct territorio *territorios, int totalTerritorios){
    printf("\nMAPA MUNDI - SITUAÇÃO ATUAL\n\n");
    for (int i = 0; i < totalTerritorios; i++) {
    printf("%d. %s                  (Exercito: %s, Tropas: %d)\n", i+1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
  
    
    }
}
// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.
void exibirMissao(struct territorio *territorios){
    printf("\nSUA MISSAO (Exercito %s)\n", territorios->cor);
    printf("%s\n", missoes[territorios->IDmissao]);
}
// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.
void faseDeAtaque(struct territorio *territorios, int totalTerritorios, int escolha_ataque, int escolha_defesa){
    

    printf("---FASE DE ATAQUE---\n\n");
    printf("Escolha o território atacante (de 1 a %d ou 0 para sair...)\n", totalTerritorios);
    scanf(" %d", &escolha_ataque);
    printf("Escolha o território defensor (de 1 a %d ou 0 para sair...)\n", totalTerritorios);
    scanf(" %d", &escolha_defesa);

      simularAtaque(&territorios[escolha_ataque - 1], &territorios[escolha_defesa - 1]);

}
// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.
void simularAtaque(struct territorio *atacante, struct territorio *defensor ){
    int ataque = 0;
    int defesa = 0;
 
    ataque = rand() % 6 + 1;
    defesa = rand() % 6 + 1;
    
    printf("O atacante %s rolou um dado e tirou: %d \n", atacante->nome, ataque );
    printf("O defensor %s rolou um dado e tirou: %d \n", defensor->nome, defesa );
    atacante->nome[strcspn(atacante->nome, "\n")] = '\0';
    defensor->nome[strcspn(defensor->nome, "\n")] = '\0';

    if (ataque > defesa){
        if (defensor->tropas <= 1 && defensor->conquistados <= 1)
        {

            strcpy(defensor->cor, atacante->cor);
            atacante->conquistados++;
            atacante->streak ++;
            defensor->streak = atacante->streak;
            defensor->conquistados = atacante->conquistados; 
            printf("Territorio conquistado pelo atacante\n");
            printf("\n");

        } else {
            defensor->tropas--;
            printf("VITORIA DO ATACANTE! O defensor perde 1 tropa.\n");
            printf("\n");

        }
        
    } else if (atacante->tropas <= 1 && atacante->conquistados <= 1){
        strcpy(atacante->cor, defensor->cor);
        defensor->conquistados++;
        defensor->streak++;
        atacante->streak = defensor->streak;
        atacante->conquistados = defensor->conquistados;
        printf("VITORIA DO DEFENSOR! Territorio conquistado pelo defensor.\n");

        } else {
            atacante->tropas--;
            printf("VITORIA DO DEFENSOR! O atacante perde 1 tropa. \n");
            printf("\n");
    }
}
// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.
int sortearMissao(struct territorio *territorios){

        int totalMissoes = sizeof(missoes)/sizeof (missoes[0]);
        int sorteio;

        do
        {
           sorteio = rand() % totalMissoes;

        } while ((sorteio == 0 && territorios->IDexercito == 0) || (sorteio == 4 && territorios->IDexercito == 0) || (sorteio == 4 && territorios->IDexercito == 2));
        
        territorios->IDmissao = sorteio;
        
        return sorteio;
}
// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.
int verificarVitoria(struct territorio *territorios, int totalTerritorios, struct territorio *territoriojogador){
    
    int achouVermelho = 0;
    int achouAzul = 0;
    int temAsia = 0;
    int temEuropa = 0;
    

    switch (territoriojogador->IDmissao)

    

        {

        case 0:

            if (territoriojogador->conquistados == 3)
            {
                return 1;

            } else {

                printf("Sua missão ainda não foi cumprida. Continue e lutar!\n");

                return 0;
            }
        break;
    
        case 1: 
        
            

            for (int i = 0; i < totalTerritorios; i++)
            {
                if (strcmp(territorios[i].cor, "Vermelho") == 0)
                {
                    achouVermelho++;

                } 
            
            }

            if (achouVermelho == 0)
            {
                return 1;

            } else {

                printf("Ainda ha exercito vermelho. Continue à lutar.\n");

                return 0; 
            }
         
        break;

        case 2:
    
            if (territoriojogador->streak >= 2)
            {
                return 1;

            } else {

                printf("Sua missão ainda não foi cumprida. Continue e lutar!\n");

                return 0;
            }
        
    
        break;

        case 3:

        

            for (int i = 0; i < totalTerritorios; i++){

                if (strcmp(territorios[i].cor, "Vermelho") == 0)
                {
                    achouAzul++;

                } 
            
            }

            if (achouAzul == 0)
            {
                return 1;

            } else {

                printf("Ainda ha exercito Vermelho. Continue à lutar.\n");

                return 0; 
            }
    
        break;

        


        case 4:
        
            

            for (int i = 0; i < totalTerritorios; i++) {
                if (strcmp(territorios[i].cor, territoriojogador->cor) == 0) {
                    if (strcmp(territorios[i].nome, "Asia") == 0) {
                        temAsia = 1;
                    }
                    if (strcmp(territorios[i].nome, "Europa") == 0) {
                        temEuropa = 1;
                    }
                }
            }

            if (temAsia && temEuropa){
                
                    return 1;

            } else { 

                    printf("Sua missão ainda não foi cumprida. Continue e lutar!\n");

                    return 0;

            }

        break;

        default:
        break;
    
    }

    return 0;

}
// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
}