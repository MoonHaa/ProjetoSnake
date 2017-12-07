#ifndef MAPA_H_
#define MAPA_H_

//define os tamanhos maximos do mapa
#define MAX_X 21
#define MAX_Y 21

//define os possiveis valores para o tabuleiro
typedef enum { VAZIA = 0, COMIDA = 1, DUPLA = 2, TRIPLA = 3, BONUS = 10, BONUS_DUPLO = 100, SPECIAL = -500, PAREDE = 999 } CASA;
//				68,5%		16%			8%			4%			2%			1%				0,5%
//define o tipo mapa
#define MAPA CASA**

//inicializa o mapa
MAPA gera_mapa(void);

//inicializa os bonus no mapa
void inicializa_bonus(MAPA map);

//inicializa os bonus no mapa // helper
void inicializa_bonus_helper(MAPA map, CASA tipo, int quantidade);

//verifica se o mapa está vazio
int mapa_limpo(MAPA map);

//limpa uma casa do mapa, usada apos a cobra comer o que havia lá
void limpa_casa(MAPA map, int x, int y);

//destroi o mapa
void free_mapa(MAPA map);

#endif //MAPA_H_
