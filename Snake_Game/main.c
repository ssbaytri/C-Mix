#include <curses.h>
#include <unistd.h>

typedef struct 
{
	int x;
	int y;
} vec2;

int main()
{
	int sh = 40;
	int sw = 20;

	WINDOW *win = initscr();

	keypad(win, true);
	nodelay(win, true);
	curs_set(0);

	vec2 head = {0, 0};
	vec2 dir = {1, 0};

	while (true)
	{
		int pressed = wgetch(win);
		if (pressed == KEY_LEFT)
		{
			dir.x = -1;
			dir.y = 0;
		}
		if (pressed == KEY_RIGHT)
		{
			dir.x = 1;
			dir.y = 0;
		}
		if (pressed == KEY_UP)
		{
			dir.x = 0;
			dir.y = -1;
		}
		if (pressed == KEY_DOWN)
		{
			dir.x = 0;
			dir.y = 1;
		}
		if (pressed == '\e')
			break;

		head.x += dir.x;
		head.y += dir.y;

		erase();
		mvaddch(head.y, head.x, 'o');
		usleep(125000);
	}
	endwin();
	return 0;
}
