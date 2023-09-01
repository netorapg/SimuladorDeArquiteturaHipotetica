//Simulador simples em C para uma arquitetura monociclo
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

int memory[MEM_SIZE];
int registers[REG_SIZE];
Instruction instr;

// Função para buscar a instrução n memória
void fetch(int PC) {
    instr = *(Instruction*)&memory[PC];
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
        case HALT:
            break;
        default:
            printf("Instrução inválida\n");
            break;
    }
}

int main() {
    // Inicializando a memória e os registradores
    for (int i = 0; i < MEM_SIZE; i++) memory[i] = 0;
    for (int i = 0; i < REG_SIZE; i++) registers[i] = 0;

    printf("RO: %d, R1: %d, R2: %d, R3: %d\n", registers[0], registers[1], registers[2], registers[3]);

    // Instrução 1: LOAD valor da memória[10 em R1
    instr.type = LOAD;
    instr.op1 = 10;
    instr.dest = 1;

    // Instrução 2: LOAD valor da memória[11] em R2
    instr.type = LOAD;
    instr.op1 = 11;
    instr.dest = 2;
    memory[4] = *(int*)&instr;// como cada instrução tem 16 bytes, a próxima instrução começará em memory[4]

    // Exemplo: instrução para adicionar conteúdo de R1 e R2 e armazenar em R3
    instr.type = ADD;
    instr.op1 = 1;
    instr.op2 = 2;
    instr.dest = 3;
    memory[8] = *(int*)&instr;


    // Loop de execução até encontrar instrução HALT
    int PC = 0;
    do {
        fetch(PC);
        execute();
        
        printf("RO: %d, R1: %d, R2: %d, R3: %d\n", registers[0], registers[1], registers[2], registers[3]);
        
        PC += sizeof(Instruction);
    }while (instr.type != HALT);

    
    return 0;

}

