#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "lib.h" // Biblioteca usada para extração de bits

//COISAS PARA FAZER
// 0 - FAzer a decodificação do formato I
// 1 - Fazer as instruções de comparação
// 2 - Fazer as instruções de load
// 3 - Fazer as instruções de store
// 4 - Fazer as instruções de mov
// 5 - Fazer as instruções de jump

//Perguntar ao professor
// A instrução de load funciona, no entanto, não do jeito certo. Ele não está seguindo a instrução binaria de forma correta
// A instrução de store funciona, no entanto, não do jeito certo. Ele não está seguindo a instrução binaria de forma correta

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
uint16_t store(uint16_t a, uint16_t b){ // Instrução de store
	memoria[a] = b;
	return 0;
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
	memoria[2] = 0b0000010111101101;// Mul r7, r5, r5
	memoria[3] = 0b0000011100101101;// Div r4, r5, r5
	memoria[4] = 0b0001111111010; // load r7, [r1]
	memoria[5] = 0b0010000111010; // store [r7], r2
}
// Aqui inicializamos os registradores
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
// Aqui executamos a instrução
void executarInstrucao() {

	uint16_t instrucao = memoria[5]; // Pega a instrução na memória

	uint16_t formato = extract_bits(instrucao, 15, 1); // Extrai o bit de formato da instrução
	uint16_t opcode = extract_bits(instrucao, 9, 6); // Extrai o opcode da instrução
	uint16_t destino = extract_bits(instrucao, 6, 3); // Extrai o destino da instrução
	uint16_t operador1 = extract_bits(instrucao, 3, 3); // Extrai o operador 1 da instrução
	uint16_t operador2 = extract_bits(instrucao, 0, 3); // Extrai o operador 2 da instrução

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
	instrucoesNaMemoria();
	inicializandoRegistradores();
	executarInstrucao();
	printarRegistradores();
	return 0;
}