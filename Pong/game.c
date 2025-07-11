#include "game.h"
#include <stdio.h>

int colors() {
    start_color();
    if (has_colors() == false) {
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
    init_pair(11, COLOR_WHITE, COLOR_BLACK); // For score display

    return 0;
}

void draw_player_pad(paddle pad) {
    attron(COLOR_PAIR(6));
    for(int y = pad.pos_y; y < pad.pos_y + pad.height; y++)
        mvaddch(y, pad.pos_x, ' ');
    attroff(COLOR_PAIR(6));
}

void draw_AIpad(paddle AIpad) {
    attron(COLOR_PAIR(7));
    for(int y = AIpad.pos_y; y < AIpad.pos_y + AIpad.height; y++)
        mvaddch(y, AIpad.pos_x, ' ');
    attroff(COLOR_PAIR(7));
}

void draw_edges(int screenWidth, int screenHeight) {
    attron(COLOR_PAIR(5));
    for(int x = 0; x < screenWidth; x++) {
        mvaddch(0, x, '-');
        mvaddch(screenHeight - 1, x, '-');
    }
    for(int y = 0; y < screenHeight; y++) {
        mvaddch(y, 0, '|');
        mvaddch(y, screenWidth - 1, '|');
    }
    attroff(COLOR_PAIR(5));
}

void move_ball(ball *ball) {
    ball->x += ball->dx;
    ball->y += ball->dy;
}

void draw_ball(ball *ball) {
    attron(COLOR_PAIR(10));
    mvaddch(ball->y, ball->x, 'O');
    attroff(COLOR_PAIR(10));
}

int collision(paddle *pad, paddle *AIpad, ball *ball, int screenH, int screenW, player *p1, player *p2) {
    // Ball collision with top and bottom
    if (ball->y <= 1 || ball->y >= screenH - 2) {
        ball->dy = -ball->dy;
    }

    // Ball collision with player paddle
    if (ball->x <= pad->pos_x + 1 && 
        ball->y >= pad->pos_y && 
        ball->y <= pad->pos_y + pad->height) {
        ball->dx = -ball->dx;
        // Add some randomness to the bounce
        ball->dy += (rand() % 3) - 1;
    }

    // Ball collision with AI paddle
    if (ball->x >= AIpad->pos_x - 1 && 
        ball->y >= AIpad->pos_y && 
        ball->y <= AIpad->pos_y + AIpad->height) {
        ball->dx = -ball->dx;
        // Add some randomness to the bounce
        ball->dy += (rand() % 3) - 1;
    }

    // Ball goes out of bounds (left side - AI scores)
    if (ball->x <= 1) {
        p2->point++;
        ball->x = screenW / 2;
        ball->y = screenH / 2;
        ball->dx = (rand() % 2) ? 1 : -1;
        ball->dy = (rand() % 2) ? 1 : -1;
        return 1;
    }

    // Ball goes out of bounds (right side - Player scores)
    if (ball->x >= screenW - 2) {
        p1->point++;
        ball->x = screenW / 2;
        ball->y = screenH / 2;
        ball->dx = (rand() % 2) ? 1 : -1;
        ball->dy = (rand() % 2) ? 1 : -1;
        return 1;
    }

    // Paddle boundary checks
    if (pad->pos_y < 1)
        pad->pos_y = 1;
    else if (pad->pos_y + pad->height > screenH - 1)
        pad->pos_y = screenH - 1 - pad->height;

    if (AIpad->pos_y < 1)
        AIpad->pos_y = 1;
    else if (AIpad->pos_y + AIpad->height > screenH - 1)
        AIpad->pos_y = screenH - 1 - AIpad->height;

    return 0;
}

void score(int screenH, int screenW, player *p1, player *p2) {
    attron(COLOR_PAIR(11));
    mvprintw(1, screenW / 4, "Player 1: %d", p1->point);
    mvprintw(1, 3 * screenW / 4 - 8, "Player 2: %d", p2->point);
    attroff(COLOR_PAIR(11));
}

void get_input(paddle *pad, paddle *AIpad, ball *ball, int *game_over) {
    int key = getch();
    
    switch (key) {
        case 'w':
        case 'W':
            pad->pos_y -= 2;
            break;
        case 's':
        case 'S':
            pad->pos_y += 2;
            break;
        case KEY_UP:
            AIpad->pos_y -= 2;
            break;
        case KEY_DOWN:
            AIpad->pos_y += 2;
            break;
        case 'q':
        case 'Q':
            *game_over = 1;
            break;
    }
}

void display_game_over(int screenH, int screenW, player *p1, player *p2) {
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(screenH / 2 - 2, screenW / 2 - 10, "GAME OVER");
    
    if (p1->point > p2->point) {
        mvprintw(screenH / 2, screenW / 2 - 15, "Player 1 wins with %d points!", p1->point);
    } else if (p2->point > p1->point) {
        mvprintw(screenH / 2, screenW / 2 - 15, "Player 2 wins with %d points!", p2->point);
    } else {
        mvprintw(screenH / 2, screenW / 2 - 10, "It's a tie!");
    }
    
    mvprintw(screenH / 2 + 2, screenW / 2 - 15, "Press any key to exit");
    attroff(COLOR_PAIR(1));
    refresh();
    getch();
}

void game_loop() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    
    if (colors() != 0) {
        return;
    }

    int screenH, screenW;
    getmaxyx(stdscr, screenH, screenW);

    paddle pad = {
        .height = 7,
        .width = 1,
        .pos_y = screenH / 2 - 3,
        .pos_x = 5
    };

    paddle AIpad = {
        .height = 7,
        .width = 1,
        .pos_y = screenH / 2 - 3,
        .pos_x = screenW - 6
    };

    ball ball = {
        .x = screenW / 2,
        .y = screenH / 2,
        .dx = (rand() % 2) ? 1 : -1,
        .dy = (rand() % 2) ? 1 : -1,
        .width = 1,
        .height = 1
    };

    player player1 = { .name = "Player 1", .point = 0 };
    player player2 = { .name = "Player 2", .point = 0 };

    int game_over = 0;
    int max_points = 5;  // Play until someone reaches 5 points

    while (!game_over) {
        clear();
        
        // Simple AI for the right paddle
        if (ball.dx > 0) {  // Only move when ball is coming towards AI
            if (AIpad.pos_y + AIpad.height/2 < ball.y) {
                AIpad.pos_y += 1;
            } else if (AIpad.pos_y + AIpad.height/2 > ball.y) {
                AIpad.pos_y -= 1;
            }
        }

        draw_edges(screenW, screenH);
        draw_player_pad(pad);
        draw_AIpad(AIpad);
        draw_ball(&ball);
        move_ball(&ball);
        collision(&pad, &AIpad, &ball, screenH, screenW, &player1, &player2);
        get_input(&pad, &AIpad, &ball, &game_over);
        
        score(screenH, screenW, &player1, &player2);
        
        // Check if game should end
        if (player1.point >= max_points || player2.point >= max_points) {
            game_over = 1;
        }
        
        refresh();
        napms(50);  // Controls game speed
    }
    
    display_game_over(screenH, screenW, &player1, &player2);
    endwin();
}

int main() {
    initscr();
    curs_set(0);
    int screenW, screenH;
    getmaxyx(stdscr, screenH, screenW);
    
    // Display welcome message
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(screenH / 2 - 2, screenW / 2 - 15, "Welcome to PONG!");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvprintw(screenH / 2, screenW / 2 - 20, "Press any key to start the game");
    mvprintw(screenH / 2 + 1, screenW / 2 - 25, "Use 'w' and 's' to move your paddle");
    mvprintw(screenH / 2 + 2, screenW / 2 - 25, "Use arrow keys to control AI paddle");
    mvprintw(screenH / 2 + 3, screenW / 2 - 25, "First to 5 points wins!");
    mvprintw(screenH / 2 + 4, screenW / 2 - 25, "Press 'q' to quit");
    attroff(COLOR_PAIR(2));
    refresh();
    
    // Wait for user input to start
    getch();
    
    // Start the game loop
    game_loop();
    
    return 0;
}