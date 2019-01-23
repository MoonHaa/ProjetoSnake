#ifndef JOGO_H_
#define JOGO_H_

//habilita função avançadas de tempo
#define _POSIX_C_SOURCE 200809L

#include <ncurses.h>
#include "arquivo_score.h"
#include "mapa.h"
#include "snake.h"
#include "time.h"

//cria uma janela com os parametros preconfigurados e desenha as bordas na tela, y e x s�o o recuo vertical e lateral, respectivamente
WINDOW* cria_janela(int comp_y, int comp_x, int y, int x);

//exibe o menu principal com destaque
void exibe_menu_principal(WINDOW *janela, int destaque, char* escolhas[], int num_escolhas);

//inicia o jogo
void inicia_jogo(RECORDE* arquivo_recordes);

//janela p�s jogo
int janela_pos_jogo(int max_y, int max_x, int y, int x, JOGADOR* player);

//função de delay do loop do jogo
void loopdelay(struct timespec start,long delay);
#endif //JOGO_H_
