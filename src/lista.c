#include "lista.h"
#include <malloc.h>

//cria o primeiro no da lista e inicializa com valores 0/0, retorna o inicio da lista
NO * cria_lista(int x, int y)
{
	NO* novo = (NO*)malloc(sizeof(NO));
	novo->x = x;
	novo->y = y;
	novo->anterior = NULL;
	novo->proximo = NULL;
	return novo;
}

//adiciona um no ao inicio da lista e inicializa com os valores fornecidos, retorna o inicio da lista
NO * push_front(NO * cabeca, int x, int y)
{
	NO* novo = (NO*)malloc(sizeof(NO));
	novo->x = x;
	novo->y = y;
	novo->anterior = NULL;
	cabeca->anterior = novo;
	novo->proximo = cabeca;
	return novo;
}

//adiciona um no ao fim da lista e inicializa com os valores fornecidos, retorna o inicio da lista
NO * push_back(NO * cabeca, int x, int y)
{
	NO* novo = (NO*)malloc(sizeof(NO));
	novo->x = x;
	novo->y = y;

	NO* fim_da_lista = fim(cabeca);
	novo->anterior = fim_da_lista;
	fim_da_lista->proximo = novo;
	novo->proximo = NULL;
	return cabeca;
}

//remove um no do inicio da lista, retorna o inicio da lista
NO * pop_front(NO * cabeca)
{
	NO* proximo = cabeca->proximo;
	proximo->anterior = NULL;
	free(cabeca);
	return proximo;
}

//remove um no do fim da lista, retorna o inicio da lista
NO * pop_back(NO * cabeca)
{
	NO* fim_da_lista = fim(cabeca);
	NO* anterior = fim_da_lista->anterior;
	anterior->proximo = NULL;
	free(fim_da_lista);
	return cabeca;
}

//deleta todos os elementos da lista, retorna NULL
NO * free_lista(NO * cabeca)
{
	NO* ponteiro = cabeca;

	if (ponteiro == NULL)
		return NULL;

	while (ponteiro->proximo != NULL)
	{
		ponteiro = ponteiro->proximo;
		free(ponteiro->anterior);
	}

	free(ponteiro);

	return NULL;
}

//encontra o ultimo no da lista, retorna o fim da lista
NO * fim(NO * cabeca)
{
	NO* ponteiro = cabeca;
	while (ponteiro->proximo != NULL)
	{
		ponteiro = ponteiro->proximo;
	}
	return ponteiro;
}
