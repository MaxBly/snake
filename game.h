
#ifndef GAME_H
#define GAME_H

typedef struct Tail Tail;
struct Tail {
    int x;
    int y;
    col c;
    Tail* prev;
    Tail* next;
};

typedef struct Head Head;
struct Head {
    int x;
    int y;
    int dir_x;
    int dir_y;
    col c;
};

typedef struct Snake Snake;
struct Snake {
    Head* head;
    Tail* tail;
    int length;
    int speed;
};

typedef struct Apple Apple;
struct Apple {
    int x;
    int y;
    col c;
};

typedef struct Garden Garden;
struct Garden {
    Apple* next;
    Apple* prev;
};


void    ggrid       (int, int, int, int, col);
int     ggetCoords  (int, int, int);
double  ggetDist    (int, int, int, int);

Snake*  initSnake   (int, int, int, int, col, int, int);

col     wheel    (int);

Tail*   pushTop (Tail*, Head*, col);
Tail*   pushBot (Tail*, int, int, col);
Tail*   pushTail(Tail*, Head*, col);
Tail*   popBot  (Tail*);
Tail*   pop     (Tail*, int, int, col, int);
void    disp    (Tail*);

#endif /* GAME_H */