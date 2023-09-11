#include <stdio.h>
#include <stdint.h>


#define MEM_SIZE 256
#define REG_SIZE 13

typedef enum {
    ADD = 0,
    SUB = 1,
    LOAD = 2,
    STORE = 3
} InstructionType;

typedef struct Instruction {
    InstructionType type;
    int op1;
    int op2;
    int dest;
} Instruction;

uint16_t memory[MEM_SIZE];
uint16_t registers[REG_SIZE];


uint16_t fetch(int PC, Instruction* instr) {
    if (PC < 0 || PC >= MEM_SIZE) {
        return 0;
    }
    *instr = *(Instruction*)&memory[PC];
    return 1;
}

// Funções para executar instruções
void executeAdd(Instruction instr) {
    registers[instr.dest] = registers[instr.op1] + registers[instr.op2];
}

void executeSub(Instruction instr) {
    registers[instr.dest] = registers[instr.op1] - registers[instr.op2];
}

void executeLoad (Instruction instr) {
    registers[instr.dest] = memory[registers[instr.op1]];
}

void executeStore(Instruction instr) {
    memory[registers[instr.op1]] = registers[instr.dest];
}

// Função para inicialização
void initialize() {
    for (int i = 0; i < MEM_SIZE; i++) {
        memory[i] = 0;
    }
    for (int i = 0; i < REG_SIZE; i++) {
        registers[i] = 0;
    }

    // Define valores nos registradores para demonstração
    registers[20] = 6;
    registers[21] = 7;

    memory[0] = ((LOAD << 12) | (20 << 8) | 4);
    memory[1] = ((LOAD << 12) | (21 << 8) | 5);
    memory[2] = ((ADD << 12) | 4 | (5 << 4) | 6);
    memory[3] = ((SUB << 12) | 7 | (8 << 4) | 9);
    
}

int main() {
    // Inicialize a memória e os registradores
    initialize();

    // Loop de execução até o final da memória
    int PC = 0;
    Instruction instr;
    while (fetch(PC, &instr)) {
        switch (instr.type) {
            case ADD:
                executeAdd(instr);
                break;
            case SUB:
                executeSub(instr);
                break;
            case LOAD:
                executeLoad(instr);
                break;
            case STORE:
                executeStore(instr);
                break;
            default:
                printf("Instrução não reconhecida\n");
                break;
        }

        printf("Registradores: ");
        for (int i = 0; i < REG_SIZE; i++) {
            printf("R%d: %d ", i, registers[i]);
        }
        printf("\n");

        PC++;
    }

    printf("Resultado da soma: R6 = %d\n", registers[6]);
    printf("Resultado da subtração: R9 = %d\n", registers[9]);
    return 0;
}
