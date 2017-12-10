#include "snake.h"
#include <malloc.h>
#include <stdio.h>

//anda uma posição mantendo o tamanho da cobra
void andar(COBRA * snake, int x, int y)
{
	NO* ponteiro = fim(snake->cabeca);
	while (ponteiro->anterior != NULL)
	{
		ponteiro->x = ponteiro->anterior->x;
		ponteiro->y = ponteiro->anterior->y;
		ponteiro = ponteiro->anterior;
	}
	ponteiro->x = x;
	ponteiro->y = y;

	return;
}

//mantem todas as posições da cobra, aumentando a nova posição na cabeça da cobra, aumenta o tamanho em 1
void comer(COBRA * snake, int x, int y)
{
	snake->cabeca = push_front(snake->cabeca, x, y);
	snake->tamanho++;
	return;
}

//inicializa a cobra com o tamanho definido pela macro INIT, sempre na horizontal, pra tras da posicao x
COBRA* inicializa(int x, int y)
{
	COBRA* snake = (COBRA*)malloc(sizeof(COBRA));
	snake->tamanho = INIT;
	snake->cabeca = cria_lista(x, y);
	int cont;
	for (cont = 1; cont <= INIT; cont++)
		snake->cabeca = push_back(snake->cabeca, x - cont, y);
	return snake;
}

//assassina a cobra, destruindo sua cauda e depois a sua cabeça
void kill_cobra(COBRA * snake)
{
	free_lista(snake->cabeca);
	snake->cabeca = NULL;
	free(snake);
	snake = NULL;
	return;
}

//verifica se a posicao pertence a cobra, desconsiderando a ultima posicao
int posicao_pertencente(COBRA* snake, int x, int y)
{
	NO* ptr = snake->cabeca;
	NO* cauda = fim(ptr);
	while (ptr->proximo != cauda)
	{
		if ((ptr->x == x) && (ptr->y == y))
			return 1;

		ptr = ptr->proximo;
	}
	return 0;
}