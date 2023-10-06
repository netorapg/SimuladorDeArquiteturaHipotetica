#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "lib.h" // Biblioteca usada para extração de bits
#include "lib.c"

uint16_t memoria [64 * 1024]; // 64 KB de memória
uint16_t registradores [8]; // 8 registradores de propósito geral
uint16_t ligado = 1; // Variável que indica se o processador está ligado ou não
uint16_t pc = 1; // Program counter
uint16_t opcode; // Extrai o opcode da instrução
uint16_t destino; // Extrai o destino da instrução
uint16_t operador1; // Extrai o operador 1 da instrução
uint16_t operador2; // Extrai o operador 2 da instrução
uint16_t registrador; // Extrai o registrador da instrução
uint16_t imediato; // Extrai o imediato da instrução

// Instruções de 16 bits
uint16_t add(uint16_t a, uint16_t b) { // Instrução de adição
	return a+b;
}

uint16_t sub(uint16_t a, uint16_t b) { // Instrução de subtração
	return a-b;
}

uint16_t mul(uint16_t a, uint16_t b) { // Instrução de multiplicação
	return a*b;
}

uint16_t divi(uint16_t a, uint16_t b) { // Instrução de divisão
	return a/b;
}

uint16_t cmp_equal(uint16_t a, uint16_t b) { // Instrução de comparação igual
  	return (a == b);
}

uint16_t cmp_neq(uint16_t a, uint16_t b) { // Instrução de comparação diferente
    	return (a != b);
}

uint16_t load(uint16_t a) { // Instrução de load
    	return memoria[a];
}

void store(uint16_t a, uint16_t b) { // Instrução de store
	memoria[a] = b;
}

void mov(uint16_t a, uint16_t b) { // Instrução de mov
	registradores[a] = b;
	pc++;
}

void jump(uint16_t b) { // Instrução de jump
	pc = b;
}

void jump_cond(uint16_t a, uint16_t b) { // Instrução de jump condicional
	if (a == 1) {
		pc = b;
	} else {
		pc++;
	}
}

void syscall() { // Instrução de syscall
	if (registradores[0] == 0) {
		ligado = 0;
	} else {
		printf("\n");
		printf("Syscall não atendido\n");
		//exit(0);
	}
}

void printarRegistradores() { // Printa os registradores	
	for(int i = 0; i < 8; i++) {
		printf(" r%d: %d ", i, registradores[i]);
	}
	printf("\n");
	printf("\n");
	printf("PC: %d", pc);
}

void printarMemoria() { // Printa a memória
	for(int i = 0; i < 20; i++) {
		printf(" %d: %d ", i, memoria[i]);
	}
}

// Função que executa as instrucoes do tipo R
void executarInstrucaoR(uint16_t instrucao) {
opcode = extract_bits(instrucao, 9, 6); // Extrai o opcode da instrução
destino = extract_bits(instrucao, 6, 3); // Extrai o destino da instrução
operador1 = extract_bits(instrucao, 3, 3); // Extrai o operador 1 da instrução
operador2 = extract_bits(instrucao, 0, 3); // Extrai o operador 2 da instrução
	switch (opcode) { // Executa a instrução de acordo com o opcode
		case 0:
			registradores[destino] = add(registradores[operador1], registradores[operador2]);
			printf("add r%d, r%d, r%d \n", destino, operador1, operador2);
			break;
		case 1:
			registradores[destino] = sub(registradores[operador1], registradores[operador2]);
			printf("sub r%d, r%d, r%d \n", destino, operador1, operador2);
			break;
		case 2:
			registradores[destino] = mul(registradores[operador1], registradores[operador2]);
			printf("mul r%d, r%d, r%d \n", destino, operador1, operador2);
			break;
		case 3:
			registradores[destino] = divi(registradores[operador1], registradores[operador2]);
			printf("divi r%d, r%d, r%d \n", destino, operador1, operador2);
			break;
	    case 4:
	        registradores[destino] = cmp_equal(registradores[operador1], registradores[operador2]);
			printf("cmp_equal r%d, r%d, r%d \n", destino, operador1, operador2);
	    	break;
        case 5:
	    	registradores[destino] = cmp_neq(registradores[operador1], registradores[operador2]);
			printf("cmp_neq r%d, r%d, r%d \n", destino, operador1, operador2);
	       	break;
        case 15:
	       	registradores[destino] = load(registradores[operador1]);
			printf("load r%d, [r%d] \n", destino, operador1);
	       	break;
		case 16:
			store(registradores[operador1], registradores[operador2]);
			printf("store r%d, [r%d] \n", operador1, operador2);
			break;
		case 63:
			syscall();
			printf("syscall \n");
			break;
			default:
			printf("Erro R\n");
	}
}

// Função que executa as instrucoes do tipo I
void executarInstrucaoI(uint16_t instrucao) {
opcode = extract_bits(instrucao, 13, 2); // Extrai o opcode da instrução
registrador = extract_bits(instrucao, 10, 3); // Extrai o registrador da instrução
imediato = extract_bits(instrucao, 0, 10); // Extrai o imediato da instrução
	switch(opcode) {
		case 0:
			jump(imediato);
			printf("jump %d \n", imediato);
			break;
		case 1:
			jump_cond(registradores[registrador], imediato);
			printf("jump_cond r%d, %d \n", registrador, imediato);
			break;
		case 3:
			mov(registrador, imediato);
			printf("mov r%d, %d \n", registrador, imediato);
			break;
		default:
			printf("Erro I\n");
	}
}

int main (int argc, char **argv) {
	
	if (argc != 2) {
		printf("usage: %s [bin_name]\n", argv[0]);
		exit(1);
    	}

	load_binary_to_memory(argv[1], memoria, 64*1024);

	while (ligado != 0) {
		uint16_t instrucao = memoria[pc]; // Pega a instrução na memória
		uint16_t formato = extract_bits(instrucao, 15, 1); // Extrai o bit de formato da instrução	
		if(formato == 0) { // Se o formato for 0, a instrução é do tipo R
			executarInstrucaoR(instrucao);
            pc++;
		} else { // Se o formato for 1, a instrução é do tipo I
			executarInstrucaoI(instrucao);
			/*if(extract_bits(instrucao, 13, 2) == 3) {
				pc++;
			}*/
			
		}
		printarRegistradores();
		printf("\n");
        //getchar();
		printarMemoria();
	}
	return 0;
}
