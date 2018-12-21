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
    List* list = NULL; // initialisation de la Liste List qui contient le serpents voire "game.c"
    int running = 1; // tant que running est a 1 le programme continue
    int x = 0, y = 0, //x, y correspodent a la grille
        xx = 0, yy = 0; // xx, yy correspondent aux coordonnée de pixel
    list = pushBot(list, x, y);//premier bloc du serpent
    //gchoose(grgb(255,0,0));

    while (running) {
        gscreen(1); //basculage sur l'ecran fictif
        gclear(grgb(0,0,0)); //clear l'ecran
        ggrid(WIDTH, HEIGHT, WIDTH/GRID, HEIGHT/GRID, grgb(60,60,255)); // afficher la grille
        //ghead(x, y, grgb(255,0,0)); //afficher un carré rouge aux positions x, y
        #ifdef DEBUG
            printf("[%d|%d][%d|%d]\n", x, xx, y, yy);
        #endif /* DEBUG */
        disp(list); // affiche l'intégralité de serpent



        if (gdoKey()) { // si une touche est dispo
            switch(ggetKey()) { //on teste la touche dispo, les variable XK_... sont definit dans <graph.h>
                case XK_Escape: running = 0;                    break;
                case XK_space:  list = pushBot(list, x, y);     break; //'temporaire' ajoute juste un bloc au serpent pour le ralonger pour les tests
                case XK_Left:   if (x>0)                x--;    break;  //fleche gauche diminue x, si il est > a 0, pour ne pas sortir de la fenetre
                case XK_Right:  if (x<WIDTH/GRID-1)     x++;    break;  //fleche droite augment x si il est inférieut a la taille de la fenetre diviser par le coef de la grille, pour pas sortir
                case XK_Down:   if (y<HEIGHT/GRID-1)    y++;    break;  //meme principe pour le haut le bas
                case XK_Up:     if (y>0)                y--;    break;
            }
            list = pushTop(list,x,y); //rajoute la nouvelle tete du serpent
            list = popBot(list); //supprimer la queue du serpent
        }

        gcopy(1,0,0,0,WIDTH,HEIGHT,0,0);// bascule l'ecran fictif sur l'ecran affiché
    }

    return 0;
}
