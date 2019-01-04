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

    int another = 0;
    int total = 0;
    int center_x = WIDTH/GRID/2;
    int center_y = HEIGHT/GRID/2;

    _c c = wheel(total);
    Snake* snake = (Snake*) malloc(sizeof(Snake)); 
    snake->length = 10;
    snake->speed = 1;
    snake->dir_x = 0;
    snake->dir_y = 0;
    snake->x = center_x;
    snake->y = center_y;

    List* tail = (List*) malloc(sizeof(List));
    for (int i = 0; i < snake->length; i++) {
        tail = pushTop(tail, snake->x, snake->y, c);
    }
    
    Garden* garden = (Garden*) malloc(sizeof(Garden));
    garden->level = 0;
    garden->n = 5;
    garden->r = 0;
    
    List* apples = NULL;
    for (int i = 0; i < garden->n; i++) {
        apples = pushTop(apples, (rand() % WIDTH/GRID), (rand() % HEIGHT/GRID), c);
    }

    unsigned long next = gms() + CYCLE;

    while (running) {
        gscreen(1);             //basculage sur l'ecran fictif
        gclear(grgb(0,0,0));    //clear l'ecran
        ggrid(WIDTH, HEIGHT, WIDTH/GRID, HEIGHT/GRID, grgb(60,60,60)); // afficher la grille

        if (another) { 
            tail = pushTop(tail, snake->x, snake->y, c); 
            another = 0;
            snake->length++;
        }
        if (gms() > next) { // a chaque cycle de temps, définit par la constante CYCLE (dans main.h)
            next = gms() + CYCLE/snake->speed;
            // on bouge le curseur seulement si on a la garanti qu'il ne sort pas du cadre
            if ((snake->x + snake->dir_x < WIDTH /GRID) && (snake->x + snake->dir_x >= 0)) snake->x = snake->x + snake->dir_x;
            if ((snake->y + snake->dir_y < HEIGHT/GRID) && (snake->y + snake->dir_y >= 0)) snake->y = snake->y + snake->dir_y;
            c = wheel(5*snake->length);
            tail = pushTop(tail, snake->x, snake->y, c); // on ralonge le serpent
            tail = popBot (tail);                        //supprimer la queue du serpent

            for (List* cur = apples; cur->next != NULL; cur = cur->next) {
                if (cur->x == snake->x && cur->y == snake->y) {
                    if ((cur->prev == NULL) && (cur->next == NULL)) {
                        apples = NULL;
                    } else {
                        cur->prev->next = cur->next;
                        cur->next->prev = cur->prev;
                    }
                    if (cur->next == NULL) {
                        cur->prev->next = NULL;
                        free(cur);
                    }
                    if (cur->prev == NULL) {
                        apples = cur->next;
                        free(cur);
                    }
                    garden->r++;
                    printf("r=%d\n", garden->r);
                    if (apples == NULL) {
                        garden->level++;
                        garden->n++;
                        garden->r = 0;
                        for (int i = 0; i < garden->n; i++) {
                            apples = pushTop(apples, (rand() % WIDTH/GRID), (rand() % HEIGHT/GRID), wheel(total));
                        }
                        snake->speed *= 1.25;
                    } else {
                        break;
                    }
                    total += 10;
                    if (total>255) total = 0;
                    tail = pushTop(tail, snake->x, snake->y, c);
                    another = 1;
                    snake->length++;
                }
            }
                /* for(List* cur = apples; cur->next != NULL; cur = cur->next) {
                    if((cur->x == snake->x) && (cur->y == snake->y)) {
                        if (cur->next == NULL) {cur->prev->next = NULL;} else {cur->prev->next = cur->next;}
                        if (cur->prev == NULL) {cur->next->prev = NULL;} else {cur->next->prev = cur->prev;}
                        free(cur);
                    
                    }
                } */

            /* if ((snake->x == apple.x) && (snake->y == apple.y)) { // si une pomme est manger on la remplace et on rallonge le serpent
                apple.x = (rand() % WIDTH /GRID); // on regénére les coordonnées
                apple.y = (rand() % HEIGHT/GRID);
                tail = pushTop(tail, snake->x, snake->y); // on ralonge le serpent
                another = 1;
                snake->length++;
            } */

            //if (snake->tail != NULL) { // on ne prend pas en compte la tete du serpent
            //    List* cur = snake->tail;
            //    for(; cur->next != NULL; cur = cur->next) { // on parcours tout le serpent sauf la tete
            //        if ((cur->x == snake->head->x) && (cur->y == snake->head->y)) {   // sa tete du serpent passe sur un bloc deja existant on reset le serpent
            //            printf("%d reset\n", total);
            //            snake = initSnake(WIDTH/GRID/2, HEIGHT/GRID/2, 0, 0, wheel(total), 0, 1);                        // cette partie corrige les collision sur le serpent et sur les bords
            //        }
            //    }
            //}
        }
        disp(tail, c); // affiche l'intégralité de serpent
        disp(apples, wheel(total)); // affiche l'intégralité de serpent
        //display(tail); // affiche l'intégralité de serpent
        display(apples, 40); // affiche l'intégralité de serpent
        display(tail, 60); // affiche l'intégralité de serpent
        dispgar(garden); // affiche l'intégralité de serpent
        //ghead(apple.x, apple.y, grgb(255, 0, 0)); // affiche la pomme

        if (gdoKey()) { // si une touche est dispo
            switch(ggetKey()) { // on teste la touche dispo, les variable XK_... sont definit dans <graph.h>
                case XK_Escape: running = 0;                                break; // running passe a 0 donc on quitte le jeu
                case XK_space:  tail = pushTop(tail, snake->x, snake->y, c); snake->length++;    break; //'temporaire' ajoute juste un bloc au serpent pour le ralonger pour les tests
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
