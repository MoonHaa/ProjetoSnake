#include "jogador.h"
#include <malloc.h>
#include <string.h>

//cria um novo jogador, inicializa seu score e seu recorde como zero, inicializa seu nome
JOGADOR * cria_jogador(char nome[50])
{
	JOGADOR* novo = (JOGADOR*)malloc(sizeof(JOGADOR));
	novo->recorde = 0;
	novo->score = 0;
	strcpy(novo->nome, nome);
	return novo;
}

//atualiza o score do jogador de acordo com o valor passado nos parametros
inline void update_score(JOGADOR * player, int valor)
{
	player->score += valor;
}

//atualiza o recorde do jogador se o score atual for maior q o recorde atual
inline void update_recorde(JOGADOR * player)
{
	if (player->score > player->recorde)
		player->recorde = player->score;
}

//deleta um jogador
void free_jogador(JOGADOR * player)
{
	free(player);
	return;
}
