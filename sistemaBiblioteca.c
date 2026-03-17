// Prática: Criar um sistema de biblioteca simples usando estruturas em C
// Objeivos:
// Implementar o casdastro e a listagem de livros usando array estático.
// Foco em structs, entrada e saída de dados e organização básica do código.

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcspn()

// Definição de Constantes Globais
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100 // Definimos uma capacidade para empréstimos.
#define TAM_STRING 100

// Definição da Estrutura (Struct)
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 para disponível, 0 para emprestado.
};

// Nova struct para armazenar informações de empréstimos.
struct Emprestimo {
    int indiceLivro; // Índice do livro emprestado na biblioteca.
    char nomeUsuario[TAM_STRING]; // Nome do usuário que fez o empréstimo.
};

// Função pata limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função Principal (main)
int main() {
    struct Livro *biblioteca;
    struct Emprestimo *emprestimo;

    // Usamos calloc para o array de livros. calloc(num_elementos, tamanho_de_cada_elemento)
    // Vantagens: além de alocar a memória, também inicializa todos os bytes a zero, o que é útil para evitar lixo de memória. No entanto, pode ser um pouco mais lento do que malloc devido à inicialização.
    biblioteca = (struct Livro *)calloc(MAX_LIVROS, sizeof(struct Livro));

    // Usamos malloc para o array de empréstimos. malloc(tamanho_total_em_bytes)
    // Vantagens: é mais flexível, pois podemos alocar exatamente o que precisamos. No entanto, precisamos garantir que inicializamos os dados corretamente antes de usá-los.
    emprestimo = (struct Emprestimo *)malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    //VERIFICAÇÃO: É crucial verificar se a alocação de memória deu certo.
    if (biblioteca == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a biblioteca!\n");
        return 1; // Encerra o programa com código de erro.
    }
    int totalLivros = 0; // Contador para o número de livros cadastrados.
    int totalEmprestimos = 0; // Contador para o número de empréstimos realizados.
    int opcao; // Variável para armazenar a opção do menu escolhida pelo usuário.

    // Laço Principal do Menu
    do {
        printf("==================================\n");
        printf("    BIBLIOTECA - PARTE1\n");
        printf("==================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Realizar empréstimo\n");
        printf("4 - Listar empréstimos\n");
        printf("0 - Sair\n");
        printf("----------------------------------\n");
        printf("Escolha uma opção: ");

        // Lê a opção do usuário.
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf

        // Processamento da Opção
        switch (opcao) {
            case 1: // Cadastro de Livro
                printf("--- Cadastro de Novo Livro ---\n\n");

                if (totalLivros < MAX_LIVROS) {
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    printf("Digite o autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);
                    
                    printf("Digite a editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                    printf("Digite a edição: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf

                    totalLivros++;

                    printf("\nLivro cadastrado com sucesso!\n");
                } else {
                    printf("Biblioteca cheia! Não é possível cadastrar mais livros.\n");
                }

                printf("\nPressione Enter para continuar...");
                getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu.
                break;

            case 2: // Listagem de Livros
                printf("--- Lista de Livros Cadastrados ---\n\n");

                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado ainda.\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("----------------------------------\n");
                        printf("Livro %d:\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edição: %d\n", biblioteca[i].edicao);
                    }
                    printf("----------------------------------\n");
                }

                // A pausa é crucial para que o usuário veja a lista antes do proximo loop limpar a tela.
                printf("\nPressione Enter para continuar...");
                getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu.
                break;

            case 3: // Realizar empréstimo
                printf("--- Realizar Empréstimo ---\n\n");

                if (totalEmprestimos == MAX_EMPRESTIMOS) {
                    printf("Limite de empréstimos atingido!\n");
                } else {
                    printf("Livros disponiveis:\n");
                    int disponiveis = 0;
                    for (int i = 0; i < totalLivros; i++) {
                        if (biblioteca[i].disponivel) {
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }

                    if (disponiveis == 0) {
                        printf("Nenhum livro disponível para empréstimo!\n");
                    } else {
                        printf("\nDigite o número do livro que deseja emprestar: ");
                        int numLivro;
                        scanf("%d", &numLivro);
                        limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf

                        int indice = numLivro - 1; // Converte para o índice do array (0 a N-1).

                        // Valida escolha do usuário.
                        if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                            printf("Digite o nome do usuário que está pegando o livro: ");
                            fgets(emprestimo[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                            emprestimo[totalEmprestimos].nomeUsuario[strcspn(emprestimo[totalEmprestimos].nomeUsuario, "\n")] = '\0'; // Remove o '\n' do final.
                           
                            // Registra o empréstimo.
                            emprestimo[totalEmprestimos].indiceLivro = indice;

                            //Atualiza o status do livro para emprestado.
                            biblioteca[indice].disponivel = 0;

                            totalEmprestimos++;
                            printf("\nEmpréstimo realizado com sucesso!\n");
                        } else {
                            printf("\nOpção inválida ou livro indisponível! Por favor, tente novamente.\n");
                        }
                    }
                }
                printf("\nPressione Enter para continuar...");
                getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu.
                break;

            case 4: // Listar empréstimos
                printf("--- Lista de Empréstimos ---\n\n");

                if (totalEmprestimos == 0) {
                    printf("Nenhum empréstimo realizado ainda.\n");
                } else {
                    for (int i = 0; i < totalEmprestimos; i++) {
                        //Usa o índice do livro armazenado no empréstimo para acessar o nome do livro na biblioteca.
                        int indiceLivro = emprestimo[i].indiceLivro;
                        printf("----------------------------------\n");
                        printf("Empréstimo %d:\n", i + 1);
                        printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                        printf("Usuário: %s\n", emprestimo[i].nomeUsuario);
                    }
                    printf("----------------------------------\n");
                }

                printf("\nPressione Enter para continuar...");
                getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu.
                break;

            case 0: // Sair
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpção inválida! Por favor, escolha uma opção válida.\n");
                printf("\nPressione Enter para continuar...");
                getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu.
                break;
                }
        }
    while (opcao != 0);

    // Liberação de Memória: É importante liberar a memória alocada dinamicamente para evitar vazamentos de memória.
    free(biblioteca);
    free(emprestimo);

    printf("Memória liberada. Programa encerrado.\n");

    return 0; // Fim do programa
}