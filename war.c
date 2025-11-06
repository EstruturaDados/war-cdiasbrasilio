//Nivel Novato
//Criar a base de territórios do jogo War
//Definir struct território
//Permiter que o usuário cadastre 5 territórios com nome, cor do exercito e 
//número de tropas
//Após cadastro, listar os territórios cadastrados, estado atual das tropas

#include <stdio.h>
#include <string.h>

//Definindo a struct para território
struct Territorio { 
    char nome[50];
    char corExercito[20];
    int numTropas;
};

//Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Declarar vetor de structs território, com capacidade para 5 territórios
#define MAX_TERRITORIOS 5
struct Territorio territorios[MAX_TERRITORIOS];
int totalTerritorios = 0;

//Função principal (Entrada de dados e listagem dos territórios)
int main() {
    printf("Cadastro de Territórios do Jogo War\n");
    printf("=====================================\n");

    //Loop para cadastro dos territórios
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Cadastro do Território %d\n", i + 1);
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0;  // Remover nova linha

        printf("Cor do Exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = 0;  // Remover nova linha

        printf("Número de Tropas: ");
        scanf("%d", &territorios[i].numTropas);
        limparBuffer();  // Limpar buffer após leitura de inteiro

        totalTerritorios++;
    }

    //Listar territórios cadastrados
    printf("\nTerritórios Cadastrados:\n");
    printf("=========================\n");
    for (int i = 0; i < totalTerritorios; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numTropas);
        printf("-------------------------\n");
    }

    return 0;
}
