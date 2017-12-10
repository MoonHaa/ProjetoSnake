#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#include "snake.h"
#include "arquivo_score.h"
#include "jogo.h"

int main(void)
{
	int max_x, max_y,
		head_x = 15, head_y = 1,
		head_x_n = 0, head_y_n = 0,
		increment_x = 1, increment_y = 0,
		escolha = 0, destaque = 1;

	char *escolhas[] = { "Iniciar jogo", "Mostrar recordes", "Sair" };
	int num_escolhas = sizeof(escolhas) / sizeof(char*);

	int tecla;

	COBRA* enfeite = inicializa(head_x, head_y); //cobrinha de enfeite para o menu

	RECORDE* arquivo_recordes = abre_recordes("recordes.txt"); //carrega o arquivo de recordes

															   //inicializar a tela
	initscr(); //inicializa a tela
	clear(); //limpa a tela
	noecho(); //esconde as teclas sendo pressionadas
	cbreak(); //desabilita o buffer de input, passa key_functions especiais
	halfdelay(3); //habilita espera temporizada por input e depois continua a execução
	curs_set(0); //desabilita o cursor
	keypad(stdscr, TRUE); //habilita o uso de teclas especias
	start_color(); //habilita o uso de cores na tela

	getmaxyx(stdscr, max_y, max_x); //tamanho maximo da tela

	WINDOW *janela_principal, *menu_principal, *menu_recordes;

	janela_principal = cria_janela(max_y, max_x, 0, 0); //cria a janela principal

	while (1)
	{
		getmaxyx(stdscr, max_y, max_x); //tamanho maximo da tela

										//mostra menu principal
		{
			menu_principal = cria_janela(max_y - 10, max_x - 20, 5, 10); //cria a janela de menu principal

			exibe_menu_principal(menu_principal, destaque, escolhas, num_escolhas); //exibe o menu principal

			tecla = wgetch(menu_principal); //le a tecla pressionada pelo usuario
			switch (tecla)	//escolhe de acordo
			{
			case KEY_UP: //muda para o texto acima
				if (destaque == 1)
					destaque = num_escolhas;
				else
					destaque--;
				break;
			case KEY_DOWN: //muda pra o texto abaixo
				if (destaque == num_escolhas)
					destaque = 1;
				else
					destaque++;
				break;
			case 10: //enter, seleciona opção
				escolha = destaque;
				break;
			default:
				break;
			}

			delwin(menu_principal); //deleta a janela de menu

		}

		//inicia novo jogo
		if (escolha == 1)
		{
			inicia_jogo(arquivo_recordes); //inicia o jogo

			halfdelay(3); //habilita espera temporizada por input e depois continua a execução

			escolha = 0; //reseta escolha do usuario
		}
		//mostra recordes
		if (escolha == 2)
		{
			menu_recordes = cria_janela(max_y, max_x, 0, 0); //cria janela dos recordes

			wclear(menu_recordes); //limpa a tela

			box(menu_recordes, 0, 0); //desenha as bordas

			mvwprintw(menu_recordes, 1, 1, "Ranking\tScore\t\tNome\t\tPressione Enter para sair");

			wrefresh(menu_recordes);

			WINDOW* subjanela = cria_janela(22, max_x, 4, 0); //cria subjanela

			int init = 0, end = 20, flag = 1;

			while (flag)
			{
				wclear(subjanela); //limpa a subjanela

				box(subjanela, 0, 0); //desenha as bordas

				for (int i = init, y = 1; i < end; i++, y++)
				{
					mvwprintw(subjanela, y, 1, "%i\t\t%i\t\t%s", i + 1, arquivo_recordes[i].score, arquivo_recordes[i].nome); //lista os recordes
				}

				wrefresh(subjanela); //atualiza a subjanela

				tecla = wgetch(subjanela); //le tecla

				switch (tecla)
				{
				case KEY_UP: //avança lista para cima
					if (init <= 0)
					{
						init = MAX_RECORD - 20;
						end = MAX_RECORD;
					}
					else
					{
						init -= 1;
						end -= 1;
					}
					break;
				case KEY_DOWN: //avança lista para baixo
					if (end >= MAX_RECORD)
					{
						init = 0;
						end = 20;
					}
					else
					{
						init += 1;
						end += 1;
					}
					break;
				case 10: //sai da exibição da lista
					flag = 0;
					break;
				default:
					break;
				}
			}

			delwin(subjanela); //destroi a subjanela
			delwin(menu_recordes); //destroi o menu de recordes

			escolha = 0; //reseta estado da escolha
		}

		//usuario escolheu sair
		if (escolha == 3)
			break;	//encerra o loop infinito

					//background dinamico, seria ideal por numa função a parte, senão desse tanto problema pra fazer
		{
			head_x_n = head_x + increment_x; //analisa a proxima posição do objeto
			head_y_n = head_y + increment_y; //analisa a proxima posição do objeto

			if (head_x_n >= (max_x - 1)) //se chegar na borda direta, muda de direção
			{
				increment_x = 0;
				increment_y = 1;
			}

			if (head_y_n >= (max_y - 1)) //se chegar na borda inferior, muda de direção
			{
				increment_x = -1;
				increment_y = 0;
			}

			if (head_x_n < 1) //se chegar na borda esquerda, muda de direção
			{
				increment_x = 0;
				increment_y = -1;
			}

			if (head_y_n < 1) //se chegar na borda superior, muda de direção
			{
				increment_x = 1;
				increment_y = 0;
			}

			head_x += increment_x; //anda com o objeto
			head_y += increment_y; //anda com o objeto

			wclear(janela_principal); //limpa a janela principal

			box(janela_principal, 0, 0); //desenha as bordas da janela

			andar(enfeite, head_x, head_y); //faz a cobra de enfeite andar no segundo plano

			NO* no_enfeite = enfeite->cabeca; //recebe a cabeça do enfeite

			while (no_enfeite->proximo != NULL) //enquanto tiver nos
			{
				//desenha a cobra
				mvwprintw(janela_principal, no_enfeite->y, no_enfeite->x, "#");

				//move para o proximo no
				no_enfeite = no_enfeite->proximo;
			}

			wrefresh(janela_principal); //atualiza a janela principal
		}
	}

	kill_cobra(enfeite); //mata a cobra de enfeite

	salva_recordes("recordes.txt", arquivo_recordes); //salva os recordes do jogo
	free_recordes(arquivo_recordes); //fecha o arquivo de recordes

	refresh(); //atualiza a tela
	delwin(janela_principal); //deleta a janela principal
	endwin(); //encerra a tela
	return 0;
}