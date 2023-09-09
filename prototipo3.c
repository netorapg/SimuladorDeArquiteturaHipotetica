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
        memory[i].type = LOAD;  // Inicializa com a instrução LOAD em vez de HALT
    }
    for (int i = 0; i < REG_SIZE; i++) {
        registers[i] = 0;
    }

    printf("RO: %d, R1: %d, R2: %d, R3: %d, R4: %d, R5: %d, R6: %d, R7: %d, R8: %d\n", registers[0], registers[1], registers[2], registers[3], registers[4], registers[5], registers[6], registers[7]);

/*  // Instrução 1: LOAD valor da memória[10 em R1
    instr.type = LOAD;
    instr.op1 = 10;
    instr.dest = 1;
    memory[0] = instr;

    // Instrução 2: LOAD valor da memória[11] em R2
    instr.type = LOAD;
    instr.op1 = 11;
    instr.dest = 2;
    memory[1] = instr;

    // Exemplo: instrução para adicionar conteúdo de R1 e R2 e armazenar em R3
    instr.type = ADD;
    instr.op1 = 1;
    instr.op2 = 2;
    instr.dest = 3;
    memory[2] = instr;
*/
  
    memory[20].type = 6;
    memory[21].type = 7;

    instr.type = LOAD;
    instr.op1 = 20;
    instr.dest = 4;
    memory[3] = instr;

    instr.type = LOAD;
    instr.op1 = 21;
    instr.dest = 5;
    memory[4] = instr;

    instr.type = ADD;
    instr.op1 = 4;
    instr.op2 = 5;
    instr.dest = 6;
    memory[5] = instr;

    // Loop de execução até o final da memória
    int PC = 0;
    while (PC < MEM_SIZE) {
        fetch(PC);
        execute();
        
      // printf("RO: %d, R1: %d, R2: %d, R3: %d, R4: %d, R5: %d, R6: %d, R7: %d, R8: %d\n", registers[0], registers[1], registers[2], registers[3], registers[4], registers[5], registers[6], registers[7]);
        
        PC++;
    }

    printf("RO: %d, R1: %d, R2: %d, R3: %d, R4: %d, R5: %d, R6: %d, R7: %d, R8: %d\n", registers[0], registers[1], registers[2], registers[3], registers[4], registers[5], registers[6], registers[7]);


    printf("Resultado da soma: R6 = %d\n", registers[6]);
    return 0;
}
