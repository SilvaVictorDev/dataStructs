/*O que você vai fazer?

Primeiro, você receberá a missão de implementar a funcionalidade de ataque entre territórios. Com base nos territórios já cadastrados, o sistema deverá permitir que um jogador selecione um território como atacante, e outro como defensor. O ataque será resolvido por meio de uma simulação com dados aleatórios (como rolagem de dados), e o resultado alterará o controle e as tropas do território atacado. 

 

Lembre-se: essa etapa deve utilizar ponteiros para manipular os dados dos territórios e a alocação dinâmica de memória para armazenar os territórios cadastrados, fornecendo maior flexibilidade ao sistema.

Requisitos funcionais

Veja as funcionalidades essenciais para a implementação de uma simulação de batalha entre territórios.

 

    Alocação dinâmica de territórios: utilizar calloc ou malloc para alocar memória para um vetor de struct Territorio com tamanho informado pelo usuário.
     
    Simulação de ataques: criar uma função void atacar(Territorio* atacante, Territorio* defensor) que simula um ataque, utilizando números aleatórios como se fossem dados de batalha.
     
    Atualização de dados: o território defensor deve mudar de dono (cor do exército) se o atacante vencer, e suas tropas devem ser atualizadas.
     
    Exibição pós-ataque: o sistema deve exibir os dados atualizados dos territórios após cada ataque.

Requisitos não funcionais

A implementação deve seguir boas práticas de organização, uso eficiente da memória e interação clara com o usuário. Acompanhe!

 

    Modularização: o código deve estar organizado com funções distintas para cadastro, exibição, ataque e liberação de memória.
     
    Uso de ponteiros: todos os acessos e modificações aos dados dos territórios devem ser feitos por ponteiros.
     
    Gerenciamento de memória: toda memória alocada dinamicamente deve ser liberada ao final do programa utilizando free.
     
    Interface amigável: o terminal deve orientar o jogador sobre quais territórios podem ser usados para atacar e defender, com mensagens claras.

Instruções detalhadas

Para que o programa funcione da maneira esperada, alguns elementos e etapas de implementação devem ser seguidos conforme descrito a seguir.

 

    Bibliotecas necessárias: inclua stdio.h, stdlib.h, string.h e time.h.
     
    Struct atualizada: utilize a struct Territorio com os campos char nome[30], char cor[10], int tropas.
     
    Alocação de memória: peça ao usuário o número total de territórios e use calloc ou malloc para alocar esse vetor de forma dinâmica.
     
    Função de ataque: implemente void atacar(Territorio* atacante, Territorio* defensor) que utilize rand() para simular um dado de ataque (1 a 6) para cada lado.
     
    Atualização dos campos: transfira a cor e metade das tropas para o território defensor se o atacante vencer. Se perder, o atacante perde uma tropa.
     
    Liberação de memória: crie uma função void liberarMemoria(Territorio* mapa) para liberar o espaço alocado.

Requisitos técnicos adicionais

Alguns cuidados extras proporcionam o bom funcionamento e a legibilidade do programa. São eles:

 

    Utilizar srand(time(NULL)) para garantir aleatoriedade nos dados de ataque.
     
    Validar as escolhas de ataque para que o jogador não ataque um território da própria cor.
     
    Usar free corretamente ao final do programa.
     
    Comentar o código explicando cada função e trecho importante.

Comentários adicionais

O desafio do nível aventureiro representa um passo importante na evolução do sistema do War estruturado. A funcionalidade de ataque aproxima o sistema do comportamento real do jogo e reforça habilidades fundamentais para a construção de programas interativos e escaláveis em C.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct para representar um território
struct Territorio {
    char nome[30]; // Nome do território
    char cor[10];  // Cor do exército
    int tropas;    // Quantidade de tropas
};

// Função para simular um ataque entre dois territórios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1; // Simula um dado de 1 a 6 para o atacante
    int dadoDefensor = rand() % 6 + 1;  // Simula um dado de 1 a 6 para o defensor

    printf("Ataque de %s (Tropas: %d) contra %s (Tropas: %d)\n", atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
    printf("Dado do Atacante: %d\n", dadoAtacante);
    printf("Dado do Defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("%s venceu o ataque!\n", atacante->nome);
        defensor->tropas /= 2; // Defensor perde metade das tropas
        strcpy(defensor->cor, atacante->cor); // Defensor muda de cor
    } else {
        // Defensor vence ou empate
        printf("%s defendeu o ataque!\n", defensor->nome);
        atacante->tropas -= 1; // Atacante perde uma tropa
    }
}

// Função para liberar a memória alocada para os territórios
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

int main() {
    int numTerritorios;

    // Solicita ao usuário o número de territórios
    printf("Digite o número de territórios: ");
    scanf("%d", &numTerritorios);
    getchar(); // Limpa o buffer de entrada

    // Aloca memória para os territórios
    struct Territorio* mapa = (struct Territorio*)malloc(numTerritorios * sizeof(struct Territorio));
    if (mapa == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os territórios!\n");
        return 1; // Encerra o programa com código de erro
    }

    // Cadastro dos territórios
    for (int i = 0; i < numTerritorios; i++) {
        printf("Cadastro do Território %d:\n", i + 1);

        printf("Digite o nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // Remove o '\n' do final

        printf("Digite a cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0'; // Remove o '\n' do final

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // Limpa o buffer de entrada

        printf("\n"); // Linha em branco para melhor visualização
    }

    srand(time(NULL)); // Inicializa a semente para números aleatórios

    // Simulação de ataques (exemplo simples)
    if (numTerritorios >= 2) {
        atacar(&mapa[0], &mapa[1]); // Exemplo de ataque entre os dois primeiros territórios
    }

    // Exibição dos dados dos territórios após o ataque
    printf("\nDados dos Territórios Após o Ataque:\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Quantidade de Tropas: %d\n", mapa[i].tropas);
    }

    // Libera a memória alocada
    liberarMemoria(mapa);

    return 0;
}