#include "jogo.h"


//cria uma janela iniciando em y/x com dimensoes comp_y/comp_x
WINDOW* cria_janela(int comp_y, int comp_x, int y, int x)
{
	WINDOW* janela = newwin(comp_y, comp_x, y, x); //cria uma nova janela
	init_pair(1, COLOR_GREEN, COLOR_BLACK); //define as cores da tela, no caso texto verde com fundo preto
	wattron(janela, COLOR_PAIR(1)); //define atributo de cor
	wattron(janela, A_BOLD); //define brilho maximo da tela
	keypad(janela, TRUE); //habilita o uso de teclas especias
	box(janela, 0, 0); //desenha as bordas da janela
	wrefresh(janela); //atualiza a tela
	return janela;
}

//exibe o menu principal do jogo
void exibe_menu_principal(WINDOW *janela, int destaque, char* escolhas[], int num_escolhas)
{
	int x = 2, y = 2;
	box(janela, 0, 0);
	for (int i = 0; i < num_escolhas; ++i)
	{
		if (destaque == i + 1) //destaca a op��o
		{
			wattron(janela, A_REVERSE);
			mvwprintw(janela, y, x, "%s", escolhas[i]);
			wattroff(janela, A_REVERSE);
		}
		else
			mvwprintw(janela, y, x, "%s", escolhas[i]);
		y++;
	}
	wrefresh(janela);
}

//inicia o jogo
void inicia_jogo(RECORDE* arquivo_recordes)
{
	int max_y, max_x, menu = 1;
	JOGADOR* player = NULL;
	char string[50];

	getmaxyx(stdscr, max_y, max_x); //tamanho maximo da tela

	//cria janela pra limpar a tela
	WINDOW* background = cria_janela(max_y, max_x, 0, 0);
	//aviso
	mvwprintw(background, 1, 2, "AVISO: Alterar o tamanho da janela pode resultar em erros durante o jogo!");
	//faz a borda da tela
	box(background, 0, 0);
	//atualiza a tela
	wrefresh(background);
	//cria submenu pra setar o nome do usuario
	WINDOW* menu_jogador = cria_janela(max_y - 10, max_x - 20, 5, 10);
	//habilita echo
	echo();
	//pergunta nome do usuario
	mvwprintw(menu_jogador, 1, 2, "Por favor, digite seu nome:\n  ");
	//desenha bordas
	box(menu_jogador, 0, 0);
	//atualiza a tela
	wrefresh(menu_jogador);
	//le o nome do usuario
	wgetstr(menu_jogador,string);
	//desabilita echo
	noecho();
	//cria o jogador
	player = cria_jogador(string);
	//fecha submenu
	delwin(menu_jogador);
	
	while (menu)
	{
		//cria subjanela para exibir os dados do usuario
		WINDOW* janela_player = cria_janela(max_y - 4, max_x - 2, 3, 1);
		//cria subjanela para o mapa
		WINDOW* janela_mapa = cria_janela(max_y - 8, max_x - 4, 6, 2);
		//forca atualizacao da tela apos certo tempo, mesmo sem input do usuario
		//caso haja input do usuario, não há delay na execução do programa
		//caso não haja input do usuario, o programa irá parar por parametro vs 1/10 de segundo
		//isso permite que o jogo possuo atualizações não uniformes, mas garante que o input do usuario será sempre executado
		//halfdelay(3);
		
		//força o input do usuario ser reconhecido imediatamente pelo programa, desabilita buffer de input
		cbreak();
		
		//inicializacao do jogo
		int game_max_y = max_y - 8;
		int game_max_x = max_x - 4;
		int head_x = (game_max_x / 2);
		int head_y = (game_max_y / 2);
		int increment_x = 1, increment_y = 0;
		int flag = 1;

		//delay do loop em us, determina a velocidade de execução do jogo, força o loop a ter um tempo constante de execução
		long delay = 250000; //pode ocorrer do tempo total do loop ser superior ao tempo do delay

		//struct utilizada para contar a passagem do tempo
		struct timespec start;

		//zera o placar do jogador
		player->score = 0;

		MAPA mapa = gera_mapa(game_max_y,game_max_x);

		COBRA* cobra = inicializa(head_x, head_y);
		//loop do jogo
		while (flag)
		{
			clock_gettime(CLOCK_MONOTONIC,&start);

			mvwprintw(janela_player, 1, 2, "Nome: %s Recorde: %i Score: %i", player->nome, player->recorde, player->score); //exibe dados do jogador
			box(janela_player, 0, 0); //desenha as bordas
			wrefresh(janela_player); //atualiza a janela

			box(janela_mapa, 0, 0); //desenha as bordas

			if (mapa_limpo(mapa, game_max_y, game_max_x)) //verifica se o mapa est� limpo, caso verdade, inicializa mais bonus no mapa novamente
				inicializa_bonus(mapa, game_max_y, game_max_x);

			//desenha o mapa na tela
			for (int i = 0; i < game_max_y; i++)
			{
				for (int j = 0; j < game_max_x; j++)
				{
					CASA posicao = mapa[i][j];

					switch (posicao)
					{
					case VAZIA:
						mvwprintw(janela_mapa, i, j, " ");
						break;
					case COMIDA:
						mvwprintw(janela_mapa, i, j, "1");
						break;
					case DUPLA:
						mvwprintw(janela_mapa, i, j, "2");
						break;
					case TRIPLA:
						mvwprintw(janela_mapa, i, j, "3");
						break;
					case BONUS:
						mvwprintw(janela_mapa, i, j, "b");
						break;
					case BONUS_DUPLO:
						mvwprintw(janela_mapa, i, j, "B");
						break;
					case SPECIAL:
						mvwprintw(janela_mapa, i, j, "*");
						break;
					default:
						break;
					}
				}
			}

			//desenha a cobra na tela
			NO* no_cobra = cobra->cabeca; //recebe a cabe�a do enfeite

			while (no_cobra->proximo != NULL) //enquanto tiver nos
			{
				//desenha a cobra
				mvwprintw(janela_mapa, no_cobra->y, no_cobra->x, "#");

				//move para o proximo no
				no_cobra = no_cobra->proximo;
			}

			//força o programa a não esperar pelo wgetch caso não tenha input disponivel
			nodelay(janela_mapa,TRUE);

			//captura o teclado
			int tecla = wgetch(janela_mapa);
			switch (tecla)
			{
			case KEY_UP:
				if (increment_y != 1)
				{
					increment_x = 0;
					increment_y = -1;
				}
				break;
			case KEY_DOWN:
				if (increment_y != -1)
				{
					increment_x = 0;
					increment_y = 1;
				}
				break;
			case KEY_LEFT:
				if (increment_x != 1)
				{
					increment_x = -1;
					increment_y = 0;
				}
				break;
			case KEY_RIGHT:
				if (increment_x != -1)
				{
					increment_x = 1;
					increment_y = 0;
				}
				break;
			default:
				break;
			}

			//analisa a proxima posicao da cabe�a da cobra
			head_x += increment_x;
			head_y += increment_y;

			if (posicao_pertencente(cobra, head_x, head_y)) //cobra bateu em si mesma
				flag = 0;

			switch (mapa[head_y][head_x])
			{
			case PAREDE: //cobra bateu numa parede
				flag = 0;
				break;
			case VAZIA: //casa vazia, anda uma posicao
				andar(cobra, head_x, head_y);
				break;
			case COMIDA: //achou comida
			case DUPLA:
			case TRIPLA:
			case BONUS:
			case BONUS_DUPLO:
				comer(cobra, head_x, head_y);
				update_score(player, mapa[head_y][head_x]);
				limpa_casa(mapa, head_x, head_y);
				delay-=250;
				if (delay < 0) //garante que o delay não seja negativo
					delay = 0;
				break;
			case SPECIAL: //achou o special
				andar(cobra, head_x, head_y);
				update_score(player, mapa[head_y][head_x]);
				limpa_casa(mapa, head_x, head_y);
				break;
			default:
				break;
			}

			wrefresh(janela_mapa); //atualiza a janela

			//faz o loop ter tempo constante
			loopdelay(start,delay);

			//força o programa a não esperar pelo wgetch caso não tenha input disponivel
			nodelay(janela_mapa,TRUE);
			
			//antes de dar flush no buffer, salva até 3 inputs
			int tecla1 = wgetch(janela_mapa),
				tecla2 = wgetch(janela_mapa),
				tecla3 = wgetch(janela_mapa);

			//dá flush do input
			flushinp();

			//reintroduz os inputs no buffer
			ungetch(tecla1);
			ungetch(tecla2);
			ungetch(tecla3);
		}
		
		//deleta cobra
		kill_cobra(cobra);
		//deleta mapa
		free_mapa(mapa);
		//fechar subjanela do mapa
		delwin(janela_mapa);
		//fechar subjanela do usuario
		delwin(janela_player);
		//salva o recorde do usuario
		update_player_recorde(player);
		//subjanela de derrota/sair
		menu = janela_pos_jogo(max_y + 4, max_x, 6, 2, player); //valores corrigidos para cobrir somente o mapa
	}
	//atualiza os recordes salvos
	update_recordes(arquivo_recordes, player);
	//deleta o jogador
	free_jogador(player);
	//fecha a janela principal
	delwin(background);
}

//gera a janela de p�s jogo
int janela_pos_jogo(int max_y, int max_x, int y, int x, JOGADOR* player)
{
	//flag de retorno para informar se o usuario escolheu sair ou reiniciar o jogo
	int retorno = 1;
	//subjanela de derrota/sair
	WINDOW* janela_eof = cria_janela(max_y - 2*y, max_x - 2*x, y, x);
	//sair do modo halfdelay
	nocbreak();
	//entrar no modo de captura continua sem timeout
	cbreak();
	while (1)
	{
		//limpa a tela
		wclear(janela_eof);
		//desenha borda
		box(janela_eof, 0, 0);
		//mensagem de fim de jogo
		mvwprintw(janela_eof, 2, 2, "Score final: %i\t Recorde: %i", player->score, player->recorde);
		mvwprintw(janela_eof, 3, 2, "Seu recorde sera salvo automaticamente ao sair do programa");
		mvwprintw(janela_eof, 4, 2, "Aperte Enter para tentar novamente ou Backspace para voltar ao menu principal");
		//atualiza a janela
		wrefresh(janela_eof);
		//captura input do usuario
		int key = wgetch(janela_eof);
		//usuario sinalizou saida do programa
		if (key == KEY_BACKSPACE)
		{
			retorno = 0;
			break;
		}
		//usuario sinalizou reinicio do jogo
		if (key == 10)
			break;
	}
	//fechar subjanela de derrota
	delwin(janela_eof);
	//retorna a saida do programa
	return retorno;
}

//executa o delay no final do loop do jogo
void loopdelay(struct timespec start, long delay)
{
	struct timespec sleep_time, stop;

	//contabiliza o tempo o mais tarde possivel, considera o tempo gasto total incluindo a chamada dessa função
	clock_gettime(CLOCK_MONOTONIC,&stop);

	//caso o loop seja mais lento que o delay apenas sai da função sem fazer nada
	if ( ( (stop.tv_sec * 1000000000 + stop.tv_nsec) - (start.tv_sec * 1000000000 + start.tv_nsec) ) > (delay * 1000) )
		return;

	//recontabiliza o tempo gasto na operação acima
	clock_gettime(CLOCK_MONOTONIC,&stop);
	
	//contabiliza o tempo faltante
	long nsec = (delay * 1000) - ((stop.tv_sec * 1000000000 + stop.tv_nsec) - (start.tv_sec * 1000000000 + start.tv_nsec));
	sleep_time.tv_sec = (__time_t)(nsec / 1000000000);
	sleep_time.tv_nsec = (long)(nsec % 1000000000);
	
	//adormece pelo tempo faltante
	while( nanosleep(&sleep_time,&sleep_time) == -1 )
		continue;
}