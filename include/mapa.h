#ifndef MAPA_H_
#define MAPA_H_

//define os tamanhos maximos do mapa //deprecated
//#define MAX_X 121
//#define MAX_Y 30

//define os possiveis valores para o tabuleiro
typedef enum { VAZIA = 0, COMIDA = 1, DUPLA = 2, TRIPLA = 3, BONUS = 10, BONUS_DUPLO = 100, SPECIAL = -500, PAREDE = 999 } CASA;
//							1%			0,5%		0,25%		0,125%		0,0625%			0,03125%
//define o tipo mapa
#define MAPA CASA**

//inicializa o mapa
MAPA gera_mapa(int max_y,int max_x);

//inicializa os bonus no mapa
void inicializa_bonus(MAPA map, int max_y, int max_x);

//inicializa os bonus no mapa // helper
void inicializa_bonus_helper(MAPA map, CASA tipo, int quantidade, int max_y, int max_x);

//verifica se o mapa est� vazio
int mapa_limpo(MAPA map, int max_y, int max_x);

//limpa uma casa do mapa, usada apos a cobra comer o que havia l�
void limpa_casa(MAPA map, int x, int y);

//destroi o mapa
void free_mapa(MAPA map);

#endif //MAPA_H_
