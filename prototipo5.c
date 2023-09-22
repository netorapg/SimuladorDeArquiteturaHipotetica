#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "lib.h" // Biblioteca usada para extração de bits

//COISAS PARA FAZER
//Tire tudo do main, deixe o código mais modular
// Deixe uma instrução armazenada para cada memória

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

uint16_t cmp_equal(uint16_t a, uint16_t b){ // Instrução de comparação igual
    if(a == b){
        return 1;
    }
    return 0;
}

uint16_t cmp_neq(uint16_t a, uint16_t b){ // Instrução de comparação diferente
    if(a != b){
        return 1;
    }
    return 0;
}

uint16_t mov(uint16_t a, uint16_t b){ // Instrução de movimentação
	return a;
}

uint16_t load(uint16_t a){ // Instrução de load
    return memoria[a];
}

void printarRegistradores(){ // Printa os registradores
	for(int i = 0; i < 8; i++){
		printf(" r%d: %d \n", i, registradores[i]);
	}
}

/*void preencheRegistradores(){
	for(int i = 0; i < 8; i++){
		registradores[i] = 0;
	}
}*/


void inicializandoRegistradores(){
	registradores[0] = 0; 
	registradores[1] = 1;
	registradores[2] = 2;
	registradores[3] = 3;
	registradores[4] = 4;
	registradores[5] = 5;
	registradores[6] = 6;
	registradores[7] = 7;
}

void executarInstrucao() {
	uint16_t formato = extract_bits(memoria[3], 15, 1); // Extrai o bit de formato da instrução

	uint16_t opcode = extract_bits(memoria[3], 9, 6); // Extrai o opcode da instrução
	
	uint16_t destino = extract_bits(memoria[3], 6, 3); // Extrai o destino da instrução

	uint16_t operador1 = extract_bits(memoria[3], 3, 3); // Extrai o operador 1 da instrução

	uint16_t operador2 = extract_bits(memoria[3], 0, 3); // Extrai o operador 2 da instrução

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
        case 4:
        registradores[destino] = cmp_equal(registradores[operador1], registradores[operador2]);
        break;
        case 5:
        registradores[destino] = cmp_neq(registradores[operador1], registradores[operador2]);
        break;
        case 6:
        registradores[destino] = load(registradores[operador1]);
        break;
		default:
		printf("Erro");
		break;
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
	//
	memoria[0] = 0b0000000101101101; // Add r5, r5, r5
	memoria[1] = 0b0000001110101101;// Sub r6, r5, r5
	memoria[2] = 0b0000010111101101;// Mul r7, r5, r5
	memoria[3] = 0b0000011100101101;// Div r4, r5, r5
; // Aqui aidicionamos o número binário da instrução na memória
/*// Inicializando os registradores
	registradores[0] = 0; 
	registradores[1] = 1;
	registradores[2] = 2;
	registradores[3] = 3;
	registradores[4] = 4;
	registradores[5] = 5;
	registradores[6] = 6;
	registradores[7] = 7;*/
    
//	preencheRegistradores();
	inicializandoRegistradores();
	executarInstrucao();

	printarRegistradores();

	return 0;
}