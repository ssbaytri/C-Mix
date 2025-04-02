#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_SCORE 256
#define FRAME_TIME 111000

typedef struct
{
	int x;
	int y;
} vec2;

int score = 0;
char score_text[16];

bool skip = false;
bool is_running = true;

int sw = 25;
int sh = 20;

WINDOW *win;

vec2 head = {0, 0};
vec2 dir = {1, 0};
vec2 segments[MAX_SCORE + 1];
vec2 food;

void restart_game()
{
	head.x = 0;
	head.y = 0;
	dir.x = 1;
	dir.y = 0;
	score = 0;
	sprintf(score_text, "[ Score: %d ]", score);
	is_running = true;
}

void quit_game()
{
	endwin();
	printf("\e[1;1H\e[2J");
	printf("\e[?25h");
	exit(0);
}

void handle_events()
{
	int pressed = wgetch(win);
	if (pressed == KEY_LEFT)
	{
		if (dir.x == 1)
		{
			skip = true;
			return;
		}
		dir.x = -1;
		dir.y = 0;
	}
	if (pressed == KEY_RIGHT)
	{
		if (dir.x == -1)
		{
			skip = true;
			return;
		}
		dir.x = 1;
		dir.y = 0;
	}
	if (pressed == KEY_UP)
	{
		if (dir.y == 1)
		{
			skip = true;
			return;
		}
		dir.x = 0;
		dir.y = -1;
	}
	if (pressed == KEY_DOWN)
	{
		if (dir.y == -1)
		{
			skip = true;
			return;
		}
		dir.x = 0;
		dir.y = 1;
	}
	if (pressed == ' ')
	{
		if (!is_running)
			restart_game();
	}
	if (pressed == '\e')
	{
		is_running = false;
		quit_game();
	}
}

void init()
{
	srand(time(NULL));
	win = initscr();
	keypad(win, true);
	noecho();
	nodelay(win, true);
	curs_set(0);
	if (has_colors() == FALSE)
	{
		endwin();
		fprintf(stderr, "Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	use_default_colors();
	init_pair(1, COLOR_RED, -1);
	init_pair(2, COLOR_GREEN, -1);
	init_pair(3, COLOR_YELLOW, -1);

	food.x = rand() % sw;
	food.y = rand() % sh;
	sprintf(score_text, "[ Score: %d ]", score);
}

bool collide(vec2 a, vec2 b)
{
	return a.x == b.x && a.y == b.y;
}

bool collide_self(vec2 pos)
{
	for (int i = 0; i < score; i++)
	{
		if (collide(pos, segments[i]))
			return true;
	}
	return false;
}

void draw_border(int y, int x, int w, int h)
{
	mvaddch(y, x, ACS_ULCORNER);
	mvaddch(y, x + w * 2 + 1, ACS_URCORNER);
	for (int i = 1; i < w * 2 + 1; i++)
		mvaddch(y, x + i, ACS_HLINE);
	for (int i = 1; i < h + 1; i++)
	{
		mvaddch(y + i, x, ACS_VLINE);
		mvaddch(y + i, x + w * 2 + 1, ACS_VLINE);
	}
	mvaddch(y + h + 1, x, ACS_LLCORNER);
	mvaddch(y + h + 1, x + w * 2 + 1, ACS_LRCORNER);
	for (int i = 1; i < w * 2 + 1; i++)
		mvaddch(y + h + 1, x + i, ACS_HLINE);
}

void draw()
{
	erase();
	attron(COLOR_PAIR(1));
	mvaddch(food.y + 1, food.x * 2 + 1, '@');
	attroff(COLOR_PAIR(1));

	attron(COLOR_PAIR(2));
	for (int i = 0; i < score; i++)
		mvaddch(segments[i].y + 1, segments[i].x * 2 + 1, ACS_DIAMOND);
	mvaddch(head.y + 1, head.x * 2 + 1, 'O');
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(3));
	draw_border(0, 0, sw, sh);
	attroff(COLOR_PAIR(3));
	mvaddstr(0, sw - 5, score_text);
}

void game_over()
{
	while (is_running == false)
	{
		handle_events();
		mvaddstr(sh / 2, sw - 16, "              Game Over          ");
		mvaddstr(sh / 2 + 1, sw - 16, "[SPACE] to restart, [ESC] to quit ");
		attron(COLOR_PAIR(3));
		draw_border(sh / 2 - 1, sw - 17, 17, 2);
		attroff(COLOR_PAIR(3));
		usleep(FRAME_TIME);
	}
}

vec2 reset_food()
{
	vec2 new_food = {1 + rand() % (sw - 2), 1 + rand() % (sh - 2)};
	while (collide(head, new_food) || collide_self(new_food))
	{
		new_food.x = 1 + rand() % (sw - 2);
		new_food.y = 1 + rand() % (sh - 2);
	}
	return new_food;
}

void update()
{
	for (int i = score; i > 0; i--)
		segments[i] = segments[i - 1];
	segments[0] = head;

	head.x += dir.x;
	head.y += dir.y;

	if (collide_self(head) || head.x < 0 || head.x >= sw || head.y < 0 || head.y >= sh)
	{
		is_running = false;
		game_over();
	}
	if (collide(head, food))
	{
		if (score < MAX_SCORE)
		{
			score++;
			sprintf(score_text, "[ Score: %d ]", score);
		}
		else
			printf("You Win!\n");
		food = reset_food();
	}
	usleep(FRAME_TIME);
}

int main()
{
	init();
	while (is_running)
	{
		handle_events();
		if (skip)
		{
			skip = false;
			continue;
		}
		update();
		draw();
	}
	quit_game();
	return 0;
}
