#include <stdio.h>

#define MEM_SIZE 256
#define REG_SIZE 8

typedef enum {
    ADD,
    SUB,
    LOAD,
    STORE,
    HALT
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

void fetch(int PC) {
    instr = memory[PC];
}

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
        case HALT:
            break;
        default:
            printf("Instrução inválida\n");
            break;
    }
}

int main() {
    // Inicializando a memória e os registradores
    for (int i = 0; i < MEM_SIZE; i++) {
        memory[i].type = HALT;
    }
    for (int i = 0; i < REG_SIZE; i++) {
        registers[i] = 0;
    }

    // Abre o arquivo binário para leitura
    FILE *file = fopen("instrucoes.bin", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lê as instruções do arquivo e as coloca na memória
    int instructionCount = 0;
    while (fread(&memory[instructionCount], sizeof(Instruction), 1, file) == 1) {
        instructionCount++;
    }

    fclose(file);

    int PC = 0;
    do{
        fetch(PC);
        execute();
        PC++;
    } while (instr.type != HALT);

    printf("Estado final dos registradores:\n");
    for (int i = 0; i < REG_SIZE; i++) {
        printf("R%d: %d\n", i, registers[i]);
    }

    return 0;
}