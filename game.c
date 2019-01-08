#include <graph.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "functions.h"
#include "main.h"
#include "menu.h"
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

void ghead(Options* ops, int x, int y, _c c) {
    int xx = ggetCoords(ops->width,  ops->grid, x);
    int yy = ggetCoords(ops->height, ops->grid, y);
    gchoose(c);
    gfillRect(xx, yy, ops->grid, ops->grid);
}

_c wheel(int p) {
    while (p > 255) { p -= 255; }
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

Snake* initSnake(Snake* snake, int x, int y, int dir_x, int dir_y, int length, int speed) {
    snake = (Snake*) malloc(sizeof(Snake));
    snake->go_on = 0;
    snake->x = x;
    snake->y = y;
    snake->dir_x = dir_x;
    snake->dir_y = dir_y;
    snake->length = length;
    snake->speed = speed;
    snake->tail = NULL;
    for (int i = 0; i < snake->length; i++) {
        snake->wheel = 10*(i+1);
        snake->tail = pushTop(snake->tail, snake->x, snake->y + snake->length-i-1, wheel(snake->wheel));
    }
    return snake;
}


Garden* initGarden(Garden* garden, Options* ops, int level, int eaten) {
    garden = (Garden*) malloc(sizeof(Garden));
    garden->level = level;
    garden->eaten = eaten;
    garden->apples = NULL;
    garden->obs = NULL;
    for (int i = 0; i < garden->level + ops->apples; i++) {
        garden->apples = pushTop(garden->apples, (rand() % ops->width/ops->grid), (rand() % ops->height/ops->grid), wheel(5*(garden->eaten)));
    }
    for (int i = 0; i < garden->level; i++) {
        garden->obs = pushTop(garden->obs, (rand() % ops->width/ops->grid), (rand() % ops->height/ops->grid), grgb(255,255,255));
    }
    return garden;
}

Snake* pause(Snake* snake) {
    snake->go_on = !(snake->go_on);
    if (!(snake->dir_x) && !(snake->dir_y)) snake->dir_y = -1;
    return snake;
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

//ajoute les coordonnées x,y a la fin de la tail
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

//supprime le p ième bloc de la taile
List* push(List* list, int x, int y, int p, _c c) {

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
void disp(Options* ops, List* list, _c c) {
    List* cur = list;
    for (; cur != NULL; cur = cur->next) {
        ghead(ops, cur->x, cur->y, cur->c);
        #ifdef DEBUG
            printf("x: %d, y: %d\n", cur->x, cur->y);
        #endif /* DEBUG */
    }
}

void score(Options* ops, Garden* garden) {
    char text[30];
    sprintf(text, "Score: %d", 5*garden->eaten);
    int ww = WINDOW_WIDTH;
    int wh = WINDOW_HEIGHT;
    int wc = (ww-ops->width)/2;
    int hc = (wh-ops->height)/2;
    int s = 2;
    int w = gstrSize(text, s) + 10;
    int h = gtopFontSize(s) + gbotFontSize(s) + 10;
    int x = ww - wc - w;
    int y = wh - hc;
    gchoose(grgb(45, 45, 45));
    gfillRect(x, y, w, h);
    gchoose(grgb(255, 255, 255));
    gwrite(x + 5, y + h/2, text, s);
}

void level(Options* ops, Garden* garden) {
    char text[30];
    sprintf(text, "Level: %d", garden->level);
    int ww = WINDOW_WIDTH;
    int wh = WINDOW_HEIGHT;
    int wc = (ww-ops->width)/2;
    int hc = (wh-ops->height)/2;
    int s = 2;
    int w = gstrSize(text, s) + 10;
    int h = gtopFontSize(s) + gbotFontSize(s) + 10;
    int x = wc;
    int y = wh - hc;
    gchoose(grgb(45, 45, 45));
    gfillRect(x, y, w, h);
    gchoose(grgb(255, 255, 255));
    gwrite(x + 5, y + h/2, text, s);
}


void dispgar(Garden* garden) {
    char format[30];
    sprintf(format, "l=%d; e=%d", garden->level, garden->eaten);
    gwrite(0, WINDOW_HEIGHT-40, format, 2);
}

void dispsnk(Snake* snake) {
    char format[30];
    sprintf(format, "l=%d; s=%d; w=%d; x=%d; y=%d;", snake->length, snake->speed, snake->wheel, snake->x, snake->y);
    gwrite(0, WINDOW_HEIGHT-20, format, 2);
}