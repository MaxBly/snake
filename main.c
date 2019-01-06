#include <graph.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "game.h"
#include "main.h"

int main(void) {
    srand(gms());
    gbegin();
    ginitWindow(100,2100,WIDTH,HEIGHT);
    gclear(grgb(45,45,45));
    int running = 1;
    int center_x = WIDTH/GRID/2;
    int center_y = HEIGHT/GRID/2;

    Snake* snake = NULL;
    snake = initSnake(snake, center_x, center_y, 0, 0, 10, 1);
    _c c = wheel(snake->wheel);

    Garden* garden = NULL;
    garden = initGarden(garden, 0, 0);

    unsigned long next = gms() + CYCLE;

    while (running) {
        gscreen(1);
        gclear(grgb(0,0,0));
        ggrid(WIDTH, HEIGHT, WIDTH/GRID, HEIGHT/GRID, grgb(60,60,60));

        if ((gms() > next) && snake->go_on) {
            next = gms() + (CYCLE/snake->speed/0.5);
            if ((snake->x + snake->dir_x < WIDTH /GRID) && (snake->x + snake->dir_x >= 0)) snake->x = snake->x + snake->dir_x;
            if ((snake->y + snake->dir_y < HEIGHT/GRID) && (snake->y + snake->dir_y >= 0)) snake->y = snake->y + snake->dir_y;
            c = wheel(snake->wheel);
            snake->tail = pushTop(snake->tail, snake->x, snake->y, wheel(snake->wheel));
            snake->tail = popBot (snake->tail);
            snake->wheel += 10;
            if (snake->wheel > 255) snake->wheel = 0;

            if (garden->apples == NULL) {
                garden = initGarden(garden, garden->level + 1, garden->eaten);
                snake->speed++;
            }

            if ((snake->tail->next->x + snake->dir_x >= WIDTH /GRID) || (snake->tail->next->x + snake->dir_x == -1)
            ||  (snake->tail->next->y + snake->dir_y >= HEIGHT/GRID) || (snake->tail->next->y + snake->dir_y == -1)) {
                snake = initSnake(snake, center_x, center_y, 0, 0, 10, 1);
                garden = initGarden(garden, 0, 0);
            }
            for (List* cur = garden->obs; cur != NULL; cur = cur->next) {
                if (cur->x == snake->x && cur->y == snake->y) {
                    snake = initSnake(snake, center_x, center_y, 0, 0, 10, 1);
                    garden = initGarden(garden, 0, 0);
                }
            }
            for (List* cur = garden->apples; cur != NULL; cur = cur->next) {
                if (cur->x == snake->x && cur->y == snake->y) {
                    if ((cur->prev != NULL) && (cur->next != NULL)) {
                        cur->prev->next = cur->next;
                        cur->next->prev = cur->prev;
                    } else if ((cur->next == NULL) && (cur->prev != NULL)) {
                        cur->prev->next = NULL;
                        free(cur);
                    } else if ((cur->prev == NULL) && (cur->next != NULL)) {
                        garden->apples = cur->next;
                        garden->apples->prev = NULL;
                        free(cur);
                    } else {
                        garden->apples = NULL;
                    }
                    garden->eaten++;
                    snake->tail = pushTop(snake->tail, snake->x, snake->y, wheel(snake->wheel));
                    snake->tail = pushTop(snake->tail, snake->x, snake->y, wheel(snake->wheel));
                    snake->length+=2;
                }
            }

            if (snake->tail != NULL) {
                List* cur = snake->tail->next;
                for(; cur->next != NULL; cur = cur->next) {
                    if ((cur->x == snake->x + snake->dir_x) && (cur->y == snake->y + snake->dir_y)) {
                        snake = initSnake(snake, center_x, center_y, 0, 0, 10, 1);
                        garden = initGarden(garden, 0, 0);
                    }
                }
            }
        }
        disp(snake->tail, wheel(snake->wheel));
        if (garden->apples) disp(garden->apples, wheel(snake->wheel));
        if (garden->obs) disp(garden->obs, wheel(snake->wheel));
        #ifdef DEBUG
            dispsnk(snake);
            dispgar(garden);
        #endif /* DEBUG */
        if (gdoKey()) {
            switch(ggetKey()) {
                case XK_Escape: running = 0;                                                    break;
                case XK_space:  snake = pause(snake);                                           break;
                case XK_Left:   if (snake->dir_x !=  1) snake->dir_x = -1, snake->dir_y = 0;    break;
                case XK_Right:  if (snake->dir_x != -1) snake->dir_x =  1, snake->dir_y = 0;    break;
                case XK_Down:   if (snake->dir_y != -1) snake->dir_y =  1, snake->dir_x = 0;    break;
                case XK_Up:     if (snake->dir_y !=  1) snake->dir_y = -1, snake->dir_x = 0;    break;
            }
        }
        gcopy(1, 0, 0, 0, WIDTH, HEIGHT, 0, 0);
    }

    return 0;
}