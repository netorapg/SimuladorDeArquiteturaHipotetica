#include <stdio.h>

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
   // registers[8] = 0;

  printf("RO: %d, R1: %d, R2: %d, R3: %d, R4: %d, R5: %d, R6: %d, R7: %d, R8: %d, R9: %d, R10: %d, R11: %d\n", registers[0], registers[1], registers[2], registers[3], registers[4], registers[5], registers[6], registers[7], registers[8], registers[9], registers[10], registers[11]);
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

    memory[22].type = 18;
    memory[23].type = 9;

    instr.type = LOAD;
    instr.op1 = 22;
    instr.dest = 7;
    memory[6] = instr;

    instr.type = LOAD;
    instr.op1 = 23;
    instr.dest = 8;
    memory[7] = instr;

    instr.type = SUB;
    instr.op1 = 7;
    instr.op2 = 8;
    instr.dest = 9;
    memory[8] = instr;

    // Loop de execução até o final da memória
    int PC = 0;
    while (PC < MEM_SIZE) {
        fetch(PC);
        execute();
        
       // printf("RO: %d, R1: %d, R2: %d, R3: %d, R4: %d, R5: %d, R6: %d, R7: %d, R8: %d, R9: %d, R10: %d, R11: %d\n", registers[0], registers[1], registers[2], registers[3], registers[4], registers[5], registers[6], registers[7], registers[8], registers[9], registers[10], registers[11]);
    
        PC++;
    }

    printf("RO: %d, R1: %d, R2: %d, R3: %d, R4: %d, R5: %d, R6: %d, R7: %d, R8: %d, R9: %d, R10: %d, R11: %d\n", registers[0], registers[1], registers[2], registers[3], registers[4], registers[5], registers[6], registers[7], registers[8], registers[9], registers[10], registers[11]);


    printf("Resultado da soma: R6 = %d\n", registers[6]);
    printf("Resultado da subtração: R9 = %d\n", registers[9]);
    return 0;
}
