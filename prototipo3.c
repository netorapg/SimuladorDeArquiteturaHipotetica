#include <stdio.h>
#include <stdint.h>

#define REG_SIZE 5
#define MEM_SIZE 256

uint16_t vetor[REG_SIZE];
uint16_t memory[MEM_SIZE];

// Definição das instruções
#define INC 0x1000
#define ADD 0x2000
#define SUB 0x3000
#define LOAD 0x4000
#define STORE 0x5000
#define HALT 0xFFFF

void fetch(int PC) {
    vetor[0] = memory[PC];
}

void execute() {
    uint16_t opcode = vetor[0] & 0xF000;
    uint16_t op1 = (vetor[0] >> 8) & 0xF;
    uint16_t op2 = (vetor[0] >> 4) & 0xF;
    uint16_t dest = vetor[0] & 0xF;

    switch (opcode) {
        case INC:
            vetor[dest]++;
            break;
        case ADD:
            vetor[dest] = vetor[op1] + vetor[op2];
            break;
        case SUB:
            vetor[dest] = vetor[op1] - vetor[op2];
            break;
        case LOAD:
            vetor[dest] = memory[op1];
            break;
        case STORE:
            memory[op1] = vetor[dest];
            break;
        case HALT:
            break;
        default:
            printf("Instrução inválida\n");
            break;
    }
}

int main() {
    for (int i = 0; i < REG_SIZE; i++) {
        vetor[i] = 0;
    }
    for (int i = 0; i < MEM_SIZE; i++) {
        memory[i] = HALT;
    }

    // Carregue suas instruções na memória aqui
    memory[0] = INC | (0 << 8) | (0 << 4) | 1;  // Incrementa o registro 0 e armazena em 1

    int PC = 0;
    do {
        fetch(PC);
        execute();

        PC++;
    } while (vetor[0] != HALT);

    printf("Estado final dos registros (vetor):\n");
    for (int i = 0; i < REG_SIZE; i++) {
        printf("R%d: %u\n", i, vetor[i]);
    }

    return 0;
}
