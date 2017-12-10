#ifndef SNAKE_H_
#define SNAKE_H_

#include "lista.h"

//define o tamanho de inicialização da cobra
#define INIT 15

//define o tipo cobra
typedef struct cobra {
	int tamanho;
	NO* cabeca;
}COBRA;

//faz a cobra andar uma posição
void andar(COBRA* snake, int x, int y);

//faz a cobra comer uma posição
void comer(COBRA* snake, int x, int y);

//inicializa a cobra a partir da posição fornecida
COBRA* inicializa(int x, int y);

//destroi a cobra
void kill_cobra(COBRA* snake);

//verifica se a posicao pertence a cobra, desconsiderando a ultima posicao
int posicao_pertencente(COBRA* snake, int x, int y);

#endif //SNAKE_H_
