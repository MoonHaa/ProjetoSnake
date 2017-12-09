#ifndef ARQUIVO_SCORE_H_
#define ARQUIVO_SCORE_H_

#include "jogador.h"

//define maximo de recordes a serem salvos
#define MAX_RECORD 100

//define o tipo recorde
typedef struct recorde {
	int score;
	char nome[50];
}RECORDE;

//abre arquivo com recordes, caso não encontre o arquivo, retorna null
//Warning! Essa função aloca um vetor de tam MAX_RECORD do tipo RECORDE
RECORDE* abre_recordes(char* arquivo);

//verifica se o score do jogador está entre os MAX_RECORD melhores scores
int verifica_recorde(RECORDE* recordes, JOGADOR* player);

//atualiza o vetor de recordes se o jogador possuir um recorde maior
void update_recordes(RECORDE* recordes, JOGADOR* player);

//salva o vetor de recorde no arquivo
//Warning! Isso sobreescreve o arquivo incondicionalmente
void salva_recordes(char* arquivo, RECORDE* recordes);

//ordena o vetor de recordes
void ordena_recordes(RECORDE* recordes);

//deleta o vetor de recordes
void free_recordes(RECORDE* recordes);

#endif //ARQUIVO_SCORE_H_
