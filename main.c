#include <graph.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "game.h"
#include "main.h"
#include "menu.h"

int main(void) {
    srand(gms());
    gbegin();

    Options* ops = initOptions(ops, WIDTH, HEIGHT, GRID, CYCLE, APPLES, SNAKE);

    ops->in_menu = 1;

    ginitWindow(100,2100,WINDOW_WIDTH,WINDOW_HEIGHT);
    gclear(grgb(45,45,45));
    int center_x = ops->width/ops->grid/2;
    int center_y = ops->height/ops->grid/2;

    Snake* snake = initSnake(snake, center_x, center_y, 0, 0, ops->snake, 1);

    Garden* garden = initGarden(garden, 0, 0);

    unsigned long next = gms() + CYCLE;

    while (ops->running) {
        gscreen(1);
        gclear(grgb(45,45,45));

        if (ops->in_game) {
            ggrid(ops->width, ops->height, ops->width/ops->grid, ops->height/ops->grid, grgb(60,60,60));

            if ((gms() > next) && snake->go_on) {
                next = gms() + (ops->cycle/snake->speed/0.5);
                if ((snake->x + snake->dir_x < ops->width /ops->grid) && (snake->x + snake->dir_x >= 0)) snake->x = snake->x + snake->dir_x;
                if ((snake->y + snake->dir_y < ops->height/ops->grid) && (snake->y + snake->dir_y >= 0)) snake->y = snake->y + snake->dir_y;
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
                    snake = initSnake(snake, center_x, center_y, 0, 0, ops->snake, 1);
                    garden = initGarden(garden, 0, 0);
                }
                for (List* cur = garden->obs; cur != NULL; cur = cur->next) {
                    if (cur->x == snake->x && cur->y == snake->y) {
                        snake = initSnake(snake, center_x, center_y, 0, 0, ops->snake, 1);
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
                            snake = initSnake(snake, center_x, center_y, 0, 0, ops->snake, 1);
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
                    case XK_Escape: ops->running = 0;                                            break;
                    case XK_space:  snake = pause(snake);                                           break;
                    case XK_Left:   if (snake->dir_x !=  1) snake->dir_x = -1, snake->dir_y = 0;    break;
                    case XK_Right:  if (snake->dir_x != -1) snake->dir_x =  1, snake->dir_y = 0;    break;
                    case XK_Down:   if (snake->dir_y != -1) snake->dir_y =  1, snake->dir_x = 0;    break;
                    case XK_Up:     if (snake->dir_y !=  1) snake->dir_y = -1, snake->dir_x = 0;    break;
                }
            }

            gcopy(1, 0, 0, 0, ops->width, ops->height, (WINDOW_WIDTH - ops->width)/2, (WINDOW_HEIGHT - ops->height)/2);
        }

        if (ops->in_menu) {




            if(gdoKey()) {
                switch(ggetKey()) {
                    case XK_Escape: ops->running = 0;   break;
                    case XK_Up:                             break;
                    case XK_Down:                           break;
                }
            }
        }

    }

    return 0;
}