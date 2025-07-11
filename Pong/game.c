#include "game.h"
#include <ncurses.h>
#include <stdio.h>

int colors()
{
	start_color();
	if (has_colors() == false)
	{
		endwin();
		printf("Your terminal does not support colors\n");
		return 1;
	}

	init_pair(1, COLOR_BLUE, COLOR_YELLOW);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_GREEN);
	init_pair(5, COLOR_WHITE, COLOR_WHITE);
	init_pair(6, COLOR_BLUE, COLOR_BLUE);
	init_pair(7, COLOR_RED, COLOR_RED);
	init_pair(8, COLOR_RED, COLOR_YELLOW);
	init_pair(9, COLOR_BLUE, COLOR_WHITE);
	init_pair(10, COLOR_BLACK, COLOR_BLACK);

	return 0;
}

void draw_player_pad(paddle pad)
{
	attron(COLOR_PAIR(6));
	for(int y = pad.pos_y; y < pad.pos_y + pad.height; y++)
		mvaddch(y, pad.pos_x, '|');
	attroff(COLOR_PAIR(6));
}

void draw_AIpad(paddle AIpad)
{
	attron(COLOR_PAIR(7));
	for(int y = AIpad.pos_y; y < AIpad.pos_y + AIpad.height; y++)
		mvaddch(y, AIpad.pos_x, '|');
	attroff(COLOR_PAIR(7));
}

void draw_edges(int screenWidth, int screenHeight)
{
	attron(COLOR_PAIR(6));
	for(int x = 0; x < screenWidth / 2; x++)
	{
		mvaddch(0, x, '-');
		mvaddch(screenHeight - 1, x, '-');
	}
	attroff(COLOR_PAIR(6));

	attron(COLOR_PAIR(7));
	for(int x = screenWidth / 2; x < screenWidth; x++)
	{
		mvaddch(0, x, '-');
		mvaddch(screenHeight - 1, x, '-');
	}
	attroff(COLOR_PAIR(7));

	attron(COLOR_PAIR(5));
	for(int y = 0; y < screenHeight; y++)
	{
		mvaddch(y, 0, '|');
		mvaddch(y, screenWidth - 1, '|');
	}
	for(int y = 0; y < screenHeight; y++)
	{
		// mvaddch(y, 0, '|');
		mvaddch(y, screenWidth / 2, '|');
	}
	attroff(COLOR_PAIR(5));
}

void move_ball(ball *ball)
{
	ball->x += ball->dx;
	ball->y += ball->dy;
}

void draw_ball(ball *ball)
{
	attron(COLOR_PAIR(10));
	mvaddch(ball->y, ball->x, '*');
	attroff(COLOR_PAIR(10));
}

int collision(paddle *pad, paddle *AIpad, ball *ball, int screenH, int screenW, player *p1, player *p2)
{
	if (ball->x == pad->pos_x + pad->width && ball->y >= pad->pos_y && ball->y < pad->pos_y + pad->height)
	{
		ball->dx = -ball->dx;
		printf("coli\n");
	}

	if (ball->x == AIpad->pos_x - ball->width && ball->y >= AIpad->pos_y && ball->y < AIpad->pos_y + AIpad->height + 1)
		ball->dx = -ball->dx;

	if (ball->x == pad->pos_x - ball->width && ball->y >= pad->pos_y && ball->y < pad->pos_y + pad->height + 1)
		ball->dx = -ball->dx;

	if (ball->y <= 0 || ball->y >= screenH - ball->height)
	{
		ball->dy = -ball->dy;
		ball->dx = ball->dx;
	}

	if (ball->x <= 0 - ball->width)
		ball->dx = -ball->dx;

	if (ball->x <= 0 + ball->width)
	{
		ball->dx = 0;
		ball->x = screenW / 2;
		ball->y = screenH / 2;
		napms(10);
		p1->point++;
		ball->dx = -ball->dx + 1;
	}

	if (ball->x >= screenW + ball->width)
	{
		ball->dx = 0;
		ball->x = screenW / 2;
		ball->y = screenH / 2;
		napms(10);
		p2->point++;
	}

	if (AIpad->pos_y < 0)
		AIpad->pos_y = 0;
	else if (AIpad->pos_y + AIpad->height > screenH)
		AIpad->pos_y = screenH - AIpad->height;

	if (pad->pos_y < 0)
		pad->pos_y = 0;
	else if(pad->pos_y + pad->height > screenH)
		pad->pos_y = screenH - pad->height;

	return 0;
}

void score(int screenH, int screenW, player *p1, player *p2)
{
	player player1 = *p1;
	player player2 = *p2;

	mvprintw(screenH / 4, screenW / 2 - 15, "%d", player2.point);
	mvprintw(screenH / 5, screenW / 2 + 6, "Player 2");
	mvprintw(screenH / 5, screenW / 2 - 15, "Player 1");
	mvprintw(screenH / 4, screenW / 2 + 6, "%d", player1.point);

	FILE *fp = fopen("score.txt", "w");
	fscanf(fp, "%d\n", &player1.point);
	fprintf(fp, "Player 1 score: %d\n", player1.point);
	fscanf(fp, "%d\n", &player2.point);
	fprintf(fp, "Player 2 score: %d\n", player2.point);
	fclose(fp);
}

void get_input(paddle *pad, paddle *AIpad, ball *ball)
{
	int key = getch();
	switch (key) {
		case KEY_UP:
			AIpad->pos_y -= 2;
			break;
		case KEY_DOWN:
			AIpad->pos_y += 2;
			break;
		case KEY_RIGHT:
			ball->dx = 1;
			break;
		case KEY_LEFT:
			ball->dx = -1;
		case 'w':
			pad->pos_y -= 5;
			break;
		case 's':
			pad->pos_y += 5;
			break;
	}
}


