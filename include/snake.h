#ifndef SNAKE_H_
#define SNAKE_H_

#include "lista.h"

//define o tamanho de inicializa��o da cobra
#define INIT 3

//define o tipo cobra
typedef struct cobra {
	int tamanho;
	NO* cabeca;
}COBRA;

//faz a cobra andar uma posi��o
void andar(COBRA* snake, int x, int y);

//faz a cobra comer uma posi��o
void comer(COBRA* snake, int x, int y);

//inicializa a cobra a partir da posi��o fornecida
COBRA* inicializa(int x, int y);

//destroi a cobra
void kill_cobra(COBRA* snake);

#endif //SNAKE_H_
