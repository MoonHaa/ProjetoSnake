#include "arquivo_score.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

//abre o arquivo de scores e cria o vetor de scores
RECORDE * abre_recordes(char * arquivo)
{
	int i;
	FILE* file = fopen(arquivo, "r");
	
	RECORDE* vetor = (RECORDE*)malloc(MAX_RECORD * sizeof(RECORDE));

	for (i = 0; i < MAX_RECORD; i++)
	{
		vetor[i].score = 0;
		strcpy(vetor[i].nome, "\0");
	}

	if (file != NULL)
	{
		int recordes_salvos;
		char string[50];
		fscanf(file,"%i %s %s ", &recordes_salvos, string, string);

		for (i = 0; i < recordes_salvos; i++)
		{
			int score;
			fscanf(file,"%s %i ", string, &score);
			//segundo cplusplus.com, para codigos c11 (iso c), um caractere de espaço nos parametros de leitura irá 
			//consumir com QUALQUER quantidade de caracteres de espaço (incluindo espaços, newline e tab)
			vetor[i].score = score;
			strcpy(vetor[i].nome, string);
		}

		fclose(file);
	}

	return vetor;
}

//verifica se o recorde do player está entre os MAX_RECORD do vetor
int verifica_recorde(RECORDE* recordes, JOGADOR * player)
{
	for (int i = 0; i < MAX_RECORD; i++)
	{
		if (player->recorde > recordes[i].score)
		{
			return 1;
		}
	}

	return 0;
}

//atualiza o vetor de recordes para incluir o recorde do jogador, se este estiver entre os MAX_RECORD
void update_recordes(RECORDE * recordes, JOGADOR * player)
{
	if (verifica_recorde(recordes, player))
	{
		recordes[MAX_RECORD - 1].score = player->recorde;
		strcpy(recordes[MAX_RECORD - 1].nome, player->nome);

		ordena_recordes(recordes);
	}
}

//escreve os recordes no arquivo, sobreescrevendo o arquivo incondicionalmente
void salva_recordes(char * arquivo, RECORDE * recordes)
{
	FILE* file = fopen(arquivo, "w");

	int count;

	for (count = 0; count < MAX_RECORD; count++)
	{
		if (recordes[count].score <= 0)
			break;
	}

	fprintf(file, "%i %s\n", count, "recorde(s) salvo(s)!");

	for (int i = 0; i < count; i++)
	{
		fprintf(file, "%s\n%i\n", recordes[i].nome, recordes[i].score);
	}

	fclose(file);
	return;
}

//ordena os elementos do vetor //decrescente
void ordena_recordes(RECORDE * recordes)
{
	RECORDE atual;
	int i, j;
	for (i = 1; i < MAX_RECORD; i++)
	{
		atual.score = recordes[i].score;
		strcpy(atual.nome, recordes[i].nome);

		for (j = i - 1; (j >= 0) && (atual.score > recordes[j].score); j--)
		{
			recordes[j + 1].score = recordes[j].score;
			strcpy(recordes[j + 1].nome, recordes[j].nome);
		}
		recordes[j + 1].score = atual.score;
		strcpy(recordes[j + 1].nome, atual.nome);
	}
}

//deleta o vetor de recordes
void free_recordes(RECORDE * recordes)
{
	free(recordes);
}
