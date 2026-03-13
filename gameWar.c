#include <stdio.h>
#include <string.h>

// Definição da struct para representar um território
struct Territorio {
    char nome[30]; // Nome do território
    char cor[10];  // Cor do exército
    int tropas;    // Quantidade de tropas
};

int main() {
    struct Territorio territorios[5]; // Vetor para armazenar 5 territórios

    // Laço para cadastro dos territórios
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do Território %d:\n", i + 1);

        // Entrada do nome do território
        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Remove o '\n' do final

        // Entrada da cor do exército
        printf("Digite a cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; // Remove o '\n' do final

        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // Limpa o buffer de entrada

        printf("\n"); // Linha em branco para melhor visualização
    }

    // Exibição dos dados dos territórios cadastrados
    printf("Dados dos Territórios Cadastrados:\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("\n"); // Linha em branco para melhor visualização
    }

    return 0;
}