#include <graph.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "functions.h"
#include "main.h"
#include "game.h"

void ggrid(int w, int h, int c, int r, _c color) {
    gchoose(color); // on choisit la couleur
    for(int i = 1; i <= c; i++) { // pour chacune des colones c;
        gseg(w/c*i, 0, w/c*i, h); //on divise la largeur de la fenetre par le nb de colone (GRID) que l'on multiplie par la colone désirer

    }
    for (int j = 1; j <= r; j++) {
        gseg(0, h/r*j, w, h/r*j);
    }
}

// permet de recuperer les coodronné graphique a partir de la HEIGT/WIDTH, du coef GRID et de la case k
int ggetCoords(int wh, int grid, int k) { return wh/(wh/grid)*k; }

//retourne la distance entre de points (permet de caclculer si on est sur une pomme ou pas, ou si on se mange soit meme)
double ggetDist(int x, int y, int xx, int yy) { return sqrt(pow(xx - x, 2) + pow(yy - y, 2)); } // formule de la distance entre deux points du plan

void ghead(int x, int y, _c c) {
    int xx = ggetCoords(WIDTH, GRID, x);
    int yy = ggetCoords(HEIGHT, GRID, y);
    gchoose(c);
    gfillRect(xx, yy, GRID, GRID);
}

_c wheel(int p) {
    if(p < 85) {
        return grgb(p*3, 255-p*3, 0);
    } else if(p < 170) {
        p -= 85;
        return grgb(255-p*3, 0, p*3);
    } else {
        p -= 170;
        return grgb(0, p*3, 255-p*3);
    }
}


//ajoute les coordonnées x,y au debut de la liste
List* pushTop(List* list, int x, int y, _c c) {
    List* new;
    new = (List*) malloc(sizeof(List));
    new->c = c;
    new->x = x;
    new->y = y;
    if (list == NULL) {
        new->prev = list;
        new->next = NULL;
    } else {
        list->prev = new;
        new->next = list;
        new->prev = NULL;
    }
    return new;
}

//ajoute les coordonnées x,y a la fin de la liste
List* pushBot(List* list, int x, int y, _c c) {
    List* new;
    new = (List*) malloc(sizeof(List));
    new->c = c;
    new->x = x;
    new->y = y;

    if (list == NULL) {
        new->next = list;
        new->prev = NULL;
        return new;
    } else {
        List* cur = list;
        for (; cur->next != NULL; cur = cur->next)
            ;
        new->prev = NULL;
        cur->next = new;
        new->prev = cur;
        return list;
    }
}
//supprimer la derniere coordonnée de la liste
List* popBot(List* list) {
    if (list == NULL) {
        return list;
    } else {
        List* cur = list;
        for (; cur->next != NULL; cur = cur->next)
            ;
        cur->prev->next = NULL;
        free(cur);
        return list;
    }
}

//supprime le p ième bloc de la liste
List* pop(List* list, int x, int y, _c c, int p) {

    if (p == 0 || list == NULL) return pushTop(list, x, y, c);

    List* cur = list;
    int k = 0;
    for(; (cur->next != NULL) && (k<p-1); cur = cur->next) {k++;};

    if(cur->next == NULL) return pushBot(list, x, y, c);

    List* new = (List*) malloc(sizeof(List));
    List* tmp = cur->next;
    new->c = c;
    new->x = x;
    new->y = y;
    tmp->prev = new;
    new->next = tmp;
    cur->next = new;
    new->prev = cur;
    return list;

}
//affiche le serpent sur la grille
void disp(List* list) {
    List* cur = list;
    #ifdef DEBUG
        printf("[");
    #endif DEBUG
    for (; cur != NULL; cur = cur->next) {
        ghead(cur->x, cur->y, cur->c);
        #ifdef DEBUG
            printf("{x: %d, y: %d}", cur->x, cur->y);
            if (cur->next!=NULL) printf(", ");
        #endif DEBUG
    }
    #ifdef DEBUG
        printf("]\n");
    #endif DEBUG
}