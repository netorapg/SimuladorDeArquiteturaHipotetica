#include <stdio.h>

#define MEM_SIZE 256

typedef enum {
    ADD,
    SUB,
    LOAD,
    STORE
} InstructionType;

typedef struct {
    InstructionType type;
    int op1;
    int op2;
    int dest;
} Instruction;

int main() {
    // Abrir o arquivo binário para escrita
    FILE *file = fopen("instrucoes.bin", "wb");
    if (file == NULL) {
        perror("Erro ao criar o arquivo de instruções");
        return 1;
    }

    // Definir as instruções e escrevê-las no arquivo binário
    Instruction instructions[] = {
        {LOAD, 10, 0, 1},
        {LOAD, 11, 0, 2},
        {ADD, 1, 2, 3},
        // Adicione mais instruções aqui, se necessário
    };

    // Escrever as instruções no arquivo
    fwrite(instructions, sizeof(Instruction), sizeof(instructions) / sizeof(Instruction), file);

    // Fechar o arquivo
    fclose(file);

    printf("Arquivo de instruções 'instrucoes.bin' criado com sucesso.\n");

    return 0;
}
