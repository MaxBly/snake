#include <graph.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "game.h"
#include "main.h"

int main(void) {
    gbegin();
    ginitWindow(100,100,WIDTH,HEIGHT);
    gclear(grgb(45,45,45));
    int running = 1;                // tant que running est a 1 le programme continue
    int x = 0, y = 0,               // x, y correspodent a la grille
        dir_x = 1, dir_y = 0;       // dir_x, dir_y correspondent aux prochain deplacement du snake

    List* list = NULL;              // initialisation de la Liste List qui contient le serpents voire "game.c"
    list = pushBot(list, x, y);     //premier bloc du serpent

    unsigned long next = gms() + CYCLE;

    while (running) {
        gscreen(1);             //basculage sur l'ecran fictif
        gclear(grgb(0,0,0));    //clear l'ecran
        ggrid(WIDTH, HEIGHT, WIDTH/GRID, HEIGHT/GRID, grgb(60,60,60)); // afficher la grille
        #ifdef DEBUG
            printf("[%d|%d][%d|%d]\n", x, dir_x, y, dir_y);
        #endif /* DEBUG */


        if (gms() > next) { // a chaque cycle de temps, définit par la constante CYCLE (dans main.h)
            next = gms() + CYCLE;
            if ((x+dir_x < WIDTH /GRID) && (x+dir_x >= 0))     x = x + dir_x; // on bouge le curseur seulement on a la garanti qu'il ne sort pas du cadre
            if ((y+dir_y < HEIGHT/GRID) && (y+dir_y >= 0))     y = y + dir_y;
            list = pushTop(list, x, y);   //rajoute la nouvelle tete du serpent
            list = popBot (list);         //supprimer la queue du serpent

            if (list->next != NULL) { // on ne prend pas en compte la tete du serpent
                List* cur = list->next;
                for(; cur->next != NULL; cur = cur->next) { // on parcours tout le serpent sauf la tete
                    if ((cur->x == x) && (cur->y == y)) {   // sa tete du serpent passe sur un bloc deja existant on reset le serpent
                        list = NULL;                        // cette partie corrige les collision sur le serpent et sur les bords
                        x = 0, y = 0;
                        list = pushBot(list, x, y);
                        dir_x = 1, dir_y = 0;
                    }
                }
            }
        }

        disp(list); // affiche l'intégralité de serpent

        if (gdoKey()) { // si une touche est dispo
            switch(ggetKey()) { //on teste la touche dispo, les variable XK_... sont definit dans <graph.h>
                case XK_Escape: running = 0;                            break;
                case XK_space:  list = pushBot(list, x, y);             break; //'temporaire' ajoute juste un bloc au serpent pour le ralonger pour les tests
                case XK_Left:   if (dir_x !=  1) dir_x = -1, dir_y = 0; break; //on change la diréction seulement si ce n'est pas la direction opposé
                case XK_Right:  if (dir_x != -1) dir_x =  1, dir_y = 0; break;
                case XK_Down:   if (dir_y != -1) dir_y =  1, dir_x = 0; break;
                case XK_Up:     if (dir_y !=  1) dir_y = -1, dir_x = 0; break;
            }
        }
        gcopy(1, 0, 0, 0, WIDTH, HEIGHT, 0, 0); // bascule l'ecran fictif sur l'ecran affiché
    }

    return 0;
}
