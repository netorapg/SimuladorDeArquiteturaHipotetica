#include <stdio.h>

#define MEM_SIZE 256
#define REG_SIZE 8

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

Instruction memory[MEM_SIZE];
int registers[REG_SIZE];
Instruction instr;

// Função para buscar a instrução na memória
void fetch(int PC) {
    instr = memory[PC];
}

// Função para decodificar e executar a instrução
void execute() {
    switch (instr.type) {
        case ADD:
            registers[instr.dest] = registers[instr.op1] + registers[instr.op2];
            break;
        case SUB:
            registers[instr.dest] = registers[instr.op1] - registers[instr.op2];
            break;
        case LOAD:
            registers[instr.dest] = memory[instr.op1].type;
            break;
        case STORE:
            memory[instr.op1].type = registers[instr.dest];
            break;
        default:
            printf("Instrução inválida\n");
            break;
    }
}

int main() {
    // Inicializando a memória e os registradores
    for (int i = 0; i < MEM_SIZE; i++) {
        memory[i].type = -1;  // Usando -1 para representar instruções inválidas
    }
    for (int i = 0; i < REG_SIZE; i++) {
        registers[i] = 0;
    }

    // Abrir o arquivo binário de instruções para leitura
    FILE *file = fopen("instrucoes.bin", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de instruções");
        return 1;
    }

    // Lê as instruções do arquivo binário e carrega na memória
    int instructionCount = 0;
    while (fread(&memory[instructionCount], sizeof(Instruction), 1, file) == 1) {
        instructionCount++;
    }

    // Fecha o arquivo após a leitura
    fclose(file);

    // Loop de execução até o final do arquivo
    int PC = 0;
    while (memory[PC].type != -1) {
        fetch(PC);
        execute();

        PC++;
    }

    // Imprime o estado final dos registradores
    printf("Estado final dos registradores:\n");
    for (int i = 0; i < REG_SIZE; i++) {
        printf("R%d: %d\n", i, registers[i]);
    }

    return 0;
}
