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
