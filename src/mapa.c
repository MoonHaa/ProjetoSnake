#include "mapa.h"
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

//cria o mapa e inicializa o mapa
MAPA gera_mapa(void)
{
	int i,j;
	MAPA map = (MAPA)malloc(MAX_Y * sizeof(CASA*));

	for (i = 0; i < MAX_Y; i++)
		map[i] = (CASA*)malloc(MAX_X * sizeof(CASA));

	for (i = 0; i < MAX_Y; i++)
		for (j = 0; j < MAX_X; j++)
			map[i][j] = VAZIA;

	for (i = 0; i < MAX_Y; i++)
	{
		map[i][0] = PAREDE;
		map[i][MAX_X-1] = PAREDE;
	}

	for (i = 0; i < MAX_X; i++)
	{
		map[0][i] = PAREDE;
		map[MAX_Y-1][i] = PAREDE;
	}

	inicializa_bonus(map);

	return map;
}

//inicializa os bonus no mapa, usa uma helper
void inicializa_bonus(MAPA map)
{
	int quant_casas = (MAX_Y - 2)*(MAX_X - 2);

	inicializa_bonus_helper(map, COMIDA, quant_casas * 0.01);

	inicializa_bonus_helper(map, DUPLA, quant_casas * 0.005);

	inicializa_bonus_helper(map, TRIPLA, quant_casas * 0.0025);

	inicializa_bonus_helper(map, BONUS, quant_casas * 0.00125);

	inicializa_bonus_helper(map, BONUS_DUPLO, quant_casas * 0.000625);

	inicializa_bonus_helper(map, SPECIAL, quant_casas * 0.0003125);

	return;
}

//gera os bonus em posições aleatorias
void inicializa_bonus_helper(MAPA map, CASA tipo, int quantidade)
{
	srand(clock());
	while (quantidade > 0)
	{
		int y = (rand() % (MAX_Y - 2)) + 1;
		int x = (rand() % (MAX_X - 2)) + 1;

		if (map[y][x] != VAZIA)
			continue;

		map[y][x] = tipo;
		quantidade--;
	}
	return;
}

//verifica se ainda existem bonus no mapa //talvez isso não seja uma implementação muito inteligente
int mapa_limpo(MAPA map)
{
	int check = 1;
	int i, j;
	for (i = 1; (i < (MAX_Y - 1)) && check; i++)
		for (j = 1; (j < (MAX_X - 1)) && check; j++)
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
