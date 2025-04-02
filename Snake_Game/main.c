#include <curses.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct 
{
	int x;
	int y;
} vec2;

int score = 0;

int main()
{
	int sh = 20;
	int sw = 20;

	WINDOW *win = initscr();

	keypad(win, true);
	nodelay(win, true);
	curs_set(0);

	vec2 head = {0, 0};
	vec2 dir = {1, 0};

	vec2 food = {rand() % sw, rand() % sh};

	while (true)
	{
		int pressed = wgetch(win);
		if (pressed == KEY_LEFT)
		{
			if (dir.x == 1) continue;
			dir.x = -1;
			dir.y = 0;
		}
		if (pressed == KEY_RIGHT)
		{
			if (dir.x == -1) continue;
			dir.x = 1;
			dir.y = 0;
		}
		if (pressed == KEY_UP)
		{
			if (dir.y == 1) continue;
			dir.x = 0;
			dir.y = -1;
		}
		if (pressed == KEY_DOWN)
		{
			if (dir.y == -1) continue;
			dir.x = 0;
			dir.y = 1;
		}
		if (pressed == '\e')
			break;

		head.x += dir.x;
		head.y += dir.y;

		if (head.x == food.x && head.y == food.y)
		{
			score++;
			food.x = rand() % sw;
			food.y = rand() % sh;
		}

		erase();
		mvaddch(food.y, food.x * 2, '@');
		mvaddch(head.y, head.x * 2, 'O');
		usleep(125000);
	}
	endwin();
	return 0;
}
