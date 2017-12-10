#ifndef JOGO_H_
#define JOGO_H_

#include <ncurses.h>
#include "arquivo_score.h"
#include "mapa.h"
#include "snake.h"


//cria uma janela com os parametros preconfigurados e desenha as bordas na tela, y e x são o recuo vertical e lateral, respectivamente
WINDOW* cria_janela(int comp_y, int comp_x, int y, int x);

//exibe o menu principal com destaque
void exibe_menu_principal(WINDOW *janela, int destaque, char* escolhas[], int num_escolhas);

//inicia o jogo
void inicia_jogo(RECORDE* arquivo_recordes);



#endif //JOGO_H_
