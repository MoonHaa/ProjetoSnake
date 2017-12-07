#ifndef LISTA_H_
#define LISTA_H_

//define o tipo NO
typedef struct NO {
	struct NO* anterior;
	int x;
	int y;
	struct NO* proximo;
}NO;

//cria uma lista duplamente encadeada
NO* cria_lista(int x, int y);

//adiciona no inicio da lista
NO* push_front(NO* cabeca, int x, int y);

//adiciona no fim da lista
NO* push_back(NO* cabeca, int x, int y);

//remove do inicio da lista
NO* pop_front(NO* cabeca);

//remove do fim da lista
NO* pop_back(NO* cabeca);

//deleta a lista
NO* free_lista(NO* cabeca);

//retorna o fim da lista
NO* fim(NO* cabeca);
#endif //LISTA_H_
