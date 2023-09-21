#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "lib.h"

uint16_t memoria [64 * 1024];
uint16_t registradores [8];



uint16_t add(uint16_t a, uint16_t b){
	return a+b;
}

uint16_t sub(uint16_t a, uint16_t b){
	return a-b;
}

uint16_t mul(uint16_t a, uint16_t b){
	return a*b;
}

uint16_t divi(uint16_t a, uint16_t b){
	return a/b;
}

void printarRegistradores(){
	for(int i = 0; i < 8; i++){
		printf(" r%d: %d", i, registradores[i]);
	}
}


int main ()
{
    // Exemplo de extração de bits
	//0b0 000000 000 000 000; // Exemplo de um número binário de 16 bits
	memoria[0]= 0b000001111111010;
	registradores[0] = 0;
	registradores[1] = 1;
	registradores[2] = 2;
	registradores[3] = 3;
	registradores[4] = 4;
	registradores[5] = 5;
	registradores[6] = 6;
	registradores[7] = 7;


	uint16_t formato = extract_bits(memoria[0], 15, 1);

	uint16_t opcode = extract_bits(memoria[0], 9, 6);
	
	uint16_t destino = extract_bits(memoria[0], 6, 3);

	uint16_t operador1 = extract_bits(memoria[0], 3, 3);

	uint16_t operador2 = extract_bits(memoria[0], 0, 3);



	switch (opcode) {
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