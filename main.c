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

    ops->center_x = ops->width/ops->grid/2;
    ops->center_y = ops->height/ops->grid/2;
    ops->in_menu = 1;

    ginitWindow(100,100,WINDOW_WIDTH,WINDOW_HEIGHT);
    gclear(grgb(45,45,45));
    Snake* snake = NULL;
    Garden* garden = NULL;

    unsigned long next = gms() + ops->cycle;
    unsigned long nextframe = gms() + (60/ops->fps)*1000;
    int menu = 0;
    while (ops->running) {
        if (gms() > nextframe) {
            nextframe = gms() + (60/ops->fps)*1000;
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
                        garden = initGarden(garden, ops, garden->level + 1, garden->eaten);
                        snake->speed++;
                    }

                    if ((snake->tail->next->x + snake->dir_x >= ops->width /ops->grid) || (snake->tail->next->x + snake->dir_x == -1)
                    ||  (snake->tail->next->y + snake->dir_y >= ops->height/ops->grid) || (snake->tail->next->y + snake->dir_y == -1)) {
                        snake = initSnake(snake, ops->center_x, ops->center_y, 0, 0, ops->snake, 1);
                        garden = initGarden(garden, ops, 0, 0);
                    }
                    for (List* cur = garden->obs; cur != NULL; cur = cur->next) {
                        if (cur->x == snake->x && cur->y == snake->y) {
                            snake = initSnake(snake, ops->center_x, ops->center_y, 0, 0, ops->snake, 1);
                            garden = initGarden(garden, ops, 0, 0);
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
                                snake = initSnake(snake, ops->center_x, ops->center_y, 0, 0, ops->snake, 1);
                                garden = initGarden(garden, ops, 0, 0);
                            }
                        }
                    }
                }
                disp(ops, snake->tail, wheel(snake->wheel));
                if (garden->apples) disp(ops, garden->apples, wheel(snake->wheel));
                if (garden->obs) disp(ops, garden->obs, wheel(snake->wheel));
                //score(ops, garden);
                #ifdef DEBUG
                    dispsnk(snake);
                    dispgar(garden);
                #endif /* DEBUG */
                if (gdoKey()) {
                    switch(ggetKey()) {
                        case XK_Escape: ops->in_game = 0; ops->in_menu = 1;                             break;
                        case XK_space:  snake = pause(snake);                                           break;
                        case XK_Left:   if (snake->dir_x !=  1) snake->dir_x = -1, snake->dir_y = 0;    break;
                        case XK_Right:  if (snake->dir_x != -1) snake->dir_x =  1, snake->dir_y = 0;    break;
                        case XK_Down:   if (snake->dir_y != -1) snake->dir_y =  1, snake->dir_x = 0;    break;
                        case XK_Up:     if (snake->dir_y !=  1) snake->dir_y = -1, snake->dir_x = 0;    break;
                    }
                }
            gcopy(1, 0, 0, 0, ops->width, ops->height, (WINDOW_WIDTH - ops->width)/2, (WINDOW_HEIGHT - ops->height)/2);
            gscreen(0);
            score(ops, garden);
            level(ops, garden);
            gscreen(1);
            } else if (ops->in_menu) {


                btn(2, "PLAY",  grgb(0, 0, 0), grgb(255, 255, 255), (menu == 0));
                btn(4, "OPTIONS",  grgb(0, 0, 0), grgb(255, 255, 255), (menu == 1));
                btn(6, "QUIT",  grgb(0, 0, 0), grgb(255, 255, 255), (menu == 2));
                if(gdoKey()) {
                    switch(ggetKey()) {
                        case XK_Escape: ops->running = 0;   break;
                        case XK_Up:   if(menu > 0) menu--; break;
                        case XK_Down: if(menu < 2) menu++; break;
                        case XK_Return:
                            switch(menu) {
                                case 0:
                                    ops->in_menu = 0;
                                    ops->center_x = ops->width/ops->grid/2;
                                    ops->center_y = ops->height/ops->grid/2;
                                    snake = initSnake(snake, ops->center_x, ops->center_y, 0, 0, ops->snake, 1);
                                    garden = initGarden(garden, ops, 0, 0);
                                    ops->in_game = 1;
                                break;
                                case 1:
                                    ops->in_menu = 0;
                                    ops->in_opts = 1;
                                break;
                                case 2:
                                    ops->running = 0;
                                break;
                            }
                        break;
                    }
                }
                gcopy(1, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
            } else if (ops->in_opts) {
                btnScroll(3,  "LENGHT", ops->snake , grgb(0, 0, 0), grgb(255, 255, 255), (menu == 0));
                btnScroll(5,  "APPLES", ops->apples, grgb(0, 0, 0), grgb(255, 255, 255), (menu == 1));
                btnScroll(7,  "GRID"  , ops->grid  , grgb(0, 0, 0), grgb(255, 255, 255), (menu == 2));
                btnScroll(9,  "WIDTH" , ops->width /ops->grid, grgb(0, 0, 0), grgb(255, 255, 255), (menu == 3));
                btnScroll(11,  "HEIGHT", ops->height/ops->grid, grgb(0, 0, 0), grgb(255, 255, 255), (menu == 4));
                btnScroll(13,  "FPS", ops->fps, grgb(0, 0, 0), grgb(255, 255, 255), (menu == 5));
                if(gdoKey()) {
                    switch(ggetKey()) {
                        case XK_Escape: ops->in_opts = 0; ops->in_menu = 1;  break;
                        case XK_Up:     if(menu > 0) menu--; break;
                        case XK_Down:   if(menu < 5) menu++; break;
                        case XK_Right:
                            switch(menu) {
                                case 0: ops->snake++ ; break;
                                case 1: ops->apples++; break;
                                case 2: ops->grid++  ; break;
                                case 3: ops->width  += ops->grid; break;
                                case 4: ops->height += ops->grid; break;
                                case 5: ops->fps++; break;
                            }
                        break;
                        case XK_Left:
                            switch(menu) {
                                case 0: ops->snake-- ; break;
                                case 1: ops->apples--; break;
                                case 2: ops->grid--  ; break;
                                case 3: ops->width  -= ops->grid; break;
                                case 4: ops->height -= ops->grid; break;
                                case 5: ops->fps--; break;
                            }
                        break;
                        case XK_Return:
                        break;
                    }
                }
                gcopy(1, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
            }
        }//nextframe
    }

    return 0;
}