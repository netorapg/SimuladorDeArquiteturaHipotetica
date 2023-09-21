#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "lib.h" // Biblioteca usada para extração de bits

uint16_t memoria [64 * 1024]; // 64 KB de memória
uint16_t registradores [8]; // 8 registradores de propósito geral


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

void printarRegistradores(){ // Printa os registradores
	for(int i = 0; i < 8; i++){
		printf(" r%d: %d", i, registradores[i]);
	}
}


int main ()
{
    // Exemplo de extração de bits
    // O primeiro bit é o bit representa o formato
    // Os próximos 6 bits representam o opcode
    // Os próximos 3 bits representam o destino
    // Os próximos 3 bits representam o operador 1
    // Os próximos 3 bits representam o operador 2
	//0b0 000000 000 000 000; // Exemplo de um número binário de 16 bits
	memoria[0]= 0b0000011101110010; // Aqui aidicionamos o número binário da instrução na memória
    // Inicializando os registradores
	registradores[0] = 0; 
	registradores[1] = 1;
	registradores[2] = 2;
	registradores[3] = 3;
	registradores[4] = 4;
	registradores[5] = 5;
	registradores[6] = 6;
	registradores[7] = 7;


	uint16_t formato = extract_bits(memoria[0], 15, 1); // Extrai o bit de formato da instrução

	uint16_t opcode = extract_bits(memoria[0], 9, 6); // Extrai o opcode da instrução
	
	uint16_t destino = extract_bits(memoria[0], 6, 3); // Extrai o destino da instrução

	uint16_t operador1 = extract_bits(memoria[0], 3, 3); // Extrai o operador 1 da instrução

	uint16_t operador2 = extract_bits(memoria[0], 0, 3); // Extrai o operador 2 da instrução



	switch (opcode) { // Executa a instrução de acordo com o opcode
		case 0:
		registradores[destino] = add(registradores[operador1], registradores[operador2]);
		break;
		case 1:
		registradores[destino] = sub(registradores[operador1], registradores[operador2]);
		break;
		case 2:
		registradores[destino] = mul(registradores[operador1], registradores[operador2]);
		break;
		case 3:
		registradores[destino] = divi(registradores[operador1], registradores[operador2]);
		break;
		default:
		printf("Erro");
		break;
	}

	printarRegistradores();

	return 0;
}