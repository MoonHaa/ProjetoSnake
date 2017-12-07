#include <stdlib.h>
#include <stdio.h>

#include "mapa.h"

int main(void)
{
	printf("Ola Mundo! Eu sou a teste!\n");

	MAPA map = gera_mapa();
	
	int i, j;
	for (i = 0; i < MAX_Y; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			printf("%i\t", map[i][j]);
		}
		printf("\n");
	}	
	free_mapa(map);
	
	return 0;
}