#include "menu.h"

#ifndef GAME_H
#define GAME_H

typedef struct List List;
struct List {
    int x;
    int y;
    _c c;
    List* prev;
    List* next;
};

typedef struct Snake Snake;
struct Snake {
    int length;
    int speed;
    int x;
    int y;
    int dir_x;
    int dir_y;
    int wheel;
    int go_on;
    List* tail;
};

typedef struct Garden Garden;
struct Garden {
    int level;
    int eaten;
    List* apples;
    List* obs;
};

void    ggrid       (int, int, int, int, _c);
int     ggetCoords  (int, int, int);
void    ghead       (Options*, int, int, _c);
_c      wheel       (int);

Snake*  initSnake   (Snake*, int, int, int, int, int , int);
Garden* initGarden  (Garden*, Options*, int, int);
Snake*  pause       (Snake*);

List*   pushTop (List*, int, int, _c);
List*   pushBot (List*, int, int, _c);
List*   popBot  (List*);
List*   push    (List*, int, int, int, _c);
void    disp    (Options*, List*, _c);

void    score   (Options*, Garden*);

void    dispgar (Garden*);
void    dispsnk (Snake*);

#endif /* GAME_H */