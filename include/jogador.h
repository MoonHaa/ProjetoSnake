#ifndef JOGADOR_H_
#define JOGADOR_H_

//define o tipo jogador
typedef struct player {
	int score;
	char nome[50];
	int recorde;
}JOGADOR;

//inicializa um jogador
JOGADOR* cria_jogador(char nome[50]);

//atualiza o score do jogador
extern void update_score(JOGADOR* player, int valor);

//atualiza o recorde (maior score) do jogador
extern void update_recorde(JOGADOR* player);

//deleta um jogador
void free_jogador(JOGADOR* player);

#endif //JOGADOR_H_
