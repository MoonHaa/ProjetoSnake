#include "mapa.h"
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

//cria o mapa e inicializa o mapa
MAPA gera_mapa(int max_y,int max_x)
{
	int i,j;
	MAPA map = (MAPA)malloc(max_y * sizeof(CASA*));

	for (i = 0; i < max_y; i++)
		map[i] = (CASA*)malloc(max_x * sizeof(CASA));

	for (i = 0; i < max_y; i++)
		for (j = 0; j < max_x; j++)
			map[i][j] = VAZIA;

	for (i = 0; i < max_y; i++)
	{
		map[i][0] = PAREDE;
		map[i][max_x-1] = PAREDE;
	}

	for (i = 0; i < max_x; i++)
	{
		map[0][i] = PAREDE;
		map[max_y-1][i] = PAREDE;
	}

	inicializa_bonus(map, max_y, max_x);

	return map;
}

//inicializa os bonus no mapa, usa uma helper
void inicializa_bonus(MAPA map, int max_y, int max_x)
{
	int quant_casas = (max_y - 2)*(max_x - 2);

	inicializa_bonus_helper(map, COMIDA, quant_casas * 0.01, max_y, max_x);

	inicializa_bonus_helper(map, DUPLA, quant_casas * 0.005, max_y, max_x);

	inicializa_bonus_helper(map, TRIPLA, quant_casas * 0.0025, max_y, max_x);

	inicializa_bonus_helper(map, BONUS, quant_casas * 0.00125, max_y, max_x);

	inicializa_bonus_helper(map, BONUS_DUPLO, quant_casas * 0.000625, max_y, max_x);

	inicializa_bonus_helper(map, SPECIAL, quant_casas * 0.0003125, max_y, max_x);

	return;
}

//gera os bonus em posi��es aleatorias
void inicializa_bonus_helper(MAPA map, CASA tipo, int quantidade, int max_y, int max_x)
{
	if(quantidade <= 0) //deve sempre existir pelo menos 1 casa com o bonus, caso contrario, não faz sentido a chamada da função 
		quantidade = 1;

	srand(clock());
	while (quantidade > 0)
	{
		int y = (rand() % (max_y - 2)) + 1;
		int x = (rand() % (max_x - 2)) + 1;

		if (map[y][x] != VAZIA)
			continue;

		map[y][x] = tipo;
		quantidade--;
	}
	return;
}

//verifica se ainda existem bonus no mapa //talvez isso n�o seja uma implementa��o muito inteligente
int mapa_limpo(MAPA map, int max_y, int max_x)
{
	int check = 1;
	int i, j;
	for (i = 1; (i < (max_y - 1)) && check; i++)
		for (j = 1; (j < (max_x - 1)) && check; j++)
			if ((map[i][j] != VAZIA) && (map[i][j] != SPECIAL) && (map[i][j] != PAREDE))
				check = 0;
	return check;
}

//limpa o bonus de uma casa, sinalizando que a cobra o comeu
void limpa_casa(MAPA map, int x, int y)
{
	map[y][x] = VAZIA;
	return;
}

//destroi o mapa
void free_mapa(MAPA map)
{
	free(map);
	return;
}
