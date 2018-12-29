#include <graph.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "functions.h"
#include "main.h"
#include "game.h"

void ggrid(int w, int h, int c, int r, col color) {
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

void ghead(int x, int y, col c) {
    int xx = ggetCoords(WIDTH, GRID, x);
    int yy = ggetCoords(HEIGHT, GRID, y);
    gchoose(c);
    gfillRect(xx, yy, GRID, GRID);
}

Snake* initSnake(int x, int y, int dir_x, int dir_y, col c, int l, int s) {

    Snake* snake = (Snake*) malloc(sizeof(Snake));
    Head* head = (Head*) malloc(sizeof(Head));
    Tail* tail = (Tail*) malloc(sizeof(Tail));
    snake->head = head;
    snake->head->x = x;
    snake->head->y = y;
    snake->head->dir_x = dir_x;
    snake->head->dir_y = dir_y;
    snake->head->c = c;
    snake->tail = tail;
    snake->length = l;
    snake->speed = s;

    snake->tail = pushBot(snake->tail, snake->head->x, snake->head->y, snake->head->c);

    return snake;
}

col wheel(int p) {
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
Tail* pushTop(Tail* tail, Head* head, col c) {
    Tail* new;
    new = (Tail*) malloc(sizeof(Tail));
    new->c = c;
    new->x = head->x - head->dir_x;
    new->y = head->y - head->dir_y;
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

//ajoute les coordonnées x,y a la fin de la liste
Tail* pushBot(Tail* tail, int x, int y, col c) {
    Tail* new;
    new = (Tail*) malloc(sizeof(Tail));
    new->c = c;
    new->x = x;
    new->y = y;
    printf("%p\n", tail);
    if (tail == NULL) {
        new->next = tail;
        new->prev = NULL;
        return new;
    } else {
        Tail* cur = tail;
        for (; cur->next != NULL; cur = cur->next)
            ;
        new->prev = NULL;
        cur->next = new;
        new->prev = cur;
            printf("%d, %d\n", tail->x, tail->y);
        return tail;
    }
}


//ajoute les coordonnées x,y a la fin de la liste
Tail* pushTail(Tail* tail, Head* head, col c) {
    Tail* new;
    new = (Tail*) malloc(sizeof(Tail));
    new->c = c;

    if (tail == NULL) {
        new->next = tail;
        new->prev = NULL;
        new->x = head->x - head->dir_x;
        new->y = head->y - head->dir_y;
        return new;
    } else {
        Tail* cur = tail;
        for (; cur->next != NULL; cur = cur->next)
            ;
        new->x = cur->x - head->dir_x;
        new->y = cur->y - head->dir_y;
        new->prev = NULL;
        cur->next = new;
        new->prev = cur;
        return tail;
    }
}

//supprimer la derniere coordonnée de la liste
Tail* popBot(Tail* list) {
    if (list == NULL) {
        return list;
    } else {
        Tail* cur = list;
        for (; cur->next != NULL; cur = cur->next)
            ;
        cur->prev->next = NULL;
        free(cur);
        return list;
    }
}

//supprime le p ième bloc de la liste
Tail* pop(Tail* list, int x, int y, col c, int p) {

    //if (p == 0 || list == NULL) return pushTop(list, x, y, c);

    Tail* cur = list;
    int k = 0;
    for(; (cur->next != NULL) && (k<p-1); cur = cur->next) {k++;};

    if(cur->next == NULL) return pushBot(list, x, y, c);

    Tail* new = (Tail*) malloc(sizeof(Tail));
    Tail* tmp = cur->next;
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
void disp(Tail* list) {
    Tail* cur = list;
    #ifdef DEBUG
        printf("[");
    #endif /* DEBUG */
    if (cur != NULL) {
        for (; cur != NULL; cur = cur->next) {
            ghead(cur->x, cur->y, cur->c);
            #ifdef DEBUG
                printf("{x: %d, y: %d}", cur->x, cur->y);
                if (cur->next!=NULL) printf(", ");
            #endif /* DEBUG */
        }
    }
    #ifdef DEBUG
        printf("]\n");
    #endif /* DEBUG */
}