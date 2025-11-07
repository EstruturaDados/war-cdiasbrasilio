/*
Nível Novato:
Criar a base de territórios do jogo War
Definir struct território
Permitir que o usuário cadastre 5 territórios com nome, cor do exercito e
número de tropas
Após cadastro, listar os territórios cadastrados, estado atual das tropas
*/

/*
Nível Aventureiro:
Implementar a funcionalidade de ataque
Usar ponteiros, alocação dinâmica de memória e
Memória: Territórios dinâmicos, enquanto o programa roda
Ponteiro: Variável para acessar o local separado para territórios
Limpar a memória ao final do programa (evitar vazamentos de memória)
Modularização: Organizar em funções para mostrar mapa e realizar ataques, simular lançamento de dados e comparar

Passo a passo:
Cadastrar territórios (nome, cor do exército, número de tropas)
Entre em loop de turnos
Entra em fase de ataque, quem ataque e quem defende
Mostrar valor de dados e resultado
Atualizar proprietário do território e número de tropas
Mostrar mapa atualizado
Finalizar o jogo quando um jogador conquistar todos os territórios ou decidir sair
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definindo a struct para território
struct Territorio
{
    char nome[50];
    char corExercito[20];
    int numTropas;
};

// Função para limpar o buffer de entrada
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Alocação de memória dinâmica para territórios
// Pergunta ao usuário o total de territórios a serem cadastrados
// Uso da função malloc para alocar memória
struct Territorio *territorios = NULL;
int totalTerritorios = 0;

// Função para remover território quando conquistado
void removerTerritorio(struct Territorio** territorios, int* total, int indiceRemover) {
    for (int i = indiceRemover; i < (*total) - 1; i++) {
        (*territorios)[i] = (*territorios)[i + 1];
    }
    (*total)--;

    struct Territorio* temp = realloc(*territorios, (*total) * sizeof(struct Territorio));
    if (temp != NULL || (*total) == 0) {
        *territorios = temp;
    } else {
        printf("Erro ao realocar memória após remoção.\n");
    }
}


// Função para verificar vitória
int verificarVitoria(struct Territorio *territorios, int total)
{
    if (total == 0)
        return 0;

    char corVencedora[20];
    strcpy(corVencedora, territorios[0].corExercito);

    for (int i = 1; i < total; i++)
    {
        if (strcmp(territorios[i].corExercito, corVencedora) != 0)
        {
            return 0; // Ainda há territórios com cores diferentes
        }
    }

    printf("\nTodos os territórios pertencem ao exército %s. Vitória!\n", corVencedora);
    return 1;
}

// Função para mostrar estatisticas finais
void mostrarEstatisticasFinais(struct Territorio *territorios, int total)
{
    printf("\nResumo por Exército:\n");
    for (int i = 0; i < total; i++)
    {
        int jaContado = 0;
        for (int k = 0; k < i; k++)
        {
            if (strcmp(territorios[i].corExercito, territorios[k].corExercito) == 0)
            {
                jaContado = 1;
                break;
            }
        }
        if (!jaContado)
        {
            int soma = 0;
            for (int j = 0; j < total; j++)
            {
                if (strcmp(territorios[i].corExercito, territorios[j].corExercito) == 0)
                {
                    soma += territorios[j].numTropas;
                }
            }
            printf("Exército %s: %d tropas\n", territorios[i].corExercito, soma);
        }
    }
}

// Função principal (Entrada de dados e listagem dos territórios)
int main()
{
    printf("Cadastro de Territórios do Jogo War\n");
    printf("=====================================\n");

    // Perguntar ao usuário o total de territórios a serem cadastrados
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &totalTerritorios);
    limparBuffer(); // Limpar buffer após leitura de inteiro

    // Uso da função malloc para alocar memória
    territorios = (struct Territorio *)malloc(totalTerritorios * sizeof(struct Territorio));
    if (territorios == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Loop para cadastro dos territórios
    for (int i = 0; i < totalTerritorios; i++)
    {
        printf("Cadastro do Território %d\n", i + 1);
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0; // Remover nova linha

        printf("Cor do Exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = 0; // Remover nova linha

        printf("Número de Tropas: ");
        scanf("%d", &territorios[i].numTropas);
        limparBuffer(); // Limpar buffer após leitura de inteiro
    }

    // Listar territórios cadastrados
    printf("\nTerritórios Cadastrados:\n");
    printf("=========================\n");
    for (int i = 0; i < totalTerritorios; i++)
    {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numTropas);
        printf("-------------------------\n");
    }

    // Loop de ataques
    char continuar;
    do
    {
        // Lógica do ataque aqui
        printf("Qual território irá atacar? ");
        int territorioAtacante, territorioDefensor;
        scanf("%d", &territorioAtacante);
        printf("Qual território irá defender? ");
        scanf("%d", &territorioDefensor);

        // Verificar se os territórios são válidos
        if (territorioAtacante < 1 || territorioAtacante > totalTerritorios ||
            territorioDefensor < 1 || territorioDefensor > totalTerritorios)
        {
            printf("Territórios inválidos. Tente novamente.\n");
            continue;
        }

        // Ajustar índices para arrays
        territorioAtacante--;
        territorioDefensor--;

        // Simular lançamento de dados e comparar resultados
        srand(time(NULL));
        int dadoAtacante = (rand() % 6) + 1;
        int dadoDefensor = (rand() % 6) + 1;
        printf("Dado do Atacante (%s): %d\n", territorios[territorioAtacante].nome, dadoAtacante);
        printf("Dado do Defensor (%s): %d\n", territorios[territorioDefensor].nome, dadoDefensor);
        if (dadoAtacante > dadoDefensor)
        {
            printf("O atacante venceu!\n");
            territorios[territorioDefensor].numTropas--;

            if (territorios[territorioDefensor].numTropas <= 0)
            {
                printf("Território %s foi conquistado por %s!\n", territorios[territorioDefensor].nome, territorios[territorioAtacante].corExercito);

                // Remover o território conquistado
                removerTerritorio(&territorios, &totalTerritorios, territorioDefensor);

                // Ajustar índice do atacante se necessário
                if (territorioDefensor < territorioAtacante)
                {
                    territorioAtacante--;
                }

                // Verificar se o jogo acabou
                if (totalTerritorios == 0)
                {
                    printf("Todos os territórios foram eliminados. Fim de jogo.\n");
                    break;
                }
            }
        }
        else
        {
            printf("O defensor venceu!\n");
            territorios[territorioAtacante].numTropas--;

            if (territorios[territorioAtacante].numTropas <= 0)
            {
                printf("Território %s foi conquistado por %s!\n", territorios[territorioAtacante].nome, territorios[territorioDefensor].corExercito);

                // Remover o território conquistado
                removerTerritorio(&territorios, &totalTerritorios, territorioAtacante);

                // Ajustar índice do defensor se necessário
                if (territorioAtacante < territorioDefensor)
                {
                    territorioDefensor--;
                }

                if (totalTerritorios == 0)
                {
                    printf("Todos os territórios foram eliminados. Fim de jogo.\n");
                    break;
                }
            }
        }

        // Mostrar mapa atualizado
        printf("\nMapa Atualizado dos Territórios:\n");
        printf("=================================\n");
        for (int i = 0; i < totalTerritorios; i++)
        {
            printf("Território %d:\n", i + 1);
            printf("Nome: %s\n", territorios[i].nome);
            printf("Cor do Exército: %s\n", territorios[i].corExercito);
            printf("Número de Tropas: %d\n", territorios[i].numTropas);
            printf("-------------------------\n");
        }

        // Verificar condição de vitória
        if (verificarVitoria(territorios, totalTerritorios))
        {
            break; // Sai do loop principal se houver um vencedor
        }

        // Questionar se o usuário deseja continuar atacando ou sair
        do
        {
            printf("Deseja continuar atacando? (s/n): ");
            scanf(" %c", &continuar);
            limparBuffer(); // Limpar buffer após leitura de caractere

            if (continuar == 'n' || continuar == 'N')
            {
                break; // Sai do loop principal
            }
            else if (continuar == 's' || continuar == 'S')
            {
                break; // Continua o loop principal
            }
            else
            {
                printf("Entrada inválida. Digite apenas 's' para continuar ou 'n' para sair.\n");
            }
        } while (1); // Loop infinito até entrada válida
    } while (continuar == 's' || continuar == 'S');

    // Mostrar estatísticas finais
    mostrarEstatisticasFinais(territorios, totalTerritorios);

    // Caso usuário decida sair, liberar a memória alocada
    free(territorios);
    printf("Memória liberada. Saindo do programa.\n");

    return 0;
}

