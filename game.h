
#ifndef GAME_H
#define GAME_H

typedef struct Tail Tail;
struct Tail {
    int x;
    int y;
    Tail* prev;
    Tail* next;
};

typedef struct Snake Snake;
struct Snake {
    int length;
    int speed;
    int x;
    int y;
    int dir_x;
    int dir_y;
};

typedef struct Garden Garden;
struct Garden {
    int level;
    int r;
    int n;
};

typedef struct Apples Apples;
struct Apples {
    int x;
    int y;
    Apples* prev;
    Apples* next;
};



typedef struct Apple Apple;
struct Apple {
    int x;
    int y;
};

void    ggrid       (int, int, int, int, _c);
int     ggetCoords  (int, int, int);
double  ggetDist    (int, int, int, int);

_c      wheel      (int);

Tail*   pushTop (Tail*, int, int);
Tail*   pushBot (Tail*, int, int);
Tail*   popBot  (Tail*);
Tail*   push    (Tail*, int, int, int);
void    disp    (Tail*, _c);
void    display (Tail*);

#endif /* GAME_H */