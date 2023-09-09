#include <stdio.h>
#include <stdint.h>

#define MEM_SIZE 256
#define REG_SIZE 13

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

uint16_t memory[MEM_SIZE];
int registers[REG_SIZE];
Instruction instr;

// Função para buscar a instrução na memória
int fetch(int PC) {
    if (PC < 0 || PC >= MEM_SIZE) {
        return 0; // Verifica se PC está dentro dos limites da memória
    }
    instr = *(Instruction*)&memory[PC];
    return 1;
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
            registers[instr.dest] = memory[instr.op1];
            break;
        case STORE:
            memory[instr.op1] = registers[instr.dest];
            break;
        default:
            printf("Instrução inválida\n");
            break;
    }
}

int main() {
    // Inicializando a memória e os registradores
    for (int i = 0; i < MEM_SIZE; i++) {
        memory[i] = 0;
    }
    for (int i = 0; i < REG_SIZE; i++) {
        registers[i] = 0;
    }

    printf("RO: %d, R1: %d, R2: %d, R3: %d, R4: %d, R5: %d, R6: %d, R7: %d, R8: %d, R9: %d, R10: %d, R11: %d\n", registers[0], registers[1], registers[2], registers[3], registers[4], registers[5], registers[6], registers[7], registers[8], registers[9], registers[10], registers[11]);

    // Define valores em posições específicas da memória para demonstração
    memory[20] = 6;
    memory[21] = 7;

    Instruction temp;

    temp.type = LOAD;
    temp.op1 = 20;
    temp.dest = 4;
    memory[3] = *(uint16_t*)&temp;

    temp.type = LOAD;
    temp.op1 = 21;
    temp.dest = 5;
    memory[4] = *(uint16_t*)&temp;

    temp.type = ADD;
    temp.op1 = 4;
    temp.op2 = 5;
    temp.dest = 6;
    memory[5] = *(uint16_t*)&temp;

    memory[22] = 18;
    memory[23] = 9;

    temp.type = LOAD;
    temp.op1 = 22;
    temp.dest = 7;
    memory[6] = *(uint16_t*)&temp;

    temp.type = LOAD;
    temp.op1 = 23;
    temp.dest = 8;
    memory[7] = *(uint16_t*)&temp;

    temp.type = SUB;
    temp.op1 = 7;
    temp.op2 = 8;
    temp.dest = 9;
    memory[8] = *(uint16_t*)&temp;

    // Loop de execução até o final da memória
    int PC = 0;
    while (fetch(PC)) {
        execute();
        
        printf("RO: %d, R1: %d, R2: %d, R3: %d, R4: %d, R5: %d, R6: %d, R7: %d, R8: %d, R9: %d, R10: %d, R11: %d\n", registers[0], registers[1], registers[2], registers[3], registers[4], registers[5], registers[6], registers[7], registers[8], registers[9], registers[10], registers[11]);
        
        PC++;
    }

    printf("Resultado da soma: R6 = %d\n", registers[6]);
    printf("Resultado da subtração: R9 = %d\n", registers[9]);
    return 0;
}
