#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "lib.h"

uint16_t memoria [64 * 1024];
uint16_t registradores [8];

const char* get_reg_name_str (uint16_t reg)
{
	static const char *str[] = {
		"r0",
		"r1",
		"r2",
		"r3",
		"r4",
		"r5",
		"r6",
		"r7"
	};

	return str[reg];
}


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

int main (int argc, char **argv)
{
	/*if (argc != 2) {
		printf("usage: %s [bin_name]\n", argv[0]);
		exit(1);
	}*/
	

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


	/*registradores[destino] = 1+1;
	printf("%d\n", registradores[5]);
	//printf("%d", formato);
	printf("%d", opcode);
	printf("%d", destino);
	printf("%d", operador1);
	printf("%d", operador2);
	
	printf("\n");	*/
	

	/*if(formato == 0){
		printf("formato R\n");
	}else{
		printf("formato I\n");
	}

	if(opcode == 0){
		printf("ADD\n");
	}else if(opcode == 1){
		printf("SUB\n");
	}else if(opcode == 2){
		printf("MUL\n");
	}else if(opcode == 3){
		printf("DIV\n");
	}else if(opcode == 4){
		printf("CMP\n");
	}else if(opcode == 5){
		printf("CMPNQ\n");
	}
*/
	



	//printf("Valor original: %04x\n", valor); // Mostra o valor original em hexadecimal
	//printf("Bits extraídos: %04x\n", formato); // Mostra os bits extraídos em hexadecimal
	
	return 0;
}