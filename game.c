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

/* Snake* initSnake(Snake* snake, int x, int y) {
    Snake* snake;
    snake = (Snake*) malloc(sizeof(Snake));
    
    
    return snake;
}
 */


//ajoute les coordonnées x,y au debut de la liste
Tail* pushTop(Tail* tail, int x, int y) {
    Tail* new;
    new = (Tail*) malloc(sizeof(Tail));
    new->x = x;
    new->y = y;
    if (tail == NULL) {
        new->prev = tail;
        new->next = NULL;
    } else {
        tail->prev = new;
        new->next = tail;
        new->prev = NULL;
    }
    return new;
}

//ajoute les coordonnées x,y a la fin de la tail
Tail* pushBot(Tail* tail, int x, int y) {
    Tail* new;
    new = (Tail*) malloc(sizeof(Tail));
    new->x = x;
    new->y = y;

    if (tail == NULL) {
        new->next = tail;
        new->prev = NULL;
        return new;
    } else {
        Tail* cur = tail;
        for (; cur->next != NULL; cur = cur->next)
            ; // [NULL|cur]
        new->prev = NULL;
        cur->next = new;
        new->prev = cur;
        return tail;
    }
}


//supprimer la derniere coordonnée de la liste
Tail* popBot(Tail* tail) {
    if (tail == NULL) {
        return tail;
    } else {
        Tail* cur = tail;
        for (; cur->next != NULL; cur = cur->next)
            ;
        cur->prev->next = NULL;
        free(cur);
        return tail;
    }
}

//supprime le p ième bloc de la taile
Tail* push(Tail* tail, int x, int y, int p) {

    if (p == 0 || tail == NULL) return pushTop(tail, x, y);

    Tail* cur = tail;
    int k = 0;
    for(; (cur->next != NULL) && (k<p-1); cur = cur->next) {k++;};

    if(cur->next == NULL) return pushBot(tail, x, y);

    Tail* new = (Tail*) malloc(sizeof(Tail));
    Tail* tmp = cur->next;
    new->x = x;
    new->y = y;
    tmp->prev = new;
    new->next = tmp;
    cur->next = new;
    new->prev = cur;
    return tail;

}
//affiche le serpent sur la grille
void disp(Tail* tail, _c c) {
    Tail* cur = tail;
    for (; cur != NULL; cur = cur->next) {
        ghead(cur->x, cur->y, c);
    }
}

void display(Tail* tail) {
    char format [3];
    Tail* cur = tail;
    for (int f = 0; cur != NULL; cur = cur->next, f++) {
        //sprintf(format, "%d", cur->d);
        gwrite(f*20, HEIGHT-20, format, 2);
    }
}