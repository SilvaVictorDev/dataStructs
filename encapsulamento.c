// Exemplo de encapsulamento em C usando typedef

#include <stdio.h>

/* Exemplo de definição de estrutura para Aluno
struct Aluno {
    char nome{50};
    int idade;
    float media;
}; */

// Usdando typedef para criar o tipo Aluno
typedef struct {
    char nome[50];
    int idade;
    float media;
} Aluno;

int main() {
    // Criando e inicializando uma variácel do tipo Aluno
    Aluno aluno1 = {"João", 20, 8.5};

    // Acessando os dados com o operador '.'
    printf("Aluno: %s\n", aluno1.nome);
    printf("Idade: %d\n", aluno1.idade);
    printf("Média: %.2f\n", aluno1.media);

    return 0;
}