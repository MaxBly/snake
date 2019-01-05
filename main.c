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
    int running = 1;                // tant que running est a 1 le programme continue
    int go_on = 0;
    int another = 0;
    int total = 0;
    int center_x = WIDTH/GRID/2;
    int center_y = HEIGHT/GRID/2;

    _c c = wheel(total);
    Snake* snake = NULL;
    snake = initSnake(snake, center_x, center_y, 0, 0, 10, 1);
    
    Garden* garden = NULL;
    garden = initGarden(garden, 0, 0);
    
    unsigned long next = gms() + CYCLE;

    while (running) {
        gscreen(1);             //basculage sur l'ecran fictif
        gclear(grgb(0,0,0));    //clear l'ecran
        ggrid(WIDTH, HEIGHT, WIDTH/GRID, HEIGHT/GRID, grgb(60,60,60)); // afficher la grille

        if (another) { 
            snake->tail = pushTop(snake->tail, snake->x, snake->y, c); 
            another = 0;
            snake->length++;
        }
        if ((gms() > next) && go_on) { // a chaque cycle de temps, définit par la constante CYCLE (dans main.h)
            next = gms() + (CYCLE/snake->speed/0.50);
            // on bouge le curseur seulement si on a la garanti qu'il ne sort pas du cadre
            if ((snake->x + snake->dir_x < WIDTH /GRID) && (snake->x + snake->dir_x >= 0)) snake->x = snake->x + snake->dir_x;
            if ((snake->y + snake->dir_y < HEIGHT/GRID) && (snake->y + snake->dir_y >= 0)) snake->y = snake->y + snake->dir_y;
            c = wheel(5*snake->length);
            snake->tail = pushTop(snake->tail, snake->x, snake->y, c); // on ralonge le serpent
            snake->tail = popBot (snake->tail);                        //supprimer la queue du serpent
            if (garden->apples == NULL) {
                garden = initGarden(garden, garden->level + 1, garden->eaten);
                snake->speed++;
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
                    total += 10;
                    if (total>255) total = 0;
                    snake->tail = pushTop(snake->tail, snake->x, snake->y, c);
                    another = 1;
                    snake->length++;
                }
            }

            if (snake->tail != NULL) { // on ne prend pas en compte la tete du serpent
                List* cur = snake->tail->next;
                for(; cur->next != NULL; cur = cur->next) { // on parcours tout le serpent sauf la tete
                    if ((cur->x == snake->x + snake->dir_x) && (cur->y == snake->y + snake->dir_y)) {   // sa tete du serpent passe sur un bloc deja existant on reset le serpent
                        printf("%d reset\n", total);
                        snake = initSnake(snake, center_x, center_y, 0, 0, 10, 1);
                        garden = initGarden(garden, 0, 0);
                    }
                }
            }
        }
        disp(snake->tail, c);
        if (garden->apples) disp(garden->apples, wheel(total));
        if (garden->obs) disp(garden->obs, wheel(total));
        dispsnk(snake);
        dispgar(garden);

        if (gdoKey()) { // si une touche est dispo
            switch(ggetKey()) { // on teste la touche dispo, les variable XK_... sont definit dans <graph.h>
                case XK_Escape: running = 0;                                break; // running passe a 0 donc on quitte le jeu
                case XK_space:  go_on = !go_on; if (!snake->dir_x && !snake->dir_y) snake->dir_y = -1;   break; //pause
                case XK_Return: snake->dir_x = 0; snake->dir_y = 0;                              break; //'temporaire' ajoute juste un bloc au serpent pour le ralonger pour les tests
                case XK_Left:   if (snake->dir_x !=  1) snake->dir_x = -1, snake->dir_y = 0;     break; //on change la diréction seulement si ce n'est pas la direction opposé
                case XK_Right:  if (snake->dir_x != -1) snake->dir_x =  1, snake->dir_y = 0;     break;
                case XK_Down:   if (snake->dir_y != -1) snake->dir_y =  1, snake->dir_x = 0;     break;
                case XK_Up:     if (snake->dir_y !=  1) snake->dir_y = -1, snake->dir_x = 0;     break;
            }
        }
        gcopy(1, 0, 0, 0, WIDTH, HEIGHT, 0, 0); // bascule l'ecran fictif sur l'ecran affiché
    }

    return 0;
}
