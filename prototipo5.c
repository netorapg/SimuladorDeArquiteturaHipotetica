#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "lib.h" // Biblioteca usada para extração de bits

// IMPORTANTE: UTILIZAR APENAS g++ para compilar o código

//COISAS PARA FAZER
// 0 - Fazer as instruções de jump

//Perguntar ao professor


uint16_t memoria [64 * 1024]; // 64 KB de memória
uint16_t registradores [8]; // 8 registradores de propósito geral
uint16_t ligado = 1; // Variável que indica se o processador está ligado ou não
uint16_t pc = 0; // Program counter
// Instruções de 16 bits
uint16_t add(uint16_t a, uint16_t b){ // Instrução de adição
	return a+b;
}
uint16_t sub(uint16_t a, uint16_t b){ // Instrução de subtração
	return a-b;
}
uint16_t mul(uint16_t a, uint16_t b){ // Instrução de multiplicação
	return a*b;
}
uint16_t divi(uint16_t a, uint16_t b){ // Instrução de divisão
	return a/b;
}
uint16_t cmp_equal(uint16_t a, uint16_t b){ // Instrução de comparação igual
  	return (a == b);
}
uint16_t cmp_neq(uint16_t a, uint16_t b){ // Instrução de comparação diferente
	return (a != b);
}
uint16_t load(uint16_t a){ // Instrução de load
    return memoria[a];
}
void store(uint16_t a, uint16_t b){ // Instrução de store
	memoria[a] = b;
}
void mov(uint16_t a, uint16_t b){ // Instrução de mov
	registradores[a] = b;
}

void jump(uint16_t b){ // Instrução de jump
	pc = b;
}

void jump_cond(uint16_t a, uint16_t b){ // Instrução de jump condicional
	if (a == 1){
		pc = b;
	}
}

void syscall(){ // Instrução de syscall
	if (registradores[0] == 0){
		ligado = 0;
		//exit(0);
	}
}

void printarRegistradores(){ // Printa os registradores
	
	for(int i = 0; i < 8; i++){
		printf(" r%d: %d ", i, registradores[i]);
	}
	printf("\n");
	printf("\n");
	printf("PC: %d", pc);
}
void printarMemoria(){ // Printa a memória
	for(int i = 0; i < 20; i++){
		printf(" %d: %d ", i, memoria[i]);
	}
}
// Aqui adicionamos o número binário da instrução na memória
 // Exemplo de extração de bits
    // O primeiro bit é o bit que representa o formato
    // Os próximos 6 bits representam o opcode
    // Os próximos 3 bits representam o destino
    // Os próximos 3 bits representam o operador 1
    // Os próximos 3 bits representam o operador 2
	//0b0 000000 000 000 000; // Exemplo de um número binário de 16 bits
	//
void instrucoesNaMemoria(){
	memoria[0] = 0b0000000101101101; // Add r5, r5, r5
	memoria[1] = 0b0000001110101101;// Sub r6, r5, r5
	memoria[2] = 0b1000000000000100;//jump 4 
	memoria[3] = 0b0000011100101101;// Div r4, r5, r5
	memoria[4] = 0b1111010000000001; // mov r5, 1
	memoria[5] = 0b0001111111010000; // load [r7], r2
	memoria[6] = 0b0010000000111010; // store [r7], r2
	memoria[7] = 0b0000100011000101; //cmp_equal r3, r0, r5
	//memoria[8] = 0b1010000000001010; //jump_cond r0, 10
	memoria[8] = 0b1011100000001010; //jump_cond r6, 10
	memoria[9] = 0b0000101010101111; //cmp_neq r2, r5, r7 
	memoria[10] = 0b0000101010111001; //cmp_neq r2, r7, r1	
	memoria[11] = 0b0000010111101101;// Mul r7, r5, r5
	memoria[12] = 0b1110000000000000; // mov r0, 0 
	memoria[13] = 0b0111111000000000; //syscall
}
// Aqui inicializamos os registradores
void inicializandoRegistradores(){
	registradores[0] = 1; 
	registradores[1] = 2;
	registradores[2] = 3;
	registradores[3] = 4;
	registradores[4] = 5;
	registradores[5] = 6;
	registradores[6] = 7;
	registradores[7] = 8;
}
// Aqui executamos a instrução
void executarInstrucaoR(uint16_t instrucao) {
	uint16_t opcode = extract_bits(instrucao, 9, 6); // Extrai o opcode da instrução
	uint16_t destino = extract_bits(instrucao, 6, 3); // Extrai o destino da instrução
	uint16_t operador1 = extract_bits(instrucao, 3, 3); // Extrai o operador 1 da instrução
	uint16_t operador2 = extract_bits(instrucao, 0, 3); // Extrai o operador 2 da instrução
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

void executarInstrucaoI(uint16_t instrucao){
	uint16_t opcode = extract_bits(instrucao, 13, 2); // Extrai o opcode da instrução
	uint16_t registrador = extract_bits(instrucao, 10, 3); // Extrai o registrador da instrução
	uint16_t imediato = extract_bits(instrucao, 0, 10); // Extrai o imediato da instrução
	switch(opcode){
	
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


int main ()
{
	instrucoesNaMemoria();
	inicializandoRegistradores();
	
	
	//printarMemoria();
	//printf("\n");
	printf("PC: %d \n", pc);
	while (ligado != 0){
		uint16_t instrucao = memoria[pc]; // Pega a instrução na memória
		uint16_t formato = extract_bits(instrucao, 15, 1); // Extrai o bit de formato da instrução	
		if(formato == 0){ // Se o formato for 0, a instrução é do tipo R
			executarInstrucaoR(instrucao);

			if(extract_bits(instrucao, 9, 6) != 63){
				pc++;
			}
		}
		else { // Se o formato for 1, a instrução é do tipo I
			executarInstrucaoI(instrucao);
			if(extract_bits(instrucao, 13, 2) == 3){
				pc++;
			}
		}
		printarRegistradores();
		printf("\n");
		getchar();
		
		//printarMemoria();
	}
	return 0;
}
